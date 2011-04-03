#ifndef TREEMIMEDATA_H
#define TREEMIMEDATA_H

#include <boost/shared_ptr.hpp>
#include <QMimeData>
#include <QtGui>
#include "treemodel.h"

#if defined(WIN32) && defined(_DEBUG)
 #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
 #define new DEBUG_NEW
#endif

using namespace boost;

typedef QList<QPersistentModelIndex> QPersistentModelIndexList;

struct ComplexItem{

    ComplexItem(){}

    ComplexItem(const QPersistentModelIndexList indexList, const QVector<ComplexItem> vChildren):
m_indexList(indexList), m_vChildren(vChildren){}

    ComplexItem(const QPersistentModelIndexList indexList):
m_indexList(indexList){}

    QPersistentModelIndexList           m_indexList;
    QVector<ComplexItem>                m_vChildren;
};

typedef QList<ComplexItem>                              ComplexItemList;

////////////////////////////////////////////////////////////////
class TreeMimeData : public QMimeData
{
    Q_OBJECT
public:
    TreeMimeData(const ComplexItemList itemList);

    const ComplexItemList* itemList() const { return &m_itemList; }

    QStringList formats() const;

protected:
    QVariant retrieveData(const QString &format,
    QVariant::Type preferredType) const;

private:
    const ComplexItemList       m_itemList;
    QStringList                 myFormats;
};

#endif //TREEMIMEDATA_H
/////////////////////////////////////////////

#ifndef DRAGDROPMODEL_H
#define DRAGDROPMODEL_H

class DragDropModel : public TreeModel
{
    Q_OBJECT

public:
    DragDropModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;

signals:
    void            ExpandThis(const QModelIndex& idx);

private:
    bool            insertChildren(const QModelIndex &parent,
                                   const QMultiMap<int,QHash<int,QString> >& children);
    bool            buildComplexItem(const QPersistentModelIndexList &indexes, ComplexItem& item) const;
    bool            insertComplexItem(const ComplexItem& cItem, const QModelIndex& parent);

};

#endif //DRAGDROPMODEL_H





