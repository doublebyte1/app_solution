//#include "globaldefs.h"
#include "frmvesseltype.h"

FrmVesselType::FrmVesselType(RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
PreviewTab(3,inRoleDef,inSample,inTDateTime,tr("Vessel Type"), ruleCheckerPtr, parent, flags){

    setupUi(this);

    installEventFilters();

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(next()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    mapper1=0;
    tSVesselTypes=0;
    viewVesselTypes=0;
    nullDellegate=0;

    initModels();
    initUI();
    initMappers();
}

FrmVesselType::~FrmVesselType()
{
    if (tSVesselTypes!=0) delete tSVesselTypes;
    if (nullDellegate!=0) delete nullDellegate;
    if (mapper1!=0) delete mapper1;
    if (viewVesselTypes!=0) delete viewVesselTypes;
}

void FrmVesselType::initHelpIds()
{
    m_widgetInfo.insert(tableView,"Medfisis::Identify_the_Vessel_Type");
    m_widgetInfo.insert(groupDetails,"Medfisis::Sub-form_Vessel_TypeDetails");
    m_widgetInfo.insert(cmbTypes,"Medfisis::vessel_type");
}

void FrmVesselType::onItemSelection()
{
    pushNext->setEnabled(tableView->selectionModel()->hasSelection());
    pushPrevious->setEnabled(tableView->selectionModel()->hasSelection());
}

void FrmVesselType::initMappers()
{
    //NOTHING
}

void FrmVesselType::initMapper1()
{
    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
    if (mapper1!=0) delete mapper1;
    mapper1= new QDataWidgetMapper(this);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    mapper1->setModel(tSVesselTypes);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lOthers;
    lOthers << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
    QList<int> lText;
    lText << 11;
    nullDellegate=new NullRelationalDelegate(lOthers,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbTypes->setModel(tSVesselTypes->relationModel(2));
    cmbTypes->setModelColumn(
        tSVesselTypes->relationModel(2)->fieldIndex(tr("Name")));

    mapper1->addMapping(cmbTypes, 2);

    mapper1->addMapping(spinNE, 3);
    mapper1->addMapping(spinNC, 4);
    mapper1->addMapping(spinAE, 5);
    mapper1->addMapping(spinAC, 6);
    mapper1->addMapping(spinIE, 7);
    mapper1->addMapping(spinIC, 8);
    mapper1->addMapping(spinOE, 9);
    mapper1->addMapping(spinOC, 10);

    mapper1->addMapping(textComments,11);

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));
}

void FrmVesselType::previewRow(QModelIndex index)
{
    QModelIndex idx=this->viewVesselTypes->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }

    updateSample(idx);

    if (!abstractPreviewRow(index)){
        //emit showError (tr("Could not preview this record!"));
        qDebug() << tr("Record discarded!") << endl;
    }else{
        mapper1->toLast();
    }
}

void FrmVesselType::setPreviewQuery()
{
    if (m_sample==0) return;

    viewVesselTypes->setQuery(
        tr("SELECT     dbo.Sampled_Cell_Vessel_Types.ID, dbo.Ref_Vessel_Types.Name [Vessel Type]")+
        tr(" FROM         dbo.Sampled_Cell_Vessel_Types INNER JOIN")+
        tr("                      dbo.Ref_Vessel_Types ON dbo.Sampled_Cell_Vessel_Types.id_vessel_type = dbo.Ref_Vessel_Types.ID")+
        tr(" WHERE     (dbo.Sampled_Cell_Vessel_Types.id_cell =")+ QVariant(m_sample->cellId).toString() + tr(")") +
        tr(" ORDER BY dbo.Sampled_Cell_Vessel_Types.ID DESC")
    );

    tableView->hideColumn(0);
    resizeToVisibleColumns(tableView);

}

void FrmVesselType::beforeShow()
{
    this->groupDetails->setVisible(false);
    setSourceText(lbSource, m_sample->bLogBook);
    initVesselTypeModel();
}

bool FrmVesselType::reallyApply()
{
        bool bError=false;

        if (mapper1->submit()){
                    bError=!
                        tSVesselTypes->submitAll();
                    if (bError){
                        if (tSVesselTypes->lastError().type()!=QSqlError::NoError)
                            emit showError(tSVesselTypes->lastError().text());
                        else
                            emit showError(tr("Could not write vessel type in the database!"));
                    }//mapper1->toLast();
        }else bError=true;

        buttonBox->button(QDialogButtonBox::Apply)->setEnabled(bError);
        //button->setEnabled(bError);

        emit lockControls(!bError,m_lWidgets);
        if (!bError){
            buttonBox->button(QDialogButtonBox::Apply)->hide();
        }else{
            buttonBox->button(QDialogButtonBox::Apply)->show();
        }

        if (!bError){
            bError=afterApply();
        }
        return !bError;
}

void FrmVesselType::uI4NewRecord()
{
    genericUI4NewRecord();

    textComments->clear();
    cmbTypes->setCurrentIndex(-1);

}

void FrmVesselType::createRecord()
{
    genericCreateRecord();

    mapper1->toLast();

    while(tSVesselTypes->canFetchMore())
        tSVesselTypes->fetchMore();

    QModelIndex idx=tSVesselTypes->index(tSVesselTypes->rowCount()-1,1);
    tSVesselTypes->setData(idx,m_sample->cellId);//id_cell

    uI4NewRecord();//init UI

    //signal for the rule checker default values
    emit addRecord();
}

void FrmVesselType::filterModel4Combo()
{
    QString strQuery(
    tr("SELECT     dbo.Ref_Vessel_Types.ID")+
    tr(" FROM         dbo.FR_ALS2Vessel INNER JOIN")+
    tr("                      dbo.Ref_Vessels ON dbo.FR_ALS2Vessel.vesselID = dbo.Ref_Vessels.VesselID INNER JOIN")+
    tr("                      dbo.Ref_Vessel_Types ON dbo.Ref_Vessels.VesselType = dbo.Ref_Vessel_Types.ID")+
    tr(" WHERE     (dbo.FR_ALS2Vessel.id_sub_frame =")+
    tr("                          (SELECT     ID")+
    tr("                            FROM          dbo.FR_Sub_Frame")+
    tr("                            WHERE      (Type =")+
    tr("                                                       (SELECT     ID")+
    tr("                                                         FROM          dbo.Ref_Frame")+
    tr("                                                         WHERE      (Name = 'root'))) AND (id_frame = ") + QVariant(m_sample->frameId).toString() + tr("))) AND (dbo.FR_ALS2Vessel.id_abstract_landingsite =")+
    tr("                          (SELECT     id_abstract_LandingSite")+
    tr("                            FROM          dbo.Sampled_Cell")+
    tr("                            WHERE      (ID = ") + QVariant(m_sample->cellId).toString() + tr("))) AND (dbo.FR_ALS2Vessel.vesselID NOT IN")+
    tr("                          (SELECT     VesselID")+
    tr("                            FROM          dbo.Abstract_Changes_Temp_Vessel")+
    tr("                            WHERE      (id_cell = ") + QVariant(m_sample->cellId).toString() + tr(") AND (To_LS =")+
    tr("                                                       (SELECT     ID")+
    tr("                                                         FROM          dbo.Ref_Abstract_LandingSite")+
    tr("                                                         WHERE      (Name = 'outside')))))")+
    tr(" UNION")+
    tr(" SELECT     Ref_Vessel_Types_1.Name")+
    tr(" FROM         dbo.FR_ALS2Vessel AS FR_ALS2Vessel_1 INNER JOIN")+
    tr("                      dbo.Ref_Vessels AS Ref_Vessels_1 ON FR_ALS2Vessel_1.vesselID = Ref_Vessels_1.VesselID INNER JOIN")+
    tr("                      dbo.Ref_Vessel_Types AS Ref_Vessel_Types_1 ON Ref_Vessels_1.VesselType = Ref_Vessel_Types_1.ID")+
    tr(" WHERE     (Ref_Vessels_1.VesselID IN")+
    tr("                          (SELECT     VesselID")+
    tr("                            FROM          dbo.Abstract_Changes_Temp_Vessel AS Abstract_Changes_Temp_Vessel_1")+
    tr("                            WHERE      (id_cell = ") + QVariant(m_sample->cellId).toString() + tr(") AND (To_LS =")+
    tr("                                                       (SELECT     id_abstract_LandingSite")+
    tr("                                                         FROM          dbo.Sampled_Cell AS Sampled_Cell_1")+
    tr("                                                         WHERE      (ID = ") + QVariant(m_sample->cellId).toString() + tr(")))))")
    );

    QSqlQuery query;
    query.prepare(strQuery);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for vessel types!"));
        return;
    }

    QString strFilter(tr(""));
     while (query.next()) {
        strFilter.append(tr("ID=") + query.value(0).toString());
        strFilter.append(tr(" OR "));
     }
     if (!strFilter.isEmpty())
         strFilter=strFilter.remove(strFilter.size()-tr(" OR ").length(),tr(" OR ").length());

    tSVesselTypes->relationModel(2)->setFilter(strFilter);
    //first we set the relation; then we create a mapper and assign the (amended) model to the mapper;
    initMapper1();
}

void FrmVesselType::initUI()
{
    setHeader();
    initPreviewTable(tableView,viewVesselTypes);
    setButtonBox(buttonBox);
    setGroupDetails(groupDetails);
    setNewButton(pushNew);
    setEditButton(pushEdit);
    setRemoveButton(pushRemove);
    setNextButton(pushNext);
    setPreviousButton(pushPrevious);

    setUIPermissions();

    //initializing the container for the readonly!
    m_lWidgets << cmbTypes;
    m_lWidgets << textComments;
    m_lWidgets << spinNE;
    m_lWidgets << spinAE;
    m_lWidgets << spinIE;
    m_lWidgets << spinOE;

    pushNext->setEnabled(false);
}

bool FrmVesselType::getNextLabel(QString& strLabel)
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //sending the name
    QModelIndex idx=viewVesselTypes->index(tableView->selectionModel()->currentIndex().row(),1);

    if (!idx.isValid()) return false;
    strLabel=idx.data().toString();
    return true;
}

void FrmVesselType::initVesselTypeModel()
{
    if (tSVesselTypes!=0) delete tSVesselTypes;

    tSVesselTypes=new QSqlRelationalTableModel();
    tSVesselTypes->setTable(QSqlDatabase().driver()->escapeIdentifier("Sampled_Cell_Vessel_Types",
        QSqlDriver::TableName));
    tSVesselTypes->setRelation(2, QSqlRelation("Ref_Vessel_Types", "ID", "Name"));
    tSVesselTypes->relationModel(2)->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tSVesselTypes->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tSVesselTypes->sort(0,Qt::AscendingOrder);
    tSVesselTypes->select();

    setPreviewModel(tSVesselTypes);
}

void FrmVesselType::initModels()
{
    if (viewVesselTypes!=0) delete viewVesselTypes;
    viewVesselTypes = new QSqlQueryModel;
}

bool FrmVesselType::applyChanges()
{
    bool bError=true;

    int cur= mapper1->currentIndex();
    bError=!submitMapperAndModel(mapper1);
    if (!bError){
        mapper1->setCurrentIndex(cur);
    }

    if (!bError) emit editLeave(true,false);
    return !bError;
}

void FrmVesselType::editFinished()
{
    setPreviewQuery();
    pushEdit->setChecked(false);
    pushNew->setEnabled(!pushEdit->isChecked());
    pushRemove->setEnabled(!pushEdit->isChecked());
    emit lockControls(true,m_lWidgets);
}

void FrmVesselType::onEditLeave(const bool bFinished, const bool bDiscarded)
{
    if (bFinished){
        editFinished();
    }}
