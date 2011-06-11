#include "connection.h"
#include "login.h"

#define MaxRecentFiles 5

 static const char *strLoadDatabase = 
     QT_TRANSLATE_NOOP("Login", "Create new connection...");

Login::Login(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags),m_connected(0){

    frmConnectPtr=0;
    mainFrmPtr=0;
    thread=0;

    setupUi(this);
    loadSettings();
}

Login::~Login()
{
    /*!
    //Clean Pointers here!
    */

    if (frmConnectPtr!=0) delete frmConnectPtr;
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

void Login::validate()
{
    for (size_t i=0; i < (size_t)gridLayout->count(); ++i)
        gridLayout->itemAt(i)->widget()->setEnabled(false);

    if (!m_connected){//Tries to connect like this
        frmConnectPtr->accept();
    }

    if (m_connected)
    {
        QSqlQuery query;
        query.prepare( tr("SELECT username, password, name, entry, modify, report, admin FROM \"UI_User\", \"UI_Role\" WHERE ( (dbo.[UI_User].role_id=dbo.[UI_Role].role_id) AND (username= :user AND password= :pass) )") );
        query.bindValue(tr(":user"), lineUser->text() );
        query.bindValue(tr(":pass"), linePasswd->text() );

        QMessageBox msgBox;
        if (!query.exec()){
            QMessageBox::critical( this, tr("DB Error"),
            query.lastError().text());
               //TODO: remove previous database connection
               qApp->exit(0);
        }
        else if (query.numRowsAffected()<1){
            QMessageBox::critical( this, tr("User Error"),
            tr("Username/Password Not Found!"));
            for (size_t i=0; i < (size_t)gridLayout->count(); ++i)
                gridLayout->itemAt(i)->widget()->setEnabled(true);
        }
        else{
            /*!
            Proceed to Login: but set the role first!
            */
                hide();
                update();
                if (mainFrmPtr==0) mainFrmPtr=new MainFrm();
                mainFrmPtr->show();
                mainFrmPtr->repaint();
                //This is assynchronous, so no point in checking for return value now...
                mainFrmPtr->initRules();

                //Store settings through a thread
                thread=new StoreSettingsThread();
                thread->setPars(tr("Database"),lineUser->text(),linePasswd->text());
                thread->start(QThread::LowPriority);
            }
        }
}

 void Login::loadSettings()
 {
     if (frmConnectPtr==0){
        frmConnectPtr=new FrmConnect(this);
        connect(frmConnectPtr, SIGNAL(ok(QString,QString,QString,QString,QString,QString)), this,
            SLOT(connectDB(QString,QString,QString,QString,QString,QString)));
    }

    QSettings settings(tr("Medstat"), tr("App"));

    /*!
    //Settings for the App credentials
    */
    if (settings.contains(tr("AppUser")))
        lineUser->setText(settings.value(tr("AppUser")).toString());
    if (settings.contains(tr("AppPass")))
        linePasswd->setText(settings.value(tr("AppPass")).toString());

    /*!
    //Settings for the Db credentials
    */
    if (settings.contains(tr("alias")))
        cmbFiles->addItem(settings.value(tr("alias")).toString());

    cmbFiles->addItem(qApp->translate("Login",strLoadDatabase));
 }

void Login::loadForm(const QString& strName)
{
    //clean form
    if (!strName.compare(strLoadDatabase,Qt::CaseSensitive)){

        for (size_t i=0; i < (size_t)frmConnectPtr->gridLayout->count(); ++i)
            if (dynamic_cast<QLineEdit*>(frmConnectPtr->gridLayout->itemAt(i)->widget())!=0)
                dynamic_cast<QLineEdit*>(frmConnectPtr->gridLayout->itemAt(i)->widget())->setText(tr(""));
        }
     else{
    /*!
    //Settings for the DB credentials
    */
        QSettings settings(tr("Medstat"), tr("App"));

        if (settings.contains(tr("alias")) &&
            settings.value(tr("alias")).toString()==strName){
                QString strAlias=settings.value(tr("alias")).toString();

                    frmConnectPtr->lineAlias->setText(strAlias);
                    frmConnectPtr->lineHost->setText(settings.value(tr("host")).toString());
                    frmConnectPtr->lineDataSource->setText(settings.value(tr("datasource")).toString());
                    frmConnectPtr->lineUsername->setText(settings.value(tr("username")).toString());
                    frmConnectPtr->linePassword->setText(settings.value(tr("password")).toString());
                    frmConnectPtr->cmbDriver->setCurrentIndex(
                            frmConnectPtr->cmbDriver->findText(
                                settings.value(tr("driver")).toString()));
        }
    }
}

 void Login::showForm(const QString& strName)
 {
    loadForm(strName);
    frmConnectPtr->show();
 }

 void Login::connectDB(const QString& strHost,const QString& strDataSource,
        const QString& strUsername,const QString& strPassword,const QString& strAlias, const QString& strDriver)
    {
        if (!m_connected){
            if (!createConnection(strHost,strDataSource, strUsername,strPassword,strAlias,strDriver)){
                QSqlDatabase db=QSqlDatabase::database();
                QMessageBox::critical( this, tr("User Error"),
                    db.lastError().text());
           }
        else{
            cmbFiles->setEnabled(false);
            frmConnectPtr->hide();

                QSettings settings(tr("Medstat"), tr("App"));
                settings.setValue(tr("host"), strHost);
                settings.setValue(tr("datasource"), strDataSource);
                settings.setValue(tr("username"), strUsername);
                settings.setValue(tr("password"), strPassword);
                settings.setValue(tr("alias"), strAlias);
                settings.setValue(tr("driver"), strDriver);

                if (cmbFiles->count()>1)cmbFiles->removeItem(0);
                cmbFiles->insertItem(cmbFiles->count()-2,strAlias);
                cmbFiles->setCurrentIndex(cmbFiles->count()-2);
                m_connected=1;
            }
        }
        else{//!< It should never bother the user with this! Why are we still connected?? :-(
            QMessageBox::critical( this, tr("App Error"),		
                tr("Could not remove previous database connection!"));

        }
 }