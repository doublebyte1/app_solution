#include <QtGui>
#include <QtSql>
#include "ui_frmvessel.h"
#include "previewtab.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMVESSEL_H
#define FRMVESSEL_H

//! Frm Vessel Class
/*!
This class implements the widget that corresponds to the Sampled Vessel definition tab;
*/

class FrmVessel : public PreviewTab, public Ui::frmVessel
{
    Q_OBJECT

    public:
        FrmVessel(Sample* inSample, DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmVessel();

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
        //void                                   onShowFrameDetails();

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
        void                                   initVesselModel();
        void                                   initMapper1();
        bool                                   comitNonAbstractVessels(const bool bLogbook,
                                                        int& id_Sampled_Cell_Vessels, int& id_Sampled_Strata_Vessels);
        bool                                   comitCellVessels(int& id);
        bool                                   comitStrataVessels(int& id);

        NullRelationalDelegate*                nullDelegate;
        QSqlRelationalTableModel*              tAVessel;
        QSqlTableModel                         *tCellVessels;
        QSqlTableModel                         *tStrataVessels;
        QSqlQueryModel*                        viewVessel;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapper2;
};
#endif //FRMVESSEL_H