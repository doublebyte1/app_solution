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
        FrmFrame(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr=0, QWidget *parent=0, Qt::WFlags flags=0);
        ~FrmFrame();

    public slots:
        void                                   blockCustomDateCtrls();
        void                                   unblockCustomDateCtrls();

    private slots:
        void                                   onAppliedChanges2FrmSampling();
        void                                   adjustFrmSamplingMode();

//        bool                                   updateSample();
//        bool                                   updateSample(const QModelIndex& idx);

        void                                   onHideFrameDetails();
        void                                   onShowFrameDetails();

        void                                   onHideFrmSampling(bool bSubmitted);

        void                                   createRecord();
        void                                   previewRow(QModelIndex index);
        void                                   onItemSelection();
        void                                   onEditLeave(const bool bFinished, const bool bDiscarded);

    signals:
        void                                   isLogBook(bool bLogBook);
        void                                   submitted(int index, bool bOk);
        void                                   setFrmSamplingMode(const FrmSampling::MODE mode);
        void                                   applyChanges2FrmSampling(const bool bApply);

    protected:
        void                                   showEvent ( QShowEvent * event );

    private:

        bool                                   updateFrameSample();
        bool                                   updateFrameSample(const QModelIndex index);
        bool                                   updateFrameSampleParts();
        bool                                   updateFrameSampleParts(const QModelIndex index);

        bool                                   isLogBook(const int frameId, bool& bLogbook);
        void                                   setPreviewQuery();
        void                                   filterModel4Combo(){;}
        void                                   uI4NewRecord();
        void                                   setHeader(){setLbHead(this->lbHeader);}
        void                                   beforeShow();
        bool                                   getNextLabel(QString& strLabel);
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
        void                                   initUI();

        QSqlQueryModel*                        viewFrameTime;
        QSqlRelationalTableModel*              tFrameTime;
        QSqlTableModel*                        frModel;
        QDataWidgetMapper*                     mapper;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        FrmFrameDetails::Mode                  m_curMode;
        bool                                   m_submitted;;/**< flag to define if the record was finalised and successfully submitted */
        bool                                   m_bSampling;;/**< flag to define if the sampling process definition is ongoing */
        bool                                   m_tabsDefined;
        bool                                   m_bInsert;
};
#endif //FRMFRAME_H