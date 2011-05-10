#include <QtGui>
#include <QtSql>
#include <QtWebKit>
#include "ui_frmprjpage.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMPRJPAGE_H
#define FRMPRJPAGE_H

//! Frm Project Page
/*!
This class implements a form, containing a web browser that points to the project page
*/

class FrmPrjPage : public QWidget, Ui::frmprjpage
{
    Q_OBJECT

    public:
        FrmPrjPage(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmPrjPage();
};

#endif //FRMPRJPAGE_H