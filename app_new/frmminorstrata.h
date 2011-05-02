#include <QtGui>
#include <QtSql>
#include "ui_frmminorstrata.h"
#include "previewtab.h"
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

class FrmMinorStrata : public PreviewTab, public Ui::frmminorstrata
{
    Q_OBJECT

    public:
        FrmMinorStrata(Sample* inSample, DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmMinorStrata();

    public slots:
        void                                  onShowForm();

    private slots:
        void                                   next();
        void                                   createRecord();
        void                                   previewRow(QModelIndex index);
        bool                                   onButtonClick(QAbstractButton * button);

        void                                   setActiveReason(bool bActive);
        void                                   disableReasonCombo();

    private:
        void                                   setPreviewQuery();
        void                                   filterModel4Combo();
        void                                   uI4NewRecord();
        void                                   setHeader(){setLbHead(this->lbHeader);}

        void                                   initModels();
        void                                   initMappers();
        void                                   initUI();

        QSqlRelationalTableModel*              tRefMinorStrata;
        QSqlQueryModel*                        viewMinorStrata;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        ButtonGroup*                           buttonGroup;
        //QModelIndex                            m_selectedIdx;
};
#endif //FRMMINORSTRATA_H