//#include "globaldefs.h"
#include "frmvesseltype.h"

FrmVesselType::FrmVesselType(Sample* inSample, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
GenericTab(3,inSample,inTDateTime,parent, flags){

    setupUi(this);

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(goForward()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    tVesselType=0;

    //initMappers();
}

FrmVesselType::~FrmVesselType()
{
    if (tVesselType!=0) delete tVesselType;
}

void FrmVesselType::initMappers()
{
    //TODO: implement this later
}

void FrmVesselType::initUI()
{
    setHeader();

    if (tVesselType==0) return;

    this->listTypes->setModel(tVesselType);
    this->listTypes->setModelColumn(0);
    this->listTypes->setAutoFillBackground(true);
    this->listTypes->setAlternatingRowColors(true);

}

void FrmVesselType::onShowForm()
{
    initModels();
    initUI();
}

void FrmVesselType::initModels()
{
    if (m_sample==0) return;

     tVesselType = new QSqlQueryModel;

//selects all vessel types presents in the cell
QString strQuery=
tr ("SELECT DISTINCT dbo.Ref_Vessel_Types.Name") +
tr(" FROM         dbo.FR_ALS2Vessel INNER JOIN") +
tr("                      dbo.Ref_Vessels ON dbo.FR_ALS2Vessel.vesselID = dbo.Ref_Vessels.VesselID INNER JOIN") +
tr("                      dbo.Ref_Vessel_Types ON dbo.Ref_Vessels.VesselType = dbo.Ref_Vessel_Types.ID") +
tr(" WHERE     (dbo.FR_ALS2Vessel.id_sub_frame =") +
tr("                          (SELECT     ID") +
tr("                            FROM          dbo.FR_Sub_Frame") +
tr("                            WHERE      (Type =")+
tr("                                                       (SELECT     ID") +
tr("                                                         FROM          dbo.Ref_Frame") +
tr("                                                         WHERE      (Name = 'root'))) AND (id_frame = [frameId]))) AND (dbo.FR_ALS2Vessel.id_abstract_landingsite =") +
tr("                          (SELECT     id_abstract_LandingSite") +
tr("                            FROM          dbo.Sampled_Cell") +
tr("                            WHERE      (ID = [cellId]))) AND (dbo.FR_ALS2Vessel.vesselID NOT IN") +
tr("                          (SELECT     VesselID") +
tr("                            FROM          dbo.Changes_Temp_Vessel") +
tr("                            WHERE      (id_cell = [cellId]) AND") +
tr(" (FROM_LS =") +
tr("                            (SELECT     id_abstract_landingsite FROM Sampled_Cell Where ID=[cellId])") +
tr(" UNION") +
tr(" SELECT DISTINCT dbo.Ref_Vessel_Types.Name") +
tr(" FROM         dbo.Ref_Vessels INNER JOIN") +
tr("                      dbo.Ref_Vessel_Types ON dbo.Ref_Vessels.VesselType = dbo.Ref_Vessel_Types.ID") +
tr(" WHERE     (dbo.Ref_Vessels.VesselID IN") +
tr("                          (SELECT     VesselID") +
tr("                            FROM          dbo.Changes_Temp_Vessel") +
tr("                            WHERE      (id_cell = [cellId]) AND TO_LS=") +
tr("                            (SELECT     id_abstract_landingsite FROM Sampled_Cell Where ID=[cellId]) )))");

qDebug() << QVariant(m_sample->frameId).toString() << endl;
strQuery.replace("[frameId]",QVariant(m_sample->frameId).toString());
strQuery.replace("[cellId]",QVariant(m_sample->cellId).toString());

qDebug() << strQuery << endl;
tVesselType->setQuery(strQuery);

     //model->setHeaderData(0, Qt::Horizontal, tr("Name"));
     //model->setHeaderData(1, Qt::Horizontal, tr("Salary"));

}