#include <QTest>
#include "frmminorstrata.h"

FrmMinorStrata::FrmMinorStrata(QWidget *parent, Qt::WFlags flags):
GenericTab(1,parent, flags){

    setupUi(this);

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(goForward()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    initUI();
}

FrmMinorStrata::~FrmMinorStrata()
{
}

void FrmMinorStrata::showDetails()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);
    //TODO:refresh preview
}

void FrmMinorStrata::initUI()
{
    setHeader();
    this->groupDetails->setVisible(false);

    customDtStart->setIsDateTime(true,false,false);
    customDtStart->setIsUTC(false);
    customDtStart->setIsAuto(false);

    customDtEnd->setIsDateTime(true,false,false);
    customDtEnd->setIsUTC(false);
    customDtEnd->setIsAuto(false);
}