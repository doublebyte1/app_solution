#include <QtGui>
#include <QtSql>
#include "ui_frmcell.h"
#include "previewtab.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMCELL_H
#define FRMCELL_H

//! Frm Cell Class
/*!
This class implements the widget that corresponds to the Sampled Cell definition tab; This tab is only
applicable to sampling type frames;
*/

class FrmCell : public PreviewTab, public Ui::frmCell
{
    Q_OBJECT

    public:
        FrmCell(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr=0, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmCell();

    signals:

    private slots:
        //! Create Record
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   createRecord();
        //! Preview Row
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   previewRow(QModelIndex index);
        //! On item selection
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   onItemSelection();
        void                                   blockCustomDateCtrls();
        void                                   unblockCustomDateCtrls();
        //! Edit finished
        /*! Reimplemented from the PreviewTab base class
        /sa previewRow(QModelIndex index), onEditLeave(const bool bFinished, const bool bDiscarded)
        */
        void                                   editFinished();
        //! On Edit Leave
        /*! Reimplemented from the PreviewTab base class
         \par bFinished flag that indicates if we started/finished editing
         \par bDiscarded flag that indicates, in case we finished, if we want to discard changes (default is false)
        /sa previewRow(QModelIndex index), editFinished()
        */
        void                                   onEditLeave(const bool bFinished, const bool bDiscarded);
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
        //! Filter combo box
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   filterModel4Combo();
        //! Set main model query
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   setPreviewQuery();
        //! Initialize UI for new record
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   uI4NewRecord();
        //! Initializations before calling the onShow PreviewTab function
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   beforeShow();
        //! Set Header widget
        /*! Reimplemented from the genericTab base class
        */
        void                                   setHeader(){setLbHead(this->lbHeader);}
        //! Init Models
        /*! Reimplemented from the genericTab base class
        */
        void                                   initModels();
        //! Init Mappers
        /*! Reimplemented from the genericTab base class
        */
        void                                   initMappers();
        //! Init UI
        /*! Reimplemented from the genericTab base class
        */
        void                                   initUI();
        //! Get the title label of the next form
        /*! Reimplemented from the PreviewTab base class
        */
        bool                                   getNextLabel(QString& strLabel);
        void                                   initCellModel();
        void                                   initMapper1();

        QSqlRelationalTableModel*              tSampCell;
        QSqlQueryModel*                        viewCell;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
};
#endif //FRMCELL_H