#include <QTest>
//#include "globaldefs.h"
#include "frmtrip.h"

FrmTrip::FrmTrip(Sample* inSample, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
PreviewTab(5,inSample,inTDateTime,tr("Fishing Trip"),parent, flags){

    setupUi(this);

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

/*
    QModelIndex idx=viewVessel->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this vessel!"));
        return;
    }

    QString id=idx.data().toString();

    tAVessel->setFilter(tr("Abstract_Sampled_Vessels.ID=")+id);
    if (tAVessel->rowCount()!=1)
        return;

    mapper1->toLast();

    if (!m_sample->bLogBook){

        //id_Sampled_Cell_Vessels
        idx=viewVessel->index(index.row(),3);
        if (!idx.isValid()){
            emit showError (tr("Could not preview this vessel!"));
            return;
        }

        id=idx.data().toString();

        tCellVessels->setFilter(tr("ID=")+id);
        if (tCellVessels->rowCount()!=1)
            return;

        mapper2->toLast();
    }

    pushNext->setEnabled(true);
*/
}

void FrmTrip::setPreviewQuery()
{
    if (m_sample==0) return;
    QString strQuery=

    tr("SELECT     dbo.Sampled_Fishing_Trips.ID, dbo.Ref_Samplers.Name, CONVERT(CHAR(10), F1.Date_Local, 103) AS [Start Date], CONVERT(VARCHAR(8), F1.Date_Local, ") +
    tr("                      108) AS [Start Time], CONVERT(CHAR(10), F2.Date_Local, 103) AS [End Date], CONVERT(VARCHAR(8), F2.Date_Local, 108) AS [End Time] ") +
    tr(" FROM         dbo.Sampled_Fishing_Trips INNER JOIN") +
    tr("                      dbo.Ref_Samplers ON dbo.Sampled_Fishing_Trips.id_sampler = dbo.Ref_Samplers.ID INNER JOIN") +
    tr("                      dbo.GL_Dates AS F1 ON dbo.Sampled_Fishing_Trips.id_start_dt = F1.ID INNER JOIN") +
    tr("                      dbo.GL_Dates AS F2 ON dbo.Sampled_Fishing_Trips.id_end_dt = F2.ID") +
    tr(" WHERE     (dbo.Sampled_Fishing_Trips.id_abstract_sampled_vessels = 1)")
    ;

    QSqlQuery query;
    query.prepare( strQuery );
    query.bindValue(0,1);
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
    m_lWidgets << cmbSite;
    m_lWidgets << cmbSampler;
    m_lWidgets << spinProf;
    m_lWidgets << spinPart;
    m_lWidgets << customDtStart;
    m_lWidgets << customDtEnd;
    m_lWidgets << spinNOE;
    m_lWidgets << spinNOC;
    m_lWidgets << spinCE;
    m_lWidgets << spinCC;
    m_lWidgets << cmbWeight;
    m_lWidgets << spinCBE;
    m_lWidgets << spinCBC;
    m_lWidgets << spinWeight;
    m_lWidgets << cmbBoxes;
    m_lWidgets << textComments;

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
    for (int i=4; i < 16; ++i){
        lOthers << i;
    }
    QList<int> lText;
    lText << 16;
    nullDellegate=new NullRelationalDelegate(lOthers,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbSite->setModel(tTrips->relationModel(4));
    cmbSite->setModelColumn(
        tTrips->relationModel(4)->fieldIndex(tr("Name")));

    cmbSampler->setModel(tTrips->relationModel(5));
    cmbSampler->setModelColumn(
        tTrips->relationModel(5)->fieldIndex(tr("Name")));

    cmbWeight->setModel(tTrips->relationModel(12));
    cmbWeight->setModelColumn(
        tTrips->relationModel(12)->fieldIndex(tr("Name")));

    cmbBoxes->setModel(tTrips->relationModel(15));
    cmbBoxes->setModelColumn(
        tTrips->relationModel(15)->fieldIndex(tr("Name")));

    mapper1->addMapping(cmbSite, 4);
    mapper1->addMapping(cmbSampler, 5);
    mapper1->addMapping(spinProf, 6);
    mapper1->addMapping(spinPart, 7);
    mapper1->addMapping(spinNOE, 8);
    mapper1->addMapping(spinNOC, 9);
    mapper1->addMapping(spinCE, 10);
    mapper1->addMapping(spinCC, 11);
    mapper1->addMapping(cmbWeight, 12);
    mapper1->addMapping(spinCBE, 13);
    mapper1->addMapping(spinCBC, 14);
    mapper1->addMapping(cmbBoxes, 15);
    mapper1->addMapping(textComments,16);
    mapper1->addMapping(cmbBoxes, 17);
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
    setSourceText(lbSource);
    initTripModel();
}

bool FrmTrip::onButtonClick(QAbstractButton* button)
{/*
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tAVessel->revertAll();
        if (tCellVessels!=0) tCellVessels->revertAll();
        return true;

    } else if (buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){

        bool bError=false;

        if (mapper1->submit()){

            //setting the vessel source
            QSqlQuery query;
            query.prepare( tr("SELECT     ID") +
                           tr(" FROM         dbo.Ref_Source") +
                           tr(" WHERE     (Name = :name)") );
            query.bindValue(0,qApp->translate("frame", (m_sample->bLogBook? strLogbook: strSampling) ));

            if (!query.exec() || query.numRowsAffected()!=1){
                emit showError(tr("Could not obtain filter for Vessels!"));
                return false;
            }
            query.first();

            while(tAVessel->canFetchMore())
                tAVessel->fetchMore();

            QModelIndex idx=tAVessel->index(tAVessel->rowCount()-1,1);
            if (!idx.isValid()){
                emit showError(tr("Could not create a record for this vessel!"));
                return false;
            }

            tAVessel->setData(idx,query.value(0).toInt());

            int id_cell, id_strata;
            if (!comitNonAbstractVessels(m_sample->bLogBook,id_cell,id_strata))
            {
                if (tCellVessels->lastError().type()!=QSqlError::NoError)
                    emit showError(tCellVessels->lastError().text());
                else if (tStrataVessels->lastError().type()!=QSqlError::NoError)
                    emit showError(tStrataVessels->lastError().text());
                bError=true;
            }else{

                QModelIndex idx=tAVessel->index(tAVessel->rowCount()-1,5);
                if (!idx.isValid()) return false;
                tAVessel->setData(idx,id_cell);
                idx=tAVessel->index(tAVessel->rowCount()-1,6);
                if (!idx.isValid()) return false;
                tAVessel->setData(idx,id_strata);

                bError=!
                    tAVessel->submitAll();
                if (bError){
                    if (tAVessel->lastError().type()!=QSqlError::NoError)
                        emit showError(tAVessel->lastError().text());
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

    mapper1->toLast();
    mapper2->toLast();*/
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
    tTrips->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tTrips->sort(0,Qt::AscendingOrder);
    tTrips->select();

    setPreviewModel(tTrips);
}

void FrmTrip::filterModel4Combo()
{
    /*
    QSqlQuery query;
    QString strQuery;

    if (!m_sample->bLogBook){

        strQuery =
        tr("SELECT     dbo.Ref_Vessels.VesselID") +
        tr(" FROM         dbo.FR_ALS2Vessel INNER JOIN") +
        tr("                      dbo.Ref_Vessels ON dbo.FR_ALS2Vessel.vesselID = dbo.Ref_Vessels.VesselID") +
        tr(" WHERE     (dbo.FR_ALS2Vessel.id_sub_frame =") +
        tr("                          (SELECT     ID") +
        tr("                            FROM          dbo.FR_Sub_Frame") +
        tr("                            WHERE      (Type =") +
        tr("                                                       (SELECT     ID") +
        tr("                                                         FROM          dbo.Ref_Frame") +
        tr("                                                         WHERE      (Name = 'root'))) AND (id_frame =")+ QVariant(m_sample->frameId).toString() + tr("))) AND (dbo.FR_ALS2Vessel.id_abstract_landingsite =") +
        tr("                          (SELECT     id_abstract_LandingSite") +
        tr("                            FROM          dbo.Sampled_Cell") +
        tr("                            WHERE      (ID = ")+ QVariant(m_sample->cellId).toString() + tr("))) AND (dbo.FR_ALS2Vessel.vesselID NOT IN") +
        tr("                          (SELECT     VesselID") +
        tr("                            FROM          dbo.Abstract_Changes_Temp_Vessel") +
        tr("                            WHERE      (id_cell = ")+ QVariant(m_sample->cellId).toString() + tr(") AND (To_LS =") +
        tr("                                                       (SELECT     ID") +
        tr("                                                         FROM          dbo.Ref_Abstract_LandingSite") +
        tr("                                                         WHERE      (Name = 'outside')))))") +
        tr(" UNION") +
        tr(" SELECT     Ref_Vessels_1.VesselID") +
        tr(" FROM         dbo.FR_ALS2Vessel AS FR_ALS2Vessel_1 INNER JOIN")+
        tr("                      dbo.Ref_Vessels AS Ref_Vessels_1 ON FR_ALS2Vessel_1.vesselID = Ref_Vessels_1.VesselID")+
        tr(" WHERE     (Ref_Vessels_1.VesselID IN")+
        tr("                          (SELECT     VesselID")+
        tr("                            FROM          dbo.Abstract_Changes_Temp_Vessel AS Abstract_Changes_Temp_Vessel_1")+
        tr("                            WHERE      (id_cell = ")+ QVariant(m_sample->cellId).toString() + tr(") AND (To_LS =")+
        tr("                                                       (SELECT     id_abstract_LandingSite")+
        tr("                                                         FROM          dbo.Sampled_Cell AS Sampled_Cell_1")+
        tr("                                                         WHERE      (ID = ")+ QVariant(m_sample->cellId).toString() + tr(")))))")
            ;

    }else{
        //TODO: update from temporary frame
        strQuery =
        tr("SELECT     FR_ALS2Vessel_1.vesselID, dbo.FR_GLS2ALS.id_gls") +
        tr(" FROM         dbo.FR_ALS2Vessel INNER JOIN") +
        tr("                      dbo.FR_GLS2ALS ON dbo.FR_ALS2Vessel.ID = dbo.FR_GLS2ALS.ID INNER JOIN") +
        tr("                      dbo.FR_ALS2Vessel AS FR_ALS2Vessel_1 ON dbo.FR_ALS2Vessel.ID = FR_ALS2Vessel_1.ID INNER JOIN") +
        tr("                      dbo.Ref_Vessels ON dbo.FR_ALS2Vessel.vesselID = dbo.Ref_Vessels.VesselID AND FR_ALS2Vessel_1.vesselID = dbo.Ref_Vessels.VesselID") +
        tr(" WHERE     (dbo.FR_ALS2Vessel.id_sub_frame =") +
        tr("                          (SELECT     ID") +
        tr("                            FROM          dbo.FR_Sub_Frame") +
        tr("                            WHERE      (Type =") +
        tr("                                                       (SELECT     ID") +
        tr("                                                         FROM          dbo.Ref_Frame") +
        tr("                                                         WHERE      (Name = 'root'))) AND (id_frame =")+ QVariant(m_sample->frameId).toString() + tr("))) AND") +
        tr(" (dbo.FR_GLS2ALS.id_gls=") +
        tr(" (SELECT     id_gls") +
        tr(" FROM         dbo.Ref_Minor_Strata") +
        tr(" WHERE     (ID = ")+ QVariant(m_sample->minorStrataId).toString() + tr(")))")
         ;
    }

    query.prepare(strQuery);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Vessels!"));
        return;
    }

    QString strFilter(tr(""));
     while (query.next()) {
        strFilter.append(tr("VesselID=") + query.value(0).toString());
        strFilter.append(tr(" OR "));
     }
     if (!strFilter.isEmpty())
         strFilter=strFilter.remove(strFilter.size()-tr(" OR ").length(),tr(" OR ").length());

    tAVessel->relationModel(2)->setFilter(strFilter);
*/
        //first we set the relation; then we create a mapper and assign the (amended) model to the mapper;
    initMapper1();
}

bool FrmTrip::updateSample()
{/*
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //updating the sample structure
    QModelIndex idx=viewVessel->index(tableView->selectionModel()->currentIndex().row(),0);

    //TODO: update the vessel here
    //m_sample->cellId=idx.data().toInt();*/
    return true;
}

bool FrmTrip::getNextLabel(QString& strLabel)
{/*
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //sending the name
    QModelIndex idx=viewVessel->index(tableView->selectionModel()->currentIndex().row(),1);
    strLabel=idx.data().toString();*/
    return true;
}
