#include "connection.h"
#include "login.h"

#define MaxRecentFiles 5

// static const char *strLoadDatabase = 
//     QT_TRANSLATE_NOOP("Login", "Create new connection...");

Login::Login(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags){

    mainFrmPtr=0;
    userModel=0;
    m_roleDef=0;

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
    if (userModel!=0) delete userModel;
    if (m_roleDef!=0) delete m_roleDef;
}

void Login::finalTouches()
{
    endSession();
}

void Login::updateTooltip(QString user){

    cmbUser->setToolTip(cmbUser->model()->index(cmbUser->currentIndex(),1).data().toString());
}

void Login::initCmbUsers()
{
    userModel=new QSqlQueryModel();
    userModel->setQuery("SELECT username, description from UI_USER");
    if (userModel->rowCount()<1){
        emit showError(tr("There are no users defined in the database! The app is unusable!"));
        exit(0);//severe!
    }
    cmbUser->setModel(userModel);
    cmbUser->setModelColumn(0);

    QSettings settings(tr("Medstat"), tr("App"));
    if (settings.contains("AppUser")){
        int cur=cmbUser->findText(settings.value("AppUser").toString(),Qt::MatchExactly);
        if (cur==-1){
            emit showError(tr("Wrong user stored on the registry! How is this possible?"));
            exit(0);
        }
        cmbUser->setCurrentIndex(cur);
    }
}

void Login::validate()
{
        QSqlQuery query;
        query.prepare( "SELECT username, password, name, new, [view], modify, remove, report, admin FROM \"UI_User\", \"UI_Role\" WHERE ( (dbo.[UI_User].role_id=dbo.[UI_Role].id) AND (username= :user AND password= :pass) )" );
        query.bindValue(":user", cmbUser->currentText() );
        query.bindValue(":pass", linePasswd->text() );
        query.setForwardOnly(true);

        QMessageBox msgBox;
        if (!query.exec()){
            QMessageBox::critical( this, tr("DB Error"),
            query.lastError().text());
               exit(0);
        }
        else if (query.numRowsAffected()<1){

            QString strStyleSheet="background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));";
            cmbUser->setStyleSheet(strStyleSheet);
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

                //Store session data, username and passwd
                QSettings settings(tr("Medstat"), tr("App"));
                settings.setValue("AppUser", cmbUser->currentText());

                if (!setRoleDef(&query)){
                    emit showError(tr("Could not retrieve the role of this user on the database!"));
                    exit(0);
                }

                if (mainFrmPtr==0) mainFrmPtr=new MainFrm(m_roleDef);

                connect(this, SIGNAL(showError(QString,bool)), mainFrmPtr,
                    SLOT(displayError(QString,bool)));

                connect(this, SIGNAL(showStatus(QString)), mainFrmPtr,
                    SLOT(statusShow(QString)));

                //base date
                if (!insertBaseDate()) return;

                 QVariant basedateID;
                 QString strError;
                 if (!getIDfromLastInsertedDate(basedateID,strError)){
                    QMessageBox::critical(0, QObject::tr("Session Error"), strError);
                    return;
                 }

                if (!startSession(cmbUser->currentText(),settings.value("city").toString(),
                    getMacAddress(),basedateID)){
                    emit showError(tr("Could not initialize session data!"));
                }

                mainFrmPtr->show();
                mainFrmPtr->repaint();
                //This is assynchronous, so no point in checking for return value now...
                mainFrmPtr->initRules();
            }
}

bool Login::setRoleDef(QSqlQuery* query)
{
    if (!query->isActive()){
        emit showError(tr("Could not use the role query!"));
        return false;
    }
    query->first();

    m_roleDef=new RoleDef();
    m_roleDef->bNew=query->value(3).toBool();
    m_roleDef->bView=query->value(4).toBool();
    m_roleDef->bMod=query->value(5).toBool();
    m_roleDef->bDel=query->value(6).toBool();
    m_roleDef->bRep=query->value(7).toBool();
    m_roleDef->bAdmin=query->value(8).toBool();

    return true;
}

void Login::showEvent ( QShowEvent * event )
{
    QString strHost, strDatabase, strUsername, strPassword, strDriver;
    if (!readSettings(strHost,strDatabase,strUsername,strPassword,strDriver))
    {
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("You must run the configurator prior to run this application!") +
                tr("\n Make sure you filled the connection settings *and* the global settings!"),QMessageBox::Ok,0);
            msgBox.exec();
            exit(0);
    }else{
        if (!connectDB(strHost,strDatabase,strUsername,strPassword,strDriver)){
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("Please run the configurator again and fix the connection values!"),QMessageBox::Ok,0);
            msgBox.exec();
            exit(0);
        }
    }
    //now let's check if it's a master database (if it is, we don't want to use it!)
    bool bIsMaster;
    if (!isMaster(bIsMaster)){
        QMessageBox msgBox(QMessageBox::Critical,tr("Database Error"),
            tr("Could not search for master information! Database may be corrupted"),QMessageBox::Ok,0);
        msgBox.exec();
        exit(0);
    } else if (bIsMaster){
        QMessageBox msgBox(QMessageBox::Critical,tr("Access Error"),
        tr("This is a master database: It cannot be used for data introduction!"),QMessageBox::Ok,0);
        msgBox.exec();
        exit(0);
    }
    //if everything went ok, lets read the users from the db!
    initCmbUsers();

}

 bool Login::readSettings(QString& strHost, QString& strDatabase, QString& strUsername, 
     QString& strPassword, QString& strDriver)
 {
    QSettings settings(tr("Medstat"), tr("App"));

    /*!
    //Settings for the App credentials
    */
    //n.b.: user is read later, after the combo is filled!

    if (settings.contains("AppPass"))
        linePasswd->setText(settings.value("AppPass").toString());

    if ( !settings.contains("host") || !settings.contains("database") ||
        !settings.contains("username") || !settings.contains("password") ||
        !settings.contains("driver") || !settings.contains("city")){
            return false;

    } else{
        //Settings for the DB credentials
        strHost=settings.value("host").toString();
        strDatabase=settings.value("database").toString();
        strUsername=settings.value("username").toString();
        strPassword=settings.value("password").toString();
        strDriver=settings.value("driver").toString();
    }

    return true;
 }

 bool Login::connectDB(const QString strHost,const QString strDatabase,
        const QString strUsername,const QString strPassword, const QString strDriver)
{
        if (!createConnection(strHost,strDatabase, strUsername,strPassword,strDriver)){
            QSqlDatabase db=QSqlDatabase::database();
            QMessageBox::critical( this, tr("User Error"),
                db.lastError().text());

            return false;
       }
    return true;
 }

 ///////////////////////////////////////////////
