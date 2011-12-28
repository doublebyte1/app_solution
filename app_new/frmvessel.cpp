#include <QTest>
#include "globaldefs.h"
#include "frmvessel.h"

FrmVessel::FrmVessel(RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
PreviewTab(4,inRoleDef,inSample,inTDateTime,tr("Vessel"),ruleCheckerPtr,parent,flags){

    setupUi(this);

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(next()));

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

void FrmVessel::onItemSelection()
{
    pushNext->setEnabled(tableView->selectionModel()->hasSelection());
    pushPrevious->setEnabled(tableView->selectionModel()->hasSelection());

}

bool FrmVessel::filterSampledCellVessels(QModelIndex index)
{
    //id_Sampled_Cell_Vessels
    QModelIndex idx=viewVessel->index(index.row(),3);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this vessel!"));
        return false;
    }

    QString id=idx.data().toString();

    tCellVessels->setFilter("ID="+id);
    if (tCellVessels->rowCount()!=1){
        emit showError (tr("Could not preview this vessel!"));
        return false;
    }

    return true;
}

void FrmVessel::previewRow(QModelIndex index)
{
    QModelIndex idx=this->viewVessel->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }

    updateSample(idx);

    if (!abstractPreviewRow(index)){
        emit showError (tr("Could not preview this record!"));
    }else{
        mapper1->toLast();

        if (!m_sample->bLogBook){
            if (!filterSampledCellVessels(index)){
                emit showError (tr("Could not preview this record!"));
            }else{
                mapper2->toLast();
            }
        }
    }
}

void FrmVessel::setPreviewQuery()
{
    if (m_sample==0) return;
    QString strQuery;
    int id;
    if (m_sample->bLogBook){//logbook

        strQuery=
        "                SELECT     dbo.Abstract_Sampled_Vessels.ID, dbo.Ref_Vessels.Name as [Vessel Name], dbo.Ref_Sample_Status.name AS Status"
        " FROM         dbo.Abstract_Sampled_Vessels INNER JOIN"
        "                      dbo.Ref_Vessels ON dbo.Abstract_Sampled_Vessels.VesselID = dbo.Ref_Vessels.VesselID INNER JOIN"
        "                      dbo.Sampled_Strata_Vessels ON dbo.Abstract_Sampled_Vessels.id_Sampled_Strata_Vessels = dbo.Sampled_Strata_Vessels.ID INNER JOIN"
        "                      dbo.Ref_Sample_Status ON dbo.Abstract_Sampled_Vessels.id_sample_status = dbo.Ref_Sample_Status.ID"
        "                      WHERE     (dbo.Sampled_Strata_Vessels.id_minor_strata = :id)"
        "                      ORDER BY dbo.Abstract_Sampled_Vessels.ID DESC"
        ;
        id=m_sample->minorStrataId;

    } else{//sampling
        strQuery=
         "            SELECT     dbo.Abstract_Sampled_Vessels.ID, dbo.Ref_Vessels.Name as [Vessel Name], dbo.Ref_Sample_Status.name AS Status, id_Sampled_Cell_Vessels"
         " FROM         dbo.Abstract_Sampled_Vessels INNER JOIN"
         "                     dbo.Sampled_Cell_Vessels ON dbo.Abstract_Sampled_Vessels.id_Sampled_Cell_Vessels = dbo.Sampled_Cell_Vessels.ID INNER JOIN"
         "                     dbo.Ref_Vessels ON dbo.Abstract_Sampled_Vessels.VesselID = dbo.Ref_Vessels.VesselID INNER JOIN"
         "                     dbo.Ref_Sample_Status ON dbo.Abstract_Sampled_Vessels.id_sample_status = dbo.Ref_Sample_Status.ID"
         "             WHERE     (dbo.Sampled_Cell_Vessels.id_cell_vessel_types = :id)"
         "                      ORDER BY dbo.Abstract_Sampled_Vessels.ID DESC"
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

    //two mappers to implement the polymorphism of abstract sampled vessels

     tCellVessels = new QSqlTableModel;
     tCellVessels->setTable("Sampled_Cell_Vessels");
     tCellVessels->setEditStrategy(QSqlTableModel::OnManualSubmit);
     tCellVessels->sort(0,Qt::AscendingOrder);
     tCellVessels->select();

    if (tStrataVessels!=0) delete tStrataVessels;

     tStrataVessels = new QSqlTableModel;
     tStrataVessels->setTable("Sampled_Strata_Vessels");
     tStrataVessels->setEditStrategy(QSqlTableModel::OnManualSubmit);
     tStrataVessels->sort(0,Qt::AscendingOrder);
     tStrataVessels->select();

}

void FrmVessel::initUI()
{
    setHeader();

    this->groupDetails->setVisible(false);
    setGroupDetails(groupDetails);
    setButtonBox(buttonBox);
    initPreviewTable(tableView,viewVessel);
    setNewButton(pushNew);
    setEditButton(pushEdit);
    setRemoveButton(pushRemove);
    setNextButton(pushNext);
    setPreviousButton(pushPrevious);

    //initializing the container for the readonly!S
    m_lWidgets << cmbVessel;
    m_lWidgets << cmbStatus;
    m_lWidgets << cmbOrigin;
    m_lWidgets << textComments;
    m_lWidgets << spinET;
    //m_lWidgets << spinCT;

    //pushNext->setEnabled(false);
}

void FrmVessel::initMapper1()
{
    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
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
        tAVessel->relationModel(2)->fieldIndex("Name"));

    cmbOrigin->setModel(tAVessel->relationModel(3));
    cmbOrigin->setModelColumn(
        tAVessel->relationModel(3)->fieldIndex("Name"));

    cmbStatus->setModel(tAVessel->relationModel(4));
    cmbStatus->setModelColumn(
        tAVessel->relationModel(4)->fieldIndex("Name"));

    mapper1->addMapping(cmbVessel, 2);
    mapper1->addMapping(cmbOrigin, 3);
    mapper1->addMapping(cmbStatus, 4);
    mapper1->addMapping(textComments,7);

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1 << mapper2;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));
}

void FrmVessel::initMappers()
{
    //mapper for the stuff on Sampled cell Vessels
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
    setSourceText(lbSource,m_sample->bLogBook);
    initVesselModel();
}

bool FrmVessel::comitNonAbstractVessels(const bool bLogbook, int& id_Sampled_Cell_Vessels, int& id_Sampled_Strata_Vessels)
{
    QSqlQuery query;

    if (bLogbook)
    {
        query.prepare( "SELECT     ID FROM Sampled_Cell_Vessels WHERE id_cell_vessel_types="
                       " (SELECT ID FROM         Sampled_Cell_Vessel_Types"
                       " WHERE     (comments = 'n/a'))" );//n.b.: when there are no names, we rely on the comment..

        if (!query.exec() || query.numRowsAffected()!=1){
            emit showError(tr("Could not create a non abstract record for this vessel (logbook)!"));
            return false;
        }
        query.first();
        id_Sampled_Cell_Vessels=query.value(0).toInt();
        return comitStrataVessels(id_Sampled_Strata_Vessels);
    }else{
        query.prepare( "SELECT     ID FROM Sampled_Strata_Vessels WHERE id_minor_strata="
                       "( SELECT ID FROM         Ref_Minor_Strata"
                       " WHERE     (Name = 'n/a') )" );

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

bool FrmVessel::reallyApply()
{
    bool bError=false;

    if (mapper1->submit()){

        //setting the vessel source
        QSqlQuery query;
        query.prepare( "SELECT     ID"
                       " FROM         dbo.Ref_Source"
                       " WHERE     (Name = :name)");
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

            //commit sampled cell vessels
            QModelIndex idx=tAVessel->index(tAVessel->rowCount()-1,5);
            if (!idx.isValid()) return false;
            tAVessel->setData(idx,id_cell);
            //commit sampled strata vessels
            idx=tAVessel->index(tAVessel->rowCount()-1,6);
            if (!idx.isValid()) return false;
            tAVessel->setData(idx,id_strata);

            //comiting abstract sampled vessels
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

    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(bError);

    emit lockControls(!bError,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->setVisible(!bError);

    if (!bError){
        mapper1->toLast();
        mapper2->toLast();
        return afterApply();
    }

    return false;
}

void FrmVessel::uI4NewRecord()
{
    genericUI4NewRecord();

    textComments->clear();

    //if there are records, defaults for the first one
    if (cmbVessel->count()>0)
        cmbVessel->setCurrentIndex(0);
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

    //signal for the rule checker default values
    emit addRecord();
}

void FrmVessel::initVesselModel()
{
    if (tAVessel!=0) delete tAVessel;

    tAVessel=new QSqlRelationalTableModel();
    tAVessel->setTable(QSqlDatabase().driver()->escapeIdentifier("Abstract_Sampled_Vessels",
        QSqlDriver::TableName));
    tAVessel->setRelation(2, QSqlRelation("Ref_Vessels", "VesselID", "Name"));
    tAVessel->setRelation(3, QSqlRelation("Ref_Sample_Origin", "ID", "Name"));
    tAVessel->setRelation(4, QSqlRelation("Ref_Sample_Status", "ID", "Name"));
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
        "SELECT     dbo.Ref_Vessels.VesselID"
        " FROM         dbo.FR_ALS2Vessel INNER JOIN"
        "                      dbo.Ref_Vessels ON dbo.FR_ALS2Vessel.vesselID = dbo.Ref_Vessels.VesselID"
        " WHERE     (dbo.FR_ALS2Vessel.id_sub_frame ="
        "                          (SELECT     ID"
        "                            FROM          dbo.FR_Sub_Frame"
        "                            WHERE      (Type ="
        "                                                       (SELECT     ID"
        "                                                         FROM          dbo.Ref_Frame"
        "                                                         WHERE      (Name = 'root'))) AND (id_frame =" + QVariant(m_sample->frameId).toString() + "))) AND (dbo.FR_ALS2Vessel.id_abstract_landingsite ="
        "                          (SELECT     id_abstract_LandingSite"
        "                            FROM          dbo.Sampled_Cell"
        "                            WHERE      (ID = " + QVariant(m_sample->cellId).toString() + "))) AND (dbo.FR_ALS2Vessel.vesselID NOT IN"
        "                          (SELECT     VesselID"
        "                            FROM          dbo.Abstract_Changes_Temp_Vessel"
        "                            WHERE      (id_cell = " + QVariant(m_sample->cellId).toString() + ") AND (To_LS ="
        "                                                       (SELECT     ID"
        "                                                         FROM          dbo.Ref_Abstract_LandingSite"
        "                                                         WHERE      (Name = 'outside'))))) AND "

        //filter by vessel types here
        " dbo.Ref_Vessels.VesselType=(SELECT id_vessel_type "
        " FROM         dbo.Sampled_Cell_Vessel_Types "
        " WHERE     (ID =" + QVariant(m_sample->vesselTypeId).toString() + "))"

        " UNION"
        " SELECT     Ref_Vessels_1.VesselID"
        " FROM         dbo.FR_ALS2Vessel AS FR_ALS2Vessel_1 INNER JOIN"
        "                      dbo.Ref_Vessels AS Ref_Vessels_1 ON FR_ALS2Vessel_1.vesselID = Ref_Vessels_1.VesselID"
        " WHERE     (Ref_Vessels_1.VesselID IN"
        "                          (SELECT     VesselID"
        "                            FROM          dbo.Abstract_Changes_Temp_Vessel AS Abstract_Changes_Temp_Vessel_1"
        "                            WHERE      (id_cell = " + QVariant(m_sample->cellId).toString() + ") AND (To_LS ="
        "                                                       (SELECT     id_abstract_LandingSite"
        "                                                         FROM          dbo.Sampled_Cell AS Sampled_Cell_1"
        "                                                         WHERE      (ID = " + QVariant(m_sample->cellId).toString() + ")))))"
            ;

    }else{
        strQuery =
        "SELECT     FR_ALS2Vessel_1.vesselID, dbo.FR_GLS2ALS.id_gls"
        " FROM         dbo.FR_ALS2Vessel INNER JOIN"
        "                      dbo.FR_GLS2ALS ON dbo.FR_ALS2Vessel.ID = dbo.FR_GLS2ALS.ID INNER JOIN"
        "                      dbo.FR_ALS2Vessel AS FR_ALS2Vessel_1 ON dbo.FR_ALS2Vessel.ID = FR_ALS2Vessel_1.ID INNER JOIN"
        "                      dbo.Ref_Vessels ON dbo.FR_ALS2Vessel.vesselID = dbo.Ref_Vessels.VesselID AND FR_ALS2Vessel_1.vesselID = dbo.Ref_Vessels.VesselID"
        " WHERE     (dbo.FR_ALS2Vessel.id_sub_frame ="
        "                          (SELECT     ID"
        "                            FROM          dbo.FR_Sub_Frame"
        "                            WHERE      (Type ="
        "                                                       (SELECT     ID"
        "                                                         FROM          dbo.Ref_Frame"
        "                                                         WHERE      (Name = 'root'))) AND (id_frame =" + QVariant(m_sample->frameId).toString() + "))) AND"
        " (dbo.FR_GLS2ALS.id_gls="
        " (SELECT     id_gls"
        " FROM         dbo.Ref_Minor_Strata"
        " WHERE     (ID = " + QVariant(m_sample->minorStrataId).toString() + ")))"
         ;
    }

    query.prepare(strQuery);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Vessels!"));
        return;
    }

    QString strFilter("");
     while (query.next()) {
        strFilter.append("VesselID=" + query.value(0).toString());
        strFilter.append(" OR ");
     }
     if (!strFilter.isEmpty())
         strFilter=strFilter.remove(strFilter.size()-QString(" OR ").length(),QString(" OR ").length());

    tAVessel->relationModel(2)->setFilter(strFilter);

        //first we set the relation; then we create a mapper and assign the (amended) model to the mapper;
    initMapper1();
}

bool FrmVessel::getNextLabel(QString& strLabel)
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //sending the name
    QModelIndex idx=viewVessel->index(tableView->selectionModel()->currentIndex().row(),1);
    strLabel=idx.data().toString();
    return true;
}

bool FrmVessel::applyChanges()
{
    bool bError=true;
    int cur1= mapper1->currentIndex();

    bError=!submitMapperAndModel(mapper1);
    if (!bError){
        if (!m_sample->bLogBook){

            int cur2= mapper2->currentIndex();

            //submit
            bError=!mapper2->submit();
            if (!bError){
                bError=!tCellVessels->submitAll();
                if (bError){
                    if (tCellVessels->lastError().type()!=QSqlError::NoError)
                        emit showError(tCellVessels->lastError().text());
                    else
                        emit showError(tr("Could not write sampled cell vessel changes in the database!"));
                }
            }

            mapper2->setCurrentIndex(cur2);
        }

    }
    mapper1->setCurrentIndex(cur1);

    if (!bError) emit editLeave(true,false);
    return !bError;
}

void FrmVessel::editFinished()
{
    setPreviewQuery();
    pushEdit->setChecked(false);
    pushNew->setEnabled(!pushEdit->isChecked());
    pushRemove->setEnabled(!pushEdit->isChecked());
    emit lockControls(true,m_lWidgets);
}

void FrmVessel::onEditLeave(const bool bFinished, const bool bDiscarded)
{
    if (bFinished){
        editFinished();
    }
}
