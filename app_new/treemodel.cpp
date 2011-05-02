/*
    treemodel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/
#include <QtGui>
#include "treeitem.h"
#include "treemodel.h"
#include "globaldefs.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << tr("Name") << tr("Description") << tr("Level") << tr("Comments")
        << tr("ID") << tr("Reasons") << tr("Origin") << tr("symbol");
    rootItem = new TreeItem(rootData);
    //setupModelData(rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role== Qt::DecorationRole){

        if (index.column()==0){//We are only rendering icons for the name property!

            QPixmap pix;
            if (!item->data(7).toString().isEmpty() && !item->data(7).toString().isNull())
                pix.load(item->data(7).toString());
            else
                pix.load(tr(":/app_new/medfisis.ico"));
                if (!pix.isNull()){
                    pix=pix.scaled(16,18);
                    return pix;
                }
        }


    }else if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());

}

QString TreeModel::getEnumString(Level l) const
{
        switch (l) {
        case 0:
            return tr("TreeModel::ROOT");
            break;
        case 1:
            return tr("TreeModel::GLS");
            break;
        case 2:
            return tr("TreeModel::LS");
            break;
        case 3:
            return tr("TreeModel::VS");
            break;
        default:
            return tr("TreeModel::ROOT");
            break;
        }
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    if (position < 0 || position > parentItem->childCount())
        return false;

    QList<QVariant> blankList;
    for (int column = 0; column < columnCount(); ++column)
        blankList << QVariant("");

    beginInsertRows(parent, position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        TreeItem *newItem = new TreeItem(blankList, parentItem);
        if (!parentItem->insertChild(position, newItem))
            break;
    }

    endInsertRows();
    return true;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    if (position < 0 || position > parentItem->childCount())
        return false;

    beginRemoveRows(parent, position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        if (!parentItem->removeChild(position))
            break;
    }

    endRemoveRows();
    return true;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

bool TreeModel::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (item->setData(index.column(), value))
        emit dataChanged(index, index);
    else
        return false;

    return true;
}

void TreeModel::setupModelData(TreeItem *parent)
{
    //DEPRECATED ////////////////////////////////////////

    QList<TreeItem*> lGls;
    QList<TreeItem*> lLs;
    QList<TreeItem*> lVs;

    //Fill GLS,LS,VS
    for (int i=0; i < 3; ++i)
    {
        QList<QVariant> columnData;
        columnData << "GLS" + QVariant(i).toString();
        columnData << "Group of Landing Sites!";

        parent->appendChild(new TreeItem(columnData, parent));
        lGls << parent->child(parent->childCount()-1);

        for (int j=0; j < 3; ++j){

            QList<QVariant> columnData;
            columnData << "LS" + QVariant(j).toString();
            columnData << "Abstract Landing Site!";

            lGls.last()->appendChild(new TreeItem(columnData, lGls.last()));
            lLs << lGls.last()->child(lGls.last()->childCount()-1);

            for (int k=0; k < 3; ++k){

                QList<QVariant> columnData;
                columnData << "Vessel" + QVariant(k).toString();
                columnData << "A Vessel!";

                lLs.last()->appendChild(new TreeItem(columnData, lLs.last()));
                lVs << lLs.last()->child(lLs.last()->childCount()-1);

            }
        }
    }
}