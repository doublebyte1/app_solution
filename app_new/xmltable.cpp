#include "xmltable.h"

static const char *TIMESTAMP = QT_TRANSLATE_NOOP("TimeDefaultFormat", "yyyyMMddhhmmss");

XmlTable::XmlTable(QObject * parent, QSqlDatabase db, const QString inDescription):
AbstractTableFormat(parent, db, tr("XML"),tr("xml"),inDescription)
{
    connect(this, SIGNAL(rollbackImport()), this,
    SLOT(doRollbackImport()));

    if (!getNullReplacements(m_NullReplacements))
        emit showError(tr("Could not retrieve from the database, the authorized values for null replacements!"));
}

XmlTable::~XmlTable()
{

}

bool XmlTable::replaceNullValues(const QString strTable, const QMap<QString,QString>& mapTMPNames)
{
    QString strImportedName;
    bool bExists;
    if (!getImportedName(strTable,strImportedName,bExists)) return false;

    QString strTMPname;
    if (!getMappedTMPName(strImportedName,mapTMPNames,strTMPname)){
        emit showError(tr("Could not obtain a mapped temporary name for this table!"));
        return false;
    }

    QHash<QString,QString> nullValues;
    if (!findNullReplacementFields(strImportedName,nullValues)) return false;

    if (nullValues.size()< 1) return true;

    QHash<QString,QString>::iterator i;
    for (i = nullValues.begin(); i != nullValues.end(); ++i){

        QHash<QString,QString> mapFieldValue;
        mapFieldValue.insert(tr("field_name"), i.key());
        QSqlRecord rec;
        if (!selectValue(tr("reviewed_type"), tr("CAS_Fields"),mapFieldValue,rec))
            return false;
        QString strNullRep, strSql;
        if (!getNullForType(rec.value(0).toString(), tr("missing"), strNullRep)) return false;

        if (!fixQueryValue(rec.value(0).toString(),i.value())) return false;
        if (!fixQueryValue(rec.value(0).toString(),strNullRep)) return false;

        strSql.append(tr("UPDATE ") + strTMPname + tr(" SET ") + i.key() + 
            tr("=") + strNullRep + tr(" WHERE ") + i.key() + tr("=") + i.value());

        QSqlQuery query;
        if (!query.prepare(strSql)) return false;
        if (!query.exec()) return false;
    }

    return true;
}

bool XmlTable::readTableNames(QStringList& tableList)
{
    QFile file(m_strFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return false;

    //Just try to parse the xml
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source = new QXmlInputSource(&file);
    if (!xmlReader.parse(source)) {file.close(); return false;}//exit, but close the file first!
    delete source;

    file.close();

     //Initialize the reader
    if (!file.open(QFile::ReadOnly | QFile::Text)) return false;
    QXmlStreamReader xml(&file);

    if (!readTableNames(xml, tableList)) return false;

    file.close();
    return true;
}

bool XmlTable::backupTable(const QString strTableName)
{
     //TODO: In the future we may want to configure the path of the dump files
     m_strDumpFilesPath=QDir::tempPath();

    QDateTime now = QDateTime::currentDateTime();
    QString strTimeStamp=now.toString(qApp->translate("TimeDefaultFormat", TIMESTAMP));

     QStringList table;
     table.push_back(strTableName);
     //2- Backup the data we want to change
    if (!export2File( m_strDumpFilesPath + tr("/")
     + strTableName + strTimeStamp + tr(".xml"),table))
         return false;

    return true;
}

void XmlTable::doRollbackImport()
{
    //! Slot triggered When we failed an import operation
    /*!
    Here we want to remove every single temporary table that we have created
    */
    if (m_strTmpTables.size()<1)
        emit showError(tr("Could not find references to remove temporary tables!"));

     QStringList::const_iterator constIterator;
     for (constIterator = m_strTmpTables.constBegin(); constIterator != m_strTmpTables.constEnd();
         ++constIterator){
         if (!dropTableIfExists(*constIterator)) emit showError(tr("Could not remove temporary table ") + (*constIterator));
     }
}

bool XmlTable::importNow()
{
    QFile file(m_strFileName);

    //1- Validate
    QString strTmpFile=QDir::tempPath()+tr("/ReferenceExportDataSet"),
    strSchema=strTmpFile+tr(".xsd"),strInstance=strTmpFile+tr(".xml");

    if (m_bValidate)
        if (!validate(strSchema,strInstance,false)) return false;

    //2 - Check if table exists and we don't want to create it!
    //3 - create a Map with TMP authorized names!!!

    m_strTmpTables.clear();//store here, to delete just in case something goes wrong

    QMap<QString,QString> mapTMPNames;
     QStringList::const_iterator constIterator;
     for (constIterator = m_strTables.constBegin(); constIterator != m_strTables.constEnd();
            ++constIterator)
     {
        bool bNoTable=false;
        QSqlQuery query;
        QString strImportedName;
        bool bExists;
        if (!getImportedName(*constIterator,strImportedName,bExists)) return false;
        if (!getObjects(query,strImportedName)) return false;
        if (query.numRowsAffected()<1) bNoTable=true;

        if (bNoTable && !m_bCreateTables){// Table does not exist and we don't want to create it
            emit showError(tr("This table does not exist on the database: we must create it, first!"));
            return false;
        }

        QString strTMPname;
        if (!generateTMPTableName(strImportedName,strTMPname,true)) return false;
        mapTMPNames.insert(strImportedName,strTMPname);
        m_strTmpTables << strTMPname;
     }

    //Initialize the reader
    if (!file.open(QFile::ReadOnly | QFile::Text)) return false;
    QXmlStreamReader xml(&file);

     //Enforce table structure policies, according to what is expressed in [CAS_Fields] table
     if (m_bVerify){
        verifyTables2Import(m_strTables,xml);
        //Don't forget to reset the xml reader
        file.close();
        if (!file.open(QFile::ReadOnly | QFile::Text)) return false;
        xml.setDevice(&file);
     }

     //create TMP table(s) in a bulk
    if (!createTablesFromXml(m_strTables,xml,mapTMPNames)) return false;

     //Loop to append data
     for (constIterator = m_strTables.constBegin(); constIterator != m_strTables.constEnd();
            ++constIterator)
     {
        //Don't forget to reset the xml reader
        file.close();
        if (!file.open(QFile::ReadOnly | QFile::Text)) return false;
        xml.setDevice(&file);

        //Check if we need to add a 'n/a' record in the end of the table
        bool bAppendNull=false;
        QHash<QString,QString> mapFieldValue;
        mapFieldValue.insert(tr("original_name"), *constIterator);
        QSqlRecord rec;
        if (!selectValue(tr("appendNullFields"), tr("CAS_Tables_Import"),mapFieldValue,rec))
            bAppendNull=false;//if it is an unkown table, we don't append the extra record
        else
            bAppendNull=rec.value(0).toBool();

        if (!insertDataFromXml(*constIterator,xml,mapTMPNames,bAppendNull)) return false;
     }

     //At this time, just update the FK references (TMP table)
    //Don't forget to reset the xml reader
     file.close();
    if (!file.open(QFile::ReadOnly | QFile::Text)) return false;
     xml.setDevice(&file);
    if (!loopThroughXMLFK(m_strTables,xml,mapTMPNames,false)) return false;

     for (constIterator = m_strTables.constBegin(); constIterator != m_strTables.constEnd();
            ++constIterator)
     {
        QString strImportedName,strTMPname;
        bool bExists;
        if (!getImportedName(*constIterator,strImportedName,bExists)) return false;
        if (!getMappedTMPName(strImportedName,mapTMPNames,strTMPname)) return false;

        //Now backup
        if (m_bBackup){
            if (!backupTable(strImportedName)) return false;
        }

        MapFK mapFK;
        if (m_bCreateTables || m_bEraseData){
            if (!storeFKConstraints(strImportedName,false,mapFK)) return false;//We must store existing FK referencing this table, since we are going to remove them!
            if (!dropFKConstraints(strImportedName,false)) return false;
        }

        if (!m_bCreateTables && m_bEraseData){
            if (!eraseData(strImportedName)) return false;
        }

        if (m_bCreateTables){
            if (!dropTableIfExists(strImportedName)) return false;
            if (!renameTable(strTMPname,strImportedName)) return false;
        }
        else{
            if (!copyTable(strTMPname,strImportedName,true)) return false;
            if (!dropTableIfExists(strTMPname)) return false;
        }

        if (m_bCreateTables || m_bEraseData)//Put FK back...
        if (!createFKConstraint(mapFK)) return false;
     }

    if (m_bCreateTables || m_bEraseData){
         //Now actually create the keys (actual table)
         file.close();
        if (!file.open(QFile::ReadOnly | QFile::Text)) return false;
         xml.setDevice(&file);
        if (!loopThroughXMLFK(m_strTables,xml,mapTMPNames,true)) return false;
    }

    if (file.isOpen()) file.close();
    return true;
}

bool XmlTable::isField2Transform(const QString strTable, const QString strField)
{
    QSqlQuery query;
    if (!getFieldDescriptionFromDB(strTable,strField,query)) return false;

    return true;
}

bool XmlTable::readFieldTransformDefs(const QString strTable, const QString strName, QString& strType, bool& bAutoInc, QString& strSeed, QString& strStep, QString& strDefault, bool& bNull, bool& bUnique)
{
    bNull=false;//n.b.: All fields in the database are non nullable!!!!

    QSqlQuery query;
    if (!getFieldDescriptionFromDB(strTable,strName,query)) return false;
    query.first();

    QSqlRecord rec=query.record();
    strType=rec.value(tr("reviewed_type")).toString();
    //Fors strings, grabb the size!
    if (strType==tr("nvarchar")||strType==tr("varchar")||strType==tr("char") || strType==tr("nchar")){
        strType.append(tr("("));
        QString strLength=rec.value(tr("reviewed_size")).toString();
        QString amLength;
        if (!fixStringMaximumLength(strLength,amLength,true,false)) return false;
        strType.append(amLength);
        strType.append(tr(")"));
    //For decimals, grabb (p,s)
    }else if (strType==tr("decimal")){
        QString strScale=rec.value(tr("reviewed_size")).toString();
        strType.append(tr("(18,") + strScale + tr(")"));//For now we only support the default precision (18) and a variable scale;
    }

    bAutoInc=rec.value(tr("change2AutoIncrement")).toBool();
    //n.b.: autoincremented is *ALWAYS* SET to seed=1, step=1
    strSeed=strStep=tr("1");
    if (rec.value(tr("HasDefaultValue")).toBool()){
        strDefault=rec.value(tr("DefaultValue")).toString();
        strDefault.prepend(tr("'"));
        strDefault.append(tr("'"));
    }
    else
        strDefault=tr("");

    bUnique=rec.value(tr("CreateUniqueCstrt")).toBool();

    return true;
}

bool XmlTable::eraseData(const QString& strTableName)
{
     return clearDBTable(strTableName);
}

bool XmlTable::updateFKReferences(const QString strName, const MapFK& mapKeys, const QMap<QString,QString>& mapTMPNames, bool bTree)
{
    QSqlQuery query;
    QString strQuery, strType;
    QString strOldCode=qApp->translate("db", OLDCODE);
    QString strTmpCol=qApp->translate("db", TMPFKCOL);
    QString strNA=qApp->translate("db", NA);

     MapFK::iterator i = mapKeys.find(strName);
     while (i != mapKeys.end() && i.key() == strName) {
        if (!getFieldDescriptionFromDB(i.value().m_parent,i.value().m_parentkey,query)) return false;
        query.first();
        strType=query.record().value(tr("reviewed_type")).toString();

        if (strType==tr("nvarchar")||strType==tr("varchar")||strType==tr("char") || strType==tr("nchar")){
            strType.append(tr("("));
            QString strLength=query.record().value(tr("reviewed_size")).toString();
            QString amLength;
            if (!fixStringMaximumLength(strLength,amLength,true,false)) return false;
            strType.append(amLength);
            strType.append(tr(")"));
        }

        QString strTMPname;
        if (!getMappedTMPName(i.value().m_child,mapTMPNames,strTMPname)){
            emit showError(tr("Could not obtain a mapped temporary name for this table!"));
            return false;
        }

        //Make the column Nullable
        strQuery=tr("ALTER TABLE ") + strTMPname + tr(" ADD ") + strTmpCol +
            QObject::tr(" ") + strType + tr(" NULL");
         if (!query.prepare(strQuery)) return false;
         if (!query.exec()) return false;

         if (!bTree){
             //Update it from the inner join
             strQuery=tr("UPDATE ") + strTMPname + tr(" SET ") + strTmpCol + tr("=A FROM") + 
                 tr("(SELECT ") + i.value().m_parent + tr(".") + i.value().m_parentkey + tr(" AS A, ") + i.value().m_parent + tr(".") +
                 strOldCode + tr(" FROM ") + strTMPname + tr(" INNER JOIN ") +  i.value().m_parent +
                 tr(" ON ") + strTMPname + tr(".") + i.value().m_childkey + tr("=") + i.value().m_parent + tr(".") + 
                 strOldCode + tr(") AS TH WHERE TH.") + strOldCode + tr("=") + strTMPname + tr(".") + i.value().m_childkey;
         }else{
             //Special query to update Tree references
            strQuery=tr("UPDATE ") + strTMPname + tr(" SET ") + strTmpCol + 
                tr("=( SELECT dbo.Tree.id FROM dbo.Tree INNER JOIN dbo.Node_Description ON dbo.Tree.id = dbo.Node_Description.id WHERE (dbo.Node_Description.") + strOldCode + tr("=") + i.value().m_childkey + tr(") AND (dbo.Tree.depth = (SELECT MAX(depth) AS Expr1 FROM dbo.Tree AS Tree_1)))");
         }
         if (!query.prepare(strQuery))return false;
         if (!query.exec()){
            qDebug() << strQuery << endl;
             return false;
         }

         //if possible, replace the nulls for a meaningful value
        QMap<QString,QString> mapTypes;
        QMap<QString,int> mapSizes;
        if (!getFields(i.value().m_parent,mapTypes,mapSizes)){
            emit showError(tr("Could not get field list for table ") + i.value().m_parent);
            return false;
        }

         bool bMakeNullable=false;
         QVariant var;
         bool bGotName=false;

        QMap<QString,QString>::iterator it;
        for (it = mapTypes.begin(); it != mapTypes.end(); ++it){
            if (it.key().compare(tr("NAME"),Qt::CaseInsensitive)==0){
                bGotName=true;
                break;
            }
        }

        if (bGotName){
             strQuery=tr("SELECT * FROM ") + i.value().m_parent + tr(" WHERE NAME='") + strNA + tr("'");
             if (!query.prepare(strQuery))return false;
             if (!query.exec()){
                qDebug() << strQuery << endl;
                 return false;
             }
             if (query.numRowsAffected()>0){
                 query.first();
                 var=query.record().value(i.value().m_parentkey);
                 strQuery=tr("UPDATE ") + strTMPname + tr(" SET ") + strTmpCol + tr("=(SELECT ") + i.value().m_parentkey
                     + tr(" FROM ") + i.value().m_parent + tr(" WHERE [Name]='") + strNA + tr("') WHERE ") + strTmpCol + tr(" IS NULL");
                 if (!query.prepare(strQuery))return false;
                 if (!query.exec()){
                    qDebug() << strQuery << endl;
                     return false;
                 }
                bMakeNullable=true;
             }
        }//bGotName

         //Check if there are any default constraints to remove!!!
         bool bGotDefault=false;
         strQuery=getDefaultCstrt(strTMPname,i.value().m_childkey);
         if (!query.prepare(strQuery))return false;
         if (!query.exec()){
            qDebug() << strQuery << endl;
             return false;
         }
         QString strCtsrtName;
         if (query.numRowsAffected()==1){
             query.first();
             strCtsrtName=query.record().value(tr("constraint_name")).toString();
             if (!dropConstraint(strCtsrtName,strTMPname)) return false;
            bGotDefault=true;
         }

         //switch temporary column for the real one!
         if (!dropColumn(strTMPname, i.value().m_childkey)) return false;
         if (!renameColumn(strTMPname,strTmpCol,i.value().m_childkey)) return false;

         //Put back the constraints!
         if (bGotDefault/* && bMakeNullable*/){
             strQuery=tr("ALTER TABLE ") + strTMPname + tr(" ADD CONSTRAINT ") + strCtsrtName +
             tr("  DEFAULT ") + var.toString() + tr(" FOR ") + i.value().m_childkey;
             if (!query.prepare(strQuery)) return false;
             if (!query.exec()){
                 qDebug() << strQuery << endl;
                 return false;
             }
         }
         //make the field non-nullable (ALWAYS!)
         if (!nullifyField(strTMPname,i.value().m_childkey,strType,/*!bMakeNullable*/false)){
             emit showError(tr("Could not turn the field non-nullable!"));
             return false;
         }
         ++i;
     }//while multimap


    return true;
}

bool XmlTable::createTmpImportFiles(const QString strInstance, const QString strSchema)
{
    bool bOk=true;

    //General variables of the schema/instance
    QString strUri;
    QFile file(m_strFileName);

    if (file.open(QFile::ReadOnly | QFile::Text)){
        QXmlStreamReader xml(&file);
        xml.readNextStartElement();

        //Initializes the file and the xml writer!
        QFile schemaFile(strSchema);
        if (schemaFile.open(QFile::WriteOnly | QFile::Text)){
            QXmlStreamWriter writer(&schemaFile);
            writer.setAutoFormatting(true);
            writer.setAutoFormattingIndent(3);

            QString strObjName;
            //Read top level element
            if (xml.name()!= tr("schema")){
                strObjName=xml.name().toString();
                bool bGotNS=false, bGotXS=false;
                size_t i=0;
                while ( i < (size_t)xml.namespaceDeclarations().toList().length() ){
                        QString aPrefix=xml.namespaceDeclarations().at(i).prefix().toString();
                        QString aUri=xml.namespaceDeclarations().at(i).namespaceUri().toString();

                        //Default ns declaration
                        if (aPrefix.isEmpty() && !aUri.isEmpty()){
                            writer.writeDefaultNamespace(aUri);
                            strUri=aUri;
                            bGotNS=true;;
                        //schema declaration
                        } else if (aPrefix.compare(tr("xs"))==0 && aUri.compare(
                            qApp->translate("xml", SCHEMA))==0){
                            writer.writeNamespace(aUri,aPrefix);
                            bGotXS=true;
                        }

                        if (bGotNS && bGotXS) break;
                        ++i;

                }
                xml.readNextStartElement();
                if (xml.name()== tr("schema")){//Now read the schema!
                    //First find all the vendor schema references
                    QMap<QString,QString> map=getVendorSchemasMap();
                    int ct=0;
                    size_t i=0;
                    while ( i < (size_t)xml.namespaceDeclarations().toList().length()
                        && ct < map.size()){
                            QString aPrefix=xml.namespaceDeclarations().at(i).prefix().toString();
                            QString aUri=xml.namespaceDeclarations().at(i).namespaceUri().toString();
                            if (map.find(aPrefix)!=map.end())
                                if (map.find(aPrefix).value()==aUri) ct++;
                            ++i;
                    }//while
                    if (ct==map.size())
                    {
                        writer.writeStartDocument();
                            if (!dumpSchema(xml,writer)) bOk=false;
                        writer.writeEndDocument();
                        schemaFile.close();

                        //dump data
                        //Initializes the file and the xml writer!
                        QFile instanceFile(strInstance);
                        if (instanceFile.open(QFile::WriteOnly | QFile::Text)){

                            writer.setDevice(&instanceFile);
                            writer.setAutoFormatting(true);
                            writer.setAutoFormattingIndent(3);
                            writer.writeDefaultNamespace(strUri);
                            writer.writeNamespace(qApp->translate("xml", SCHEMA),tr("xs"));
                            writer.writeStartDocument();
                                writer.writeStartElement(strObjName);
                                    //Dump data
                                    if (!dumpXML(strObjName,xml,writer)) bOk=false;
                                writer.writeEndElement();
                            writer.writeEndDocument();
                            instanceFile.close();

                        }else bOk=false;
                    }
                    else bOk=false;

                }else bOk=false;//Schema *must* be the second element of the DOM!
            }
            else bOk=false;//Schema *cannot* be the first element of the DOM!

            if (xml.hasError()) {
                emit showError(xml.errorString());
                bOk=false;
            }
        }else bOk=false;
    }else bOk=false;

    file.close();

    return bOk;
}

bool XmlTable::dumpXML(const QString stopToken, QXmlStreamReader& reader, QXmlStreamWriter& writer)
{
    while (!reader.atEnd()) {
         reader.readNext();
         if (reader.name().compare(stopToken)==0 && reader.isEndElement())
             break;
         writer.writeCurrentToken(reader);
    }

   if (reader.hasError()) {
         return false;
   }

    return true;
}

bool XmlTable::exportData(const QStringList strTables, QXmlStreamWriter& xml)
{
     QStringList::const_iterator constIterator;
     for (constIterator = strTables.constBegin(); constIterator != strTables.constEnd();
            ++constIterator)
     {
         if (!exportTable(*constIterator,xml)){
             //TODO: emit an error here later? DONT RETURN FALSE as some tables may be empty
             //qDebug() << *constIterator << endl;
         }
     }

    return true;
}

bool XmlTable::export2File(const QString strFilename, const QStringList strTables)
{
    //Initializes the file and the xml writer!
    QFile file(strFilename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) return false;
    QXmlStreamWriter xml(&file);

    xml.setAutoFormatting(true);
    xml.setAutoFormattingIndent(3);

    QFileInfo fi(m_strFileName);

    xml.writeNamespace( tr("http://www.w3.org/2001/XMLSchema"), tr("xs") );
    xml.writeDefaultNamespace(
        qApp->translate("xml", URI) + tr("ReferenceExportDataSet"));

    xml.writeStartDocument();
    xml.writeStartElement(tr("ReferenceExportDataSet"));

        if (!exportSchema(strTables,xml)) return false;
        if (!exportData(strTables,xml)) return false;

    xml.writeEndElement();
    xml.writeEndDocument();

    file.close();
    QStringList fileList;
    QDir dir;
    QString strPath=dir.filePath(fi.path());
    if (!addVendorFiles(strPath,fileList)) return false;

    for (size_t i=0; i <(size_t)fileList.size();++i)
    {
        emit showStatus(tr("Appended Schema: ") + fileList.at(i));
    }

    if (m_bValidate){
        QString strTmpFile=QDir::tempPath()+tr("/ReferenceExportDataSet"),
        strSchema=strTmpFile+tr(".xsd"),strInstance=strTmpFile+tr(".xml");
        return validate(strSchema,strInstance);
        //n.b.: Do not use the validation for now, as the validator does not accept empty elements!
    }
    else return true;
}

bool XmlTable::exportNow()
{
    return export2File(m_strFileName,m_strTables);
}

bool XmlTable::exportTable(const QString strTable, QXmlStreamWriter& xml)
{
    // Do not export *Diagrams*!!
    if (strTable.compare(tr("sysdiagrams"))==0) return false;

     QSqlQueryModel model;
     model.setQuery(tr("SELECT * FROM ") + strTable);
     if (model.rowCount()<1 || model.columnCount()<1) return false;

    if (model.lastError().isValid())
        emit showError(model.lastError().text());

    //N.b.: always do this to force retrieving the column count, as the SQL server driver
    // has a limit of 256 rows!!!!
    while (model.canFetchMore())
    {
        model.fetchMore();
    }

     for (size_t i=0; i < (size_t)model.rowCount(); ++i)
     {
        xml.writeStartElement(strTable);

         for (size_t j=0; j < (size_t)model.columnCount(); ++j){
             if (model.record().fieldName(j).compare(tr("upsize_ts"),Qt::CaseInsensitive)!=0
                 && model.record().fieldName(j).compare(tr("OLD_CODE"),Qt::CaseInsensitive)!=0){
                 QVariant val=model.record(i).value(model.record().fieldName(j));
                 if (val.isValid() && !val.isNull())
                     xml.writeTextElement(model.record().fieldName(j),val.toString());
                 else{
                     xml.writeEmptyElement(model.record().fieldName(j));
                 }
             }
         }

        xml.writeEndElement();
     }

    return true;
}

void XmlTable::setFileName(QString strFileName)
{
    m_strFileName=strFileName;
}

bool XmlTable::applySchema(const QString strInstance, const QString strSchema)
{
    //Check if files exist, just in case...
    if ( !QFile::exists(strSchema) || !QFile::exists(strInstance)) return false;

    bool errorOccurred;
    QXmlSchema schema;
    schema.load( QUrl(strSchema) );

    if ( schema.isValid() ) {

        MessageHandler messageHandler;
        QXmlSchemaValidator validator( schema );
        validator.setMessageHandler(&messageHandler);

        if ( validator.validate( QUrl(strInstance) ) )
            errorOccurred=false;
        else
            errorOccurred=true;

        if (errorOccurred) {
            emit showError(messageHandler.statusMessage());
            return false;
        } else {
            emit showStatus(tr("instance is valid"));
            return true;
        }


    } else {
        //qDebug()<< "schema is invalid" << endl;
        emit showError (tr("schema is invalid"));
        return false;
    }

    return false;
}

bool XmlTable::createTmpExportFiles(const QString strInstance, const QString strSchema)
{
    //Write Schema
    QFile schemaFile(strSchema);
    if (!schemaFile.open(QFile::WriteOnly | QFile::Text)) return false;
    QXmlStreamWriter schemaWriter(&schemaFile);//start writing schema
    schemaWriter.setAutoFormatting(true);
    schemaWriter.setAutoFormattingIndent(3);

    schemaWriter.writeNamespace( SCHEMA, tr("xs") );
    schemaWriter.writeDefaultNamespace(
        qApp->translate("xml", URI) + tr("ReferenceExportDataSet"));

    schemaWriter.writeStartDocument();
        if (!exportSchema(m_strTables,schemaWriter)) return false;
    schemaWriter.writeEndDocument();
    schemaFile.close();

    //Write XML instance
    QFile instanceFile(strInstance);
    if (!instanceFile.open(QFile::WriteOnly | QFile::Text)) return false;
    QXmlStreamWriter instanceWriter(&instanceFile);//start writing instance
    instanceWriter.setAutoFormatting(true);
    instanceWriter.setAutoFormattingIndent(3);

    instanceWriter.writeDefaultNamespace(
        qApp->translate("xml", URI) + tr("ReferenceExportDataSet"));
    instanceWriter.writeNamespace( SCHEMA, tr("xs") );

    instanceWriter.writeStartDocument();
        instanceWriter.writeStartElement(tr("ReferenceExportDataSet"));
        if (!exportData(m_strTables,instanceWriter)) return false;
        instanceWriter.writeEndElement();
    instanceWriter.writeEndDocument();
    instanceFile.close();

    return true;
}

bool XmlTable::validate(const QString strSchema, const QString strInstance, bool bExport)
{
    //! Validate Xml and Schema
        /*!
        This function uses Qt validator API, for validating the instance against the schema.
        Since inline schemas are not supported, we need two generate *two* temporary files!
        \par bool true=export, false=import
        \return bool as success or failure
        */

    //1 - Generate TMP files /////////////////////////////////
    if (bExport){
        if (!createTmpExportFiles(strInstance,strSchema)) return false;
    }else{
        if (!createTmpImportFiles(strInstance,strSchema)) return false;
    }

    //2 - Validate instance against schema/////////////////////////////////
    if (!applySchema(strInstance,strSchema)) return false;

    return true;
    /*QDir dir;
    return (dir.remove(strSchema) && 
      dir.remove(strInstance) );*/
}
