#include "frmexport.h"
#include "xmltable.h"

FrmExport::FrmExport(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags){

    setupUi(this);

    connect(pushClose, SIGNAL(clicked()), this,
    SIGNAL(hideFrm()));

    listWidget->setAlternatingRowColors(true);
    listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //UI initializes
    groupOptions->setVisible(true);
    checkVerify->setVisible(false);//It does not make sense to verify this on export!
    checkCreate->setVisible(false);
    checkAppend->setVisible(false);
    checkBackups->setVisible(false);
    toolButton->setVisible(false);
    lbFile->setVisible(false);
    radioDefinition->click();
    previewTable->setAlternatingRowColors(true);
    previewTable->setVisible(false);
    previewTable->setSelectionMode(QAbstractItemView::NoSelection);
    tableModel=0;
    fieldModel=0;

    for (size_t i=0; i < (size_t)groupType->layout()->count(); ++i){
        //cast
        if ( qobject_cast<QRadioButton*>(groupType->layout()->itemAt(i)->widget())!=0 )
            connect(qobject_cast<QRadioButton*>(groupType->layout()->itemAt(i)->widget()), SIGNAL(clicked()), this,
            SLOT(preview()));
    }

    if (!readTableNames()) emit showError(tr("Could not read table names from database!"));
    else emit showStatus(tr("Finished reading table names from database"));

    if (!initFactory()) emit showError(tr("Could not initialize import/export formats!"));
    else emit showStatus(tr("Finished initializing import/export formats"));
}

bool FrmExport::initFactory()
{
     //! Init Table Factory
    /*!
    Uses factory to initialize a container, with all the supported import/export table formats
    */
    TableFactory* tableF = new TableFactory();
    m_listFormats.push_back(formatPtr(tableF->GetTable(AbstractTableFormat::TA)));
    //TODO: add other formats here...!

    //connect signal
    if (static_cast<AbstractTableFormat*>(m_listFormats.last().get())!=0)
    {
        connect(static_cast<AbstractTableFormat*>(m_listFormats.last().get()),
            SIGNAL(showStatus(QString)),
            this, SIGNAL(showStatus(QString)));

        connect(static_cast<AbstractTableFormat*>(m_listFormats.last().get()),
            SIGNAL(showError(QString,bool)),
            this, SIGNAL(showError(QString,bool)));
    }

    delete tableF;

    return m_listFormats.size()>0;
}

FrmExport::~FrmExport()
{
    if (tableModel!=0) delete tableModel;
    if (fieldModel!=0) delete fieldModel;
}

bool FrmExport::readTableNames()
{
    QSqlDatabase db = QSqlDatabase::database();

    listWidget->clear();
    listWidget->addItems(db.tables());
    if (checkShowViews->isChecked()){
        listWidget->addItems(db.tables(QSql::Views));
    }
    /*//n.b.: this code DOES NOT work! (Qts fault!)
    if (checkShowInternal->isChecked()){
        listWidget->addItems(db.tables(QSql::SystemTables));
    }*/

    return true;
}

void FrmExport::Ok()
{
    if (this->listWidget->selectedItems().count() < 1){
        emit showError(tr("No Items selected! You must select at least one table to import/export"));
        return;
    }

    //Retrieve the supported formats
    QString strFilter;

    if (!AbstractFormat::buildFormatFilter(strFilter,m_listFormats)){
        emit showError(tr("No formats for exporting were found!"),true);
        return;
    }

    // Retrieve last visited directory from the system
    QSettings settings(tr("Medstat"), tr("App"));

    QString strDir;
    if (settings.contains(tr("LastDirectory")))
        strDir=settings.value(tr("LastDirectory")).toString();
    else
        strDir=QDir::currentPath();

    QString fileName
         =QFileDialog::getSaveFileName(0,
         tr("Export Table(s)"), strDir, strFilter);

    if (!fileName.isEmpty() && !fileName.isNull()){

        QFileInfo fi(fileName);

        // Store last visited directory
        settings.setValue(tr("LastDirectory"), fi.absolutePath());

        AbstractFormat* aFormat=AbstractFormat::findFormat(fi.completeSuffix(),
            m_listFormats);
        if (!aFormat){
            emit showError(tr("Unsupported Export Format!"), true);
            return;
        }

        aFormat->setFileName(fileName);

        if (static_cast<AbstractTableFormat*>(aFormat)==0)
        {
            emit showError(tr("Could not retrieve this file format!"),true);
            return;
        }

        QStringList strTables;
        for (size_t i=0; i < (size_t)listWidget->selectedItems().count();++i){
            strTables << listWidget->selectedItems().at(i)->text();
        }
        (static_cast<AbstractTableFormat*>(aFormat))->setTables(strTables);
        (static_cast<AbstractTableFormat*>(aFormat))->setValidation(checkValidate->isChecked());

        QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
        if (!aFormat->exportNow()){
            emit showError(tr("Could no Export to the Chosen Format!"), true);
            QApplication::restoreOverrideCursor();//Don't forget to restore the cursor b4 exiting...
            return;
        }
        QApplication::restoreOverrideCursor();

    }
}

void FrmExport::Cancel()
{

}

void FrmExport::preview()
{
    //! Preview Table
    /*!
    Override function provided for convenience; it grabs the current item and previews it.
    */
    if (listWidget->selectedItems().size()==1)
        preview(listWidget->currentItem());
}

void FrmExport::preview(QListWidgetItem* item)
{
    previewTable->setVisible(true);

    if (tableModel!=0){
        delete tableModel;
        tableModel=0;
    }

    tableModel=new QSqlTableModel
        (this,QSqlDatabase::database());

    tableModel->setTable(item->text());
    tableModel->select();

    if (tableModel->lastError().type() != QSqlError::NoError){
        emit showError(tableModel->lastError().text());
        return;
    }

    if (radioDefinition->isChecked())//preview definition
    {
        if (!loadFields()) emit showError(tr("Could not read fields from database!"));
        else emit showStatus(tr("Previewing fields from Database: Ok"));
    }
    else{//preview data
        if (!loadTable()) emit showError(tr("Could not read data from database!"));
        else emit showStatus(tr("Previewing table from Database: Ok"));
    }
}

bool FrmExport::loadTable()
{
    previewTable->setModel(tableModel);
    previewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    return true;
}

bool FrmExport::loadFields()
{
    FieldList fieldRows;
    for (size_t i=0; i < (size_t)tableModel->record().count();++i)
    {
        QStringList fieldColumns;

        //Initialize one field description as a row
        QSqlField aField=tableModel->record().field(i);
        fieldColumns.append(tableModel->record().fieldName(i));
        fieldColumns.append(QVariant::typeToName(tableModel->record().field(tableModel->record().fieldName(i))
            .type()));
        fieldColumns.append(QVariant(aField.length()).toString());

        fieldRows.push_back(fieldColumns);
    }

    fieldModel=new FieldListModel(fieldRows,this);
    previewTable->setModel(fieldModel);
    previewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    return true;
}
