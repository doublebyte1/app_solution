#include <QtGui>
#include <QtSql>
 #include <QThread>
#include <QtNetwork/QNetworkInterface>

#include "ui_login.h"
#include "mainfrm.h"
#include "frmconnect.h"
//#include "roledef.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

#ifndef STORESETTINGSTHREAD_H
#define STORESETTINGSTHREAD_H

QString                         getMacAddress();

//////////////////////////////////////////////////////////////////////////////

//! StoreSettingsThread Class
/*!
Storing settings was taking too long, so we put it inside a class, with low priority;
*/

class StoreSettingsThread : public QThread
 {
    Q_OBJECT

        public:
            StoreSettingsThread(){
              QObject::connect(this,
                               SIGNAL(finished()),
                               this,
                               SLOT(deleteLater()));
            }

            void setPars(const QString strDatabase, const QString strUser, const QString strPassword)
            {
                m_strDatabase=strDatabase;
                m_strUser=strUser;
                m_strPassword=strPassword;
            }

            void run(){
                //Store settings
                QSettings settings("Medstat", "App");
                settings.setValue("AppUser", m_strUser);
                settings.setValue("AppPass", m_strPassword);

                qDebug() << getMacAddress() << endl;

                 exec();
            }

        private:
            QString     m_strDatabase;
            QString     m_strUser;
            QString     m_strPassword;

 };
#endif //STORESETTINGSTHREAD_H
/////////////////////////////////////////////////////

#ifndef LOGIN_H
#define LOGIN_H

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! Login Class
/*!
This class contains an instantiation of the UI Login class;
*/

class Login : public QWidget, public Ui::frmLogin
{
    Q_OBJECT

    public:
        Login(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~Login();

    signals:
        void                                gotConnection(bool bOk);

    public slots:
        void                                validate();
        void                                loadForm(const QString& strName);
        void                                showForm(const QString& strName);
        void                                connectDB(const QString& strHost,const QString& strDataSource,
        const QString&                      strUsername,const QString& strPassword,const QString& strAlias, const QString& strDriver);

    private slots:
        //void                                onGotConnection(bool bOk);

    private:
            bool                            disconnectDB();
            void                            loadFile(const QString &fileName);
            void                            loadSettings();

            MainFrm*                        mainFrmPtr;
            FrmConnect*                     frmConnectPtr;
            bool                            m_connected;
            StoreSettingsThread*            thread;
            //RoleDef*		rolePtr;

};

#endif // LOGIN_H
