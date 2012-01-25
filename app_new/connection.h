#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "globaldefs.h"

/*!
    This file defines a helper function to open a *default* connection to the Database.
    New connections must have a name!
*/

static bool createConnection(const QString strHost, const QString strDatabase, const QString strUser,
                                            const QString strPass, const QString strDriver)
{
       QSqlDatabase db = QSqlDatabase::addDatabase( strDriver );
        db.setConnectOptions(QT_TR_NOOP("SQL_ATTR_LOGIN_TIMEOUT=1000,SQL_COPT_SS_MARS_ENABLED,SQL_MARS_ENABLED_YES,Mars_Connection=yes"));
        db.setHostName(strHost);
        QString strData="DRIVER={" + strDatabaseDriver + "};SERVER="+ strHost + ";DATABASE=" + strDatabase + ";UID=" + strUser + ";PWD=" + strPass +"; MARS_Connection=yes;";
        db.setDatabaseName(strData);
        db.setUserName(strUser);
        db.setPassword(strPass);
        //Open the Database
        if  (!db.open()){
            QString error;
            error = db.lastError().text();
            qDebug() <<  error ;
            return false;
        }
    return true;
}

#endif
