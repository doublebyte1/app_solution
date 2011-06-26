#ifndef FIELDLISTMODEL_H
#define FIELDLISTMODEL_H

#include <QtGui>
#include <QtSql>
#include "abstracttableformat.h"

#if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

typedef QVector<QStringList>                   FieldList;//!< typedef for storing the list of fields, and their characteristics (2D)

//! FieldListModel
/*!
This class provides a model, to fill the TableWidget with a field description of the table
*/
 class FieldListModel : public QAbstractTableModel
 {
     Q_OBJECT

 public:
     FieldListModel(const FieldList inStrData, QObject *parent = 0);
     ~FieldListModel(){}

     void                                       setModelData(const FieldList inStrData);

     int                                        rowCount(const QModelIndex &parent = QModelIndex()) const;
     int                                        columnCount(const QModelIndex &parent = QModelIndex()) const;

     QVariant                                   data(const QModelIndex &index, int role = Qt::DisplayRole) const;
     QVariant                                   headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

 private:
     FieldList                                  m_strData;
     QStringList                                m_headers;
 };
 #endif // FIELDLISTMODEL
