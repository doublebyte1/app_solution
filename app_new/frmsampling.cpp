#include <QTest>
#include "frmsampling.h"
#include "previewtab.h"

FrmSampling::FrmSampling(Sample* inSample, QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags),m_sample(inSample){

    setupUi(this);
    m_submitted=false;
    tSampLevels=0;
    tRefSchema=0;
    tRefLevels=0;
    initModels();
    initUI();
}

FrmSampling::~FrmSampling()
{
    if (tSampLevels!=0) delete tSampLevels;
    if (tRefSchema!=0) delete tRefSchema;
    if (tRefLevels!=0) delete tRefLevels;
}

void FrmSampling::setTips(const bool bLogbook)
{
    lbSource->setToolTip(tr("This is a ") + (bLogbook? tr("logbook"): tr("sampling")) + tr(" frame"));
    lbSource->setStatusTip(tr("This is a ") + (bLogbook? tr("logbook"): tr("sampling")) + tr(" frame"));
    lbSource->setWhatsThis(tr("This is a ") + (bLogbook? tr("logbook"): tr("sampling")) + tr(" frame"));
}

void FrmSampling::showEvent ( QShowEvent * event )
{
    setSourceText(lbSource,m_sample->bLogBook);
    setTips(m_sample->bLogBook);

    tSampLevels->setFilter(tr("id_fr_time=")+QVariant(m_sample->frameTimeId).toString());

    //right now we force the logbook to multi-stage logbook and sampling to multi-stage sampling
    //HARDCODED for now: logbook=2; sampling=3
    cmbSchema->setCurrentIndex(m_sample->bLogBook?2:3);

    initRecords(cmbSchema->currentIndex());

    //cmbSchema->setEnabled(true);
    tableView->setEnabled(true);
    m_submitted=false;
    pushApply->setEnabled(!m_submitted);
}

void FrmSampling::initRecords(int index)
{
    if (!this->isVisible()) return;

    //first revert changes
    tSampLevels->revertAll();

    QModelIndex idx=cmbSchema->model()->index(index,0);
    tRefLevels->setFilter("id_schema="+idx.data().toString());

     for (int i=0; i < tRefLevels->rowCount(); ++i)
     {
         tSampLevels->insertRow(tSampLevels->rowCount());
         QModelIndex idx1=tSampLevels->index(tSampLevels->rowCount()-1,1);
         tSampLevels->setData(idx1,m_sample->frameTimeId);
         QModelIndex idx2=tSampLevels->index(tSampLevels->rowCount()-1,2);
         QModelIndex idLevel=tRefLevels->index(i,0);
         tSampLevels->setData(idx2,idLevel.data());
     }
}

void FrmSampling::back()
{
    emit hideFrmSampling(m_submitted);
}

void FrmSampling::apply()
{
    if (tSampLevels->submitAll()){
        m_submitted=true;
    }else{
        if (tSampLevels->lastError().type()!=QSqlError::NoError)
            emit showError(tSampLevels->lastError().text());
        else
            emit showError(tr("Failed to submit data: unknown error!"));
    }

    tableView->setEnabled(!m_submitted);
    //cmbSchema->setEnabled(!m_submitted);
    pushApply->setEnabled(!m_submitted);
}

void FrmSampling::initModels()
{
    if (tRefSchema!=0) delete tRefSchema;

    tRefSchema = new QSqlTableModel;
    tRefSchema->setTable(tr("Ref_Schema"));
    tRefSchema->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tRefSchema->sort(0,Qt::AscendingOrder);
    tRefSchema->select();

    if (tSampLevels!=0) delete tSampLevels;

    tSampLevels=new CustomModel();
    tSampLevels->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Levels"),
        QSqlDriver::TableName));
    tSampLevels->setRelation(2, QSqlRelation(tr("Ref_Levels"), tr("ID"), tr("Name")));
    tSampLevels->setRelation(4, QSqlRelation(tr("Ref_Criteria"), tr("ID"), tr("Name")));
    tSampLevels->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tSampLevels->sort(0,Qt::AscendingOrder);
    tSampLevels->select();

    tSampLevels->setHeaderData(2,Qt::Horizontal, tr("Level"));
    tSampLevels->setHeaderData(3,Qt::Horizontal, tr("Sample size"));
    tSampLevels->setHeaderData(4,Qt::Horizontal, tr("Criteria"));

    tRefLevels = new QSqlTableModel;
    tRefLevels->setTable(tr("Ref_Levels"));
    tRefLevels->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tRefLevels->sort(0,Qt::AscendingOrder);
    tRefLevels->select();
}

void FrmSampling::initUI()
{
    cmbSchema->setModel(tRefSchema);
    cmbSchema->setModelColumn(1);
    cmbSchema->setEnabled(false);

    initTable();
    tableView->resizeColumnsToContents();
}

void FrmSampling::initTable()
{
    tableView->setModel(tSampLevels);
    tableView->sortByColumn(0);
    tableView->hideColumn(0);
    tableView->hideColumn(1);

    tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));

     connect(tSampLevels, SIGNAL(dataChanged(const QModelIndex & ,const QModelIndex & )), tableView,
    SLOT(resizeColumnsToContents()));
}

//////////////////////////////////////////////////////////////
CustomModel::CustomModel(QObject * parent, QSqlDatabase db):
QSqlRelationalTableModel (parent,db){


}

CustomModel::~CustomModel()
{
}

Qt::ItemFlags CustomModel::flags ( const QModelIndex & index ) const
{
    if (index.column()==2){
        return Qt::ItemIsSelectable;
    }else{
        return QSqlRelationalTableModel::flags(index);
    }
}
/*
///////////////////////////////////////////////
Delegate::Delegate(QObject * parent):
QSqlRelationalDelegate (parent){


}

void Delegate::setEditorData(QWidget *editor,
                       const QModelIndex &index) const
{
  if (!editor->metaObject()->userProperty().isValid()) {
    if (editor->property("currentIndex").isValid()) {
      editor->setProperty("currentIndex", index.data());
      return;
    }
  }
  QItemDelegate::setEditorData(editor, index);
}

void Delegate::setModelData(QWidget *editor,
                     QAbstractItemModel *model,
                     const QModelIndex &index) const
{
  if (!editor->metaObject()->userProperty().isValid()) {
    QVariant value = editor->property("currentIndex");
    if (value.isValid()) {
      model->setData(index, value);
      return;
    }
  }
  QItemDelegate::setModelData(editor, model, index);
}
*/