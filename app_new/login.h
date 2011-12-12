#ifndef LOGIN_H
#define LOGIN_H

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

//! StoreSettingsThread Class
/*!
This class implements a thread that writes the session settings in the database.
It has low priority, so it does not bother us too much!
*/

class StoreSettingsThread : public QThread
 {
    Q_OBJECT

        public:
            StoreSettingsThread()
            {
              QObject::connect(this,
                               SIGNAL(finished()),
                               this,
                               SLOT(deleteLater()));
            }

            ~StoreSettingsThread(){
            }

            void setPars(const QString strUser, const QString strLocation)
            {
                m_strUser=strUser;
                m_strLocation=strLocation;
            }

            void run(){

                mutex.tryLock();
                bool bOk=insertSessionRecord();
                mutex.unlock();

                if (bOk)
                    emit showStatus (tr("Session settings sucessfully created in the database!"));

                exec();

            }

        signals:
            void        showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages
            void        showStatus(QString str);//!< signal for showing messages in the status bar

        private:

            bool insertSessionRecord()
            {
                //base date
                 QSqlQuery query1;
                 query1.prepare("exec Insert_Base_Date");
                 query1.setForwardOnly(true);
                 query1.exec();
                 if (query1.lastError().type()!=QSqlError::NoError){
                    emit showError(query1.lastError().text(),true);
                    return false;
                 }


                 QVariant basedateID, startdateID;
                 QString strError;
                 if (!getIDfromLastInsertedDate(basedateID,strError)){
                    emit showError(strError,true);
                    return false;
                 }

                 //location
                 QSqlQuery query2;
                 query2.prepare("SELECT ID FROM Ref_Location WHERE (City_Name=:location)");
                 query2.bindValue(":location", m_strLocation);
                 query2.setForwardOnly(true);
                 query2.exec();
                 if (query2.lastError().type()!=QSqlError::NoError){
                    emit showError(query2.lastError().text(),true);
                    return false;
                 }
                 query2.first();
                 QVariant locationID=query2.value(0);

                 //start date
                 QSqlQuery query3;
                 query3.prepare("exec InsertCurrentDateTime");
                 query3.setForwardOnly(true);
                 query3.exec();
                 if (query3.lastError().type()!=QSqlError::NoError){
                    emit showError(query3.lastError().text(),true);
                    return false;
                 }
                 if (!getIDfromLastInsertedDate(startdateID,strError)){
                    emit showError(strError,true);
                    return false;
                 }

                 //end date (for now "n/a": ammend in the end!)
                 QVariant enddateID;
                 if (!getNADate(enddateID,strError)){
                    emit showError(strError,true);
                    return false;
                 }

                 //user
                 QSqlQuery query4;
                 query4.prepare("SELECT ID FROM UI_USER WHERE (username=:username)");
                 query4.bindValue(":username", m_strUser);
                 query4.setForwardOnly(true);
                 query4.exec();
                 if (query4.lastError().type()!=QSqlError::NoError){
                    emit showError(query4.lastError().text(),true);
                    return false;
                 }
                 query4.first();
                 QVariant userID=query4.value(0);

                QSqlTableModel* table= new QSqlTableModel;
                table->setTable(QSqlDatabase().driver()->escapeIdentifier("GL_SESSION",
                QSqlDriver::TableName));
                table->setEditStrategy(QSqlTableModel::OnManualSubmit);
                table->sort(0,Qt::AscendingOrder);
                table->select();

                if (!insertRecordIntoModel(table)){
                    emit showError(tr("Could not insert record into GL_Sessions table!"),true);
                    return false;
                }

                QModelIndex idx=table->index(table->rowCount()-1,1);
                table->setData(idx,userID);
                idx=table->index(table->rowCount()-1,2);
                table->setData(idx,getMacAddress());
                idx=table->index(table->rowCount()-1,3);
                table->setData(idx,basedateID);
                idx=table->index(table->rowCount()-1,4);
                table->setData(idx,locationID);
                idx=table->index(table->rowCount()-1,5);
                table->setData(idx,startdateID);
                idx=table->index(table->rowCount()-1,6);
                table->setData(idx,enddateID);
                idx=table->index(table->rowCount()-1,7);
                table->setData(idx,tr("This is an automated generated session record: pls do not attempt to edit it!"));

                if (!table->submitAll()){
                    emit showError(tr("Could not submit record into GL_Sessions table!"),true);
                    delete table;
                    return false;
                }

                delete table;
                return true;
            }

            QString             m_strDatabase;
            QString             m_strUser;
            QString             m_strPassword;
            QString             m_strLocation;
            QMutex              mutex;
 };
/////////////////////////////////////////////////////////////////////////////////

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
        void                                showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages
        void                                showStatus(QString str);//!< signal for showing messages in the status bar

    public slots:
        void                                validate();
        bool                                connectDB(const QString& strHost,const QString& strDataSource,
        const QString&                      strUsername,const QString& strPassword,const QString& strAlias, const QString& strDriver);

    private slots:
            void                            finalTouches();

    private:
            bool                            disconnectDB();
            void                            loadFile(const QString &fileName);
            bool                            readSettings(QString& strHost, QString& strAlias, QString& strDatasource, QString& strUsername, 
                                                QString& strPassword, QString& strDriver);
            void                            showEvent ( QShowEvent * event );
            bool                            startSession(const QString strUser, const QString strLocation);
            void                            endSession();

            MainFrm*                        mainFrmPtr;
};

#endif // LOGIN_H
