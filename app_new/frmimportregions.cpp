#include "frmimportregions.h"

#define LEVEL_INIT 1 //This is the level number we want to show in the UI
#define INT_LEVEL_INIT 2 //This is the real level we use in the DB (Root=1)

FrmImportRegions::FrmImportRegions(QWidget *parent, Qt::WFlags flags):
SecondaryFrm(parent, flags){

    setupUi(this);

    connect(pushClose, SIGNAL(clicked()), this,
    SIGNAL(hideFrm()));

    m_ctr=LEVEL_INIT;
}

FrmImportRegions::~FrmImportRegions()
{

}

void FrmImportRegions::adjustButtons()
{
    pushApply->setEnabled(true);
    pushCancel->setEnabled(true);
}

void FrmImportRegions::showEvent ( QShowEvent * event )
{
    Init();
    pushApply->setEnabled(false);
    pushCancel->setEnabled(false);
}

void FrmImportRegions::Apply()
{
    //Update bottomLevelTable
    if (m_mapTablesFields.size() < 1){
        emit showError(tr("You must choose some node tables, before attempting to generate a model!"));
        return;
    }

    HashNodeRef::const_iterator it=m_mapTablesFields.constEnd();
    it--;
    bottomLevelTable=it.value()->m_strTable;

    //First convert into a proper list model
    if (!convert2List(m_mapTablesFields)){
        emit showError(tr("Could not convert to List Model!"));
        return;
    }
    //Then convert to a hierarchical set model
    if (!list2Nested()){
        emit showError(tr("Could not convert to Nested Set Model!"));
        return;
    }

    pushApply->setEnabled(false);
    emit showStatus(tr("Model successfully converted and imported into the database!"));
}

void FrmImportRegions::Cancel()
{
    listWidget->clear();//reset list
    m_ctr=LEVEL_INIT;//reset counter
    m_mapTablesFields.clear();//reset map
    pushCancel->setEnabled(false);
    pushApply->setEnabled(false);
}

void FrmImportRegions::Init()
{
    QSqlDatabase db=QSqlDatabase::database();
    cmbTables->addItems(db.tables());
    cmbTables->setCurrentIndex(0);
    refreshFields(cmbTables->currentText());
}

void FrmImportRegions::addItems2List()
{
    //Validate Table Name and field Name: we need this because it's an edit box!
    //TODO: Maybe we can find a better solution later?

    QSqlDatabase db=QSqlDatabase::database();
    if (!db.tables().contains(cmbTables->currentText())){
        cmbFields->clear();
        emit showError(tr("This table does not exist in the database!"));
        cmbTables->setFocus();
        return;
    }
    else{
        bool bGotFields=false;
         QSqlQueryModel *model = new QSqlQueryModel;
         model->setQuery(tr("SELECT * FROM ") + cmbTables->currentText());

         for (size_t i=0; i < (size_t)model->columnCount();++i){
             if (model->record().fieldName(i)==cmbFields->currentText()){
                 bGotFields=true;
                 break;
             }
         }
         delete model;
         if (!bGotFields){
             emit showError(tr("This field does not exist in this table!"));
             return;
         }
    }

     //Validate table name and field ok: proceed...
    QString strItem;
    for (int i=0; i < m_ctr;++i)
        strItem.append(tr("    "));

    strItem.append(tr("Level ") + QVariant(m_ctr).toString() + tr("-> Node(") + cmbTables->currentText()
        +tr(") ;") + (m_ctr>1? tr(" Parent Field (") + cmbFields->currentText() + tr(");"): tr("" )));
     listWidget->addItem(strItem);

     m_mapTablesFields.insert(
                m_ctr-(LEVEL_INIT-INT_LEVEL_INIT),
                nodeRefPtr(new NodeRef(cmbTables->currentText(),cmbFields->currentText())));

    m_ctr++;
}

void FrmImportRegions::refreshFields(QString strTable)
{
    cmbFields->clear();

     QSqlQueryModel *model = new QSqlQueryModel;
     model->setQuery(tr("SELECT * FROM ") + strTable);

     for (int i=0; i < model->columnCount();++i)
         cmbFields->addItem(model->record().fieldName(i));

     delete model;
}
