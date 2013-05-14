#ifndef GENERICSORTPROXYMODEL_H
#define GENERICSORTPROXYMODEL_H
 
#include <QSortFilterProxyModel>
 
class GenericSortProxyModel : public QSortFilterProxyModel
{
public:
GenericSortProxyModel(QObject *parent=0);
void setparametros(QList<bool> booleanColumns);
protected:
virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
virtual QVariant data ( const QModelIndex & index, int role ) const;
virtual bool setData ( const QModelIndex & index, const QVariant & value, int role );
 
private:
QList<bool> booleanSet;
QVariant nullVariant;
 
};
 
#endif // GENERICSORTPROXYMODEL_H