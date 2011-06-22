#include "frmreports.h"

FrmReports::FrmReports(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags){

    setupUi(this);

     connect(pushClose, SIGNAL(clicked()), this,
    SIGNAL(hideFrmReports()),Qt::UniqueConnection);
}

FrmReports::~FrmReports()
{

}