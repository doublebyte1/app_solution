//#include "globaldefs.h"
#include "frmvesseltype.h"

FrmVesselType::FrmVesselType(Sample* inSample, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
PreviewTab(3,inSample,inTDateTime,tr("Vessel Type"),parent, flags){

    setupUi(this);

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

void FrmVesselType::initMappers()
{
    //NOTHING
}

void FrmVesselType::initMapper1()
{
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
}

void FrmVesselType::previewRow(QModelIndex index)
{
    m_selectedIdx=index;//stores the index
    emit submitted(this->m_index,true);

    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    emit lockControls(true,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->hide();

    QModelIndex idx=this->viewVesselTypes->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this cell!"));
        return;
    }

    QString id=idx.data().toString();

    tSVesselTypes->setFilter(tr("Sampled_Cell_Vessel_Types.ID=")+id);
    if (tSVesselTypes->rowCount()!=1)
        return;

    mapper1->toLast();

    pushNext->setEnabled(true);
}

void FrmVesselType::setPreviewQuery()
{
    if (m_sample==0) return;

    viewVesselTypes->setQuery(
        tr("SELECT     dbo.Sampled_Cell_Vessel_Types.ID, dbo.Ref_Vessel_Types.Name")+
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
    initVesselTypeModel();
}

bool FrmVesselType::onButtonClick(QAbstractButton* button)
{
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tSVesselTypes->revertAll();
        return true;

    } else if (buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){

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

        button->setEnabled(bError);

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
    }else return false;
    return false;
}

void FrmVesselType::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    textComments->clear();
    cmbTypes->setCurrentIndex(-1);

    emit lockControls(false,m_lWidgets);
    buttonBox->button(QDialogButtonBox::Apply)->show();

    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
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
    tr("                            FROM          dbo.Changes_Temp_Vessel")+
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
    tr("                            FROM          dbo.Changes_Temp_Vessel AS Changes_Temp_Vessel_1")+
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

    setPreviewTable(tableView);
    tableView->setModel(viewVesselTypes);
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->hide();
    tableView->setSelectionMode(
        QAbstractItemView::SingleSelection);
    tableView->horizontalHeader()->setClickable(false);
    tableView->horizontalHeader()->setFrameStyle(QFrame::NoFrame);

    //initializing the container for the readonly!
    m_lWidgets << cmbTypes;
    m_lWidgets << textComments;
    m_lWidgets << spinNE;
    m_lWidgets << spinAE;
    m_lWidgets << spinIE;
    m_lWidgets << spinOE;

    pushNext->setEnabled(false);
}

bool FrmVesselType::updateSample()
{
    //updating the sample structure
    QModelIndex idx=viewVesselTypes->index(m_selectedIdx.row(),0);
    if (!idx.isValid()) return false;
    m_sample->vesselTypeId=idx.data().toInt();
    return true;
}

bool FrmVesselType::getNextLabel(QString& strLabel)
{
    //sending the name
    QModelIndex idx=viewVesselTypes->index(m_selectedIdx.row(),1);
    if (!idx.isValid()) return false;
    strLabel=idx.data().toString();
    return true;
}

void FrmVesselType::initVesselTypeModel()
{
    if (tSVesselTypes!=0) delete tSVesselTypes;

    tSVesselTypes=new QSqlRelationalTableModel();
    tSVesselTypes->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Cell_Vessel_Types"),
        QSqlDriver::TableName));
    tSVesselTypes->setRelation(2, QSqlRelation(tr("Ref_Vessel_Types"), tr("ID"), tr("Name")));
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