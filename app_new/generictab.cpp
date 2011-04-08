#include <QTest>
#include "generictab.h"

GenericTab::GenericTab(const int index, DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags),m_index(index), m_tDateTime(inTDateTime){

    connect(this, SIGNAL(lockControls(bool,QList<QWidget*>&)), this,
    SLOT(onLockControls(bool,QList<QWidget*>&)));
}

GenericTab::~GenericTab()
{
}

bool GenericTab::getDtId(const int mapIdx, int& id)
{
    QModelIndex idx= m_tDateTime->index(mapIdx,0);
    if (!idx.isValid()) return false;
    id=m_tDateTime->data(idx).toInt();
    return true;
}

void GenericTab::goBack()
{
    emit navigate(false,m_index);
}

void GenericTab::goForward()
{
    emit navigate(true,m_index);
}

void GenericTab::onLockControls(bool bLock,QList<QWidget*>& lWidgets)
{
    for (int i=0; i < lWidgets.size();++i)
        lWidgets.at(i)->setDisabled(bLock);
}

///////////////////////////////////////////////

NullRelationalDelegate::NullRelationalDelegate(QList<int> colsOthers, QList<int> colsText, QObject *parent):
                        QSqlRelationalDelegate(parent),m_colsText(colsText),m_colsOthers(colsOthers)
{

}
void NullRelationalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (m_colsOthers.contains(index.column())){//others
        QSqlRelationalDelegate::setModelData(editor,model,index);
    }else{

        if (m_colsText.contains(index.column())){//textEdits
            model->setData(index, editor->property("plainText") == tr("") ?
                QVariant() :
            editor->property("plainText"));
        }else {
            model->setData(index, editor->property("text") == tr("") ?
            QVariant() :
            editor->property("text"));
        }
    }
}

void NullRelationalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (m_colsOthers.contains(index.column())){//others
        QSqlRelationalDelegate::setEditorData(editor,index);
    }else{
        if (m_colsText.contains(index.column())){//text edits
            editor->setProperty("plainText", index.data());
        }else {
            editor->setProperty("text", index.data());
        }
    }
}
