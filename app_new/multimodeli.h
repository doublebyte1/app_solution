#include <QtGui>
#include <QtSql>

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef MULTIMODELI_H
#define MULTIMODELI_H

//! Multiple Row Model Interface Class
/*!
This class ties together a mode and a listview with extended selection; the listview is associated with a source table, 
from which we read the values and an output table, where we introduce the multiple choices: one record for each choice;
We want to do this, to support multiple values to certain fields in the database.
*/

class MultiModelI
{
    //Q_OBJECT

    public:
        MultiModelI(QListView* listView, QSqlQueryModel* source, QSqlTableModel* output);
        ~MultiModelI();

        //! List to Model
        /*! This is the function that translates the multiple choices on the List, to multiple records on the model
        //createRecord + submit
        */
        bool                list2Model(const bool bNew=true);
        //! Model to List
        /*! This is the function that translates the multiple choices on the model, to the list widget
        \param strField field that will be used for the filter, as string
        //preview record
        */
        bool                model2List(const QString strField);
        //! Set Output Id
        /*! This sets the id that ties all the multiple records together on the output table; output
        table= outId+ choices id; we must fill this, each time we initialize a record on the main table;
        */
        void                setParentId(const int aId){m_parentId=aId;}

    private:
        void                init();
        bool                findId4Item(const int row, int& id);

        int                 m_parentId;/**< parent ID for  the multiple records on the output table */
        QListView*          m_listView;
        QSqlQueryModel*     m_source;/**< table to feed the widget */
        QSqlTableModel*     m_output;/**< table to write the choices */

};
#endif //MULTIMODELI_H