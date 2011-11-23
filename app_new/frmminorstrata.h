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
        FrmMinorStrata(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr=0, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmMinorStrata();

    public slots:

    private slots:
        void                                   createRecord();
        void                                   previewRow(QModelIndex index);
        void                                   blockCustomDateCtrls();
        void                                   unblockCustomDateCtrls();

        void                                   setActiveReason(bool bActive);
        void                                   disableReasonCombo();
        void                                   onItemSelection();

        void                                   onEditLeave(const bool bFinished, const bool bDiscarded);
        void                                   editFinished();

        void                                   onShowFrameDetails();
        void                                   onHideFrameDetails();

    private:
        //! Really Apply
        /*! Reimplemented from the GenericTab base class; this is where we effectively apply the changes, after successfully
        bypassing the binder validation;
        */
        bool                                   reallyApply();
        //! Apply Changes
        /*! Reimplemented from the PreviewTab base class; this is where we effectively apply the edits, after confirming through a dialog;
        */
        bool                                   applyChanges();//TODO: implement this!
        void                                   setPreviewQuery();
        void                                   filterModel4Combo();
        void                                   uI4NewRecord();
        void                                   setHeader(){setLbHead(this->lbHeader);}
        void                                   initModels();
        void                                   initMappers();
        void                                   initUI();
        void                                   beforeShow();

        //! Get the title label of the next form
        /*! Reimplemented from the PreviewTab base class
        */
        bool                                   getNextLabel(QString& strLabel);
        //! Update the sample structure
        /*! Reimplemented from the PreviewTab base class
        */
        //bool                                   updateSample();

        QSqlRelationalTableModel*              tRefMinorStrata;
        QSqlQueryModel*                        viewMinorStrata;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        ButtonGroup*                           buttonGroup;
};
#endif //FRMMINORSTRATA_H