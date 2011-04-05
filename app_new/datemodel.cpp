#include "datemodel.h"

void DateModel::amendDateTimeType(bool bIsDateTime)
{
    QModelIndex idx=index(this->rowCount()-1,4);//Type
    if (!idx.isValid()) return;
    int typeID;
    if (!getDateTimeType(true,bIsDateTime,typeID)) return;
    this->setData(idx,typeID);
}

bool DateModel::getDateTimeType( const bool bDate, const bool bTime, int& typeID)
{
    QSqlQuery query;
    query.prepare(
    tr("SELECT        ID")+
    tr(" FROM         Ref_DateTime_Type")+
    tr(" WHERE Name=:name")
    );

    QString strType;
    if (bDate && bTime) strType=tr("DateTime");
    else if (bDate) strType=tr("Date");
    else if (bTime) strType=tr("Time");
    else strType=tr("n/a");

    query.bindValue(0, strType);
    if (!query.exec()) return false;
    if (query.numRowsAffected()!=1) return false;//It must *always* find an id

    query.first();
    typeID=query.value(0).toInt();
    return true;
}

bool DateModel::getLocationID(int& ID)
{
    QSqlQuery query;
    query.prepare(
    tr("SELECT     TOP (1) id_location")+
    tr(" FROM         dbo.GL_Session")+
    tr(" ORDER BY ID DESC")
    );

    if (!query.exec()) return false;
    if (query.numRowsAffected()!=1) return false;//It must *always* find an id

    query.first();
    ID=query.value(0).toInt();
    return true;
}

bool DateModel::insertNewRecord(const bool bAuto, const bool bDate, const bool bTime)
{
    if (!bDate && !bTime) return false;

    this->insertRow(this->rowCount());

    QModelIndex idx=index(this->rowCount()-1,1);//location: for now we always grab it from the session data
    if (!idx.isValid()) return false;
    int locationID;
    if (!getLocationID(locationID)) return false;
    this->setData(idx,locationID);

    idx=index(this->rowCount()-1,4);//Type
    if (!idx.isValid()) return false;
    int typeID;
    if (!getDateTimeType(bDate,bTime,typeID)) return false;
    this->setData(idx,typeID);

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
