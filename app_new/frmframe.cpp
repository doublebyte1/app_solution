#include <QTest>
#include "frmframe.h"

FrmFrame::FrmFrame(QWidget *parent, Qt::WFlags flags):
GenericTab(0,parent, flags){

    setupUi(this);

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(goForward()));

    connect(toolView, SIGNAL(clicked()), this,
        SLOT(onShowFrameDetails()));//TODO:change curidex to grabb the id

    connect(toolEdit, SIGNAL(clicked()), this,
    SLOT(onShowFrameDetails()));

    connect(this, SIGNAL(hideFrameDetails()), this,
        SLOT(onHideFrameDetails()));

    tRefFrame=new QSqlRelationalTableModel();
    tRefFrame->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("FR_Frame"),
        QSqlDriver::TableName));
    tRefFrame->setRelation(0, QSqlRelation(tr("FR_Frame"), tr("ID"), tr("Name")));

    radioNew->setChecked(true);
    enableDisableStuff(false);
    radioCopy->setChecked(true);

    tRefFrame->select();
    filterTable(tRefFrame->relationModel(0));

    initMappers();
}

FrmFrame::~FrmFrame()
{
    if (tRefFrame!=0) delete tRefFrame;
}

void FrmFrame::enableDisableStuff(const bool b)
{
    cmbPrexistent->setEnabled(b);
    toolView->setEnabled(b);
    groupNew->setEnabled(!b);
}

void FrmFrame::onChoosePreExistent()
{
    enableDisableStuff(true);
}

void FrmFrame::onCreateNew()
{
    enableDisableStuff(false);
}

void FrmFrame::onHideFrameDetails()
{
    int copyIndex=cmbCopy->currentIndex();
    int exIndex=cmbPrexistent->currentIndex();

    tRefFrame->relationModel(0)->select();

    cmbCopy->setCurrentIndex(copyIndex);
    cmbPrexistent->setCurrentIndex(exIndex);
}

void FrmFrame::onShowFrameDetails()
{
    if (dynamic_cast<QToolButton*>(QObject::sender())!=0){
        if (QObject::sender()->objectName()==tr("toolView")){
            if (cmbPrexistent->currentIndex()!=-1)
                emit showFrameDetails(FrmFrameDetails::VIEW,FrmFrameDetails::PERMANENT,
                cmbPrexistent->model()->index(cmbPrexistent->currentIndex(),0).data().toInt());
        }else if (QObject::sender()->objectName()==tr("toolEdit")){
            if (radioCopy->isChecked() && cmbCopy->currentIndex()!=-1)
                emit showFrameDetails(FrmFrameDetails::EDIT,FrmFrameDetails::PERMANENT,
                cmbCopy->model()->index(cmbCopy->currentIndex(),0).data().toInt());
            else if (radioCreate->isChecked())
                emit showFrameDetails(FrmFrameDetails::CREATE,FrmFrameDetails::PERMANENT,-1);
        }
    }
}

void FrmFrame::initMappers()
{
    if (tRefFrame==0) return ;

    mapper1= new QDataWidgetMapper(this);
    mapper1->setModel(tRefFrame);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper1->setItemDelegate(new QSqlRelationalDelegate(this));

    cmbCopy->setModel(tRefFrame->relationModel(0));
    cmbCopy->setModelColumn(
        tRefFrame->relationModel(0)->fieldIndex(tr("Name")));

    mapper2= new QDataWidgetMapper(this);

    mapper2->setModel(tRefFrame);
    mapper2->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper2->setItemDelegate(new QSqlRelationalDelegate(this));

    cmbPrexistent->setModel(tRefFrame->relationModel(0));
    cmbPrexistent->setModelColumn(
        tRefFrame->relationModel(0)->fieldIndex(tr("Name")));

    mapper1->addMapping(this->cmbPrexistent, 0, tr("currentIndex").toAscii());
    mapper2->addMapping(this->cmbCopy, 0, tr("currentIndex").toAscii());

    mapper1->toLast();
    mapper2->toLast();
}