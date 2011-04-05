#include "datemodel.h"


bool DateModel::insertNewRecord(const bool bAuto)
{
    this->insertRow(this->rowCount());

    QModelIndex idx=index(this->rowCount()-1,1);//local
    if (!idx.isValid()) return false;
    this->setData(idx,4);//TODO: get the right value for this

    idx=index(this->rowCount()-1,4);//Type
    if (!idx.isValid()) return false;
    this->setData(idx,4);//TODO: get the right value for this

    if (bAuto){
        idx=index(this->rowCount()-1,3);//Local Date
        QDateTime now = QDateTime::currentDateTime();
        this->setData(idx,now);
        idx=index(this->rowCount()-1,2);//UTC Date
        now = QDateTime::currentDateTime();
        this->setData(idx,now.toUTC());
    }
    return true;
}

bool DateModel::submitAll()
{
    //TODO: handle this later!!!
    //Silently set the foreign_key id_activity_header to 8, to satisfy the constraint;

    //Fill the UTC "versions" of RecDate and LastMod Date
/*
    QModelIndex idx1=this->createIndex(m_curIdx,17);
    QModelIndex idx2=this->createIndex(m_curIdx,2);
    if (!FillUTCDate(idx2,idx1)) return false;

    idx1=this->createIndex(m_curIdx,18);
    idx2=this->createIndex(m_curIdx,15);
    if (!FillUTCDate(idx2,idx1)) return false;

    //Fill the locations for the two dates
    idx1=this->createIndex(m_curIdx,20);
    if (!FillLocation(idx1)) return false;
    idx1=this->createIndex(m_curIdx,19);
    if (!FillLocation(idx1)) return false;

    //Sets the Date fields to be *only* date!
    idx1=this->createIndex(m_curIdx,22);
    if (!SetIsDateTime(idx1,false)) return false;
    idx1=this->createIndex(m_curIdx,21);
    if (!SetIsDateTime(idx1,false)) return false;

    if (!QSqlRelationalTableModel::submitAll()){
        emit showError(this->lastError().text());
        return false;
    }
*/
    return true;
}