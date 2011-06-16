#include <QtGui>
#include <QtSql>
#include "ui_frmcatch.h"
#include "previewtab.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMCATCH_H
#define FRMCATCH_H

//! Frm Catch Class
/*!
This class implements the widget that corresponds to the Sampled Catch definition tab;
*/

class FrmCatch : public PreviewTab, public Ui::FrmCatch
{
    Q_OBJECT

    public:
        FrmCatch(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr=0, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmCatch();

    private slots:
        //! Create Record
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   createRecord();
        //! Preview Row
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   previewRow(QModelIndex index);
        //! On Button Click
        /*! Reimplemented from the PreviewTab base class
        */
        //bool                                   onButtonClick(QAbstractButton * button);
        void                                   onItemSelection();

    private:
        bool                                   reallyApply();
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
        //! Update the sample structure
        /*! Reimplemented from the PreviewTab base class
        */
        bool                                   updateSample();
        void                                   initCatchModel();
        void                                   initMapper1();

//        QSqlTableModel*                        tOpCat;
//        QSqlQueryModel*                        tRefCat;

        NullRelationalDelegate*                nullDelegate;
        QSqlRelationalTableModel*              tCatch;
        QSqlQueryModel*                        viewCatch;
        QDataWidgetMapper*                     mapper1;
        MapperRuleBinder*                      m_mapperBinderPtr;
};
#endif //FRMCATCH_H