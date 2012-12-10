#ifndef SQL_H
#define SQL_H

//#include <QSqlDatabase>
//#include <QSqlError>
//#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QtSql>
#include <QtGui>
#include <QtNetwork/QNetworkInterface>
#include <boost/shared_ptr.hpp>
#include "globaldefs.h"
#include "json.h"

using namespace boost;
using namespace QtJson;

#define MSQL_MAX 2147483647
#define MAX_SIZE 4000
/*!
    This file defines helper functions and constants for sql queries and XML
*/
static const char *COLLATE = "COLLATE SQL_Latin1_General_CP1_CI_AS";
     //TODO: GET THIS FROM THE DB OR THE UI?

static const char *DEFAULTSCHEMA = "dbo";

static const char *URI = "http://tempuri.org/";

static const char *SCHEMA = "http://www.w3.org/2001/XMLSchema";

static const char *TMPCHAR = "_";

static QString bottomLevelTable="Ref_Minor_Strata";//This is the default table for the bottom level, but we can change it within the regions UI

static const QString strNoValue="274b68192b056e268f128ff63bfcd4a4";

//static const QString strSomeDate="SomeDate";

static const QString strDateFormat="yyyy-MM-ddThh:mm:ss";
//static const QString strDBDateFormat="ddd d yyyy hh:mmAP";

static const QString strMasterTable="MASTER";
static const QString strMasterName="master";
static const QString strClientName="client";

//! Table Sequence struct
/*! This structure allows us to construct a one direction table flow for a sampling process. 
Each element (table) provides us with the necessary information for navigation: the name of the parent field, the name of
the next table and if it contains or not dates (for Date Validation purposes)
*/
struct sTable {
    sTable( const QString refField, const QString next, const bool bHasDates):
    m_refField(refField), m_next(next), m_bHasDates(bHasDates)
    {}
    sTable()
    {}
   QString             m_refField;//!< name of the field that stores a reference to the parent
   QString             m_next;//!< name of the table that is next on the sequence
   bool                m_bHasDates;//!< boolean to flag if we have dates
};

//! FK struct
/*! This structure represents a Foreign Key, with parent, child and respective keys
*/
struct FK {
    //! Constructor.
        /*!
          This is the constructor for a foreign key, that initializes all the member variables.
          \param parent parent table name
          \param child child table name
          \param parent key field on the parent
          \param child key field on the child
          \sa cell()
        */
    FK(const QString parent, const QString child, const QString parentkey, const QString childkey):
    m_parent(parent), m_child(child), m_parentkey(parentkey), m_childkey(childkey)
    {}
    //! Constructor.
        /*!
          Overriden empty constructor 
          \sa FK(const QString parent, const QString child, const QString parentkey const QString childkey)
        */
    FK()
    {}
   QString             m_parent;//!< parent table name
   QString             m_child;//!< child table name
   QString             m_parentkey;//!< parent key field
   QString             m_childkey;//!< child key field
};
//////////////////////////////////////////////////////////////////////////////
typedef QMultiMap<QString,FK>                   MapFK;//!< typedef for mapping foreign keys (with a name)

//! NodeRef struct
/*! This structure references a node (table, field) from an imported adjacency model,
that we want to convert to a nested set;
*/
struct NodeRef {
    //! Constructor.
        /*!
          This is the constructor for a NodeRef, that initializes all the member variables.
          \param table table name
          \param field field name
        */
    NodeRef(const QString table, const QString field):m_strTable(table),
        m_strField(field)
    {}
   QString             m_strTable;//!< table name
   QString             m_strField;//!< field name
};

typedef shared_ptr<NodeRef>                     nodeRefPtr;//!< typedef for a smart pointer containing a Node Reference Structure
typedef QHash<int,nodeRefPtr>                   HashNodeRef;//!< typedef for mapping Node References (key=level,value=NodeRef(table,field)

static bool getImportedName(const QString inName, QString& outName, bool& bExists)
{
    //! Get Imported Table Name
    /*!
    This function allows a rename of imported tables on the database, as long as they are
    in a certain list
    \param inName original table name, as string
    \param outName out: imported table name, as string
    \param bExists out: boolean to write if it found the table or not, in the list of imported tables
    \return boolean as success or failure
    */

    //if (inName.isEmpty()) return false;

    QSqlQuery query;
    QString strQuery="SELECT original_name, imported_name FROM Info_Tables_Import WHERE original_name=:table";
    if (!query.prepare(strQuery))
        return false;
    query.bindValue(":table",inName);
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << query.lastError().text() << endl;
        return false;
    }
    query.first();
    if (query.numRowsAffected()>0)
        outName=query.record().value("imported_name").toString();
    else
        outName=inName;

    bExists=query.numRowsAffected()>0;
    query.finish();
    return true;
}

static bool escapeSqlString(QString& inStr)
{
    //! Escape SQL string
    /*!
    This function escapes all necessary sql "non-friendly characters"!
    We are being very "economical" here, so we pass an input string address and
    change it within this function =:->.
    \param inStr in and out: address of a string containing the information that we want to correct
    \return boolean as success or failure
    */

    int found=inStr.indexOf("'");
    if (found!=-1)
        inStr.replace("'","''");
    return true;
}

static bool castBoolean(const QString inBool, QString& outBool)
{
    //! Cast Boolean to Bit
    /*!
    Sql Server does not have a boolean type, so we have to cast true and false
    to bit (0 or 1)
    \param inBool input boolean, as string
    \param outBool output boolean, as string
    \return boolean as success or failure
    */

    if (inBool.compare("true",Qt::CaseInsensitive)==0 ||
        inBool.compare("1")==0)
        outBool="1";
    else if (inBool.compare("false",Qt::CaseInsensitive)==0 ||
        inBool.compare("0")==0)
        outBool="0";
    else return false;

    return true;
}

static bool castDate(QString inDate, QString& outDate)
{
    //! Truncate datetimeoffset
    /*!
    This function truncates a Dateoffset string, and it transforms it into
    a datetime conform string; if the string is not a datetimeoffset, it does nothing with it!
    \param inDate in: original date string
    \param outDate out: address of a string to put the amended date
    \return boolean as success or failure
    */

    int found=inDate.indexOf("+");
    if (found!=-1) inDate.remove(found,inDate.length()-found);

    QString strQuery="SELECT CAST('" + inDate + "' AS datetime)";
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()!=1) return false;
    query.first();
    outDate=query.value(0).toString();
    return true;
}

static bool getTypeInfo(const QString strTableName, const QString strFieldName, QSqlRecord& rec)
{
    QSqlQuery query;
    QString strQuery(QString("SELECT data_type 'datatype', numeric_precision, numeric_scale FROM information_schema.columns WHERE") +
        QString(" (table_name =:table AND column_name=:column)"));
    if (!query.prepare(strQuery)) return false;
    query.bindValue(":table",strTableName);
    query.bindValue(":column",strFieldName);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();

    rec=query.record();
    return true;
}

static bool getFieldPrecision(const QString strTableName, const QString strFieldName, QString& strPrecision, QString& strScale)
{
    QSqlRecord rec;
    if (!getTypeInfo(strTableName,strFieldName,rec)) return false;
    strPrecision=rec.value(rec.indexOf("numeric_precision")).toString();
    strScale=rec.value(rec.indexOf("numeric_scale")).toString();
    return true;
}

static bool getFieldType(const QString strTableName, const QString strFieldName, QString& strType)
{
    //! Get Field Type
    /*!
    This function executes a query to retrieve the sql type of a field
    \param strTableName binded parameter table name
    \param strFieldName binded parameter field name
    \param strType address of a string, to put the result (type)
    \return boolean as success or failure
    */

    QSqlRecord rec;
    if (!getTypeInfo(strTableName,strFieldName,rec)) return false;
    strType=rec.value(rec.indexOf("datatype")).toString();
    return true;
}

static bool dropConstraint(const QString strConstraint, const QString strTable)
{
    //! Drop Constraint
    /*!
    This function provides the removal of a named constraint, given a certain table
    name and constraint identifier (as string);
    \param strConstraint constraint name
    \param strTable table name
    \return boolean as success or failure
    */

    QSqlQuery query;
    QString strQuery(QString(
        "ALTER TABLE ") + strTable + QString(" DROP CONSTRAINT ") + strConstraint);
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    return query.exec();
}

static bool nullifyField(const QString strTable, const QString strField, const QString strType, bool bNullify=false)
{
    //! Set Field to Null (or not)
    /*!
    This function alters a table, to set a field to NULL (or not null);
    its mainly use for primary keys, as we cannot have primary keys on fields that allow nulls...
    \param strTable table name as string
    \param strField field name as string
    \param strType field data type (to put on the query)
    \param bNullify if set to false (default), it will make the field nullable; otherwise, it will make it non nullable!
    \return boolean as success or failure
    */

    QSqlQuery query;
    QString strQuery=QString("ALTER TABLE ") + strTable + QString(" ALTER COLUMN ") + strField +
        QString(" ") + strType +
        (!bNullify? " NOT": QString("")) + QString(" NULL");
    query.prepare(strQuery);
    query.setForwardOnly(true);
    return query.exec();
}

static bool fixStringMaximumLength(const QString strIn, QString &strOut, const bool bRead, const bool bRestrict=true)
{
    //! Fix the maximum length of a string
    /*!
    Sql server does not allow strings to exceed a 8000 maximum size.
    In case we must exceed this value we have to use "MAX"identifier: but do we really want to?
    \param strIn input maximum size (as string)
    \param strOut amended maximum size (as string)
    \param bRestrict if set to true, it will restrict the maximum size to a define value; otherwise, it will use MAX
    \param bRead if it is reading an XML it uses the SQL MAX identifier to insert it in the database; if it is writing, it writes SQL max size as we are using an int schema type
    \return boolean as success or failure
    */

    bool bOk;
    int num=QVariant(strIn).toInt(&bOk);
    if (!bOk) return false;
    if (num>=MAX_SIZE)
    {
        if (bRestrict) strOut=QVariant(MAX_SIZE).toString();
        else
            strOut=!bRead?QVariant(MSQL_MAX).toString(): "MAX";
    }
    else strOut=strIn;
    return true;
}

static bool dropTableIfExists(const QString strTableName)
{
    //! Drop Table if Exists
    /*!
    This function drops a table, in case it exists
    \param strTable table name
    \return bool as success or failure of the two operations
    */

    QString strQuery=
        QString("IF EXISTS(SELECT name FROM sys.tables WHERE name LIKE '")
        + strTableName + QString("') BEGIN DROP TABLE ") + strTableName + 
        QString(" END");

    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    return query.exec();
}

static bool getObjectID4Table(int& outId, const QString strField, const QString strTable)
{
    QString strQuery=
QString("SELECT obj.[name], col.[name], col.[colstat], col.* FROM [syscolumns] col JOIN [sysobjects] obj") +
QString(" ON obj.[id] = col.[id] WHERE obj.type = 'U' AND col.[status] = 0x80") +
QString(" AND (obj.[name]=:table AND col.[name]=:field) ORDER BY obj.[name] ")
;
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.bindValue(":table", strTable);
    query.bindValue(":field", strField);
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    query.first();
    outId=query.value(4).toInt();
    return true;
}

static bool getObjects(QSqlQuery& query, const QString strTable=QString())
{
    //! Get Object Ids
    /*!
    This function queries system table sys.columns
    and grabs tablenames, column names and object ids (so that we can use it later on queries);
    \param query address if a query object
    \param strTable optional parameter, if we want to use this query to verify the existence of a certain table
    \return bool as success or failure of the two operations
    */

    QString strQuery;
    if (strTable.isEmpty()){
        strQuery=
        "SELECT OBJECT_NAME(object_id) AS TableName, object_id, name, is_identity FROM sys.columns";
    }
    else
        strQuery=QString(
        "SELECT OBJECT_NAME(object_id) AS TableName, object_id, name, is_identity FROM sys.columns")
        +QString(" WHERE     (OBJECT_NAME(object_id) = '") + strTable + QString("')");

    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    query.finish();
    return (strTable.isEmpty()?query.numRowsAffected()>0:true);
}

static bool getAutoIncrementInfo(const int objectID, QSqlQuery& query)
{
    //! Get Seed and Increment Step
    /*!
    This function is used to retrieve more information
    about identity columns; it retrieves the auto increment seed and auto increment step.
    n.b.: the values have to be casted to *integers* since they are SQL variants and will 
    come has byte arrays!!
    \param objectID object id
    \param query address if a query object
    \return bool as success or failure of the two operations
    */

    QString strQuery(
        "SELECT CAST(seed_value AS decimal), CAST(increment_value AS decimal) FROM sys.identity_columns WHERE (object_id =:id)"
        );
    if (!query.prepare(strQuery)) return false;
    query.bindValue(":id",objectID);
    query.setForwardOnly(true);
    return query.exec();
}

static bool getIsNullableAndDefault(const QString strTable, const QString strField,
                                    QSqlQuery& query)
{
    //! Get Info about Column
    /*!
    This function uses a query to find out if the column is nullable and 
    its default value (in case it has one!!)
    \param strTable table name
    \param strField field name
    \param query address if a query object
    \return bool as success or failure of the two operations
    */

    QString strQuery=
    "SELECT     TABLE_NAME, COLUMN_NAME, COLUMN_DEFAULT, IS_NULLABLE, DATA_TYPE, CHARACTER_MAXIMUM_LENGTH"
    " FROM         INFORMATION_SCHEMA.COLUMNS"
    " WHERE     (TABLE_NAME LIKE :table) AND (COLUMN_NAME like :column)";

    if (!query.prepare(strQuery)) return false;

    query.bindValue(":table", strTable);
    query.bindValue(":column", strField);
    query.setForwardOnly(true);
    return query.exec();
}

static bool tableHasIdentity(const QString strTableName, bool& bIdentity)
{
    //! Identify Identity Column
    /*!
    This is a convenience function to identify if a table has identity column
    \param strTableName table name
    \param bIdentity address of a bool to put the result
    \sa identityName(const QString strTableName, QString& strField)
    */

    QSqlQuery query;
    QString strQuery=QString("SELECT OBJECTPROPERTY(object_id('") + 
        strTableName + QString("'), 'TableHasIdentity')");
    query.prepare(strQuery);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();
    bIdentity=query.value(0).toBool();
    return true;
}

static bool identityName(const QString strTableName, QString& strField)
{
    //! Identify Identity Column
    /*!
    This is a useful query to retrieve the identity column, of a given table
    (in case it has one); n.b.: use this together with tableHasIdentity(const QString strTableName, bool& bIdentity),
    once we don't support the results for tables with *no* identity column!
    \param strTableName table name
    \param strField address of a string, to put the identity table name
    \return bool as success or failure of the two operations
    \sa tableHasIdentity(const QString strTableName, bool& bIdentity)
    */
    QSqlQuery query;
    QString strQuery(QString(
    "select object_name(object_id),name from sys.identity_columns where objectproperty(object_id,'isusertable')=1 AND object_name(object_id)='")
    + strTableName + QString("'"));
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();
    strField=query.value(query.record().indexOf("name")).toString();
    return true;
}

static bool disableAllConstraints4Table(const QString strTableName, bool bNoCheck){
    QSqlQuery query;
    QString strQuery;
    if (bNoCheck){
        strQuery=QString(
            "ALTER TABLE ") + strTableName + QString(" NOCHECK CONSTRAINT ALL");
    }else{
        strQuery=QString(
            "ALTER TABLE ") + strTableName + QString(" CHECK CONSTRAINT ALL");
    }

    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    return (query.exec());

}

static bool disableAllTriggers4Table(const QString strTableName, bool bDisable)
{
    QSqlQuery query;
    QString strQuery;
    if (bDisable){
        strQuery=QString(
            "ALTER TABLE ") + strTableName + QString(" DISABLE TRIGGER ALL");
    }else{
        strQuery=QString(
            "ALTER TABLE ") + strTableName + QString(" ENABLE TRIGGER ALL");
    }

    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    return (query.exec());

}

static bool clearDBTable(const QString strTableName, bool bReseed=true)
{
    //! Delete Rows from Table
    /*!
    This function uses sql queries to clear a table from all rows, and reseed the identity column (or not)
    n.b.: queries do not support the binding of table names!
    \param strTableName table name
    \param bool reset the identity column
    \return bool as success or failure of the two operations
    */

    if (!disableAllTriggers4Table(strTableName,true)) return false;

    QSqlQuery query;
    QString strQuery="DELETE FROM ";
    strQuery.append(strTableName);
    query.prepare(strQuery);
    query.setForwardOnly(true);

    bool bOk=query.exec();

    if (!disableAllTriggers4Table(strTableName,false)) return false;

    if (bReseed){
        //Reseed columns
        bool bIdentity;
        //Check if we have an identity column, first!
        if (!tableHasIdentity(strTableName,bIdentity)) return false;
        if (bIdentity){
            strQuery="DBCC CHECKIDENT (";
            strQuery.append(strTableName);

            //We must check the starting seed before reseeding!
            QString strField;
            //Check identity field
            if (!identityName(strTableName,strField)) return false;

/*
            //Grabbing the object id
            QSqlQuery idQuery;
            if (!getObjects(idQuery)) return false;

            int objectID=-1;

             while (idQuery.next()) {
                 if (idQuery.value(idQuery.record().indexOf(QObject::tr("TableName"))).toString()==strTableName
                     && idQuery.value(idQuery.record().indexOf(QObject::tr("name"))).toString()==strField){
                        objectID=idQuery.value(idQuery.record().indexOf(QObject::tr("object_id"))).toInt();
                        break;
                 }
             }
*/
             
            int objectID;
            if (!getObjectID4Table(objectID, strField, strTableName))
                return false;
            

             //if (objectID==-1) return false;

            //Get autoincrementinfo
             QSqlQuery seedQuery;
             if (!getAutoIncrementInfo(objectID, seedQuery)) return false;
             if (seedQuery.numRowsAffected()!=1) return false;
             seedQuery.first();
             int seed=seedQuery.value(0).toInt();//Casted seed value

             //We must pass the current value to the reseeder (seed-1)
             strQuery.append(QString(" , RESEED, ") + QVariant(seed-1).toString()
                 + QString(")"));
            query.prepare(strQuery);
            query.setForwardOnly(true);
            query.exec();
        }
    }

    return bOk;
}

static QString selectAllRecordsFromTable(const QString strTable)
{
    return QString("SELECT * FROM ") + strTable;
}

static QString identifyConstraint()
{
    //! identify Constraints
    /*!
    This query returns the constraint name, given a certain id (binded parameter)
      \return QString SQL query text as string
    */
    return QString(
    "SELECT sys.sysobjects.name as NAME, sys.sysobjects.xtype FROM sys.sysobjects INNER JOIN sys.sysforeignkeys ON sys.sysobjects.id = sys.sysforeignkeys.constid WHERE (sys.sysobjects.id = ?)"
);

}

static QString selectPKConstraints(const QString strTable=QString())
{
    //! Select PK Constraints
    /*!
    This query returns the FK constraints from a certain table
    \param strTable if this parameter is empty will return all constraints from the database
     \return QString SQL query text as string
    */
    if (!strTable.isEmpty() && !strTable.isNull())
        return QString(
"SELECT Col.COLUMN_NAME, Tab.CONSTRAINT_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS Tab INNER JOIN INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE AS Col ON Tab.CONSTRAINT_NAME = Col.CONSTRAINT_NAME AND Tab.TABLE_NAME = Col.TABLE_NAME WHERE (Tab.CONSTRAINT_TYPE = 'PRIMARY KEY ') AND (Col.TABLE_NAME = '")
+ strTable + QString("')");
    else
        return QString(
    "SELECT Col.COLUMN_NAME, Tab.CONSTRAINT_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS Tab INNER JOIN INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE AS Col ON Tab.CONSTRAINT_NAME = Col.CONSTRAINT_NAME AND Tab.TABLE_NAME = Col.TABLE_NAME WHERE (Tab.CONSTRAINT_TYPE = 'PRIMARY KEY ')"
    );
}

static QString selectFKConstraints(const QString strTable=QString(), bool bFK=true)
{
    //! Select Constraints
    /*!
    This query returns the FK constraints related to a certain table; having the table has
    primary or foreign is controlled by the bool bFK parameter (which defaults to true, so the table is Foreign).
    \param strTable if this parameter is empty will return all constraints from the database
    \param FK this parameter only makes sense when the query is refering to a certain table, and it controls
    whether we want to have it as foreign, or primary table;
     \return QString SQL query text as string
    */
    if (!strTable.isEmpty() && !strTable.isNull())
        return QString(
"SELECT FK.TABLE_NAME AS FK_Table, CU.COLUMN_NAME AS FK_Column, PK.TABLE_NAME AS PK_Table, PT.COLUMN_NAME AS PK_Column, C.CONSTRAINT_NAME AS Constraint_Name FROM INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS C INNER JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS FK ON C.CONSTRAINT_NAME = FK.CONSTRAINT_NAME INNER JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS PK ON C.UNIQUE_CONSTRAINT_NAME = PK.CONSTRAINT_NAME INNER JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS CU ON C.CONSTRAINT_NAME = CU.CONSTRAINT_NAME INNER JOIN (SELECT i1.TABLE_NAME, i2.COLUMN_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS i1 INNER JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS i2 ON i1.CONSTRAINT_NAME = i2.CONSTRAINT_NAME WHERE (i1.CONSTRAINT_TYPE = 'PRIMARY KEY')) AS PT ON PT.TABLE_NAME = PK.TABLE_NAME WHERE ")
 + (bFK?"FK.TABLE_NAME='":"PK.TABLE_NAME='") + strTable + "'";
    else
        return QString(
        "SELECT FK.TABLE_NAME AS FK_Table, CU.COLUMN_NAME AS FK_Column, PK.TABLE_NAME AS PK_Table, PT.COLUMN_NAME AS PK_Column, C.CONSTRAINT_NAME AS Constraint_Name FROM INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS C INNER JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS FK ON C.CONSTRAINT_NAME = FK.CONSTRAINT_NAME INNER JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS PK ON C.UNIQUE_CONSTRAINT_NAME = PK.CONSTRAINT_NAME INNER JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS CU ON C.CONSTRAINT_NAME = CU.CONSTRAINT_NAME INNER JOIN (SELECT i1.TABLE_NAME, i2.COLUMN_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS i1 INNER JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS i2 ON i1.CONSTRAINT_NAME = i2.CONSTRAINT_NAME WHERE (i1.CONSTRAINT_TYPE = 'PRIMARY KEY')) AS PT ON PT.TABLE_NAME = PK.TABLE_NAME"
        );
}

static QString selectAllConstraints()
{
        return QString(
    "SELECT OBJECT_NAME(object_id) AS NameofConstraint, SCHEMA_NAME(schema_id) AS SchemaName, OBJECT_NAME(parent_object_id) AS TableName, type_desc AS ConstraintType FROM sys.objects WHERE (type_desc LIKE '%CONSTRAINT')"
    );
}

static bool createFKConstraint(const MapFK mapFK)
{
    QSqlQuery query;
    QString strSql;
     MapFK::const_iterator i;
     for (i = mapFK.constBegin(); i != mapFK.constEnd(); ++i){

         MapFK::iterator j = mapFK.find(i.key());
         QString strChildKeys, strParentKeys, strChild, strParent;
         strChild=(*j).m_child;
         strParent=(*j).m_parent;
         strSql=( QString("ALTER TABLE ")+ strChild +
             QString(" WITH CHECK ADD CONSTRAINT ") + i.key() + 
            QString(" FOREIGN KEY(") );

         while (j != mapFK.end() && j.key() == i.key()) {
             strChildKeys.append(j.value().m_childkey);
             strChildKeys.append(",");
             strParentKeys.append(j.value().m_parentkey);
             strParentKeys.append(",");
             ++j;
         }
         strParentKeys.remove(strParentKeys.length()-1,1);//remove last comma
         strChildKeys.remove(strChildKeys.length()-1,1);//remove last comma

        strSql.append(strChildKeys + QString(") REFERENCES ") + (strParent) + 
        QString(" (") + strParentKeys + QString(")") );

        query.prepare(strSql);
        query.setForwardOnly(true);
        if (!query.exec()){
            return false;
        }

     }
     return true;
}

static bool storeFKConstraints(const QString strTableName, const bool bFK, MapFK& mapFK)
{
    //TODO: add a description here later!

    //If there are any FK referencing this table, we *must* delete them first!
    QSqlQueryModel model;
    model.setQuery(selectFKConstraints(strTableName,bFK));

    //N.b.: always do this to force retrieving the column count, as the SQL server driver
    // has a limit of 256 rows!!!!
    while (model.canFetchMore())
    {
        model.fetchMore();
    }

    for (size_t i=0; i < (size_t)model.rowCount();++i){
        QSqlRecord rec=model.record(i);

        QString fkName=rec.value("CONSTRAINT_NAME").toString();
        mapFK.insert(fkName,FK(rec.value("PK_Table").toString(),
            rec.value("FK_Table").toString(),rec.value("PK_Column").toString(),
            rec.value("FK_Column").toString()));
    }

    return true;
}

static bool dropFKConstraints(const QString strTableName, const bool bFK)
{
    //TODO: add a description here later!

    //If there are any FK referencing this table, we *must* delete them first!
    QSqlQueryModel model;
    model.setQuery(selectFKConstraints(strTableName,bFK));

    //N.b.: always do this to force retrieving the column count, as the SQL server driver
    // has a limit of 256 rows!!!!
    while (model.canFetchMore())
    {
        model.fetchMore();
    }

    for (size_t i=0; i < (size_t)model.rowCount();++i){
        QSqlRecord rec=model.record(i);

        QString fkName=rec.value("CONSTRAINT_NAME").toString();
        if (!dropConstraint(fkName, rec.value("FK_Table").toString())) return false;
    }

    return true;
}

static bool verifyConstraintName(const QString inStr, QString& outStr)
{
    //! Amend Constraint Name
    /*!
    This function checks if this constraint name is already in use in the db, and it case
    it is, it renames it by appending an underscore; then it loops again, to see if the new name
    is also in use;
    \param inStr original constraint name
    \param outStr address of a string to put the new constraint name
    \return bool as success or failure
    */

    QSqlQueryModel model;
    model.setQuery(selectAllConstraints());

    //N.b.: always do this to force retrieving the column count, as the SQL server driver
    // has a limit of 256 rows!!!!
    while (model.canFetchMore())
    {
        model.fetchMore();
    }

    QString strFkName=inStr;
    size_t j=0;
    while (j < (size_t)model.rowCount()){
        QSqlRecord rec=model.record(j);
        if (rec.value("NameofConstraint").toString()==(strFkName)){
            strFkName.append("_");
            j=-1;//Search again from beginning
        }
        ++j;
    }
    outStr=strFkName;
    return true;
}

static bool getSchemaType(const QVariant type, const QMap<QString,QString>& mapQt2Xs, QString& strType)
{
    //! Return schema type from a Qt Type
    /*!
    This function maps the Qt data types into xml schema types
    n.b.: do not use tinyint types in the database, as they come converted as uint and will
    be mixed with booleans by qt! (maybe in the future we need to take the translation layer of
    types from Qt's "shoulders" and use a more precise method (for instance, query the database!)
    \param type in: QVariant type
    \par mapQt2Xs in: reference of a map, containing the conversion from Qt to Schema types
    \param strType out: string with a xs type
    \return bool as success or failure
    */

    QMap<QString, QString>::const_iterator it = mapQt2Xs.find(type.typeName());
    if (it == mapQt2Xs.end()) return false;//first check point
    strType=it.value();
    return !strType.isEmpty() && !strType.isNull();//second check point
}

static QString listCASImportTables(const QString strTable=QString())
{
    //! List CAS Tables
    /*!
    This function retrieves a query to list the original name of all the tables
    from CAS that we want to import
    \param strTable optional table name to filter query
    \return query string
    */

    return QString("SELECT original_name, imported_name FROM Info_Tables_Import") + 
        (strTable.isEmpty()?QString(""): QString(" WHERE original_name='")
        +strTable + QString("'"));
}

static bool getNullForType(const QString strType, const QString strInternalName, QString& outStrNull)
{
    //! Get Nulls Replacement
    /*!
    This function gets the designated value to replace a null in the database;
     Designated values are on table [Null_Replacements], referenced by an internal name and description
     to fit a variety of situations. Since null replacements take the data type of the field, we need 
     a range of null replacements to support many data types; at this moment supported types are:
     different flavours of char and int, float, decimal, datetime and bit (boolean).
     ; the desired internal_name of the null is given and it is calculated a 
     TODO: add time stamp!
    \param strType field type (to calculate appropriated name)
    \param strInternalName internal name of the null (on table [Null_Replacements]
    \param outStrNull out: string variable to put the null replacement in
    \return bool as success or failure;
    */
    QSqlQuery query;
    QString strQuery, strPar;

    if (strType.contains("nvarchar") || strType.contains("varchar")){
        strPar="varchar";
    }
    else if (strType.compare("nchar(3)")==0 || strType.compare("char(3)")==0){
        strPar="char3";
    }
    else if (/*strType.compare(QObject::tr("smallint"))==0 || */strType.compare("bigint")==0
        || strType.compare("int")==0){
        strPar="int";
    }
    else if (strType.compare("smallint")==0){
            strPar="smallint";
    }
    else if (strType.compare("datetime")==0){
        strPar="datetime";
    }
    else if (strType.compare("bit")==0 || strType.compare("tinyint")==0){
        strPar="bit";
    }
    else if (strType.compare("decimal")==0/* || strType.compare(QObject::tr("float"))==0*/){
        strPar="float";
    }
    else if ( strType.compare("float")==0 ){//we currently *DO NOT* support floats: only decimals!!!!
        return false;
    }
    else return false;

    strQuery=QString("SELECT ") + strPar + QString(" FROM GL_Null_Replacements WHERE internal_name='")
    + strInternalName + QString("'");
    query.prepare(strQuery);

    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()<1) return false;
    query.first();
    outStrNull=query.record().value(0).toString();
    return true;
}

static bool replaceNulls(const QString strTable, const QString strField, const QString strType, const QString strInternalName)
{
    //! Replace Nulls
    /*!
    This function performs an update on a certain table, and a certain field, in order to replace nulls
     for a value from table [Null_Replacements]; the desired internal_name of the null is given and it is calculated a 
     value, based on its type;
     Supported types are: nvarchar,varchar,nchar(3),char(3),int,smallint,decimal,bit,datetime.
     TODO: add time stamp!
    \param strTable table name
    \param strType field type (to calculate appropriated name)
    \param strInternalName internal name of the null (on table [Null_Replacements]
    \return bool as success or failure;
    */

    QString val;
    if (!getNullForType(strType,strInternalName,val)) return false;
    QString strQuery=QString("UPDATE ") + strTable + QString(" SET ") +
        strField + QString("='") + val + QString("' WHERE ") + strField + 
        QString(" IS NULL");

    QSqlQuery query;
    query.prepare(strQuery);

    query.setForwardOnly(true);
    if (!query.exec()) return false;

    return true;
}

static bool getFields(const QString strTable, QMap<QString,QString>& mapTypes, QMap<QString,int>& mapSizes)
{
    //TODO: Describe this!

    QSqlQuery query;
    QString strQuery="select column_name,DATA_TYPE,CHARACTER_MAXIMUM_LENGTH from information_schema.columns where table_name = :table";
    if (!query.prepare(strQuery)) return false;
    query.bindValue(":table",strTable);
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    while (query.next()){
        mapTypes.insert(query.value(0).toString(),query.value(1).toString());
        mapSizes.insert(query.value(0).toString(),(size_t)query.value(2).toInt());
    }
    return true;
}

static bool getImportedFieldsDescription(const QString strTable, QMap<QString,QString>& mapTypes, QMap<QString,int>& mapSizes)
{
    //TODO: Describe this!
    QSqlQuery query;
    QString strQuery="select field_name,original_type,original_size FROM Info_Fields where table_name = :table";
    if (!query.prepare(strQuery)) return false;
    query.bindValue(":table",strTable);
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    while (query.next()){
        mapTypes.insert(query.value(0).toString(),query.value(1).toString());
        mapSizes.insert(query.value(0).toString(),(size_t)query.value(2).toInt());
    }
    return true;
}

static QString alterNull(const QString strTable, const QString strField,
                         const QString strType, bool bNull=true){

    return QString("ALTER TABLE ") + strTable + QString(" ALTER COLUMN ") + strField +
        QString(" ")+
        strType + (!bNull? " NOT ":QString(" ")) + QString("NULL");
}

static bool prepareAdjacencyTable(HashNodeRef& mapTablesFields)
{
    //Supported table structure to import: ID (nvarchar) field, Name, NameENG, Description

    //n.b.: respect this order!
    if (!dropTableIfExists("##List_Conversion")) return false;

    MapFK mapFK;
    if (!storeFKConstraints("Fr_Tree",false,mapFK)) return false;//We must store existing FK referencing this table, since we are going to remove them!
    if (!dropFKConstraints("Fr_Tree",false)) return false;

    if (!clearDBTable("Fr_Tree")) return false;
    if (!clearDBTable("Fr_Node_Description")) return false;

    QSqlQuery query, query2;
    QString strQuery;
    //Initialize Root on Node_description
    if (!query.prepare("INSERT INTO Fr_Node_Description (name,name_eng) VALUES('Root','Root')")) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.finish();

    //Create TMP table and fill with the mapping between old codes and new codes
    if (!query.prepare("CREATE TABLE ##List_Conversion( [id] [int] IDENTITY(1,1) NOT NULL, [table_name] [nvarchar](50) COLLATE SQL_Latin1_General_CP1_CI_AS NULL, [code] [int] NULL, CONSTRAINT [PK_List_Conversion] PRIMARY KEY CLUSTERED ( [id] ASC )WITH (PAD_INDEX = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY] ) ON [PRIMARY]")) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.finish();

    if (!query.prepare("INSERT INTO ##List_Conversion (table_name,code) VALUES('Root',0)")) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.finish();

     HashNodeRef::const_iterator i = mapTablesFields.constBegin();
     while (i != mapTablesFields.constEnd()) {
         strQuery=QString("SELECT * FROM ") + i.value()->m_strTable;
        if (!query.prepare(strQuery)) return false;
        query.setForwardOnly(true);
        if (!query.exec()) return false;
        QVector<QString> vQueries;

        while (query.next()){
            strQuery=QString("INSERT INTO ##List_Conversion (table_name,code) VALUES('") + 
             i.value()->m_strTable + QString("',CAST(") + query.record().value("id").toString()+
             QString(" AS INT))");
            //if (!query2.prepare(strQuery)) return false;
            //if (!query2.exec()) return false;
            //query2.finish();
            vQueries.append(strQuery);
        }
        query.finish();

        QVector<QString>::const_iterator queriesIterator;
        //now batch execute queries!
        for (queriesIterator = vQueries.constBegin(); queriesIterator != vQueries.constEnd();
            ++queriesIterator){
            if (!query.prepare(*queriesIterator)) return false;
            query.setForwardOnly(true);
            if (!query.exec()) return false;
            query.finish();
        }

        ++i;
     }

    query.prepare("SELECT int FROM GL_Null_Replacements WHERE internal_name='Missing'");
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();
    QString strNull=query.value(0).toString();

    query.finish();
    //Initialize Root on Fr_Tree
    if (!query.prepare(QString("INSERT INTO Fr_Tree (parent,lft,rgt,depth) VALUES(-1,") + strNull +
        QString(",") + strNull + QString(",") + strNull + QString(")"))) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.finish();

    //First check nulls
    QString strType;
    //Turn off null clause
    QStringList treeFields;
    treeFields << "lft" << "rgt" << "depth";

    QStringList::const_iterator constIterator;
    for (constIterator = treeFields.constBegin(); constIterator != treeFields.constEnd();
        ++constIterator){
        if (!getFieldType("Fr_Tree",*constIterator,strType)) return false;
        strQuery=alterNull("Fr_Tree",*constIterator,strType,true);
        if (!query.prepare(strQuery)) return false;
        query.setForwardOnly(true);
        if (!query.exec()) return false;
        query.finish();
    }

     if (!disableAllTriggers4Table("Fr_Node_Description",true)) return false;
     if (!disableAllTriggers4Table("Fr_Tree",true)) return false;

    //Fill Fr_Node_Description
    i = mapTablesFields.constBegin();
    while (i != mapTablesFields.constEnd()) {
             strQuery=
             QString("INSERT INTO Fr_Node_Description (name,name_eng,description,OLD_CODE) ")+ //n.b.: removing nulls from description and name_eng
             QString(
             //"SELECT Name,NameENG,Description,ID FROM ") +
             "SELECT Name,CASE WHEN NameENG IS NULL THEN 'missing' ELSE NameENG END as NameENG, CASE WHEN Description IS NULL THEN 'missing' ELSE Description END as Description, ID FROM ") +
            i.value()->m_strTable;

             if (!query.prepare(strQuery)) return false;
             query.setForwardOnly(true);
             if (!query.exec()) return false;
             query.finish();

             ++i;
    }

    //Fill Fr_Tree
    size_t ct=0;
    i = mapTablesFields.constBegin();
    while (i != mapTablesFields.constEnd()) {
                strQuery=QString("SELECT ") + i.value()->m_strField + QString(
                    " FROM ") + i.value()->m_strTable;
                if (!query.prepare(strQuery)) return false;
                query.setForwardOnly(true);
                if (!query.exec()) return false;

                QVector<QString> vQueries;

                while (query.next()){
                    if (ct>0){
                        HashNodeRef::const_iterator ii = i;
                        --ii;
                        strQuery=QString("INSERT INTO Fr_Tree (parent) SELECT id FROM ##List_Conversion WHERE CODE=")+
                            query.record().value(i.value()->m_strField).toString() + QString(" AND table_name like '") +
                            ii.value()->m_strTable + QString("'");
                    }else{
                        strQuery="INSERT INTO Fr_Tree (parent) VALUES(1)";
                    }
                    vQueries.append(strQuery);
                }
                query.finish();

                QVector<QString>::const_iterator queriesIterator;
                //now batch execute queries!
                for (queriesIterator = vQueries.constBegin(); queriesIterator != vQueries.constEnd();
                    ++queriesIterator){
                    if (!query.prepare(*queriesIterator)) return false;
                    query.setForwardOnly(true);
                    if (!query.exec()) return false;
                    query.finish();
                }

            ct++;
            ++i;
    }

     //Put nulls back, but first update...
    for (constIterator = treeFields.constBegin(); constIterator != treeFields.constEnd();
        ++constIterator){

            strQuery=QString("UPDATE Fr_Tree set ") + *constIterator + QString("='") + strNull + QString("' WHERE ") + *constIterator 
            + QString(" IS NULL");
        if (!query.prepare(strQuery)) return false;
        query.setForwardOnly(true);
        if (!query.exec()) return false;
        query.finish();

        if (!getFieldType("Fr_Tree",*constIterator,strType)) return false;
        strQuery=alterNull("Fr_Tree",*constIterator,strType,false);

        if (!query.prepare(strQuery)) return false;
        query.setForwardOnly(true);
        if (!query.exec()) return false;
        query.finish();
    }

    //Don't forget to remove the Temp Table!
    strQuery="DROP TABLE ##List_Conversion";
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    //Don't forget to put the constraints back
    if (!createFKConstraint(mapFK)) return false;

    if (!disableAllTriggers4Table("Fr_Node_Description",false)) return false;
    if (!disableAllTriggers4Table("Fr_Tree",false)) return false;

    return true;
}

static bool convert2List(HashNodeRef mapTablesFields)
{
    if (!prepareAdjacencyTable(mapTablesFields)) return false;
    return true;
}

static bool updateDepth(const int id)
{
    //! Update Depth
    /*!
    This function fills the depth field, which reflects the indentation of the node on the hierarchy.
    It is stored in the db for information purposes 
    N.b: This function affects one record *only*!
    \par id id of the node.
    \return booleans as success or failure
    */

    QSqlQuery query;
    //Query for Depth
    QString strQuery="SELECT COUNT(t2.id)-1 as depth, T1.id from Fr_Tree as T1, Fr_Tree as T2 WHERE ( (T1.lft BETWEEN t2.lft AND T2.rgt) AND T1.id=? ) GROUP BY T1.lft, T1.id";
    query.prepare(strQuery);
    query.addBindValue(id);
    query.setForwardOnly(true);
    query.exec();

    if (query.numRowsAffected()<1) return false;
    query.first();
    int result=query.value(query.record().indexOf("depth")).toInt();

    //Update
    strQuery="UPDATE Fr_Tree Set depth=? WHERE id=?";
    query.prepare(strQuery);
    query.addBindValue(result);
    query.addBindValue(id);
    query.setForwardOnly(true);
    query.exec();

    return query.numRowsAffected()==1;
}

static bool list2Nested()
{
    if (!disableAllTriggers4Table("Fr_Tree",true)) return false;

    QSqlQuery query;
    if (!query.prepare("list2Nested")) return false;
    if (!query.exec()) return false;

    //update depth
    if (!query.prepare("SELECT id from Fr_Tree")) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()<1) return false;
    while (query.next())
    {
        if (!updateDepth(query.record().value("id").toInt())) return false;
    }
     if (!disableAllTriggers4Table("Fr_Tree",false)) return false;
    return true;
}

static bool getFieldDescriptionFromDB(const QString strTable, const QString strField, QSqlQuery& query)
{
    //! Get Field Description
    /*!
    This function selects one record on Info_Fields, providing the information to import a certain field
    into the DB;
    N.b: This function affects one record *only*!
    \par strTable table name
    \par strField field name
    \par query address of a query to put the result
    \return booleans as success or failure
    */

    QString strQuery="SELECT * FROM Info_Fields WHERE table_name LIKE :table and field_name LIKE :field";
    if (!query.prepare(strQuery)) return false;
    query.bindValue(":table",strTable);
    query.bindValue(":field",strField);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    return query.numRowsAffected()==1;
}

static bool findNullReplacementFields(const QString strTable,
                        QHash<QString,QString>& nullValues)
{
    //TODO: add description
    QSqlQuery query;
    QString strSql="SELECT field_name,NullValue from Info_Fields WHERE table_name=:table AND replaceNulls=1";
    if (!query.prepare(strSql)) return false;
    query.bindValue(":table",strTable);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()>0)
    {
        while (query.next()){
            nullValues.insert(query.record().value(0).toString(),query.record().value(1).toString());
        }
    }

    return true;
}

static bool selectValue(const QString strFieldOut, const QString strTable, const QHash<QString,QString>& mapFieldValue,
                        QSqlRecord& rec, bool bAppendQuotes=true){
    //! Select Value
    /*!
    This is an utility function that will provide the result of a simple SELECT+WHERE query;
    Its receives as parameters a field that will be returned on the result, a table name, and an hash that can
    contain multiple fields/values to build the query condition.
    \par strFieldOut field returned on the result
    \par strTable table name
    \par mapFieldValue hash containing WHERE parameteres (field,value) pairs
    \par rec out: record with the result
    \return booleans boolean indicating whether this table contains or not a "converted" ID field.
    */

    QSqlQuery query;
    QString strWHERE;
    QHash<QString, QString>::const_iterator i = mapFieldValue.constBegin();
    size_t ct=0;
    while (i != mapFieldValue.constEnd()) {
        if (ct) strWHERE.append(QString(" AND "));
        strWHERE.append(i.key() + QString("=") + (bAppendQuotes?QString("'"):QString("")) + i.value() +
            (bAppendQuotes?QString("'"):QString("")));
     ++i;
     ++ct;
    }

    QString strQuery=QString("SELECT ") + strFieldOut + QString(" FROM ") + strTable +
        QString(" WHERE ") + strWHERE;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    if (query.numRowsAffected()>0)
    {
        query.first();
        rec=query.record();
        return true;
    }
    return false;
}

static bool convert2PK(const QString strTable)
{
    //! Convert to Primary Key
    /*!
    This is a simple convenience function that indicates whether this table has a "converted" ID field;
    that is: a created autoincrement, identity field that will replace a now obsolete PK.
    n.b.: this function will return false, also if it cannot find the giventable in the list of imported tables...
    \par strTable table name
    \return booleans boolean indicating whether this table contains or not a "converted" ID field.
    */

    QString strQuery="SELECT convertPK2Int FROM Info_Tables_Import WHERE imported_name=:table";
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.bindValue(":table",strTable);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()>0)
    {
        query.first();
        return query.record().value(0).toBool();
    }
    return false;
}

static bool renameColumn(const QString strTable, const QString strField, const QString strNewName)
{
    QString strQuery=QString("EXEC sp_rename '") + strTable + QString(".") + strField +
        QString("', '") + strNewName + QString("', 'COLUMN'");
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        //qDebug() << strQuery << endl;
        return false;
    }
    return true;
}

static QString getDefaultCstrt(const QString strTable, const QString strField)
{
    return 
        QString("select t.name, c.name, d.name as constraint_name, d.definition from sys.tables t join sys.default_constraints d on d.parent_object_id = t.object_id join sys.columns c on c.object_id = t.object_id and c.column_id = d.parent_column_id where t.name = '") 
        + strTable + QString("' and c.name = '") + strField + QString("'");
}

static bool dropColumn(const QString strTable, const QString strField)
{
    QString strQuery=QString("ALTER TABLE ") + strTable + QString(" DROP COLUMN ") + strField;
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }
    return true;
}

static bool renameTable(const QString oldTableName, const QString newTableName)
{
    QString strQuery=QString("EXEC sp_rename '") + oldTableName + QString("', '") + newTableName
        + QString("'");
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }
    return true;
}

static bool copyTable(const QString strTableFrom, const QString strTableTo, bool bExists)
{
    QString strQuery;
    if (!bExists){
        strQuery=QString("SELECT * INTO ") + strTableTo +  QString(" FROM ") + strTableFrom;
    }
    else{
        QMap<QString,QString> mapTypes;
        QMap<QString,int> mapSizes;
        if (!getFields(strTableFrom,mapTypes,mapSizes)) return false;
        QString strFields;

        //In case the table has an identity column, we must identify it and exclude it from the inserts!
        QString strIdentity;
        bool bIdentity=false;
        if (!tableHasIdentity(strTableFrom,bIdentity)) return false;
        if (bIdentity){
            if (!identityName(strTableFrom,strIdentity)) return false;
        }

        QMap<QString, QString>::const_iterator i = mapTypes.constBegin();
        while (i != mapTypes.constEnd()) {
            if (i.key().compare(strIdentity)!=0){
                strFields.append(i.key());
                strFields.append(",");
            }
             ++i;
        }
        strFields.remove(strFields.lastIndexOf(","),1);

        strQuery=QString("INSERT INTO ") + strTableTo + QString(" (") + strFields +
            QString(") SELECT ") + strFields + QString(" FROM ") + strTableFrom;
    }

    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << query.lastError().text() << endl;
        return false;
    }
    return true;
}

static bool generateTMPTableName(const QString instrTableName, QString& outStrTableName, bool bVerify=false)
{
    QSqlQuery query;
    outStrTableName=TMPCHAR + instrTableName;

    if (bVerify){
        //Create TMP table name, but first make sure it does not exist yet...
        if (!getObjects(query,outStrTableName)) return false;
        while (query.numRowsAffected()>0){
            outStrTableName=TMPCHAR + outStrTableName;
            if (!getObjects(query,outStrTableName)) return false;
        }
    }

    return true;
}

static bool fixQueryValue(const QString strType, QString& strVal)
{
    if ( strType=="nvarchar" || strType=="varchar" || strType=="char"
        || strType=="nchar"){
            if (!escapeSqlString(strVal)) return false;

                strVal.prepend("'");
                strVal.append("'");
        }
    else if (strType=="datetime"){
            QString strOut;
            if (!castDate(strVal,strOut))
                return false;
            strVal=strOut;
            strVal.prepend("'");
            strVal.append("'");
        }
    else if (strType=="bit"){
            QString strOut;
            if (!castBoolean(strVal,strOut))
                return false;
            strVal=strOut;
        }

    return true;
}

static bool getMappedTMPName(const QString inStrName, const QMap<QString,QString>& mapTMPNames, QString& outStrName)
{
    QMap<QString,QString>::iterator it=mapTMPNames.find(inStrName);
    if (it==mapTMPNames.end()) return false;
    outStrName=it.value();

    return true;
}

static bool getNullReplacements(QStringList& list){

    QString strQuery="Select internal_name from GL_Null_Replacements WHERE internal_name <> 'misc'";
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }
    if (query.numRowsAffected()< 1) return false;
    while (query.next())
        list << query.record().value(0).toString();

    return true;
}

static bool GetCurentLocation(int& locationID)
{
    QString strQuery=
        "Select ID FROM Location WHERE IsCurrent=1";
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }

    //We only allow one current location at a time
    if (query.numRowsAffected()!= 1) return false;
    query.first();
    locationID=query.record().value("ID").toInt();

    return true;
}

static bool getIdForValue(const QString strTable, const QString strIdField,
                                    const QString strPar, QString& strId)
{//!< This is a convenience function to retrieve the id of a given value!

    QSqlQuery query;
    if (!query.prepare(
        QString("SELECT ") + strIdField + QString(" FROM ") + strTable + QString(" WHERE (Name LIKE :par)"))) return false;
    query.bindValue(":par",strPar);

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    strId=query.value(query.record().indexOf(strIdField)).toString();

    return true;
}

static QString countOcurrenciesForThisPort()
{
    return QString(
    "SELECT count(Ref_PSU.Name) FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par"
    );
}

static QString checkActiveFromLastRecord()
{
    return QString(
"SELECT Top(1) ActiveVessels,TempRemoved FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par ORDER by id_activity DESC"
    );
}

static QString checkIfPortHasVessels1(const QString strPsu)//OBSOLETE
{
    //N.b.: *the use of this function was descontinued, because we want to use binded queries instead!!!*

    //! Check if Port has Vessels -- first test
    /* This function was designed to test a given PSU, to find out whether it has already
    a record in CAS_Activity, and in case it has if it contains active vessels;
    if it contains active vessels it returns 1, otherwise it returns false;
    if there is no record in CAS_Activity, it also returns true;
    n.b.: unfortunately is impossible to have this query as cached...!
    \param strPsu Name of the samping unit
    \return QString as query string;
    */

    QString str= 

"declare @cnt int, @act int, @tempRem int, @sum int "
"set @cnt=(SELECT count(Ref_PSU.Name) FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par) "
"if (@cnt>0) "
"Begin "
"    set @act=(SELECT Top(1) ActiveVessels FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par ORDER by id_activity DESC) "
"    set @tempRem=(SELECT Top(1) TempRemoved FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par ORDER by id_activity DESC) "
"    set @sum=@act + @tempRem "
"    if (@sum=0) select(0) else select(1) "
"End "
"else select (1)"

//"IF :par IN (SELECT distinct Ref_PSU.Name FROM Reg_Vessels INNER JOIN Ref_PSU ON HomePort=ID) BEGIN select (1) END ELSE BEGIN select (0) END"
//"IF :par IN (SELECT Name FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID) BEGIN select (1) END ELSE BEGIN select (0) END"
;

    str.replace(":par","'" + strPsu + "'");
    return str;
}

static QString checkIfPortHasVessels2()
{
    //! Check if Port has Vessels -- second test
    /* This function was designed find out if there are any vessels registered for this port;
    if it has any vessels it returns 1, otherwise it returns false;
    \return QString as query string;
    */

    return QString(
        "IF :par IN (SELECT distinct Ref_PSU.Name FROM Reg_Vessels INNER JOIN Ref_PSU ON HomePort=ID) select(1) else select(0) "
);
}

static bool getYearLimits(int& start, int&end)
{
    //We retrieve the last inserted limits that are active (in case there are more than 1)!
    QSqlQuery query;
    if (!query.prepare(
        "select Top(1) start_year,end_year from Ref_Year_Limits WHERE active=1 ORDER BY ID DESC")) return false;

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    start=query.value(0).toInt();
    end=query.value(1).toInt();

    return true;
}

static bool getLastIdActivity(QString& strId)
{
    //! Get Last id_activity
    /* This function find the last id_activity/last record on CAS_activity;
    \par strId address of a string, to put the result on;
    \return boolean as sucess or failure
    */

    QSqlQuery query;
    if (!query.prepare(
        "select Top(1) id_activity from CAS_Activity ORDER BY id_activity DESC")) return false;

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    strId=query.value(0).toString();

    return true;
}

static bool getLastRecordFromTable(const QString strId, const QString strTable, QSqlRecord & rec)
{
    //! Get Last record of a Given Table
    /* This function finds the last record of a given table, given an order ID (to apply the ORDER BY to)
    \par strId name of the id field
    \par strTable table name
    \par rec address if an QsqlRecord to put the result on
    \return boolean as sucess or failure
    */

    QSqlQuery query;
    if (!query.prepare(
        QString("select Top(1) * from ") + strTable + QString(" ORDER BY ") + 
        strId + QString(" DESC")
        )) return false;

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    rec=query.record();

    return true;
}

static bool getNaRuleID(size_t& id)
{
    //! Get the ID of the 'n/a' rule
    /* This is a convenience function to grabb the ID of the rule that contains 'n/a';
    This rule is used to mark dummy trigger ptrs, that only store references to controls:
    in this way they can also be stored in the reference map.
    \par id size_t address, to put the id of the rule
    \return boolean as sucess or failure
    */

    QSqlQuery query;
    if (!query.prepare(
        "select id from UI_Rules WHERE [rule] like 'n/a'")) return false;

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    id=(size_t)query.value(0).toInt();

    return true;
}

static QString selectPortsFromDifferentPsu(const QString idPsu)
{
    //! Select Ports from a different psu
    /* This is a query to look for ports that belong do a different Psu, and
    at the same time are being sampled by the logbook approach;
    This function was made obsolete in the current app since we retrieve this query
    from a view in the db.
    \par idPsu current psu
    \return QString query string
    */

        QString strQuery=
        "SELECT     DISTINCT "
        "             A.HomePort, B.id_psu, B.name "
        "FROM         dbo.Reg_Vessels A INNER JOIN "
        "              dbo.Ref_Source ON A.VesselID = dbo.Ref_Source.VesselID "
        "                    INNER JOIN Ref_Ports B on A.HomePort=B.ID "
        " WHERE     (dbo.Ref_Source.IsLogBook = 1)  AND ((SELECT count(ID) from Ref_Ports WHEre B.id_psu<>PAR)>0)"
        ;

        strQuery.replace("PAR",idPsu);
    return strQuery;
}

static QString viewVesselsFromAnotherPort(const QString idPsu)
{
    //! Select Other Ports
    /* This is a query to look for other ports that belong to the same Psu, and
    at the same time are being sampled by the logbook approach;
    This function was made obsolete in the current app since we retrieve this query
    from a view in the db.
    \par idPsu current psu
    \return QString query string
    */

    return QString(
        "SELECT     dbo.Ref_Source.VesselID, dbo.Reg_Vessels.UniqueRegistrationNumber, dbo.Reg_Vessels.Name, dbo.Reg_Vessels.MainGearType, "
        "                      dbo.Reg_Vessels.Flag, dbo.Reg_Vessels.HomePort, dbo.Reg_Vessels.Length, dbo.Reg_Vessels.EnginePower, dbo.Reg_Vessels.GT, "
        "                      dbo.Reg_Vessels.VesselType "
        "FROM         dbo.Reg_Vessels INNER JOIN "
        "                      dbo.Ref_Source ON dbo.Reg_Vessels.VesselID = dbo.Ref_Source.VesselID "
        "WHERE     (dbo.Reg_Vessels.HomePort NOT IN "
        "                          (SELECT     ID"
        "                            FROM          dbo.Ref_Ports"
        "                            WHERE      (id_psu = ") + idPsu + 
        QString(" ))) AND (dbo.Ref_Source.IsLogBook = 1)        ")
        ;
}

static QString updateMonthlyFrameWithAddedVessel()
{
    //! Add New Vessel to the Monthly Frame
    /* This is a query to update the monthly frame with a new vessel;
    The vessel is set up as permanently added (default), with an 'uknown' reason;
    you can amend this later, through the UI.
    n.b.: this is a binded query, to you need to bind a :par later, with the vesselID
    and also with Added and tempAdded ids!
    \return QString query string
    */

        return QString(
    "DECLARE @par int, @id_activity int, @added INT, @tempAdded INT; "
    "SET @par=:par "
    "SET @id_activity=(SELECT Top(1) id_activity from CAS_Activity ORDER BY id_activity DESC) "
    "IF(SELECT IsLogBook FROM Ref_Source WHERE VesselID=@par)=0 SET @added=1 "
    "ELSE SET @added=2;"
    "INSERT INTO CAS_MonthlyFrame (VesselID,id_activity,id_gear,id_operational_status,id_temp_removed,id_removed,id_secondary_gear,id_added,id_temp_added) "
    "SELECT @par,@id_activity,MainGearType,1,11,11,SecondaryGearType,@added,5 from Reg_Vessels WHERE VesselID=@par "
    );

}

static QString rebuildIndexesSql()
{
    return
        "EXEC sp_MSforeachtable @command1=\"print '?' DBCC DBREINDEX ('?', ' ', 80)\""
        ;
}

static bool grabDateById(const int inId, QDateTime& outDate)
{
    //! Grab date by id
    /*!
    This is an utility function that receives a ID on table GL_Dates and returns a local date.
    \param inId id on table GL_Dates
    \param outDate address of QDateTime to store the results
    \return boolean stating as success or failure
    */

     QSqlQueryModel model;
     model.setQuery("SELECT Date_Local from GL_Dates WHERE ID=" + QVariant(inId).toString());

     if (model.rowCount()!=1) return false;
     outDate=model.record(0).value("Date_Local").toDateTime();

     return true;
}

static bool onCheckDependantDates(const QMap<QString,sTable>& mapTables, const QString curTable, const QDateTime& curStartDt, const QDateTime& curEndDt
                                   ,QString strTable, int id, QString& strError)
{
    //! On Check Dependant dates
    /*!
    This function goes trough the table sequence and searches if the new dates invalidate time intervals on previously inserted records.
    This is a recurrent function that searches for the first table dependant of the current one, that has date records; the following ones will *always* be contained in this interval.
    \param mapTables map with table names and sTable objects with relevant information
    \param curTable name of the starting table
    \param curStartDt new start date
    \param curEndDt new end date
    \param strTable name of the table that is being tested right now
    \param id id of the parent (to filter the table)
    \param strError string to store the error
    \return boolean stating if the change is validated or not
    */

    QMap<QString,sTable>::const_iterator it=mapTables.find(strTable);
    if (it==mapTables.end()){
        strError=QObject::tr("Could not find this table on the database!");
        return false;
    }

    if (strTable.compare(curTable)==0){
        //it does not have anything after! (last table with dates)
        if (it.value().m_next.compare(qApp->translate("null_replacements", strNa))==0) return true;
        return onCheckDependantDates(mapTables,curTable,curStartDt,curEndDt,it.value().m_next,id,strError);
    }else{

         QSqlQueryModel model;
         model.setQuery("SELECT * FROM " + strTable + " WHERE " + it.value().m_refField + "="
             + QVariant(id).toString());

     //if it does not have dates, keep going with a filter till it finds it...
     if (!it.value().m_bHasDates){

         for (int i=0; i < model.rowCount(); ++i)
         {
            if (!onCheckDependantDates(mapTables,curTable,
                curStartDt,curEndDt,it.value().m_next,model.record(i).value("ID").toInt(),strError))
                return false;
         }

     }else{

         QDateTime startDate, endDate;

         for (int i=0; i < model.rowCount(); ++i)
         {

             if (!grabDateById(model.record(i).value("id_start_dt").toInt(),startDate) ||
                 !grabDateById(model.record(i).value("id_end_dt").toInt(),endDate))
             {
                 strError=QObject::tr("Could not retrieve start/end date from table ") + strTable;
                return false;
             }

             //n.b.: use .toTime_t() for comparison of uints!
            if ( curStartDt.toTime_t() > startDate.toTime_t() || curEndDt.toTime_t() < endDate.toTime_t())
            {
                 strError=startDate > curStartDt?
                     QObject::tr("This start date invalidates the time interval on table ") + strTable:
                  QObject::tr("This end date invalidates the time interval on table ") + strTable;
                 return false;
            }
         }
         //everything went ok: it validates the dates!
        return true;
     }

     }

     return true;
}

static bool getIDfromLastInsertedTable(const QString strTable, QVariant& outID,QString& strError)
{
    QSqlQuery query;
    query.prepare("select top(1) ID from " + strTable + " order by ID Desc");
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() < 1){
         if (query.lastError().type() != QSqlError::NoError)
             strError=query.lastError().text();
         else
            strError=QObject::tr("Could not retrieve last inserted id from ") + strTable + QObject::tr("!");
         return false;
        }
     query.first();
     outID=query.value(0);
     return true;
}

static bool getIDfromLastInsertedDate(QVariant& outID,QString& strError)
{
    return getIDfromLastInsertedTable("GL_DATES",outID, strError);
}

static bool getNADate(QVariant& outID,QString& strError)
{
    QSqlQuery query;
    query.prepare("select ID from GL_DATES WHERE (Date_Type=(SELECT ID from Ref_DateTime_Type WHERE Name='n/a'))");
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() < 1){
         if (query.lastError().type() != QSqlError::NoError)
             strError=query.lastError().text();
         else
            strError=QObject::tr("Could not retrieve n/a date!");
         return false;
        }
     query.first();
     outID=query.value(0);
     return true;
}

static bool getLastUpdate(int& outID)
{
    QString strError;
    QSqlQuery query;
    query.prepare("SELECT     TOP (1) log_ID FROM         dbo.Info_Patch ORDER BY ID DESC");
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() < 1){
         if (query.lastError().type() != QSqlError::NoError)
             strError=query.lastError().text();
         else
            strError=QObject::tr("Could not retrieve ID from last update!");
         return false;
        }
     query.first();
     outID=query.value(0).toInt();
     return true;
}

static bool insertLastUpdate()
{
    QString strError;
    QSqlQuery query;
    query.prepare("insert into info_patch(log_id) select TOP(1) ID from info_changes order by ID DESC");
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() < 1){
         if (query.lastError().type() != QSqlError::NoError)
             strError=query.lastError().text();
         else
            strError=QObject::tr("Could not insert ID from last update!");
         return false;
        }
     return true;
}


static bool getLastSessionData(QSqlQuery& query){

    QString strError, strQuery=
    "SELECT     TOP (1) dbo.GL_Dates.Date_UTC, dbo.GL_Dates.Date_Local, dbo.GL_Dates.Date_Type, dbo.Ref_Location.City_Name, dbo.GL_Session.ID, dbo.GL_Session.mac_address, dbo.UI_User.username"
    " FROM         dbo.GL_Session INNER JOIN"
    "                      dbo.GL_Dates ON dbo.GL_Session.id_base_date = dbo.GL_Dates.ID INNER JOIN"
    "                      dbo.Ref_Location ON dbo.GL_Session.id_location = dbo.Ref_Location.ID INNER JOIN"
    "                      dbo.UI_USER ON dbo.GL_Session.id_user = dbo.UI_USER.ID"
    " ORDER BY dbo.GL_Session.ID DESC";

    query.prepare(strQuery);

    query.setForwardOnly(true);
    if (!query.exec()){
         if (query.lastError().type() != QSqlError::NoError)
             qDebug() << query.lastError().text() << endl;
         else
             qDebug() << QObject::tr("Could not retrieve data from current session!") << endl;
         return false;
     }

return true;
}

static bool isDateTime(const QString strTable, const QString strField, bool& bIsDateTime)
{
     bIsDateTime=false;

    QString strQuery=
    "select count(*)"
    " from sys.foreign_key_columns as fk"
    " inner join sys.tables as t on fk.parent_object_id = t.object_id"
    " inner join sys.columns as c on fk.parent_object_id = c.object_id and fk.parent_column_id = c.column_id"
    " where fk.referenced_object_id = (select object_id from sys.tables where name = 'GL_Dates')"
    " and t.name=:table and c.name=:field";

    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(":table",strTable);
    query.bindValue(":field",strField);
    query.setForwardOnly(true);
    if (!query.exec()){
         if (query.lastError().type() != QSqlError::NoError)
             qDebug() << query.lastError().text() << endl;
         else
             qDebug() <<  "Could not determine if this field is datetime!!" << endl;

         return false;
    }else {
        query.first();
        if (query.value(0).toInt()==1){
            bIsDateTime=true;
        }
    }
    return true;
}

static bool serializeDateTime(const QVariantMap nestedMap, QString& strDateUTC, QString& strDateLocal, int& dateType)
{
    QVariantMap nestedDate2=nestedMap["date"].toMap();
    strDateUTC=nestedDate2["date_utc"].toString();
    strDateLocal=nestedDate2["date_local"].toString();
    dateType=nestedDate2["date_type"].toInt();

    return true;
}

static bool deserializeDateTime(const int id, QVariantMap & nestedMap)
{
   QVariantMap nestedMap2;

   QSqlQuery query;
   QString strQuery=
    "SELECT  "
    "      [Date_UTC]"
    "      ,[Date_Local]"
    "      ,[Date_Type]"
    "  FROM [GL_Dates] where ID =:id";

    query.prepare(strQuery);
    query.bindValue(":id",id);
    query.setForwardOnly(true);
     if (!query.exec() || query.numRowsAffected() < 1){
         if (query.lastError().type() != QSqlError::NoError)
             qDebug() << query.lastError().text() << endl;
         else
             qDebug() << QObject::tr("Could not retrieve date details!") << endl;
         return false;
        }

    query.first();
    nestedMap2["date_utc"]=query.value(query.record().indexOf("Date_UTC")).toString();
    nestedMap2["date_local"]=query.value(query.record().indexOf("Date_Local")).toString();
    nestedMap2["date_type"]=query.value(query.record().indexOf("Date_Type")).toInt();

    nestedMap["date"]=nestedMap2;
    return true;
}

static bool buildJSONCell(const QSqlQuery& query, QVariantMap& nestedMap)
{
    QVariantMap nestedMap2;

    nestedMap["id"]=query.value(query.record().indexOf("id")).toString();
    nestedMap["table"]=query.value(query.record().indexOf("table")).toString();
    nestedMap["column"]=query.value(query.record().indexOf("column")).toString();

    QString strField=query.value(query.record().indexOf("column")).toString();
    strField=strField.remove("[");
    strField=strField.remove("]");

    bool bIsDateTime;
    if (!isDateTime(query.value(query.record().indexOf("table")).toString(),
        strField,bIsDateTime)) return false;

    nestedMap2["from"]=query.value(query.record().indexOf("from")).toString();
    nestedMap2["to"]=query.value(query.record().indexOf("to")).toString();

    if (bIsDateTime){
        if (query.value(query.record().indexOf("from")).toString().compare(
            strNoValue)!=0){

            QVariantMap nestedMap3;
            if (!deserializeDateTime(query.value(query.record().indexOf("from")).toInt(),
                nestedMap3)) return false;
            nestedMap2["from"]=nestedMap3;
        }

        if (query.value(query.record().indexOf("to")).toString().compare(
            strNoValue)!=0){
            QVariantMap nestedMap3;
            if (!deserializeDateTime(query.value(query.record().indexOf("to")).toInt(),
                nestedMap3)) return false;
            nestedMap2["to"]=nestedMap3;
        }

    }
    nestedMap["values"]=nestedMap2;

    return true;
}
//! Is Master
/*! This function checks if the current database is master. The check consists in verifying the existence of the master table.
\par the address of a boolean variable to write the results
\return boolean has success or faillure
*/
static bool isMaster(bool& bIsMaster)
{
    bIsMaster= QSqlDatabase::database().tables().indexOf(strMasterTable)!=-1;
    return true;
}

static bool getLastChanges(const int ID, QString& strJSON, QString& strError)
{
    //QString strError;
    QSqlQuery query;

    QString strQuery=
    "SELECT     *"
    " FROM [info_changes] WHERE ID > :id ORDER BY ID ASC";

    query.prepare(strQuery);
    query.bindValue(":id",ID);
    query.setForwardOnly(true);
     if (!query.exec()){
         if (query.lastError().type() != QSqlError::NoError)
             strError=query.lastError().text();
         else
             strError=QObject::tr("Could not retrieve last changes!");
         return false;
        }
     else if (query.numRowsAffected() < 1){
         strError=QObject::tr("There are no changes to export!");
         return false;
     }

    QVariantMap map, nestedMap, nestedMap2, nestedMap3;
    QList<QVariant> mapList;
    query.first();

    if (!buildJSONCell(query,nestedMap)){
        qDebug() << QObject::tr("Could not read info change row!");
        return false;
    }
    mapList.push_back(nestedMap);

     while (query.next()) {
        if (!buildJSONCell(query,nestedMap)){
            qDebug() << QObject::tr("Could not read info change row!");
            return false;
        }
        mapList.push_back(nestedMap);
     }

     //Let's reuse this query
     if (query.isActive()) query.finish();
    if (!getLastSessionData(query))
        return false;

    query.first();

    if (query.record().indexOf("date_utc")==-1 ||query.record().indexOf("date_local")==-1
        || query.record().indexOf("date_type")==-1 || query.record().indexOf("city_name")==-1)
            return false;

    nestedMap3["date_utc"]=query.value(query.record().indexOf("date_utc")).toString();
    nestedMap3["date_local"]=query.value(query.record().indexOf("date_local")).toString();
    nestedMap3["date_type"]=query.value(query.record().indexOf("date_type")).toString();

    nestedMap2["base_date"]=nestedMap3;
    nestedMap2["city_name"]=query.value(query.record().indexOf("city_name")).toString();
    //TODO: replace database name by mac address
    //nestedMap2["mac_address"]=query.value(query.record().indexOf("mac_address")).toString();
    nestedMap2["mac_address"]=QSqlDatabase::database().databaseName();
    nestedMap2["user"]=query.value(query.record().indexOf("username")).toString();
    map["session"]=nestedMap2;
    map["change"]=mapList;

    bool bIsMaster;
    if (!isMaster(bIsMaster)){
        qDebug() << QObject::tr("Could not search for master information! Database may be corrupted!")
            << endl;
        return false;
    }
    map["mode"]=bIsMaster?strMasterName:strClientName;

    QByteArray data = Json::serialize(map);
    strJSON=QString::fromUtf8(data.constData());

     return true;
}

static bool insertRecordIntoModel(QSqlTableModel* m)
{
    while(m->canFetchMore())
        m->fetchMore();

    return m->insertRow(m->rowCount());
}

static QString getMacAddress()
{
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(interface.flags() & QNetworkInterface::IsLoopBack))
            return interface.hardwareAddress();
    }
    return QString();
}

static bool insertBaseDate()
{
    QSqlQuery query1;
    query1.prepare("exec Insert_Base_Date");
    query1.setForwardOnly(true);
    query1.exec();
    if (query1.lastError().type()!=QSqlError::NoError){
     QMessageBox::critical(0, QObject::tr("Database Error"), query1.lastError().text());
    return false;
    }
    return true;
}

    //! Start Session
    /*! This function initializes session data in the database, by creating a record on table GL_Dates.
    This record is completed, at the end of the session (with end date).
    \par strUser username as string
    \par strLocation location as string
    \return boolean as success or failure
    \sa endSession()
                */
static bool startSession(const QString strUser, const QString strLocation,
                         const QString strMacAddress, const QVariant basedateID, const QString strComment)
{
    QVariant startdateID;

     //location
     QSqlQuery query2;
     query2.prepare("SELECT ID FROM Ref_Location WHERE (City_Name=:location)");
     query2.bindValue(":location", strLocation);
     query2.setForwardOnly(true);
     query2.exec();
     if (query2.lastError().type()!=QSqlError::NoError){
        QMessageBox::critical(0, QObject::tr("Database Error"), query2.lastError().text());
        return false;
     }
     query2.first();
     QVariant locationID=query2.value(0);

     //start date
     QSqlQuery query3;
     query3.prepare("exec InsertCurrentDateTime");
     query3.setForwardOnly(true);
     query3.exec();
     if (query3.lastError().type()!=QSqlError::NoError){
        QMessageBox::critical(0, QObject::tr("Database Error"), query3.lastError().text());
        return false;
     }

     QString strError;
     if (!getIDfromLastInsertedDate(startdateID,strError)){
        QMessageBox::critical(0, QObject::tr("Database Error"), strError);
        return false;
     }

     //end date (for now "n/a": ammend in the end!)
     QVariant enddateID;
     if (!getNADate(enddateID,strError)){
        QMessageBox::critical(0, QObject::tr("Database Error"), strError);
        return false;
     }

     //user
     QSqlQuery query4;
     query4.prepare("SELECT ID FROM UI_USER WHERE (username=:username)");
     query4.bindValue(":username", strUser);
     query4.setForwardOnly(true);
     query4.exec();
     if (query4.lastError().type()!=QSqlError::NoError){
        QMessageBox::critical(0, QObject::tr("Database Error"), query4.lastError().text());
        return false;
     }
     query4.first();
     QVariant userID=query4.value(0);

    QSqlTableModel* table= new QSqlTableModel;
    table->setTable(QSqlDatabase().driver()->escapeIdentifier("GL_SESSION",
    QSqlDriver::TableName));
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table->sort(0,Qt::AscendingOrder);
    table->select();

    if (!insertRecordIntoModel(table)){
        QMessageBox::critical(0, QObject::tr("Database Error"), 
            QObject::tr("Could not insert record into GL_Sessions table!"));
        return false;
    }

    QModelIndex idx=table->index(table->rowCount()-1,1);
    table->setData(idx,userID);
    idx=table->index(table->rowCount()-1,2);
    table->setData(idx,strMacAddress/*getMacAddress()*/);
    idx=table->index(table->rowCount()-1,3);
    table->setData(idx,basedateID);
    idx=table->index(table->rowCount()-1,4);
    table->setData(idx,locationID);
    idx=table->index(table->rowCount()-1,5);
    table->setData(idx,startdateID);
    idx=table->index(table->rowCount()-1,6);
    table->setData(idx,enddateID);
    idx=table->index(table->rowCount()-1,7);
    //table->setData(idx,QObject::tr("This is an automated generated session record: pls do not attempt to edit it!"));
    table->setData(idx,strComment);

    if (!table->submitAll()){
        QMessageBox::critical(0, QObject::tr("Session Error"), 
            QObject::tr("Could not insert record into GL_Sessions table!"));
        delete table;
        return false;
    }

    delete table;
    return true;
}

//! End Session
/*! This function completes the session data in the database, by amending a record on table GL_Dates.
This record was initialized with startSession(const QString strUser, const QString strLocation).
\sa startSession(const QString strUser, const QString strLocation)
*/
static void endSession()
{
    QSqlTableModel* table= new QSqlTableModel();
    table->setTable(QSqlDatabase().driver()->escapeIdentifier("GL_SESSION",
    QSqlDriver::TableName));
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table->sort(0,Qt::AscendingOrder);
    table->select();

     //end date
     QSqlQuery query;
     query.prepare("exec InsertCurrentDateTime");
     query.exec();
     if (query.lastError().type()!=QSqlError::NoError){
        qDebug() << query.lastError().text() << endl;
     }

    QVariant enddateID;
     QString strError;
     if (!getIDfromLastInsertedDate(enddateID,strError)){
        qDebug() << strError << endl;
     }

    QModelIndex idx=table->index(table->rowCount()-1,6);
    table->setData(idx,enddateID);

    if (!table->submitAll()){
        qDebug() << QObject::tr("Could not submit record into GL_Sessions table!") << endl;
    }

    delete table;
}

#endif

