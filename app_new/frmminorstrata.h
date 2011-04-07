#include <QtGui>
#include <QtSql>
#include "ui_frmminorstrata.h"
#include "generictab.h"
#include "buttongroup.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMMINORSTRATA_H
#define FRMMINORSTRATA_H

//! Frm MinorStrata Class
/*!
This class implements the widget that corresponds to the MinorStrata definition tab
*/

class FrmMinorStrata : public GenericTab, public Ui::frmminorstrata
{
    Q_OBJECT

    public:
        FrmMinorStrata(DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmMinorStrata();

    private slots:
        //void                                   showDetails();
        void                                   viewRecord();
        void                                   createRecord();
        void                                   onButtonClick(QAbstractButton * button);

    private:
        void                                   setReadOnly(const bool bRO);
        void                                   setHeader(){setLbHead(this->lbHeader);}
        void                                   initModels();
        void                                   initMappers();
        void                                   initUI();
        bool                                   getDateModel(const int dtField, QSqlQueryModel& model);
        QSqlRelationalTableModel*              tRefMinorStrata;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapper2;
        QDataWidgetMapper*                     mapper3;
        ButtonGroup*                           buttonGroup;
        NullRelationalDelegate*                nullDellegate;
};
#endif //FRMMINORSTRATA_H