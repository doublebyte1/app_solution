#include "previewtab.h"

PreviewTab::PreviewTab(const int index, Sample* inSample, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
GenericTab(index,inSample,inTDateTime,parent, flags){

    m_model=0;
    m_table=0;
}

PreviewTab::~PreviewTab()
{
    //if (m_model!=0) delete m_model;//N.b.: dont delete model here: it does not belong to this class!
}

void PreviewTab::resizeEvent ( QResizeEvent * event )
{
    (void) event;
    if (m_table==0) return;
    resizeToVisibleColumns(m_table);
}

void PreviewTab::onShowForm()
{
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

    onShowUi();

}

void PreviewTab::genericCreateRecord()
{
    //removing filters
    if (m_model==0) return ;
    if (!m_model->filter().isEmpty()) m_model->setFilter(tr(""));

    if (m_tDateTime==0) return ;
    if (!m_tDateTime->filter().isEmpty()) m_tDateTime->setFilter(tr(""));

    while(m_model->canFetchMore())
        m_model->fetchMore();

    //Check for uncomitted changes
    QModelIndex idx=m_model->index(m_model->rowCount()-1,0);
    if (!idx.isValid()) return;

    if (m_model->isDirty(idx))
        m_model->revertAll();

    m_model->insertRow(m_model->rowCount());
}
