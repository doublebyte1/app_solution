#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#if defined(WIN32) && defined(_DEBUG)
 #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
 #define new DEBUG_NEW
#endif

class TreeItem;

//! Tree Model Class
/*!
This class implements the concept of a tree model, that can be pluged into a tree widget.
A tree model is a set of tree items;
*/

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    //! An enum for the levels of nodes in the tree
    /*! Supported levels are: root, gls, ls ,v
    */
    enum Level { ROOT, /*!< Enum value for Root. */
                GLS, /*!< Enum value for Group of Landing Sites. */
                LS, /*!< Enum value for Landing Sites. */
                VS /*!< Enum value for Vessels. */
                };

    TreeModel(QObject *parent = 0);
    ~TreeModel();

    TreeItem* root() const { return rootItem; }

    /*! Verify changes on the tree
    ... This function loops through all elements, finds out the ones that change
        and removes reasons for the ones that did not change effectively;
        It returns a list of *effectively* changed items, so that we can do 
        something with them! (for instance highlight them!)
    */
    QModelIndexList     verifyChanges();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

    void sort(int column, Qt::SortOrder order);

    QList<QPersistentModelIndex> pIndexes;

private:
    void setupModelData(TreeItem *parent);
    QString getEnumString(Level l) const;
    bool recursiveVerifyChanges(TreeItem* item, QModelIndexList& list);

    TreeItem *rootItem;
};
#endif