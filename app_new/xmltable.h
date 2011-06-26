#ifndef XMLTABLE_H
#define XMLTABLE_H

#include <QtXmlPatterns>
#include <QtXml>
#include <QFileDialog>
#include <QtSql>
#include "AbstractTableFormat.h"
#include "sql.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

static const char *OLDCODE = QT_TRANSLATE_NOOP("db", "OLD_CODE");
static const char *TMPFKCOL = QT_TRANSLATE_NOOP("db", "FK_TMP");
static const char *NA = QT_TRANSLATE_NOOP("db", "n/a");


//! XML Table Class
/*!
This class contains an instantiation of the AbstractTableFormat class, for XML format
*/

class XmlTable : public AbstractTableFormat
{
    Q_OBJECT

    public:
        XmlTable(QObject * parent = 0, QSqlDatabase db = QSqlDatabase(), const QString inDescription=
            tr("Extensible Markup Language"));
        ~XmlTable();
        //! Exports the table object into XML
            /*!
            Reimplementation of the function on the base class
              \sa import(const Format format=XML, bool bData=true);
            */
        bool                            exportNow();
        bool                            importNow();

        //! Set FileName
        /*!
        This is the implementation of the pure virtual function on the base class.
        N.b.: We must set this before exporting!
         \param strFileName A file name
         \sa setExportFormat(QString strFormat), setEditor(QTextEdit* editor)
        */
        void                            setFileName(QString strFileName);

    protected:
        virtual bool                    dumpSchema(QXmlStreamReader& reader, QXmlStreamWriter& writer)=0;
        virtual bool                    exportSchema(const QStringList strTables, QXmlStreamWriter& xml)=0;
        virtual bool                    addVendorFiles(const QString strPath, QStringList& strFiles)=0;
        virtual QMap<QString,QString>   getVendorSchemasMap()=0;
        virtual bool                    readTableXML(const QString strTable, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames)=0;
        virtual bool                    getFieldTypeXML(QXmlStreamReader& xml, QString& strType, int& size, bool bSeparateSize=false)=0;
        virtual bool                    createTablesFromXml(const QStringList strTables, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames)=0;
        virtual bool                    insertDataFromXml(const QString strTableName, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bAppendNullReplacement=false)=0;
        virtual bool                    loopThroughXMLFK(const QStringList strTables, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bCreateKeys)=0;
        //! Read Table Names
        /*!
        This is the function which actually does the reading (polymorfically)!
         \param QXmlStreamReader a xml reader
         \param QStringList a list, to fill with table names
         \return bool as success or failure
        */
        virtual bool                    readTableNames(QXmlStreamReader& xml, QStringList& tableList)=0;
        virtual bool                    verifyTables2Import(QStringList strTables, QXmlStreamReader& xml)=0;
        virtual bool                    verifyTableXML(const QString strTable, QXmlStreamReader& xml)=0;
        bool                            exportData(const QStringList strTables, QXmlStreamWriter& xml);
        bool                            dumpXML(const QString stopToken, QXmlStreamReader& reader, QXmlStreamWriter& writer);
        bool                            readTableNames(QStringList& tableList);
        bool                            readFieldTransformDefs(const QString strTable, const QString strName, QString& strType, bool& bAutoInc, QString& strSeed, QString& strStep, QString& strDefault, bool& bNull, bool& bUnique);
        bool                            isField2Transform(const QString strTable, const QString strField);
        bool                            updateFKReferences(const QString strName, const MapFK& mapKeys, const QMap<QString,QString>& mapTMPNames, bool bTree=false);
        bool                            replaceNullValues(const QString strTable, const QMap<QString, QString>& mapTMPNames);

    private:
        //! Exports data to a designated file
        /*!
        This is a wrapper for exportNow() receiving one filenames as parameter:
        it is provided for convenience, for reuse in other situations.
         \param QString A file name
         \sa exportNow
        */
        bool                            export2File(const QString strFilename, const QStringList strTables);
        bool                            exportTable(const QString strTable, QXmlStreamWriter& xml);
        bool                            validate(const QString strSchema, const QString strInstance, bool bExport=true);
        bool                            createTmpExportFiles(const QString strInstance, const QString strSchema);
        bool                            createTmpImportFiles(const QString strInstance, const QString strSchema);
        bool                            applySchema(const QString strInstance, 
                                        const QString strSchema);
        bool                            eraseData(const QString& strTableName);
        bool                            backupTable(const QString strTableName);

    private slots:
        void                            doRollbackImport();

};
#endif // AbstractTableFormat_H
/////////////////////////////////////////////////////////
 class MessageHandler : public QAbstractMessageHandler
 {
     public:
         MessageHandler()
             : QAbstractMessageHandler(0)
         {
         }

         QString statusMessage() const
         {
             return m_description;
         }

         int line() const
         {
             return m_sourceLocation.line();
         }

         int column() const
         {
             return m_sourceLocation.column();
         }

     protected:
         virtual void handleMessage(QtMsgType type, const QString &description,
                                    const QUrl &identifier, const QSourceLocation &sourceLocation)
         {
             Q_UNUSED(type);
             Q_UNUSED(identifier);

             m_messageType = type;
             m_description = description;
             m_sourceLocation = sourceLocation;
         }

     private:
         QtMsgType m_messageType;
         QString m_description;
         QSourceLocation m_sourceLocation;
 };