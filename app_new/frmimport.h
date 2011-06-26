#ifndef FRMIMPORT_H
#define FRMIMPORT_H

#include <QtGui>
#include <QtSql>
#include "ui_frmTables.h"
//#include "customform.h"
#include "fieldlistmodel.h"
#include <boost/shared_ptr.hpp>

#if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

using namespace boost;

//! Import Tables Class
/*!
//TODO: add a description here later
*/

class FrmImport : public QWidget, public Ui::frmTables
{
//! Typedef for a shared pointer, containing an abstract table format
typedef shared_ptr<AbstractFormat>                        formatPtr;

    Q_OBJECT

    public:
        FrmImport(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmImport();

    signals:
        void                        hideFrm();
        void                        rollbackImport();
        void                        showStatus(QString str);
        void                        showError(QString str, const bool bShowMsgBox=true);

    private:
        bool                        loadTable();
        bool                        loadFields();
        QSqlTableModel*             tableModel;
        FieldListModel*             fieldModel;
        bool                        initFactory();
        QList<formatPtr>            m_listFormats;
        QString                     m_fileName;

    private slots:
        bool        readTableNames(){return false;}//This slot is not implemented in this class!
        bool        readTableNames(AbstractTableFormat* aFormat);
        void        hideAppend(bool bHide);
        void        Ok();
        void        Cancel();
        void        preview(QListWidgetItem* item);
        void        preview();
        void        chooseFile();
};
#endif // FRMIMPORT_H
