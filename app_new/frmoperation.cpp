#include <QTest>
#include "frmoperation.h"

FrmOperation::FrmOperation(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
PreviewTab(6,inSample,inTDateTime,tr("Fishing Operation"), ruleCheckerPtr, parent, flags){

    setupUi(this);

    blockCustomDateCtrls();

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(next()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    connect(this, SIGNAL(blockCatchUISignals(const bool)), catchInputCtrl,
    SIGNAL(blockWidgetsSignals(const bool)));

    tOperations=0;
    tOpCat=0;
    tRefCat=0;
    multiModelI=0;
    viewOperations=0;
    mapper1=0;
    mapperStartDt=0;
    mapperEndDt=0;
    nullDelegate=0;

    initModels();
    initUI();
    initMappers();

}

FrmOperation::~FrmOperation()
{
    if (tOpCat!=0) delete tOpCat;
    if (tRefCat!=0) delete tRefCat;
    if (multiModelI!=0) delete multiModelI;
    if (tOperations!=0) delete tOperations;
    if (viewOperations!=0) delete viewOperations;
    if (nullDelegate!=0) delete nullDelegate;
    if (mapper1!=0) delete mapper1;
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;
}


void FrmOperation::onItemSelection()
{
    pushNext->setEnabled(tableView->selectionModel()->hasSelection());
}

void FrmOperation::previewRow(QModelIndex index)
{
    emit blockCatchUISignals(true);

    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->hide();

    QModelIndex idx=viewOperations->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this operation!"));
        return;
    }

    int intId=idx.data().toInt();//for the MultiModelI
    QString id=idx.data().toString();

    tOperations->setFilter(tr("Sampled_Fishing_Operations.ID=")+id);
    if (tOperations->rowCount()!=1)
        return;

    mapper1->toLast();

    //Now fix the dates
    idx=tOperations->index(0,2);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this trip!"));
        return;
    }
    QString strStartDt=idx.data().toString();
    idx=tOperations->index(0,3);
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

    //preview record on the listView
    multiModelI->setParentId(intId);
    multiModelI->model2List(tr("id_fishing_operation"));

    pushNext->setEnabled(true);

    emit blockCatchUISignals(false);
}

void FrmOperation::setPreviewQuery()
{
    if (m_sample==0) return;
    QString strQuery=

    tr("SELECT     dbo.Sampled_Fishing_Operations.ID, dbo.Ref_Gears.Name as [Gear Used], CONVERT(CHAR(10), F1.Date_Local, 103) AS [Start Date], ") +
    tr(" CASE WHEN F1.Date_Type=(SELECT ID from Ref_DateTime_Type WHERE Name='Date') THEN 'missing' ELSE") +
    tr(" CONVERT(VARCHAR(8), F1.Date_Local, 108) END [Start Time]") +
    tr(" , CONVERT(CHAR(10), F2.Date_Local, 103) AS [End Date], ") +
    tr(" CASE WHEN F2.Date_Type=(SELECT ID from Ref_DateTime_Type WHERE Name='Date') THEN 'missing' ELSE") +
    tr(" CONVERT(VARCHAR(8), F2.Date_Local, 108) END [End Time] ") +
    tr(" FROM         dbo.Sampled_Fishing_Operations INNER JOIN") +
    tr("                      dbo.Ref_Gears ON dbo.Sampled_Fishing_Operations.id_gear = dbo.Ref_Gears.ID INNER JOIN") +
    tr("                      dbo.GL_Dates AS F1 ON dbo.Sampled_Fishing_Operations.id_start_dt = F1.ID INNER JOIN") +
    tr("                      dbo.GL_Dates AS F2 ON dbo.Sampled_Fishing_Operations.id_end_dt = F2.ID") +
    tr(" WHERE     (dbo.Sampled_Fishing_Operations.id_fishing_trip = :id) ORDER BY ID DESC")
    ;

    QSqlQuery query;
    query.prepare( strQuery );
    query.bindValue(0,m_sample->tripId);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Sampled Fishing Operations!"));
        return;
    }

    viewOperations->setQuery(query);

    tableView->hideColumn(0);
    resizeToVisibleColumns(tableView);
}

void FrmOperation::initModels()
{
    if (viewOperations!=0) delete viewOperations;
    viewOperations = new QSqlQueryModel;

    if (tRefCat!=0) delete tRefCat;

     tRefCat = new QSqlQueryModel;
     tRefCat->setQuery(
        tr("SELECT   ID, Name FROM         dbo.Ref_Commercial_Categories ORDER BY ID")
         );

    if (tOpCat!=0) delete tOpCat;

    tOpCat=new QSqlTableModel();
    tOpCat->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Fishing_Operations_Categories"),
        QSqlDriver::TableName));
    tOpCat->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tOpCat->sort(0,Qt::AscendingOrder);
    tOpCat->select();

     multiModelI=new MultiModelI(listCategories,tRefCat,tOpCat);
}

void FrmOperation::initUI()
{
    setHeader();

    this->groupDetails->setVisible(false);
    initPreviewTable(tableView,viewOperations);
    setButtonBox(buttonBox);
    setGroupDetails(groupDetails);

    //initializing the container for the readonly!S
    m_lWidgets << spinOrder;
    m_lWidgets << cmbFishingZone;
    m_lWidgets << cmbGear;
    m_lWidgets << customDtStart;
    m_lWidgets << customDtEnd;
    m_lWidgets << spinNoUnits;
    m_lWidgets << doubleSpinSize;
    m_lWidgets << catchInputCtrl;
    m_lWidgets << textComments;
    m_lWidgets << listCategories;

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

void FrmOperation::initMapper1()
{
    emit blockCatchUISignals(true);

    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
    if (mapper1!=0) delete mapper1;
    mapper1= new QDataWidgetMapper(this);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (tOperations==0) return;

    mapper1->setModel(tOperations);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lOthers;
    for (int i=4; i < 19; ++i){
        lOthers << i;
    }
    lOthers << 20;
    QList<int> lText;
    lText << 19;
    nullDellegate=new NullRelationalDelegate(lOthers,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbFishingZone->setModel(tOperations->relationModel(18));
    cmbFishingZone->setModelColumn(
        tOperations->relationModel(18)->fieldIndex(tr("Name")));

    cmbGear->setModel(tOperations->relationModel(4));
    cmbGear->setModelColumn(
        tOperations->relationModel(4)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbWeightUnits()->setModel(tOperations->relationModel(7));
    catchInputCtrl->pCmbWeightUnits()->setModelColumn(
        tOperations->relationModel(7)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbBoxUnits()->setModel(tOperations->relationModel(10));
    catchInputCtrl->pCmbBoxUnits()->setModelColumn(
        tOperations->relationModel(10)->fieldIndex(tr("Name")));

    catchInputCtrl->pCmbUnitUnits()->setModel(tOperations->relationModel(14));
    catchInputCtrl->pCmbUnitUnits()->setModelColumn(
        tOperations->relationModel(14)->fieldIndex(tr("Name")));

    mapper1->addMapping(cmbGear, 4);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinTotalE(), 5);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinTotalC(), 6);
    mapper1->addMapping(catchInputCtrl->pCmbWeightUnits(), 7);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinNoBoxesE(), 8);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinNoBoxesC(), 9);
    mapper1->addMapping(catchInputCtrl->pCmbBoxUnits(), 10);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinWeightBox(), 11);
    mapper1->addMapping(catchInputCtrl->pSpinUnitsE(), 12);
    mapper1->addMapping(catchInputCtrl->pSpinUnitsC(), 13);
    mapper1->addMapping(catchInputCtrl->pCmbUnitUnits(), 14);
    mapper1->addMapping(spinNoUnits, 15);
    mapper1->addMapping(doubleSpinSize, 16);
    mapper1->addMapping(spinOrder, 17);
    mapper1->addMapping(cmbFishingZone, 18);
    mapper1->addMapping(catchInputCtrl->pDoubleSpinWeightUnit(), 20);

    mapper1->addMapping(textComments,19);

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1 << mapperStartDt << mapperEndDt;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));

    connect(m_mapperBinderPtr, SIGNAL(defaultValuesRead()), this,
        SLOT(unblockCustomDateCtrls()));

    emit blockCatchUISignals(false);
}

void FrmOperation::blockCustomDateCtrls()
{
    //block signals here because of the rule binder!
    customDtStart->blockSignals(true);
    customDtEnd->blockSignals(true);
}

void FrmOperation::unblockCustomDateCtrls()
{
    //block signals here because of the rule binder!
    customDtStart->blockSignals(false);
    customDtEnd->blockSignals(false);
}

void FrmOperation::initMappers()
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

void FrmOperation::beforeShow()
{
    this->groupDetails->setVisible(false);

    setSourceText(lbSource,m_sample->bLogBook);
    initOperationModel();
}

bool FrmOperation::reallyApply()
{
        bool bError=false;

        if (!listCategories->selectionModel()->hasSelection()){
            emit showError(tr("You must select one or more commercial categories for this trip!"));
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
                    QModelIndex idxStart=tOperations->index(tOperations->rowCount()-1,2);
                    if (idxStart.isValid()){
                        tOperations->setData(idxStart,idStart);
                    }else bError=true;
                }else bError=true;

                int idEnd;
                if (getDtId(endIdx,idEnd)){
                    QModelIndex idxEnd=tOperations->index(tOperations->rowCount()-1,3);
                    if (idxEnd.isValid()){
                        tOperations->setData(idxEnd,idEnd);
                    }else bError=true;
                }else bError=true;

            if (mapper1->submit()){
                bError=!
                    tOperations->submitAll();
                    if (bError){
                        if (tOperations->lastError().type()!=QSqlError::NoError)
                            emit showError(tOperations->lastError().text());
                        else
                            emit showError(tr("Could not write operation in the database!"));
                    }else{
                        //Comiting Sampled_Fishing_Operations_Categories
                        QModelIndex idd=tOperations->index(tOperations->rowCount()-1,0);
                        multiModelI->setParentId(idd.data().toInt());
                        if (!multiModelI->list2Model()){
                            emit showError(tr("Could not associate commercial categories to this fishing operation!"));
                            bError=true;
                        }

                    }
            }

            }
        }
        //button->setEnabled(bError);
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

void FrmOperation::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(false,m_lWidgets);

    customDtStart->setIsDateTime(true,true,true);
    customDtEnd->setIsDateTime(true,true,true);
    textComments->clear();
    listCategories->clearSelection();

    if (cmbFishingZone->count()) cmbFishingZone->setCurrentIndex(0);
    if (cmbGear->count()) cmbGear->setCurrentIndex(0);

    buttonBox->button(QDialogButtonBox::Apply)->show();
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}

void FrmOperation::createRecord()
{
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

    while(tOperations->canFetchMore())
        tOperations->fetchMore();

    //Fields that we have to fill behind the scenes...
    QModelIndex idx=tOperations->index(tOperations->rowCount()-1,1);
    tOperations->setData(idx,m_sample->tripId);//id_fishing_trip

    uI4NewRecord();//init UI

    //signal for the rule checker default values
    emit addRecord();

    emit blockCatchUISignals(false);
}

void FrmOperation::initOperationModel()
{
    if (tOperations!=0) delete tOperations;

    tOperations=new QSqlRelationalTableModel();
    tOperations->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Fishing_Operations"),
        QSqlDriver::TableName));

    tOperations->setRelation(4, QSqlRelation(tr("Ref_Gears"), tr("ID"), tr("Name")));
    tOperations->setRelation(7, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));
    tOperations->setRelation(10, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));
    tOperations->setRelation(14, QSqlRelation(tr("Ref_Units"), tr("ID"), tr("Name")));
    tOperations->setRelation(18, QSqlRelation(tr("Ref_Fishing_Zones"), tr("ID"), tr("Name")));

    tOperations->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tOperations->sort(0,Qt::AscendingOrder);
    tOperations->select();

    setPreviewModel(tOperations);
}

void FrmOperation::filterModel4Combo()
{
    if (!m_sample) return;

    QSqlQuery query;
    QString strQuery;

    if (m_sample->tripId==-1){
            emit showError(tr("Could not identify the trip for this operation!"));
            return;
        }

    strQuery=
        tr("SELECT     id_fishing_gear")+
        tr(" FROM         dbo.Sampled_Fishing_Trips_Gears")+
        tr(" WHERE     (id_fishing_trip = ") + QVariant(m_sample->tripId).toString() + tr(")");

    query.prepare(strQuery);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Gears!"));
        return;
    }

    QString strFilter(tr(""));
    while (query.next()) {
        strFilter.append(tr("ID=") + query.value(0).toString());
        strFilter.append(tr(" OR "));
    }
    if (!strFilter.isEmpty())
        strFilter=strFilter.remove(strFilter.size()-tr(" OR ").length(),tr(" OR ").length());

    tOperations->relationModel(4)->setFilter(strFilter);

    initMapper1();
}

bool FrmOperation::updateSample()
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //updating the sample structure
    QModelIndex idx=viewOperations->index(tableView->selectionModel()->currentIndex().row(),0);

    m_sample->operationId=idx.data().toInt();
    return true;
}

bool FrmOperation::getNextLabel(QString& strLabel)
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //sending the name
    QModelIndex idx=viewOperations->index(tableView->selectionModel()->currentIndex().row(),3);
    strLabel=idx.data().toString();
    return true;
}
