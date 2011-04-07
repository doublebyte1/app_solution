#include <QTest>
#include "frmminorstrata.h"

FrmMinorStrata::FrmMinorStrata(DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
GenericTab(1,inTDateTime,parent, flags){

    setupUi(this);

    tRefMinorStrata=0;
    buttonGroup=0;
    nullDellegate=0;
    mapper2=0;
    mapper3=0;

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(goForward()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    initModels();
    initUI();
    initMappers();
}

FrmMinorStrata::~FrmMinorStrata()
{
    if (tRefMinorStrata!=0) delete tRefMinorStrata;
    if (buttonGroup!=0) delete buttonGroup;
    if (nullDellegate!=0) delete nullDellegate;
    if (mapper2!=0) delete mapper2;
    if (mapper3!=0) delete mapper3;
}

void FrmMinorStrata::setReadOnly(const bool bRO)
{

    label_3->setEnabled(!bRO);
    cmbGLS->setEnabled(!bRO);
    groupActivity->setEnabled(!bRO);
    radioActive->setEnabled(!bRO);
    horizontalLayout->setEnabled(!bRO);
    radioInactive->setEnabled(!bRO);
    cmbReasons->setEnabled(!bRO);
    label_4->setEnabled(!bRO);
    textComments->setEnabled(!bRO);
    label->setEnabled(!bRO);
    label_2->setEnabled(!bRO);
    customDtStart->setEnabled(!bRO);
    customDtEnd->setEnabled(!bRO);

    if (bRO){
        buttonBox->button(QDialogButtonBox::Apply)->hide();
    }else{
        buttonBox->button(QDialogButtonBox::Apply)->show();
    }

}

void FrmMinorStrata::viewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    setReadOnly(true);

    QSqlQueryModel DtModel1,DtModel2;
    if (!getDateModel(1,DtModel1)) emit showError(tr("Could not init date model!"));
    if (!getDateModel(2,DtModel2)) emit showError(tr("Could not init date model!"));
    mapper2->setModel(&DtModel1);
    mapper3->setModel(&DtModel2);

}

void FrmMinorStrata::createRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    setReadOnly(false);

    tRefMinorStrata->insertRow(tRefMinorStrata->rowCount());
    mapper1->toLast();

    m_tDateTime->insertRow(m_tDateTime->rowCount()-1);
    mapper2->toLast();
    m_tDateTime->insertRow(m_tDateTime->rowCount()-1);
    mapper3->toLast();

}

void FrmMinorStrata::onButtonClick(QAbstractButton* button)
{
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tRefMinorStrata->revertAll();

    } else if (buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){
        //COMIT DATES, COMIT MAPPERS, ERRORS
        this->tRefMinorStrata->submitAll();
    }
}
/*
void FrmMinorStrata::showDetails()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);
    //TODO:refresh preview
}
*/
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

    buttonGroup=new ButtonGroup(this);
    buttonGroup->addButton(radioActive,0);
    buttonGroup->addButton(radioInactive,1);
}

void FrmMinorStrata::initModels()
{
    //Minor Strata
    tRefMinorStrata=new QSqlRelationalTableModel();
    tRefMinorStrata->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Ref_Minor_Strata"),
        QSqlDriver::TableName));
    tRefMinorStrata->setRelation(4, QSqlRelation(tr("Ref_Group_of_LandingSites"), tr("ID"), tr("Name")));
    tRefMinorStrata->setRelation(6, QSqlRelation(tr("Ref_No_Recording_Activities"), tr("ID"), tr("Name")));
    //tRefMinorStrata->setRelation(1, QSqlRelation(tr("GL_Dates"), tr("id_start_dt"), tr("Date_Local")));
    //tRefMinorStrata->setRelation(2, QSqlRelation(tr("GL_Dates"), tr("id_end_dt"), tr("Date_Local")));
    tRefMinorStrata->select();
}

bool FrmMinorStrata::getDateModel(const int dtField, QSqlQueryModel& model)
{
    QModelIndex dtID=tRefMinorStrata->index(mapper1->currentIndex(),dtField);
    if (!dtID.isValid()) return false;
    QString strId=dtID.data().toString();

    //QSqlQueryModel DtModel1;
    model.setQuery(tr("SELECT Date_Local FROM GL_DATES WHERE ID=") + strId);
    //QDateTime dt = DtModel1.record(1).value(tr("Date_Local")).toDateTime();

    return true;
}

void FrmMinorStrata::initMappers()
{
    if (tRefMinorStrata==0) return ;

    mapper1= new QDataWidgetMapper(this);
    mapper1->setModel(tRefMinorStrata);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lCmb;
    lCmb << 4 << 5 << 6;
    QList<int> lText;
    lText << 7;
    nullDellegate=new NullRelationalDelegate(lCmb,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbGLS->setModel(tRefMinorStrata->relationModel(4));
    cmbGLS->setModelColumn(
        tRefMinorStrata->relationModel(4)->fieldIndex(tr("Name")));

    cmbReasons->setModel(tRefMinorStrata->relationModel(6));
    cmbReasons->setModelColumn(
        tRefMinorStrata->relationModel(6)->fieldIndex(tr("Name")));

    mapper1->addMapping(lineNew, 8);
    mapper1->addMapping(cmbGLS, 4);
    mapper1->addMapping(cmbReasons, 6);
    mapper1->addMapping(buttonGroup,5);
    mapper1->addMapping(textComments,7);
    mapper1->toLast();

    if (m_tDateTime==0) return ;

    mapper2= new QDataWidgetMapper(this);

    mapper2->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper2->setItemDelegate(new QItemDelegate(this));
    mapper2->addMapping(customDtStart,0,tr("dateTime").toAscii());

    mapper3= new QDataWidgetMapper(this);
    mapper3->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper3->setItemDelegate(new QItemDelegate(this));
    mapper3->addMapping(customDtEnd,0,tr("dateTime").toAscii());

    mapper2->toFirst();
    mapper3->toFirst();
}

