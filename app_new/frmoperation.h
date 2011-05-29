#include <QtGui>
#include <QtSql>
#include "ui_frmoperation.h"
#include "previewtab.h"
#include "multimodeli.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMOPERATION_H
#define FRMOPERATION_H

//! Frm Operation Class
/*!
This class implements the widget that corresponds to the Sampled Fishing Operation definition tab;
*/

class FrmOperation : public PreviewTab, public Ui::FrmOperation
{
    Q_OBJECT

    public:
        FrmOperation(Sample* inSample, DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmOperation();

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
        bool                                   onButtonClick(QAbstractButton * button);
        void                                   onItemSelection();

    private:
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
        void                                   initOperationModel();
        void                                   initMapper1();

        QSqlTableModel*                        tOpCat;
        QSqlQueryModel*                        tRefCat;
        MultiModelI*                           multiModelI;

        NullRelationalDelegate*                nullDelegate;
        QSqlRelationalTableModel*              tOperations;
        QSqlQueryModel*                        viewOperations;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
};
#endif //FRMOPERATION_H