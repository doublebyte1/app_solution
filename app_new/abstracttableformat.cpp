#include "abstracttableformat.h"
#include "tableadapter.h"

AbstractTableFormat::AbstractTableFormat(QObject * parent, QSqlDatabase db, 
               const QString inName, const QString inExtension, const QString inDescription):
QSqlTableModel(parent, db), AbstractFormat(inName, inExtension, inDescription){

}

AbstractTableFormat::~AbstractTableFormat()
{

}

/////////////////////////////////////////////

AbstractTableFormat* TableFactory::GetTable(AbstractTableFormat::Format format) {
    switch (format){
        case 0:
            return new TableAdapter();
        case 1:
            //TODO: Add script imp here!
        case 2:
        //TODO: add other formats here
        default:
            return NULL;//n.b. it should never come here!
    }
}
