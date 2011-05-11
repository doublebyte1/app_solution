#include "previewtab.h"

PreviewTab::PreviewTab(const int index, Sample* inSample, DateModel* inTDateTime, const QString inStrTitle, QWidget *parent, Qt::WFlags flags):
GenericTab(index,inSample,inTDateTime,inStrTitle,parent,flags){

    m_model=0;
    m_table=0;
}

PreviewTab::~PreviewTab()
{
    //if (m_model!=0) delete m_model;//N.b.: dont delete model here: it does not belong to this class!
}

bool PreviewTab::afterApply()
{
    setPreviewQuery();
    m_table->selectRow(0);
    m_model->select();

    while(m_model->canFetchMore())
        m_model->fetchMore();

    QModelIndex cIdx=m_model->index(m_model->rowCount()-1,0);
    if (!cIdx.isValid()) return false;

    //selects the last index
    m_table->selectionModel()->setCurrentIndex(cIdx,QItemSelectionModel::Select | QItemSelectionModel::Rows);

    return true;
}

void PreviewTab::resizeEvent ( QResizeEvent * event )
{
    (void) event;
    if (m_table==0) return;
    resizeToVisibleColumns(m_table);
}

void PreviewTab::onShowForm()
{
    beforeShow();

    //Make sure all models are up to date, and without filters
    if (m_model==0) return;
    m_model->select();
    m_tDateTime->select();
    setPreviewQuery();

    if (m_model==0) return ;
    if (!m_model->filter().isEmpty()) m_model->setFilter(tr(""));

    if (m_tDateTime==0) return ;
    if (!m_tDateTime->filter().isEmpty()) m_tDateTime->setFilter(tr(""));

    //filter the relational model
    filterModel4Combo();

    if (m_selectedIdx.isValid())
        m_table->selectRow(m_selectedIdx.row());
}

bool PreviewTab::next()
{
    //retrieve selected index
    if (!m_selectedIdx.isValid()){
        emit showError(tr("You must select one Cell!"));
        return false;
    }

    if (!updateSample()) return false;
    QString strLabel;
    if (!getNextLabel(strLabel)) return false;

    emit forward(lbHead->text()+ tr("-> ") + strLabel);
    return true;
}

void PreviewTab::genericCreateRecord()
{
    //removing filters
    if (m_model==0) return ;
    if (!m_model->filter().isEmpty()) m_model->setFilter(tr(""));

    if (m_tDateTime==0) return ;
    if (!m_tDateTime->filter().isEmpty()) m_tDateTime->setFilter(tr(""));
/*
    while(m_model->canFetchMore())
        m_model->fetchMore();

    //Check for uncomitted changes
    QModelIndex idx=m_model->index(m_model->rowCount()-1,0);
    if (!idx.isValid()) return;

    if (m_model->isDirty(idx))
        m_model->revertAll();

    m_model->insertRow(m_model->rowCount());
*/
    insertRecordIntoModel(m_model);
}

void PreviewTab::insertRecordIntoModel(QSqlTableModel* m)
{
    while(m->canFetchMore())
        m->fetchMore();

    //Check for uncomitted changes
    QModelIndex idx=m->index(m->rowCount()-1,0);
    if (idx.isValid() && m->isDirty(idx))
        m->revertAll();

    m->insertRow(m->rowCount());
}
