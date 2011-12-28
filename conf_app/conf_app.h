#ifndef CONF_APP_H
#define CONF_APP_H

#include <QtSql>
#include <QtGui/QMainWindow>
#include "ui_conf_app.h"

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
        void                    connectionChanged();
        void                    statusShow(const QString str);

    private slots:
        void                    showTable(const QString strTable);
        void                    applyChanges2Table();
        void                    connectDB();
        void                    disconnectDB();
        void                    onConnectionChange();
        void                    onStatusShow(const QString str);
        void                    filterModel(QString strCountry);
        void                    apply();
        void                    enableApply();
        void                    onShowStartupMsgI(bool bNoShow);
        void                    onShowStartupMsg(const bool bShow);
        void                    insertRow();
        void                    removeRow();

    private:
        void                    initUI();
        void                    initModels();
        void                    enableConnectionCtrls(const bool bEnable);
        void                    loadSettings(const int section);
        void                    saveSettings(const int section);
        bool                    fillLocations();
        bool                    listTables();
        void                    showEvent ( QShowEvent * event );

        QToolBar*                         toolbar;
        bool                              m_bConnected;
        QSqlQueryModel                    *cityModel;
        QSqlQueryModel                    *countryModel;
        QSqlRelationalTableModel*         tableModel;

};

#endif // CONF_APP_H
