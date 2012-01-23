#include <QTest>
//#include "globaldefs.h"
#include "frmtrip.h"

FrmTrip::FrmTrip(RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
PreviewTab(5,inRoleDef,inSample,inTDateTime,tr("Fishing Trip"), ruleCheckerPtr, parent, flags){

    setupUi(this);

    blockCustomDateCtrls();

    installEventFilters();

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(next()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    connect(this, SIGNAL(blockCatchUISignals(const bool)), catchInputCtrl,
    SIGNAL(blockWidgetsSignals(const bool)));

    tTrips=0;
    tRefGears=0;
    tTripGears=0;
    tRefZones=0;
    tTripZones=0;
    viewTrips=0;
    mapper1=0;
    multiModelI=0;
    multiModelI2=0;
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
    if (tRefGears!=0) delete tRefGears;
    if (tTripGears!=0) delete tTripGears;
    if (tRefZones!=0) delete tRefZones;
    if (tTripZones!=0) delete tTripZones;
    if (viewTrips!=0) delete viewTrips;
    if (nullDelegate!=0) delete nullDelegate;
    if (mapper1!=0) delete mapper1;
    if (multiModelI!=0) delete multiModelI;
    if (multiModelI2!=0) delete multiModelI2;
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;
}

void FrmTrip::initHelpIds()
{
    m_widgetInfo.insert(tableView,"Medfisis::Enter_the_Fishing_Trip");
    m_widgetInfo.insert(groupDetails,"Medfisis::Sub-form_Fishing_TripDetails");
    m_widgetInfo.insert(spinProf,"Medfisis::professional_fishermen");
    m_widgetInfo.insert(spinPart,"Medfisis::part-time_fishermen");
}

void FrmTrip::onItemSelection()
{
    pushNext->setEnabled(tableView->selectionModel()->hasSelection());
    pushPrevious->setEnabled(tableView->selectionModel()->hasSelection());
}

void FrmTrip::previewRow(QModelIndex index)
{
    emit blockCatchUISignals(true);

    QModelIndex idx=viewTrips->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this trip!"));
        return;
    }

    updateSample(idx);

    if (!abstractPreviewRow(index)){
        emit showError (tr("Could not preview this record!"));
    }else{

        int intId=idx.data().toInt();//for the MultiModelI

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

        m_tDateTime->setFilter("ID=" + strStartDt + " OR ID=" + strEndDt);

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

        //preview record on the listView
        multiModelI->setParentId(intId);
        multiModelI->model2List("id_fishing_trip");

        //preview record on the listView
        multiModelI2->setParentId(intId);
        multiModelI2->model2List("id_fishing_trip");
    }

    emit blockCatchUISignals(true);
}

void FrmTrip::setPreviewQuery()
{
    if (m_sample==0) return;
    QString strQuery=

    "SELECT     dbo.Sampled_Fishing_Trips.ID, dbo.Ref_Samplers.Name as Sampler, CONVERT(CHAR(10), F1.Date_Local, 103) AS [Start Date], "
    " CASE WHEN F1.Date_Type=(SELECT ID from Ref_DateTime_Type WHERE Name='Date') THEN 'missing' ELSE"
    " CONVERT(VARCHAR(8), F1.Date_Local, 108) END [Start Time]"
    " , CONVERT(CHAR(10), F2.Date_Local, 103) AS [End Date], "
    " CASE WHEN F2.Date_Type=(SELECT ID from Ref_DateTime_Type WHERE Name='Date') THEN 'missing' ELSE"
    " CONVERT(VARCHAR(8), F2.Date_Local, 108) END [End Time] "
    " FROM         dbo.Sampled_Fishing_Trips INNER JOIN"
    "                      dbo.Ref_Samplers ON dbo.Sampled_Fishing_Trips.id_sampler = dbo.Ref_Samplers.ID INNER JOIN"
    "                      dbo.GL_Dates AS F1 ON dbo.Sampled_Fishing_Trips.id_start_dt = F1.ID INNER JOIN"
    "                      dbo.GL_Dates AS F2 ON dbo.Sampled_Fishing_Trips.id_end_dt = F2.ID"
    " WHERE     (dbo.Sampled_Fishing_Trips.id_abstract_sampled_vessels = :id) ORDER BY ID DESC"
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

    if (tRefGears!=0) delete tRefGears;

     tRefGears = new QSqlQueryModel;
     tRefGears->setQuery(
        "SELECT     ID, Name"
        " FROM         dbo.Ref_Gears ORDER BY ID ASC"
         );

    if (tTripGears!=0) delete tTripGears;

    tTripGears=new QSqlTableModel();
    tTripGears->setTable(QSqlDatabase().driver()->escapeIdentifier("Sampled_Fishing_Trips_Gears",
        QSqlDriver::TableName));
    tTripGears->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tTripGears->sort(0,Qt::AscendingOrder);
    tTripGears->select();

    QString strDep="select count(id) from Sampled_Fishing_operations WHERE (id_fishing_trip=:id)";

     multiModelI=new MultiModelI(listGears,tRefGears,tTripGears,
         strDep);

    if (tRefZones!=0) delete tRefZones;

     tRefZones = new QSqlQueryModel;
     tRefZones->setQuery(
        "SELECT     ID, Name"
        " FROM         dbo.Ref_Fishing_zones ORDER BY ID ASC"
         );

    if (tTripZones!=0) delete tTripZones;

    tTripZones=new QSqlTableModel();
    tTripZones->setTable(QSqlDatabase().driver()->escapeIdentifier("Sampled_fishing_trips_zones",
        QSqlDriver::TableName));
    tTripZones->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tTripZones->sort(0,Qt::AscendingOrder);
    tTripZones->select();

     multiModelI2=new MultiModelI(listZones,tRefZones,tTripZones,
         strDep);
}

void FrmTrip::initUI()
{
    setHeader();

    this->groupDetails->setVisible(false);
    initPreviewTable(tableView,viewTrips);
    setButtonBox(buttonBox);
    setGroupDetails(groupDetails);
    setNewButton(pushNew);
    setEditButton(pushEdit);
    setRemoveButton(pushRemove);
    setNextButton(pushNext);
    setPreviousButton(pushPrevious);

    setUIPermissions();

    //initializing the container for the readonly!S
    m_lWidgets << cmbSampler;
    m_lWidgets << spinProf;
    m_lWidgets << spinPart;
    m_lWidgets << customDtStart;
    m_lWidgets << customDtEnd;
    m_lWidgets << catchInputCtrl;
    m_lWidgets << textComments;
    m_lWidgets << spinNOE;
    //m_lWidgets << spinNOC;
    //m_lWidgets << cmbFishingZone;
    m_lWidgets << listGears;
    m_lWidgets << listZones;
    m_lWidgets << cmbSite;
    m_lWidgets << pushClear;

    customDtStart->setIsUTC(false);
    customDtStart->setIsAuto(false);

    customDtEnd->setIsUTC(false);
    customDtEnd->setIsAuto(false);

    connect(customDtStart, SIGNAL(isDateTime(bool,int)), m_tDateTime,
        SLOT(amendDateTimeType(bool,int)));

    connect(customDtEnd, SIGNAL(isDateTime(bool,int)), m_tDateTime,
        SLOT(amendDateTimeType(bool,int)));
}

void FrmTrip::initMapper1()
{
    emit blockCatchUISignals(true);

    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
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
        tTrips->relationModel(4)->fieldIndex("Name"));

    cmbSampler->setModel(tTrips->relationModel(5));
    cmbSampler->setModelColumn(
        tTrips->relationModel(5)->fieldIndex("Name"));

    catchInputCtrl->pCmbWeightUnits()->setModel(tTrips->relationModel(12));
    catchInputCtrl->pCmbWeightUnits()->setModelColumn(
        tTrips->relationModel(12)->fieldIndex("Name"));

    catchInputCtrl->pCmbBoxUnits()->setModel(tTrips->relationModel(15));
    catchInputCtrl->pCmbBoxUnits()->setModelColumn(
        tTrips->relationModel(15)->fieldIndex("Name"));

    catchInputCtrl->pCmbUnitUnits()->setModel(tTrips->relationModel(20));
    catchInputCtrl->pCmbUnitUnits()->setModelColumn(
        tTrips->relationModel(20)->fieldIndex("Name"));

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

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1 << mapperStartDt << mapperEndDt;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));

    connect(m_mapperBinderPtr, SIGNAL(defaultValuesRead()), this,
        SLOT(unblockCustomDateCtrls()));

    emit blockCatchUISignals(false);
}

void FrmTrip::blockCustomDateCtrls()
{
    //block signals here because of the rule binder!
    customDtStart->blockSignals(true);
    customDtEnd->blockSignals(true);
}

void FrmTrip::unblockCustomDateCtrls()
{
    //block signals here because of the rule binder!
    customDtStart->blockSignals(false);
    customDtEnd->blockSignals(false);
}

void FrmTrip::initMappers()
{
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;

    mapperStartDt= new QDataWidgetMapper(this);
    mapperStartDt->setModel(m_tDateTime);
    mapperStartDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperStartDt->setItemDelegate(new QItemDelegate(this));
    mapperStartDt->addMapping(customDtStart,2,QString("dateTime").toAscii());

    mapperEndDt= new QDataWidgetMapper(this);
    mapperEndDt->setModel(m_tDateTime);
    mapperEndDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperEndDt->setItemDelegate(new QItemDelegate(this));
    mapperEndDt->addMapping(customDtEnd,2,QString("dateTime").toAscii());
}

void FrmTrip::beforeShow()
{
    this->groupDetails->setVisible(false);
    if (m_sample->bLogBook)
        m_lWidgets << cmbSite;

    setSourceText(lbSource,m_sample->bLogBook);
    initTripModel();

}

bool FrmTrip::reallyApply()
{
    bool bError=false;

    if (!listZones->selectionModel()->hasSelection()){
        emit showError(tr("You must select one or more zones for this trip!"));
        bError=true;
    }else{

        if (!listGears->selectionModel()->hasSelection()){
            emit showError(tr("You must select one or more gears for this trip!"));
            bError=true;
        }else{

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
                            emit showError(tr("Could not write trip in the database!"));
                }else{
                    QModelIndex idd=tTrips->index(tTrips->rowCount()-1,0);

                    //multimodel for gears
                    multiModelI->setParentId(idd.data().toInt());
                    QString strError;
                    if (!multiModelI->list2Model(strError)){
                        emit showError(strError);
                        bError=true;
                    }
                    //multimodel for zones
                    multiModelI2->setParentId(idd.data().toInt());
                    if (!multiModelI2->list2Model(strError)){
                        emit showError(strError);
                        bError=true;
                    }

                }
            }
            }
        }
    }
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(bError);

    emit lockControls(!bError,m_lWidgets);
    if (!bError){
        buttonBox->button(QDialogButtonBox::Apply)->hide();
    }else{
        buttonBox->button(QDialogButtonBox::Apply)->show();
    }

    if (!bError)
        return afterApply();

    return false;
}

void FrmTrip::uI4NewRecord()
{
    genericUI4NewRecord();

    customDtStart->setIsDateTime(true,true,true);
    customDtEnd->setIsDateTime(true,true,true);

    textComments->clear();
    listGears->clearSelection();
    listZones->clearSelection();

    if (cmbSampler->count()> 0) cmbSampler->setCurrentIndex(0);
    if (cmbSite->count()> 0) cmbSite->setCurrentIndex(0);
}

void FrmTrip::createRecord()
{
    //block the signals while introducing record, so we dont have to validate the units mismatch
    emit blockCatchUISignals(true);

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

    tTripGears->setFilter(tr(""));

    uI4NewRecord();//init UI

    //signal for the rule checker default values
    emit addRecord();

    emit blockCatchUISignals(false);
}

void FrmTrip::initTripModel()
{
    if (tTrips!=0) delete tTrips;

    tTrips=new QSqlRelationalTableModel();
    tTrips->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Fishing_Trips"),
        QSqlDriver::TableName));
    tTrips->setRelation(4, QSqlRelation("Ref_Abstract_LandingSite", "ID", "Name"));
    tTrips->setRelation(5, QSqlRelation("Ref_Samplers", "ID", "Name"));
    tTrips->setRelation(12, QSqlRelation("Ref_Units", "ID", "Name"));
    tTrips->setRelation(15, QSqlRelation("Ref_Units", "ID", "Name"));
    tTrips->setRelation(20, QSqlRelation("Ref_Units", "ID", "Name"));
    tTrips->setRelation(22, QSqlRelation("Ref_Fishing_Zones", "ID", "Name"));
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

    if (m_sample->bLogBook){

        if (m_sample->minorStrataId==-1){
            emit showError(tr("Could not identify the minor strata of this frame!"));
            return;
        }

        strQuery=
        "SELECT     TOP (100) PERCENT dbo.Ref_Abstract_LandingSite.ID"
        " FROM         dbo.Ref_Minor_Strata INNER JOIN"
        "                      dbo.FR_Time ON dbo.Ref_Minor_Strata.id_frame_time = dbo.FR_Time.ID INNER JOIN"
        "                      dbo.FR_Frame ON dbo.FR_Time.id_frame = dbo.FR_Frame.ID INNER JOIN"
        "                      dbo.FR_Sub_Frame ON dbo.FR_Frame.ID = dbo.FR_Sub_Frame.id_frame INNER JOIN"
        "                      dbo.FR_GLS2ALS ON dbo.FR_Sub_Frame.ID = dbo.FR_GLS2ALS.id_sub_frame INNER JOIN"
        "                      dbo.Ref_Abstract_LandingSite ON dbo.FR_GLS2ALS.id_abstract_landingsite = dbo.Ref_Abstract_LandingSite.ID"
        " WHERE     (dbo.Ref_Minor_Strata.ID = " + QVariant(m_sample->minorStrataId).toString() + " ) AND (dbo.FR_GLS2ALS.id_gls ="
        "                  (SELECT     id_gls"
        "                    FROM          dbo.Ref_Minor_Strata AS Ref_Minor_Strata_1"
        "                    WHERE      (ID = " + QVariant(m_sample->minorStrataId).toString() + ")))"
        ;//for getting all the boats on the frame, just remove the last condition

        query.prepare(strQuery);
        if (!query.exec()){
            emit showError(tr("Could not obtain filter for Landing Sites!"));
        return;
        }

        QString strFilter("");
        while (query.next()) {
            strFilter.append("ID=" + query.value(0).toString());
            strFilter.append(" OR ");
        }
        if (!strFilter.isEmpty())
            strFilter=strFilter.remove(strFilter.size()-QString(" OR ").length(),QString(" OR ").length());

        tTrips->relationModel(4)->setFilter(strFilter);

    }else{

        strQuery=
        "SELECT     id_abstract_LandingSite"
        " FROM         dbo.Sampled_Cell"
        " WHERE     (ID = :id)"
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
        strFilter.append("ID=" + query.value(0).toString());

        if (!strFilter.isEmpty()){
            tTrips->relationModel(4)->setFilter(strFilter);
        }

    }

    initMapper1();
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

void FrmTrip::editFinished()
{
    setPreviewQuery();
    pushEdit->setChecked(false);
    pushNew->setEnabled(!pushEdit->isChecked());
    pushRemove->setEnabled(!pushEdit->isChecked());
    emit lockControls(true,m_lWidgets);
}

void FrmTrip::onEditLeave(const bool bFinished, const bool bDiscarded)
{
    if (bFinished){
        editFinished();
    }
}

bool FrmTrip::applyChanges()
{
    bool bError=false;

    if (!listZones->selectionModel()->hasSelection()){
        emit showError(tr("You must select one or more zones for this trip!"));
        bError=true;
    }else{

        if (!listGears->selectionModel()->hasSelection()){
            emit showError(tr("You must select one or more gears for this trip!"));
            bError=true;
        }else{

            QString strError;
            if (!checkDependantDates(tTrips->tableName(), customDtStart->dateTime(),
                customDtEnd->dateTime(),tTrips->tableName(),m_sample->tripId, strError))
            {
                emit showError(strError);
                bError=true;
            }else{

                int startIdx=mapperStartDt->currentIndex();
                int endIdx=mapperEndDt->currentIndex();

                //Setting the datetime type changes here!
                bool bDate, bTime;
                int typeID;

                customDtStart->getIsDateTime(bDate,bTime);
                if (!m_tDateTime->getDateTimeType(true,bTime,typeID)){
                    return false;
                }
                m_tDateTime->setData(m_tDateTime->index(0,3),typeID);

                customDtEnd->getIsDateTime(bDate,bTime);
                if (!m_tDateTime->getDateTimeType(true,bTime,typeID)){
                    return false;
                }
                m_tDateTime->setData(m_tDateTime->index(1,3),typeID);

                bError=!submitDates(mapperStartDt, mapperEndDt);

                if (!bError){
                    mapperStartDt->setCurrentIndex(startIdx);
                    mapperEndDt->setCurrentIndex(endIdx);

                    int cur= mapper1->currentIndex();
                    bError=!submitMapperAndModel(mapper1);
                    if (!bError){
                        mapper1->setCurrentIndex(cur);

                        if (tTrips->rowCount()!=1) return false;
                        QModelIndex idd=tTrips->index(0,0);

                        //Comiting Sampled_Fishing_Trips_Gears
                        multiModelI->setParentId(idd.data().toInt());
                        QString strError;
                        if (!multiModelI->list2Model(strError,false)){
                            emit showError(strError);
                            bError=true;
                        }

                        //Comiting Sampled_Fishing_Trips_Zones
                        multiModelI2->setParentId(idd.data().toInt());
                        if (!multiModelI2->list2Model(strError,false)){
                            emit showError(strError);
                            bError=true;
                        }

                    }// mapper 1 submission
                } else emit showError(tr("Could not edit dates in the database!"));
            }//check dependant dates
        }//if list gears has selection
    }//if list zones has selection

    if (!bError) emit editLeave(true,false);
    return !bError;
}

