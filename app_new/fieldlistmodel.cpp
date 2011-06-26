#include "fieldlistmodel.h"

 FieldListModel::FieldListModel(const FieldList inStrData, QObject *parent)
     : QAbstractTableModel(parent),m_strData(inStrData)
 {
     //Initialize field headers!
     m_headers << tr("Name");
     m_headers << tr("Type");
     m_headers << tr("Length");
 }

  void FieldListModel::setModelData(const FieldList inStrData)
 {
     m_strData=inStrData;
     reset();
 }

int FieldListModel::rowCount(const QModelIndex & ) const
 {
      return m_strData.size();
 }

 int FieldListModel::columnCount(const QModelIndex & ) const
 {
     if (m_strData.size()<1) return 0;
     return m_strData.at(0).count();
 }

  QVariant FieldListModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid() || role != Qt::DisplayRole)
         return QVariant();
     return m_strData.at(index.row()).at(index.column());
 }


QVariant FieldListModel::headerData(int section ,
                             Qt::Orientation orientation,
                             int role) const
{
    if (role==0 && orientation==Qt::Horizontal){
        return m_headers.at(section);
    }
    else return QVariant();
}
