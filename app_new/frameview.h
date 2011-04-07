#include <QtGui>
#include <QTreeView>
#include "treemodel.h"
#include "frmchangereasons.h"
#include "dragdropmodel.h"

#if defined(WIN32) && defined(_DEBUG)
 #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
 #define new DEBUG_NEW
#endif

#ifndef CUSTOMACTION_H
#define CUSTOMACTION_H

//! Custom Action
/*!
This reimplementation of the QAction class
allows us to send custom signals, containing QModelIndexes as arguments;
*/

class CustomAction: public QAction
{
    Q_OBJECT

    public:
        CustomAction( const QString & text, QObject * parent );
        ~CustomAction();

    public slots:
        void setCurIdx(const QModelIndex& curIdx){m_curIdx=curIdx;}

    signals:
        void triggered(const QModelIndex& index);

    private slots:
        void emitCurIdx();

    private:
        QModelIndex     m_curIdx;
};

#endif //CUSTOMACTION_H
/////////////////////////////////////////////////////////////////

#ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H

class ComboBoxItem : public QComboBox
{
    Q_OBJECT

private:
    QTreeWidgetItem *item;
    int column;

public:
    ComboBoxItem(QTreeWidgetItem*, int);

public slots:
    void changeItem(int);

};
#endif //COMBOBOXITEM_H

//////////////////////////////////////////////////////////////////////

#ifndef TREEITEMDELEGATE_H
#define TREEITEMDELEGATE_H

//! Tree Item Delegate Class
/*!
This is a delegate that allows us to customize the way we see items in the QTreeView
*/

class TreeItemDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

        public:
            TreeItemDelegate (QObject *parent = 0);
            ~TreeItemDelegate();

        protected:
            QWidget         *createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
            void            setEditorData(QWidget *editor, const QModelIndex &index) const;
            void            setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

        private:
            QSqlTableModel* tChanges;
            void            init();

};

#endif //TREEITEM_DELEGATE_H

/////////////////////////////////////////////////////////////////
#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

//! View to Visualize the Frame
/*!
This class is a reimplementation of QTreeView, that allows selective
"drops", according to the inbuilt levels (GLS, LS, Vessels);
*/

class FrameView: public QTreeView
{
    Q_OBJECT

    public:
        FrameView(QWidget *parent = 0);
        ~FrameView();

        bool                        verifyChanges();

    public slots:
        //void                        sortByColumn(int column, Qt::SortOrder order);
        void                        expand ( const QModelIndex & index );

    protected:
        void                        contextMenuEvent(QContextMenuEvent *event);

    signals:
        void                        DragStarted();
        void                        PromptReason(const QModelIndex& idx,
                                        const TreeModel::Level level);

    private slots:
        int                        showFrmChangeReasons(const QModelIndex & indexTo,
            const QString& strItems, const QString& strParents, const TreeModel::Level level);
        void                       insertNewItem(const QModelIndex & parent);

    private:
        void                        dragEnterEvent ( QDragEnterEvent * event );
        void                        dragMoveEvent(QDragMoveEvent * event );
        void                        dropEvent ( QDropEvent * event );
        QAbstractItemView::DropIndicatorPosition
                                    position(const QPoint &pos, const QRect &rect, const QModelIndex &index) const;
        void                        getIndexFromPos(QModelIndex& idx, const QPoint &curPos);
        bool                        dropOn(QDropEvent *event, int *dropRow, int *dropCol, QModelIndex *dropIndex);
        bool                        droppingOnItself(QDropEvent *event, const QModelIndex &index);
        void                        initActions();
        bool                        flagMoved(const ComplexItem& cItem, const QModelIndex& parent);
        bool                        flagBin(const ComplexItem& cItem, const QModelIndex& parent, const bool bBin);
        bool                        insertReasons(const ComplexItem& cItem, const QModelIndex& parent, const QString strText);
        void                        initUi();
        bool                        isOnTheBin(QSortFilterProxyModel* pModel, QModelIndex& index);
        void                        getSymbolStr(const TreeModel::Level l, const bool bBin, QString& strSymbol);
        CustomAction                *newAct;
        CustomAction                *newVirtualAct;
        FrmChangeReasons*           frmChangeReasons;
        TreeItemDelegate            *itemDelegate;


};
#endif //FRAMEVIEW_H
