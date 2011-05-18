#include <QTest>
#include "globaldefs.h"
#include "frmvessel.h"

FrmVessel::FrmVessel(Sample* inSample, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
PreviewTab(4,inSample,inTDateTime,tr("Vessel"),parent, flags){

    setupUi(this);

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    tAVessel=0;
    tCellVessels=0;
    tStrataVessels=0;
    viewVessel=0;
    mapper1=0;
    mapper2=0;
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
    if (mapper2!=0) delete mapper2;
    if (tCellVessels!=0) delete tCellVessels;
    if (tStrataVessels!=0) delete tStrataVessels;
}

void FrmVessel::previewRow(QModelIndex index)
{
    m_selectedIdx=index;//stores the index
    //emit submitted(this->m_index,true);

    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->hide();

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
}

void FrmVessel::setPreviewQuery()
{
    if (m_sample==0) return;
    QString strQuery;
    int id;
    if (m_sample->bLogBook){//logbook

        strQuery=
        tr("                SELECT     dbo.Abstract_Sampled_Vessels.ID, dbo.Ref_Vessels.Name, dbo.Ref_Sample_Status.name AS Status") +
        tr(" FROM         dbo.Abstract_Sampled_Vessels INNER JOIN") +
        tr("                      dbo.Ref_Vessels ON dbo.Abstract_Sampled_Vessels.VesselID = dbo.Ref_Vessels.VesselID INNER JOIN") +
        tr("                      dbo.Sampled_Strata_Vessels ON dbo.Abstract_Sampled_Vessels.id_Sampled_Strata_Vessels = dbo.Sampled_Strata_Vessels.ID INNER JOIN") +
        tr("                      dbo.Ref_Sample_Status ON dbo.Abstract_Sampled_Vessels.id_sample_status = dbo.Ref_Sample_Status.ID") +
        tr("                      WHERE     (dbo.Sampled_Strata_Vessels.id_minor_strata = :id)") +
        tr("                      ORDER BY dbo.Abstract_Sampled_Vessels.ID DESC")
        ;
        id=m_sample->minorStrataId;

    } else{//sampling
        strQuery=
         tr("            SELECT     dbo.Abstract_Sampled_Vessels.ID, dbo.Ref_Vessels.Name, dbo.Ref_Sample_Status.name AS Status, id_Sampled_Cell_Vessels") +
         tr(" FROM         dbo.Abstract_Sampled_Vessels INNER JOIN") +
         tr("                     dbo.Sampled_Cell_Vessels ON dbo.Abstract_Sampled_Vessels.id_Sampled_Cell_Vessels = dbo.Sampled_Cell_Vessels.ID INNER JOIN") +
         tr("                     dbo.Ref_Vessels ON dbo.Abstract_Sampled_Vessels.VesselID = dbo.Ref_Vessels.VesselID INNER JOIN") +
         tr("                     dbo.Ref_Sample_Status ON dbo.Abstract_Sampled_Vessels.id_sample_status = dbo.Ref_Sample_Status.ID") +
         tr("             WHERE     (dbo.Sampled_Cell_Vessels.id_cell_vessel_types = :id)") +
         tr("                      ORDER BY dbo.Abstract_Sampled_Vessels.ID DESC")
         ;
        id=m_sample->vesselTypeId;
    }

    QSqlQuery query;
    query.prepare( strQuery );
    query.bindValue(0,id);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Vessels!"));
        return;
    }

    viewVessel->setQuery(query);

    tableView->hideColumn(0);
    tableView->hideColumn(3);
    resizeToVisibleColumns(tableView);
}

void FrmVessel::initModels()
{
    if (viewVessel!=0) delete viewVessel;
    viewVessel = new QSqlQueryModel;

    if (tCellVessels!=0) delete tCellVessels;

     tCellVessels = new QSqlTableModel;
     tCellVessels->setTable(tr("Sampled_Cell_Vessels"));
     tCellVessels->setEditStrategy(QSqlTableModel::OnManualSubmit);
     tCellVessels->sort(0,Qt::AscendingOrder);
     tCellVessels->select();

    if (tStrataVessels!=0) delete tStrataVessels;

     tStrataVessels = new QSqlTableModel;
     tStrataVessels->setTable(tr("Sampled_Strata_Vessels"));
     tStrataVessels->setEditStrategy(QSqlTableModel::OnManualSubmit);
     tStrataVessels->sort(0,Qt::AscendingOrder);
     tStrataVessels->select();

}

void FrmVessel::initUI()
{
    setHeader();

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

    if (tAVessel==0) return;

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
    mapper1->addMapping(textComments,7);
}

void FrmVessel::initMappers()
{
    if (mapper2!=0) delete mapper2;
    mapper2= new QDataWidgetMapper(this);
    mapper2->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper2->setModel(tCellVessels);
    mapper2->addMapping(spinET, 2);
    mapper2->addMapping(spinCT, 3);
    mapper2->toLast();
}

void FrmVessel::beforeShow()
{
    this->groupDetails->setVisible(false);
    this->groupFT->setVisible(!m_sample->bLogBook);
    setSourceText(lbSource);
    initVesselModel();
}

bool FrmVessel::comitNonAbstractVessels(const bool bLogbook, int& id_Sampled_Cell_Vessels, int& id_Sampled_Strata_Vessels)
{
    QSqlQuery query;

    if (bLogbook)
    {
        query.prepare( tr("SELECT     ID FROM Sampled_Cell_Vessels WHERE id_cell_vessel_types=") +
                       tr(" (SELECT ID FROM         Ref_Vessel_Types") +
                       tr(" WHERE     (Name = 'n/a'))") );

        if (!query.exec() || query.numRowsAffected()!=1){
            emit showError(tr("Could not create a non abstract record for this vessel (logbook)!"));
            return false;
        }
        query.first();
        id_Sampled_Cell_Vessels=query.value(0).toInt();
        return comitStrataVessels(id_Sampled_Strata_Vessels);
    }else{
        query.prepare( tr("SELECT     ID FROM Sampled_Strata_Vessels WHERE id_minor_strata=") +
                       tr("( SELECT ID FROM         Ref_Minor_Strata") +
                       tr(" WHERE     (Name = 'n/a') )") );

        if (!query.exec() || query.numRowsAffected()!=1){
            emit showError(tr("Could not create a non abstract record for this vessel (sampled)!"));
            return false;
        }
        query.first();
        id_Sampled_Strata_Vessels=query.value(0).toInt();
        return comitCellVessels(id_Sampled_Cell_Vessels);
    }

    return true;
}

bool FrmVessel::comitCellVessels(int& id)
{
    while(tCellVessels->canFetchMore())
        tCellVessels->fetchMore();

    //We dont need to introduce a record here, cause it has been done with the map
    QModelIndex idx=tCellVessels->index(tCellVessels->rowCount()-1,1);
    if (!idx.isValid()) return false;
    tCellVessels->setData(idx,m_sample->vesselTypeId);

    //submit
    if (!mapper2->submit()) return false;
    if (!tCellVessels->submitAll()) return false;

    //and get the id
    idx=tCellVessels->index(tCellVessels->rowCount()-1,0);
    if (!idx.isValid()) return false;
    id=idx.data().toInt();

    return true;
}

bool FrmVessel::comitStrataVessels(int& id)
{
    insertRecordIntoModel(tStrataVessels);

    while(tStrataVessels->canFetchMore())
        tStrataVessels->fetchMore();

    QModelIndex idx=tStrataVessels->index(tStrataVessels->rowCount()-1,1);
    if (!idx.isValid()) return false;
    tStrataVessels->setData(idx,m_sample->minorStrataId);

    if (!tStrataVessels->submitAll()) return false;

    idx=tStrataVessels->index(tStrataVessels->rowCount()-1,0);
    id=idx.data().toInt();

    return true;
}

bool FrmVessel::onButtonClick(QAbstractButton* button)
{
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
            return afterApply() /*&& lockLastVessel()*/;

    }//else return false;

    mapper1->toLast();
    mapper2->toLast();
    return false;
}

bool FrmVessel::lockLastVessel()
{
    QSqlQuery query;
    QString strQuery=
    tr(" SELECT     TOP (1) VesselID") +
    tr(" FROM         dbo.Abstract_Sampled_Vessels") +
    tr(" ORDER BY ID DESC");

    query.prepare(strQuery);
    if (!query.exec() || query.numRowsAffected()!=1){
        emit showError(tr("Could not obtain the last inserted vessel!"));
        return false;
    }
    query.first();

    return lockVessel(query.value(0).toInt());
}

bool FrmVessel::lockVessel(const int vesselId)
{
    QSqlQuery query;
    QString strQuery=

    tr("UPDATE Abstract_Changes_Temp_Vessel") +
    tr(" SET hasRecords=1") +
    tr(" WHERE (id_cell=:cellId) and (VesselId=:vesselId)")
    ;

    query.prepare(strQuery);
    query.bindValue(0,m_sample->cellId);
    query.bindValue(1,vesselId);
    if (!query.exec()){
        emit showError(tr("Could not lock vessels!!"));
        return false;
    }

    return true;
}

void FrmVessel::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(false,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->show();

    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);

    textComments->clear();
}

void FrmVessel::createRecord()
{
    genericCreateRecord();
    mapper1->toLast();

    if (!m_sample->bLogBook){
        if (tCellVessels==0) return;
        if (mapper2==0) return;

        insertRecordIntoModel(tCellVessels);
        mapper2->toLast();
    }

    uI4NewRecord();//init UI*/
}

void FrmVessel::initVesselModel()
{
    if (tAVessel!=0) delete tAVessel;

    tAVessel=new QSqlRelationalTableModel();
    tAVessel->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Abstract_Sampled_Vessels"),
        QSqlDriver::TableName));
    tAVessel->setRelation(2, QSqlRelation(tr("Ref_Vessels"), tr("VesselID"), tr("Name")));
    tAVessel->setRelation(3, QSqlRelation(tr("Ref_Sample_Origin"), tr("ID"), tr("Name")));
    tAVessel->setRelation(4, QSqlRelation(tr("Ref_Sample_Status"), tr("ID"), tr("Name")));
    tAVessel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tAVessel->sort(0,Qt::AscendingOrder);
    tAVessel->select();

    setPreviewModel(tAVessel);
}

void FrmVessel::filterModel4Combo()
{
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

        //first we set the relation; then we create a mapper and assign the (amended) model to the mapper;
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
