#include <QTest>
#include "mainfrm.h"

MainFrm::MainFrm(QWidget *parent, Qt::WFlags flags):
QMainWindow(parent, flags){

    tDateTime=0;
    pFrmFrame=0;
    pFrmMinorStrata=0;
    pFrmFrameDetails=0;
    pFrmCell=0;
    sSample=0;
    setupUi(this);
    //initTabs();
}

MainFrm::~MainFrm()
{
    if (tDateTime!=0) delete tDateTime;
    if (pFrmFrame!=0) delete pFrmFrame;
    if (pFrmMinorStrata!=0) delete pFrmMinorStrata;
    if (pFrmFrameDetails!=0) delete pFrmFrameDetails;
    if (pFrmCell!=0) delete pFrmCell;
    if (sSample!=0) delete sSample;
}

void MainFrm::resetTabs()
{
        while (tabWidget->count()>0){
            this->tabWidget->removeTab(tabWidget->count()-1);
        }

        tabWidget->repaint();
        vTabs.clear();

        if (pFrmCell!=0) {delete pFrmCell; pFrmCell=0;}
        if (pFrmFrameDetails!=0) {delete pFrmFrameDetails; pFrmFrameDetails=0;}
        if (pFrmMinorStrata!=0) {delete pFrmMinorStrata; pFrmMinorStrata=0;}
        if (pFrmFrame!=0) {delete pFrmFrame; pFrmFrame=0;}
        if (tDateTime!=0) {delete tDateTime; tDateTime=0;}
        if (sSample!=0) {delete sSample; sSample=0;}

        //Dates
        tDateTime= new DateModel();
        tDateTime->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("GL_Dates"),
            QSqlDriver::TableName));
        tDateTime->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tDateTime->setAuto(false);
        tDateTime->select();

        //Sample
        sSample=new Sample;
}

void MainFrm::initTabs()
{
    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    statusShow(tr("Wait..."));

        resetTabs();

        pFrmFrame=new FrmFrame(sSample,tDateTime);
        vTabs.push_back(pFrmFrame);
        this->tabWidget->insertTab(0,pFrmFrame, tr("Frame"));

        pFrmMinorStrata=new FrmMinorStrata(sSample,tDateTime);
        vTabs.push_back(pFrmMinorStrata);
        this->tabWidget->insertTab(1,pFrmMinorStrata, tr("Minor Strata"));

        pFrmCell=new FrmCell(sSample,tDateTime);
        vTabs.push_back(pFrmCell);
        this->tabWidget->insertTab(2,pFrmCell, tr("Cell"));

        pFrmFrameDetails=new FrmFrameDetails();
         connect(pFrmFrameDetails, SIGNAL(hideFrameDetails(bool)), this,
        SLOT(hideFrameDetails()));

         connect(pFrmFrameDetails, SIGNAL(showStatus(QString)), this,
        SLOT(statusShow(QString)));

         connect(pFrmFrameDetails, SIGNAL(showError(QString, const bool)), this,
        SLOT(displayError(QString, const bool)));

        gridLayout->addWidget(pFrmFrameDetails);
        pFrmFrameDetails->hide();

        // Connect all the signals
         for (int i = 0; i < vTabs.size(); ++i) {

             connect(vTabs.at(i), SIGNAL(navigate(const bool, const int)), this,
            SLOT(navigateThroughTabs(const bool, const int)),Qt::UniqueConnection);

             connect(vTabs.at(i), SIGNAL(showFrameDetails(const FrmFrameDetails::Mode, const FrmFrameDetails::Persistence, Sample*,QList<int>&, const bool)), this,
            SLOT(showFrameDetails(const FrmFrameDetails::Mode, const FrmFrameDetails::Persistence, Sample*,QList<int>&,const bool)),Qt::UniqueConnection);

             connect(pFrmFrameDetails, SIGNAL(hideFrameDetails(bool)), vTabs.at(i),
            SIGNAL(hideFrameDetails(bool)),Qt::UniqueConnection);

             connect(vTabs.at(i), SIGNAL(showError(QString,bool)), this,
            SLOT(displayError(QString,bool)),Qt::UniqueConnection);

             connect(vTabs.at(i), SIGNAL(showStatus(QString)), this,
            SLOT(statusShow(QString)),Qt::UniqueConnection);

             if (i < vTabs.size()-1){
                 connect(vTabs.at(i), SIGNAL(forward(const QString)), vTabs.at(i+1),
                SLOT(fillHeader(const QString)),Qt::UniqueConnection);
             }

         }

    statusShow(tr("Sampling Operation successfully initialized."));
    qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
}

void MainFrm::navigateThroughTabs(const bool bNext, const int idx)
{
    if (bNext){
        if (idx<tabWidget->count()){
            tabWidget->setCurrentIndex(idx+1);
        }
    }else{
        if (idx>0){
            tabWidget->setCurrentIndex(idx-1);
        }
    }
}

void MainFrm::hideFrameDetails()
{
    pFrmFrameDetails->hide();
    tabWidget->show();
    //emit hideFrameDetails(bCommited);
}

void MainFrm::showFrameDetails(const FrmFrameDetails::Mode mode,
                               const FrmFrameDetails::Persistence persistence,Sample* sample,
                               QList<int>& blackList, const bool bSupportNewItems){
    pFrmFrameDetails->setFrameDetails(mode,persistence,sample,blackList,bSupportNewItems);
    tabWidget->hide();
    pFrmFrameDetails->show();
}

void MainFrm::displayError(QString strError, const bool bShowMsgBox)
{
    //! Display MsgBox with Error
    /*!
    This implementation of the msgbox functionality
    uses a container for storing the shared_pointers with msgsboxes;
    We need to have pointers, so that they live outside the scope of this function
    and eventually more than one, as multiple error boxes can popup from nested classes.
    To prevent the container from growing forever, we clean it everytime we come to this function
    (b4 adding more boxes!), so its maximum size at a certain moment won't never exceed the number simultaneously displayed msgboxes!
    */

    cleanupMsgBoxes();

    statusShow(strError);
    if (bShowMsgBox){
        m_listMsgBoxes.push_back(MsgBoxPtr(new CustomMsgBox(this)));
        m_listMsgBoxes.last().get()->lbMsg->setWordWrap(true);
        m_listMsgBoxes.last().get()->fillDialog(tr("Error"),strError);
        m_listMsgBoxes.last().get()->show();
    }
}

void MainFrm::cleanupMsgBoxes()
{
    //Cleanup unused pointers!
    for (int i = 0; i < m_listMsgBoxes.length(); ++i){
        if ( !m_listMsgBoxes.at(i).get()->isVisible() )
            m_listMsgBoxes.removeAt(i);
    }
}

void MainFrm::statusShow(QString str)
{
    statusBar()->setStyleSheet(tr(
     "QStatusBar {"
     "    background: "
     "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                     " stop: 0 #FFFF00, stop: 0.4 #FFFF66,"
                                     " stop: 0.5 #FFFF99, stop: 1.0 #FFFFCC)"
     ";"
     "}"));

    statusBar()->showMessage(str);
}

void MainFrm::statusClean(QString str)
{
    if (str.isEmpty() || str.isNull()){
        statusBar()->setStyleSheet(tr(""));
    }
}
