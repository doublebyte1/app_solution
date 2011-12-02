#include <QTest>
#include "frmsampling.h"
#include "previewtab.h"

FrmSampling::FrmSampling(Sample* inSample, DateModel* inTDateTime, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
GenericTab(0, inSample,inTDateTime,tr("Sampling Technique"), ruleCheckerPtr, parent, flags){

    setupUi(this);
    m_submitted=false;
    tSampLevels=0;
    tRefSampTec=0;
    tRefLevels=0;
    mapper1=0;
    mapper2=0;
    nullDellegate=0;
    m_mode=FrmSampling::NONE;

    initModels();
    initUI();
}

FrmSampling::~FrmSampling()
{
    if (tSampLevels!=0) delete tSampLevels;
    if (tRefSampTec!=0) delete tRefSampTec;
    if (tRefLevels!=0) delete tRefLevels;
    if (nullDellegate!=0) delete nullDellegate;
    if (mapper1!=0) delete mapper1;
    if (mapper2!=0) delete mapper2;
}

void FrmSampling::setTips(const bool bLogbook)
{
    lbSource->setToolTip(tr("This is a ") + (bLogbook? qApp->translate("frame", strLogbook): qApp->translate("frame", strSampling)) + tr(" frame"));
    lbSource->setStatusTip(tr("This is a ") + (bLogbook? qApp->translate("frame", strLogbook): qApp->translate("frame", strSampling)) + tr(" frame"));
    lbSource->setWhatsThis(tr("This is a ") + (bLogbook? qApp->translate("frame", strLogbook): qApp->translate("frame", strSampling)) + tr(" frame"));
}

bool FrmSampling::createRecords ()
{
    //first revert changes
    tRefSampTec->revertAll();
    tSampLevels->revertAll();

    return (tRefSampTec->insertRow(tRefSampTec->rowCount()));
}

void FrmSampling::insertRow()
{
    if (!tSampLevels->insertRow(tSampLevels->rowCount()))
        emit showError(tr("Could not add a sampled level to the table!"));
    else 
        emit showStatus(tr("Sampled level successfully initialized!"));
}

void FrmSampling::removeRow()
{
    if (!tableView->selectionModel()->hasSelection()){
        emit showError (tr("If you want to remove a row, you must select it first!"));
    }else{
        int delRow=tableView->selectionModel()->currentIndex().row();
        if (!tSampLevels->removeRow(delRow))
            emit showError(tr("Could not remove a sampled level from this table!"));
        else
        emit showStatus(tr("Sampled level successfully removed!"));
    }
}

void FrmSampling::onShowForm()
{
    setSourceText(lbSource,m_sample->bLogBook);
    setTips(m_sample->bLogBook);

    if (m_mode==CREATE){

        if (!createRecords()){
            emit showError(tr("Could not initialize records for Sampling Technique!"));
            return;
        }else {
            mapper1->toLast();
            emit addRecord();
            emit showStatus(tr("Records successfully initialized for characterizing the sampling technique used for this frame!"));
        }

        for (int i=0; i < tSampLevels->rowCount(); ++i)
            tableView->hideRow(i);

    }if (m_mode==EDIT){

        bool bError=false;

        tRefSampTec->setFilter("id_fr_time=" + QVariant(m_sample->frameTimeId).toString());

        QModelIndex idx=tRefSampTec->index(0,0);
        if (idx.isValid()){

            tSampLevels->setFilter("id_sampling_technique=" + idx.data().toString());
            tSampLevels->select();

            mapper1->toLast();

        } else {
            emit showError(tr("Could not find a sampling technique for this frame!"));
        }
    }

    m_submitted=false;

    groupTechnique->setEnabled(!m_submitted);
    pushApply->setEnabled(!m_submitted);
    pushApply->setVisible(m_mode==CREATE);

}

void FrmSampling::showEvent ( QShowEvent * event )
{
    spinPopulation->blockSignals(true);
    spinSample->blockSignals(true);
    onShowForm();
    spinPopulation->blockSignals(false);
    spinSample->blockSignals(false);
}

void FrmSampling::back()
{
    emit hideFrmSampling(m_submitted);
}

void FrmSampling::initMappers()
{
    if (m_mapperBinderPtr!=0) {delete m_mapperBinderPtr; m_mapperBinderPtr=0;}
    if (mapper1!=0) delete mapper1;

    mapper1= new QDataWidgetMapper(this);
    mapper1->setModel(tRefSampTec);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lCmb;
    lCmb << 5 << 6 << 7;
    QList<int> lText;
    lText << 3 << 4;
    nullDellegate=new NullRelationalDelegate(lCmb,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbStrategy->setModel(tRefSampTec->relationModel(5));
    cmbStrategy->setModelColumn(
        tRefSampTec->relationModel(5)->fieldIndex(tr("Name")));

    mapper1->addMapping(lineName, 1);
    mapper1->addMapping(cmbStrategy, 5);
    mapper1->addMapping(textComments,3);
    mapper1->addMapping(textComments,4);
    mapper1->addMapping(spinPopulation,7);
    mapper1->addMapping(spinSample,6);

    QList<QDataWidgetMapper*> lMapper;
    lMapper << mapper1 ;
    m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, m_sample, lMapper, this->objectName());
    if (!initBinder(m_mapperBinderPtr))
        emit showError(tr("Could not init binder!"));

    //TODO: create delegate (and binder) for the table?
}

bool FrmSampling::comitSamplingTechnique()
{
    bool bError=false;

    int curIndex=mapper1->currentIndex();
    if (curIndex==-1) return true; //there are no changes on this form!! (CAREFULL WITH THIS TEST)

    if (!mapper1->submit()){
            if (tRefSampTec->lastError().type()!=QSqlError::NoError)
                emit showError(tRefSampTec->lastError().text());
            else
                emit showError(tr("Could not submit mapper!"));
            bError=true;
    }else{
            QModelIndex idx=tRefSampTec->index(tRefSampTec->rowCount()-1,8);
            if (!idx.isValid()) return false;
            if (!tRefSampTec->setData(idx,m_sample->frameTimeId)) return false;

            if (!tRefSampTec->submitAll()){
                if (tRefSampTec->lastError().type()!=QSqlError::NoError)
                    emit showError(tRefSampTec->lastError().text());
                else
                    emit showError(tr("Could not write Sampling Technique in the database!"));
                bError=true;
            }else
                emit showStatus(tr("Sampling Technique successfully written in the database!"));
    }

    mapper1->setCurrentIndex(curIndex);

    return !bError;
}

bool FrmSampling::comitSampledLevels()
{
    bool bError=false;
    int id;
    int ct=0;

    QModelIndex indexTechnique=tRefSampTec->index(tRefSampTec->rowCount()-1,0);
    if (!indexTechnique.isValid()) return false;
    id=indexTechnique.data().toInt();
    for (int i=0; i < tSampLevels->rowCount(); ++i)
    {
            QModelIndex indexId=tSampLevels->index(i,0);
            if (!indexId.isValid()) return false;
            if (tSampLevels->isDirty(indexId)){
                QModelIndex indexFr=tSampLevels->index(i,7);
                if (!indexFr.isValid()) return false;
                if (!tSampLevels->setData(indexFr,id)) return false;
                ++ct;
            }
    }
/*
    if (ct<1 && m_mode==CREATE){
        emit showError(tr("You must add some level(s) to this sampling strategy!"));
        return false;
    }
*/
    if (!tSampLevels->submitAll()){
        if (tSampLevels->lastError().type()!=QSqlError::NoError){
            emit showError(tSampLevels->lastError().text());
        }else
            emit showError(tr("Could not write Sampling levels in the database!"));
        bError=true;
    }else{
        emit showStatus(tr("Sampling Technique successfully written in the database!"));
        if (m_mode==CREATE)tSampLevels->setFilter("id_sampling_technique=" + QVariant(id).toString());
    }

    return !bError;
}

void FrmSampling::onApplyChanges2FrmSampling(const bool bApply)
{
    if (bApply)
            apply();
}

bool FrmSampling::reallyApply()
{
    //first comit tRefSampTec; then get the id and comit tSampLevels
    bool bError=(!comitSamplingTechnique() || !comitSampledLevels());

    m_submitted=!bError;
    groupTechnique->setEnabled(!m_submitted);
    pushApply->setEnabled(!m_submitted);

    if (!bError && m_mode!=CREATE) AppliedChanges2SamplingFrame();
    return !bError;
}

void FrmSampling::initModels()
{
    if (tRefSampTec!=0) delete tRefSampTec;

    tRefSampTec = new QSqlRelationalTableModel;
    tRefSampTec->setTable(tr("Ref_Sampling_Technique"));
    tRefSampTec->setRelation(5, QSqlRelation(tr("Ref_Strategy"), tr("ID"), tr("Name")));

    //filter n/a records
    filterTable(tRefSampTec->relationModel(5));

    tRefSampTec->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tRefSampTec->sort(0,Qt::AscendingOrder);
    tRefSampTec->select();

    if (tSampLevels!=0) delete tSampLevels;

    tSampLevels=new QSqlRelationalTableModel();
    tSampLevels->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Sampled_Levels"),
        QSqlDriver::TableName));
    tSampLevels->setRelation(1, QSqlRelation(tr("Ref_Levels"), tr("ID"), tr("Name")));
    tSampLevels->setRelation(4, QSqlRelation(tr("Ref_Strategy"), tr("ID"), tr("Name")));

    //filter n/a records
    filterTable(tSampLevels->relationModel(1));
    filterTable(tSampLevels->relationModel(4));

    tSampLevels->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tSampLevels->sort(0,Qt::AscendingOrder);
    tSampLevels->select();

    tSampLevels->setHeaderData(1,Qt::Horizontal, tr("Level"));
    tSampLevels->setHeaderData(2,Qt::Horizontal, tr("Sample size"));
    tSampLevels->setHeaderData(3,Qt::Horizontal, tr("Population size"));
    tSampLevels->setHeaderData(4,Qt::Horizontal, tr("Strategy"));
    tSampLevels->setHeaderData(5,Qt::Horizontal, tr("Description"));
    tSampLevels->setHeaderData(6,Qt::Horizontal, tr("Comments"));

    tRefLevels = new QSqlTableModel;
    tRefLevels->setTable("Ref_Levels");
    tRefLevels->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tRefLevels->sort(0,Qt::AscendingOrder);
    tRefLevels->select();
}

void FrmSampling::initUI()
{
    initTable();
    initMappers();
}

void FrmSampling::initTable()
{
    tableView->setModel(tSampLevels);
    tableView->sortByColumn(0, Qt::AscendingOrder);
    tableView->hideColumn(0);// identity
    tableView->hideColumn(7);//id sampling technique

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