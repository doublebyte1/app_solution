#include <QtGui>
#include <QtSql>
#include "ui_frmframe.h"
#include "generictab.h"
#include "datemodel.h"

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

class FrmFrame : public GenericTab, public Ui::frmframe
{
    Q_OBJECT

    public:
        FrmFrame(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmFrame();

    private slots:
        void                                   onHideFrameDetails();
        void                                   onShowFrameDetails();
        void                                   next();
        void                                   apply();

    private:
        bool                                   getCurrentFrame(int& id);
        bool                                   getStartDt(int& id);
        bool                                   getEndDt(int& id);
        void                                   initModels();
        void                                   setUiDefaults();
        void                                   initMappers();
        QSqlRelationalTableModel*              tRefFrame;
        DateModel*                             tDateTime;
        QSqlTableModel*                        tFrameTime;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapper2;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
};
#endif //FRMFRAME_H