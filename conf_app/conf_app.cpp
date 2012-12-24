#include "conf_app.h"
#include "connection.h"
#include "sql.h"
//#include "json.h"
#include <QMessageBox>
#include <QDir>

using namespace QtJson;

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
    m_dbmode=INVALID;

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

bool conf_app::doDump(const int lu, const QString strMacAddress)
{
    if (!m_bConnected){

             QMessageBox::warning(this, tr("Patch Process"),
             tr("You must be connected to the database to perform the 'Dump'!")
             +tr("\n Please connect and try again!"));
             return false;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
     tr("Dump patch to file"), getOutputName("diff"), tr("Patch Files (*.diff)"));

    if (!fileName.isEmpty()){
        qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
        statusShow(tr("Wait..."));

        qApp->processEvents();

        QString strError;
        if (!writeDiff(fileName,lu, strMacAddress, strError)){
            if (strError.isEmpty()) strError=tr("Could not write patch file!");
            qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
            QMessageBox msgBox(QMessageBox::Critical,tr("Dumping Error"),
                strError,QMessageBox::Ok,0);
            msgBox.exec();
            statusShow(tr(""));
            return false;
        }

        statusShow(tr("Patch saved on ") + fileName);
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
    }
    return true;
}

bool conf_app::writeDiff(const QString strFileName, const int lu, const QString strMacAddress, QString& strError)
{
    QString strJSON;

    if (!getLastChanges(lu,strJSON,strMacAddress,(m_dbmode==MASTER),strError)) return false;

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

bool conf_app::startPatchSession(const QString strDateUTC, const QString strDateLocal,
                        const int dateType, const QString strCityName, const QString strMacAddress, const QString strUser)
{
//TODO: replace city name, by pair: (country,city)
    int newDate;
    if (!insertDate(InfoDate(strDateUTC,strDateLocal,dateType),newDate)) return false;
    QVariant baseDateID=QVariant(newDate);

    return startSession(strUser, strCityName, strMacAddress, baseDateID,
        QString("This record was generated during a patch session!"));
}

void conf_app::doPatch()
{
    int lu_master;//we want to store this variable for the master
    QString strClientMac;//we want to store this variable for the master
    if (!doApply(lu_master,strClientMac)){
        if (m_dbmode==MASTER){
            QMessageBox::critical(this, tr("Patch Process"),
             tr("You must apply a patch before requesting a diff!"));
            }
            return;
    }

    //For the client, the last update is on info_client; for the master, it is the value we read
    //on the patch (this is why the patch is compulsory)
    int lastUpdate;
    QString strMacAddress;
    if (m_dbmode==CLIENT){
        QString strError;
        if (!getLastUpdate(lastUpdate,strError)){
            QMessageBox::critical(this, tr("Patch Process"),
             strError);
            return;
        }
        strMacAddress=getMacAddress();
    }else {
        lastUpdate=lu_master;
        strMacAddress=strClientMac;
    }

    doDump(lastUpdate,strMacAddress);
}

bool conf_app::doApply(int& lu_master, QString& strMacAddress)
{
    if (!m_bConnected){

             QMessageBox::warning(this, tr("Patch Process"),
             tr("You must be connected to the database to apply the 'Patch'!")
             +tr("\n Please connect and try again!"));
             return false;
    }
    QString fileName = QFileDialog::getOpenFileName(this,
     tr("Open patch file"), "", tr("Patch Files (*.diff)"));

    if (!fileName.isEmpty()){
        qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );

        qApp->processEvents();
        QString strContent;
        if (!readFile(fileName,strContent)){
                qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
                 QMessageBox::warning(this, tr("Patch Process"),
                 tr("Could not read patch file!")
                 +tr("\n Are you sure this is a valid file?"));
                 return false;
        }else{
            /*
            QString strError="";
            int ctNew=0;
            int ctMod=0;
            int ctDel=0;
            if (!readAndApplyChangesfromPatch(strContent, ctNew, ctMod, ctDel, strError)){
                qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
                QMessageBox::critical(this, tr("Patch Process"),
                    (strError.isEmpty()?tr("Could not read and apply changes in this file!!"):strError));
                 return false;
            }
            */
            listInfoChanges lChanges;
            QString strDateUTC, strDateLocal, strCityName, strUser, strError="";
            int dateType;
            QList<QVariant> mapReferences;
            if (!readChangesfromPatch(strContent,strDateUTC,strDateLocal,dateType,
                strCityName,strMacAddress,strUser,lu_master,lChanges,mapReferences,strError)){
                qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
                QMessageBox::critical(this, tr("Patch Process"),
                    (strError.isEmpty()?tr("Could not read any changes in this file!!"):strError));
                 return false;
            }
            //3 - backup db (establish rollback mechanism)
            //4 - prompt the user with changes

            if (!startPatchSession(strDateUTC,strDateLocal,dateType,strCityName,strMacAddress,strUser)){
                qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
                QMessageBox::critical(this, tr("Patch Process"),
                 tr("Could not start a mini session!!"));
                 return false;
            }

            int ctNew=0;
            int ctMod=0;
            int ctDel=0;
            strError="";
            if (!applyChangesfromPatch(mapReferences,lChanges,lu_master,ctNew,ctMod,ctDel,strError))
            {
                qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
                 QMessageBox::warning(this, tr("Patch Process"),
                     (strError.isEmpty()?tr("Could not apply this patch!"):strError));
                 return false;
            }
            endSession();

            //5 - apply patches sequentially (establish rollback mechanism)
            //FK?

            qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
            QMessageBox::information(this, tr("Patch Process"),
                                     tr("Patch successfully applied.\n") +
                                     QString("There were %1 inserts, %2 removals and %3 modifications!").arg(ctNew)
                                     .arg(ctDel).arg(ctMod));

        }//read file
        return true;
    }else if(m_dbmode==CLIENT){
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
        return true;
    }

    qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
    return false;
}

bool conf_app::insertDate(const InfoDate date, int& id)
{
    QSqlTableModel* tModel = new QSqlTableModel;
    tModel->setTable(QSqlDatabase().driver()->escapeIdentifier("GL_DATES",
    QSqlDriver::TableName));
    tModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tModel->select();

    if (!insertRecordIntoModel(tModel)){
        delete tModel; tModel=0;
        return false;
    }
    QModelIndex idx=tModel->index(tModel->rowCount()-1,tModel->record().indexOf("Date_UTC"));
    if (!idx.isValid()){delete tModel; tModel=0; return false;}
    QDateTime dt=QDateTime::fromString(date.m_strUTC,strDateFormat);
    if (!dt.isValid()){delete tModel; tModel=0; return false;}
    tModel->setData(idx, dt);

    idx=tModel->index(tModel->rowCount()-1,tModel->record().indexOf("Date_Local"));
    if (!idx.isValid()){delete tModel; tModel=0; return false;}
    dt=QDateTime::fromString(date.m_strLocal,strDateFormat);
    if (!dt.isValid()){delete tModel; tModel=0; return false;}
    tModel->setData(idx, dt);

    idx=tModel->index(tModel->rowCount()-1,tModel->record().indexOf("Date_Type"));
    if (!idx.isValid()){delete tModel; tModel=0; return false;}
    tModel->setData(idx, date.m_type);

    bool bOk=tModel->submitAll();

    if (bOk){

        while(tModel->canFetchMore())
            tModel->fetchMore();

        idx=tModel->index(tModel->rowCount()-1,tModel->record().indexOf("ID"));
        if (!idx.isValid()){delete tModel; tModel=0; return false;}
        id=idx.data().toInt();
    }

    delete tModel; tModel=0;
    return bOk;
}

bool conf_app::insertNewRecord(const listInfoChanges& lChanges)
{
    bool bOk=true;

    QSqlTableModel* tModel = new QSqlTableModel;
    tModel->setTable(QSqlDatabase().driver()->escapeIdentifier(lChanges.at(0).m_strTable,
    QSqlDriver::TableName));
    tModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tModel->select();

    if (!insertRecordIntoModel(tModel)) return false;

    for (int i=0; i < lChanges.size(); ++i){

        QString strField=lChanges.at(i).m_strField;
        strField=strField.remove("[");
        strField=strField.remove("]");

        QModelIndex idx=tModel->index(tModel->rowCount()-1,tModel->record().indexOf(strField));
        if (!idx.isValid()) return false;

        bool bIsDate=false;
        int newDate=-1;
        if (lChanges.at(i).m_varNew.type()==QVariant::Map){

            QVariantMap nestedDate=lChanges.at(i).m_varNew.toMap();
            QVariantMap nestedDate2=nestedDate["date"].toMap();
            QString strDateUTC=nestedDate2["date_utc"].toString();
            QString strDateLocal=nestedDate2["date_local"].toString();
            int dateType=nestedDate2["date_type"].toInt();

            if (!insertDate(InfoDate(strDateUTC,strDateLocal,dateType),newDate)){

                QMessageBox msgBox(QMessageBox::Critical,tr("Patch Error"),
                    tr("Could not insert date in the database!"),QMessageBox::Ok,0);
                msgBox.exec();
                return false;
            }
            bIsDate=true;
        }

        tModel->setData(idx, bIsDate?newDate:lChanges.at(i).m_varNew);
    }
    bOk=tModel->submitAll();

    if (!bOk){
        QString strError;
        if (tModel->lastError().type() != QSqlError::NoError)
            strError=tModel->lastError().text();
        else
            strError=tr("Could not insert record in the database!");

            QMessageBox msgBox(QMessageBox::Critical,tr("Patch Error"),
                strError,QMessageBox::Ok,0);
            msgBox.exec();
    }

    //a bit of house-keeping...
    delete tModel; tModel=0;
    return bOk;
}

bool conf_app::packRecord(const QList<QVariant>& mapReferences, listInfoChanges& lChanges, int& i, listInfoChanges& aRecord, bool& bBreak, QString& strError)
{
    bBreak=false;
    QString curTable=lChanges.at(i).m_strTable;
    QSqlTableModel *aTable=new QSqlTableModel ();
    aTable->setTable(curTable);
    int start=i;

    while (i < lChanges.count() && lChanges.at(i).m_strTable.compare(curTable)==0
        && i < (start + aTable->record().count()-1)){

        //Identify references here
        QVariant vFrom, vTo;
        if (lChanges.at(i).m_varOld.toString().contains("Ref:",Qt::CaseInsensitive)){
            if (!identifyReference(mapReferences,lChanges.at(i).m_varOld.toString(),
                vFrom,strError)) return false;
            lChanges[i].m_varOld=vFrom;
        }

        if (lChanges.at(i).m_varNew.toString().contains("Ref:",Qt::CaseInsensitive)){
            if (!identifyReference(mapReferences,lChanges.at(i).m_varNew.toString(),
                vTo,strError)) return false;
            lChanges[i].m_varNew=vTo;
        }

        aRecord.push_back(lChanges.at(i));
        ++i;
    }

    if (i==lChanges.count()) bBreak=true;
    else if (lChanges.at(i).m_strTable.compare(curTable)!=0 || i==(start + aTable->record().count()-1))
            i--;

    delete aTable; aTable=0;

    return true;
}

bool conf_app::identifyRecord(const listInfoChanges& packRecord, int& outID)
{
    QString curTable=packRecord.at(0).m_strTable;

    bool bIsDateTime=false;
    QString strQuery;

    //TODO: get ID name?

    QString strFirst=QString("select ") + curTable + QString(".ID FROM ")+curTable;
    for (int i=0; i < packRecord.count(); ++i){
        if (i>0) strQuery+= QString(" AND ");

        QString strField=packRecord.at(i).m_strField;
        strField=strField.remove("[");
        strField=strField.remove("]");

        QString strType;
        if (!getFieldType(packRecord.at(i).m_strTable,strField,strType)){

            QMessageBox msgBox(QMessageBox::Critical,tr("Patch Error"),
                "Could not get field type!",QMessageBox::Ok,0);
            msgBox.exec();

            return false;
        }

        if (!isDateTime(curTable,strField,bIsDateTime)){

            QMessageBox msgBox(QMessageBox::Critical,tr("Patch Error"),
                "Could not determine if this field is datetime!",QMessageBox::Ok,0);
            msgBox.exec();
            return false;
        }

        if (bIsDateTime){

            if (packRecord.at(i).m_varOld.type()!=QVariant::Map) return false;
            QVariantMap nestedDate=packRecord.at(i).m_varOld.toMap();
            QVariantMap nestedDate2=nestedDate["date"].toMap();
            QString strDateUTC=nestedDate2["date_utc"].toString();
            QString strDateLocal=nestedDate2["date_local"].toString();
            int dateType=nestedDate2["date_type"].toInt();

            //Dates are in ISO86, but to make sure they dont *include* the ms, we have to trim it to 
            // the left 19 characters
            strQuery+=
     " LEFT(CONVERT(varchar, (dt" + QVariant(i).toString() + ".Date_UTC), 126),19)='"
                + strDateUTC + "'";

            strQuery+=
     " AND LEFT(CONVERT(varchar, (dt" + QVariant(i).toString() + ".Date_Local), 126),19)='"
                + strDateLocal + "'";

            strQuery+=" AND dt" + QVariant(i).toString() + QString(".date_type=") + QVariant(dateType).toString();
            strFirst.append(QString(" INNER JOIN GL_DATES AS dt") + QVariant(i).toString()
                + QString(" ON ") + curTable + "." + strField + QString("=dt")+ QVariant(i).toString()
                +QString(".ID"));

        }else if (strType.contains("CHAR",Qt::CaseInsensitive)){
            strQuery+= curTable + "." + strField + QString("=");
            strQuery+= "'" + packRecord.at(i).m_varOld.toString() + "'";
        }else{
            strQuery+= curTable + "." + strField + QString("=");
            strQuery+= packRecord.at(i).m_varOld.toString();
        }
    }

    strQuery.prepend(strFirst + QString(" WHERE "));

    QString strError;
    QSqlQuery query;
    query.prepare(strQuery);
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() != 1){
         if (query.lastError().type() != QSqlError::NoError)
             strError=query.lastError().text();
         else
             strError=QObject::tr("Could not identify a unique record! Please check if you have duplicates");

            QMessageBox msgBox(QMessageBox::Critical,tr("Patch Error"),
                strError,QMessageBox::Ok,0);
            msgBox.exec();

         return false;
        }

     query.first();
     outID=query.value(0).toInt();

    return true;
}

bool conf_app::removeRecord(const listInfoChanges& packRecord)
{
    int outID;

    if (!identifyRecord(packRecord,outID)){
        qDebug() << "Could not identify record!" << endl;
        return false;
    }

    QString strError;
    QSqlQuery query;
    QString curTable=packRecord.at(0).m_strTable;

    QString strQuery=QString("delete from ") + curTable + QString(" WHERE ID=:id");

    //if (query.isActive()) query.finish();
    query.prepare(strQuery);
    query.bindValue(":id",outID);
    query.setForwardOnly(true);
    if (!query.exec() || query.numRowsAffected() != 1){
         if (query.lastError().type() != QSqlError::NoError)
             strError=query.lastError().text();
         else
             strError=QObject::tr("Could not remove record to remove!");

            QMessageBox msgBox(QMessageBox::Critical,tr("Patch Error"),
                strError,QMessageBox::Ok,0);
            msgBox.exec();

         return false;
    }

    return true;
}

bool conf_app::modRecord(const InfoChanges& chRec, const int id)
{
    QString strType;
    QString strField=chRec.m_strField;
    strField=strField.remove("[");
    strField=strField.remove("]");

    if (!getFieldType(chRec.m_strTable,strField,strType)){
        qDebug() << "Could not determine field type!" << endl;
        return false;
    }

    QString strQuery= "UPDATE " + chRec.m_strTable + " SET "
         + chRec.m_strField + 
         (strType.contains("CHAR",Qt::CaseInsensitive)? "='"
         :"=") + chRec.m_varNew.toString() + 
         (strType.contains("CHAR",Qt::CaseInsensitive)? "' WHERE ID=":
         " WHERE ID=")
         + QVariant(id).toString();

    QSqlQuery query;
    query.prepare(strQuery);
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() < 1){
         if (query.lastError().type() != QSqlError::NoError)
             qDebug() << query.lastError().text() << endl;
         else
             qDebug() << QObject::tr("Could not update record!") << endl;
         return false;
     }
    return true;
}

bool conf_app::identifyRecordByDate(const listInfoChanges& aRecord,
                         const listInfoChanges& dtRecs, const listInfoChanges& iDt,
                         listInfoChanges& lcopy, int & outID, QString& modField, bool& bFound)
{
    bool bIsEqual;
    for (int j=0; j < dtRecs.size(); ++j){

        if (dtRecs.at(j).m_varNew.type()!=QVariant::Map) return false;
        QVariantMap nestedDate=dtRecs.at(j).m_varNew.toMap();
        QVariantMap nestedDate2=nestedDate["date"].toMap();

        bIsEqual=true;
        int k;
        for (k=0; k < iDt.count(); ++k){

            QString strField=iDt.at(k).m_strField;
            strField=strField.remove("[");
            strField=strField.remove("]");

            QString strVal=nestedDate2[strField.toLower()].toString();
            if (strVal.isEmpty()) return false;

            if (iDt.at(k).m_varNew.toString().compare(strVal)!=0){
                bIsEqual=false;
                break;
            }
        }//for k
        if (bIsEqual){
            int y;
            for (y=0; y < aRecord.size(); ++y){
                if (aRecord.at(y).m_strField.compare(dtRecs.at(j).m_strField)==0)
                {
                    //qDebug() << aRecord.at(y).m_strField << endl;
                    break;
                }
            }
            lcopy=listInfoChanges(aRecord);
            lcopy.removeAt(y);
            QVariantMap nestedMap, nestedMap2;

            for (int z=0; z < iDt.size(); ++z){

                QString strField=iDt.at(z).m_strField;
                strField=strField.remove("[");
                strField=strField.remove("]");
                strField=strField.toLower();

                nestedMap2[strField]=iDt.at(z).m_varOld;
                if (iDt.at(z).m_varOld.toString().compare(
                    iDt.at(z).m_varNew.toString())!=0)
                    modField=iDt.at(z).m_strField;
            }

            nestedMap["date"]=nestedMap2;

            lcopy.push_back(InfoChanges(aRecord.at(y).m_id,
                aRecord.at(y).m_strTable,aRecord.at(y).m_strField,
                nestedMap,aRecord.at(y).m_varNew));

            if (identifyRecord(lcopy,outID)){
                bFound=true;
                break;
            }
        }
    }//for j

    return true;
}

bool conf_app::findDateID(const QString strTable, const QString strField, const int inID, int &outID)
{
    QString strQuery="SELECT " + strField + 
        " FROM " + strTable + " WHERE ID=" + QVariant(inID).toString();

    QSqlQuery query;
    query.prepare(strQuery);
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() < 1){
         if (query.lastError().type() != QSqlError::NoError)
             qDebug() << query.lastError().text() << endl;
         else
             qDebug() << QObject::tr("Could not retrieve datetime id!") << endl;
         return false;
     }
     query.first();
     outID=query.value(0).toInt();

     return true;
}

bool conf_app::modDateRecord(const listInfoChanges& aRecord, const listInfoChanges& iDt)
{
    listInfoChanges dtRecs;
    QString curTable=aRecord.at(0).m_strTable;

    //Identify all the datetime records on this table
    for (int j=0; j < aRecord.size(); j++){
        bool bIsDateTime;

        QString strField=aRecord.at(j).m_strField;
        strField=strField.remove("[");
        strField=strField.remove("]");

        if (!isDateTime(curTable,strField,bIsDateTime)){
            QMessageBox msgBox(QMessageBox::Critical,tr("Patch Error"),
            "Could not determine if this field is datetime!",QMessageBox::Ok,0);
            msgBox.exec();
            return false;
        } 
        if (bIsDateTime) dtRecs.push_back(aRecord.at(j));
    }

    //The structure of the patch is DateTime record (GL_Dates) precedeed by a table, means
    // that we have a table with a datetime record that changed.
    //We have to identify at least one record!
    if (dtRecs.size() < 1){
        qDebug() <<
            "This table was identified as having one datetime record, but we cant find any!" << endl;
        return false;
    }

    int outID;
    bool bFound;
    listInfoChanges lcopy;
    QString modField;

    //Here is the challenge: identify which one of the date-fields had the date changed;
    //For that, we try replacing the changed date in all the date fields, till we identify
    //a unique record.
    if (!identifyRecordByDate(aRecord,dtRecs,iDt,lcopy,outID,modField,bFound)){
        qDebug() << "Could not identify date record!" << endl;
        return false;
    }

    if (!bFound){
        qDebug() << "Could not find any date record matching this field!" << endl;
        return false;
    }

    //Find FK reference for this field on GL_Dates
    int dtID;
    if (!findDateID(lcopy.at(0).m_strTable, lcopy.at(lcopy.size()-1).m_strField, outID,dtID))
    {
        qDebug() << "Could not find the matching date for this reference!" << endl;
        return false;
    }

     QString strDateUTC, strDateLocal;
     int dateType;
     if (lcopy.at(lcopy.size()-1).m_varNew.type()!=
         QVariant::Map)
         return false;

     if (!serializeDateTime(lcopy.at(lcopy.size()-1).m_varNew.toMap(),
         strDateUTC,strDateLocal,dateType)){
        return false;
     }

     //Finally amend this date
     if (!amendDate(dtID,modField,strDateLocal))
         return false;

     return true;
}

bool conf_app::applyChangesfromPatch(const QList<QVariant>& mapReferences, listInfoChanges& lChanges, const int lu_master, int& cnew, int& cmod, int& cdel, QString& strError)
{
    for (int i=0; i < lChanges.count(); ++i)
    {
            if (lChanges.at(i).m_varNew.toString().compare(strNoValue)==0){//REM

                listInfoChanges aRecord;
                bool bBreak;
                if (!packRecord(mapReferences,lChanges,i,aRecord,bBreak,strError)){
                    strError=tr("Could not distinguish record!");
                    return false;
                }

                if (aRecord.size()>0){

                        if (!removeRecord(aRecord)){
                            strError=tr("Could not remove record from the database!");
                            return false;
                        }
                        cdel++;
                }else return false;

                if (bBreak) break;

            }else if (lChanges.at(i).m_varNew.toString().compare(strNoValue)!=0 &&
                lChanges.at(i).m_varOld.toString().compare(strNoValue)!=0){//EDIT

                    //If it is a date, extracts the date records and goes further
                    bool bIsDate=false;
                    listInfoChanges iDt;
                    if (lChanges.at(i).m_strTable.compare("GL_DATES",Qt::CaseInsensitive)==0){
                        iDt.push_back(lChanges.at(i));
                        ++i;
                        bIsDate=true;

                        while(i < lChanges.size() &&
                            lChanges.at(i).m_strTable.compare("GL_DATES",Qt::CaseInsensitive)==0)
                        {
                            iDt.push_back(lChanges.at(i));
                            ++i;
                        }
                        //Let's jump to the previous rec
                        i=i-iDt.size();
                        i--;
                        QString prevTable=lChanges.at(i).m_strTable;
                        while (i>-1 && prevTable==lChanges.at(i).m_strTable){
                            i--;
                        }

                        i++;
                    }

                    //packs the following records
                    listInfoChanges aRecord;
                    bool bBreak;
                    if (!packRecord(mapReferences,lChanges,i,aRecord,bBreak,strError)){
                        strError=tr("Could not distinguish record!");
                        return false;
                    }

                    //Dates don't get amended on the spot. Instead, the reference record
                    //on GL_Dates gets amended
                    if (bIsDate){

                        if (!modDateRecord(aRecord,iDt)){
                            strError="Could not modify date record!";
                            return false;
                        }
                        i=(aRecord.size()+iDt.size())-1;
                        cmod++;
                    }else{

                        //JUMP redundant records that are on the log
                        //Lets just ignore them for now, till we solve the problem!
                        bool bDif=false;
                        InfoChanges ch;
                        for (int z=0; z < aRecord.size(); ++z){
                            if (aRecord.at(z).m_varOld!=aRecord.at(z).m_varNew){
                                bDif=true;
                                ch=InfoChanges(aRecord.at(z));
                                break;
                            }
                        }

                        if (bDif){
                            int outID;
                            if (!identifyRecord(aRecord, outID)){
                                strError="Could not identify this record!";
                                return false;
                            }

                            if (!modRecord(ch,outID)){
                                strError="Could not modify record!";
                                return false;
                            }
                            cmod++;
                        }
                    }


            }else if (lChanges.at(i).m_varOld.toString().compare(strNoValue)==0){//INSERT

                listInfoChanges aRecord;
                bool bBreak;
                if (!packRecord(mapReferences,lChanges,i,aRecord,bBreak,strError)){
                    strError=tr("Could not distinguish record!");
                    return false;
                }

                if (aRecord.size()>0){

                    if (!insertNewRecord(aRecord)){
                        strError=tr("Could not insert record in the database!");
                        return false;
                    }
                    cnew++;
                }else return false;

                if (bBreak) break;

            }else
                return false;

    }//for

    //Writing the ID of the last update (master and client)
    if (m_dbmode==CLIENT){
        QString strError="";
        if (!insertLastMasterUpdate(lu_master,strError)){
            if (strError.isEmpty()) strError=tr("Could not write ID of last local Update !");
            return false;
        }
    }

    return true;
}


bool conf_app::amendDate(const int ID, const QString strField, const QString strDate)
{
    QString strQuery="UPDATE [GL_DATES] SET "
        + strField + "='" +
        strDate + "' WHERE ID=" + QVariant(ID).toString();

        QSqlQuery query;
        query.prepare(strQuery);
        query.setForwardOnly(true);
         if (!query.exec() || query.numRowsAffected() < 1){
             if (query.lastError().type() != QSqlError::NoError)
                 qDebug() << query.lastError().text() << endl;
             else
                 qDebug() << QObject::tr("Could not amend datetime!") << endl;
             return false;
            }

    return true;
}
/*
bool conf_app::readAndApplyChangesfromPatch(const QString strContent, int& ctNew, int& ctMod,
                                            int& ctDel, QString& strError)
{
    bool ok;
    QVariantMap result = Json::parse(strContent, ok).toMap();

    if(!ok){
        strError=tr("Could not parse JSON content!")
        +tr("\n Are you sure the syntax is valid?");

        return false;
    }

    QString strMode= result["mode"].toString();

    if (m_dbmode==MASTER && strMode.compare(strMasterName, Qt::CaseInsensitive)==0){
            strError=tr("Master databases can only be updated by clients!");
        return false;
    }else if (m_dbmode==CLIENT && strMode.compare(strClientName, Qt::CaseInsensitive)==0){
            strError=tr("Client databases can only be updated by the master!");
        return false;
    } else if (m_dbmode==INVALID) return false; // it should never come here

    QVariantMap nestedMap1 = result["session"].toMap();
    QVariantMap nestedMap3 = nestedMap1["base_date"].toMap();

    QString strDateUTC=nestedMap3["date_utc"].toString();
    QString strDateLocal=nestedMap3["date_local"].toString();
    int dateType=nestedMap3["date_type"].toInt();
    QString strCityName=nestedMap1["city_name"].toString();
    QString strMacAddress=nestedMap1["mac_address"].toString();
    QString strUser=nestedMap1["user"].toString();

    QString lu_master=result["lu_master"].toInt();

    if (!startPatchSession(strDateUTC,strDateLocal,dateType,strCityName,strMacAddress,strUser)){
         strError=tr("Could not start a mini session!!");
         return false;
    }

    foreach(QVariant change, result["change"].toList()) {

        QVariantMap nestedMap = change.toMap();
        QVariantMap nestedMap2 = nestedMap["values"].toMap();

        QVariant vFrom=nestedMap2["from"];
        QVariant vTo=nestedMap2["to"];

        
        //identifying fk references
        if (nestedMap2["from"].toString().contains("Ref:",Qt::CaseInsensitive)){
            if (!identifyReference(result["FK"].toList(),nestedMap2["from"].toString(),
                vFrom,strError)) return false;
        }

        if (nestedMap2["to"].toString().contains("Ref:",Qt::CaseInsensitive)){
            if (!identifyReference(result["FK"].toList(),nestedMap2["to"].toString(),
                vTo,strError)) return false;
        }

        //apply

        InfoChanges ichanges(nestedMap["id"].toInt(),nestedMap["table"].toString(),
            nestedMap["column"].toString(), vFrom, vTo);
        lChanges.push_back(ichanges);
    }

    endSession();

    return true;
}
*/
bool conf_app::readChangesfromPatch(const QString strContent, QString& strDateUTC, QString& strDateLocal,
                        int& dateType, QString& strCityName, QString& strMacAddress, QString& strUser, int& lu_master, listInfoChanges& lChanges, 
                        QList<QVariant>& mapReferences, QString& strError)
{
    bool ok;
    QVariantMap result = Json::parse(strContent, ok).toMap();

    if(!ok){
        strError=tr("Could not parse JSON content!")
        +tr("\n Are you sure the syntax is valid?");

        return false;
    }

    QString strMode= result["mode"].toString();

    if (m_dbmode==MASTER && strMode.compare(strMasterName, Qt::CaseInsensitive)==0){
            strError=tr("Master databases can only be updated by clients!");
        return false;
    }else if (m_dbmode==CLIENT && strMode.compare(strClientName, Qt::CaseInsensitive)==0){
            strError=tr("Client databases can only be updated by the master!");
        return false;
    } else if (m_dbmode==INVALID) return false; // it should never come here

    QVariantMap nestedMap1 = result["session"].toMap();
    QVariantMap nestedMap3 = nestedMap1["base_date"].toMap();

    strDateUTC=nestedMap3["date_utc"].toString();
    strDateLocal=nestedMap3["date_local"].toString();
    dateType=nestedMap3["date_type"].toInt();
    strCityName=nestedMap1["city_name"].toString();
    strMacAddress=nestedMap1["mac_address"].toString();
    strUser=nestedMap1["user"].toString();

    lu_master=result["lu_master"].toInt();

    mapReferences=result["FK"].toList();

    foreach(QVariant change, result["change"].toList()) {

        QVariantMap nestedMap = change.toMap();
        QVariantMap nestedMap2 = nestedMap["values"].toMap();

        QVariant vFrom=nestedMap2["from"];
        QVariant vTo=nestedMap2["to"];

        InfoChanges ichanges(nestedMap["id"].toInt(),nestedMap["table"].toString(),
            nestedMap["column"].toString(), vFrom, vTo);
        lChanges.push_back(ichanges);
    }

    return true;
}

bool conf_app::findJSONReference(const QList<QVariant>& mapReferences, const int ID, QVariantMap& map,
                             QString& strTable, QString& strError)
{
    foreach(QVariant fk, mapReferences) {
        QVariantMap nestedMap = fk.toMap();
        if (nestedMap["id"].toInt()==ID){
            map=nestedMap["record"].toMap();
            strTable=nestedMap["table"].toString();
            break;
        }
    }

    if (map.isEmpty()|| strTable.isEmpty()){
        strError=QObject::tr("Could not find this reference on the FK section!");
        return false;
    }
    return true;
}

bool conf_app::findDBReference(const QList<QVariant>& mapReferences, const QString strTable, QVariantMap map, QVariant& outID, QString& strError)
{
    map.remove("ID");

    QString strQuery="SELECT ID FROM [";
    strQuery+=strTable;
    strQuery+="] WHERE ";

    QVariantMap::const_iterator i;
     for (i = map.constBegin(); i != map.constEnd(); ++i){
        if (i!=map.constBegin()) strQuery +=" AND ";

        bool bHasQuotes=false;

        //TODO: test if the type is coming ok
        QSqlRecord rec;
        if (!getTypeInfo(strTable,i.key(),rec)) return false;

        if (rec.field(0).value()=="nvarchar") bHasQuotes=true;

        QString strValue=i.value().toString();
        if (i.value().toString().contains("Ref:",Qt::CaseInsensitive)){
            QVariant outV;
            if (!identifyReference(mapReferences,i.value().toString(),outV,strError)) return false;
            strValue=outV.toString();
        }
        if (!i.value().toMap().isEmpty() && i.value().toMap()["date"].isValid()){
            QList<int> ids;
            if (!identifyDate(InfoDate(i.value().toMap()["date"].toMap()["date_utc"].toString(),
                i.value().toMap()["date"].toMap()["date_local"].toString(),
                i.value().toMap()["date"].toMap()["date_type"].toInt()),ids,strError))
                    return false;

            strQuery+=" (";
            for (int j=0; j < ids.size(); ++j){
                if (j>0) strQuery+=" OR ";
                strQuery+=i.key();
                strQuery+="=";
                strQuery+=QVariant(ids.at(j)).toString();
            }
            strQuery+=" )";
        }else{
            strQuery+=i.key();
            strQuery+=QString("=")+(bHasQuotes?QString("'"):QString(""))+strValue
                +(bHasQuotes?QString("'"):QString(""));
        }
     }

    QSqlQuery query;
    query.prepare(strQuery);
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() < 1){
         if (query.lastError().type() != QSqlError::NoError)
             strError=query.lastError().text();
         else
             strError=QObject::tr("Could not identify any record in the DB!");
         return false;
        }

    //TODO: what about if there is more than one record?
     if (query.numRowsAffected() > 1){
        qDebug() << "Warning: identifed more than one record in the DB!" << endl;
        qDebug() << strQuery << endl;
     }

    query.first();
    outID=query.value(0);

    return true;
}

bool conf_app::identifyReference(const QList<QVariant>& mapReferences, const QString strRef, QVariant& outV, QString& strError)
{
    QVariantMap map;
    QString strID=strRef.right(strRef.length()-strRef.lastIndexOf(":")-1);
    QString strTable;

    if (!findJSONReference(mapReferences,strID.toInt(),map,strTable,strError)) return false;
    if (!findDBReference(mapReferences,strTable,map,outV,strError)) return false;

    return true;
}

bool conf_app::readFile(const QString strFileName, QString& outStr)
{
     QFile file(strFileName);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return false;

     QByteArray ba=file.readAll();
     outStr=QString::fromUtf8(ba);

    return true;
}

void conf_app::initUI()
{
    this->setWindowTitle(qApp->applicationName() + qApp->applicationVersion());

    toolbar->addAction(this->actionExit);
    toolbar->addAction(this->actionCreate_backup);
    toolbar->addAction(this->actionRestore_backup);
    toolbar->addAction(this->actionPatch);
    toolbar->setFloatable(true);
    toolbar->setMovable(true);

     connect(actionShow_startup_message, SIGNAL(triggered(bool)),this,
        SLOT(onShowStartupMsg(bool) ),Qt::UniqueConnection);

     connect(actionCreate_backup, SIGNAL(triggered()),this,
        SLOT(doBackup() ),Qt::UniqueConnection);

     connect(actionRestore_backup, SIGNAL(triggered()),this,
        SLOT(doRestore() ),Qt::UniqueConnection);

     connect(actionPatch, SIGNAL(triggered()),this,
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

        if (aModel==roleModel){
            //refresh combo
            userModel->relationModel(2)->select();
            comboRole->setModel(userModel->relationModel(2));
        }
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

    m_dbmode=INVALID;
    setWindowTitle(qApp->applicationName() + qApp->applicationVersion());

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

        //QSqlDatabase::database().setDatabaseName(lineDatabase->text());

        //Checks the type of the database (master/client)
        bool bIsMaster;
        if (!isMaster(bIsMaster)){
            QMessageBox msgBox(QMessageBox::Critical,tr("Database Error"),
                tr("Could not search for master information! Database may be corrupted"),QMessageBox::Ok,0);
            msgBox.exec();
            exit(0);
        }
        m_dbmode=(bIsMaster?MASTER:CLIENT);
        
        if (m_dbmode==MASTER){
            toolbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            setWindowTitle(qApp->applicationName() + qApp->applicationVersion()
                + " (" + strMasterName + ")");

        }else if (m_dbmode==CLIENT){
            toolbar->setStyleSheet("");
            setWindowTitle(qApp->applicationName() + qApp->applicationVersion()
                + " (" + strClientName + ")");

        }else{
            QMessageBox msgBox(QMessageBox::Critical,tr("App Error"),
                tr("Could not assign master/client mode to the application!"),QMessageBox::Ok,0);
            msgBox.exec();
            exit(0);
        }

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

    } else if (aModel==roleModel){

        //cleaning the formatting from previous validations...
        lineRoleName->setStyleSheet("");
        checkAdmin->setStyleSheet("");
        checkMod->setStyleSheet("");
        checkNew->setStyleSheet("");
        checkRemove->setStyleSheet("");
        checkRep->setStyleSheet("");
        checkView->setStyleSheet("");

        if (lineRoleName->text().isEmpty()){
            strError=tr("Role name must not be empty!"); lineRoleName->setStyleSheet(strStyleSheet);
        } else if (!checkAdmin->isChecked() && !checkMod->isChecked() &&
            !checkNew->isChecked() && !checkRemove->isChecked() && !checkRep->isChecked()
            && !checkView->isChecked()){
                strError=tr("You must select at least one permission type!");
                checkAdmin->setStyleSheet(strStyleSheet);
                checkMod->setStyleSheet(strStyleSheet);
                checkNew->setStyleSheet(strStyleSheet);
                checkRemove->setStyleSheet(strStyleSheet);
                checkRep->setStyleSheet(strStyleSheet);
                checkView->setStyleSheet(strStyleSheet);
        }

        bOk=!lineRoleName->text().isEmpty() && (checkAdmin->isChecked() || checkMod->isChecked() ||
            checkNew->isChecked() || checkRemove->isChecked() || checkRep->isChecked()
            || checkView->isChecked());
    } else bOk=false;

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

void conf_app::adjustEnables(QPushButton* aPushEdit,QPushButton* aPushRemove,QSqlTableModel* aModel)
{
    aPushEdit->setEnabled(aModel->rowCount()>0);
    aPushRemove->setEnabled(aModel->rowCount()>0);
}

void conf_app::adjustUserEnables()
{
    if (!userModel || !pushEditUser || !pushRemoveUser) return;
    adjustEnables(pushEditUser,pushRemoveUser,userModel);
}

void conf_app::adjustRoleEnables()
{
    if (!roleModel || !pushEditRole || !pushRemoveRole) return;
    adjustEnables(pushEditRole,pushRemoveRole,roleModel);
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

    if (aTable==tableUsers){
        connect(aTable->model(), SIGNAL(rowsInserted ( const QModelIndex, int, int)), this,
            SLOT(adjustUserEnables()));
        connect(aTable->model(), SIGNAL(rowsRemoved ( const QModelIndex, int, int)), this,
            SLOT(adjustUserEnables()));
    }else if (aTable==tableRoles){
        connect(aTable->model(), SIGNAL(rowsInserted ( const QModelIndex, int, int)), this,
            SLOT(adjustRoleEnables()));
        connect(aTable->model(), SIGNAL(rowsRemoved ( const QModelIndex, int, int)), this,
            SLOT(adjustRoleEnables()));
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
