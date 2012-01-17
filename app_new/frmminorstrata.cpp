#include <QTest>
#include "globaldefs.h"
#include "frmminorstrata.h"

FrmMinorStrata::FrmMinorStrata(RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
PreviewTab(1, inRoleDef, inSample,inTDateTime,tr("Minor Strata"), ruleCheckerPtr, parent, flags){

    setupUi(this);

    blockCustomDateCtrls();

    installEventFilters();

    viewMinorStrata=0;
    tRefMinorStrata=0;
    buttonGroup=0;
    mapper1=0;
    mapperStartDt=0;
    mapperEndDt=0;

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(next()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    connect(toolButton, SIGNAL(clicked()), this,
        SLOT(onShowFrameDetails()));

    connect(this, SIGNAL(hideFrameDetails(bool)), this,
        SLOT(onHideFrameDetails()));

    initModels();
    initUI();
    initMappers();

    connect(m_mapperBinderPtr, SIGNAL(defaultValuesRead()), this,
        SLOT(unblockCustomDateCtrls()));
}

FrmMinorStrata::~FrmMinorStrata()
{
    if (tRefMinorStrata!=0) delete tRefMinorStrata;
    if (buttonGroup!=0) delete buttonGroup;
    if (mapper1!=0) delete mapper1;
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;
    if (viewMinorStrata!=0) delete viewMinorStrata;
}

void FrmMinorStrata::onHideFrameDetails()
{
    if (!pushEdit->isChecked()){
        toolButton->setEnabled(false);
        pushNext->setEnabled(true);
        pushPrevious->setEnabled(true);
    }
}

void FrmMinorStrata::onShowFrameDetails()
{
    if (!tableView->selectionModel()->hasSelection()){
        emit showError(tr("You must select one minor strata!"));
        return;
    }

    QList<int> blackList;
    blackList << 1 << 2;//TODO: what are this hardcoded values? tests?
    int options=FrmFrameDetails::READ_TMP;

    if (pushEdit->isChecked()){
        options= options | FrmFrameDetails::CACHE_CHANGES;
    }

    emit showFrameDetails(FrmFrameDetails::VIEW,FrmFrameDetails::TEMPORARY,
        m_sample, blackList, options);
}

bool FrmMinorStrata::getNextLabel(QString& strLabel)
{
    if (!tableView->selectionModel()->hasSelection())
        return false;

    //sending the name
    QModelIndex idx=viewMinorStrata->index(tableView->selectionModel()->currentIndex().row(),1);
    if (!idx.isValid()) return false;
    strLabel=idx.data().toString();
    return true;
}

bool FrmMinorStrata::applyChanges()
{
    bool bError=true;

    QString strError;
    if (!checkDependantDates("Ref_Minor_Strata", customDtStart->dateTime(),
        customDtEnd->dateTime(),"Ref_Minor_Strata",m_sample->minorStrataId, strError))
    {
        emit showError(strError);
    }else{

        int cur= mapper1->currentIndex();
        bError=!submitMapperAndModel(mapper1);
        if (!bError){
            mapper1->setCurrentIndex(cur);
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

    if (!bError) emit editLeave(true,false);
    return !bError;
}

void FrmMinorStrata::editFinished()
{
    setPreviewQuery();
    pushEdit->setChecked(false);
    pushNew->setEnabled(!pushEdit->isChecked());
    pushRemove->setEnabled(!pushEdit->isChecked());
    toolButton->setEnabled(false);
    emit lockControls(true,m_lWidgets);
}

void FrmMinorStrata::onEditLeave(const bool bFinished, const bool bDiscarded)
{
    if (bFinished){

        if (!bDiscarded && m_sample->bLogBook){
            //apply changes to temp frame
            emit applyChanges2FrameDetails();
            return;
        }else{
            editFinished();
        }

    }

    toolButton->setEnabled(!bFinished);
}

void FrmMinorStrata::disableReasonCombo()
{
    if (static_cast<QRadioButton*>(QObject::sender())==0) return;

    cmbReasons->setEnabled(static_cast<QRadioButton*>(QObject::sender())!=radioActive);
}

void FrmMinorStrata::setActiveReason(bool bActive)
{
    if (bActive){
        int index=cmbReasons->findText(qApp->translate("null_replacements", strNa ));
        cmbReasons->setCurrentIndex(index);
    }
}

void FrmMinorStrata::previewRow(QModelIndex index)
{
    //updating the sample
    QModelIndex idx=viewMinorStrata->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this record!"));
        return;
    }

    updateSample(idx);

    if (!abstractPreviewRow(index)){
        emit showError (tr("Could not preview this record!"));
    }else{

        QModelIndex idx=viewMinorStrata->index(index.row(),0);
        if (!idx.isValid()){
            emit showError (tr("Could not preview this minor strata!"));
            return;
        }

        mapper1->toLast();

        //Now fix the dates
        idx=tRefMinorStrata->index(0,1);
        if (!idx.isValid()){
            emit showError (tr("Could not preview this minor strata!"));
            return;
        }
        QString strStartDt=idx.data().toString();
        idx=tRefMinorStrata->index(0,2);
        if (!idx.isValid()){
            emit showError (tr("Could not preview this minor strata!"));
            return;
        }
        QString strEndDt=idx.data().toString();

        m_tDateTime->setFilter("ID=" + strStartDt + " OR ID=" + strEndDt);

        if (m_tDateTime->rowCount()!=2)
            return;

        mapperEndDt->toLast();
        mapperStartDt->setCurrentIndex(mapperEndDt->currentIndex()-1);

    }
}

void FrmMinorStrata::uI4NewRecord()
{
    genericUI4NewRecord();

    lineNew->clear();
    radioActive->click();
    textComments->clear();

    toolButton->setEnabled(false);
}

void FrmMinorStrata::filterModel4Combo()
{
    QString strQuery=
    "SELECT     dbo.FR_F2GLS.id_gls "
    "FROM         dbo.FR_Sub_Frame INNER JOIN"
    "                 dbo.FR_F2GLS ON dbo.FR_Sub_Frame.ID = dbo.FR_F2GLS.id_sub_frame INNER JOIN"
    "                  dbo.FR_Frame INNER JOIN"
    "                  dbo.FR_Time ON dbo.FR_Frame.ID = dbo.FR_Time.id_frame ON dbo.FR_Sub_Frame.id_frame = dbo.FR_Frame.ID "
    "WHERE     (dbo.FR_Time.ID = :id) AND (dbo.FR_Sub_Frame.Type ="
    "                      (SELECT     ID"
    "                        FROM          dbo.Ref_Frame"
    "                        WHERE      (Name = :root)) )";

    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(0,m_sample->frameTimeId);
    query.bindValue(1,qApp->translate("frame", strRoot));

    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Group of Landing Sites!"));
        return;
    }

    QString strFilter(tr(""));
     while (query.next()) {
        strFilter.append(tr("ID=") + query.value(0).toString());
        strFilter.append(tr(" OR "));
     }
     if (!strFilter.isEmpty())
         strFilter=strFilter.remove(strFilter.size()-QString(" OR ").length(),QString(" OR ").length());
     else{
        emit showError(tr("Could not obtain a filter for Group of Landing Sites!"));
        return;
     }

    tRefMinorStrata->relationModel(4)->setFilter(strFilter);
}

void FrmMinorStrata::beforeShow()
{
    this->groupDetails->setVisible(false);
    setSourceText(lbSource,m_sample->bLogBook);
    toolButton->setVisible(m_sample->bLogBook);
}

void FrmMinorStrata::createRecord()
{
    genericCreateRecord();

    mapper1->toLast();

    //TODO: put dates from the frame as default

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

    mapperStartDt->setCurrentIndex(m_tDateTime->rowCount()-2);
    mapperEndDt->setCurrentIndex(m_tDateTime->rowCount()-1);

    QModelIndex idx=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,3);
    tRefMinorStrata->setData(idx,m_sample->frameTimeId);//id_frame_time

    uI4NewRecord();//init UI

    //signal for the rule checker default values
    emit addRecord();
}

bool FrmMinorStrata::reallyApply()
{
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
                QModelIndex idxStart=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,1);
                if (idxStart.isValid()){
                    tRefMinorStrata->setData(idxStart,idStart);
                }else bError=true;
            }else bError=true;

            int idEnd;
            if (getDtId(endIdx,idEnd)){
                QModelIndex idxEnd=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,2);
                if (idxEnd.isValid()){
                    tRefMinorStrata->setData(idxEnd,idEnd);
                }else bError=true;
            }else bError=true;

            if (!bError){
                if (mapper1->submit()){
                    bError=!
                        tRefMinorStrata->submitAll();
                    if (bError){
                        if (tRefMinorStrata->lastError().type()!=QSqlError::NoError)
                            emit showError(tRefMinorStrata->lastError().text());
                        else
                            emit showError(tr("Could not write Minor Strata in the database!"));
                    }//mapper1->toLast();
                }else bError=true;
            }
        }
        //button->setEnabled(bError);
        buttonBox->button(QDialogButtonBox::Apply)->setEnabled(bError);

        emit lockControls(!bError,m_lWidgets);
        buttonBox->button(QDialogButtonBox::Apply)->setVisible(bError);

        if (!bError){
            if (!afterApply()){
                bError=false;
            }else if (m_sample->bLogBook) {

                toolButton->setEnabled(true);

                updateSample();

                QToolTip::showText(toolButton->mapToGlobal(toolButton->pos()), 
                    tr("You have just initialized a minor strata!\n Now before starting to introduce information, ")
                    + tr("take a moment to have a look at the frame.\n ")
                    + tr("If you wish to do any temporary changes, *please do it NOW*! ")
                    , toolButton);

                //lets disable next till we review the frame
                pushNext->setEnabled(false);
                pushPrevious->setEnabled(false);

            }
        }
        return !bError;
}

void FrmMinorStrata::initUI()
{
    setHeader();

    customDtStart->setIsDateTime(true,false,false);
    customDtStart->setIsUTC(false);
    customDtStart->setIsAuto(false);

    customDtEnd->setIsDateTime(true,false,false);
    customDtEnd->setIsUTC(false);
    customDtEnd->setIsAuto(false);

    buttonGroup=new ButtonGroup(this);
    buttonGroup->addButton(radioActive,0);
    buttonGroup->addButton(radioInactive,1);

    initPreviewTable(tableView,viewMinorStrata);
    setButtonBox(buttonBox);
    setGroupDetails(groupDetails);
    setNewButton(pushNew);
    setEditButton(pushEdit);
    setRemoveButton(pushRemove);
    setNextButton(pushNext);
    setPreviousButton(pushPrevious);

    setUIPermissions();

    m_lWidgets << lineNew;
    m_lWidgets << label_3;
    m_lWidgets << cmbGLS;
    m_lWidgets << groupActivity;
    m_lWidgets << radioActive;
    m_lWidgets << radioInactive;
    m_lWidgets << cmbReasons;
    m_lWidgets << label_4;
    m_lWidgets << textComments;
    m_lWidgets << label;
    m_lWidgets << label_2;
    m_lWidgets << customDtStart;
    m_lWidgets << customDtEnd;

    toolButton->setEnabled(false);
}

void FrmMinorStrata::onItemSelection()
{
    //the signal radio button does not work very well, so lets read the value on the table!
    QModelIndex idx=viewMinorStrata->index(tableView->currentIndex().row(),4);

    pushNext->setEnabled(tableView->selectionModel()->hasSelection()
        && idx.data().toBool()==false
        && !toolButton->isEnabled());

    pushPrevious->setEnabled(tableView->selectionModel()->hasSelection()
        && !toolButton->isEnabled());
}

void FrmMinorStrata::setPreviewQuery()
{
    viewMinorStrata->setQuery(
    "SELECT     dbo.Ref_Minor_Strata.ID, dbo.Ref_Minor_Strata.Name, CONVERT(CHAR(10),F1.Date_Local,103) AS [Start Date], CONVERT(CHAR(10),F2.Date_Local,103) AS [End Date], "
    "CASE WHEN dbo.Ref_Minor_Strata.IsClosed=0 THEN 'false' ELSE 'true' END Closed "
    " FROM         dbo.Ref_Minor_Strata INNER JOIN"
    "                      dbo.GL_Dates AS F1 ON dbo.Ref_Minor_Strata.id_start_dt = F1.ID INNER JOIN"
    "                      dbo.GL_Dates AS F2 ON dbo.Ref_Minor_Strata.id_end_dt = F2.ID"
    "                      WHERE     (dbo.Ref_Minor_Strata.id_frame_time = " + QVariant(m_sample->frameTimeId).toString() + ")"
    "                      ORDER BY dbo.Ref_Minor_Strata.ID DESC"
    );

    tableView->hideColumn(0);
    resizeToVisibleColumns(tableView);
}

void FrmMinorStrata::initModels()
{
    //Minor Strata
    tRefMinorStrata=new QSqlRelationalTableModel();
    tRefMinorStrata->setTable(QSqlDatabase().driver()->escapeIdentifier("Ref_Minor_Strata",
        QSqlDriver::TableName));
    tRefMinorStrata->setRelation(4, QSqlRelation("Ref_Group_of_LandingSites", "ID", "Name"));
    tRefMinorStrata->setRelation(6, QSqlRelation("Ref_No_Recording_Activities", "ID", "Name"));
    tRefMinorStrata->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tRefMinorStrata->sort(0,Qt::AscendingOrder);
    tRefMinorStrata->select();

    setPreviewModel(tRefMinorStrata);

    viewMinorStrata = new QSqlQueryModel;
    viewMinorStrata->setHeaderData(0, Qt::Horizontal, tr("Name"));
    viewMinorStrata->setHeaderData(1, Qt::Horizontal, tr("Start"));
    viewMinorStrata->setHeaderData(2, Qt::Horizontal, tr("End"));
    viewMinorStrata->setHeaderData(3, Qt::Horizontal, tr("Closed"));
}

void FrmMinorStrata::initMappers()
{
    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
    if (mapper1!=0) delete mapper1;

    mapper1= new QDataWidgetMapper(this);
    mapper1->setModel(tRefMinorStrata);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lCmb;
    lCmb << 4 << 5 << 6;
    QList<int> lText;
    lText << 7;
    nullDellegate=new NullRelationalDelegate(lCmb,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbGLS->setModel(tRefMinorStrata->relationModel(4));
    cmbGLS->setModelColumn(
        tRefMinorStrata->relationModel(4)->fieldIndex("Name"));

    cmbReasons->setModel(tRefMinorStrata->relationModel(6));
    cmbReasons->setModelColumn(
        tRefMinorStrata->relationModel(6)->fieldIndex("Name"));

    mapper1->addMapping(lineNew, 8);
    mapper1->addMapping(cmbGLS, 4);
    mapper1->addMapping(cmbReasons, 6);
    mapper1->addMapping(buttonGroup,5);
    mapper1->addMapping(textComments,7);

    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;

    mapperStartDt= new QDataWidgetMapper(this);
    mapperStartDt->setModel(m_tDateTime);
    mapperStartDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperStartDt->setItemDelegate(new QItemDelegate(this));
    mapperStartDt->addMapping(customDtStart,2,QString("dateTime").toAscii());

    mapperEndDt= new QDataWidgetMapper(this);
    mapperEndDt->setModel(m_tDateTime);
    mapperEndDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperEndDt->setItemDelegate(new QItemDelegate(this));
    mapperEndDt->addMapping(customDtEnd,2,QString("dateTime").toAscii());

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1 << mapperStartDt << mapperEndDt;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));
}

void FrmMinorStrata::blockCustomDateCtrls()
{
    //block signals here because of the rule binder!
    customDtStart->blockSignals(true);
    customDtEnd->blockSignals(true);
}

void FrmMinorStrata::unblockCustomDateCtrls()
{
    //block signals here because of the rule binder!
    customDtStart->blockSignals(false);
    customDtEnd->blockSignals(false);
}

