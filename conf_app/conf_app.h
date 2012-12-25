#ifndef CONF_APP_H
#define CONF_APP_H

#include <QtSql>
#include <QtGui>
#include "ui_conf_app.h"
#include "nullrelationaldelegate.h"
#include "booleantable.h"
#include "genericsortproxymodel.h"
//#include "frmlu.h"
#include "sql.h"

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

    enum DBMode { MASTER=1, CLIENT=2, INVALID=-1 };

    signals:
        void                    connectionChanged();//!< Signal to indicate that the connection state changed (connected or disconnected)
        void                    statusShow(const QString str);//!< Signal indicating we want to display a message on the toolbar
        void                    submit(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
                                            QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                                            QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable);
        void                    lockControls(bool bLock,QGroupBox* aGroupDetails);/**< signal to lock/unlock a list of controls */
        void                    editLeave(const bool bFinished,QPushButton* aPushEdit,QPushButton* aPushNew,
                                   QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDataWidgetMapper* aMapper,QSqlTableModel* aModel,
                                   QDialogButtonBox* aButtonBox,QSqlQueryModel* viewModel,
                                   const QString strQuery, QTableView* aTable,const bool bDiscarded=false);/**< signal emitted after finishing the editing process*/

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
        //! Do Dump
        /*!
        This slot writes a database patch (.diff), based on the log table "info_changes"; 
        the patch itself is a text file, written in JSON format (http://www.json.org/)
         \sa doPatch()
        */
        bool                    doDump(const int lu, const QString strMacAddress);
        //! Do Patch
        /*!
        TODO: write something here later!!
         \sa doDump()
        */
        //bool                    continueDump(const int lu, const QString strMacAddress);
        void                    doPatch();
        bool                    doApply(int& lu_master, QString& strMacAddress);
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

        //! On button click (Users)
        /*!
        This is the entry point for the generic onButtonClick, on the context of the user tab. Its only
        argument is the clicked button, as we pass everything else (user's specific controls and 
        data) to the subsequent function.
        \par button clicked button (apply or close);
         \sa onRoleButtonClick(QAbstractButton* button),onButtonClick(QAbstractButton* button,QDialogButtonBox* aButtonBox,QDataWidgetMapper* aMapper, QGroupBox* aGroupDetails,
                                    QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                                    QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable)
        */
        bool                    onUserButtonClick(QAbstractButton* button);
        //! On button click (Role)
        /*!
        This is the entry point for the generic onButtonClick, on the context of the role tab. Its only
        argument is the clicked button, as we pass everything else (role's specific controls and 
        data) to the subsequent function.
        \par button clicked button (apply or close);
         \sa onUserButtonClick(QAbstractButton* button),onButtonClick(QAbstractButton* button,QDialogButtonBox* aButtonBox,QDataWidgetMapper* aMapper, QGroupBox* aGroupDetails,
                                    QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                                    QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable)
        */
        bool                    onRoleButtonClick(QAbstractButton* button);
        //! Create Record (User)
        /*!
        This is the entry point for the generic createRecord, on the context of the user tab. It does not have any arguments
        as we pass everything (user's specific controls and 
        data) to the subsequent function.
        \par button clicked button (apply or close);
         \sa createRoleRecord(), createRecord(QSqlTableModel* aModel,QDataWidgetMapper* aMapper, 
                QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox, QPushButton* aPushEdit,QPushButton* aPushRemove)
        */
        void                    createUserRecord();
        //! Create Record (Role)
        /*!
        This is the entry point for the generic createRecord, on the context of the role tab. It does not have any arguments
        as we pass everything (user's specific controls and 
        data) to the subsequent function.
        \par button clicked button (apply or close);
         \sa createUserRecord(), createRecord(QSqlTableModel* aModel,QDataWidgetMapper* aMapper, 
                QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox, QPushButton* aPushEdit,QPushButton* aPushRemove)
        */
        void                    createRoleRecord();
        //! Apply Model
        /*!
        This slot is a response to the submit signal and it introduces the validation layer, 
        redirecting (or not) the flow to reallyApplyModel, where we actually perform the comit
        to the database.
        \par aMapper mapper of the form;
        \par aButtonBox close & apply buttons;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par viewModel read-only model that supports the preview on the tableview (normally only shows name and another property);
        \par strQuery query string to build the viewModel;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushNew pushbutton to create new record;
        \par aPushRemove pushbutton to indicate the removal of a record;
        \par aModel model behind the mapper;
        \par tableView preview table;
        \sa reallyApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
                                    QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable),submit(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
                                            QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
        */
        bool                    ApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
                                  QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                                  QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable);
        //! On Lock Controls
        /*!
        This slot is a response to the lockControls signal it enables/disables the controls on the preview tab.
        \par bLock boolean to indicate if we want to block (disable) or unblock (enable) the controls;
        \par aGroupDetails target groupbox;
        \sa lockControls(bool bLock,QGroupBox* aGroupDetails)
*/
        void                    onLockControls(bool bLock,QGroupBox* aGroupDetails);
        //! Resize Tables
        /*!
        This slot automatically resizes the contents of the user and role tables, with a form resize 
        \par int index of the tab we are in;
*/
        void                    resizeTables(int index);
        //! Adjust User Enables
        /*!
        This an entry point for the generic adjustUserEnables function. This function provides the necessary
        context (controls, data) for the user tab.
        \sa adjustEnables(QPushButon* aPushEdit,QPushButon* aPushRemove,QSqlTableModel* aModel),adjustRoleEnables()
*/
        void                    adjustUserEnables();
        //! Adjust Role Enables
        /*!
        This an entry point for the generic adjustUserEnables function. This function provides the necessary
        context (controls, data) for the role tab.
        \sa adjustEnables(QPushButon* aPushEdit,QPushButon* aPushRemove,QSqlTableModel* aModel),adjustUserEnables()
*/
        void                    adjustRoleEnables();
        //! Preview User
        /*!
        This an entry point for the generic previewRecord function. This function provides the necessary
        context (controls, data) for the user tab.
        \sa previewRole(QModelIndex index),previewRecord(const QModelIndex index,QDataWidgetMapper* aMapper,QPushButton* aPushNew,
                                            QPushButton* aPushEdit, QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QSqlTableModel* aModel,
                                            QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable)
*/
        void                    previewUser(QModelIndex index);
        //! Preview Role
        /*!
        This an entry point for the generic previewRecord function. This function provides the necessary
        context (controls, data) for the role tab.
        \sa previewUser(QModelIndex index),previewRecord(const QModelIndex index,QDataWidgetMapper* aMapper,QPushButton* aPushNew,
                                            QPushButton* aPushEdit, QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QSqlTableModel* aModel,
                                            QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable)
*/
        void                    previewRole(QModelIndex index);
        //! Edit User
        /*!
        This an entry point for the generic editRecord function. This function provides the necessary
        context (controls, data) for the user tab.
        \sa editRole(bool on), editRecord(const bool on,QSqlTableModel* aModel,QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QDataWidgetMapper* aMapper,
                                    QSqlQueryModel* viewModel, const QString strQuery,QTableView* aTable);

*/
        bool                    editUser(bool on);
        //! Edit Role
        /*!
        This an entry point for the generic editRecord function. This function provides the necessary
        context (controls, data) for the role tab.
        \sa editUser(bool on), editRecord(const bool on,QSqlTableModel* aModel,QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QDataWidgetMapper* aMapper,
                                    QSqlQueryModel* viewModel, const QString strQuery,QTableView* aTable);

*/
        bool                    editRole(bool on);
        //! On Edit Leave
        /*!
        This slot connects to the editLeave signal, and implements the changes in the UI that
        reflect the end of an edition.
        \par bFinished boolean to indicate if the edition process has been terminated (true) or initiated (false);
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushNew pushbutton to create new record;
        \par aPushRemove pushbutton to indicate the removal of a record;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par aMapper mapper of the form;
        \par aModel model behind the mapper;
        \par aButtonBox close & apply buttons;
        \par viewModel read-only model that supports the preview on the tableview (normally only shows name and another property);
        \par strQuery query string to build the viewModel;
        \par tableView preview table;
        \par bDiscarded boolean to indicate if the edition process has been discarded;
        \sa editLeave(const bool bFinished,QPushButton* aPushEdit,QPushButton* aPushNew,
               QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDataWidgetMapper* aMapper,QSqlTableModel* aModel,
               QDialogButtonBox* aButtonBox,QSqlQueryModel* viewModel,
               const QString strQuery, QTableView* aTable,const bool bDiscarded=false)
       */
        void                    onEditLeave(const bool bFinished, QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDataWidgetMapper* aMapper,QSqlTableModel* aModel,QDialogButtonBox* aButtonBox,
                                    QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable, const bool bDiscarded);
        //! Remove User
        /*!
        Slot that removes a user record from the db;
        \sa removeRole()
*/
        void                    removeUser();
        //! Remove Role
        /*!
        Slot that removes a role record from the db;
        \sa removeUser()
*/
        void                    removeRole();

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
        //! Init Users
        /*!
        This function establishes the bindings between the UI and the DB, on the users tab.
        It basically connects the tableview with a query model, and associates a mapper with the controls.
        \sa initRoles()
         */
        bool                    initUsers();
        //! Init Roles
        /*!
        This function establishes the bindings between the UI and the DB, on the role tab.
        It basically connects the tableview with a query model, and associates a mapper with the controls.
        \sa initUsers()
         */
        bool                    initRoles();
        //! UI for New Record
        /*!
        Function that initializes the UI associated with a new record in the managing tab (cleans lineboxes, etc).
        \par aGroupDetails groupbox with the preview
        \par aButtonBox close & apply buttons
         */
        void                    UI4NewRecord(QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox);
        //! Set Preview query
        /*!
        This functions sets a model query based on an SQL string.
        \par viewModel query model that we want to update;
        \par strQuery select query as SQL string
         */
        void                    setPreviewQuery(QSqlQueryModel* viewModel, const QString strQuery);
        //! Init Preview Table
        /*!
        This functions Initializes the QTableView that previews the model.
        \par aTable preview table;
        \par view read-only query model;
         */
        void                    initPreviewTable(QTableView* aTable, QSqlQueryModel* view);
        //! ReallyApply Model
        /*!
        This is the function that actually comits the changes to the mapper and to the model, inputting
        the results into the database. It normally follows ApplyModel, after successfully bypassing
        the validation.
        \par aMapper mapper of the form;
        \par aButtonBox close & apply buttons;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par viewModel read-only model that supports the preview on the tableview (normally only shows name and another property);
        \par strQuery query string to build the viewModel;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushNew pushbutton to create new record;
        \par aPushRemove pushbutton to indicate the removal of a record;
        \par aModel model behind the mapper;
        \par tableView preview table;
        \sa reallyApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
                QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,QPushButton* aPushNew,
                QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable);
         */
        bool                    reallyApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
                                    QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable);
        //! Abstract Preview Row
        /*!
        This function is called by the generic previewRecord, and it previews a row, that was selected
        by the user on the tableview. It makes some changes on the UI (enables/disables), checks if the
        record was discarded, and finally sets a filter in the model for the given record.
        \index selected model index;
        \par aMapper mapper of the form;
        \par aPushNew pushbutton to create new record;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushRemove pushbutton to indicate the removal of a record;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par aButtonBox close & apply buttons;
        \par aModel model behind the mapper;
        \par viewModel read-only model that supports the preview on the tableview (normally only shows name and another property);
        \par strQuery query string to build the viewModel;
        \par tableView preview table;
        \sa previewRecord(const QModelIndex index,QDataWidgetMapper* aMapper,QPushButton* aPushNew,
                QPushButton* aPushEdit, QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QSqlTableModel* aModel,
                QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable);
*/
        bool                    abstractPreviewRow(QModelIndex index,QPushButton* aPushNew,QPushButton* aPushEdit,QPushButton* aPushRemove,
                                      QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox, QSqlTableModel* aModel,
                                      QDataWidgetMapper* aMapper, QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable);
        //! Edit Record
        /*!
        This is the triggered function when we toggle the edit mode, over a record.
        First it analyses if we are entering or leaving an edit; if we are leaving, it prompts
        the user to save changes; finally it modifies the UI according to the state, result.
        \par aModel model behind the mapper;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushNew pushbutton to create new record;
        \par aPushRemove pushbutton to indicate the removal of a record;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par aButtonBox close & apply buttons;
        \par aMapper mapper of the form;
        \par viewModel read-only model that supports the preview on the tableview (normally only shows name and another property);
        \par strQuery query string to build the viewModel;
        \par tableView preview table;
        \sa editUser(bool on),editRole(bool on)
*/
        bool                    editRecord(const bool on,QSqlTableModel* aModel,QPushButton* aPushEdit,QPushButton* aPushNew,
                                    QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QDataWidgetMapper* aMapper,
                                    QSqlQueryModel* viewModel, const QString strQuery,QTableView* aTable);
        //! On button click
        /*!
        Here we perform the actions specific to the chosen button; "close" closes the preview form
        and apply submits the changes to the underlying model.
        \par button clicked button (apply or close);
        \par aButtonBox close & apply buttons;
        \par aMapper mapper of the form;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par viewModel read-only model that supports the preview on the tableview (normally only shows name and another property);
        \par strQuery query string to build the viewModel;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushNew pushbutton to create new record;
        \par aPushRemove pushbutton to indicate the removal of a record;
        \par aModel model behind the mapper;
        \par tableView preview table;
        \sa onUserButtonClick(QAbstractButton* button),onRoleButtonClick(QAbstractButton* button)
*/
        bool                    onButtonClick(QAbstractButton* button,QDialogButtonBox* aButtonBox,QDataWidgetMapper* aMapper, QGroupBox* aGroupDetails,
                                    QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
                                    QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable);
        //! Show Event
        /*!
        Reimplemented from the base class.
         */
        void                              showEvent ( QShowEvent * event );
        void                              resizeEvent ( QResizeEvent * event );
        bool                              runScript(const QString strScript, QStringList& args);
        void                              createProcess();
        QString                           getOutputName(const QString strExt);
        bool                              writeDiff(const QString strFileName, const int lu,
            const QString strMacAddress, QString& strError);
        //! Generic Create Record
        /*!
        Generic function to create a new record (applied to roles and users). It is called by createRecord.
        \par aModel table model;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushRemove pushbutton to indicate the removal of a record;
        \sa createRecord(QSqlTableModel* aModel,QDataWidgetMapper* aMapper, 
                QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox, QPushButton* aPushEdit,QPushButton* aPushRemove);
*/
        bool                              genericCreateRecord(QSqlTableModel* aModel,QPushButton* aPushEdit,
                                                QPushButton* aPushRemove);
        //! Discard New Record
        /*!
        This function allows to discard changes, on a record that was being created/edited.
        \par aModel table model;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
*/
        bool                              discardNewRecord(QSqlTableModel* aModel,QPushButton* aPushEdit);
        //! Remove Record
        /*!
        This is the generic function that deletes a record from the database. It is generally called
        from removeUser() or removeRole().
        \par aModel table model;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par viewModel read-only model that supports the preview on the tableview (normally only shows name and another property);
        \par strQuery query string to build the viewModel;
        \par col index of the field that contains the ID (to translate the index from the view to the model);
        \sa removeUser(), removeRole()
*/
        void                              removeRecord(QTableView* aTable,QSqlTableModel* aModel,QGroupBox* aGroupDetails,
                                                    QSqlQueryModel* viewModel, const QString strQuery, const int col);
        //! Translate Index
        /*!
        This function translates a index on the preview view, on an index in the table model.
        \par inIdx input index from the query view;
        \par col index of the field that contains the ID;
        \par aTable preview table;
        \par aModel table model;
        \par outIdx output index (index on the model)
*/
        bool                              translateIndex(const QModelIndex inIdx, const int col, QTableView* aTable, 
                                                QSqlTableModel* aModel, QModelIndex& outIdx);
        //! Validate
        /*!
        Function that validates the UI, looking for empty controls, etc; it has a part related to the role UI
        and another part related to the User UI. It is generally called from the applyModel.
        \par aModel table model;
        \sa ApplyModel(QDataWidgetMapper* aMapper, QDialogButtonBox* aButtonBox, QGroupBox* aGroupDetails,
              QSqlQueryModel* viewModel, const QString strQuery, QPushButton* aPushEdit,
              QPushButton* aPushNew, QPushButton* aPushRemove, QSqlTableModel* aModel,QTableView* aTable);
*/
        bool                              validate(const QSqlTableModel* aModel);
        //! Create Record
        /*!
        Interface for the function genericCreateRecord, that also applies some changes to the UI.
        \par aModel table model;
        \par aMapper mapper of the form;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par aButtonBox close & apply buttons;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushRemove pushbutton to indicate the removal of a record;
        \sa genericCreateRecord(QSqlTableModel* aModel,QPushButton* aPushEdit,
                                                QPushButton* aPushRemove)
*/
        void                              createRecord(QSqlTableModel* aModel,QDataWidgetMapper* aMapper, 
                                                QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox, QPushButton* aPushEdit,QPushButton* aPushRemove);
        //! Adjust Enables
        /*!
        This convenience functions, disables the pushEdit and pushRemove buttons on the managing tab. 
        Since they should not active when there are no records, it is connected to the rowsInserted( const QModelIndex, int, int)
        and rowsRemoved( const QModelIndex, int, int) signals, that indicate changes in the model.
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushRemove pushbutton to indicate the removal of a record;
        \par aModel table model;
        /sa adjustUserEnables(), adjustRoleEnables()
*/
        void                              adjustEnables(QPushButton* aPushEdit,QPushButton* aPushRemove,QSqlTableModel* aModel);
        //! Preview Record
        /*!
        Previews the select record by displaying it in the preview tab in preview mode (disabled controls).
        \par index model index of the record we want to preview;
        \par aMapper mapper of the form;
        \par aPushNew pushbutton to create new record;
        \par aPushEdit pushbutton to trigger edit mode (toggle);
        \par aPushRemove pushbutton to indicate the removal of a record;
        \par aGroupDetails form with preview of the record, that can also be use for edit/new;
        \par aButtonBox close & apply buttons;
        \par aModel model behind the mapper;
        \par viewModel read-only model that supports the preview on the tableview (normally only shows name and another property);
        \par strQuery query string to build the viewModel;
        \par tableView preview table;
        \sa previewUser(), previewRole()
*/
        void                              previewRecord(const QModelIndex index,QDataWidgetMapper* aMapper,QPushButton* aPushNew,
                                            QPushButton* aPushEdit, QPushButton* aPushRemove,QGroupBox* aGroupDetails,QDialogButtonBox* aButtonBox,QSqlTableModel* aModel,
                                            QSqlQueryModel* viewModel, const QString strQuery, QTableView* aTable);
        bool                              readFile(const QString strFileName, QString& outStr);
        bool                              readChangesfromPatch(const QString strContent, QString& strDateUTC, QString& strDateLocal,
                                                    int& dateType, QString& strCityName, QString& strMacAddress, QString& strUser, int& lu_master, listInfoChanges& lChanges, 
                                                    QList<QVariant>& mapReferences, QString& strError);
        bool                              applyChangesfromPatch(const QList<QVariant>& mapReferences, listInfoChanges& lChanges, const int lu_master,
                                                                    int& cnew, int& cmod, int& cdel, QString& strError);
        bool                              readAndApplyChangesfromPatch(const QString strContent, int& ctNew, int& ctMod, int& ctDel, QString& strError);
        bool                              insertNewRecord(const listInfoChanges& lChanges);
        bool                              insertDate(const InfoDate date, int& id);
        bool                              amendDate(const int ID, const QString strField, const QString strDate);
        bool                              packRecord(const QList<QVariant>& mapReferences, listInfoChanges& lChanges, int& i, 
                                            listInfoChanges& aRecord, bool& bBreak, QString& strError);
        bool                              removeRecord(const listInfoChanges& packRecord);
        bool                              modRecord(const InfoChanges& chRec, const int id);
        bool                              identifyRecord(const listInfoChanges& packRecord, int& outID);
        bool                              modDateRecord(const listInfoChanges& aRecord, const listInfoChanges& iDt);
        bool                              identifyRecordByDate(const listInfoChanges& aRecord,
                                                                 const listInfoChanges& dtRecs, const listInfoChanges& iDt,
                                                                 listInfoChanges& lcopy, int & outID, QString& modField, bool& bFound);
        bool                              findDateID(const QString strTable, const QString strField, const int inID, int &outID);
        bool                              startPatchSession(const QString strDateUTC, const QString strDateLocal,
                                                                const int dateType, const QString strCityName, const QString strMacAddress, const QString strUser);
        bool                              identifyReference(const QList<QVariant>& mapReferences, const QString strRef,
                                                              QVariant& outV, QString& strError);
        bool                               findJSONReference(const QList<QVariant>& mapReferences, const int ID, 
                                                    QVariantMap& map, QString& strTable, QString& strError);
        bool                               findDBReference(const QList<QVariant>& mapReferences,const QString strTable, QVariantMap map,
                                                    QVariant& outID, QString& strError);

        bool                              m_bConnected;//!< Boolean flag to indicate the connection status
        QSqlQueryModel                    *cityModel;//!< Pointer to the city database model (table "Ref_Location")
        QSqlQueryModel                    *countryModel;//!< Pointer to the country database model (table "Ref_Countries")
        QSqlRelationalTableModel          *userModel;//!< Pointer to the user database model (table "UI_User")
        QSqlTableModel                    *roleModel;//!< Pointer to the role database model (table "UI_Role")
        QSqlRelationalTableModel*         tableModel;//!< Pointer to a generic table model (any database table)
        QProcess*                          myProcess;//!< Pointer to a process (sqlcmd)
        QString                            m_databaseLogicalName;
        QString                            m_databasePath;
        QString                            m_logLogicalName;
        QString                            m_logPath;
        QString                            m_strBackupName;
        bool                               m_bShowSqlMessages;
        DBMode                             m_dbmode;

        QSqlQueryModel*                    viewUsers;
        QSqlQueryModel*                    viewRoles;
        QDataWidgetMapper*                 mapperUsers;
        QDataWidgetMapper*                 mapperRoles;
        NullRelationalDelegate*            nullDelegateUsers;
        NullRelationalDelegate*            nullDelegateRoles;
        QModelIndex                        m_lastIndex;//!< variable that stores the last clicked index
};

#endif // CONF_APP_H
