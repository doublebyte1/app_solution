#include <QtGui>
#include <QtSql>
#include "ui_frmreports.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMREPORTS_H
#define FRMREPORTS_H

//! Frm Reports Class
/*!
This class implements a form where we can load reports, using the Exaro report engine;
*/

class FrmReports : public QWidget, public Ui::frmreports
{
    Q_OBJECT

    public:
        FrmReports(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmReports();

    signals:
        void                        hideFrmReports();

    private slots:

};
#endif //FRMREPORTS_H