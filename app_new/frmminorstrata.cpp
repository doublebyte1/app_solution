#include <QTest>
#include "globaldefs.h"
#include "frmminorstrata.h"

FrmMinorStrata::FrmMinorStrata(DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
GenericTab(1,inTDateTime,parent, flags){

    setupUi(this);

    tRefMinorStrata=0;
    buttonGroup=0;
    nullDellegate=0;
    mapperStartDt=0;
    mapperEndDt=0;

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
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;
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
    /*
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    setReadOnly(true);

    QSqlQueryModel DtModel1,DtModel2;
    if (!getDateModel(1,DtModel1)) emit showError(tr("Could not init date model!"));
    if (!getDateModel(2,DtModel2)) emit showError(tr("Could not init date model!"));
    mapperStartDt->setModel(&DtModel1);
    mapperEndDt->setModel(&DtModel2);
*/
}

void FrmMinorStrata::createRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    setReadOnly(false);

    if (tRefMinorStrata==0) return ;

    tRefMinorStrata->insertRow(tRefMinorStrata->rowCount());

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

    if(!m_tDateTime) return;
    m_tDateTime->select();

    bool bDate, bTime;
    customDtStart->getIsDateTime(bDate,bTime);
    if (!m_tDateTime->insertNewRecord(customDtStart->getIsAuto(),bDate,bTime)){
        emit showError(tr("Could not insert start date!"));
        return;
    }
    customDtEnd->getIsDateTime(bDate,bTime);
    if (!m_tDateTime->insertNewRecord(customDtStart->getIsAuto(),bDate,bTime)){
        emit showError(tr("Could not insert start date!"));
        return;
    }

    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;

    mapperStartDt= new QDataWidgetMapper(this);
    mapperStartDt->setModel(m_tDateTime);
    mapperStartDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperStartDt->setItemDelegate(new QItemDelegate(this));
    mapperStartDt->addMapping(customDtStart,3,tr("dateTime").toAscii());

    mapperEndDt= new QDataWidgetMapper(this);
    mapperEndDt->setModel(m_tDateTime);
    mapperEndDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperEndDt->setItemDelegate(new QItemDelegate(this));
    mapperEndDt->addMapping(customDtEnd,3,tr("dateTime").toAscii());

    mapperStartDt->setCurrentIndex(m_tDateTime->rowCount()-2);
    mapperEndDt->setCurrentIndex(m_tDateTime->rowCount()-1);

    QModelIndex idx=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,3);
    tRefMinorStrata->setData(idx,m_varData);//id_sub_frame

    QString strQuery=
    tr("SELECT     dbo.FR_F2GLS.id_gls ") +
    tr("FROM         dbo.FR_Sub_Frame INNER JOIN") +
    tr("                 dbo.FR_F2GLS ON dbo.FR_Sub_Frame.ID = dbo.FR_F2GLS.id_sub_frame INNER JOIN") +
    tr("                  dbo.FR_Frame INNER JOIN") +
    tr("                  dbo.FR_Time ON dbo.FR_Frame.ID = dbo.FR_Time.id_frame ON dbo.FR_Sub_Frame.id_frame = dbo.FR_Frame.ID ") +
    tr("WHERE     (dbo.FR_Time.ID = :id) AND (dbo.FR_Sub_Frame.Type =") +
    tr("                      (SELECT     ID") +
    tr("                        FROM          dbo.Ref_Frame") +
    tr("                        WHERE      (Name = :root)) )");

    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(0,m_varData);
    query.bindValue(1,qApp->translate("frame", strRoot));

    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Group of Landing Sites!"));
        return;
    }

    QString strFilter(tr(""));
     while (query.next()) {
        strFilter.append(tr("ID=") + query.value(0).toString());
        strFilter.append(tr(" OR "));
     }
     if (!strFilter.isEmpty())
         strFilter=strFilter.remove(strFilter.size()-tr(" OR ").length(),tr(" OR ").length());

    tRefMinorStrata->relationModel(4)->setFilter(strFilter);
}

void FrmMinorStrata::onButtonClick(QAbstractButton* button)
{
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tRefMinorStrata->revertAll();

    } else if (buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){

        bool bError=false;
        //First insert the dates...
        if (!mapperStartDt->submit() 
            || !mapperEndDt->submit()){
            if (m_tDateTime->lastError().type()!=QSqlError::NoError)
                emit showError(m_tDateTime->lastError().text());
            else
                emit showError(tr("Could not submit mapper!"));
            bError=true;
        }
        else{
            if (!m_tDateTime->submitAll()){
                if (m_tDateTime->lastError().type()!=QSqlError::NoError)
                    emit showError(m_tDateTime->lastError().text());
                else
                    emit showError(tr("Could not write DateTime in the database!"));

                bError=true;
            }
        }

        int startIdx=m_tDateTime->rowCount()-2;
        int endIdx=m_tDateTime->rowCount()-1;

        mapperStartDt->setCurrentIndex(startIdx);
        mapperEndDt->setCurrentIndex(endIdx);

        if (bError) {
            emit showError(tr("Could not create dates in the database!"));
        }else{

            int idStart;
            if (getDtId(startIdx,idStart)){
                QModelIndex idxStart=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,1);
                if (idxStart.isValid()){
                    tRefMinorStrata->setData(idxStart,idStart);
                }else bError=true;
            }else bError=true;

            int idEnd;
            if (getDtId(endIdx,idEnd)){
                QModelIndex idxEnd=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,2);
                if (idxEnd.isValid()){
                    tRefMinorStrata->setData(idxEnd,idEnd);
                }else bError=true;
            }else bError=true;

            if (!bError){
                if (mapper1->submit()){
                    bError=!
                        tRefMinorStrata->submitAll();
                    if (bError){
                        if (tRefMinorStrata->lastError().type()!=QSqlError::NoError)
                            emit showError(tRefMinorStrata->lastError().text());
                        else
                            emit showError(tr("Could not write Minor Strata in the database!"));
                    }mapper1->toLast();
                }else bError=true;
            }
        }
        button->setEnabled(bError);
        setReadOnly(!bError);
    }
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
    tRefMinorStrata->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tRefMinorStrata->select();
}

bool FrmMinorStrata::getDateModel(const int dtField, QSqlQueryModel& model)
{
    QModelIndex dtID=tRefMinorStrata->index(mapper1->currentIndex(),dtField);
    if (!dtID.isValid()) return false;
    QString strId=dtID.data().toString();
    model.setQuery(tr("SELECT Date_Local FROM GL_DATES WHERE ID=") + strId);

    return true;
}

void FrmMinorStrata::initMappers()
{
    /*
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
    //mapper1->toLast();
*/
    /*
    if (m_tDateTime==0) return ;

    mapperStartDt= new QDataWidgetMapper(this);
    mapperEndDt= new QDataWidgetMapper(this);
*/
    //mapperStartDt->toFirst();
    //mapperEndDt->toFirst();
}

