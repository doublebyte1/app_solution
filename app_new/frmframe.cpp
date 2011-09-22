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
    mapper1=0;
    mapper2=0;
    mapperStartDt=0;
    mapperEndDt=0;
    m_submitted=false;

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

    initModels();
    initUI();
    initMappers();
}

FrmFrame::~FrmFrame()
{
    if (tFrameTime!=0) delete tFrameTime;
    if (viewFrameTime!=0) delete viewFrameTime;
    if (mapper1!=0) delete mapper1;
    if (mapper2!=0) delete mapper2;
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
        tr(" WHERE     (dbo.FR_Time.comments NOT LIKE '%n/a%')")
        //Important: do not show the n/a record!
    );

    tableView->hideColumn(0);
    tableView->hideColumn(4);
    resizeToVisibleColumns(tableView);
}

void FrmFrame::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(false,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->setVisible(true);
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}

void FrmFrame::beforeShow()
{
    this->groupDetails->setVisible(false);
}

void FrmFrame::createRecord()
{
    genericCreateRecord();

    mapper2->toLast();

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

    uI4NewRecord();//init UI

    //signal for the rule checker default values
    emit addRecord();
}

void FrmFrame::previewRow(QModelIndex index)
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->setVisible(false);

    QModelIndex idx=viewFrameTime->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this sampling frame!"));
        return;
    }

    QString id=idx.data().toString();

    tFrameTime->setFilter(tr("Fr_Time.ID=")+id);
    if (tFrameTime->rowCount()!=1)
        return;

    idx=tFrameTime->index(0,1);
    tFrameTime->relationModel(1)->setFilter(tr("Name='")+idx.data().toString()+tr("'"));

    mapper1->toLast();
    mapper2->toLast();

    //Now fix the dates
    idx=tFrameTime->index(0,2);
    if (!idx.isValid()){
        emit showError (tr("Could not preview start date of this sampling frame!"));
        return;
    }

    QString strStartDt=idx.data().toString();

    idx=tFrameTime->index(0,3);
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

}

void FrmFrame::onItemSelection()
{
    pushNext->setEnabled(tableView->selectionModel()->hasSelection());
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
    onShowForm();
}

void FrmFrame::initModels()
{
    //Frame_Time (Physical frame + time frame!)
    tFrameTime=new QSqlRelationalTableModel();
    tFrameTime->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("FR_Time"),
        QSqlDriver::TableName));

    tFrameTime->setRelation(1, QSqlRelation(tr("FR_Frame"), tr("ID"), tr("Name")));

    tFrameTime->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tFrameTime->sort(0,Qt::AscendingOrder);
    tFrameTime->select();
    filterTable(tFrameTime->relationModel(1));

    setPreviewModel(tFrameTime);

     viewFrameTime = new QSqlQueryModel;
}

void FrmFrame::initUI()
{
    setHeader();

    radioCopy->setChecked(true);
    //pushApply->setEnabled(true);
    //pushNext->setEnabled(!pushApply);

    initPreviewTable(tableView,viewFrameTime);
    setButtonBox(buttonBox);
    setGroupDetails(groupDetails);

    m_lWidgets << groupPhysical;
    m_lWidgets << groupTime;
}

void FrmFrame::onHideFrameDetails()
{
    int curP=cmbPrexistent->currentIndex();
    int curC=cmbCopy->currentIndex();

    tFrameTime->relationModel(1)->select();

    if (m_curMode==FrmFrameDetails::VIEW){
        cmbPrexistent->setCurrentIndex(curP);
        cmbCopy->setCurrentIndex(curC);
    }else{
        cmbCopy->setCurrentIndex(cmbCopy->count()-1);
        cmbPrexistent->setCurrentIndex(cmbPrexistent->count()-1);
    }
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

void FrmFrame::initMappers()
{
    if (tFrameTime==0) return ;
    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
    if (mapper1!=0) delete mapper1;

    mapper1= new QDataWidgetMapper(this);
    mapper1->setModel(tFrameTime);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper1->setItemDelegate(new QSqlRelationalDelegate(this));

    cmbCopy->setModel(tFrameTime->relationModel(1));
    cmbCopy->setModelColumn(
        tFrameTime->relationModel(1)->fieldIndex(tr("Name")));

    if (mapper2!=0) delete mapper2;

    mapper2= new QDataWidgetMapper(this);
    mapper2->setModel(tFrameTime);
    mapper2->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper2->setItemDelegate(new QSqlRelationalDelegate(this));

    cmbPrexistent->setModel(tFrameTime->relationModel(1));
    cmbPrexistent->setModelColumn(
        tFrameTime->relationModel(1)->fieldIndex(tr("Name")));

    mapper1->addMapping(this->cmbPrexistent, 1, tr("currentIndex").toAscii());
    mapper2->addMapping(this->cmbCopy, 1, tr("currentIndex").toAscii());

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

    mapper1->toLast();
    mapper2->toLast();

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1 << mapper2 << mapperStartDt << mapperEndDt;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));
}

bool FrmFrame::reallyApply()
{
    bool bError=false;

    //We call a stored procedure to see if there are GLS available outside the bin
     QSqlQuery query;
     query.setForwardOnly(true);

     int id= tFrameTime->relationModel(1)->index(cmbPrexistent->currentIndex(),0).data().toInt();

     //int id= cmbPrexistent->model()->index(cmbPrexistent->currentIndex(),1).data().toInt();

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

        //First insert the dates...
        if (!mapperStartDt->submit() || !mapperEndDt->submit()){
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

                if (mapper2->submit()){
                    bError=!
                        tFrameTime->submitAll();
                    if (bError){
                        if (tFrameTime->lastError().type()!=QSqlError::NoError)
                            emit showError(tFrameTime->lastError().text());
                        else
                            emit showError(tr("Could not write Sampling Frame in the database!"));
                    }//mapper1->toLast();
                }else bError=true;

    }

    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(bError);

    emit lockControls(!bError,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->setVisible(bError);

    if (!bError){
        if (!afterApply()){
            bError=false;
        }else{

            /*
            while(tRefMinorStrata->canFetchMore())
                tRefMinorStrata->fetchMore();

            QModelIndex idx=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,0);
            if (!idx.isValid()) bError=false;
            else m_sample->minorStrataId=idx.data().toInt();//updating the id here, because of the frame details*/
        }
    }

    return !bError;

/*
    setReadOnly(!bError);

    if (!bError)
    {
        emit showStatus(tr("Record successfully inserted in the database!"));
        m_submitted=true;
        updateSample();//update sample here, because of the save
        return true;
    }
    else return false;
    */
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

    //pushNext->setEnabled(bRO);
    //pushApply->setEnabled(!bRO);
}

bool FrmFrame::isLogBook(const int frameId, bool& bLogbook)
{
    //check which type of frame we have...
    QString strQuery=
    tr("SELECT     dbo.Ref_Source.Name") +
    tr(" FROM         dbo.FR_Frame INNER JOIN") +
    tr("                      dbo.Ref_Source ON dbo.FR_Frame.id_source = dbo.Ref_Source.ID") +
    tr(" WHERE     (dbo.FR_Frame.ID = ?)");

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

bool FrmFrame::updateSample()
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //updating the sample structure
    QModelIndex idx=viewFrameTime->index(tableView->selectionModel()->currentIndex().row(),0);

    if (!idx.isValid()) return false;
    m_sample->frameTimeId=idx.data().toInt();

    idx=viewFrameTime->index(tableView->selectionModel()->currentIndex().row(),4);

    if (!idx.isValid()) return false;
    m_sample->frameId=idx.data().toInt();

    bool bLogbook;
    if (!isLogBook(m_sample->frameId,bLogbook)) return false;
    m_sample->bLogBook=bLogbook;

    return true;

/*
    while(tFrameTime->canFetchMore())
    tFrameTime->fetchMore();

    QModelIndex idx=tFrameTime->index(tFrameTime->rowCount()-1,0);
    if (!idx.isValid()){
        emit showError(tr("Could not retrieve index of the last inserted frame!"));
        return false;
    }
    m_sample->frameTimeId=idx.data().toInt();

    idx=tFrameTime->index(tFrameTime->rowCount()-1,1);
    if (!idx.isValid()){
        emit showError(tr("Could not retrieve index of the last inserted frame!"));
        return false;
    }
    m_sample->frameId=idx.data().toInt();

    //check which type of frame we have...
    QString strQuery=
    tr("SELECT     dbo.Ref_Source.Name") +
    tr(" FROM         dbo.FR_Frame INNER JOIN") +
    tr("                      dbo.Ref_Source ON dbo.FR_Frame.id_source = dbo.Ref_Source.ID") +
    tr(" WHERE     (dbo.FR_Frame.ID = ?)");

    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(0,m_sample->frameId);
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
        m_sample->bLogBook=true;
    else if (strSource.compare(qApp->translate("frame", strSampling),Qt::CaseInsensitive)==0)
        m_sample->bLogBook=false;
    else{
        emit showError(tr("The type of this frame is not usable! (not logbook and not sampling)!"));
        return false;
    }

    return true;*/
}
/*
bool FrmFrame::next()
{
    //We force a submitted record on this session, unless its coming here later...
    if (m_tabsDefined){
        emit forward(cmbPrexistent->currentText());
        return true;
    }

    if (m_submitted){

        emit submitted(m_index,true);
        emit isLogBook(m_sample->bLogBook);

        m_tabsDefined=true;
        emit forward(cmbPrexistent->currentText());
        return true;
    }
    emit showError(tr("It was not defined any time frame for this frame!"));
    return false;
}
*/
bool FrmFrame::loadFrameFromSample()
{
    /*
    tFrameTime->relationModel(1)->setFilter(tr("FR_Time.id_frame=") + QVariant(m_sample->frameId).toString());
    //n.b.: do NOT forget to cast the integers on the filters to *strings*!!!!!

    if (tFrameTime->relationModel(1)->rowCount()!=1){
        emit showError (tr("Could not find this frame!"));
        return false;
    }
*/
    tFrameTime->setFilter(tr("FR_Time.ID=") + QVariant(m_sample->frameTimeId).toString());
    if (tFrameTime->rowCount()!=1){
        emit showError (tr("Could not find this frame time!"));
        return false;
    }

    //Now fix the dates
    QModelIndex idx=tFrameTime->index(0,2);
    if (!idx.isValid()){
        emit showError (tr("Could not load the start date of this frame!"));
        return false;
    }
    QString strStartDt=idx.data().toString();
    idx=tFrameTime->index(0,3);
    if (!idx.isValid()){
        emit showError (tr("Could not load the end date of this frame!"));
        return false;
    }
    QString strEndDt=idx.data().toString();

    m_tDateTime->setFilter(tr("ID=") + strStartDt + tr(" OR ID=") + strEndDt);

    if (m_tDateTime->rowCount()!=2){
        emit showError (tr("Could not find this date time!"));
        return false;
    }

    mapperEndDt->toLast();
    mapperStartDt->setCurrentIndex(mapperEndDt->currentIndex()-1);

    initMappers();

    m_submitted=true;
    setReadOnly(true);

    return true;
}