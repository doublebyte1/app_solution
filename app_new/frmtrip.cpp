#include <QTest>
//#include "globaldefs.h"
#include "frmtrip.h"

FrmTrip::FrmTrip(Sample* inSample, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
PreviewTab(5,inSample,inTDateTime,tr("Fishing Trip"),parent, flags){

    setupUi(this);

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(next()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    tTrips=0;
    viewTrips=0;
    mapper1=0;
    mapperStartDt=0;
    mapperEndDt=0;
    nullDelegate=0;

    initModels();
    initUI();
    initMappers();
}

FrmTrip::~FrmTrip()
{
    if (tTrips!=0) delete tTrips;
    if (viewTrips!=0) delete viewTrips;
    if (nullDelegate!=0) delete nullDelegate;
    if (mapper1!=0) delete mapper1;
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;
}


void FrmTrip::onItemSelection()
{
    pushNext->setEnabled(tableView->selectionModel()->hasSelection());
}

void FrmTrip::previewRow(QModelIndex index)
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->hide();

    QModelIndex idx=viewTrips->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this vessel!"));
        return;
    }

    QString id=idx.data().toString();

    tTrips->setFilter(tr("Sampled_Fishing_Trips.ID=")+id);
    if (tTrips->rowCount()!=1)
        return;

    mapper1->toLast();

    //Now fix the dates
    idx=tTrips->index(0,2);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this trip!"));
        return;
    }
    QString strStartDt=idx.data().toString();
    idx=tTrips->index(0,3);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this trip!"));
        return;
    }
    QString strEndDt=idx.data().toString();

    m_tDateTime->setFilter(tr("ID=") + strStartDt + tr(" OR ID=") + strEndDt);

    if (m_tDateTime->rowCount()!=2)
        return;

    //adjusting the display format of the dates on preview
    QModelIndex idxDType=m_tDateTime->index(0,4);
    if (!idxDType.isValid()) return;
    customDtStart->adjustDateTime(idxDType,idxDType.data());
    idxDType=m_tDateTime->index(1,4);
    if (!idxDType.isValid()) return;
    customDtEnd->adjustDateTime(idxDType,idxDType.data());

    mapperEndDt->toLast();
    mapperStartDt->setCurrentIndex(mapperEndDt->currentIndex()-1);

    pushNext->setEnabled(true);
}

void FrmTrip::setPreviewQuery()
{
    if (m_sample==0) return;
    QString strQuery=

    tr("SELECT     dbo.Sampled_Fishing_Trips.ID, dbo.Ref_Samplers.Name, CONVERT(CHAR(10), F1.Date_Local, 103) AS [Start Date], ") +
    tr(" CASE WHEN F1.Date_Type=(SELECT ID from Ref_DateTime_Type WHERE Name='Date') THEN 'missing' ELSE") +
    tr(" CONVERT(VARCHAR(8), F1.Date_Local, 108) END [Start Time]") +
    tr(" , CONVERT(CHAR(10), F2.Date_Local, 103) AS [End Date], ") +
    tr(" CASE WHEN F2.Date_Type=(SELECT ID from Ref_DateTime_Type WHERE Name='Date') THEN 'missing' ELSE") +
    tr(" CONVERT(VARCHAR(8), F2.Date_Local, 108) END [End Time] ") +
    tr(" FROM         dbo.Sampled_Fishing_Trips INNER JOIN") +
    tr("                      dbo.Ref_Samplers ON dbo.Sampled_Fishing_Trips.id_sampler = dbo.Ref_Samplers.ID INNER JOIN") +
    tr("                      dbo.GL_Dates AS F1 ON dbo.Sampled_Fishing_Trips.id_start_dt = F1.ID INNER JOIN") +
    tr("                      dbo.GL_Dates AS F2 ON dbo.Sampled_Fishing_Trips.id_end_dt = F2.ID") +
    tr(" WHERE     (dbo.Sampled_Fishing_Trips.id_abstract_sampled_vessels = :id) ORDER BY ID DESC")
    ;

    QSqlQuery query;
    query.prepare( strQuery );
    query.bindValue(0,m_sample->sampVesselId);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Sampled Fishing Trips!"));
        return;
    }

    viewTrips->setQuery(query);

    tableView->hideColumn(0);
    resizeToVisibleColumns(tableView);
}

void FrmTrip::initModels()
{
    if (viewTrips!=0) delete viewTrips;
    viewTrips = new QSqlQueryModel;

    viewTrips->setHeaderData(0, Qt::Horizontal, tr("Sampler"));
    viewTrips->setHeaderData(1, Qt::Horizontal, tr("Start Date"));
    viewTrips->setHeaderData(2, Qt::Horizontal, tr("Start Time"));
    viewTrips->setHeaderData(3, Qt::Horizontal, tr("End Date"));
    viewTrips->setHeaderData(4, Qt::Horizontal, tr("End Time"));
}

void FrmTrip::initUI()
{
    setHeader();

    this->groupDetails->setVisible(false);
    initPreviewTable(tableView,viewTrips);

    //initializing the container for the readonly!S
    m_lWidgets << cmbSampler;
    m_lWidgets << spinProf;
    m_lWidgets << spinPart;
    m_lWidgets << customDtStart;
    m_lWidgets << customDtEnd;
    m_lWidgets << catchInputCtrl;
    m_lWidgets << textComments;
    m_lWidgets << spinNOE;
    m_lWidgets << spinNOC;
    customDtStart->setIsUTC(false);
    customDtStart->setIsAuto(false);

    customDtEnd->setIsUTC(false);
    customDtEnd->setIsAuto(false);

    connect(customDtStart, SIGNAL(isDateTime(bool,int)), m_tDateTime,
        SLOT(amendDateTimeType(bool,int)));

    connect(customDtEnd, SIGNAL(isDateTime(bool,int)), m_tDateTime,
        SLOT(amendDateTimeType(bool,int)));

    pushNext->setEnabled(false);
}

void FrmTrip::initMapper1()
{
    if (mapper1!=0) delete mapper1;
    mapper1= new QDataWidgetMapper(this);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (tTrips==0) return;

    mapper1->setModel(tTrips);

    if (nullDellegate!=0) delete nullDellegate;

    QList<int> lOthers;
    QList<int> lText;
    for (int i=4; i < 22; ++i){
        if (i!=16)
            lOthers << i;
        else
            lText << i;
    }

    nullDellegate=new NullRelationalDelegate(lOthers,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbSite->setModel(tTrips->relationModel(4));
    cmbSite->setModelColumn(
        tTrips->relationModel(4)->fieldIndex(tr("Name")));

    cmbSampler->setModel(tTrips->relationModel(5));
    cmbSampler->setModelColumn(
        tTrips->relationModel(5)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbWeightUnits()->setModel(tTrips->relationModel(12));
    catchInputCtrl->pCmbWeightUnits()->setModelColumn(
        tTrips->relationModel(12)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbBoxUnits()->setModel(tTrips->relationModel(15));
    catchInputCtrl->pCmbBoxUnits()->setModelColumn(
        tTrips->relationModel(15)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbUnitUnits()->setModel(tTrips->relationModel(20));
    catchInputCtrl->pCmbUnitUnits()->setModelColumn(
        tTrips->relationModel(20)->fieldIndex(tr("Name")));

    mapper1->addMapping(cmbSite, 4);
    mapper1->addMapping(cmbSampler, 5);
    mapper1->addMapping(spinProf, 6);
    mapper1->addMapping(spinPart, 7);

    mapper1->addMapping(spinNOE, 8);
    mapper1->addMapping(spinNOC, 9);

    mapper1->addMapping(catchInputCtrl->pDoubleSpinTotalE(), 10);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinTotalC(), 11);

    mapper1->addMapping(catchInputCtrl->pCmbWeightUnits(), 12);

    mapper1->addMapping(catchInputCtrl->pDoubleSpinNoBoxesE(), 13);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinNoBoxesC(), 14);
    mapper1->addMapping(catchInputCtrl->pCmbBoxUnits(), 15);
    mapper1->addMapping(textComments,16);

    mapper1->addMapping(catchInputCtrl->pDoubleSpinWeightBox(), 17);

    mapper1->addMapping(catchInputCtrl->pSpinUnitsE(), 18);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinWeightUnit(), 19);

    mapper1->addMapping(catchInputCtrl->pCmbUnitUnits(), 20);
    mapper1->addMapping(catchInputCtrl->pSpinUnitsC(), 21);

}

void FrmTrip::initMappers()
{
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
}

void FrmTrip::beforeShow()
{
    this->groupDetails->setVisible(false);
    if (m_sample->bLogBook)
        m_lWidgets << cmbSite;

    setSourceText(lbSource);
    initTripModel();
}

bool FrmTrip::onButtonClick(QAbstractButton* button)
{
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tTrips->revertAll();
        return true;

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

        while(m_tDateTime->canFetchMore())
            m_tDateTime->fetchMore();

        int startIdx=m_tDateTime->rowCount()-2;
        int endIdx=m_tDateTime->rowCount()-1;

        mapperStartDt->setCurrentIndex(startIdx);
        mapperEndDt->setCurrentIndex(endIdx);

        if (bError) {
            emit showError(tr("Could not create dates in the database!"));
        }else{

            int idStart;
            if (getDtId(startIdx,idStart)){
                QModelIndex idxStart=tTrips->index(tTrips->rowCount()-1,2);
                if (idxStart.isValid()){
                    tTrips->setData(idxStart,idStart);
                }else bError=true;
            }else bError=true;

            int idEnd;
            if (getDtId(endIdx,idEnd)){
                QModelIndex idxEnd=tTrips->index(tTrips->rowCount()-1,3);
                if (idxEnd.isValid()){
                    tTrips->setData(idxEnd,idEnd);
                }else bError=true;
            }else bError=true;

        if (mapper1->submit()){
            bError=!
                    tTrips->submitAll();
                if (bError){
                    if (tTrips->lastError().type()!=QSqlError::NoError)
                        emit showError(tTrips->lastError().text());
                    else
                        emit showError(tr("Could not write cell in the database!"));
                }
        }
        }

        button->setEnabled(bError);

        emit lockControls(!bError,m_lWidgets);
        if (!bError){
            buttonBox->button(QDialogButtonBox::Apply)->hide();
        }else{
            buttonBox->button(QDialogButtonBox::Apply)->show();
        }

        if (!bError)
            return afterApply();

    }

    return false;
}

void FrmTrip::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(false,m_lWidgets);

    customDtStart->setIsDateTime(true,true,true);

    customDtEnd->setIsDateTime(true,true,true);

    textComments->clear();

    buttonBox->button(QDialogButtonBox::Apply)->show();
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}

void FrmTrip::createRecord()
{
    genericCreateRecord();
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

    customDtStart->setModelRow(m_tDateTime->rowCount()-2);
    customDtEnd->setModelRow(m_tDateTime->rowCount()-1);

    mapperStartDt->setCurrentIndex(m_tDateTime->rowCount()-2);
    mapperEndDt->setCurrentIndex(m_tDateTime->rowCount()-1);

    //IMPORTANT: do this after setting the model row!
    connect(m_tDateTime, SIGNAL(getDateType(QModelIndex,QVariant)), customDtStart,
        SLOT(adjustDateTime(QModelIndex,QVariant)),Qt::UniqueConnection);

    connect(m_tDateTime, SIGNAL(getDateType(QModelIndex,QVariant)), customDtEnd,
        SLOT(adjustDateTime(QModelIndex,QVariant)),Qt::UniqueConnection);

    while(tTrips->canFetchMore())
        tTrips->fetchMore();

    //Fields that we have to fill behind the scenes...
    QModelIndex idx=tTrips->index(tTrips->rowCount()-1,1);
    tTrips->setData(idx,m_sample->sampVesselId);//id_abstract_sampled_vessels

    //TODO: on sample fill the abstract landing site
    if (!m_sample->bLogBook){
        cmbSite->setCurrentIndex(0);
        cmbSite->setEnabled(false);
    }

    uI4NewRecord();//init UI
}

void FrmTrip::initTripModel()
{
    if (tTrips!=0) delete tTrips;

    tTrips=new QSqlRelationalTableModel();
    tTrips->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Fishing_Trips"),
        QSqlDriver::TableName));
    tTrips->setRelation(4, QSqlRelation(tr("Ref_Abstract_LandingSite"), tr("ID"), tr("Name")));
    tTrips->setRelation(5, QSqlRelation(tr("Ref_Samplers"), tr("ID"), tr("Name")));
    tTrips->setRelation(12, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));
    tTrips->setRelation(15, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));
    tTrips->setRelation(20, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));
    tTrips->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tTrips->sort(0,Qt::AscendingOrder);
    tTrips->select();

    setPreviewModel(tTrips);
}

void FrmTrip::filterModel4Combo()
{
    if (!m_sample) return;

    QSqlQuery query;
    QString strQuery, strFilter;

    //TODO: filter MS for Logbook 
    if (m_sample->bLogBook){

        //DUVIDA: filtro para o LS?
        if (m_sample->minorStrataId==-1){
            emit showError(tr("Could not identify the minor strata of this frame!"));
            return;
        }

        strQuery=
        tr("SELECT     TOP (100) PERCENT dbo.Ref_Abstract_LandingSite.ID") +
        tr(" FROM         dbo.Ref_Minor_Strata INNER JOIN") +
        tr("                      dbo.FR_Time ON dbo.Ref_Minor_Strata.id_frame_time = dbo.FR_Time.ID INNER JOIN") +
        tr("                      dbo.FR_Frame ON dbo.FR_Time.id_frame = dbo.FR_Frame.ID INNER JOIN") +
        tr("                      dbo.FR_Sub_Frame ON dbo.FR_Frame.ID = dbo.FR_Sub_Frame.id_frame INNER JOIN") +
        tr("                      dbo.FR_GLS2ALS ON dbo.FR_Sub_Frame.ID = dbo.FR_GLS2ALS.id_sub_frame INNER JOIN") +
        tr("                      dbo.Ref_Abstract_LandingSite ON dbo.FR_GLS2ALS.id_abstract_landingsite = dbo.Ref_Abstract_LandingSite.ID") +
        tr(" WHERE     (dbo.Ref_Minor_Strata.ID = ") + QVariant(m_sample->minorStrataId).toString() + (" ) AND (dbo.FR_GLS2ALS.id_gls =") +
        tr("                  (SELECT     id_gls") +
        tr("                    FROM          dbo.Ref_Minor_Strata AS Ref_Minor_Strata_1") +
        tr("                    WHERE      (ID = ") + QVariant(m_sample->minorStrataId).toString() + (")))")
        ;//for getting all the boats on the frame, just remove the last condition

        query.prepare(strQuery);
        if (!query.exec()){
            emit showError(tr("Could not obtain filter for Landing Sites!"));
        return;
        }

        QString strFilter(tr(""));
        while (query.next()) {
            strFilter.append(tr("ID=") + query.value(0).toString());
            strFilter.append(tr(" OR "));
        }
        if (!strFilter.isEmpty())
            strFilter=strFilter.remove(strFilter.size()-tr(" OR ").length(),tr(" OR ").length());

        tTrips->relationModel(4)->setFilter(strFilter);

    }else{

        strQuery=
        tr("SELECT     id_abstract_LandingSite") +
        tr(" FROM         dbo.Sampled_Cell") +
        tr(" WHERE     (ID = :id)")
        ;

        query.prepare(strQuery);

        if (m_sample->cellId==-1){
            emit showError(tr("There is a problem with the type of this frame!"));
            return;
        }
        query.bindValue(0,m_sample->cellId);

        if (!query.exec() || query.numRowsAffected()!=1){
            emit showError(tr("Could not obtain filter for landing sites!"));
            return;
        }

        query.first();
        strFilter.append(tr("ID=") + query.value(0).toString());

        if (!strFilter.isEmpty()){
            tTrips->relationModel(4)->setFilter(strFilter);
        }

    }

    initMapper1();
}

bool FrmTrip::updateSample()
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //updating the sample structure
    QModelIndex idx=viewTrips->index(tableView->selectionModel()->currentIndex().row(),0);

    //TODO: update the vessel here
    m_sample->tripId=idx.data().toInt();
    return true;
}

bool FrmTrip::getNextLabel(QString& strLabel)
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //sending the name
    QModelIndex idx=viewTrips->index(tableView->selectionModel()->currentIndex().row(),2);//startdate
    strLabel=idx.data().toString();
    return true;
}
