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
    pFrmVesselType=0;
    pFrmVessel=0;
    pFrmTrip=0;
    pFrmPrjPage=0;
    toolbar=0;
    //m_bTabsDefined=false;

    setupUi(this);

    initUi();
    //initTabs();
}

MainFrm::~MainFrm()
{
    tabWidget->disconnect();
    vTabs.clear();
    if (pFrmFrame!=0) delete pFrmFrame;
    if (pFrmMinorStrata!=0) delete pFrmMinorStrata;
    if (pFrmFrameDetails!=0) delete pFrmFrameDetails;
    if (pFrmCell!=0) delete pFrmCell;
    if (pFrmVesselType!=0) delete pFrmVesselType;
    if (pFrmVessel!=0) delete pFrmVessel;
    if (pFrmTrip!=0) delete pFrmTrip;
    if (pFrmPrjPage!=0) delete pFrmPrjPage;
    if (toolbar!=0) delete toolbar;
    //n.b.: delete these in the end, as they are used by the forms!
    if (tDateTime!=0) delete tDateTime;
    if (sSample!=0) delete sSample;
}

void MainFrm::initUi()
{
    //read this from the app settings
    this->setWindowTitle(qApp->applicationName() + qApp->applicationVersion());

     connect(actionAbout_Qt, SIGNAL(triggered()),qApp,
        SLOT(aboutQt () ),Qt::UniqueConnection);

     connect(actionAbout_this_project, SIGNAL(triggered()),this,
        SLOT(aboutThisProject () ),Qt::UniqueConnection);

     connect(actionLoad, SIGNAL(triggered()),this,
        SLOT(loadFile () ),Qt::UniqueConnection);

     connect(actionSave, SIGNAL(triggered()),this,
        SLOT(writeFile () ),Qt::UniqueConnection);

    toolbar=addToolBar(tr("Main Toolbar"));
    toolbar->setFloatable(true);
    toolbar->setMovable(true);
    toolbar->addAction(this->actionNew);
    toolbar->addAction(this->actionLoad);
    toolbar->addAction(this->actionSave);
    toolbar->addSeparator();
    toolbar->addAction(this->actionAbout_this_project);
    toolbar->addAction(this->actionAbout_Qt);
}

void MainFrm::loadFile()
{
    //TODO: open file
}

void MainFrm::writeFile()
{
    //TODO: check if a project is open or new
    QString fileName = QFileDialog::getSaveFileName(this,
     tr("Save Project"), "", tr("Project Files (*.xml)"));

    if (!fileName.isEmpty())
        CreateXMLFile(fileName);
}

void MainFrm::CreateXMLFile(const QString strFileName)
{
	QFile file(strFileName);
 
	/*open a file */
	if (!file.open(QIODevice::WriteOnly))
	{
	/* show wrror message if not able to open file */
	QMessageBox::warning(0, "Read only", "The file is in read only mode");
	}	
	else
	{
		/*if file is successfully opened then create XML*/
		QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();
		/* set device (here file)to streamwriter */
		xmlWriter->setDevice(&file);
		/* Writes a document start with the XML version number version. */
		xmlWriter->writeStartDocument();
		/* Writes a start element with name,
		* Subsequent calls to writeAttribute() will add attributes to this element.
		 here we creating a tag <persons>*/
		xmlWriter->writeStartElement("persons");
 	    /*end tag persons*/
		xmlWriter->writeEndElement();
		/*end document */
		xmlWriter->writeEndDocument();
               delete xmlWriter;
	}
}

void MainFrm::aboutThisProject()
{
    if (pFrmPrjPage==0)
    {
        pFrmPrjPage=new FrmPrjPage;
    }
    if (pFrmPrjPage->isVisible()==false)
        pFrmPrjPage->showMaximized();
}

void MainFrm::resetTabs()
{
        tabWidget->disconnect();

        while (tabWidget->count()>0){
            this->tabWidget->removeTab(tabWidget->count()-1);
        }

        tabWidget->repaint();
        vTabs.clear();

        if (pFrmCell!=0) {delete pFrmCell; pFrmCell=0;}
        if (pFrmFrameDetails!=0) {delete pFrmFrameDetails; pFrmFrameDetails=0;}
        if (pFrmMinorStrata!=0) {delete pFrmMinorStrata; pFrmMinorStrata=0;}
        if (pFrmFrame!=0) {delete pFrmFrame; pFrmFrame=0;}
        if (pFrmVesselType!=0) {delete pFrmVesselType; pFrmVesselType=0;}
        if (pFrmVessel!=0) {delete pFrmVessel; pFrmVessel=0;}
        if (pFrmTrip!=0) {delete pFrmTrip; pFrmTrip=0;}
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

void MainFrm::initPreviewTab(PreviewTab* tab)
{
    vTabs.push_back(tab);
}

void MainFrm::initTabs()
{
    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    statusShow(tr("Wait..."));

        resetTabs();

        pFrmFrame=new FrmFrame(sSample,tDateTime);

         connect(pFrmFrame, SIGNAL(isLogBook(bool)), this,
        SLOT(rearrangeTabs(bool)),Qt::UniqueConnection);

         connect(pFrmFrame, SIGNAL(submitted(int,bool)), this,
        SLOT(addTab(int,bool)),Qt::UniqueConnection);

        vTabs.push_back(pFrmFrame);
        this->tabWidget->insertTab(0,pFrmFrame, pFrmFrame->title());

        pFrmMinorStrata=new FrmMinorStrata(sSample,tDateTime);
        initPreviewTab(pFrmMinorStrata);
        pFrmCell=new FrmCell(sSample,tDateTime);
        initPreviewTab(pFrmCell);
        pFrmVesselType=new FrmVesselType(sSample,tDateTime);
        initPreviewTab(pFrmVesselType);
        pFrmVessel=new FrmVessel(sSample,tDateTime);
        initPreviewTab(pFrmVessel);
        pFrmTrip=new FrmTrip(sSample,tDateTime);
        initPreviewTab(pFrmTrip);

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

             connect(vTabs.at(i), SIGNAL(showFrameDetails(const FrmFrameDetails::Mode, const FrmFrameDetails::Persistence, Sample*,QList<int>&, const FrmFrameDetails::Options)), this,
            SLOT(showFrameDetails(const FrmFrameDetails::Mode, const FrmFrameDetails::Persistence, Sample*,QList<int>&, const FrmFrameDetails::Options)),Qt::UniqueConnection);

             connect(pFrmFrameDetails, SIGNAL(hideFrameDetails(bool)), vTabs.at(i),
            SIGNAL(hideFrameDetails(bool)),Qt::UniqueConnection);

             connect(vTabs.at(i), SIGNAL(showError(QString,bool)), this,
            SLOT(displayError(QString,bool)),Qt::UniqueConnection);

             connect(vTabs.at(i), SIGNAL(showStatus(QString)), this,
            SLOT(statusShow(QString)),Qt::UniqueConnection);

             if (i < vTabs.size()-1){
                 connect(vTabs.at(i), SIGNAL(forward(const QString)), vTabs.at(i+1),
                SLOT(fillHeader(const QString)),Qt::UniqueConnection);

                 connect(vTabs.at(i), SIGNAL(forward(const QString)), vTabs.at(i+1),
                SLOT(onShowForm()),Qt::UniqueConnection);
             }

             if (i>0)
                 tabWidget->setTabEnabled(i,false);

         }

    statusShow(tr("Sampling Operation successfully initialized."));
    qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
}

void MainFrm::rearrangeTabs(bool bLogBook)
{
    //We only want to do this (the first time we press next, and therefore using this flag...)
    if (bLogBook)
    {
        vTabs.remove(2,2);
        updateIndexes(2);
    }
}


void MainFrm::updateIndexes(const int from)
{
     for (int i = from; i < vTabs.size(); ++i) {
         vTabs.at(i)->setIndex(i);
     }

     for (int i = from-1; i < vTabs.size()-1; ++i) {
         connect(vTabs.at(i), SIGNAL(forward(const QString)), vTabs.at(i+1),
        SLOT(fillHeader(const QString)),Qt::UniqueConnection);

         connect(vTabs.at(i), SIGNAL(forward(const QString)), vTabs.at(i+1),
        SLOT(onShowForm()),Qt::UniqueConnection);
     }

}


void MainFrm::addTab(int idx, bool bOk)
{
    if (bOk && tabWidget->count()==(idx+1) && idx< vTabs.size()-1){
        this->tabWidget->insertTab(vTabs.size()
        ,vTabs.at(idx+1), vTabs.at(idx+1)->title());
    }
}

void MainFrm::navigateThroughTabs(const bool bNext, const int idx)
{
    tabWidget->blockSignals(true);//lets block the signals to prevent entering the next again...

    if (bNext){
        if (idx<tabWidget->count()){
            addTab(idx,true);
            tabWidget->setCurrentIndex(idx+1);
        }
    }else{
        if (idx>0){
            tabWidget->setCurrentIndex(idx-1);
        }
    }

    tabWidget->blockSignals(false);//and unblock...
}

void MainFrm::hideFrameDetails()
{
    pFrmFrameDetails->hide();
    tabWidget->show();
    //emit hideFrameDetails(bCommited);
}

void MainFrm::showFrameDetails(const FrmFrameDetails::Mode mode,
                               const FrmFrameDetails::Persistence persistence,Sample* sample,
                               QList<int>& blackList, const FrmFrameDetails::Options options){
    pFrmFrameDetails->setFrameDetails(mode,persistence,sample,blackList, options);
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
