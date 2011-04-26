#include <QtGui>
#include <QtSql>
#include "ui_frmcell.h"
#include "generictab.h"

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

class FrmCell : public GenericTab, public Ui::frmCell
{
    Q_OBJECT

    public:
        FrmCell(DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmCell();

    signals:

    public slots:
        void                                   onShowForm();

    private slots:
        //void                                   next();
        void                                   createRecord();
        void                                   previewRow(QModelIndex index);
        void                                   onButtonClick(QAbstractButton * button);

    private:
        void                                   setReadOnly(const bool bRO);
        void                                   filterLS();
        void                                   uI4NewRecord();
        //void                                   resizeEvent ( QResizeEvent * event );
        void                                   setSampCellQuery();
        //void                                   setReadOnly(const bool bRO);
        void                                   setHeader(){setLbHead(this->lbHeader);}
        void                                   initModels();
        void                                   initMappers();
        void                                   initUI();
        QSqlRelationalTableModel*              tSampCell;
        QSqlQueryModel*                        viewCell;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        //ButtonGroup*                           buttonGroup;
        //NullRelationalDelegate*                nullDellegate;
};
#endif //FRMCELL_H