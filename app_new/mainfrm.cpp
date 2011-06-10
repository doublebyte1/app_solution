#include <QTest>
#include "mainfrm.h"

MainFrm::MainFrm(QWidget *parent, Qt::WFlags flags):
QMainWindow(parent, flags){

    tDateTime=0;
    pFrmFrame=0;
    pFrmMinorStrata=0;
    pFrmFrameDetails=0;
    pFrmCell=0;
    sSample=new Sample;
    pFrmVesselType=0;
    pFrmVessel=0;
    pFrmTrip=0;
    pFrmOperation=0;
    pFrmCatch=0;
    pFrmPrjPage=0;
    toolbar=0;

    setAttribute( Qt::WA_AlwaysShowToolTips);

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
    if (pFrmOperation!=0) delete pFrmOperation;
    if (pFrmCatch!=0) delete pFrmCatch;
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

bool MainFrm::readXMLFile(const QString strFileName)
{
    //TODO: add some XML semantic  validation?

    SessionFileParser *handler=new SessionFileParser(sSample);

    QFile file( strFileName );
    QXmlInputSource source( &file );

    QXmlSimpleReader reader;
    reader.setContentHandler( handler );
    reader.setErrorHandler(handler);

    if (!reader.parse( source )){
        delete handler; handler=0;
        return false;
    }

    delete handler; handler=0;
    return true;
}

void MainFrm::loadTabs()
{
    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    statusShow(tr("Wait..."));

        resetTabs();
        initTabs();

        if (pFrmFrame==0) return;
        this->tabWidget->insertTab(0,pFrmFrame, pFrmFrame->title());

        if (sSample->frameId==-1 || sSample->frameTimeId==-1) return;

        if (pFrmFrame->loadFrameFromSample()){

            QVector<int> vSample;
            if (sSample->minorStrataId!=-1) vSample << sSample->minorStrataId;
            if (sSample->cellId!=-1) vSample << sSample->cellId;
            if (sSample->vesselTypeId!=-1) vSample << sSample->vesselTypeId;
            if (sSample->sampVesselId!=-1) vSample << sSample->sampVesselId;
            if (sSample->tripId!=-1) vSample << sSample->tripId;
            if (sSample->operationId!=-1) vSample << sSample->operationId;
            //TODO: add catch?

            if (vSample.size()>1){//We need to read more information
                pFrmFrame->next();

                if (vSample.size() > vTabs.size()){
                    displayError(tr("Could not load project file!"),true);//TODO: improve errors!
                }else{

                    bool bOk=true;
                    int ct=0;
                    QVector<int>::const_iterator it;
                     for (it = vSample.begin(); it != vSample.end(); ++it){
                         if (!vTabs.at(ct)->next()){
                             bOk=false;
                            break;
                         }
                         ct++;
                     }

                    if (bOk) statusShow(tr("Project successfully loaded."));
                    else displayError (tr("Could not load tab ") + vTabs.at(ct)->title() + tr("!"),false);
                }
            }
 
        }else{
            displayError(tr("Could not load project file!"),true);
        }

    qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
}

void MainFrm::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
     tr("Open Project"), tr(""), tr("Project Files (*.xml)"));

    if (!fileName.isEmpty()){
        if (!readXMLFile(fileName))
            this->displayError(tr("Could not parse XML file! Are you sure this is a valid project file?"),true);
        else
            loadTabs();
    }
}

void MainFrm::writeFile()
{
    if ( tabWidget->count() <1 || sSample->frameId==-1 || sSample->frameTimeId==-1){
        QMessageBox::information(this, tr("Medfisis"),
                                        tr("There is nothing to save."),
                                        QMessageBox::Ok);
         return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
     tr("Save Project"), "", tr("Project Files (*.xml)"));

    if (!fileName.isEmpty()){
        if (!CreateXMLFile(fileName))
            this->displayError(tr("Could not write XML file!"),true);
    }
}

bool MainFrm::CreateXMLFile(const QString strFileName)
{
    QFile file(strFileName);

    /*open a file */
    if (!file.open(QIODevice::WriteOnly))
    {
        /* show error message if not able to open file */
        QMessageBox::warning(0, tr("Read only"), tr("The file is in read only mode"));
    }
    else
    {
        if (sSample==0) return false;

        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();//top
            stream.writeStartElement(tr("session"));
                stream.writeTextElement(tr("title"), tr("Session File"));
                stream.writeTextElement(tr("description"), 
                    tr("This is a session file, which stores the point of the application where the user was.\n Please do *NOT* edit it, unless you know what you are doing!"));
                /*
                stream.writeStartElement(tr("connection"));
                stream.writeAttribute(tr("alias"), QSqlDatabase::database().connectionName());
                    stream.writeTextElement(tr("database"), QSqlDatabase::database().databaseName());
                    stream.writeTextElement(tr("driver"), QSqlDatabase::database().driverName());
                    stream.writeTextElement(tr("host"), QSqlDatabase::database().hostName());
                    stream.writeTextElement(tr("user"), QSqlDatabase::database().userName());
                stream.writeEndElement();//connection*/
                stream.writeStartElement(tr("indexes"));

                    stream.writeTextElement(tr("isLogbook"), QVariant(sSample->bLogBook).toString());
                    stream.writeTextElement(tr("frameId"), QVariant(sSample->frameId).toString());
                    stream.writeTextElement(tr("frameTimeId"), QVariant(sSample->frameTimeId).toString());
                    if (sSample->minorStrataId!=-1) stream.writeTextElement(tr("minorStrataId"), QVariant(sSample->minorStrataId).toString());
                    if (sSample->cellId!=-1) stream.writeTextElement(tr("cellId"), QVariant(sSample->cellId).toString());
                    if (sSample->vesselTypeId!=-1) stream.writeTextElement(tr("vesselTypeId"), QVariant(sSample->vesselTypeId).toString());
                    if (sSample->sampVesselId!=-1) stream.writeTextElement(tr("sampVesselId"), QVariant(sSample->sampVesselId).toString());
                    if (sSample->tripId!=-1) stream.writeTextElement(tr("tripId"), QVariant(sSample->tripId).toString());
                    if (sSample->operationId!=-1) stream.writeTextElement(tr("operationId"), QVariant(sSample->operationId).toString());

                stream.writeEndElement();//indexes
            stream.writeEndElement();//top
        stream.writeEndDocument();

        return true;
    }

    return false;
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
        if (pFrmOperation!=0) {delete pFrmOperation; pFrmOperation=0;}
        if (pFrmCatch!=0) {delete pFrmCatch; pFrmOperation=0;}
        if (tDateTime!=0) {delete tDateTime; tDateTime=0;}

        //Dates
        tDateTime= new DateModel();
        tDateTime->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("GL_Dates"),
            QSqlDriver::TableName));
        tDateTime->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tDateTime->setAuto(false);
        tDateTime->select();
}

void MainFrm::initPreviewTab(PreviewTab* tab)
{
    vTabs.push_back(tab);
}

void MainFrm::newTabs()
{
    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    statusShow(tr("Wait..."));

        resetTabs();
        if (sSample!=0) {delete sSample; sSample=0;}
        sSample=new Sample;
        initTabs();

        if (pFrmFrame==0) return;
        this->tabWidget->insertTab(0,pFrmFrame, pFrmFrame->title());

    statusShow(tr("Project successfully initialized."));
    qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
}

void MainFrm::initTabs()
{
    pFrmFrame=new FrmFrame(sSample,tDateTime);

     connect(pFrmFrame, SIGNAL(isLogBook(bool)), this,
    SLOT(rearrangeTabs(bool)),Qt::UniqueConnection);

     connect(pFrmFrame, SIGNAL(submitted(int,bool)), this,
    SLOT(addTab(int,bool)),Qt::UniqueConnection);

    vTabs.push_back(pFrmFrame);

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
    pFrmOperation=new FrmOperation(sSample,tDateTime);
    initPreviewTab(pFrmOperation);
    pFrmCatch=new FrmCatch(sSample,tDateTime);
    initPreviewTab(pFrmCatch);

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

/////////////////////////////////////////////

SessionFileParser::SessionFileParser(Sample* sample)
{
    m_sample=sample;
    m_bReadingIsLogbook=false;
    m_bReadingFrameId=false;
    m_bReadingFrameTimeId=false;
    m_bReadingMinorStrataId=false;
    m_bReadingCellId=false;
    m_bReadingVesselTypeId=false;
    m_bReadingSampVesselId=false;
    m_bReadingTripId=false;
    m_bReadingOperationId=false;

    m_ct=0;
}

SessionFileParser::~SessionFileParser()
{
    //if (m_sample!=0) delete m_sample;
}

bool SessionFileParser::startElement( const QString& , const QString& , const QString &name, const QXmlAttributes &)
{
      if( name == QObject::tr("isLogbook") )
        m_bReadingIsLogbook=true;
      else if( name == QObject::tr("frameId") )
        m_bReadingFrameId=true;
      else if( name == QObject::tr("frameTimeId") )
        m_bReadingFrameTimeId=true;
      else if( name == QObject::tr("minorStrataId") )
        m_bReadingMinorStrataId=true;
      else if( name == QObject::tr("cellId") )
        m_bReadingCellId=true;
      else if( name == QObject::tr("vesselTypeId") )
        m_bReadingVesselTypeId=true;
      else if( name == QObject::tr("sampVesselId") )
        m_bReadingSampVesselId=true;
      else if( name == QObject::tr("tripId") )
        m_bReadingTripId=true;
      else if( name == QObject::tr("operationId") )
        m_bReadingOperationId=true;

    return true;
  }

bool SessionFileParser::characters ( const QString & ch )
{
    if (m_bReadingIsLogbook){
        m_sample->bLogBook=QVariant(ch).toBool();
        m_bReadingIsLogbook=false;
        m_ct++;
    }else if (m_bReadingFrameId){
        m_sample->frameId=QVariant(ch).toInt();
        m_bReadingFrameId=false;
        m_ct++;
    }else if (m_bReadingFrameTimeId){
        m_sample->frameTimeId=QVariant(ch).toInt();
        m_bReadingFrameTimeId=false;
        m_ct++;
    }else if (m_bReadingMinorStrataId){
        m_sample->minorStrataId=QVariant(ch).toInt();
        m_bReadingMinorStrataId=false;
    }else if (m_bReadingCellId){
        m_sample->cellId=QVariant(ch).toInt();
        m_bReadingCellId=false;
    }else if (m_bReadingVesselTypeId){
        m_sample->vesselTypeId=QVariant(ch).toInt();
        m_bReadingVesselTypeId=false;
    }else if (m_bReadingSampVesselId){
        m_sample->sampVesselId=QVariant(ch).toInt();
        m_bReadingSampVesselId=false;
    }else if (m_bReadingTripId){
        m_sample->tripId=QVariant(ch).toInt();
        m_bReadingTripId=false;
    }else if (m_bReadingOperationId){
        m_sample->operationId=QVariant(ch).toInt();
        m_bReadingOperationId=false;
    }

    //return m_bReadingFrameId==false || m_bReadingFrameTimeId==false;
    return true;
}

 bool SessionFileParser::fatalError (const QXmlParseException & exception)
 {
     qWarning() << QObject::tr("Fatal error on line") << exception.lineNumber()
                << QObject::tr(", column") << exception.columnNumber() << ":"
                << exception.message();

     return false;
 }

bool SessionFileParser::endDocument()
{
    return m_ct==3;
}