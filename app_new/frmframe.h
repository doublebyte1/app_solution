#include <QtGui>
#include <QtSql>
#include "ui_frmframe.h"
#include "previewtab.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

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

        bool                                   loadFrameFromSample();

    public slots:
        //bool                                   next();
        void                                   blockCustomDateCtrls();
        void                                   unblockCustomDateCtrls();

    private slots:
        void                                   onHideFrameDetails();
        void                                   onShowFrameDetails();

        void                                   createRecord();
        void                                   editRecord(bool on);
        void                                   previewRow(QModelIndex index);
        void                                   onItemSelection();

    signals:
        void                                   isLogBook(bool bLogBook);
        void                                   submitted(int index, bool bOk);

    protected:
        void                                   showEvent ( QShowEvent * event );

    private:
        bool                                   isLogBook(const int frameId, bool& bLogbook);
        void                                   setPreviewQuery();
        void                                   filterModel4Combo(){;}
        void                                   uI4NewRecord();
        void                                   setHeader(){setLbHead(this->lbHeader);}
        void                                   beforeShow();
        bool                                   getNextLabel(QString& strLabel);

        //! Really Apply
        /*! Reimplemented from the GenericTab base class; this is where we effectively apply the changes, after successfully
        bypassing the binder validation;
        */
        bool                                   reallyApply();
        void                                   setReadOnly(const bool bRO);
        bool                                   updateSample();
        void                                   initModels();
        void                                   initMappers();
        void                                   initUI();

        QSqlQueryModel*                        viewFrameTime;
        QSqlRelationalTableModel*              tFrameTime;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapper2;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        FrmFrameDetails::Mode                  m_curMode;
        bool                                   m_submitted;
        bool                                   m_tabsDefined;
};
#endif //FRMFRAME_H