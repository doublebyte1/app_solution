#include <QtGui>
#include <QtSql>
#include "ui_frmvesseltype.h"
#include "generictab.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMVESSELTYPE_H
#define FRMVESSELTYPE_H

//! Frm Vessel Type
/*!
This class implements the widget that corresponds to the Sampled Vessel Type definition tab; This tab is only
applicable to logbook type frames;
*/

class FrmVesselType : public GenericTab, public Ui::FrmVesselType
{
    Q_OBJECT

    public:
        FrmVesselType(Sample* inSample, DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmVesselType();

    public slots:
        void                                  onShowForm();

    private:
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

        QSqlQueryModel*                        tVesselType;
        //QSqlQueryModel*                        viewVesselType;
        //QDataWidgetMapper*                     mapper1;
        //QDataWidgetMapper*                     mapperStartDt;
        //QDataWidgetMapper*                     mapperEndDt;
};
#endif //FRMVESSELTYPE_H