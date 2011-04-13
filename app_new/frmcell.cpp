#include <QTest>
#include "globaldefs.h"
#include "FrmCell.h"

FrmCell::FrmCell(DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
GenericTab(2,inTDateTime,parent, flags){

    setupUi(this);

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(goForward()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    initModels();
    initUI();
    initMappers();
}

FrmCell::~FrmCell()
{
}

void FrmCell::onShowForm()
{

}

void FrmCell::initModels()
{

}

void FrmCell::initUI()
{
    setHeader();
}

void FrmCell::initMappers()
{

}