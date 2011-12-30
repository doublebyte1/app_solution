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
        FrmVessel(RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr=0, QWidget *parent = 0, Qt::WFlags flags = 0);
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
        //! Edit finished
        /*! Reimplemented from the PreviewTab base class
        \sa previewRow(QModelIndex index), onEditLeave(const bool bFinished, const bool bDiscarded)
        */
        void                                   editFinished();

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
        //! Filter Sampled Cell Vessels
        /*! Since we need to filter an additional mapper/model for the Sampled Cell Vessels (Sampling approach),
        this is an utility function that focus on the selected abstract sampled vessel current item,
        and grabbs the related sampled cell vessel record, filtering that model
        \par index model index for the current selected item on the table view
        \return boolean as success or failure
        */
        bool                                   filterSampledCellVessels(QModelIndex index);
        void                                   initVesselModel();
        void                                   initMapper1();
        //! Comit non abstract vessels
        /*! This is an interface for deciding the instatiation of the abstract vessel, into a sampled strata vessel
        or a sampled cell vessel. From here, it it points to the respective functions: comitCellVessels(int& id),
        comitStrataVessels(int& id), and in the end it give us a pair of ids (one of them corresponding to a n/a record).
        This ids are necessary to finish filling the record on abstract sampled vessels table.
        \par bLogbook flag indicating if it is a logbook or not
        /id address of an integer to put the calculated id_Sampled_Cell_Vessels
        /id address of an integer to put the calculated id_Sampled_Strata_Vessels
        \return boolean as success or failure
        \sa comitCellVessels(int& id), comitStrataVessels(int& id)
        */
        bool                                   comitNonAbstractVessels(const bool bLogbook,
                                                        int& id_Sampled_Cell_Vessels, int& id_Sampled_Strata_Vessels);
        //! Comit Sampled Cell Vessels
        /*! Initializes a record on Sampled Cell Vessels and gives us the id
        \return boolean as success or failure
        \sa comitNonAbstractVessels(const bool bLogbook,int& id_Sampled_Cell_Vessels, int& id_Sampled_Strata_Vessels)
        , comitStrataVessels(int& id)
        */
        bool                                   comitCellVessels(int& id);
        //! Comit Sampled Strata Vessels
        /*! Initializes a record on Sampled Strata Vessels and gives us the id
        \return boolean as success or failure
        \sa comitNonAbstractVessels(const bool bLogbook,int& id_Sampled_Cell_Vessels, int& id_Sampled_Strata_Vessels)
        , comitCellVessels(int& id)
        */
        bool                                   comitStrataVessels(int& id);
        NullRelationalDelegate*                nullDelegate;
        QSqlRelationalTableModel*              tAVessel;
        QSqlTableModel                         *tCellVessels;
        QSqlTableModel                         *tStrataVessels;
        QSqlQueryModel*                        viewVessel;
        QDataWidgetMapper*                     mapper1;/**< mapper for the stuff on abstract sampled vessels */
        QDataWidgetMapper*                     mapper2;/**< mapper for the stuff on sampled cell vessels (spin boxes) */
};
#endif //FRMVESSEL_H