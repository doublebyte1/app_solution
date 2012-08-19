#ifndef CONF_APP_H
#define CONF_APP_H

#include <QtSql>
#include <QtGui>
#include "ui_conf_app.h"
#include "nullrelationaldelegate.h"

#if defined(WIN32) && defined(_DEBUG)
 #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
 #define new DEBUG_NEW
#endif

//! Query show startup Msg
/*! This is an utility function to query the registry and
find out if we need to display the startup msg dialog
\return boolean to indicate if we need to display the startup msg
*/
bool                      queryShowStartupMsg();
bool                      queryShowSqlMsg();

void                      resizeToVisibleColumns ( QTableView* table );
void                      filterTable(QSqlTableModel* table);
bool                      insertRecordIntoModel(QSqlTableModel* m);

//! Configure Application Class
/*!
This class is the main dialog of the Configurator.
It is a simple app, with a toolbar and a file menu providing basic options, and a
toolbox with the settings grouped by sections. All this information is read and written on
the registry, so that it can be used next time and also by other applications, part of the Medfisis package.
*/

class conf_app : public QMainWindow, public Ui::conf_appClass
{
    Q_OBJECT

    public:
        conf_app(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~conf_app();

    signals:
        void                    connectionChanged();//!< Signal to indicate that the connection state changed (connected or disconnected)
        void                    statusShow(const QString str);//!< Signal indicating we want to display a message on the toolbar
        void                    submit(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupBox,
                                            QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                                            QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel);
        void                    lockControls(bool bLock,QGroupBox* box);/**< signal to lock/unlock a list of controls */
        //void                    doneWithProcess();//!< Signal to indicate that the process executed
        void                     editLeave(const bool bFinished,QPushButton* aPushEdit=0,QPushButton* aPushNew=0,
                                   QPushButton* aPushRemove=0,QGroupBox* group=0,QDataWidgetMapper* aMapper=0,QSqlTableModel* aModel=0,
                                   QDialogButtonBox* buttons=0,const bool bDiscarded=false);

    private slots:
        //! Show Table
        /*!
        This function displays a particular table (argument) in the tableview.
        It sets the table of the model, hides the identity column, and shows the edition buttons,
         \param strTable A table name
         \sa listTables(),applyChanges2Table()
        */
        void                    showTable(const QString strTable);
        //! Apply Changes to Table
        /*!
        This function apply all the uncomited changes to the database and works out the 
        enabling/disabling of buttons.
         \sa listTables(),showTable(const QString strTable)
        */
        void                    applyChanges2Table();
        //! Connect to the Database
        /*!
        This function establishes a connection to the database.
         \sa disconnectDB()
        */
        void                    connectDB();
        //! Disconnect from the Database
        /*!
        This function disconnects the existent connection to the database.
         \sa connectDB()
        */
        void                    disconnectDB();
        //! On Connection change
        /*!
        This is the slot that connects to the connectionChanged() signal; here we work out
        the enabling/disabling of buttons, according to the connection status;
         \sa connectionChanged()
        */
        void                    onConnectionChange();
        //! On Status Show
        /*!
        This is the slot that connects to the statusShow(const QString str) signal; here we display the
        string argument, in the statusbar.
         \param str status message
         \sa statusShow(const QString str)
        */
        void                    onStatusShow(const QString str);
        //! Filter Model
        /*!
        This slot establishes the query model for the country combobox; this is a query to
        table "Ref_Countries", with a WHERE clause for the country that we pass as argument.
         \param strCountry country
        */
        void                    filterModel(QString strCountry);
        //! Apply
        /*!
        This slot saves the regional settings to the registry and applies the correspondent
        enable/disable of buttons in the UI.
        */
        void                    apply();
        //! Enable Apply
        /*!
        This slot enables the apply button.
        */
        void                    enableApply();
        //! On Show Startup Message Interface
        /*!
        This slot calls the onShowStartupMsg(const bool bShow), and updates also the action menu.
         \param bNoShow boolean variable indicating if we want to show startup msg (false), or not (true)
         \sa onShowStartupMsg(const bool bShow)
        */
        void                    onShowStartupMsgI(bool bNoShow);
        //! On Show Startup Message
        /*!
        This slot stores on the registry our choices for startup message showing, so that 
        we can remember it next time.
         \param bShow boolean variable indicating if we want to show startup msg (true), or not (false)
         \sa onShowStartupMsgI(bool bNoShow)
        */
        void                    onShowStartupMsg(const bool bShow);
        //! Insert row
        /*!
        This slot inserts a row in the table
         \sa removeRow()
        */
        void                    insertRow();
        //! Remove row
        /*!
        This slot removes a row from the table
         \sa insertRow()
        */
        void                    removeRow();
        //! Do Backup
        /*!
        This slot performs the backup of the database in a file; for that, we reuse the existent
        database connection!
         \sa doRestore()
        */
        void                    doBackup();
        //! Do Restore
        /*!
        This slot performs the restore of the database from a file; we need exclusive access to the db
        to perform this, so we can neither reuse the existent connection, nor connect through the odbc
        using the existent dns (that is associated to the default database). We use a trick of
        launching sqlcmd as a process, and sending as parameters a script file with the restore query.
        This file is created "on-the-fly" based on our parameters (filename with restore), and removed
        when we no longer need it.
         \sa doBackup()
        */
        void                    doRestore();

        void                    doDump();
        void                    doPatch();

        //! Read Process Error
        /*!
        This slot connects to the readyReadStandardError() signal of the process launched with sqlcmd;
        here we can catch any errors thrown by this process.
         \sa readProcessOutput(), processFinished()
        */
        void                    readProcessError();
        //! Read Process Output
        /*!
        This slot connects to the readyReadStandardOutput() signal of the process launched with sqlcmd;
        here we can catch any output thrown by this process.
         \sa readProcessError(), processFinished()
        */
        void                    readProcessOutput();
        //! Process Finished
        /*!
        This slot connects to the finished(int,QProcess::ExitStatus) signal of the process launched
        with sqlcmd; here we do some "household" tidying up, like removing the temporary file and restablishing the normal cursor.
         \sa readProcessError(), readProcessOutput()
        */
        void                    processFinished();
        void                    finishedReadingNames();
        void                    parseParams();
        void                    finishedCheckingBackupFile();
        void                    parseBackupFileInfo();
        void                    showSqlMessages(bool bShow);
        void                    finishedRestore();

        bool                    onButtonClick(QAbstractButton * button);
        void                    createUserRecord();
        bool                    ApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupBox,
                                  QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                                  QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel);
        void                    onLockControls(bool bLock,QGroupBox* box);
        void                    previewRecord(const QModelIndex index,QDataWidgetMapper* aMapper,QPushButton* aPushNew,
                                    QPushButton* aPushEdit, QPushButton* aPushRemove,QGroupBox* group,QDialogButtonBox* buttons,QSqlTableModel* aModel);
        void                    onEditLeave(const bool bFinished, QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove,QGroupBox* group,QDataWidgetMapper* aMapper,QSqlTableModel* aModel,QDialogButtonBox* buttons,const bool bDiscarded);
        void                    resizeUsersTable(int index);
        void                    adjustUserEnables();
        void                    previewUser(QModelIndex index);
        bool                    editRecord(const bool on,QSqlTableModel* aModel,QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove,QGroupBox* group,QDialogButtonBox* buttons,QDataWidgetMapper* aMapper,
                                    QSqlQueryModel* viewModel, const QString strQuery,QTableView* aTable);
        bool                    editUser(bool on);
        void                    removeUser();

    private:
        //! Init UI
        /*!
        Initializes the UI: toolbars, enables/disables, signals, etc. It is called on the constructor.
        */
        void                    initUI();
        //! Init Models
        /*!
        Initializes city and country models. It is called by fillLocations(), right after we established a connection. to the db
         \sa fillLocations()
        */
        void                    initModels();
        //! Enable Connection Controls
        /*!
        This function adjusts the UI to the new connection status.
         \par bEnable boolean to indicate if we want to enable the controls (true) or not (false)
        */
        void                    enableConnectionCtrls(const bool bEnable);
        //! Load Settings
        /*!
        This function reads the settings from the registry, and uses them to fill the UI default values.
        We divided the settings in two sections:
        - 0 - related to the connection string
        - 1 - related to the regional settings (country, city)
         \par section section of the Settings as integer.
         \sa saveSettings(const int section)
        */
        void                    loadSettings(const int section);
        //! Save Settings
        /*!
        This function reads the values in the UI and saves them in the registry, so 
        we can read them next time, through function loadSettings(const int section).
        We divided the settings in two sections:
        - 0 - related to the connection string
        - 1 - related to the regional settings (country, city)
         \par section section of the Settings as integer.
         \sa loadSettings(const int section)
        */
        void                    saveSettings(const int section);
        //! Fill Locations
        /*!
        This function initializes the city and country models, and uses them to fill the UI.
         \sa initModels()
        */
        bool                    fillLocations();
        //! List Tables
        /*!
        This function makes a direct call to the database to retrieve the list of tables, and uses it
        to fill the tables combobox, on the UI. It is called right after a connection to the db is established.
         */
        bool                    listTables();

        bool                    initUsers();
        void                    UI4NewRecord(QGroupBox* group,QDialogButtonBox* aButtonBox);

        void                    setPreviewQuery(QSqlQueryModel* viewModel, const QString strQuery);
        void                    initPreviewTable(QTableView* aTable, QSqlQueryModel* view);
        bool                    reallyApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupBox,
                                    QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove, QSqlTableModel* aModel);
        bool                    abstractPreviewRow(QModelIndex index,QPushButton* pNew,QPushButton* pEdit,QPushButton* pRem,
                                    QGroupBox* box,QDialogButtonBox* aButtonBox, QSqlTableModel* aModel);

        //! Show Event
        /*!
        Reimplemented from the base class.
         */
        void                              showEvent ( QShowEvent * event );

        void                              resizeEvent ( QResizeEvent * event );
        bool                              runScript(const QString strScript, QStringList& args);
        void                              createProcess();
        QString                           getOutputName(const QString strExt);
        bool                              writeDiff(const QString strFileName);
        void                              genericCreateRecord(QSqlTableModel* aModel);
        bool                              discardNewRecord(QSqlTableModel* aModel);
        void                              removeRecord(QTableView* aTable,QSqlTableModel* aModel,QGroupBox* group,
                                                    QSqlQueryModel* viewModel, const QString strQuery);
        bool                              translateIndex(const QModelIndex inIdx, QTableView* aTable, 
                                                QSqlTableModel* aModel, QModelIndex& outIdx);
        bool                              validate(const QSqlTableModel* aModel);
        void                              createRecord(QSqlTableModel* aModel,QDataWidgetMapper* aMapper, 
                                                QGroupBox* aGroup,QDialogButtonBox* aButtonBox);

        bool                              m_bConnected;//!< Boolean flag to indicate the connection status
        QSqlQueryModel                    *cityModel;//!< Pointer to the city database model (table "Ref_Location")
        QSqlQueryModel                    *countryModel;//!< Pointer to the country database model (table "Ref_Countries")
        QSqlRelationalTableModel          *userModel;//!< Pointer to the user database model (table "UI_User")
        QSqlRelationalTableModel*         tableModel;//!< Pointer to a generic table model (any database table)
        QProcess*                          myProcess;//!< Pointer to a process (sqlcmd)
        QString                            m_databaseLogicalName;
        QString                            m_databasePath;
        QString                            m_logLogicalName;
        QString                            m_logPath;
        QString                            m_strBackupName;
        bool                               m_bShowSqlMessages;

        QSqlQueryModel*                    viewUsers;
        QDataWidgetMapper*                 mapperUsers;
        NullRelationalDelegate*            nullDelegate;
        QModelIndex                        m_lastIndex;
};

#endif // CONF_APP_H
