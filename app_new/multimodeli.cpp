#include "previewtab.h"
#include "multimodeli.h"

MultiModelI::MultiModelI(QListView* listView, QSqlQueryModel* source, QSqlTableModel* output, QString strSql):
m_listView(listView),m_source(source), m_output(output), m_strSql(strSql){

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

bool MultiModelI::checkDependants(const int fid, bool& hasDependants)
{
    QSqlQuery query;
    query.prepare( m_strSql );
    query.bindValue(0,fid);
    if (!query.exec() || query.numRowsAffected()!=1) return false;
    query.first();
    hasDependants=query.value(0).toInt()>0;
    return true;
}

bool MultiModelI::list2Model(QString& strError, const bool bNew)
{
    //1 - for each selected index: see the id and create a new record on the main table with it
    QModelIndexList mil = m_listView->selectionModel()->selectedIndexes();

    if (!bNew){
        bool bRemove=false;
        foreach (QModelIndex index, m_selectedIndexes)
        {
            if (!mil.contains(index)){
                bRemove=true;
                break;
            }
        }

        if (bRemove){

            if (m_output->rowCount()< 1) return false;// oops! somthing went wrong here! :->
            int fid=m_output->index(0,1).data().toInt();
            bool bHasDependants;
            if (!checkDependants(fid,bHasDependants)) return false;
            if (!bHasDependants){
                if (!m_output->removeRows(0,m_output->rowCount())) return false;
            }else{
                strError=QObject::tr("Could not update ") + m_output->tableName()
                    + QObject::tr(" since there are dependant records!");
                return false;
            }
        }
    }

    if (m_parentId==-1) return false;

    int prevRow=-1;
    foreach (QModelIndex index, mil)
    {
        if (index.row()!=prevRow){
            int itemId;
            if (!findId4Item(index.row(),itemId)) return false;

            if (!insertRecordIntoModel(m_output)){
                strError=QObject::tr("Could not introduce a record in the model!");
                return false;
            }

            QModelIndex idx=m_output->index(m_output->rowCount()-1,1);
            if (!idx.isValid()) return false;
            if (!m_output->setData(idx,m_parentId,Qt::EditRole)) return false;

            idx=m_output->index(m_output->rowCount()-1,2);
            if (!idx.isValid()) return false;
            if (!m_output->setData(idx,itemId,Qt::EditRole)) return false;

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
    m_selectedIndexes.clear();

    for (int i=0; i <m_output->rowCount(); ++i){
        QModelIndex idx1=m_output->index(i,2);//value item on output table

        QModelIndexList list=m_source->match(m_source->index(0, 0),
            Qt::DisplayRole,
            idx1.data(),
            2, // look *
            Qt::MatchRecursive); // look *

        if (list.isEmpty()) return false;
        QModelIndex idx2=list.at(0);//m_source->index(j,0);//index on source table

        if (!idx2.isValid()) return false;
        m_listView->selectionModel()->select(idx2,QItemSelectionModel::Rows | QItemSelectionModel::Select);
        m_listView->scrollTo(m_listView->selectionModel()->selectedIndexes().last());

        m_selectedIndexes.push_back(idx2);
    }

    m_output->setFilter(QString());

    return true;
}