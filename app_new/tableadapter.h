#ifndef TABLEADAPTER_H
#define TABLEADAPTER_H

#include <QtXmlPatterns>
#include <QtXml>
#include <QtSql>
#include "xmltable.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! Table Adapter Class
/*!
This class implements an Xml Table, using MS a Schema (Table Adapters).
*/

class TableAdapter : public XmlTable
{
    Q_OBJECT

    public:
        TableAdapter(QObject * parent = 0, QSqlDatabase db = QSqlDatabase());
        ~TableAdapter();

    protected:
        bool                    initializeSet(const QStringList tableList, QXmlStreamReader& xml, MapKeys& mapKeys);
        bool                    createTablesFromXml(const QStringList strTables, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames);
        bool                    readTableXML(const QString strTable, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames);
        bool                    getFieldTypeXML(QXmlStreamReader& xml, QString& strType, int& size, bool bSeparateSize=false);
        bool                    readPKXML(const QString strTable, const QString strName, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames);
        bool                    dumpSchema(QXmlStreamReader& reader, QXmlStreamWriter& writer);
        bool                    exportSchema(const QStringList strTables, QXmlStreamWriter& xml);
        QMap<QString,QString>   getVendorSchemasMap();
        bool                    readTableNames(QXmlStreamReader& xml, QStringList& tableList);
        bool                    insertDataFromXml(const QString strTableName, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bAppendNullReplacement=false);
        bool                    loopThroughXMLFK(const QStringList strTables, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bCreateKeys);
        bool                    verifyTables2Import(QStringList strTables, QXmlStreamReader& xml);
        bool                    verifyTableXML(const QString strTable, QXmlStreamReader& xml);

    private:
        bool                    search4FK(const QStringList strTables, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bCreateKeys);
        bool                    addExtraAttributes(const QString strTable, const QString strField, QXmlStreamWriter& xml);
        QString                 buildSelectorPath(const QString str);
        QString                 buildFieldPath(const QString str);
        bool                    exportPK(const QSqlRecord rec, const QString strTable, const QStringList fieldList, QXmlStreamWriter& xml);
        bool                    exportFK(const QSqlRecord rec, QXmlStreamWriter& xml);
        void                    initTypeMapping();
        bool                    validate(QString strFileName);
        bool                    addVendorFiles(const QString strPath, QStringList& strFiles);
        bool                    exportFieldDefs(const QString strTable, QXmlStreamWriter& xml);
        bool                    insertDataIntoTable(const QString strTableName, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bAppendNullReplacement=false);
        QMap<QString,QString>   m_mapQt2Xs;//<! Map QT types to Schema types
        QMap<QString,QString>   m_mapXs2Sql;//<! Map Schema types to SQL

};
#endif // TABLEADAPTER_H
