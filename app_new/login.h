#include <QtGui>
#include <QtSql>
 #include <QThread>
#include <QtNetwork/QNetworkInterface>

#include "ui_login.h"
#include "mainfrm.h"
//#include "roledef.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

QString                         getMacAddress();

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
        bool                                connectDB(const QString& strHost,const QString& strDataSource,
        const QString&                      strUsername,const QString& strPassword,const QString& strAlias, const QString& strDriver);

    private:
            bool                            disconnectDB();
            void                            loadFile(const QString &fileName);
            bool                            readSettings(QString& strHost, QString& strAlias, QString& strDatasource, QString& strUsername, 
                                                QString& strPassword, QString& strDriver);
            void                            showEvent ( QShowEvent * event );

            MainFrm*                        mainFrmPtr;

};

#endif // LOGIN_H
