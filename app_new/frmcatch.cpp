#include "frmcatch.h"

FrmCatch::FrmCatch(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
PreviewTab(7,inSample,inTDateTime,tr("Catch"), ruleCheckerPtr,parent, flags){

    setupUi(this);

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


void FrmCatch::onItemSelection()
{
    //pushNext->setEnabled(tableView->selectionModel()->hasSelection());
}

void FrmCatch::previewRow(QModelIndex index)
{
    emit blockCatchUISignals(true);

    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->hide();

    QModelIndex idx=viewCatch->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this catch!"));
        return;
    }

    QString id=idx.data().toString();

    tCatch->setFilter(tr("Sampled_Catch.ID=")+id);
    if (tCatch->rowCount()!=1)
        return;

    mapper1->toLast();

    //pushNext->setEnabled(true);
    emit blockCatchUISignals(false);
}

void FrmCatch::setPreviewQuery()
{
    if (m_sample==0) return;

    QString strQuery=
    tr("SELECT     dbo.Sampled_Catch.ID, dbo.Ref_Commercial_Categories.Name AS [Commercial Category], ")+
    tr("                      dbo.Sampled_Catch.catch_weight_estimated AS [Total Catch], dbo.Ref_Units.Name AS Units")+
    tr(" FROM         dbo.Sampled_Catch INNER JOIN")+
    tr("                      dbo.Ref_Commercial_Categories ON dbo.Sampled_Catch.id_commercial_category = dbo.Ref_Commercial_Categories.ID INNER JOIN")+
    tr("                      dbo.Ref_Units ON dbo.Sampled_Catch.id_catch_no_boxes_units = dbo.Ref_Units.ID AND ")+
    tr("                      dbo.Sampled_Catch.id_catch_units_units = dbo.Ref_Units.ID AND dbo.Sampled_Catch.id_catch_weight_units = dbo.Ref_Units.ID AND ")+
    tr("                      dbo.Sampled_Catch.id_sample_units = dbo.Ref_Units.ID")+
    tr("                      WHERE     (dbo.Sampled_Catch.id_fishing_operation = :id) ORDER BY ID DESC")
    ;

    QSqlQuery query;
    query.prepare( strQuery );
    query.bindValue(0,m_sample->operationId);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Sampled Catches!"));
        return;
    }

    qDebug() << query.numRowsAffected() << endl;

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

    //initializing the container for the readonly!S
    m_lWidgets << cmbCategory;
    m_lWidgets << catchInputCtrl;
    m_lWidgets << spinNoInd;
    m_lWidgets << doubleSpinWeight;
    m_lWidgets << cmbUnits;
    m_lWidgets << textComments;

    pushNext->setEnabled(false);
}

void FrmCatch::initMapper1()
{
    emit blockCatchUISignals(true);

    if (mapper1!=0) delete mapper1;
    mapper1= new QDataWidgetMapper(this);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (tCatch==0) return;

    mapper1->setModel(tCatch);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lOthers;
    for (int i=2; i < 15; ++i){
        lOthers << i;
    }
    lOthers << 16;
    QList<int> lText;
    lText << 15;
    nullDellegate=new NullRelationalDelegate(lOthers,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbCategory->setModel(tCatch->relationModel(2));
    cmbCategory->setModelColumn(
        tCatch->relationModel(2)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbWeightUnits()->setModel(tCatch->relationModel(5));
    catchInputCtrl->pCmbWeightUnits()->setModelColumn(
        tCatch->relationModel(5)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbBoxUnits()->setModel(tCatch->relationModel(8));
    catchInputCtrl->pCmbBoxUnits()->setModelColumn(
        tCatch->relationModel(8)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbUnitUnits()->setModel(tCatch->relationModel(11));
    catchInputCtrl->pCmbUnitUnits()->setModelColumn(
        tCatch->relationModel(11)->fieldIndex(tr("Name")));

    cmbUnits->setModel(tCatch->relationModel(14));
    cmbUnits->setModelColumn(
        tCatch->relationModel(14)->fieldIndex(tr("Name")));

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

    mapper1->addMapping(spinNoInd, 12);
    mapper1->addMapping(doubleSpinWeight, 13);
    mapper1->addMapping(cmbUnits, 14);

    mapper1->addMapping(textComments,15);

    emit blockCatchUISignals(false);
}

void FrmCatch::initMappers()
{
    //Nothing
}

void FrmCatch::beforeShow()
{
    this->groupDetails->setVisible(false);

    setSourceText(lbSource);
    initCatchModel();
}

bool FrmCatch::onButtonClick(QAbstractButton* button)
{
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tCatch->revertAll();
        return true;

    } else if (buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){

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

void FrmCatch::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(false,m_lWidgets);

    textComments->clear();

    //TODO: remove this initialization later, when we put the BL layer
    catchInputCtrl->cmbBoxUnits->setCurrentIndex(this->catchInputCtrl->cmbBoxUnits->findText(
        qApp->translate("null_replacements", strNa)));

    catchInputCtrl->cmbUnitUnits->setCurrentIndex(this->catchInputCtrl->cmbUnitUnits->findText(
        qApp->translate("null_replacements", strNa)));

    catchInputCtrl->cmbWeightUnits->setCurrentIndex(this->catchInputCtrl->cmbWeightUnits->findText(
        qApp->translate("null_replacements", strNa)));

    cmbUnits->setCurrentIndex(cmbUnits->findText(
        qApp->translate("null_replacements", strNa)));

    buttonBox->button(QDialogButtonBox::Apply)->show();
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
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

    emit blockCatchUISignals(false);
}

void FrmCatch::initCatchModel()
{
    if (tCatch!=0) delete tCatch;

    tCatch=new QSqlRelationalTableModel();
    tCatch->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Catch"),
        QSqlDriver::TableName));

    tCatch->setRelation(2, QSqlRelation(tr("Ref_Commercial_Categories"), tr("ID"), tr("Name")));

    tCatch->setRelation(5, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));//catch_weight units
    tCatch->setRelation(8, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));//no_boxes_units
    tCatch->setRelation(11, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));//units units
    tCatch->setRelation(14, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));//sample units

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
        tr("SELECT     id_commercial_category")+
        tr(" FROM         dbo.Sampled_Fishing_Operations_Categories")+
        tr(" WHERE     (id_fishing_operation = ") + QVariant(m_sample->operationId).toString() + tr(")");

    query.prepare(strQuery);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for commercial categories!"));
        return;
    }

    QString strFilter(tr(""));
    while (query.next()) {
        strFilter.append(tr("ID=") + query.value(0).toString());
        strFilter.append(tr(" OR "));
    }
    if (!strFilter.isEmpty())
        strFilter=strFilter.remove(strFilter.size()-tr(" OR ").length(),tr(" OR ").length());

    tCatch->relationModel(2)->setFilter(strFilter);

    initMapper1();
}

bool FrmCatch::updateSample()
{/*
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //updating the sample structure
    QModelIndex idx=viewOperations->index(tableView->selectionModel()->currentIndex().row(),0);

    m_sample->operationId=idx.data().toInt();*/
    return true;
}

bool FrmCatch::getNextLabel(QString& strLabel)
{/*
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //sending the name
    QModelIndex idx=viewOperations->index(tableView->selectionModel()->currentIndex().row(),3);
    strLabel=idx.data().toString();*/
    return true;
}
