#include "conf_app.h"
#include "connection.h"
#include <QMessageBox>
#include <QDir>

//We need to mantain these names in order to mantain compatibility with the historical backups
//static const QString strLogicalFile="albania_dat";
//static const QString strLogFile="albania_log";
//static const QString strDatabasePath="C:\\medfisis_dat\\";
static const QString strSqlClient="sqlcmd";

conf_app::conf_app(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    setupUi(this);
    m_bConnected=false;
    cityModel=0;
    countryModel=0;
    tableModel=0;
    myProcess=0;

    initUI();
}

conf_app::~conf_app()
{
    //if (QSqlDatabase::database().isOpen()){
        if (cityModel!=0) delete cityModel;
        if (countryModel!=0) delete countryModel;
        if (tableModel!=0) delete tableModel;
    //}
    if (myProcess!=0 && myProcess->isOpen()){
        myProcess->close();
        delete myProcess;
    }
}

void conf_app::apply()
{
    saveSettings(1);
    pushApply->setEnabled(false);
    emit statusShow(tr("Location Settings successfully saved!"));
}

void conf_app::enableApply()
{
    pushApply->setEnabled(true);
}

void conf_app::initModels()
{
    if (cityModel!=0){
        delete cityModel;
        cityModel=0;
    }if (countryModel!=0){
        delete countryModel;
        countryModel=0;
    }

     cityModel = new QSqlQueryModel;
     countryModel = new QSqlQueryModel;
}

void conf_app::doBackup()
{
    if (!m_bConnected){

             QMessageBox::warning(this, tr("Backup Process"),
             tr("You must be connected to the database to perform the 'Backup'!")
             +tr("\n Please connect and try again!"));
             return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
     tr("Export backup to file"), getBackupName(), tr("Backup Files (*.bak)"));

    if (!fileName.isEmpty()){

    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    statusShow(tr("Wait..."));

        QSqlQuery query;
        QString strQuery="BACKUP DATABASE albania TO DISK = '"
            + fileName +"'";
        query.prepare(strQuery);

        if (!query.exec()){
            QString strError;
            if (QSqlDatabase::database().lastError().type()!=QSqlError::NoError)
                strError=QSqlDatabase::database().lastError().text();
            else
                strError=tr("Could not backup database!");

            QMessageBox msgBox(QMessageBox::Critical,tr("Database Error"),strError,QMessageBox::Ok,0);
            msgBox.exec();

        }else{
            statusShow(tr("Database successfully backed up to ") + fileName);
        }
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
    }
}

QString conf_app::getBackupName()
{
    QString str;
    //TODO: Change this to read data directory
    //str=QDir::currentPath() + QDir::separator();
    QSettings settings("Medstat", "App");
    if (!settings.contains("database")){

        QMessageBox::critical(this, tr("Backup database"),
                                tr("Can not read database name! Are we connected?"));
        return str;

    }
    str+=settings.value("database").toString();
    str+="_";
    str+=QDateTime::currentDateTime().toString("yyyymmddhhmmss");
    str+=".bak";
    return str;
}

void conf_app::readProcessError()
{
    QMessageBox::critical(this, tr("Restore Process"),
                            myProcess->readAllStandardError().data());
}

void conf_app::readProcessOutput()
{
    if (m_bShowSqlMessages){
        QMessageBox::information(this, tr("Restore Process"),
                                myProcess->readAllStandardOutput().data());
    }else{
        emit statusShow(myProcess->readAllStandardOutput().data());
    }
}

void conf_app::parseParams()
{
    QString str=QString(myProcess->readAllStandardOutput().data());
    if (str.contains(".mdf")){

        //removing the first bit...
        int idx=str.lastIndexOf("-");
        str=str.right(str.length()-(idx+1));
        str=str.simplified();

        QStringList strSplit=str.split(" ");

        if (strSplit.size() < 4){

            QMessageBox::critical(this, tr("Restore Process"),
             tr("Could not parse database parameters!"));
            qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
            return;
        }
        m_databaseLogicalName=strSplit[0];
        m_databasePath=strSplit[2];
        m_logLogicalName=strSplit[11];
        m_logPath=strSplit[13];

        if (m_bShowSqlMessages){

            QMessageBox::information(this, tr("Restore Process"),
                tr("Logical database name: ") + m_databaseLogicalName + "\n" +
                tr("Logical log name: ") + m_logLogicalName + "\n" +
                tr("Database physical path: ") + m_databasePath + "\n" +
                tr("Log physical path: ") + m_logPath + "\n"
                );

        }else{
            emit statusShow(
            tr("Logical database name: ") + m_databaseLogicalName + "\n" +
            tr("Logical log name: ") + m_logLogicalName + "\n" +
            tr("Database physical path: ") + m_databasePath + "\n" +
            tr("Log physical path: ") + m_logPath + "\n");
        }

    }
}

void conf_app::showSqlMessages(const bool bShow){

    m_bShowSqlMessages=bShow;
    QSettings settings("Medstat", "App");
    settings.setValue("showSqlMsg", QVariant(bShow).toString());
}

void conf_app::finishedCheckingBackupFile()
{
    processFinished();

    QStringList args;

    QSettings settings("Medstat", "App");
    if(!settings.contains("database")){

        QMessageBox::critical(this, tr("Restore Process"),
        tr("Could not find database name on the registry!\n")+
        tr("Please establish the complete connection string prior running setup!"));
        return;

    }

    QString strScript=
    "RESTORE DATABASE [" + settings.value("database").toString() +"] FROM DISK = '"
    + m_strBackupName + "' WITH FILE = 1," +
    " MOVE '" + m_databaseLogicalName +"' TO '" + m_databasePath + "'," +
    " MOVE '" + m_logLogicalName +"' TO '" + m_logPath + "'," +
    " NOUNLOAD, STATS = 10"; 

    if (!runScript(strScript,args)){
         QMessageBox::critical(this, tr("App"),
             tr("Could not create file: ") + QDir::tempPath() + QDir::separator() + "MyScript.sql");
    }

    //dont forget to reset the process!
    createProcess();

     connect(myProcess, SIGNAL(readyReadStandardOutput()),this,
        SLOT(readProcessOutput() ),Qt::UniqueConnection);

     connect(myProcess, SIGNAL(readyReadStandardError()),this,
        SLOT(readProcessError() ),Qt::UniqueConnection);

     connect(myProcess, SIGNAL(finished(int,QProcess::ExitStatus)),this,
        SLOT(finishedRestore() ),Qt::UniqueConnection);

    QString app(strSqlClient);
     myProcess->start(app, args);
     if (!myProcess->waitForStarted()) {
         QMessageBox::critical(this, tr("App"),
             tr("Could not start Sql Server from %1.").arg(app));
         return;
     }
}

void conf_app::parseBackupFileInfo()
{
    QString str=QString(myProcess->readAllStandardOutput().data());

    //removing the first bit...
    int idx=str.lastIndexOf("---");
    str=str.right(str.length()-(idx+1));
    str=str.simplified();

    QStringList strSplit=str.split(" ");

    //first exist point
    if (strSplit.size() < 25){

        QMessageBox::critical(this, tr("Restore Process"),
         tr("Could not parse database parameters!\n Restore cancelled!"));
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
        return;
    }

    //second exit point
    if (m_databaseLogicalName!=strSplit[1] || m_logLogicalName !=strSplit[25]){

        QMessageBox::warning(this, tr("Restore Process"),
        tr("Logical database name on this backup: ") + strSplit[1] + "\n" +
        tr("Logical log name on this backup: ") + strSplit[25] + "\n" +
        tr("Attention: The logical name on this backup differs from the database name!\n"));

        //qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
        //return;

    }

    if (m_bShowSqlMessages){

        QMessageBox::information(this, tr("Restore Process"),
            tr("Logical database name on this backup: ") + strSplit[1] + "\n" +
            tr("Logical log name on this backup: ") + strSplit[25] + "\n" +
            tr("Match with database logical Names: ok \n")
            );

    }else{
            emit statusShow(
                tr("Logical database name on this backup: ") + strSplit[1] + "\n" +
                tr("Logical log name on this backup: ") + strSplit[25] + "\n" +
                tr("Match with database logical Names: ok \n")
            );

    }
}

void conf_app::createProcess()
{
    if (myProcess!=0){
        myProcess->close();
        delete myProcess; myProcess=0;
    }
    myProcess=new QProcess();
}

void conf_app::finishedRestore()
{
    processFinished();
    emit statusShow(tr("Restore finished!"));
     qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );

}

void conf_app::finishedReadingNames()
{
    processFinished();

    QStringList args;

    QString strScript=
    "RESTORE FILELISTONLY"
    " FROM DISK = '" + m_strBackupName + "'"
    " WITH FILE=1"; 

    if (!runScript(strScript,args)){
         QMessageBox::critical(this, tr("App"),
             tr("Could not create file: ") + QDir::tempPath() + QDir::separator() + "MyScript.sql");
         qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
         return;
    }

    //dont forget to reset the process!
    createProcess();

     connect(myProcess, SIGNAL(finished(int,QProcess::ExitStatus)),this,
        SLOT(finishedCheckingBackupFile() ),Qt::UniqueConnection);

     connect(myProcess, SIGNAL(readyReadStandardOutput()),this,
        SLOT(parseBackupFileInfo() ),Qt::UniqueConnection);

    QString app(strSqlClient);
     myProcess->start(app, args);
     if (!myProcess->waitForStarted()) {
         QMessageBox::critical(this, tr("App"),
             tr("Could not start Sql Server from %1.").arg(app));
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
         return;
     }

}

void conf_app::processFinished()
{
     if (QFile(QDir::tempPath() + QDir::separator() + "MyScript.sql").exists()){
         if(!QFile::remove(QDir::tempPath() + QDir::separator() + "MyScript.sql")){

             QMessageBox::warning(this, tr("Restore Process"),
             tr("Could not remove temporary script file!"));
            return;
         }
     }
     statusShow(tr("Temporary script file sucessfully removed!"));
}

void conf_app::doRestore()
{
    if (m_bConnected){

             QMessageBox::warning(this, tr("Restore Process"),
             tr("You must be disconnected from the database to perform the 'Restore'!")
             +tr("\n Please disconnect and try again!"));
             return;
    }

    QSettings settings("Medstat", "App");
    if(!settings.contains("host")){

             QMessageBox::warning(this, tr("Restore Process"),
             tr("We cannot retrieve the host value from any previous connection!!")
             +tr("\n Please connect to the database to build the string, \n disconnect, and try again!"));
             return;
    }

    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    statusShow(tr("Wait..."));

    QString app(strSqlClient);
    createProcess();

    m_strBackupName = QFileDialog::getOpenFileName(this,
     tr("Read Backup"), tr(""), tr("Backup Files (*.bak)"));

    if (!m_strBackupName.isEmpty()){

         connect(myProcess, SIGNAL(finished(int,QProcess::ExitStatus)),this,
            SLOT(finishedReadingNames() ),Qt::UniqueConnection);

         connect(myProcess, SIGNAL(readyReadStandardOutput()),this,
            SLOT(parseParams() ),Qt::UniqueConnection);

        QStringList args;
        QString strScript=
        "USE FAOCASDATA \n"
        "GO \n"
        "EXEC sp_helpfile \n"
        "GO \n";

        if (!runScript(strScript,args)){
             QMessageBox::critical(this, tr("App"),
                 tr("Could not create file: ") + QDir::tempPath() + QDir::separator() + "MyScript.sql");
             qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
            return;
        }
         myProcess->start(app, args);
         if (!myProcess->waitForStarted()) {
             QMessageBox::critical(this, tr("App"),
                 tr("Could not start Sql Server from %1.").arg(app));
             return;
         }
    } else
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
}

bool conf_app::runScript(const QString strScript, QStringList& args)
{
        QFile file(QDir::tempPath() + QDir::separator() + "MyScript.sql");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
             return false;
        }
        QSettings settings("Medstat", "App");

        QTextStream out(&file);
        out << strScript;

        file.close(); 

        //replace the slashes for windows
        QString strTemp=QDir::tempPath() + QDir::separator() + "MyScript.sql";
#if defined(WIN32)
        strTemp.replace("/", "\\");
#endif
        args << QLatin1String("-S")
         << settings.value("host").toString()
         << QLatin1String("-i")
         << strTemp;

        return true;
}

void conf_app::initUI()
{
    toolbar->addAction(this->actionExit);
    toolbar->addAction(this->actionCreate_backup);
    toolbar->addAction(this->actionRestore_backup);
    toolbar->setFloatable(true);
    toolbar->setMovable(true);

     connect(actionShow_startup_message, SIGNAL(triggered(bool)),this,
        SLOT(onShowStartupMsg(bool) ),Qt::UniqueConnection);

     connect(actionCreate_backup, SIGNAL(triggered()),this,
        SLOT(doBackup() ),Qt::UniqueConnection);

     connect(actionRestore_backup, SIGNAL(triggered()),this,
        SLOT(doRestore() ),Qt::UniqueConnection);

    if (QSqlDatabase::drivers().isEmpty())
    QMessageBox::information(this, tr("No database drivers found"),
                             tr("This app requires at least one Qt database driver. "
                                "Please check the documentation how to build the "
                                "Qt SQL plugins."));

    this->cmbDriver->addItems(QSqlDatabase::drivers());

    pushDisconnect->setEnabled(false);
    groupSettings->setEnabled(false);
    groupTables->setEnabled(false);

    pushInsert->setEnabled(false);
    pushRemove->setEnabled(true);

    connect(this, SIGNAL(connectionChanged()), this,
        SLOT(onConnectionChange()));

    connect(this, SIGNAL(statusShow(const QString)), this,
        SLOT(onStatusShow(const QString)));

    loadSettings(0);

}

void conf_app::filterModel(QString strCountry)
{
    cityModel->setQuery("SELECT     dbo.Ref_Countries.Name AS country_name, dbo.Ref_Location.City_Name"
    "                       FROM         dbo.Ref_Location INNER JOIN"
    "                      dbo.Ref_Countries ON dbo.Ref_Location.Country = dbo.Ref_Countries.ID"
    "                       WHERE (dbo.Ref_Countries.Name='" + strCountry + "')"
    );

    cmbCity->setModel(cityModel);
    cmbCity->setModelColumn(1);
}

void conf_app::showEvent ( QShowEvent * event )
{
    actionShow_startup_message->setChecked(queryShowStartupMsg());
    actionShow_SQL_message->setChecked(queryShowSqlMsg());

    m_bShowSqlMessages=actionShow_SQL_message->isChecked();
}

void conf_app::onShowStartupMsgI(bool bNoShow)
{
    onShowStartupMsg(!bNoShow);
    this->actionShow_startup_message->setChecked(!bNoShow);
}

void conf_app::onShowStartupMsg(const bool bShow)
{
    QSettings settings("Medstat", "App");
    settings.setValue("showStartupMsg", QVariant(bShow).toString());
}

void conf_app::enableConnectionCtrls(const bool bEnable)
{
    lineHost->setEnabled(bEnable);
    lineDatabase->setEnabled(bEnable);
    lineUsername->setEnabled(bEnable);
    linePassword->setEnabled(bEnable);
    //lineAlias->setEnabled(bEnable);
    cmbDriver->setEnabled(bEnable);
}

void conf_app::onConnectionChange()
{
    pushConnect->setEnabled(!m_bConnected);
    pushDisconnect->setEnabled(m_bConnected);
    groupSettings->setEnabled(m_bConnected);
    groupTables->setEnabled(m_bConnected);
    enableConnectionCtrls(!m_bConnected);

}

void conf_app::disconnectDB()
{
    if (cityModel!=0){
        delete cityModel;
        cityModel=0;
    }if (countryModel!=0){
        delete countryModel;
        countryModel=0;
    }

    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("qt_sql_default_connection");

    emit statusShow(tr("Connection removed!"));

    m_bConnected=false;

    emit connectionChanged();
    groupSettings->setEnabled(m_bConnected);
    groupTables->setEnabled(m_bConnected);
}

void conf_app::connectDB()
{
    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    emit statusShow(tr("Establishing connection... wait!"));

    enableConnectionCtrls(false);

    m_bConnected=createConnection(lineHost->text(),lineDatabase->text(),
        lineUsername->text(),linePassword->text(),
        /*lineAlias->text(),*/cmbDriver->currentText());

    qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );

    if (m_bConnected){
        saveSettings(0);
        if (!fillLocations()){
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("Could not read locations from the database!"),QMessageBox::Ok,0);
            msgBox.exec();
        }
        if (!listTables()){
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("Could not read table list from the database!"),QMessageBox::Ok,0);
            msgBox.exec();
        }
        loadSettings(1);
        emit statusShow(tr("Connection sucessfully created!"));
    }else{

        QString strError;
        if (QSqlDatabase::database().lastError().type()!=QSqlError::NoError)
            strError=QSqlDatabase::database().lastError().text();
        else
            strError=tr("Could not connect to the database!");

        QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),strError,QMessageBox::Ok,0);
        msgBox.exec();

        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }

    emit connectionChanged();
    groupSettings->setEnabled(m_bConnected);
    groupTables->setEnabled(m_bConnected);
}

void conf_app::saveSettings(const int section)
{
    QSettings settings("Medstat", "App");

    if (section==0){

        settings.setValue("host", lineHost->text());
        settings.setValue("database", lineDatabase->text());
        settings.setValue("username", lineUsername->text());
        settings.setValue("password", linePassword->text());
        settings.setValue("driver", cmbDriver->currentText());

    } else if (section==1){

        settings.setValue("country", cmbCountry->currentText());
        settings.setValue("city", cmbCity->currentText());

    }
}

void conf_app::loadSettings(const int section)
{

    QSettings settings("Medstat", "App");

    if (section==0){

        //Settings for the DB credentials
        lineHost->setText(settings.contains("host")?settings.value("host").toString():".\\FAOCAS");
        lineDatabase->setText(settings.contains("database")?settings.value("database").toString():"albania");
        lineUsername->setText(settings.contains("username")?settings.value("username").toString():"dev");
        linePassword->setText(settings.contains("password")?settings.value("password").toString():"test123");
        cmbDriver->setCurrentIndex(
                cmbDriver->findText(settings.contains("driver")?
                settings.value("driver").toString():"QODBC3"));

    } else if (section==1){

        int found= cmbCountry->findData(settings.value("country").toString(),Qt::DisplayRole,Qt::MatchExactly);
        if (found !=-1){
            cmbCountry->setCurrentIndex(found);
        }
        found= cmbCity->findData(settings.value("city").toString(),Qt::DisplayRole,Qt::MatchExactly);
        if (found !=-1){
            cmbCity->setCurrentIndex(found);
        }

    }else{ //n.b.: it should never come here!
        QMessageBox msgBox(QMessageBox::Critical,tr("Settings Error"),
            tr("You are trying to read a non-existent settings group!"),QMessageBox::Ok,0);
        msgBox.exec();
    }
}

void conf_app::onStatusShow(const QString str)
{
    this->statusBar()->setStyleSheet(tr(
     "QStatusBar {"
     "    background: "
     "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                     " stop: 0 #FFFF00, stop: 0.4 #FFFF66,"
                                     " stop: 0.5 #FFFF99, stop: 1.0 #FFFFCC)"
     ";"
     "}"));

    this->statusBar()->showMessage(str);
}

bool conf_app::listTables()
{
    QSqlDatabase db=QSqlDatabase::database();
    cmbTables->addItems(db.tables());

    return(cmbTables->count()>0);
}

void conf_app::applyChanges2Table()
{
    bool bError=false;

    if (!tableModel->submitAll()){
        if (tableModel->lastError().type()!=QSqlError::NoError){

            QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
                tableModel->lastError().text(),QMessageBox::Ok,0);
            msgBox.exec();

        }else{

            QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
                tr("Could not write Sampling levels in the database!"),QMessageBox::Ok,0);
            msgBox.exec();

        }
        bError=true;
    }else{
        emit statusShow(tr("Changes successfully written in the database!"));
    }

    pushApply_2->setEnabled(bError);
    pushInsert->setEnabled(bError);
    pushRemove->setEnabled(bError);
    tableView->setEnabled(bError);
}

void conf_app::showTable(const QString strTable)
{
    if (tableModel==0){
        tableModel= new QSqlRelationalTableModel;
    }

    bool bDirty=false;

    for (int i=0; i < tableModel->rowCount(); ++i){
        for (int j=0; j < tableModel->columnCount(); ++j){
            QModelIndex index=tableModel->index(i,j);
            if (tableModel->isDirty(index)){
                bDirty=true;
                break;
            }
        }
        if (bDirty) break;
    }

    if (bDirty){

        QMessageBox msgBox;
        msgBox.setText(tr("You have uncomitted changes!")
        );
        msgBox.setInformativeText(tr("Are you sure you want to abandon the edition of this table?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

         switch (ret) {
           //case QMessageBox::Yes:
            case QMessageBox::No:
                return;
                break;
            default:
                break;
         }
    }

    tableModel->setTable(QSqlDatabase().driver()->escapeIdentifier(strTable,
    QSqlDriver::TableName));
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->sort(0,Qt::AscendingOrder);
    tableModel->select();

    tableView->setModel(tableModel);

    QSqlRecord rec=tableModel->record();
    for (int i=0; i < rec.count(); ++i){
        if (rec.field(i).isGenerated()){
            tableView->hideColumn(i);
            break;
        }
    }

    pushInsert->setEnabled(true);
    pushRemove->setEnabled(true);
    pushApply_2->setEnabled(true);
    tableView->setEnabled(true);

}

void conf_app::insertRow()
{
    if (!tableModel->insertRow(tableModel->rowCount())){

        QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
            tr("Could not add a row to this table!"),QMessageBox::Ok,0);
        msgBox.exec();

    }else 
        emit statusShow(tr("Record successfully initialized!"));
}

void conf_app::removeRow()
{
    if (!tableView->selectionModel()->hasSelection()){

        QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
            tr("If you want to remove a row, you must select it first!"),QMessageBox::Ok,0);
        msgBox.exec();

    }else{
        int delRow=tableView->selectionModel()->currentIndex().row();
        if (!tableModel->removeRow(delRow)){

            QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
                tr("Could not remove a row from this table!"),QMessageBox::Ok,0);
            msgBox.exec();

        }else
            emit statusShow(tr("Row successfully removed!"));
    }
}

bool conf_app::fillLocations()
{
    initModels();

    countryModel->setQuery(
        "SELECT ID, Name from Ref_Countries WHERE"
        "   ID IN (SELECT Country from Ref_Location)"
        );

    cmbCountry->setModel(countryModel);
    cmbCountry->setModelColumn(1);

    return (countryModel->rowCount()>0);
}

//////////////////////////////////////////////////////////////////////

bool queryShowStartupMsg()
{
    QSettings settings("Medstat", "App");
    if (!settings.contains("showStartupMsg"))
        return true;

    return settings.value("showStartupMsg").toBool();
}

bool queryShowSqlMsg()
{
    QSettings settings("Medstat", "App");
    if (!settings.contains("showSqlMsg"))
        return true;

    return settings.value("showSqlMsg").toBool();
}