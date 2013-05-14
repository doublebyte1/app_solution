#include "nullrelationaldelegate.h"

NullRelationalDelegate::NullRelationalDelegate(QList<int> colsOthers, QList<int> colsText, QObject *parent):
                        QSqlRelationalDelegate(parent),m_colsText(colsText), m_colsOthers(colsOthers)
{

}
void NullRelationalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (m_colsOthers.contains(index.column())){
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
