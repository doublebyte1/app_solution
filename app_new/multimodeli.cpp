#include "previewtab.h"
#include "multimodeli.h"

MultiModelI::MultiModelI(QListView* listView, QSqlQueryModel* source, QSqlTableModel* output):
m_listView(listView),m_source(source), m_output(output){

    m_parentId=-1;
    init();
}

MultiModelI::~MultiModelI()
{

}

void MultiModelI::init()
{
    //The source model always has two columns (id - 0 -  and name - 1)
    m_listView->setModel(m_source);
    m_listView->setModelColumn(1);
}

bool MultiModelI::list2Model(QString& strError, const bool bNew)
{
    if (!bNew){
        if (!m_output->removeRows(0,m_output->rowCount())) return false;
    }

    if (m_parentId==-1) return false;
    //1 - for each selected index: see the id and create a new record on the main table with it
    QModelIndexList mil = m_listView->selectionModel()->selectedIndexes();
    int prevRow=-1;
    foreach (QModelIndex index, mil)
    {
        if (index.row()!=prevRow){
            int itemId;
            if (!findId4Item(index.row(),itemId)) return false;
            insertRecordIntoModel(m_output);

            while(m_output->canFetchMore())
                m_output->fetchMore();

            QModelIndex idx=m_output->index(m_output->rowCount()-1,1);
            m_output->setData(idx,m_parentId);
            idx=m_output->index(m_output->rowCount()-1,2);
            m_output->setData(idx,itemId);
            if (!m_output->submitAll()){
                if (m_output->lastError().type()!=QSqlError::NoError){
                        strError=m_output->lastError().text();
                }else strError=QObject::tr("Error submiting records to multimodel!");
                return false;
            }
            prevRow=index.row();
        }
    }

    return true;
}

bool MultiModelI::findId4Item(const int row, int& id)
{
    id=m_source->record(row).value(0).toInt();
    return true;
}

bool MultiModelI::model2List(const QString strField)
{
    if (m_parentId==-1) return false;
    m_output->setFilter(strField +QObject::tr("=") + QVariant(m_parentId).toString());

    m_listView->clearSelection();
    for (int i=0; i <m_output->rowCount(); ++i){
        QModelIndex idx1=m_output->index(i,2);//value item on output table

        int j=-1;
        //TODO: improve way of finding the id without looping through the records!!!
        for (j=0; j < m_source->rowCount(); ++j){
            if (m_source->index(j,0).data().toInt()==idx1.data()) break;
        }
        if (j==-1) return false;
        QModelIndex idx2=m_source->index(j,0);//index on source table

        if (!idx2.isValid()) return false;
        m_listView->selectionModel()->select(idx2,QItemSelectionModel::Rows | QItemSelectionModel::Select);
        m_listView->scrollTo(m_listView->selectionModel()->selectedIndexes().last());
    }

    return true;
}