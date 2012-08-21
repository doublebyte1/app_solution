#include "conf_app.h"
#include "connection.h"
#include "sql.h"
#include <QMessageBox>
#include <QDir>

//We need to mantain these names in order to mantain compatibility with the historical backups
//static const QString strLogicalFile="albania_dat";
//static const QString strLogFile="albania_log";
//static const QString strDatabasePath="C:\\medfisis_dat\\";
static const QString strSqlClient="sqlcmd";

static const QString strViewUsers=
    "SELECT     dbo.UI_User.ID, dbo.UI_User.username AS Name, dbo.UI_Role.name AS Role"
    " FROM         dbo.UI_User INNER JOIN"
    "                      dbo.UI_Role ON dbo.UI_User.role_id = dbo.UI_Role.id WHERE NAME <> 'n/a'"
;
static const QString strViewRole=
"SELECT     id, name AS Name, description AS Description"
" FROM         dbo.UI_Role WHERE NAME <> 'n/a'"
;

conf_app::conf_app(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    setupUi(this);
    m_bConnected=false;

    cityModel=0;
    countryModel=0;
    tableModel=0;
    userModel=0;
    roleModel=0;
    viewUsers=0;
    viewRoles=0;
    myProcess=0;
    mapperUsers=0;
    mapperRoles=0;
    nullDelegateUsers=0;
    nullDelegateRoles=0;
    m_lastIndex=QModelIndex();
    //tablePerm=0;
    //proxymodel=0;

    initUI();
}

conf_app::~conf_app()
{
    //if (QSqlDatabase::database().isOpen()){
        if (cityModel!=0) delete cityModel;
        if (countryModel!=0) delete countryModel;
        if (userModel!=0) delete userModel;
        if (roleModel!=0) delete roleModel;
        if (tableModel!=0) delete tableModel;
        if (viewUsers!=0) delete viewUsers;
        if (viewRoles!=0) delete viewRoles;
        if (mapperUsers!=0) delete mapperUsers;
        if (mapperRoles!=0) delete mapperRoles;
        if (nullDelegateUsers!=0) delete nullDelegateUsers;
        if (nullDelegateRoles!=0) delete nullDelegateRoles;
        //if (tablePerm!=0) delete tablePerm;
        //if (proxymodel!=0) delete proxymodel;
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
    }if (viewUsers!=0){
        delete viewUsers;
        viewUsers=0;
    }if (viewRoles!=0){
        delete viewRoles;
        viewRoles=0;
    }if (userModel!=0){
        delete userModel;
        userModel=0;
    }if (roleModel!=0){
        delete roleModel;
        roleModel=0;
    }

     cityModel = new QSqlQueryModel;
     countryModel = new QSqlQueryModel;

    userModel = new QSqlRelationalTableModel;
    userModel->setTable(QSqlDatabase().driver()->escapeIdentifier("UI_User",
    QSqlDriver::TableName));
    userModel->setRelation(2, QSqlRelation("UI_Role", "id", "name"));
    userModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    userModel->sort(0,Qt::AscendingOrder);
    filterTable(userModel->relationModel(2));//removing the n/a*/
    userModel->select();

    roleModel = new QSqlTableModel;
    roleModel->setTable(QSqlDatabase().driver()->escapeIdentifier("UI_Role",
    QSqlDriver::TableName));
    roleModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    roleModel->sort(0,Qt::AscendingOrder);
    roleModel->select();
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
     tr("Export backup to file"), getOutputName("bak"), tr("Backup Files (*.bak)"));

    if (!fileName.isEmpty()){

    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    statusShow(tr("Wait..."));

        QSettings settings("Medstat", "App");
        if (!settings.contains("database")){

            QMessageBox::critical(this, tr("Backup database"),
                                    tr("Can not read database name! Are we connected?"));
            return;

        }
        QString strDatabase=settings.value("database").toString();

        QSqlQuery query;
        QString strQuery="BACKUP DATABASE " + strDatabase + " TO DISK = '"
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

QString conf_app::getOutputName(const QString strExt)
{
    QString str;
    //TODO: Change this to read data directory
    //str=QDir::currentPath() + QDir::separator();
    QSettings settings("Medstat", "App");
    if (!settings.contains("database")){

        QMessageBox::critical(this, tr("Output database"),
                                tr("Can not read database name! Are we connected?"));
        return str;

    }
    str+=settings.value("database").toString();
    str+="_";
    str+=QDateTime::currentDateTime().toString("yyyymmddhhmmss");
    str+="."+strExt;
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
    if (m_databaseLogicalName!=strSplit[1] || m_logLogicalName !=strSplit[21]){

        QMessageBox::warning(this, tr("Restore Process"),
        tr("Logical database name on this backup: ") + strSplit[1] + "\n" +
        tr("Logical log name on this backup: ") + strSplit[21] + "\n" +
        tr("Attention: The logical name on this backup differs from the database name!\n"));

        //qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
        //return;

    }

    if (m_bShowSqlMessages){

        QMessageBox::information(this, tr("Restore Process"),
            tr("Logical database name on this backup: ") + strSplit[1] + "\n" +
            tr("Logical log name on this backup: ") + strSplit[21] + "\n" +
            tr("Match with database logical Names: ok \n")
            );

    }else{
            emit statusShow(
                tr("Logical database name on this backup: ") + strSplit[1] + "\n" +
                tr("Logical log name on this backup: ") + strSplit[21] + "\n" +
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

void conf_app::doDump()
{
    if (!m_bConnected){

             QMessageBox::warning(this, tr("Patch Process"),
             tr("You must be connected to the database to perform the 'Dump'!")
             +tr("\n Please connect and try again!"));
             return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
     tr("Dump patch to file"), getOutputName("diff"), tr("Patch Files (*.diff)"));

    if (!fileName.isEmpty()){
        qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
        statusShow(tr("Wait..."));
        if (!writeDiff(fileName)){
            QMessageBox msgBox(QMessageBox::Critical,tr("Dumping Error"),
                tr("Could not write patch file!"),QMessageBox::Ok,0);
            msgBox.exec();
            statusShow(tr(""));
        }else
                statusShow(tr("Patch saved on ") + fileName);
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
    }
}

bool conf_app::writeDiff(const QString strFileName)
{

    int lastUpdate;
    if (!getLastUpdate(lastUpdate)) return false;
    QString strJSON;
    if (!getLastChanges(lastUpdate,strJSON)) return false;

    QFile file(strFileName);

    /*open a file */
    if (!file.open(QIODevice::WriteOnly))
    {
        /* show error message if not able to open file */
        QMessageBox::warning(0, tr("Read only"), tr("The file is in read only mode"));
        return false;
    }
    else{
         QTextStream out(&file);
         out << strJSON;
         file.close();
    }

    return true;
}

void conf_app::doPatch()
{
    if (!m_bConnected){

             QMessageBox::warning(this, tr("Patch Process"),
             tr("You must be connected to the database to apply the 'Patch'!")
             +tr("\n Please connect and try again!"));
             return;
    }
    //1 - read patch file
    //2 - parse JSON
    //3 - backup db (establish rollback mechanism)
    //4 - apply patches sequentially (establish rollback mechanism)
    //5 - store the stamp of the last update
}

void conf_app::initUI()
{
    /*
    tablePerm=new BooleanTable(groupRoleDetail);
    tablePerm->setObjectName(QString::fromUtf8("tablePerm"));
    gridLayout_7->addWidget(tablePerm, 2, 0, 1, 2);
    gridLayout_7->update();
*/
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

     connect(actionDump_patch, SIGNAL(triggered()),this,
        SLOT(doDump() ),Qt::UniqueConnection);

     connect(actionApply_patch, SIGNAL(triggered()),this,
        SLOT(doPatch() ),Qt::UniqueConnection);

    if (QSqlDatabase::drivers().isEmpty())
    QMessageBox::information(this, tr("No database drivers found"),
                             tr("This app requires at least one Qt database driver. "
                                "Please check the documentation how to build the "
                                "Qt SQL plugins."));

    this->cmbDriver->addItems(QSqlDatabase::drivers());

    pushDisconnect->setEnabled(false);
    groupSettings->setEnabled(false);
    groupTables->setEnabled(false);

    groupUsers->setEnabled(false);
    groupUsersDetail->setVisible(false);
    groupUsers->layout()->update();

    groupRole->setEnabled(false);
    groupRoleDetail->setVisible(false);
    groupRole->layout()->update();

    pushInsert->setEnabled(false);
    pushRemove->setEnabled(true);

    connect(this, SIGNAL(connectionChanged()), this,
        SLOT(onConnectionChange()));

    connect(this, SIGNAL(statusShow(const QString)), this,
        SLOT(onStatusShow(const QString)));

     connect(toolBox, SIGNAL(currentChanged(int)),this,
        SLOT(resizeTables(int) ),Qt::UniqueConnection);

     connect(this, SIGNAL(submit(QDataWidgetMapper*, QDialogButtonBox*, QGroupBox*, QSqlQueryModel*,const QString,
                                            QPushButton*,QPushButton*, QPushButton*, QSqlTableModel*,QTableView*)),this,
        SLOT(ApplyModel(QDataWidgetMapper*, QDialogButtonBox*, QGroupBox*,QSqlQueryModel*,const QString,
        QPushButton*,QPushButton*, QPushButton*, QSqlTableModel*,QTableView*)),Qt::UniqueConnection);

    connect(this, SIGNAL(lockControls(bool,QGroupBox*)), this,
    SLOT(onLockControls(bool,QGroupBox*)));

    connect(this, SIGNAL(editLeave(const bool,QPushButton*,QPushButton*,QPushButton*,QGroupBox*,
        QDataWidgetMapper*,QSqlTableModel*,QDialogButtonBox*,QSqlQueryModel*,const QString,QTableView*,const bool)), this,
        SLOT(onEditLeave(const bool,QPushButton*,QPushButton*,QPushButton*,QGroupBox*,QDataWidgetMapper*,
        QSqlTableModel*,QDialogButtonBox*,QSqlQueryModel*,const QString, QTableView*,const bool)));

    loadSettings(0);
}

void conf_app::onEditLeave(const bool bFinished, QPushButton* aPushEdit,QPushButton* aPushNew,
                           QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDataWidgetMapper* aMapper,QSqlTableModel* aModel,QDialogButtonBox* aButtonBox,
                           QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable, const bool bDiscarded)
{
   if (bFinished){
       aPushEdit->setChecked(false);
       aPushNew->setEnabled(!pushEditUser->isChecked());
       aPushRemove->setEnabled(!aPushEdit->isChecked());
        previewRecord(m_lastIndex,aMapper,aPushNew,aPushEdit,aPushRemove,aGroupDetails,aButtonBox,aModel
            ,viewModel,strQuery,aTable);
       emit lockControls(true,aGroupDetails);
   }else{
        aPushNew->setEnabled(false);
        aPushRemove->setEnabled(false);
   }
}

void conf_app::resizeTables(int index)
{
    if (index==3) resizeToVisibleColumns(tableRoles);
    if (index==4) resizeToVisibleColumns(tableUsers);
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
qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );

        if (cityModel!=0){
            delete cityModel;
            cityModel=0;
        }if (countryModel!=0){
            delete countryModel;
            countryModel=0;
        }if (tableModel!=0){
            delete tableModel;
            tableModel=0;
        }if (viewUsers!=0){
            delete viewUsers;
            viewUsers=0;
        }if (viewRoles!=0){
            delete viewRoles;
            viewRoles=0;
        }if (userModel!=0){
            delete userModel;
            userModel=0;
        }if (roleModel!=0){
            delete roleModel;
            roleModel=0;
        }

    QString strConn;
        QSqlDatabase db=QSqlDatabase::database();
        strConn=db.connectionName();
        db.close();
        db = QSqlDatabase();

    db.removeDatabase(strConn);

    emit statusShow(tr("Connection removed!"));

    m_bConnected=false;

    emit connectionChanged();
    groupSettings->setEnabled(m_bConnected);
    groupTables->setEnabled(m_bConnected);
    groupUsers->setEnabled(m_bConnected);
    groupRole->setEnabled(m_bConnected);

qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
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
        if (!initUsers()){
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("Could not read users from the database!"),QMessageBox::Ok,0);
            msgBox.exec();
        }
        if (!initRoles()){
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("Could not read roles from the database!"),QMessageBox::Ok,0);
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
    groupUsers->setEnabled(m_bConnected);
    groupRole->setEnabled(m_bConnected);
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
        lineDatabase->setText(settings.contains("database")?settings.value("database").toString():"FAOCASDATA");
        lineUsername->setText(settings.contains("username")?settings.value("username").toString():"dev");
        linePassword->setText(settings.contains("password")?settings.value("password").toString():"Test123");
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

bool conf_app::initRoles()
{
    viewRoles = new QSqlQueryModel;
    viewRoles->setHeaderData(1, Qt::Horizontal, tr("Name"));
    viewRoles->setHeaderData(2, Qt::Horizontal, tr("Description"));

    setPreviewQuery(viewRoles,QString(strViewRole));

    initPreviewTable(tableRoles,viewRoles);
/*
    QList<bool> chkCols;
    // fields that should be checkbox are 1
    chkCols<<0<<0<<0<<1<<1<<1<<1<<1<<1;

    if(proxymodel!=0) delete proxymodel;
    proxymodel=new GenericSortProxyModel();
    proxymodel->setparametros(chkCols);
    proxymodel->setSourceModel(roleModel);

    tablePerm->setModel(proxymodel);
    tablePerm->hideColumn(0);
    tablePerm->hideColumn(1);
    tablePerm->hideColumn(2);
*/
    if (mapperRoles!=0) {delete mapperRoles; mapperRoles=0;}

    mapperRoles= new QDataWidgetMapper(this);
    mapperRoles->setModel(roleModel);
    mapperRoles->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (nullDelegateRoles!=0) delete nullDelegateRoles;
    QList<int> lText;
    QList<int> lCmb;
    lText << 2;
    nullDelegateRoles=new NullRelationalDelegate(lCmb,lText);
    mapperRoles->setItemDelegate(nullDelegateRoles);

    mapperRoles->addMapping(lineRoleName, roleModel->fieldIndex("name"));
    mapperRoles->addMapping(textRoleDesc, roleModel->fieldIndex("description"));
    mapperRoles->addMapping(checkNew, 3, "checked");
    mapperRoles->addMapping(checkView, 4, "checked");
    mapperRoles->addMapping(checkMod, 5, "checked");
    mapperRoles->addMapping(checkRemove, 6, "checked");
    mapperRoles->addMapping(checkRep, 7, "checked");
    mapperRoles->addMapping(checkAdmin, 8, "checked");

    return true;
}

bool conf_app::initUsers()
{
    viewUsers = new QSqlQueryModel;
    viewUsers->setHeaderData(1, Qt::Horizontal, tr("Name"));
    viewUsers->setHeaderData(2, Qt::Horizontal, tr("Role"));

    setPreviewQuery(viewUsers,QString(strViewUsers));

    initPreviewTable(tableUsers,viewUsers);

    if (mapperUsers!=0) {delete mapperUsers; mapperUsers=0;}

    mapperUsers= new QDataWidgetMapper(this);
    mapperUsers->setModel(userModel);
    mapperUsers->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    comboRole->setModel(userModel->relationModel(2));
    comboRole->setModelColumn(userModel->relationModel(2)->fieldIndex("Name"));

    mapperUsers->addMapping(lineUser, userModel->fieldIndex("username"));
    mapperUsers->addMapping(lineUserPassword, 1);//the other line password is dummy!
    mapperUsers->addMapping(lineUserPassword_2, 1);//the other line password is dummy!
    mapperUsers->addMapping(comboRole, 2);
    mapperUsers->addMapping(textUserDesc, 4);

    if (nullDelegateUsers!=0) delete nullDelegateUsers;
    QList<int> lCmb;
    lCmb << 0 << 1 << 2;
    QList<int> lText;
    lText << 4;
    nullDelegateUsers=new NullRelationalDelegate(lCmb,lText);
    mapperUsers->setItemDelegate(nullDelegateUsers);

    return true;
}

bool conf_app::genericCreateRecord(QSqlTableModel* aModel,QPushButton* aPushEdit,
                              QPushButton* aPushRemove)
{
    //removing filters
    if (aModel==0) return false;
    if (!aModel->filter().isEmpty()) aModel->setFilter(tr(""));

    if (!discardNewRecord(aModel,aPushEdit)) return false;

    if (pushEditUser->isChecked()) pushEditUser->setChecked(false);
    aPushEdit->setEnabled(false);
    aPushRemove->setEnabled(false);

    return insertRecordIntoModel(aModel);
}

void conf_app::createRoleRecord()
{
    createRecord(roleModel,mapperRoles,groupRoleDetail,roleButtonBox,pushEditRole,pushRemoveRole);

    //some more specific user UI settings go here!
    lineRoleName->clear();
    textRoleDesc->clear();

    QObjectList children=frame->children();
    for (int i=0; i < children.count(); ++i){
        if (qobject_cast<QCheckBox*>(children.at(i))!=0){
            qobject_cast<QCheckBox*>(children.at(i))->setChecked(false);
        }
    }
}

void conf_app::createUserRecord()
{
    createRecord(userModel,mapperUsers,groupUsersDetail,userButtonBox,pushEditUser,pushRemoveUser);

    //some more specific user UI settings go here!

    //refresh combo
    userModel->relationModel(2)->select();
    comboRole->setModel(userModel->relationModel(2));

    lineUser->clear();
    lineUserPassword->clear();
    lineUserPassword_2->clear();
    textUserDesc->clear();
}

void conf_app::createRecord(QSqlTableModel* aModel,QDataWidgetMapper* aMapper, QGroupBox* aGroupDetails,
                            QDialogButtonBox* aButtonBox,QPushButton* aPushEdit,QPushButton* aPushRemove)
{
    if (!genericCreateRecord(aModel,aPushEdit,aPushRemove)){
        QMessageBox::critical(this, tr("Record Error"),
                            tr("Could not create record!"));
        return;
    }

    aMapper->toLast();

    UI4NewRecord(aGroupDetails,aButtonBox);//init UI
}

void conf_app::UI4NewRecord(QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox)
{
    aGroupDetails->setVisible(true);
    emit lockControls(false,aGroupDetails);

    aButtonBox->button(QDialogButtonBox::Close)->setVisible(false);
    aButtonBox->button(QDialogButtonBox::Apply)->setVisible(true);
    aButtonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}

bool conf_app::onUserButtonClick(QAbstractButton* button)
{
    return onButtonClick(button,userButtonBox,mapperUsers,groupUsersDetail,viewUsers,
        strViewUsers,pushEditUser,pushNewUser,pushRemoveUser,userModel,tableUsers);
}

bool conf_app::onRoleButtonClick(QAbstractButton* button)
{
    return onButtonClick(button,roleButtonBox,mapperRoles,groupRoleDetail,viewRoles,
        strViewRole,pushEditRole,pushNewRole,pushRemoveRole,roleModel,tableRoles);
}

bool conf_app::onButtonClick(QAbstractButton* button,QDialogButtonBox* aButtonBox,QDataWidgetMapper* aMapper, QGroupBox* aGroupDetails,
                              QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                              QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable)
{
    if ( aButtonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        aGroupDetails->hide();
        aModel->revertAll();
        return true;

    } else if (aButtonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){
        emit submit(aMapper,aButtonBox,aGroupDetails,viewModel,strQuery,aPushEdit,aPushNew,
            aPushRemove,aModel,aTable);
        return true;
    }
    else return false;
}

bool conf_app::ApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
                              QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                              QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable)
{
    if (validate(aModel))
        return reallyApplyModel(aMapper,aButtonBox,aGroupDetails,viewModel,strQuery,aPushEdit,aPushNew,aPushRemove,aModel,aTable);
    else{
        return false;
    }

}

bool conf_app::validate(const QSqlTableModel* aModel)
{
    bool bOk=true;
    QString strError="";
    QString strStyleSheet="background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));";

    //Validating user controls
    if (aModel==userModel){

        //cleaning the formatting from previous validations...
        lineUser->setStyleSheet("");
        comboRole->setStyleSheet("");
        lineUserPassword->setStyleSheet("");
        lineUserPassword_2->setStyleSheet("");

        if (lineUser->text().isEmpty()){
            strError=tr("Username must not be empty!"); lineUser->setStyleSheet(strStyleSheet);
        }else if (comboRole->currentIndex()==-1) {
            strError=tr("Role must not be empty!"); comboRole->setStyleSheet(strStyleSheet);
        }else if (lineUserPassword->text().isEmpty()){
         strError=tr("Password must not be empty!"); lineUserPassword->setStyleSheet(strStyleSheet);
        }else if (lineUserPassword_2->text().isEmpty()) {
            strError=tr("Please type again the password!"); lineUserPassword_2->setStyleSheet(strStyleSheet);
        }else if (lineUserPassword->text().compare(lineUserPassword_2->text())!=0) {
            strError=tr("Passwords don't match!");
            lineUserPassword->setStyleSheet(strStyleSheet);
            lineUserPassword_2->setStyleSheet(strStyleSheet);
        }

        bOk=!(lineUser->text().isEmpty() || comboRole->currentIndex()==-1 || lineUserPassword->text().isEmpty()
            || lineUserPassword_2->text().isEmpty() || (lineUserPassword->text().compare(lineUserPassword_2->text())!=0));
    }

    if (!bOk)
        QMessageBox::critical(this, tr("Validation Error"),
                            strError);

    return bOk;
}

bool conf_app::reallyApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
                                QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,QPushButton* aPushNew,
                                QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable)
{
    bool bError=false;

    if (aMapper->submit()){
                    bError=!
                        aModel->submitAll();
                    if (bError){
                        if (aModel->lastError().type()!=QSqlError::NoError)
                            QMessageBox::critical(this, tr("Database Error"),
                                                    aModel->lastError().text());
                        else
                            QMessageBox::critical(this, tr("Database Error"),
                                                    tr("Could not write user in the database!"));
                    }
                    else setPreviewQuery(viewModel,strQuery);        //}else bError=true;
    }else bError=true;

    aButtonBox->button(QDialogButtonBox::Apply)->setEnabled(bError);

    emit lockControls(!bError,aGroupDetails);

    if (!aPushEdit->isChecked())
        aButtonBox->button(QDialogButtonBox::Apply)->setVisible(bError);

    if (!bError) emit editLeave(true,aPushEdit,aPushNew,aPushRemove,aGroupDetails,aMapper,aModel,
        aButtonBox,viewModel,strQuery,aTable,false);

    return true;
}

void conf_app::onLockControls(bool bLock,QGroupBox* aGroupDetails)
{
    //Enabling everuthing *except* the buttonbox!
    QObjectList children=aGroupDetails->children();
    for (int i=0; i < children.count(); ++i){
        if (qobject_cast<QDialogButtonBox*>(children.at(i))==0){
            if (qobject_cast<QWidget*>(children.at(i))!=0){
                qobject_cast<QWidget*>(children.at(i))->setEnabled(!bLock);
            }
        }
    }
}

void conf_app::setPreviewQuery(QSqlQueryModel* viewModel, const QString strQuery)
{
    viewModel->setQuery(strQuery);
}

void conf_app::adjustUserEnables()
{
    if (!userModel || !pushEditUser || !pushRemoveUser) return;

    pushEditUser->setEnabled(userModel->rowCount()>0);
    pushRemoveUser->setEnabled(userModel->rowCount()>0);
}

void conf_app::previewRole(QModelIndex index)
{//entry point for roles
    previewRecord(index,mapperRoles,pushNewRole,pushEditRole,pushRemoveRole,groupRoleDetail,
        roleButtonBox,roleModel,viewRoles,strViewRole,tableRoles);
}

void conf_app::previewUser(QModelIndex index)
{//entry point for users
    previewRecord(index,mapperUsers,pushNewUser,pushEditUser,pushRemoveUser,groupUsersDetail
        ,userButtonBox,userModel,viewUsers,strViewUsers,tableUsers);
}

void conf_app::previewRecord(const QModelIndex index,QDataWidgetMapper* aMapper,QPushButton* aPushNew,
                             QPushButton* aPushEdit, QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QSqlTableModel* aModel,
                             QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable)
{
    if (!index.isValid()) return;

    m_lastIndex=index;

    QModelIndex idx=index.model()->index(index.row(),0);
    if (!idx.isValid()){
        QMessageBox::critical(this, tr("Preview Error"),
                                tr("Could not preview this record!"));
        return;
    }

    if (abstractPreviewRow(index,aPushNew,aPushEdit,aPushRemove,aGroupDetails,aButtonBox,aModel,
        aMapper,viewModel,strQuery,aTable)){
        aMapper->toLast();
    }
}

bool conf_app::discardNewRecord(QSqlTableModel* aModel, QPushButton* aPushEdit)
{
    QModelIndex dirtyIdx=aModel->index(aModel->rowCount()-1,0);

    if (aModel->isDirty(dirtyIdx) || aPushEdit->isChecked()){

        QMessageBox msgBox;
        msgBox.setText(aPushEdit->isChecked()?tr("You are editing a record."):
            tr("You are creating a new record."));
        msgBox.setInformativeText(tr("Are you sure you want to leave and loose all changes?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

         switch (ret) {
           case QMessageBox::Yes:
                aModel->revertAll();
                aPushEdit->setChecked(false);
                return true;
               break;
           case QMessageBox::No:
                return false;
               break;
           default:
               // should never be reached
               break;
         }
    }

    return true;
}

bool conf_app::abstractPreviewRow(QModelIndex index,QPushButton* aPushNew,QPushButton* aPushEdit,QPushButton* aPushRemove,
      QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox, QSqlTableModel* aModel,
      QDataWidgetMapper* aMapper, QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable)
{
    bool bOk=true;

    //its on a new record
    if (!discardNewRecord(aModel,aPushEdit)) return false;

    aGroupDetails->setVisible(true);

    emit lockControls(true,aGroupDetails);
    aButtonBox->button(QDialogButtonBox::Apply)->setVisible(false);
    aButtonBox->button(QDialogButtonBox::Close)->setVisible(true);

    aPushEdit->setEnabled(true);
    aPushEdit->setEnabled(true);
    aPushRemove->setEnabled(true);

    //setting the filter
    QModelIndex idx=index.model()->index(index.row(),0);
    if (!idx.isValid()){
        bOk=false;
    }

    QString id=idx.data().toString();

    if (qobject_cast<QSqlTableModel*>(aModel)!=0)
        aModel->setFilter(aModel->tableName()+".ID="+id);

    if (aModel->rowCount()!=1)
        bOk=false;

    if (!bOk)
            QMessageBox::critical(this, tr("Preview Error"),
                                tr("Could not preview this record!"));

    return true;//returns if it is discarded or not!
}

bool conf_app::editUser(bool on)
{
    return editRecord(on,userModel,pushEditUser,pushNewUser,pushRemoveUser,groupUsersDetail,
        userButtonBox,mapperUsers,viewUsers,strViewUsers,tableUsers);
}

bool conf_app::editRole(bool on)
{
    return editRecord(on,roleModel,pushEditRole,pushNewRole,pushRemoveRole,groupRoleDetail,
        roleButtonBox,mapperRoles,viewRoles,strViewRole,tableRoles);
}

bool conf_app::editRecord(const bool on,QSqlTableModel* aModel,QPushButton* aPushEdit,QPushButton* aPushNew,
                          QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QDataWidgetMapper* aMapper,
                          QSqlQueryModel* viewModel, const QString strQuery,QTableView* aTable)
{
    if (!on){

      //lets do this first, and then we decide if we want to turn it off!
        aPushEdit->setChecked(true);

        QMessageBox msgBox;
        msgBox.setText(tr("You are modifying a record."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

         switch (ret) {
           case QMessageBox::Save:
               ApplyModel(aMapper,aButtonBox,aGroupDetails,viewModel,strQuery,aPushEdit,
                   aPushNew,aPushRemove,aModel,aTable);
               return false;
           case QMessageBox::Discard:
               aModel->revertAll();
               emit editLeave(true,aPushEdit,aPushNew,aPushRemove,
                   aGroupDetails,aMapper,aModel,aButtonBox,viewModel,strQuery,aTable,
                   true);
               break;
           case QMessageBox::Cancel:
               aPushEdit->setChecked(true);
                emit editLeave(false,aPushEdit,aPushNew,aPushRemove,aGroupDetails,aMapper,aModel,
                    aButtonBox,viewModel,strQuery,aTable);
                return true;
                break;
           default:
               // should never be reached
               break;
         }

    }else{//Let's force the user to click on the table!
        if (!aTable->selectionModel()->hasSelection() || !aGroupDetails->isVisible()){

            QMessageBox::critical(this, tr("Edit Record"),
                                    tr("You must select an item to edit!"));

            aPushEdit->setChecked(false);
            return false;
        }

        emit editLeave(false,aPushEdit,aPushNew,aPushRemove,aGroupDetails,aMapper,aModel,aButtonBox,
            viewModel,strQuery,aTable);
    }
    aButtonBox->button(QDialogButtonBox::Close)->setVisible(!on);
    emit lockControls(!on,aGroupDetails);

    return true;
}

void conf_app::removeUser()
{
    removeRecord(tableUsers,userModel,groupUsersDetail,viewUsers,QString(strViewUsers),3);
}

void conf_app::removeRole()
{
    removeRecord(tableRoles,roleModel,groupRoleDetail,viewRoles,QString(strViewRole),0);
}

void conf_app::removeRecord(QTableView* aTable, QSqlTableModel* aModel, QGroupBox* aGroupDetails,
                            QSqlQueryModel* viewModel, const QString strQuery, const int col)
{
    if (!aTable->selectionModel()->hasSelection()){
        QMessageBox::critical(this, tr("Remove Error"),
                                tr("You have not selected any record to remove!"));
        return;
    }

    if (!aTable->selectionModel()->currentIndex().isValid()){
        QMessageBox::critical(this, tr("Remove Error"),
                                tr("You have not selected a valid record!"));
        return;
    }

    QModelIndex idx;
    if (!translateIndex(aTable->selectionModel()->currentIndex(),col,aTable,aModel,idx)){
        QMessageBox::critical(this, tr("Remove Error"),
                                tr("Could not remove this record!"));
        return;
    }

    QModelIndex idName=aTable->model()->index(aTable->selectionModel()->currentIndex().row(),1);

    QMessageBox msgBox;
    msgBox.setText(tr("You have selected record '") + idName.data().toString() +
        tr("' for deletion."));
    msgBox.setInformativeText(tr("Are you sure you want to remove this record and all its dependants?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

     switch (ret) {
       case QMessageBox::Yes:

            if ( !aModel->removeRow(idx.row()) ){

                if (aModel->lastError().type()!=QSqlError::NoError)
                    QMessageBox::critical(this, tr("Remove Error"),
                                            aModel->lastError().text());
                else
                    QMessageBox::critical(this, tr("Remove Error"),
                                            tr("Could not remove this record!"));

            }else{
                if (!aModel->submitAll()){

                    if (aModel->lastError().type()!=QSqlError::NoError)
                        QMessageBox::critical(this, tr("Remove Error"),
                                                aModel->lastError().text());
                    else
                        QMessageBox::critical(this, tr("Remove Error"),
                                                tr("Could not remove this record!"));

                }
                else{
                    statusShow(tr("Record successfully removed from the database!"));
                    setPreviewQuery(viewModel,strQuery);
                    aGroupDetails->hide();
                }
            }

           break;
       case QMessageBox::No:
           return;
           break;
       default:
           // should never be reached
           break;
     }
}

bool conf_app::translateIndex(const QModelIndex inIdx, const int col, QTableView* aTable, QSqlTableModel* aModel, QModelIndex& outIdx)
{
    QModelIndex idx=aTable->model()->index(inIdx.row(),0);
    if (!idx.isValid()){

        QMessageBox::critical(this, tr("Remove Error"),
                                tr("Could not remove this row!"));

        return false;
    }

    QModelIndex start=aModel->index(0,col);
    QModelIndexList list=aModel->match(start,0,idx.data(),1,0);

    if (list.count()!=1) return false;
    outIdx=list.at(0);

    return true;
}

void conf_app::initPreviewTable(QTableView* aTable, QSqlQueryModel* view)
{
    aTable->setModel(view);

    if (aTable->objectName()=="tableUsers"){
        connect(aTable->model(), SIGNAL(rowsInserted ( const QModelIndex, int, int)), this,
            SLOT(adjustUserEnables()));

        connect(aTable->model(), SIGNAL(rowsRemoved ( const QModelIndex, int, int)), this,
            SLOT(adjustUserEnables()));
    }

    aTable->setAlternatingRowColors(true);
    aTable->verticalHeader()->hide();
    aTable->setSelectionMode(
        QAbstractItemView::SingleSelection);
    aTable->setSelectionBehavior( QAbstractItemView::SelectRows);
    aTable->horizontalHeader()->setClickable(false);
    aTable->horizontalHeader()->setFrameStyle(QFrame::NoFrame);
    aTable->hideColumn(0);
}

void conf_app::resizeEvent ( QResizeEvent * event )
{
    (void) event;
    if (tableUsers!=0) resizeToVisibleColumns(tableUsers);
    if (tableRoles!=0) resizeToVisibleColumns(tableRoles);

    if (toolBox->currentIndex()==3)
        groupUsers->layout()->update();
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

void resizeToVisibleColumns ( QTableView* table )
{
    int ct=0;
    if (table->model()!=0){
        for (int i=0; i < table->model()->columnCount(); ++i)
            if (!table->isColumnHidden(i)) ++ ct;

        for (int i=0; i < table->model()->columnCount(); ++i)
            if (!table->isColumnHidden(i))
                table->setColumnWidth(i,table->width()/ct);
    }
}

void filterTable(QSqlTableModel* table)
{
    table->setFilter("Name<>'" + qApp->translate("null_replacements", strNa)
            + "' AND Name<>'" + qApp->translate("bin", strOutside)
            + "' AND Name<>'" + qApp->translate("null_replacements", strMissing)
            + "' AND Name<>'" + qApp->translate("null_replacements", strOther)
            + "' AND Name<>'" + qApp->translate("null_replacements", strUnknown)
            + "'");
}
bool insertRecordIntoModel(QSqlTableModel* m)
{
    while(m->canFetchMore())
        m->fetchMore();

    return m->insertRow(m->rowCount());
}
