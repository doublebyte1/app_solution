#include <QtGui>
#include <QtSql>
#include "ui_frmframe.h"
#include "generictab.h"

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
        FrmFrame(Sample* inSample, DateModel* inTDateTime, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmFrame();

        bool                                   loadFrameFromSample();

    public slots:
        void                                   onShowForm(){;}//does nothing
        bool                                   next();

    private slots:
        void                                   onHideFrameDetails();
        void                                   onShowFrameDetails();
        void                                   apply();

    signals:
        void                                   isLogBook(bool bLogBook);
        void                                   submitted(int index, bool bOk);

    private:
        void                                   setReadOnly(const bool bRO){(void)bRO;}//does nothing

        bool                                   updateSample();
        bool                                   getCurrentFrame(int& id);
        void                                   initModels();
        void                                   initMappers();
        void                                   initUI();
        QSqlRelationalTableModel*              tRefFrame;
        QSqlTableModel*                        tFrameTime;
        QDataWidgetMapper*                     mapper1;
        QDataWidgetMapper*                     mapper2;
        QDataWidgetMapper*                     mapperStartDt;
        QDataWidgetMapper*                     mapperEndDt;
        FrmFrameDetails::Mode                  m_curMode;
        bool                                   m_submitted;
        bool                                   m_tabsDefined;
        int                                    m_curFrameTime;
};
#endif //FRMFRAME_H