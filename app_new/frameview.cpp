#include <QtGui>
#include "frameview.h"
#include "treeitem.h"
#include "globaldefs.h"

FrameView::FrameView(QWidget *parent):
QTreeView(parent){

    this->setEditTriggers(QAbstractItemView::EditKeyPressed);
    //this->setEditTriggers(QAbstractItemView::AllEditTriggers);
    //this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    this->header()->setClickable(true);

    newAct=0;
    newVirtualAct=0;
    frmChangeReasons=0;
    itemDelegate=0;

    initActions();
    initUi();
}

FrameView::~FrameView()
{
    if (newAct!=0) delete newAct;
    if (newVirtualAct!=0) delete newVirtualAct;
    if (frmChangeReasons!=0) delete frmChangeReasons;
    if (itemDelegate!=0) delete itemDelegate;
}

void FrameView::initUi()
{
    itemDelegate=new TreeItemDelegate();
    this->setItemDelegateForColumn(5,itemDelegate);
}

int FrameView::showFrmChangeReasons(const QModelIndex & indexTo, const QString& strItems, 
                                    const QString& strParents, const TreeModel::Level level)
{
    if (frmChangeReasons==0)
        frmChangeReasons=new FrmChangeReasons(this);

    frmChangeReasons->setVesselReasons(level==TreeModel::LS);
    frmChangeReasons->textChanges->clear();

    QString txt=tr("You are trying to move [items] from [from] to [to]. Are you sure you want to accept this change?");
    txt.replace(tr("[items]"),strItems);
    txt.replace(tr("[from]"),strParents);

    QSortFilterProxyModel *pModel=static_cast<QSortFilterProxyModel*>(model());
    txt.replace(tr("[to]"),
        pModel->sourceModel()->data(indexTo,0).toString());

    frmChangeReasons->lbChangeCoordinates->setText(txt);

    frmChangeReasons->adjustSize();
    return frmChangeReasons->exec();
}

 void FrameView::initActions()
{
    newAct = new CustomAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new item"));

    connect(newAct, SIGNAL(triggered(const QModelIndex&)), this,
        SLOT(insertNewItem(const QModelIndex&)));

    newVirtualAct = new CustomAction(tr("&New Virtual Landing Site"), this);
    newVirtualAct->setShortcuts(QKeySequence::Forward);
    newVirtualAct->setStatusTip(tr("Create a new virtual landing site"));

    connect(newVirtualAct, SIGNAL(triggered(const QModelIndex&)), this,
        SLOT(insertNewItem(const QModelIndex&)));

 }

void FrameView::insertNewItem(const QModelIndex & parent)
{
    QSortFilterProxyModel *pModel=static_cast<QSortFilterProxyModel*>(model());
    if (pModel==0) return;

    pModel->sourceModel()->insertRow(0,parent);
    QModelIndex idx = pModel->sourceModel()->index(0, 2, parent);//level
    if (!idx.isValid()) return;
    TreeItem *pItem = static_cast<TreeItem*>
        (parent.internalPointer());

    int curLevel=pItem->data(2).toInt()+1;
    pModel->sourceModel()->setData(idx, static_cast<TreeModel::Level>(curLevel));

    idx = pModel->sourceModel()->index(0, 4, parent);//id (NEW)
    if (!idx.isValid()) return;
    pModel->sourceModel()->setData(idx, -1);

    idx = pModel->sourceModel()->index(0, 6, parent);//origin
    if (!idx.isValid()) return;
    pModel->sourceModel()->setData(idx, -1);

    QString strSymbol;
    getSymbolStr(static_cast<TreeModel::Level>(curLevel),false,strSymbol);
    idx = pModel->sourceModel()->index(0, 7, parent);//symbol
    if (!idx.isValid()) return;
    pModel->sourceModel()->setData(idx, strSymbol);

    expand(idx);
}

 void FrameView::contextMenuEvent(QContextMenuEvent *event)
 {
    QModelIndex index;
    getIndexFromPos(index, event->pos());

    if (index.isValid()){

        //We disallow insertion of new items on the bin!
        QSortFilterProxyModel *pModel=static_cast<QSortFilterProxyModel*>(model());
        if (!pModel) return;
        if (isOnTheBin(pModel,index)) return;

        TreeItem *item = static_cast<TreeItem*>
        (index.internalPointer());

        if (static_cast<TreeModel::Level>(item->data(2).toInt())==TreeModel::ROOT ||
            static_cast<TreeModel::Level>(item->data(2).toInt())==TreeModel::GLS ){

             QMenu menu(this);

            if (static_cast<TreeModel::Level>(item->data(2).toInt())==TreeModel::GLS)
            {
                if (newVirtualAct!=0){
                    newVirtualAct->setCurIdx(index);
                    menu.addAction(newVirtualAct);
                }
            }else{
                if (newAct!=0){//being extra carefull here!
                    newAct->setCurIdx(index);
                    menu.addAction(newAct);
                }
            }

             menu.exec(event->globalPos());

        }
    }
 }

void FrameView::expand ( const QModelIndex & index )
{
    QSortFilterProxyModel* pModel=static_cast<QSortFilterProxyModel*>(model());
    if (!pModel) return;

    QModelIndex newIdx=pModel->mapFromSource(index);
    return QTreeView::expand(newIdx);
}

void FrameView::getIndexFromPos(QModelIndex& idx, const QPoint &curPos)
{
   //! Helper function that calculates model Index From Mouse Position
    /*!
      \param QModelIndex out: index
      \param QPoint in: cursor position
    */

    QSortFilterProxyModel* pModel=static_cast<QSortFilterProxyModel*>(model());
    if (!pModel) return;

    QModelIndex index=pModel->mapToSource(indexAt(curPos));
    if (!index.isValid()){
        idx=QModelIndex();
        return;
    }

    idx=index;
}
void FrameView::dragEnterEvent ( QDragEnterEvent * event )
{
    emit DragStarted();
    QTreeView::dragEnterEvent(event);
}

void FrameView::dragMoveEvent(QDragMoveEvent * event )
{
    /*
    const TreeMimeData * mimeData=
            qobject_cast<const TreeMimeData *>(event->mimeData());

    if (mimeData==0) return;

    QModelIndex move_to = indexAt(event->pos());

            d->dropIndicatorRect = QRect();
            d->dropIndicatorPosition = OnViewport;
            if (d->isIndexDropEnabled(rootIndex()))
                event->accept(); // allow dropping in empty areas
/*
    foreach (QModelIndex index, mimeData->treeItemDefs()->itemIndexes) {
    {

    }
*/
    return QTreeView::dragMoveEvent(event);
}

QAbstractItemView::DropIndicatorPosition
FrameView::position(const QPoint &pos, const QRect &rect, const QModelIndex &index) const
{
    bool overwrite=true;
    QAbstractItemView::DropIndicatorPosition r = QAbstractItemView::OnViewport;
    if (!overwrite) {
        const int margin = 2;
        if (pos.y() - rect.top() < margin) {
            r = QAbstractItemView::AboveItem;
        } else if (rect.bottom() - pos.y() < margin) {
            r = QAbstractItemView::BelowItem;
        } else if (rect.contains(pos, true)) {
            r = QAbstractItemView::OnItem;
        }
    } else {
        QRect touchingRect = rect;
        touchingRect.adjust(-1, -1, 1, 1);
        if (touchingRect.contains(pos, false)) {
            r = QAbstractItemView::OnItem;
        }
    }

    if (r == QAbstractItemView::OnItem && (!(model()->flags(index) & Qt::ItemIsDropEnabled)))
        r = pos.y() < rect.center().y() ? QAbstractItemView::AboveItem : QAbstractItemView::BelowItem;

    return r;
}

bool FrameView::dropOn(QDropEvent *event, int *dropRow, int *dropCol, QModelIndex *dropIndex)
{
    QModelIndex index;
    QSortFilterProxyModel *pModel;

    if (viewport()->rect().contains(event->pos())) {

        pModel=static_cast<QSortFilterProxyModel*>(model());
        if (pModel==0) return false;
        index = pModel->mapToSource(indexAt(event->pos()));

        if (!index.isValid() || !visualRect(pModel->mapFromSource(index)).contains(event->pos()))
            index = this->rootIndex();
    }

    QAbstractItemView::DropIndicatorPosition dropIndicatorPosition;
    // If we are allowed to do the drop
    if (pModel->sourceModel()->supportedDropActions() & event->dropAction()) {
        int row = -1;
        int col = -1;
        if (index != this->rootIndex()) {
            dropIndicatorPosition = position(event->pos(),
                visualRect(pModel->mapFromSource(index)), pModel->mapFromSource(index));
            switch (dropIndicatorPosition) {
            case QAbstractItemView::AboveItem:
                row = index.row();
                col = index.column();
                index = index.parent();
                break;
            case QAbstractItemView::BelowItem:
                row = index.row() + 1;
                col = index.column();
                index = index.parent();
                break;
            case QAbstractItemView::OnItem:
            case QAbstractItemView::OnViewport:
                break;
            }
        } else {
            dropIndicatorPosition = QAbstractItemView::OnViewport;
        }
        *dropIndex = index;
        *dropRow = row;
        *dropCol = col;
        if (!droppingOnItself(event, index))
        return true;
    }
    return false;
}

bool FrameView::isOnTheBin(QSortFilterProxyModel* pModel, QModelIndex& index)
{
    bool bBin=false;
    QModelIndex pI=index;
    while (pI!=rootIndex())
    {
        QModelIndex pII=pModel->sourceModel()->index(pI.row(),0,pI.parent());
        if (pII.data().toString().compare(
            qApp->translate("bin", strBin), Qt::CaseInsensitive)==0){
                bBin=true;
                break;
        }
        else if (pII.data().toString().compare(
            qApp->translate("frame", strRoot), Qt::CaseInsensitive)==0){
                bBin=false;
                break;
        }
        pI=pI.parent();
    }
    return bBin;
}

void FrameView::dropEvent ( QDropEvent * event )
{
   //! Reimplementation of the QAbstractItemView::dropEvent in order to enable a selective dropping;
    /*!
      \param QDropEvent a drop event
      \sa dragEnterEvent ( QDragEnterEvent * event )
    */
    bool bOk=false;
    QModelIndex index;
    int col = -1;
    int row = -1;
    if (dropOn(event, &row, &col, &index)) {

        TreeItem *pItem = static_cast<TreeItem*>
            (index.internalPointer());

        if (pItem!=0){

            if (event->mimeData()->hasFormat(tr("application/tree"))!=0){

                const TreeMimeData * mimeData=
                        qobject_cast<const TreeMimeData *>(event->mimeData());

                if (mimeData!=0){

                    //Get the droplevel and parent name...
                    int dropLevel=pItem->data(2).toInt();
                    QString strParentName=pItem->data(0).toString();

                    QSortFilterProxyModel *pModel=static_cast<QSortFilterProxyModel*>(model());
                    if (pModel!=0){

                        //Find out if we need to gray out the symbols
                        bool bBin=isOnTheBin(pModel,index);

                        QList<ComplexItem>::const_iterator i;
                        for (i = mimeData->itemList()->begin(); i != mimeData->itemList()->end(); ++i){

                            foreach (QPersistentModelIndex pIdx, (*i).m_indexList) {

                                if (pIdx.column()==2){

                                    int dragLevel=pIdx.data().toInt();

                                    QModelIndex idName=pModel->sourceModel()->index(pIdx.row(),0,pIdx.parent());

                                    //check if its dropping on itself!
                                    TreeItem *curItem = static_cast<TreeItem*>
                                        (idName.internalPointer());
                                    if (curItem!=0){

                                        if ( (dropLevel==dragLevel-1 || strParentName
                                            .compare(qApp->translate("bin", strBin), Qt::CaseInsensitive)==0
                                            ) && curItem!=pItem ){

                                                QModelIndex idx=pModel->sourceModel()->index(pIdx.row(),6,pIdx.parent());
                                                if (idx.data()==-1){
                                                    pModel->sourceModel()->setData(idx,
                                                        idx.parent().internalId());
                                                }

                                                //Flag the symbols
                                                if (flagBin((*i),pIdx.parent(),bBin))

                                                bOk=true;

                                    }else bOk=false;
                                }else bOk=false;
                            }
                        }//foreach
                    }//for
                }else bOk=false;//pModel
            }else bOk=false;
         }else bOk=false;
        }else bOk=false;
    }else bOk=false;

    if (!bOk){
        event->setDropAction(Qt::IgnoreAction);
        event->accept();
        return;
    }

    return QTreeView::dropEvent(event);

}

bool FrameView::flagBin(const ComplexItem& cItem, const QModelIndex& parent, const bool bBin)
{
    QSortFilterProxyModel *pModel=static_cast<QSortFilterProxyModel*>(model());
    if (pModel==0)
        return false;

    foreach (QPersistentModelIndex index, cItem.m_indexList) {
        QModelIndex idx = pModel->sourceModel()->index(index.row(), index.column(), parent);
        if (idx.column()==7){

            QModelIndex binIdx=pModel->sourceModel()->index(idx.row(),7,idx.parent());
            if (!binIdx.isValid()) return false;

            QModelIndex lIdx=pModel->sourceModel()->index(idx.row(),2,idx.parent());
            if (!lIdx.isValid()) return false;

            TreeModel::Level lv=static_cast<TreeModel::Level>(pModel->sourceModel()->data(lIdx).toInt());

            QString strSymb;
            getSymbolStr(lv,bBin,strSymb);

            pModel->sourceModel()->setData(binIdx, strSymb);
        }
    }

    if (cItem.m_vChildren.size()>0)
    {
        QModelIndex pIndex=cItem.m_indexList.first();
        for (int i=0; i < cItem.m_vChildren.size(); ++i){
            flagBin(cItem.m_vChildren.at(i),pIndex,bBin);
        }
    }
    return true;
}

void FrameView::getSymbolStr(const TreeModel::Level l, const bool bBin, QString& strSymbol)
{
    switch (l) {
        case TreeModel::VS:
            bBin?strSymbol=tr(":/app_new/vesseld.png"):strSymbol=tr(":/app_new/vessel.png");
            break;
        case TreeModel::LS:
            bBin?strSymbol=tr(":/app_new/lsd.png"):strSymbol=tr(":/app_new/ls.png");
            break;
        case TreeModel::GLS:
            bBin?strSymbol=tr(":/app_new/glsd.png"):strSymbol=tr(":/app_new/gls.png");
            break;
        default:
            strSymbol=tr("medfisis.ico");
    }
}

bool FrameView::flagMoved(const ComplexItem& cItem, const QModelIndex& parent)
{
    QSortFilterProxyModel *pModel=static_cast<QSortFilterProxyModel*>(model());
    if (pModel==0)
        return false;

    foreach (QPersistentModelIndex index, cItem.m_indexList) {
        QModelIndex idx = pModel->sourceModel()->index(index.row(), index.column(), parent);
        if (idx.column()==6){

            QModelIndex pIdx=pModel->sourceModel()->index(parent.row(),0,parent.parent());
            if (!pIdx.isValid()) return false;
            pModel->sourceModel()->setData(idx, pIdx.internalId());
        }
    }

    if (cItem.m_vChildren.size()>0)
    {
        QModelIndex pIndex=cItem.m_indexList.first();
        for (int i=0; i < cItem.m_vChildren.size(); ++i){
            flagMoved(cItem.m_vChildren.at(i),pIndex);
        }
    }
    return true;
}

bool FrameView::insertReasons(const ComplexItem& cItem, const QModelIndex& parent, const QString strText)
{
    QSortFilterProxyModel *pModel=static_cast<QSortFilterProxyModel*>(model());
    if (pModel==0)
        return false;

    foreach (QPersistentModelIndex index, cItem.m_indexList) {
        QModelIndex idx = pModel->sourceModel()->index(index.row(), index.column(), parent);
        if (idx.column()==5){

            QModelIndex lIdx=pModel->sourceModel()->index(index.row(),2,parent);
            if (!lIdx.isValid()) return false;
                pModel->sourceModel()->setData(idx, strText);
        }
    }

    if (cItem.m_vChildren.size()>0)
    {
        QModelIndex pIndex=cItem.m_indexList.first();
        for (int i=0; i < cItem.m_vChildren.size(); ++i){
            insertReasons(cItem.m_vChildren.at(i),pIndex,qApp->translate("dragged", strDragged));
        }
    }
    return true;
}


bool FrameView::droppingOnItself(QDropEvent *event, const QModelIndex &index)
{
    Qt::DropAction dropAction = event->dropAction();
    if (dragDropMode() == QAbstractItemView::InternalMove)
        dropAction = Qt::MoveAction;
    if (event->possibleActions() & Qt::MoveAction
        && dropAction == Qt::MoveAction) {
            QModelIndexList selectedIndexes = this->selectedIndexes();
        QModelIndex child = index;
        while (child.isValid() && child != this->rootIndex()) {
            if (selectedIndexes.contains(child))
                return true;
            child = child.parent();
        }
    }
    return false;
}

bool FrameView::verifyChanges()
{
    selectAll();
    QModelIndexList mil = selectionModel()->selectedIndexes();

    QSortFilterProxyModel *pModel=static_cast<QSortFilterProxyModel*>(model());
    if (pModel==0)
        return false;

    foreach (QModelIndex index, mil)
    {
        QModelIndex mapIdx=pModel->mapToSource(index);
        if (mapIdx.isValid()){
            if (mapIdx.data()!=-1){//item moved

                    //Item did not effectively *moved*!
                    if (mapIdx.data()==mapIdx.parent().internalId()){

                    QModelIndex rIdx=pModel->sourceModel()->index(
                    mapIdx.row(),5,mapIdx.parent());

                    if (rIdx.isValid()){
                        if (!rIdx.data().toString().isEmpty())
                            pModel->sourceModel()->setData(rIdx,tr(""),Qt::DisplayRole);
                            pModel->sourceModel()->setData(rIdx,tr(""),Qt::EditRole);
                    }

                    }

            }else{//clear reasons for items that did not move!

                    QModelIndex rIdx=pModel->sourceModel()->index(
                    mapIdx.row(),5,mapIdx.parent());

                    if (rIdx.isValid()){
                        if (!rIdx.data().toString().isEmpty())
                            pModel->sourceModel()->setData(rIdx,tr(""));
                    }

            }
        }
    }
    selectionModel()->clear();

    return true;
}

//////////////////////////////////////
CustomAction::CustomAction( const QString & text, QObject * parent ): QAction(text,parent)
{
    connect(this, SIGNAL(triggered()), this,
        SLOT(emitCurIdx()));
}

CustomAction::~CustomAction()
{

}

void CustomAction::emitCurIdx()
{
    if (m_curIdx.isValid())
        emit triggered(m_curIdx);
}

///////////////////////////////////
ComboBoxItem::ComboBoxItem(QTreeWidgetItem *item, int column)
{
    this->item = item;
    this->column = column;
    connect(this, SIGNAL(currentIndexChanged(int)), SLOT(changeItem(int)));
}

void ComboBoxItem::changeItem(int index)
{
    if(index >=0)
    {
        item->setData(this->column, Qt::UserRole, this->itemText(index));
        qDebug() << item->data(this->column, Qt::UserRole).toString();
    }
}

//////////////////////////////////////

TreeItemDelegate::TreeItemDelegate(QObject *parent):
                        QStyledItemDelegate (parent)
{
    tChanges=0;
    init();
}

TreeItemDelegate::~TreeItemDelegate()
{
    if (tChanges!=0) delete tChanges;
}

void TreeItemDelegate::init()
{
    tChanges=new QSqlTableModel;
    tChanges->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Ref_Changes"),
        QSqlDriver::TableName));
    tChanges->select();
}

void TreeItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
 if(QComboBox *cb = qobject_cast<QComboBox *>(editor))
        // save the current text of the combo box as the current value of the item
        model->setData(index, cb->currentText(), Qt::EditRole);
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void TreeItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(QComboBox *cb = qobject_cast<QComboBox *>(editor)) {
        // get the index of the text in the combobox that matches the current value of the itenm
        QString currentText = index.data(Qt::EditRole).toString();
        int cbIndex = cb->findText(currentText);
        // if it is valid, adjust the combobox
        if(cbIndex >= 0)
            cb->setCurrentIndex(cbIndex);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

QWidget * TreeItemDelegate::createEditor
    ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    bool bShowCmb=false;

    // ComboBox ony in column 5
    if(index.column() ==5 ){

        const QSortFilterProxyModel *pModel=dynamic_cast<const QSortFilterProxyModel*>(index.model());
        if (pModel==0) return new QWidget;

        const DragDropModel *dModel=dynamic_cast<const DragDropModel*>(pModel->sourceModel());
        if (dModel==0) return new QWidget;

        QModelIndex idx=pModel->mapToSource(index);

        if (index==idx) return new QWidget;

        if (idx.isValid()){

                QModelIndex idx2=dModel->index(idx.row(),2,idx.parent());
                if (idx2.isValid()
                                   && static_cast<TreeModel::Level>(idx2.data().toInt())==TreeModel::VS)
                    bShowCmb=true;
        }

    }

    if (bShowCmb){
        // Create the combobox and populate it
        QComboBox* cmb = new QComboBox(parent);
        cmb->setModel(tChanges);
        cmb->setModelColumn(2);

        return cmb;
    }else{
        return QStyledItemDelegate::createEditor(parent, option, index);
    }

}