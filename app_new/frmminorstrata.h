#include <QtGui>
#include <QtSql>
#include "ui_frmminorstrata.h"
#include "generictab.h"

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
        FrmMinorStrata(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmMinorStrata();

};
#endif //FRMMINORSTRATA_H