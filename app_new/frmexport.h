#ifndef FRMEXPORT_H
#define FRMEXPORT_H

#include <QtGui>
#include <QtSql>
#include "ui_frmTables.h"
#include "generictab.h"
#include "fieldlistmodel.h"
#include <boost/shared_ptr.hpp>

#if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

using namespace boost;

class SecondaryFrm;

//! Export Tables Class
/*!
This form derives from the form tables class and it has a list of tables and a preview;
The list of tables is loaded from the database; The purpose of this UI is to allow user to
select which tables to export.
*/

class FrmExport : public SecondaryFrm, public Ui::frmTables
{
//! Typedef for a shared pointer, containing an abstract table format
typedef shared_ptr<AbstractFormat>                        formatPtr;

    Q_OBJECT

    public:
        FrmExport(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmExport();

    private:
        bool                        loadTable();
        bool                        loadFields();
        QSqlTableModel*             tableModel;
        FieldListModel*             fieldModel;
        bool                        initFactory();
        QList<formatPtr>            m_listFormats;

    private slots:
        void        loadItem(QListWidgetItem* item);
        void        Ok();
        void        Cancel();
        void        preview(QListWidgetItem* item);
        void        preview();
        void        chooseFile(){;}//!< This function is not implemented for this class
        void        hideAppend(bool bHide){(void)bHide;}//!< This function is not implemented for this class
        bool        readTableNames();
};
#endif // FrmExport_H
