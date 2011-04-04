#include <QtGui>
#include "dragdropmodel.h"
#include "treeitem.h"

///////////////////////////////////////////////////////////////////////////
DragDropModel::DragDropModel(QObject *parent)
    : TreeModel(parent)
{
}
bool DragDropModel::insertComplexItem(const ComplexItem& cItem, const QModelIndex& parent)
{
    insertRows(0, 1, parent);
    foreach (QPersistentModelIndex index, cItem.m_indexList) {

        QModelIndex idx = this->index(0, index.column(), parent);
        setData(idx, index.data(0));

    }

    emit ExpandThis(parent);

    if (cItem.m_vChildren.size()>0)
    {
        QModelIndex pIndex=this->index(0,0,parent);
        for (int i=0; i < cItem.m_vChildren.size(); ++i)
            insertComplexItem(cItem.m_vChildren.at(i),pIndex);

        emit ExpandThis(pIndex);
    }

    return true;
}

bool DragDropModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qApp->setOverrideCursor( QCursor(Qt::BusyCursor ) );

    if (action == Qt::IgnoreAction){
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
        return true;
    }

    if (!data->hasFormat(tr("application/tree"))){
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
        return false;
    }

    const TreeMimeData * mimeData=
            qobject_cast<const TreeMimeData *>(data);

    if (mimeData==0){
        qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );
        return false;
    }

    QList<ComplexItem>::const_iterator i;
     for (i = mimeData->itemList()->begin(); i != mimeData->itemList()->end(); ++i){
         insertComplexItem(*i,parent);
     }

    qApp->setOverrideCursor( QCursor(Qt::ArrowCursor ) );

    return true;
}

Qt::ItemFlags DragDropModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = TreeModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::NoItemFlags | defaultFlags;
}

bool DragDropModel::buildComplexItem(const QPersistentModelIndexList &indexes, ComplexItem& cItem) const
{
    foreach (QPersistentModelIndex index, indexes) {

        if (index.column()==0){

            TreeItem *item = static_cast<TreeItem*>
                (index.internalPointer());

            if (item->childCount()>0){
                QVector<ComplexItem> vComplexChildItems;
                for (int i=0; i < item->childCount(); ++i){
                    QPersistentModelIndexList childIndexList;
                    ComplexItem childComplexItem;
                    for (int j=0; j < item->child(i)->columnCount(); ++j)
                    {
                        QPersistentModelIndex idx=this->index(item->child(i)->row(),j,index);
                        childIndexList << idx;
                    }
                    buildComplexItem(childIndexList,childComplexItem);
                    vComplexChildItems << childComplexItem;
                }
                cItem.m_vChildren=vComplexChildItems;
            }
            cItem.m_indexList=indexes;
        }

    }

    return true;
}

QMimeData *DragDropModel::mimeData(const QModelIndexList &indexes) const
{
    QPersistentModelIndexList items;
    ComplexItemList           itemList;

    //organize the indexes per item
    QMap<qint64,qint64> mapDistinct;
    QMultiMap<qint64,QPersistentModelIndex> oIndexes;
    foreach (QModelIndex index, indexes) {
        QPersistentModelIndex idx=index;
        oIndexes.insert(idx.internalId(),index);
        mapDistinct.insert(idx.internalId(),idx.internalId());
    }

    //Now build recursively the complex items!
    QMapIterator<qint64,qint64> itr(mapDistinct);
    while (itr.hasNext()) {
        itr.next();
        QPersistentModelIndexList indexList;
        QMultiMap<qint64,QPersistentModelIndex>::iterator itrr = oIndexes.find(itr.key());
        while (itrr != oIndexes.end() && itrr.key()==itr.key()) {
            indexList.push_front(itrr.value());//put indexes in the right order!
             ++itrr;
         }
        ComplexItem cItem=ComplexItem();
        buildComplexItem(indexList,cItem);
        itemList << cItem;
    }

    TreeMimeData *mimeData = new TreeMimeData(itemList);
    return mimeData;

}

QStringList DragDropModel::mimeTypes() const
{
    QStringList types;
    types << tr("application/tree");
    return types;
}

Qt::DropActions DragDropModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

/////////////////////////////////////

TreeMimeData::TreeMimeData(const ComplexItemList itemList):
                           m_itemList(itemList)
{
    myFormats << tr("application/tree");
}

QStringList TreeMimeData::formats() const
{
    return myFormats;
}

QVariant TreeMimeData::retrieveData(const QString &format,
                                     QVariant::Type preferredType) const
{
    return QMimeData::retrieveData(format, preferredType);
}

