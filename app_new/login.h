#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui>
#include <QtSql>
 #include <QThread>
#include <QtNetwork/QNetworkInterface>

#include "ui_login.h"
#include "mainfrm.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

QString                         getMacAddress();

//! StoreSettingsThread Class
/*!
This class implements a thread that writes the session settings in the database.
It has low priority, so it does not bother us too much!
n.b.: discontinued!
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

        //void                                gotConnection(bool bOk);
        void                                showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages
        void                                showStatus(QString str);//!< signal for showing messages in the status bar

    public slots:
        //! Validate
        /*! This is the function that validates username and password, and if the authentication goes through
        proceeds with the launching of the main application and starts the init rules thread.
        */
        void                                validate();
        //! Connect DB
        /*! This is the function that establishes a connection with the DB. All parameters here are
        read from the registry, as we need to set them up first using the configurator.
        \par strHost host name as string
        \par strDatabase database name as string
        \par strUsername username as string
        \par strPassword password as string
        \par strDriver driver name as string
        \returns boolean as success or failure
        \sa disconnectDB()
        */
        bool                               connectDB(const QString strHost,const QString strDatabase,
        const QString                      strUsername,const QString strPassword, const QString strDriver);

    private slots:
            //! Final Touches
            /*! This slots is connected to the signal aboutToQuit();
            We use it to perform tasks that we want to do when leaving the app (for instace writing the end of session data)
            */
            void                            finalTouches();
            //! Update tooltip
            /*! This slots updates the tooltip of the username combobox, with the user
            description (read from the database)
            \par user username as string
            */
            void                            updateTooltip(QString user);

    private:
            //! Set Role Definition
            /*! This slots is called after a successfull validation through validate() and
            ot basically fills the RoleDef structure, with the values of this query.
            The RoleDef structure encapsulates the permission model for the current user, and it 
            is going to be passed around forms (on their construction) to define which portion
            of the UI is visible, in the session.
            \par query active query, containing the role definition for the current user
            \return boolean as success or failure
            */
            bool                            setRoleDef(QSqlQuery* query);
            //! Init combo users
            /*! This function initializes the combobox with a list of usernames
            */
            void                            initCmbUsers();
            //! Read Settings
            /*!
            This function reads the connection settings from the registry, and stores the inside the argument variables.
            It is used to retreive the values, to silently connect to the database.
            \par strHost address of a string to store the host name
            \par strDatabase address of a string to store the database name
            \par strUsername address of a string to store the username
            \par strPassword address of a string to store the password
            \par strAlias database address of a string to store the alias
            \par strDriver address of a string to store the driver name
            \return boolean as success or failure
            \sa connectDB(const QString strHost,const QString strDatabase,const QString
            strUsername,const QString strPassword,const QString strAlias, const QString strDriver)
            */
            bool                            readSettings(QString& strHost, QString& strDatabase, QString& strUsername, 
                                                QString& strPassword, QString& strDriver);
            //! Show Event
            /*!
            Reimplemented from the base class.
             */
            void                            showEvent ( QShowEvent * event );
            //! Start Session
            /*! This function initializes session data in the database, by creating a record on table GL_Dates.
            This record is completed, at the end of the session (with end date).
            \par strUser username as string
            \par strLocation location as string
            \return boolean as success or failure
            \sa endSession()
            */
            bool                            startSession(const QString strUser, const QString strLocation);
            //! End Session
            /*! This function completes the session data in the database, by amending a record on table GL_Dates.
            This record was initialized with startSession(const QString strUser, const QString strLocation).
            \sa startSession(const QString strUser, const QString strLocation)
            */
            void                            endSession();
            QSqlQueryModel*                 userModel;//!< Pointer to a model containing the users and roles from the database
            MainFrm*                        mainFrmPtr;//!< Pointer to a main form object
            RoleDef*                        m_roleDef;//!< Pointer to a RoleDef structure
};

#endif // LOGIN_H
