#include <QtGui>

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

#ifndef BOOLEANTABLE_H
#define BOOLEANTABLE_H

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! BooleanTable Class
/*!
This class implements tableview that transposes the columns of the database to rows, and translates
a logical column in two (enable/disable).
*/

class BooleanTable : public QTableView
{
    Q_OBJECT

    public:
        BooleanTable(QWidget *parent = 0);
        ~BooleanTable();

    void                                showOnlyLastRow();
    void                                showAllRows();

    private:

};

#endif // BOOLEANTABLE_H
