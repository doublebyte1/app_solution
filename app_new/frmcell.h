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
applicable to logbook type frames;
*/

class FrmCell : public PreviewTab, public Ui::frmCell
{
    Q_OBJECT

    public:
        FrmCell(Sample* inSample, DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmCell();

    signals:

    private slots:
        //void                                   next();
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
        void                                   onShowFrameDetails();

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
        void                                   showEvent ( QShowEvent * event );

        QSqlRelationalTableModel*              tSampCell;
        QSqlQueryModel*                        viewCell;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        //int                                    m_start;
        //int                                    m_end;
};
#endif //FRMCELL_H