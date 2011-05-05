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

    initModels();
    initUI();
    initMappers();
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

}

bool FrmVesselType::next()
{
    return false;
}

void FrmVesselType::onShowForm()
{
    //initModels();
    //initUI();
    setViewQuery();
}

void FrmVesselType::setViewQuery()
{
    QString strQuery(
    tr("SELECT     dbo.Ref_Vessel_Types.Name")+
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

     tVesselType->setQuery(strQuery);

    this->listTypes->setModel(tVesselType);
    this->listTypes->setModelColumn(0);
    this->listTypes->setAutoFillBackground(true);
    this->listTypes->setAlternatingRowColors(true);

}

void FrmVesselType::initModels()
{
    if (m_sample==0) return;
    if (tVesselType!=0) delete tVesselType;

     tVesselType = new QSqlQueryModel();
}