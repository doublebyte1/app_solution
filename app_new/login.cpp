#include "connection.h"
#include "login.h"

#define MaxRecentFiles 5

// static const char *strLoadDatabase = 
//     QT_TRANSLATE_NOOP("Login", "Create new connection...");

Login::Login(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags){

    mainFrmPtr=0;
    thread=0;

    setupUi(this);

    connect(qApp,
                   SIGNAL(aboutToQuit()),
                   this,
                   SLOT(finalTouches()));
}

Login::~Login()
{
    /*!
    //Clean Pointers here!
    */

    if (mainFrmPtr!=0) delete mainFrmPtr;
    if (thread!=0){
        //! Make sure we stop the thread before deleting it;
        while (thread->isRunning()){
            thread->terminate();
            thread->wait();
        }
        delete thread;
    }
}

void Login::finalTouches()
{
    endSession();
}

void Login::endSession()
{
    QSqlTableModel* table= new QSqlTableModel();
    table->setTable(QSqlDatabase().driver()->escapeIdentifier("GL_SESSION",
    QSqlDriver::TableName));
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table->sort(0,Qt::AscendingOrder);
    table->select();

     //end date
     QSqlQuery query;
     query.prepare("exec InsertCurrentDateTime");
     query.exec();
     if (query.lastError().type()!=QSqlError::NoError){
        qDebug() << query.lastError().text() << endl;
     }

    QVariant enddateID;
     QString strError;
     if (!getIDfromLastInsertedDate(enddateID,strError)){
        qDebug() << strError << endl;
     }

    QModelIndex idx=table->index(table->rowCount()-1,6);
    table->setData(idx,enddateID);

    if (!table->submitAll()){
        qDebug() << tr("Could not submit record into GL_Sessions table!") << endl;
    }

    delete table;
}

void Login::validate()
{
        QSqlQuery query;
        query.prepare( "SELECT username, password, name, entry, modify, report, admin FROM \"UI_User\", \"UI_Role\" WHERE ( (dbo.[UI_User].role_id=dbo.[UI_Role].id) AND (username= :user AND password= :pass) )" );
        query.bindValue(":user", lineUser->text() );
        query.bindValue(":pass", linePasswd->text() );

        QMessageBox msgBox;
        if (!query.exec()){
            QMessageBox::critical( this, tr("DB Error"),
            query.lastError().text());
               qApp->exit(0);
        }
        else if (query.numRowsAffected()<1){

            QString strStyleSheet="background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));";
            lineUser->setStyleSheet(strStyleSheet);
            linePasswd->setStyleSheet(strStyleSheet);

            QMessageBox::critical( this, tr("Authentication Error"),
            tr("Username/Password Not Found!"));
        }
        else{
            /*!
            Proceed to Login: but set the role first!
            */
                hide();
                update();

                //Store session data through a thread
                QSettings settings(tr("Medstat"), tr("App"));

                if (thread!=0) {
                    while (thread->isRunning()){
                        thread->terminate();
                        thread->wait();
                    }
                    delete thread; thread=0;
                }

                thread=new StoreSettingsThread();
                thread->setPars(lineUser->text(),settings.value("city").toString());

                if (mainFrmPtr==0) mainFrmPtr=new MainFrm();

                connect(thread, SIGNAL(showError(QString,bool)), mainFrmPtr,
                    SLOT(displayError(QString,bool)));

                connect(thread, SIGNAL(showStatus(QString)), mainFrmPtr,
                    SLOT(statusShow(QString)));

                thread->start(QThread::LowPriority);

                mainFrmPtr->show();
                mainFrmPtr->repaint();
                //This is assynchronous, so no point in checking for return value now...
                //mainFrmPtr->initRules();
            }
}

void Login::showEvent ( QShowEvent * event )
{
    QString strHost, strAlias, strDataSource, strUsername, strPassword, strDriver;
    if (!readSettings(strHost,strAlias,strDataSource,strUsername,strPassword,strDriver))
    {
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("You must run the configurator prior to run this application!"),QMessageBox::Ok,0);
            msgBox.exec();
            qApp->exit(0);
    }else{
        if (!connectDB(strHost,strDataSource,strUsername,strPassword,strAlias,strDriver)){
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("Please run the configurator again and fix the connection values!"),QMessageBox::Ok,0);
            msgBox.exec();
            qApp->exit(0);
        }
    }
}

 bool Login::readSettings(QString& strHost, QString& strAlias, QString& strDatasource, QString& strUsername, 
     QString& strPassword, QString& strDriver)
 {
    QSettings settings(tr("Medstat"), tr("App"));

    /*!
    //Settings for the App credentials
    */
    if (settings.contains("AppUser"))
        lineUser->setText(settings.value("AppUser").toString());
    if (settings.contains("AppPass"))
        linePasswd->setText(settings.value("AppPass").toString());

    if ( !settings.contains("host") || !settings.contains("datasource") ||
        !settings.contains("username") || !settings.contains("password") ||
        !settings.contains("driver") || !settings.contains("city")){
            return false;

    } else{
        //Settings for the DB credentials
        strAlias=settings.value("alias").toString();
        strHost=settings.value("host").toString();
        strDatasource=settings.value("datasource").toString();
        strUsername=settings.value("username").toString();
        strPassword=settings.value("password").toString();
        strDriver=settings.value("driver").toString();
    }

    return true;
 }

 bool Login::connectDB(const QString& strHost,const QString& strDataSource,
        const QString& strUsername,const QString& strPassword,const QString& strAlias, const QString& strDriver)
{
        if (!createConnection(strHost,strDataSource, strUsername,strPassword,strAlias,strDriver)){
            QSqlDatabase db=QSqlDatabase::database();
            QMessageBox::critical( this, tr("User Error"),
                db.lastError().text());

            return false;
       }
    return true;
 }

 ///////////////////////////////////////////////

QString getMacAddress()
{
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(interface.flags() & QNetworkInterface::IsLoopBack))
            return interface.hardwareAddress();
    }
    return QString();
}