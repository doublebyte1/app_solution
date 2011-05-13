#include <QTest>
#include "globaldefs.h"
#include "frmcell.h"

FrmCell::FrmCell(Sample* inSample, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
PreviewTab(2,inSample,inTDateTime,tr("Cell"),parent, flags){

    setupUi(this);

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(next()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    connect(toolButton, SIGNAL(clicked()), this,
        SLOT(onShowFrameDetails()));

    tSampCell=0;
    viewCell=0;
    mapper1=0;
    mapperStartDt=0;
    mapperEndDt=0;

    initModels();
    initUI();
    initMappers();
}

FrmCell::~FrmCell()
{
    if (tSampCell!=0) delete tSampCell;
    if (viewCell!=0) delete viewCell;
}

void FrmCell::onShowFrameDetails()
{
    if (!m_selectedIdx.isValid()){
        emit showError(tr("You must select one cell!"));
        return;
    }

    QModelIndex idx=viewCell->index(m_selectedIdx.row(),0);
    if (m_sample->cellId!=idx.data().toInt()){
        emit showError(tr("We only support changes in the last inserted cell!"));
        return;
    }

    //TODO: check if there is overlap with the temporary frame to send a flag
    QList<int> blackList;
    blackList << 1 << 2;
    FrmFrameDetails::Options options=FrmFrameDetails::READ_TMP;
    emit showFrameDetails(FrmFrameDetails::VIEW,FrmFrameDetails::TEMPORARY,
        m_sample, blackList, options);
}

void FrmCell::previewRow(QModelIndex index)
{
    m_selectedIdx=index;//stores the index
    emit submitted(this->m_index,true);

    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->hide();

    QModelIndex idx=viewCell->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }

    QString id=idx.data().toString();

    tSampCell->setFilter(tr("Sampled_Cell.ID=")+id);
    if (tSampCell->rowCount()!=1)
        return;

    mapper1->toLast();

    //Now fix the dates
    idx=tSampCell->index(0,1);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }
    idx=tSampCell->index(0,2);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }
    QString strStartDt=idx.data().toString();

    idx=tSampCell->index(0,3);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
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
    pushNext->setEnabled(true);
}

void FrmCell::setPreviewQuery()
{
    viewCell->setQuery(
tr("SELECT     TOP (100) PERCENT dbo.Sampled_Cell.ID, dbo.Ref_Abstract_LandingSite.Name as [Landing Site], CONVERT(CHAR(10), F1.Date_Local, 103) AS [Start Date], CONVERT(CHAR(10), ") +
tr("                      F2.Date_Local, 103) AS [End Date] ") +
tr("FROM         dbo.Sampled_Cell INNER JOIN") +
tr("                      dbo.GL_Dates AS F1 ON dbo.Sampled_Cell.id_start_date = F1.ID INNER JOIN") +
tr("                      dbo.GL_Dates AS F2 ON dbo.Sampled_Cell.id_end_date = F2.ID INNER JOIN") +
tr("                      dbo.Ref_Abstract_LandingSite ON dbo.Ref_Abstract_LandingSite.ID = dbo.Sampled_Cell.id_abstract_LandingSite ") +
tr("WHERE     (dbo.Sampled_Cell.id_Minor_Strata = ")  + QVariant(m_sample->minorStrataId).toString() + tr(")") +
tr(" ORDER BY dbo.Sampled_Cell.ID DESC")
);

    tableView->hideColumn(0);
    resizeToVisibleColumns(tableView);
}

void FrmCell::initModels()
{
    if (viewCell!=0) delete viewCell;
    viewCell = new QSqlQueryModel;
    viewCell->setHeaderData(0, Qt::Horizontal, tr("Site"));
    viewCell->setHeaderData(1, Qt::Horizontal, tr("Date"));
    viewCell->setHeaderData(2, Qt::Horizontal, tr("Time"));
}

void FrmCell::initUI()
{
    setHeader();

    connect(this, SIGNAL(hideFrameDetails(bool)), toolButton,
        SLOT(setEnabled(bool)));

    toolButton->setEnabled(false);

    this->groupDetails->setVisible(false);

    customDtStart->setIsUTC(false);
    customDtStart->setIsAuto(false);

    customDtEnd->setIsUTC(false);
    customDtEnd->setIsAuto(false);

    connect(customDtStart, SIGNAL(isDateTime(bool,int)), m_tDateTime,
        SLOT(amendDateTimeType(bool,int)));

    connect(customDtEnd, SIGNAL(isDateTime(bool,int)), m_tDateTime,
        SLOT(amendDateTimeType(bool,int)));

    setPreviewTable(tableView);
    tableView->setModel(viewCell);
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->verticalHeader()->hide();
    tableView->setSelectionMode(
        QAbstractItemView::SingleSelection);
    tableView->horizontalHeader()->setClickable(false);
    tableView->horizontalHeader()->setFrameStyle(QFrame::NoFrame);

    //initializing the container for the readonly!S
    m_lWidgets << cmbLS;
    m_lWidgets << customDtStart;
    m_lWidgets << customDtEnd;
    m_lWidgets << textComments;
    m_lWidgets << spinNE;
    m_lWidgets << spinAE;
    m_lWidgets << spinIE;
    m_lWidgets << spinOE;

    pushNext->setEnabled(false);
}

void FrmCell::initMapper1()
{
    if (mapper1!=0) delete mapper1;
    mapper1= new QDataWidgetMapper(this);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    mapper1->setModel(tSampCell);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lOthers;
    lOthers << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12;
    QList<int> lText;
    lText << 13;
    nullDellegate=new NullRelationalDelegate(lOthers,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbLS->setModel(tSampCell->relationModel(4));
    cmbLS->setModelColumn(
        tSampCell->relationModel(4)->fieldIndex(tr("Name")));

    mapper1->addMapping(cmbLS, 4);

    mapper1->addMapping(spinNE, 5);
    mapper1->addMapping(spinNC, 6);
    mapper1->addMapping(spinAE, 7);
    mapper1->addMapping(spinAC, 8);
    mapper1->addMapping(spinIE, 9);
    mapper1->addMapping(spinIC, 10);
    mapper1->addMapping(spinOE, 11);
    mapper1->addMapping(spinOC, 12);

    mapper1->addMapping(textComments,13);
}

void FrmCell::initMappers()
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

void FrmCell::beforeShow()
{
    //The dictionary of SQL relations does *not* respond to filter changes, and therefore
    //we need to initialize a new cell model (and setup the relations) everytime. For this
    //reason, dont bother to initialize it in the beginning.

    initCellModel();
    this->groupDetails->setVisible(false);
    setSourceText(lbSource);
}

bool FrmCell::onButtonClick(QAbstractButton* button)
{
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tSampCell->revertAll();
        return true;

    } else if (buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){

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
                QModelIndex idxStart=tSampCell->index(tSampCell->rowCount()-1,2);
                if (idxStart.isValid()){
                    tSampCell->setData(idxStart,idStart);
                }else bError=true;
            }else bError=true;

            int idEnd;
            if (getDtId(endIdx,idEnd)){
                QModelIndex idxEnd=tSampCell->index(tSampCell->rowCount()-1,3);
                if (idxEnd.isValid()){
                    tSampCell->setData(idxEnd,idEnd);
                }else bError=true;
            }else bError=true;

            if (!bError){
                if (mapper1->submit()){
                    bError=!
                        tSampCell->submitAll();
                    if (bError){
                        if (tSampCell->lastError().type()!=QSqlError::NoError)
                            emit showError(tSampCell->lastError().text());
                        else
                            emit showError(tr("Could not write cell in the database!"));
                    }//mapper1->toLast();
                }else bError=true;
            }
        }
        button->setEnabled(bError);

        emit lockControls(!bError,m_lWidgets);
        if (!bError){
            buttonBox->button(QDialogButtonBox::Apply)->hide();
        }else{
            buttonBox->button(QDialogButtonBox::Apply)->show();
        }

        if (!bError){
            if (!afterApply()) bError=false;
            else{
                toolButton->setEnabled(true);

                while(tSampCell->canFetchMore())
                    tSampCell->fetchMore();

                tSampCell->select();
                QModelIndex idx=tSampCell->index(tSampCell->rowCount()-1,0);
                if (!idx.isValid()) bError=false;
                else m_sample->cellId=idx.data().toInt();//updating the id here, because of the frame details
                //mapper1->toLast();
            }
        }
        return !bError;
    }else return false;
}

void FrmCell::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(false,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->show();

    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);

    customDtStart->setIsDateTime(true,true,true);
    customDtStart->checkBox()->click();//the click is necessary to imit the relavant signal

    customDtEnd->setIsDateTime(true,true,true);
    customDtEnd->checkBox()->click();//the click is necessary to imit the relevant signal

    textComments->clear();

    toolButton->setEnabled(false);
}

void FrmCell::createRecord()
{
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

    while(tSampCell->canFetchMore())
        tSampCell->fetchMore();

    QModelIndex idx=tSampCell->index(tSampCell->rowCount()-1,1);
    tSampCell->setData(idx,m_sample->minorStrataId);//id_minor_strata

    uI4NewRecord();//init UI
}

void FrmCell::initCellModel()
{
    if (tSampCell!=0) delete tSampCell;

    tSampCell=new QSqlRelationalTableModel();
    tSampCell->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Cell"),
        QSqlDriver::TableName));
    tSampCell->setRelation(4, QSqlRelation(tr("Ref_Abstract_LandingSite"), tr("ID"), tr("Name")));
    tSampCell->relationModel(4)->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tSampCell->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tSampCell->sort(0,Qt::AscendingOrder);
    tSampCell->select();

    setPreviewModel(tSampCell);

}

void FrmCell::filterModel4Combo()
{
    QString strQuery =
tr("SELECT     dbo.FR_GLS2ALS.id_abstract_landingsite AS ls, dbo.Ref_Minor_Strata.id_gls, dbo.FR_GLS2ALS.id_gls AS Expr1") +
tr(" FROM         dbo.Ref_Minor_Strata INNER JOIN") +
tr("                      dbo.FR_Time ON dbo.Ref_Minor_Strata.id_frame_time = dbo.FR_Time.ID INNER JOIN") +
tr("                      dbo.FR_Frame ON dbo.FR_Time.id_frame = dbo.FR_Frame.ID INNER JOIN") +
tr("                      dbo.FR_Sub_Frame ON dbo.FR_Frame.ID = dbo.FR_Sub_Frame.id_frame INNER JOIN") +
tr("                      dbo.FR_GLS2ALS ON dbo.FR_Sub_Frame.ID = dbo.FR_GLS2ALS.id_sub_frame AND dbo.Ref_Minor_Strata.id_gls = dbo.FR_GLS2ALS.id_gls") +
tr(" WHERE     (dbo.Ref_Minor_Strata.ID = :id)")
;

    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(0,m_sample->minorStrataId);
    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Landing Sites!"));
        return;
    }

    QString strFilter(tr(""));
     while (query.next()) {
        strFilter.append(tr("ID=") + query.value(0).toString());
        strFilter.append(tr(" OR "));
     }
     if (!strFilter.isEmpty())
         strFilter=strFilter.remove(strFilter.size()-tr(" OR ").length(),tr(" OR ").length());

    tSampCell->relationModel(4)->setFilter(strFilter);
    //first we set the relation; then we create a mapper and assign the (amended) model to the mapper;
    initMapper1();
}

bool FrmCell::updateSample()
{
    //updating the sample structure
    QModelIndex idx=viewCell->index(m_selectedIdx.row(),0);
    if (!idx.isValid()) return false;
    m_sample->cellId=idx.data().toInt();
    return true;
}

bool FrmCell::getNextLabel(QString& strLabel)
{
    //sending the name
    QModelIndex idx=viewCell->index(m_selectedIdx.row(),1);
    if (!idx.isValid()) return false;
    strLabel=idx.data().toString();
    return true;
}
