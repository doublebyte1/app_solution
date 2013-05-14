#include "booleantable.h"

BooleanTable::BooleanTable(QWidget *parent):
QTableView(parent){

}

BooleanTable::~BooleanTable()
{
    /*!
    //Clean Pointers here!
    */

}

void BooleanTable::showOnlyLastRow()
{
    for (int i=0; i < this->model()->rowCount()-1;++i){
        this->hideRow(i);
    }
}

void BooleanTable::showAllRows()
{
    for (int i=0; i < this->model()->rowCount()-1;++i){
        this->showRow(i);
    }

}
