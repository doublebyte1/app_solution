#include "genericsortproxymodel.h"
 
GenericSortProxyModel::GenericSortProxyModel(QObject *parent)
:QSortFilterProxyModel(parent)
{
 
}
void GenericSortProxyModel::setparametros(QList<bool> booleanColumns)
{
if(!booleanColumns.empty())
foreach(bool column , booleanColumns)
{
this->booleanSet.append(column);
}
 
}
 
Qt::ItemFlags GenericSortProxyModel::flags ( const QModelIndex & index ) const
{
 
if(!index.isValid())
return Qt::ItemIsEnabled;
if(booleanSet.value(index.column()))
return Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
else
return QSortFilterProxyModel::flags(index);
}
 
QVariant GenericSortProxyModel::data ( const QModelIndex & index, int role = Qt::DisplayRole ) const
{
if(!index.isValid())
return this->nullVariant;
if(booleanSet.value(index.column()) && (role==Qt::CheckStateRole || role==Qt::DisplayRole)) {
if(role==Qt::CheckStateRole)
return index.data(Qt::EditRole).toBool()?QVariant(Qt::Checked):QVariant(Qt::Unchecked);
else if(role==Qt::DisplayRole)
return this->nullVariant;
}
else
return QSortFilterProxyModel::data(index,role);
 
}
bool GenericSortProxyModel::setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole )
{
if(!index.isValid())
return false;
if(booleanSet.value(index.column()) && role==Qt::CheckStateRole)
{
QVariant data= value.toInt()==Qt::Checked?QVariant(true):QVariant(false);
return QSortFilterProxyModel::setData(index,data,Qt::EditRole);
}
else
return QSortFilterProxyModel::setData(index,value,role);
}
