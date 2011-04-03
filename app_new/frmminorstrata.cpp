#include <QTest>
#include "frmminorstrata.h"

FrmMinorStrata::FrmMinorStrata(QWidget *parent, Qt::WFlags flags):
GenericTab(1,parent, flags){

    setupUi(this);

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(goForward()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));
}

FrmMinorStrata::~FrmMinorStrata()
{
}
