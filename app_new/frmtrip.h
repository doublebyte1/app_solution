#include <QtGui>
#include <QtSql>
#include "ui_frmtrip.h"
#include "previewtab.h"
#include "multimodeli.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMTRIP_H
#define FRMTRIP_H

//! Frm Trip Class
/*!
This class implements the widget that corresponds to the Sampled Fishing Trip definition tab;
*/

class FrmTrip : public PreviewTab, public Ui::FrmTrip
{
    Q_OBJECT

    public:
        FrmTrip(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr=0, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmTrip();

    private slots:
        //! Create Record
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   createRecord();
        void                                   editRecord(bool on){;}
        //! Preview Row
        /*! Reimplemented from the PreviewTab base class
        */
        void                                   previewRow(QModelIndex index);
        void                                   onItemSelection();
        void                                   blockCustomDateCtrls();
        void                                   unblockCustomDateCtrls();

    private:
        //! Really Apply
        /*! Reimplemented from the GenericTab base class; this is where we effectively apply the changes, after successfully
        bypassing the binder validation;
        */
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
        void                                   initTripModel();
        void                                   initMapper1();

        NullRelationalDelegate*                nullDelegate;
        QSqlRelationalTableModel*              tTrips;

        QSqlTableModel*                        tTripGears;
        QSqlQueryModel*                        tRefGears;
        MultiModelI*                           multiModelI;

        QSqlQueryModel*                        viewTrips;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
};
#endif //FRMTRIP_H