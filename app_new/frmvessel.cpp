#include <QTest>
#include "globaldefs.h"
#include "frmvessel.h"

FrmVessel::FrmVessel(Sample* inSample, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
PreviewTab(4,inSample,inTDateTime,tr("Vessel"),parent, flags){

    setupUi(this);

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    connect(toolButton, SIGNAL(clicked()), this,
        SLOT(onShowFrameDetails()));

    tAVessel=0;
    viewVessel=0;
    mapper1=0;
    nullDelegate=0;

    initModels();
    initUI();
    initMappers();
}

FrmVessel::~FrmVessel()
{
    if (tAVessel!=0) delete tAVessel;
    if (viewVessel!=0) delete viewVessel;
    if (nullDelegate!=0) delete nullDelegate;
    if (mapper1!=0) delete mapper1;
}

void FrmVessel::onShowFrameDetails()
{
/*
    if (!m_selectedIdx.isValid()){
        emit showError(tr("You must select one cell!"));
        return;
    }

    QModelIndex idx=viewCell->index(m_selectedIdx.row(),0);
    if (m_sample->cellId!=idx.data().toInt()){
        emit showError(tr("We only support changes in the last inserted cell!"));
        return;
    }

    QList<int> blackList;
    blackList << 1 << 2;
    emit showFrameDetails(FrmFrameDetails::VIEW,FrmFrameDetails::TEMPORARY_ALL,
        m_sample, blackList, false);*/
}

void FrmVessel::previewRow(QModelIndex index)
{/*
    m_selectedIdx=index;//stores the index
    emit submitted(this->m_index,true);

    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->hide();

    QModelIndex idx=viewCell->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }

    QString id=idx.data().toString();

    tSampCell->setFilter(tr("Sampled_Cell.ID=")+id);
    if (tSampCell->rowCount()!=1)
        return;

    mapper1->toLast();

    //Now fix the dates
    idx=tSampCell->index(0,1);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }
    idx=tSampCell->index(0,2);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }
    QString strStartDt=idx.data().toString();

    idx=tSampCell->index(0,3);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
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
    pushNext->setEnabled(true);*/
}

void FrmVessel::setPreviewQuery()
{/*
    viewCell->setQuery(
tr("SELECT     TOP (100) PERCENT dbo.Sampled_Cell.ID, dbo.Ref_Abstract_LandingSite.Name as [Landing Site], CONVERT(CHAR(10), F1.Date_Local, 103) AS [Start Date], CONVERT(CHAR(10), ") +
tr("                      F2.Date_Local, 103) AS [End Date] ") +
tr("FROM         dbo.Sampled_Cell INNER JOIN") +
tr("                      dbo.GL_Dates AS F1 ON dbo.Sampled_Cell.id_start_date = F1.ID INNER JOIN") +
tr("                      dbo.GL_Dates AS F2 ON dbo.Sampled_Cell.id_end_date = F2.ID INNER JOIN") +
tr("                      dbo.Ref_Abstract_LandingSite ON dbo.Ref_Abstract_LandingSite.ID = dbo.Sampled_Cell.id_abstract_LandingSite ") +
tr("WHERE     (dbo.Sampled_Cell.id_Minor_Strata = ")  + QVariant(m_sample->minorStrataId).toString() + tr(") ") +
tr("ORDER BY dbo.Sampled_Cell.ID DESC")
);

    tableView->hideColumn(0);
    resizeToVisibleColumns(tableView);*/
}

void FrmVessel::initModels()
{
    if (viewVessel!=0) delete viewVessel;
    viewVessel = new QSqlQueryModel;
}

void FrmVessel::initUI()
{
    setHeader();

    connect(this, SIGNAL(hideFrameDetails(bool)), toolButton,
        SLOT(setEnabled(bool)));

    toolButton->setEnabled(false);

    this->groupDetails->setVisible(false);

    setPreviewTable(tableView);
    tableView->setModel(viewVessel);
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->verticalHeader()->hide();
    tableView->setSelectionMode(
        QAbstractItemView::SingleSelection);
    tableView->horizontalHeader()->setClickable(false);
    tableView->horizontalHeader()->setFrameStyle(QFrame::NoFrame);

    //initializing the container for the readonly!S
    m_lWidgets << cmbVessel;
    m_lWidgets << cmbStatus;
    m_lWidgets << cmbOrigin;
    m_lWidgets << textComments;
    m_lWidgets << spinET;
    m_lWidgets << spinCT;

    pushNext->setEnabled(false);
}

void FrmVessel::initMapper1()
{
    if (mapper1!=0) delete mapper1;
    mapper1= new QDataWidgetMapper(this);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    mapper1->setModel(tAVessel);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lOthers;
    lOthers << 2 << 3 << 4 << 5 << 6;
    QList<int> lText;
    lText << 7;
    nullDellegate=new NullRelationalDelegate(lOthers,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbVessel->setModel(tAVessel->relationModel(2));
    cmbVessel->setModelColumn(
        tAVessel->relationModel(2)->fieldIndex(tr("Name")));

    cmbOrigin->setModel(tAVessel->relationModel(3));
    cmbOrigin->setModelColumn(
        tAVessel->relationModel(3)->fieldIndex(tr("Name")));

    cmbStatus->setModel(tAVessel->relationModel(4));
    cmbStatus->setModelColumn(
        tAVessel->relationModel(4)->fieldIndex(tr("Name")));

    mapper1->addMapping(cmbVessel, 2);
    mapper1->addMapping(cmbOrigin, 3);
    mapper1->addMapping(cmbStatus, 4);

    //mapper1->addMapping(spinET, 5);
    //mapper1->addMapping(spinCT, 6);

    mapper1->addMapping(textComments,7);
}

void FrmVessel::initMappers()
{/*

    mapperStartDt= new QDataWidgetMapper(this);
    mapperStartDt->setModel(m_tDateTime);
    mapperStartDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperStartDt->setItemDelegate(new QItemDelegate(this));
    mapperStartDt->addMapping(customDtStart,3,tr("dateTime").toAscii());

    mapperEndDt= new QDataWidgetMapper(this);
    mapperEndDt->setModel(m_tDateTime);
    mapperEndDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperEndDt->setItemDelegate(new QItemDelegate(this));
    mapperEndDt->addMapping(customDtEnd,3,tr("dateTime").toAscii());*/
}

void FrmVessel::beforeShow()
{
    this->groupDetails->setVisible(false);
    initVesselModel();
}

bool FrmVessel::onButtonClick(QAbstractButton* button)
{/*
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tSampCell->revertAll();
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
                QModelIndex idxStart=tSampCell->index(tSampCell->rowCount()-1,2);
                if (idxStart.isValid()){
                    tSampCell->setData(idxStart,idStart);
                }else bError=true;
            }else bError=true;

            int idEnd;
            if (getDtId(endIdx,idEnd)){
                QModelIndex idxEnd=tSampCell->index(tSampCell->rowCount()-1,3);
                if (idxEnd.isValid()){
                    tSampCell->setData(idxEnd,idEnd);
                }else bError=true;
            }else bError=true;

            if (!bError){
                if (mapper1->submit()){
                    bError=!
                        tSampCell->submitAll();
                    if (bError){
                        if (tSampCell->lastError().type()!=QSqlError::NoError)
                            emit showError(tSampCell->lastError().text());
                        else
                            emit showError(tr("Could not write cell in the database!"));
                    }mapper1->toLast();
                }else bError=true;
            }
        }
        button->setEnabled(bError);

        emit lockControls(!bError,m_lWidgets);
        if (!bError){
            buttonBox->button(QDialogButtonBox::Apply)->hide();
        }else{
            buttonBox->button(QDialogButtonBox::Apply)->show();
        }

        if (!bError){
            setPreviewQuery();
            tableView->selectRow(0);
            tSampCell->select();
            toolButton->setEnabled(true);
            QModelIndex idx=tSampCell->index(tSampCell->rowCount()-1,0);
            if (!idx.isValid()) return false;
            m_sample->cellId=idx.data().toInt();//updating the id here, because of the frame details
            mapper1->toLast();
        }
        return !bError;
    }else return false;*/

    return false;
}

void FrmVessel::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(false,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->show();

    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);

    textComments->clear();
    cmbOrigin->setCurrentIndex(-1);
    cmbStatus->setCurrentIndex(-1);
    cmbVessel->setCurrentIndex(-1);

    toolButton->setEnabled(false);
}

void FrmVessel::createRecord()
{
    genericCreateRecord();

    mapper1->toLast();

    //TODO: insert the other models
    /*
    while(tAVessel->canFetchMore())
        tAVessel->fetchMore();

    QModelIndex idx=tAVessel->index(tAVessel->rowCount()-1,1);
    tAVessel->setData(idx,m_sample->minorStrataId);//id_minor_strata
    */

    uI4NewRecord();//init UI*/
}
/*
void FrmVessel::initCellModel()
{
    if (tSampCell!=0) delete tSampCell;

    tSampCell=new QSqlRelationalTableModel();
    tSampCell->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Cell"),
        QSqlDriver::TableName));
    tSampCell->setRelation(4, QSqlRelation(tr("Ref_Abstract_LandingSite"), tr("ID"), tr("Name")));
    tSampCell->relationModel(4)->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tSampCell->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tSampCell->select();

    setPreviewModel(tSampCell);
}
*/

void FrmVessel::initVesselModel()
{
    if (tAVessel!=0) delete tAVessel;

    tAVessel=new QSqlRelationalTableModel();
    tAVessel->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Abstract_Sampled_Vessels"),
        QSqlDriver::TableName));
    tAVessel->setRelation(2, QSqlRelation(tr("Ref_Vessels"), tr("VesselID"), tr("Name")));
    tAVessel->setRelation(3, QSqlRelation(tr("Ref_Sample_Origin"), tr("id_sample_origin"), tr("Name")));
    tAVessel->setRelation(4, QSqlRelation(tr("Ref_Sample_Status"), tr("id_sample_status"), tr("Name")));

    tAVessel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tAVessel->select();

    setPreviewModel(tAVessel);
}

void FrmVessel::filterModel4Combo()
{
    QString strQuery =
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
tr("                            FROM          dbo.Changes_Temp_Vessel") +
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
tr("                            FROM          dbo.Changes_Temp_Vessel AS Changes_Temp_Vessel_1")+
tr("                            WHERE      (id_cell = ")+ QVariant(m_sample->cellId).toString() + tr(") AND (To_LS =")+
tr("                                                       (SELECT     id_abstract_LandingSite")+
tr("                                                         FROM          dbo.Sampled_Cell AS Sampled_Cell_1")+
tr("                                                         WHERE      (ID = ")+ QVariant(m_sample->cellId).toString() + tr(")))))")
    ;

    QSqlQuery query;
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
    //first we set the relation; then we create a mapper and assign the (amended) model to the mapper;*/
    initMapper1();
}

bool FrmVessel::updateSample()
{/*
    //updating the sample structure
    QModelIndex idx=viewCell->index(m_selectedIdx.row(),0);
    if (!idx.isValid()) return false;
    m_sample->cellId=idx.data().toInt();*/
    return true;
}

bool FrmVessel::getNextLabel(QString& strLabel)
{/*
    //sending the name
    QModelIndex idx=viewCell->index(m_selectedIdx.row(),1);
    if (!idx.isValid()) return false;
    strLabel=idx.data().toString();*/
    return true;
}
