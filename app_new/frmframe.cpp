#include <QTest>
#include "frmframe.h"
#include "ModelInterface.h"
#include "globaldefs.h"

FrmFrame::FrmFrame(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
GenericTab(0,inSample,inTDateTime,tr("frame"), ruleCheckerPtr, parent,flags){

    setupUi(this);

    m_mapperBinderPtr=0;
    tRefFrame=0;
    tFrameTime=0;
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

    bool bDate, bTime;
    customDtStart->getIsDateTime(bDate,bTime);
    m_tDateTime->insertNewRecord(customDtStart->getIsAuto(),bDate,bTime);
    customDtEnd->getIsDateTime(bDate,bTime);
    m_tDateTime->insertNewRecord(customDtStart->getIsAuto(),bDate,bTime);

    mapper1=0;
    mapper2=0;
    mapperStartDt=0;
    mapperEndDt=0;
    m_submitted=false;

    initUI();
    initMappers();

    while(m_tDateTime->canFetchMore())
        m_tDateTime->fetchMore();

    mapperStartDt->setCurrentIndex(m_tDateTime->rowCount()-2);//just before last
    mapperEndDt->setCurrentIndex(m_tDateTime->rowCount()-1);

    connect(m_mapperBinderPtr, SIGNAL(defaultValuesRead()), this,
        SLOT(unblockCustomDateCtrls()));

    //signal for the rule checker default values
    emit addRecord();
}

FrmFrame::~FrmFrame()
{
    if (tRefFrame!=0) delete tRefFrame;
    if (m_mapperBinderPtr!=0) delete m_mapperBinderPtr;
    if(tFrameTime!=0) delete tFrameTime;
    if (mapper1!=0) delete mapper1;
    if (mapper2!=0) delete mapper2;
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;
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

void FrmFrame::initModels()
{
    //Frame
    tRefFrame=new QSqlRelationalTableModel();
    tRefFrame->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("FR_Frame"),
        QSqlDriver::TableName));
    tRefFrame->setRelation(0, QSqlRelation(tr("FR_Frame"), tr("ID"), tr("Name")));
    tRefFrame->sort(0,Qt::AscendingOrder);
    tRefFrame->select();
    filterTable(tRefFrame->relationModel(0));

    //Frame_Time (Physical frame + time frame!)
    tFrameTime=new QSqlTableModel();
    tFrameTime->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("FR_Time"),
        QSqlDriver::TableName));
    tFrameTime->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tFrameTime->sort(0,Qt::AscendingOrder);
    tFrameTime->select();
}

void FrmFrame::initUI()
{
    radioCopy->setChecked(true);
    pushApply->setEnabled(true);
    pushNext->setEnabled(!pushApply);
}

void FrmFrame::onHideFrameDetails()
{
    int curP=cmbPrexistent->currentIndex();
    int curC=cmbCopy->currentIndex();

    tRefFrame->relationModel(0)->select();

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
    if (tRefFrame==0) return ;

    if (mapper1!=0) delete mapper1;

    mapper1= new QDataWidgetMapper(this);
    mapper1->setModel(tRefFrame);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper1->setItemDelegate(new QSqlRelationalDelegate(this));

    cmbCopy->setModel(tRefFrame->relationModel(0));
    cmbCopy->setModelColumn(
        tRefFrame->relationModel(0)->fieldIndex(tr("Name")));

    if (mapper2!=0) delete mapper2;

    mapper2= new QDataWidgetMapper(this);
    mapper2->setModel(tRefFrame);
    mapper2->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper2->setItemDelegate(new QSqlRelationalDelegate(this));

    cmbPrexistent->setModel(tRefFrame->relationModel(0));
    cmbPrexistent->setModelColumn(
        tRefFrame->relationModel(0)->fieldIndex(tr("Name")));

    mapper1->addMapping(this->cmbPrexistent, 0, tr("currentIndex").toAscii());
    mapper2->addMapping(this->cmbCopy, 0, tr("currentIndex").toAscii());

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

    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1 << mapper2 << mapperStartDt << mapperEndDt;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));
}

bool FrmFrame::getCurrentFrame(int& id)
{
    QModelIndex idx= tRefFrame->relationModel(0)->index(cmbPrexistent->currentIndex(),0);
    if (!idx.isValid()) return false;
    id=tRefFrame->relationModel(0)->data(idx).toInt();
    return true;
}

void FrmFrame::reallyApply()
{
    bool bError=false;

    //We call a stored procedure to see if there are GLS available outside the bin
     QSqlQuery query;
     query.setForwardOnly(true);

     int id= cmbPrexistent->model()->index(cmbPrexistent->currentIndex(),0).data().toInt();

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

        tFrameTime->insertRow(tFrameTime->rowCount());
        QModelIndex idx=tFrameTime->index(tFrameTime->rowCount()-1,1);//id frame
        if (idx.isValid()){
                int idFrame;
                if (getCurrentFrame(idFrame)){
                    tFrameTime->setData(idx,idFrame);
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
            }else bError=true;
        }
        bError=!tFrameTime->submitAll();
    }

    setReadOnly(!bError);

    if (!bError)
    {
        emit showStatus(tr("Record successfully inserted in the database!"));
        m_submitted=true;
        updateSample();//update sample here, because of the save
    }
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

    pushNext->setEnabled(bRO);
    pushApply->setEnabled(!bRO);
}

bool FrmFrame::updateSample()
{
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

    return true;
}

bool FrmFrame::next()
{
    //We force a submitted record on this session, unless its coming here later...

    //if (m_curFrameTime==-1) return false;

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

bool FrmFrame::loadFrameFromSample()
{
    tRefFrame->relationModel(0)->setFilter(tr("FR_Frame.ID=") + QVariant(m_sample->frameId).toString());
    //n.b.: do NOT forget to cast the integers on the filters to *strings*!!!!!

    if (tRefFrame->relationModel(0)->rowCount()!=1){
        emit showError (tr("Could not find this frame!"));
        return false;
    }

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