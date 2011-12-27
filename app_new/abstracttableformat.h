#ifndef AbstractTableFormat_H
#define AbstractTableFormat_H

#include <QtSql>
#include "abstractformat.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! AbstractTableFormat Class
/*!
This class contains a table object from the database, that we can import/export in various formats.
*/

class AbstractTableFormat : public QSqlTableModel, public AbstractFormat
{
    Q_OBJECT

    public:
            //! An enum for export/import formats
            /*! Formats supported so far: XML and Script (plain text)
            */
            enum Format { TA, /*!< Enum value for MS Table Adapter Format. */
                          SCRIPT, /*!< Enum value for script format(SQL Server Script). */
            };

        AbstractTableFormat(QObject * parent = 0, QSqlDatabase db = QSqlDatabase(),
            const QString inName=0, const QString inExtension=0, const QString inDescription=0);

        ~AbstractTableFormat();

        //! Get Temporary Path
        /*!
        This function retrieves the path used to store the dump files (backups)
         \return temporaty path as string
        */
        QString                   getDumpFilesPath(){return m_strDumpFilesPath;}
        //! Set Type
        /*!
        This function sets the type of export/import (data or definition), switching a flag as a member variable.
        N.b.: We must set this before exporting!
         \param boolean true for table contents and false for table definition (fields)
         \sa setTable(QString strTable), exportNow()
        */
        void                    setType(bool bData){m_bType=bData;}//!< bData=true, means table contents; bData=false means field definition
        //! Set Table
        /*!
        This function specifies the table that we want to export/import; later we can add support for multiple tables
        or the entire database.
        N.b.: We must set this before exporting!
         \param string table name
         \sa setType(bool bData), exportNow()
        */
        void                    setTables(QStringList strTables){m_strTables=strTables;}//<! set table(s) to export
        void                    setCreateTables(const bool bCreate){m_bCreateTables=bCreate;}
        void                    setEraseData(const bool bErase){m_bEraseData=bErase;}
        void                    setValidation(const bool bValidate){m_bValidate=bValidate;}
        void                    setBackup(const bool bBackup){m_bBackup=bBackup;}
        void                    setVerifyTables(const bool bVerify){m_bVerify=bVerify;}

        //! Read Table Names
        /*!
        This function parses the XML file and gives back a list of table names;
         \param tableList StringList address, to fill with table names
         \return boolean as success or failure
        */
        virtual bool            readTableNames(QStringList& tableList)=0;
        virtual bool            initializeSet(const QStringList tableList, QXmlStreamReader& xml, MapKeys& mapKeys)=0;

    signals:
        void                    showStatus(QString str);
        void                    showError(QString str, const bool bShowMsgBox=true);
        void                    rollbackImport();

    protected:
        bool                    m_bType;// Data or Field definition?
        QString                 m_strFileName;
        QStringList             m_strTables;
        QStringList             m_strTmpTables;
        QString                 m_strDumpFilesPath;
        bool                    m_bCreateTables;
        bool                    m_bEraseData;
        bool                    m_bValidate;
        bool                    m_bBackup;
        bool                    m_bVerify;
        QStringList             m_NullReplacements;

    private:
};
#endif // AbstractTableFormat_H
/////////////////////////////////////////
#ifndef TABLEFACTORY_H
#define TABLEFACTORY_H

class TableFactory {
    public:
        TableFactory(){}
        AbstractTableFormat*    GetTable(AbstractTableFormat::Format format);
};

#endif // TABLEFACTORY_H
