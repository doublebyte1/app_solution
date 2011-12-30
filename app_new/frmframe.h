#include <QtGui>
#include <QtSql>
#include "ui_frmframe.h"
#include "previewtab.h"
#include "frmsampling.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

class FrmSampling;

//////////////////////////////////////////////////////////////////////
#ifndef FRMFRAME_H
#define FRMFRAME_H

//! Frm Frame Class
/*!
This class implements the widget that corresponds to the frame definition tab
*/

class FrmFrame : public PreviewTab, public Ui::frmframe
{
    Q_OBJECT

    public:
        FrmFrame(RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr=0, QWidget *parent=0, Qt::WFlags flags=0);
        ~FrmFrame();

    public slots:
        void                                   blockCustomDateCtrls();
        void                                   unblockCustomDateCtrls();

    private slots:
        //! Edit finished
        /*! Reimplemented from the PreviewTab base class
        \sa previewRow(QModelIndex index), onEditLeave(const bool bFinished, const bool bDiscarded)
        */
        void                                   editFinished();
        //! On Hide FrameDetails
        /*! Slot that is called, when FrameDetails Form hide event
        */
        void                                   onHideFrameDetails();
        //! On Show FrameDetails
        /*! Slot that is called, when FrameDetails Form show event
        */
        void                                   onShowFrameDetails();

        void                                   adjustFrmSamplingMode();
        void                                   onHideFrmSampling(bool bSubmitted);
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
        //! On Edit Leave
        /*! Reimplemented from the PreviewTab base class
         \par bFinished flag that indicates if we started/finished editing
         \par bDiscarded flag that indicates, in case we finished, if we want to discard changes (default is false)
        \sa previewRow(QModelIndex index), editFinished()
        */
        void                                   onEditLeave(const bool bFinished, const bool bDiscarded);

    signals:
        void                                   isLogBook(bool bLogBook);
        void                                   submitted(int index, bool bOk);
        void                                   setFrmSamplingMode(const FrmSampling::MODE mode);
        void                                   applyChanges2FrmSampling(const bool bApply);

    private:
        bool                                   updateFrameSample();
        bool                                   updateFrameSample(const QModelIndex index);
        bool                                   updateFrameSampleParts();
        bool                                   updateFrameSampleParts(const QModelIndex index);

        bool                                   isLogBook(const int frameId, bool& bLogbook);
        //! Set main model query
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   setPreviewQuery();
        //! Filter combo box
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   filterModel4Combo(){;}/**< Here it does nothing! */
        //! Initialize UI for new record
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   uI4NewRecord();
        //! Set Header widget
        /*! Reimplemented from the genericTab base class
        */
        void                                   setHeader(){setLbHead(this->lbHeader);}
        //! Initializations before calling the onShow PreviewTab function
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   beforeShow();
        //! Get the title label of the next form
        /*! Reimplemented from the PreviewTab base class
        */
        bool                                   getNextLabel(QString& strLabel);
        //! Apply Changes
        /*! Reimplemented from the PreviewTab base class; this is where we effectively apply the edits, after confirming through a dialog;
        */
        bool                                   applyChanges();

        //! Really Apply
        /*! Reimplemented from the GenericTab base class; this is where we effectively apply the changes, after successfully
        bypassing the binder validation;
        */
        bool                                   reallyApply();
        void                                   setReadOnly(const bool bRO);
        void                                   initModels();
        void                                   initFrModel();
        void                                   initMappers();
        void                                   initMapper2();
        //! Init UI
        /*! Reimplemented from the genericTab base class
        */
        void                                   initUI();
        QSqlQueryModel*                        viewFrameTime;
        QSqlRelationalTableModel*              tFrameTime;
        QSqlTableModel*                        frModel;
        QDataWidgetMapper*                     mapper;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        FrmFrameDetails::Mode                  m_curMode;
        bool                                   m_submitted;/**< flag to define if the record was finalised and successfully submitted */
        bool                                   m_bSampling;/**< flag to define if the sampling process definition is ongoing */
        bool                                   m_tabsDefined;
        bool                                   m_bInsert;
};
#endif //FRMFRAME_H