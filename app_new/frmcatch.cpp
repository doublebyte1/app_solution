#include "frmcatch.h"

FrmCatch::FrmCatch(RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
PreviewTab(7, inRoleDef,inSample,inTDateTime,tr("Catch"), ruleCheckerPtr,parent, flags){

    setupUi(this);

    installEventFilters();

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    connect(this, SIGNAL(blockCatchUISignals(const bool)), catchInputCtrl,
    SIGNAL(blockWidgetsSignals(const bool)));

    tCatch=0;
    viewCatch=0;
    mapper1=0;
    nullDelegate=0;

    initModels();
    initUI();
    initMappers();
}

FrmCatch::~FrmCatch()
{
    if (tCatch!=0) delete tCatch;
    if (viewCatch!=0) delete viewCatch;
    if (nullDelegate!=0) delete nullDelegate;
    if (mapper1!=0) delete mapper1;
}

void FrmCatch::initHelpIds()
{
    m_widgetInfo.insert(tableView,"Medfisis::Enter_the_Catch_Data");
    m_widgetInfo.insert(groupDetails,"Medfisis::Sub-form_CatchDetails");
    m_widgetInfo.insert(groupCatch,"Medfisis::Sub-form_CatchTotals");
    m_widgetInfo.insert(catchInputCtrl,"Medfisis::Sub-form_CatchTotals");
    m_widgetInfo.insert(groupGear,"Medfisis::Sub-form_CatchSample ");
}

void FrmCatch::onItemSelection()
{
    //n.b.: we don't enable next for now!
    pushPrevious->setEnabled(tableView->selectionModel()->hasSelection());
}

void FrmCatch::previewRow(QModelIndex index)
{
    emit blockCatchUISignals(true);

    QModelIndex idx=viewCatch->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this catch!"));
        return;
    }

    updateSample(idx);

    if (!abstractPreviewRow(index)){
        emit showError (tr("Could not preview this record!"));
    }else{
        mapper1->toLast();
    }

    emit blockCatchUISignals(false);
}

void FrmCatch::setPreviewQuery()
{
    if (m_sample==0) return;

    QString strQuery=
    "SELECT     dbo.Sampled_Catch.ID, dbo.Ref_Commercial_Categories.Name AS [Commercial Category], "
    "                      dbo.Sampled_Catch.catch_weight_estimated AS [Total Catch], dbo.Ref_Units.Name AS Units"
    " FROM         dbo.Sampled_Catch INNER JOIN"
    "                      dbo.Ref_Commercial_Categories ON dbo.Sampled_Catch.id_commercial_category = dbo.Ref_Commercial_Categories.ID INNER JOIN"
    "                      dbo.Ref_Units ON dbo.Sampled_Catch.id_catch_no_boxes_units = dbo.Ref_Units.ID AND "
    "                      dbo.Sampled_Catch.id_catch_units_units = dbo.Ref_Units.ID AND dbo.Sampled_Catch.id_catch_weight_units = dbo.Ref_Units.ID AND "
    "                      dbo.Sampled_Catch.id_sample_units = dbo.Ref_Units.ID"
    "                      WHERE     (dbo.Sampled_Catch.id_fishing_operation = :id) ORDER BY ID DESC"
    ;

    QSqlQuery query;
    query.prepare( strQuery );
    query.bindValue(0,m_sample->operationId);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Sampled Catches!"));
        return;
    }

    viewCatch->setQuery(query);

    tableView->hideColumn(0);
    resizeToVisibleColumns(tableView);
}

void FrmCatch::initModels()
{
    if (viewCatch!=0) delete viewCatch;
    viewCatch = new QSqlQueryModel;

    initCatchModel();
}

void FrmCatch::initUI()
{
    setHeader();

    this->groupDetails->setVisible(false);
    initPreviewTable(tableView,viewCatch);
    setButtonBox(buttonBox);
    setGroupDetails(groupDetails);
    setNewButton(pushNew);
    setEditButton(pushEdit);
    setRemoveButton(pushRemove);
    setPreviousButton(pushPrevious);

    setUIPermissions();

    //initializing the container for the readonly!S
    m_lWidgets << cmbCategory;
    m_lWidgets << catchInputCtrl;
    m_lWidgets << spinNoInd;
    m_lWidgets << doubleSpinWeight;
    m_lWidgets << cmbUnits;
    m_lWidgets << textComments;
}

void FrmCatch::initMapper1()
{
    emit blockCatchUISignals(true);

    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}

    if (mapper1!=0) delete mapper1;
    mapper1= new QDataWidgetMapper(this);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (tCatch==0) return;

    mapper1->setModel(tCatch);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lOthers;
    for (int i=2; i < 18; ++i){
        if (i!=15)
            lOthers << i;
    }
    QList<int> lText;
    lText << 15;
    nullDellegate=new NullRelationalDelegate(lOthers,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbCategory->setModel(tCatch->relationModel(2));
    cmbCategory->setModelColumn(
        tCatch->relationModel(2)->fieldIndex("Name"));

    catchInputCtrl->pCmbWeightUnits()->setModel(tCatch->relationModel(5));
    catchInputCtrl->pCmbWeightUnits()->setModelColumn(
        tCatch->relationModel(5)->fieldIndex("Name"));

    catchInputCtrl->pCmbBoxUnits()->setModel(tCatch->relationModel(8));
    catchInputCtrl->pCmbBoxUnits()->setModelColumn(
        tCatch->relationModel(8)->fieldIndex("Name"));

    catchInputCtrl->pCmbUnitUnits()->setModel(tCatch->relationModel(11));
    catchInputCtrl->pCmbUnitUnits()->setModelColumn(
        tCatch->relationModel(11)->fieldIndex("Name"));

    cmbUnits->setModel(tCatch->relationModel(14));
    cmbUnits->setModelColumn(
        tCatch->relationModel(14)->fieldIndex("Name"));

    mapper1->addMapping(cmbCategory, 2);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinTotalE(), 3);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinTotalC(), 4);
    mapper1->addMapping(catchInputCtrl->pCmbWeightUnits(), 5);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinNoBoxesE(), 6);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinNoBoxesC(), 7);
    mapper1->addMapping(catchInputCtrl->pCmbBoxUnits(), 8);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinWeightBox(), 9);
    mapper1->addMapping(catchInputCtrl->pSpinUnitsE(), 10);
    mapper1->addMapping(catchInputCtrl->pSpinUnitsC(), 16);
    mapper1->addMapping(catchInputCtrl->pCmbUnitUnits(), 11);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinWeightUnit(), 17);

    mapper1->addMapping(spinNoInd, 12);
    mapper1->addMapping(doubleSpinWeight, 13);
    mapper1->addMapping(cmbUnits, 14);

    mapper1->addMapping(textComments,15);

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));

}

void FrmCatch::initMappers()
{
    //Does Nothing
}

void FrmCatch::beforeShow()
{
    this->groupDetails->setVisible(false);

    setSourceText(lbSource,m_sample->bLogBook);
    initCatchModel();
}

bool FrmCatch::reallyApply()
{
    bool bError=false;

    if (mapper1->submit()){
        bError=!
            tCatch->submitAll();
            if (bError){
                if (tCatch->lastError().type()!=QSqlError::NoError)
                    emit showError(tCatch->lastError().text());
                else
                    emit showError(tr("Could not write operation in the database!"));
            }
    }else bError=true;

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

void FrmCatch::uI4NewRecord()
{
    genericUI4NewRecord();

    textComments->clear();
    if (cmbCategory->count()>0) cmbCategory->setCurrentIndex(0);
}

void FrmCatch::createRecord()
{
    emit blockCatchUISignals(true);

    genericCreateRecord();
    mapper1->toLast();

    while(tCatch->canFetchMore())
        tCatch->fetchMore();

    //Fields that we have to fill behind the scenes...
    QModelIndex idx=tCatch->index(tCatch->rowCount()-1,1);
    tCatch->setData(idx,m_sample->operationId);//id_fishing_operation

    uI4NewRecord();//init UI

    //signal for the rule checker default values
    emit addRecord();

    emit blockCatchUISignals(false);
}

void FrmCatch::initCatchModel()
{
    if (tCatch!=0) delete tCatch;

    tCatch=new QSqlRelationalTableModel();
    tCatch->setTable(QSqlDatabase().driver()->escapeIdentifier("Sampled_Catch",
        QSqlDriver::TableName));

    tCatch->setRelation(2, QSqlRelation("Ref_Commercial_Categories", "ID", "Name"));

    tCatch->setRelation(5, QSqlRelation("Ref_Units", "ID", "Name"));//catch_weight units
    tCatch->setRelation(8, QSqlRelation("Ref_Units", "ID", "Name"));//no_boxes_units
    tCatch->setRelation(11, QSqlRelation("Ref_Units", "ID", "Name"));//units units
    tCatch->setRelation(14, QSqlRelation("Ref_Units", "ID", "Name"));//sample units

    tCatch->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tCatch->sort(0,Qt::AscendingOrder);
    tCatch->select();

    setPreviewModel(tCatch);
}

void FrmCatch::filterModel4Combo()
{
    if (!m_sample) return;

    QSqlQuery query;
    QString strQuery;

    if (m_sample->operationId==-1){
            emit showError(tr("Could not identify the operation for this catch!"));
            return;
        }

    strQuery=
        "SELECT     id_commercial_category"
        " FROM         dbo.Sampled_Fishing_Operations_Categories"
        " WHERE     (id_fishing_operation = " + QVariant(m_sample->operationId).toString() + ")";

    query.prepare(strQuery);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for commercial categories!"));
        return;
    }

    QString strFilter("");
    while (query.next()) {
        strFilter.append("ID=" + query.value(0).toString());
        strFilter.append(" OR ");
    }
    if (!strFilter.isEmpty())
        strFilter=strFilter.remove(strFilter.size()-QString(" OR ").length(),QString(" OR ").length());

    tCatch->relationModel(2)->setFilter(strFilter);

    initMapper1();
}

bool FrmCatch::getNextLabel(QString& strLabel)
{
    //n.b.: we don't need this implementation, for tge time being!
    return true;
}

void FrmCatch::editFinished()
{
    setPreviewQuery();
    pushEdit->setChecked(false);
    pushNew->setEnabled(!pushEdit->isChecked());
    pushRemove->setEnabled(!pushEdit->isChecked());
    emit lockControls(true,m_lWidgets);
}

void FrmCatch::onEditLeave(const bool bFinished, const bool bDiscarded)
{
    if (bFinished){
        editFinished();
    }
}

bool FrmCatch::applyChanges()
{
   bool bError=true;

    int cur= mapper1->currentIndex();
    bError=!submitMapperAndModel(mapper1);
    if (!bError){
        mapper1->setCurrentIndex(cur);
    }

    emit editLeave(true,false);
    return !bError;
}