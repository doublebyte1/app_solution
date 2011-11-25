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

    private slots:
        //! Create Record
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   createRecord();
        //! Preview Row
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   previewRow(QModelIndex index);
        void                                   blockCustomDateCtrls();
        void                                   unblockCustomDateCtrls();

        void                                   setActiveReason(bool bActive);
        void                                   disableReasonCombo();
        //! On item selection
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   onItemSelection();
        //! On Edit Leave
        /*! Reimplemented from the PreviewTab base class
         \par bFinished flag that indicates if we started/finished editing
         \par bDiscarded flag that indicates, in case we finished, if we want to discard changes (default is false)
        /sa previewRow(QModelIndex index), editFinished()
        */
        void                                   onEditLeave(const bool bFinished, const bool bDiscarded);
        //! Edit finished
        /*! Reimplemented from the PreviewTab base class
        /sa previewRow(QModelIndex index), onEditLeave(const bool bFinished, const bool bDiscarded)
        */
        void                                   editFinished();
        //! On Show FrameDetails
        /*! Slot that is called, when FrameDetails Form show event
        */
        void                                   onShowFrameDetails();
        //! On Hide FrameDetails
        /*! Slot that is called, when FrameDetails Form hide event
        */
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
        bool                                   applyChanges();
        //! Set main model query
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   setPreviewQuery();
        //! Filter combo box
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   filterModel4Combo();
        //! Initialize UI for new record
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   uI4NewRecord();
        //! Set Header widget
        /*! Reimplemented from the genericTab base class
        */
        void                                   setHeader(){setLbHead(this->lbHeader);}
        void                                   initModels();
        void                                   initMappers();
        void                                   initUI();
        void                                   beforeShow();

        //! Get the title label of the next form
        /*! Reimplemented from the PreviewTab base class
        */
        bool                                   getNextLabel(QString& strLabel);
        QSqlRelationalTableModel*              tRefMinorStrata;
        QSqlQueryModel*                        viewMinorStrata;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        ButtonGroup*                           buttonGroup;
};
#endif //FRMMINORSTRATA_H