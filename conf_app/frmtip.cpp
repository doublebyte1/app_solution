#include "frmtip.h"

FrmTip::FrmTip(QWidget *parent, Qt::WFlags flags):
QDialog(parent, flags){

    setupUi(this);

    connect(this->checkShow, SIGNAL(clicked(bool)), this,
        SIGNAL(showStartupMsg(bool)));

}

FrmTip::~FrmTip()
{
    /*!
    //Clean Pointers here!
    */

}