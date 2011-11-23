#include <QTest>
#include "frmframe.h"
#include "ModelInterface.h"
#include "globaldefs.h"

FrmFrame::FrmFrame(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
PreviewTab(0,inSample,inTDateTime,tr("frame"), ruleCheckerPtr, parent,flags){

    setupUi(this);

    lbHeader->setVisible(false);//Always hidden!
    lbHeader->clear();
    tFrameTime=0;
    viewFrameTime=0;
    frModel=0;
    mapper=0;
    mapperStartDt=0;
    mapperEndDt=0;
    m_submitted=false;
    m_curMode=FrmFrameDetails::NONE;
    m_bInsert=false;
    m_bSampling=false;

    m_tabsDefined=false;

    blockCustomDateCtrls();

    customDtStart->setIsDateTime(true,false,false);
    customDtStart->setIsUTC(false);
    customDtStart->setIsAuto(false);

    customDtEnd->setIsDateTime(true,false,false);
    customDtEnd->setIsUTC(false);
    customDtEnd->setIsAuto(false);

    connect(toolView, SIGNAL(clicked()), this,
        SLOT(onShowFrameDetails()));//TODO:change curidex to grabb the id

    connect(toolEdit, SIGNAL(clicked()), this,
    SLOT(onShowFrameDetails()));

    connect(this, SIGNAL(hideFrameDetails(bool)), this,
        SLOT(onHideFrameDetails()));

    connect(toolProcess, SIGNAL(clicked()), this,
        SIGNAL(showFrmSampling()));

    connect(this, SIGNAL(hideFrmSampling(bool)), this,
        SLOT(onHideFrmSampling(bool)));

    initModels();
    initUI();
    initMappers();

    setLoading(true);

    onShowForm();
}

FrmFrame::~FrmFrame()
{
    if (tFrameTime!=0) delete tFrameTime;
    if (viewFrameTime!=0) delete viewFrameTime;
    if (frModel!=0) delete frModel;
    if (mapper!=0) delete mapper;
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;
}

void FrmFrame::setPreviewQuery()
{
    viewFrameTime->setQuery(
        tr("SELECT     dbo.FR_Time.ID, dbo.FR_Frame.Name, CONVERT(CHAR(10), A.Date_Local, 103) AS [Lower Limit], CONVERT(CHAR(10), B.Date_Local, 103) AS [Upper Limit],")+
        tr("                  dbo.FR_Time.id_frame") +
        tr(" FROM         dbo.FR_Time INNER JOIN") +
        tr("                  dbo.GL_Dates AS A ON dbo.FR_Time.id_start_dt = A.ID INNER JOIN")+
        tr("                 dbo.GL_Dates AS B ON dbo.FR_Time.id_end_dt = B.ID INNER JOIN")+
        tr("                  dbo.FR_Frame ON dbo.FR_Time.id_frame = dbo.FR_Frame.ID")+
        tr(" WHERE     (dbo.FR_Time.comments NOT LIKE '%n/a%')") +
        tr(" ORDER BY dbo.FR_Time.ID DESC")
        //Important: do not show the n/a record!
    );

    tableView->hideColumn(0);
    tableView->hideColumn(4);
    resizeToVisibleColumns(tableView);
}

void FrmFrame::uI4NewRecord()
{
    genericUI4NewRecord();
    groupProcess->setEnabled(false);
}

void FrmFrame::beforeShow()
{
    this->groupDetails->setVisible(false);
}

void FrmFrame::editFinished()
{
    setPreviewQuery();
    emit lockControls(true,m_lWidgets);
    groupProcess->setEnabled(false);
    //everything went ok, so we can check it off!
    pushEdit->setChecked(false);
}

void FrmFrame::onEditLeave(const bool bFinished, const bool bDiscarded)
{
    if (!bFinished){
        emit setFrmSamplingMode(FrmSampling::EDIT);
    }else{
        if (!bDiscarded){
            emit applyChanges2FrmSampling(!bDiscarded);
            return;
        }else{
            pushEdit->setChecked(false);
        }
    }
    groupProcess->setEnabled(!bFinished);
}

bool FrmFrame::applyChanges()
{
    bool bError=true;

    QString strError;
    if (!checkDependantDates(tr("Fr_Time"), customDtStart->dateTime(),
        customDtEnd->dateTime(),tr("Fr_Time"),m_sample->frameTimeId, strError))
    {
        emit showError(strError);
    }else{

        int cur= mapper->currentIndex();
        bError=!submitMapperAndModel(mapper);
        if (!bError){
            mapper->setCurrentIndex(cur);
            int curStart, curEnd;
            curStart=mapperStartDt->currentIndex();
            curEnd=mapperEndDt->currentIndex();

            bError=submitDates(mapperStartDt, mapperEndDt);

            if (!bError){
                mapperStartDt->setCurrentIndex(curStart);
                mapperEndDt->setCurrentIndex(curEnd);
            }

        }
    }

    //pushEdit->setChecked(bError);
    emit editLeave(true,false);
    return !bError;
}

void FrmFrame::createRecord()
{
    if (m_bSampling){
        emit showError(tr("You can not insert a new record, before you have completed this one: \n define the sampling process!"));
        return;
    }

    genericCreateRecord();

    mapper->toLast();

    bool bDate, bTime;
    customDtStart->getIsDateTime(bDate,bTime);
    m_tDateTime->insertNewRecord(customDtStart->getIsAuto(),bDate,bTime);
    customDtEnd->getIsDateTime(bDate,bTime);
    m_tDateTime->insertNewRecord(customDtStart->getIsAuto(),bDate,bTime);

    while(m_tDateTime->canFetchMore())
        m_tDateTime->fetchMore();

    mapperStartDt->setCurrentIndex(m_tDateTime->rowCount()-2);//just before last
    mapperEndDt->setCurrentIndex(m_tDateTime->rowCount()-1);

    connect(m_mapperBinderPtr, SIGNAL(defaultValuesRead()), this,
        SLOT(unblockCustomDateCtrls()));

    m_bInsert=true;

    uI4NewRecord();//init UI

    //signal for the rule checker default values
    emit addRecord();

    //signal for the FrmSampling
    emit setFrmSamplingMode(FrmSampling::CREATE);
}

bool FrmFrame::updateFrameSample(const QModelIndex index)
{
    return updateFrameSampleParts(index) && updateSample(index);
}

bool FrmFrame::updateFrameSample()
{
    return updateFrameSampleParts() && updateSample();
}

bool FrmFrame::updateFrameSampleParts(const QModelIndex index)
{
    QModelIndex idx2=viewFrameTime->index(index.row(),4);

    //frame id
    if (!idx2.isValid()) return false;
    m_sample->frameId=idx2.data().toInt();

    //logbook
    bool bLogbook;
    if (!isLogBook(m_sample->frameId,bLogbook)) return false;
    m_sample->bLogBook=bLogbook;

    return true;
}

bool FrmFrame::updateFrameSampleParts()
{
    //check if there is a selection
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //updating the sample structure
    QModelIndex idx=tableView->model()->index(tableView->selectionModel()->currentIndex().row(),0);

    if (!idx.isValid()) return false;

    return updateFrameSampleParts(idx);
}

void FrmFrame::previewRow(QModelIndex index)
{
    if (m_bSampling) return;

    if (!index.isValid()) return;

    QModelIndex idx=tableView->model()->index(index.row(),0);
    if (!updateFrameSample(idx)){
        emit showError(tr("Could not update sample with values of this row!"));
        return;
    }

    //its on a new record
    if (!discardNewRecord()) return;

    //its on a edit
    if (pushEdit->isChecked()){
        pushEdit->setChecked(false);
        if (!editRecord(false)) return;
    }

    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    groupProcess->setEnabled(false);

    buttonBox->button(QDialogButtonBox::Apply)->setVisible(false);
    buttonBox->button(QDialogButtonBox::Close)->setVisible(true);

    pushNew->setEnabled(true);
    pushEdit->setEnabled(true);
    pushRemove->setEnabled(true);

    QModelIndex pIdx;
    if (!translateIndex(index,pIdx)) return;

    idx=viewFrameTime->index(index.row(),0);

    mapper->setCurrentModelIndex(pIdx);

    blockCustomDateCtrls();

    //Now fix the dates
    idx=tFrameTime->index(pIdx.row(),2);
    if (!idx.isValid()){
        emit showError (tr("Could not preview start date of this sampling frame!"));
        return;
    }

    QString strStartDt=idx.data().toString();

    idx=tFrameTime->index(pIdx.row(),3);
    if (!idx.isValid()){
        emit showError (tr("Could not preview end date of this sampling frame!"));
        return;
    }
    QString strEndDt=idx.data().toString();

    m_tDateTime->setFilter(tr("ID=") + strStartDt + tr(" OR ID=") + strEndDt);

    if (m_tDateTime->rowCount()!=2)
        return;

    mapperEndDt->toLast();
    mapperStartDt->setCurrentIndex(mapperEndDt->currentIndex()-1);

    unblockCustomDateCtrls();

}

void FrmFrame::onItemSelection()
{
    //if (!pushEdit->isChecked())
    pushNext->setEnabled(tableView->selectionModel()->hasSelection() && !m_bSampling);
}

void FrmFrame::blockCustomDateCtrls()
{
    //block signals here because of the rule binder!
    customDtStart->blockSignals(true);
    customDtEnd->blockSignals(true);
}

void FrmFrame::unblockCustomDateCtrls()
{
    //block signals here because of the rule binder!
    customDtStart->blockSignals(false);
    customDtEnd->blockSignals(false);
}


void FrmFrame::showEvent ( QShowEvent * event )
{
    //Since this is the first form, we have to force the call here!
    //if (m_curMode == FrmFrameDetails::NONE && !pushEdit->isChecked())
        //onShowForm();
}


void FrmFrame::initModels()
{
    initFrModel();

    viewFrameTime = new QSqlQueryModel;

    frModel = new QSqlTableModel;
    frModel->setTable("Fr_Frame");
    frModel->select();
}

void FrmFrame::initUI()
{
    setHeader();

    radioCopy->setChecked(true);

    initPreviewTable(tableView,viewFrameTime);
    //tableView->selectRow(0);
    setButtonBox(buttonBox);
    setNewButton(pushNew);
    setEditButton(pushEdit);
    setRemoveButton(pushRemove);
    setNextButton(pushNext);
    setGroupDetails(groupDetails);

    m_lWidgets << groupPhysical;
    m_lWidgets << groupTime;
}

void FrmFrame::initFrModel()
{
    if (tFrameTime!=0) delete tFrameTime;

    tFrameTime=new QSqlRelationalTableModel();
    tFrameTime->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("FR_Time"),
        QSqlDriver::TableName));

    tFrameTime->setRelation(1, QSqlRelation(tr("FR_Frame"), tr("ID"), tr("Name")));

    tFrameTime->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tFrameTime->sort(0,Qt::AscendingOrder);
    tFrameTime->select();
    //filterTable(tFrameTime->relationModel(1));

    setPreviewModel(tFrameTime);
}

void FrmFrame::onHideFrameDetails()
{
    int curP=cmbPrexistent->currentIndex();
    int curC=cmbCopy->currentIndex();

    if (m_curMode==FrmFrameDetails::VIEW){
        cmbPrexistent->setCurrentIndex(curP);
        cmbCopy->setCurrentIndex(curC);
    }else{
        int m=mapper->currentIndex();
        //We have to do all this, to reset the model and the relation!!!!

        if (m_bInsert){
            QModelIndex idx=tFrameTime->index(tFrameTime->rowCount()-1,1);
            if (tFrameTime->isDirty(idx)) tFrameTime->revertAll();
        }

        initFrModel();

        if (m_bInsert)
            genericCreateRecord();

        initMapper2();
        mapper->setCurrentIndex(m);
        cmbPrexistent->setCurrentIndex(cmbPrexistent->count()-1);

        frModel->select();
        cmbCopy->setCurrentIndex(cmbCopy->count()-1);

    }

    m_curMode=FrmFrameDetails::NONE;
}

void FrmFrame::onShowFrameDetails()
{
    if (dynamic_cast<QToolButton*>(QObject::sender())!=0){
        if (QObject::sender()->objectName()==tr("toolView")){
            m_curMode=FrmFrameDetails::VIEW;
            if (cmbPrexistent->currentIndex()!=-1){
                m_sample->frameId=cmbPrexistent->model()->index(cmbPrexistent->currentIndex(),0).data().toInt();
                emit showFrameDetails(FrmFrameDetails::VIEW,FrmFrameDetails::PERMANENT,
                m_sample);
            }
        }else if (QObject::sender()->objectName()==tr("toolEdit")){
            if (radioCopy->isChecked() && cmbCopy->currentIndex()!=-1){
                m_curMode=FrmFrameDetails::EDIT;
                m_sample->frameId=cmbCopy->model()->index(cmbCopy->currentIndex(),0).data().toInt();
                emit showFrameDetails(FrmFrameDetails::EDIT,FrmFrameDetails::PERMANENT,
                m_sample);
            }
            else if (radioCreate->isChecked()){
                m_curMode=FrmFrameDetails::CREATE;
                m_sample->frameId=-1;
                emit showFrameDetails(FrmFrameDetails::CREATE,FrmFrameDetails::PERMANENT,m_sample);
            }
        }
    }
}

void FrmFrame::onHideFrmSampling(bool bSubmitted)
{
    if (pushEdit->isChecked()) return;

    pushEdit->setEnabled(bSubmitted);
    pushRemove->setEnabled(bSubmitted);

    if (bSubmitted){
        m_bSampling=false;
        if (afterApply()){
            groupProcess->setEnabled(false);
            m_bInsert=false;
            m_submitted=true;
            if (!updateFrameSample()){
                emit showError(tr("Could not update sample with values of this row!"));
                return;
            }

        }
    }

    if (!groupDetails->isVisible())
        groupDetails->setVisible(true);
}

void FrmFrame::initMapper2()
{
    emit blockCatchUISignals(true);

    if (tFrameTime==0) return ;
    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
    if (mapper!=0) delete mapper;

    mapper= new QDataWidgetMapper(this);
    mapper->setModel(tFrameTime);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));

    cmbPrexistent->setModel(tFrameTime->relationModel(1));
    cmbPrexistent->setModelColumn(
        tFrameTime->relationModel(1)->fieldIndex(tr("Name")));

    mapper->addMapping(this->cmbPrexistent, 1/*, tr("currentIndex").toAscii()*/);
    //mapper->toLast();

    //connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
      //   this, SLOT(previewRow(QModelIndex)));

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper << mapperStartDt << mapperEndDt;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));

    emit blockCatchUISignals(false);
}

void FrmFrame::initMappers()
{
    cmbCopy->setModel(frModel);
    cmbCopy->setModelColumn(1);

    if (m_tDateTime==0) return;

    if (mapperStartDt!=0) delete mapperStartDt;

    mapperStartDt= new QDataWidgetMapper(this);
    mapperStartDt->setModel(m_tDateTime);
    mapperStartDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperStartDt->setItemDelegate(new QItemDelegate(this));
    mapperStartDt->addMapping(customDtStart,3,tr("dateTime").toAscii());

    if (mapperEndDt!=0) delete mapperEndDt;

    mapperEndDt= new QDataWidgetMapper(this);
    mapperEndDt->setModel(m_tDateTime);
    mapperEndDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperEndDt->setItemDelegate(new QItemDelegate(this));
    mapperEndDt->addMapping(customDtEnd,3,tr("dateTime").toAscii());

    initMapper2();
    mapper->toLast();
}

bool FrmFrame::reallyApply()
{
    bool bError=false;

    //We call a stored procedure to see if there are GLS available outside the bin
     QSqlQuery query;
     query.setForwardOnly(true);

     if (cmbPrexistent->currentIndex()==-1){
        emit showError(tr("You must select a frame!"));
        bError=true;
     }else{

         int id= tFrameTime->relationModel(1)->index(cmbPrexistent->currentIndex(),0).data().toInt();

        int n=0;
        query.prepare("{CALL spCountGLS4Frame(?,?)}");
        query.bindValue(0,id);
        query.bindValue("Number",n,QSql::Out);

         if (!query.exec()){
             emit showError(query.lastError().text());
             bError=true;;
         }

        n = query.boundValue("Number").toInt();

        if (n<1){
            emit showError(tr("There are no Group of Landing Sites for this frame!"));
            bError=true;
        }else{

            bError=submitDates(mapperStartDt, mapperEndDt);

            while(m_tDateTime->canFetchMore())
                m_tDateTime->fetchMore();

            mapperStartDt->setCurrentIndex(m_tDateTime->rowCount()-2);
            mapperEndDt->setCurrentIndex(m_tDateTime->rowCount()-1);

            int startIdx=mapperStartDt->currentIndex();
            int endIdx=mapperEndDt->currentIndex();

            if (bError) {
                emit showError(tr("Could not create dates in the database!"));
            }else{

            //Now insert the record
            while(tFrameTime->canFetchMore())
                tFrameTime->fetchMore();

            //tFrameTime->insertRow(tFrameTime->rowCount());
            QModelIndex idx=tFrameTime->index(tFrameTime->rowCount()-1,1);//id frame
            if (idx.isValid()){
                    tFrameTime->setData(idx,id);
                    QModelIndex idx=tFrameTime->index(tFrameTime->rowCount()-1,2);//start dt
                    if (idx.isValid()){
                        int idStart;
                        if (getDtId(startIdx,idStart)){
                            tFrameTime->setData(idx,idStart);
                            idx=tFrameTime->index(tFrameTime->rowCount()-1,3);//end dt
                            if (idx.isValid()){
                                int idEnd;
                                if (getDtId(endIdx,idEnd)){
                                    tFrameTime->setData(idx,idEnd);
                                }else bError=true;
                            }
                        }else bError=true;
                    }else bError=true;
                }else bError=true;
            }

            bError=!submitMapperAndModel(mapper);

        }

     }
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(bError);

    emit lockControls(!bError,m_lWidgets);

    setPreviewQuery();
    groupProcess->setEnabled(true);
    m_bSampling=true;//waiting for the sampling input...!

    tableView->selectRow(0);
    //updateSample();
    if (!updateFrameSample()){
        emit showError(tr("Could not update sample with values of this row!"));
        bError=true;
    }

    QToolTip::showText(toolProcess->mapToGlobal(toolProcess->pos()), 
        tr("You have just initialized a frame!\n Now before starting to introduce information, ")
        + tr("take a moment to define the sampling technique used to collect this data.\n ")
        + tr("This is very important to allows later to generate the correct estimates. ")
        , toolProcess);
    //toolProcess->setFocus();

    return !bError;
}

void FrmFrame::setReadOnly(const bool bRO)
{
    if (bRO){
        QList<QWidget*> lWidgets;
        lWidgets << this->groupPhysical;
        lWidgets << this->groupTime;
        emit lockControls(true,lWidgets);
    }else{
        if (tFrameTime->lastError().type()!=QSqlError::NoError)
            emit showError(tFrameTime->lastError().text());
        else
            emit showError(tr("Could not submit results!"));
    }
}

bool FrmFrame::isLogBook(const int frameId, bool& bLogbook)
{
    //check which type of frame we have...
    QString strQuery=
    "SELECT     dbo.Ref_Source.Name"
    " FROM         dbo.FR_Frame INNER JOIN"
    "                      dbo.Ref_Source ON dbo.FR_Frame.id_source = dbo.Ref_Source.ID"
    " WHERE     (dbo.FR_Frame.ID = ?)";

    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(0,frameId);
    if (!query.exec()){
        emit showError(query.lastError().text());
        return false;
    }
    if (query.numRowsAffected()<1){
        emit showError(tr("Could not determine the type of this frame!"));
        return false;
    }

    query.first();
    QString strSource=query.value(0).toString();
    if (strSource.compare(qApp->translate("frame", strLogbook),Qt::CaseInsensitive)==0)
        bLogbook=true;
    else if (strSource.compare(qApp->translate("frame", strSampling),Qt::CaseInsensitive)==0)
        bLogbook=false;
    else{
        emit showError(tr("The type of this frame is not usable! (not logbook and not sampling)!"));
        return false;
    }

    return true;
}

bool FrmFrame::getNextLabel(QString& strLabel)
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //sending the name
    QModelIndex idx=viewFrameTime->index(tableView->selectionModel()->currentIndex().row(),1);
    if (!idx.isValid()) return false;
    strLabel=idx.data().toString();
    return true;
}

void FrmFrame::adjustFrmSamplingMode()
{
    if ( !pushEdit->isChecked() ||
        cmbPrexistent->currentText().compare(
                    qApp->translate("null_replacements", strNa))==0 )
                                                                            return;

    //set here if it is logbook or not
    m_sample->frameId=cmbPrexistent->model()->index(cmbPrexistent->currentIndex(),0).data().toInt();
    bool bLogbook;
    if (!isLogBook(m_sample->frameId,bLogbook)){
        emit showError(tr("Could not determine the type of this frame!"));
        return;
    }

    m_sample->bLogBook=bLogbook;

    emit setFrmSamplingMode(FrmSampling::REPLACE);
}
