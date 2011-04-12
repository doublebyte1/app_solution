#include <QtGui>
#include <QtSql>
#include "ui_frmminorstrata.h"
#include "generictab.h"
#include "buttongroup.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMMINORSTRATA_H
#define FRMMINORSTRATA_H

//! Frm MinorStrata Class
/*!
This class implements the widget that corresponds to the MinorStrata definition tab
*/

class FrmMinorStrata : public GenericTab, public Ui::frmminorstrata
{
    Q_OBJECT

    public:
        FrmMinorStrata(DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmMinorStrata();

    signals:

    public slots:
        void                                  onShowForm();

    private slots:
        void                                   previewRow(QModelIndex index);
        void                                   setActiveReason(bool bActive);
        void                                   disableReasonCombo();
        void                                   viewRecord();
        void                                   createRecord();
        void                                   onButtonClick(QAbstractButton * button);

    private:
        void                                   resizeToVisibleColumns ( QTableView* table );
        void                                   resizeEvent ( QResizeEvent * event );
        void                                   setMinorStrataQuery();
        void                                   setReadOnly(const bool bRO);
        void                                   setHeader(){setLbHead(this->lbHeader);}
        void                                   initModels();
        void                                   initMappers();
        void                                   initUI();
        bool                                   getDateModel(const int dtField, QSqlQueryModel& model);
        QSqlRelationalTableModel*              tRefMinorStrata;
        QSqlQueryModel*                        viewMinorStrata;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        ButtonGroup*                           buttonGroup;
        NullRelationalDelegate*                nullDellegate;
};
#endif //FRMMINORSTRATA_H