#include "conf_app.h"
#include "connection.h"
#include <QMessageBox>

conf_app::conf_app(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    setupUi(this);
    m_bConnected=false;
    cityModel=0;
    countryModel=0;
    tableModel=0;

    initUI();
}

conf_app::~conf_app()
{
    if (QSqlDatabase::database().isOpen()){
        if (cityModel!=0) delete cityModel;
        if (countryModel!=0) delete countryModel;
        if (tableModel!=0) delete tableModel;
    }
}

void conf_app::apply()
{
    saveSettings(1);
    pushApply->setEnabled(false);
    emit statusShow(tr("Location Settings successfully saved!"));
}

void conf_app::enableApply()
{
    pushApply->setEnabled(true);
}

void conf_app::initModels()
{
    if (cityModel!=0){
        delete cityModel;
        cityModel=0;
    }if (countryModel!=0){
        delete countryModel;
        countryModel=0;
    }

     cityModel = new QSqlQueryModel;
     countryModel = new QSqlQueryModel;
}

void conf_app::initUI()
{
    toolbar=addToolBar(tr("Main Toolbar"));
    toolbar->addAction(this->actionExit);
    toolbar->setFloatable(true);
    toolbar->setMovable(true);

     connect(actionShow_startup_message, SIGNAL(triggered(bool)),this,
        SLOT(onShowStartupMsg(bool) ),Qt::UniqueConnection);

    if (QSqlDatabase::drivers().isEmpty())
    QMessageBox::information(this, tr("No database drivers found"),
                             tr("This app requires at least one Qt database driver. "
                                "Please check the documentation how to build the "
                                "Qt SQL plugins."));

    this->cmbDriver->addItems(QSqlDatabase::drivers());

    pushDisconnect->setEnabled(false);
    groupSettings->setEnabled(false);
    groupTables->setEnabled(false);

    pushInsert->setEnabled(false);
    pushRemove->setEnabled(true);

    connect(this, SIGNAL(connectionChanged()), this,
        SLOT(onConnectionChange()));

    connect(this, SIGNAL(statusShow(const QString)), this,
        SLOT(onStatusShow(const QString)));

    loadSettings(0);

}

void conf_app::filterModel(QString strCountry)
{
    cityModel->setQuery("SELECT     dbo.Ref_Countries.Name AS country_name, dbo.Ref_Location.City_Name"
    "                       FROM         dbo.Ref_Location INNER JOIN"
    "                      dbo.Ref_Countries ON dbo.Ref_Location.Country = dbo.Ref_Countries.ID"
    "                       WHERE (dbo.Ref_Countries.Name='" + strCountry + "')"
    );

    cmbCity->setModel(cityModel);
    cmbCity->setModelColumn(1);
}

void conf_app::showEvent ( QShowEvent * event )
{
    actionShow_startup_message->setChecked(queryShowStartupMsg());
}

void conf_app::onShowStartupMsgI(bool bNoShow)
{
    onShowStartupMsg(!bNoShow);
    this->actionShow_startup_message->setChecked(!bNoShow);
}

void conf_app::onShowStartupMsg(const bool bShow)
{
    QSettings settings("Medstat", "App");
    settings.setValue("showStartupMsg", QVariant(bShow).toString());
}

void conf_app::enableConnectionCtrls(const bool bEnable)
{
    lineHost->setEnabled(bEnable);
    lineDataSource->setEnabled(bEnable);
    lineUsername->setEnabled(bEnable);
    linePassword->setEnabled(bEnable);
    lineAlias->setEnabled(bEnable);
    cmbDriver->setEnabled(bEnable);
}

void conf_app::onConnectionChange()
{
    pushConnect->setEnabled(!m_bConnected);
    pushDisconnect->setEnabled(m_bConnected);
    groupSettings->setEnabled(m_bConnected);
    groupTables->setEnabled(m_bConnected);
    enableConnectionCtrls(!m_bConnected);

}

void conf_app::disconnectDB()
{
    if (cityModel!=0){
        delete cityModel;
        cityModel=0;
    }if (countryModel!=0){
        delete countryModel;
        countryModel=0;
    }

    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("qt_sql_default_connection");

    emit statusShow(tr("Connection removed!"));

    m_bConnected=false;

    emit connectionChanged();
}

void conf_app::connectDB()
{
    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );
    emit statusShow(tr("Establishing connection... wait!"));

    enableConnectionCtrls(false);

    m_bConnected=createConnection(lineHost->text(),lineDataSource->text(),
        lineUsername->text(),linePassword->text(),
        lineAlias->text(),cmbDriver->currentText());

    qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );

    if (m_bConnected){
        saveSettings(0);
        if (!fillLocations()){
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("Could not read locations from the database!"),QMessageBox::Ok,0);
            msgBox.exec();
        }
        if (!listTables()){
            QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),
                tr("Could not read table list from the database!"),QMessageBox::Ok,0);
            msgBox.exec();
        }
        loadSettings(1);
        emit statusShow(tr("Connection sucessfully created!"));
    }else{

        QString strError;
        if (QSqlDatabase::database().lastError().type()!=QSqlError::NoError)
            strError=QSqlDatabase::database().lastError().text();
        else
            strError=tr("Could not connect to the database!");

        QMessageBox msgBox(QMessageBox::Critical,tr("Connection Error"),strError,QMessageBox::Ok,0);
        msgBox.exec();

        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }

    emit connectionChanged();
    groupSettings->setEnabled(m_bConnected);
    groupTables->setEnabled(m_bConnected);
}

void conf_app::saveSettings(const int section)
{
    QSettings settings("Medstat", "App");

    if (section==0){

        settings.setValue("host", lineHost->text());
        settings.setValue("datasource", lineDataSource->text());
        settings.setValue("username", lineUsername->text());
        settings.setValue("password", linePassword->text());
        settings.setValue("alias", lineAlias->text());
        settings.setValue("driver", cmbDriver->currentText());

    } else if (section==1){

        settings.setValue("country", cmbCountry->currentText());
        settings.setValue("city", cmbCity->currentText());

    }
}

void conf_app::loadSettings(const int section)
{

    QSettings settings("Medstat", "App");

    if (section==0){

        //Settings for the DB credentials
        lineAlias->setText(settings.value("alias").toString());
        lineHost->setText(settings.value("host").toString());
        lineDataSource->setText(settings.value("datasource").toString());
        lineUsername->setText(settings.value("username").toString());
        linePassword->setText(settings.value("password").toString());
        cmbDriver->setCurrentIndex(
                cmbDriver->findText(
                    settings.value("driver").toString()));

    } else if (section==1){

        int found= cmbCountry->findData(settings.value("country").toString(),Qt::DisplayRole,Qt::MatchExactly);
        if (found !=-1){
            cmbCountry->setCurrentIndex(found);
        }
        found= cmbCity->findData(settings.value("city").toString(),Qt::DisplayRole,Qt::MatchExactly);
        if (found !=-1){
            cmbCity->setCurrentIndex(found);
        }

    }else{ //n.b.: it should never come here!
        QMessageBox msgBox(QMessageBox::Critical,tr("Settings Error"),
            tr("You are trying to read a non-existent settings group!"),QMessageBox::Ok,0);
        msgBox.exec();
    }
}

void conf_app::onStatusShow(const QString str)
{
    this->statusBar()->setStyleSheet(tr(
     "QStatusBar {"
     "    background: "
     "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                     " stop: 0 #FFFF00, stop: 0.4 #FFFF66,"
                                     " stop: 0.5 #FFFF99, stop: 1.0 #FFFFCC)"
     ";"
     "}"));

    this->statusBar()->showMessage(str);
}

bool conf_app::listTables()
{
    QSqlDatabase db=QSqlDatabase::database();
    cmbTables->addItems(db.tables());

    return(cmbTables->count()>0);
}

void conf_app::applyChanges2Table()
{
    bool bError=false;

    if (!tableModel->submitAll()){
        if (tableModel->lastError().type()!=QSqlError::NoError){

            QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
                tableModel->lastError().text(),QMessageBox::Ok,0);
            msgBox.exec();

        }else{

            QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
                tr("Could not write Sampling levels in the database!"),QMessageBox::Ok,0);
            msgBox.exec();

        }
        bError=true;
    }else{
        emit statusShow(tr("Changes successfully written in the database!"));
    }

    pushApply_2->setEnabled(bError);
    pushInsert->setEnabled(bError);
    pushRemove->setEnabled(bError);
    tableView->setEnabled(bError);
}

void conf_app::showTable(const QString strTable)
{
    if (tableModel==0){
        tableModel= new QSqlRelationalTableModel;
    }

    bool bDirty=false;

    for (int i=0; i < tableModel->rowCount(); ++i){
        for (int j=0; j < tableModel->columnCount(); ++j){
            QModelIndex index=tableModel->index(i,j);
            if (tableModel->isDirty(index)){
                bDirty=true;
                break;
            }
        }
        if (bDirty) break;
    }

    if (bDirty){

        QMessageBox msgBox;
        msgBox.setText(tr("You have uncomitted changes!")
        );
        msgBox.setInformativeText(tr("Are you sure you want to abandon the edition of this table?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

         switch (ret) {
           //case QMessageBox::Yes:
            case QMessageBox::No:
                return;
                break;
            default:
                break;
         }
    }

    tableModel->setTable(QSqlDatabase().driver()->escapeIdentifier(strTable,
    QSqlDriver::TableName));
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->sort(0,Qt::AscendingOrder);
    tableModel->select();

    tableView->setModel(tableModel);

    QSqlRecord rec=tableModel->record();
    for (int i=0; i < rec.count(); ++i){
        if (rec.field(i).isGenerated()){
            tableView->hideColumn(i);
            break;
        }
    }

    pushInsert->setEnabled(true);
    pushRemove->setEnabled(true);
    pushApply_2->setEnabled(true);
    tableView->setEnabled(true);

}

void conf_app::insertRow()
{
    if (!tableModel->insertRow(tableModel->rowCount())){

        QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
            tr("Could not add a row to this table!"),QMessageBox::Ok,0);
        msgBox.exec();

    }else 
        emit statusShow(tr("Record successfully initialized!"));
}

void conf_app::removeRow()
{
    if (!tableView->selectionModel()->hasSelection()){

        QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
            tr("If you want to remove a row, you must select it first!"),QMessageBox::Ok,0);
        msgBox.exec();

    }else{
        int delRow=tableView->selectionModel()->currentIndex().row();
        if (!tableModel->removeRow(delRow)){

            QMessageBox msgBox(QMessageBox::Critical,tr("Table Edition Error"),
                tr("Could not remove a row from this table!"),QMessageBox::Ok,0);
            msgBox.exec();

        }else
            emit statusShow(tr("Row successfully removed!"));
    }
}

bool conf_app::fillLocations()
{
    initModels();

    countryModel->setQuery(
        "SELECT ID, Name from Ref_Countries WHERE"
        "   ID IN (SELECT Country from Ref_Location)"
        );

    cmbCountry->setModel(countryModel);
    cmbCountry->setModelColumn(1);

    return (countryModel->rowCount()>0);
}

//////////////////////////////////////////////////////////////////////

bool queryShowStartupMsg()
{
    QSettings settings("Medstat", "App");
    if (!settings.contains("showStartupMsg"))
        return true;

    return settings.value("showStartupMsg").toBool();
}
