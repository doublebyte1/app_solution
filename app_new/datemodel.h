#ifndef DATEMODEL_H
#define DATEMODEL_H

#include <QtSql>

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! Date Model Class
/*!
//TODO: add a description here later
*/

class DateModel: public QSqlTableModel
{
    Q_OBJECT

    public:
        bool            insertNewRecord(const bool bAuto);
        bool            submitAll();
        void            setAuto(const bool bAuto){m_bAuto=bAuto;}

    private:
        bool            m_bAuto;

};

#endif // DATEMODEL_H
