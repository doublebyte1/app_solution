#include "tableadapter.h"
#include "sql.h"

static const char *strMsdata = 
     QT_TRANSLATE_NOOP("xml", "urn:schemas-microsoft-com:xml-msdata");

TableAdapter::TableAdapter(QObject * parent, QSqlDatabase db):
XmlTable(parent, db, tr("XML with MS Schema"))
{
    initTypeMapping();//We don't need to check on this function
}

TableAdapter::~TableAdapter()
{

}

QMap<QString,QString> TableAdapter::getVendorSchemasMap()
{
    QMap<QString,QString> map;
    map.insert(tr("msdata"),strMsdata);

    return map;
}

bool TableAdapter::insertDataFromXml(const QString strTableName, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bAppendNullReplacement)
{
    bool bReadingTables=false;

    while (! xml.isEndDocument() && !xml.hasError()){
        xml.readNextStartElement();
        if (xml.isStartElement() && xml.name().toString().compare(tr("schema"))==0){
            xml.skipCurrentElement();
            bReadingTables=true;
            xml.readNextStartElement();
        }
        if (bReadingTables){
            if (xml.name().toString().compare(strTableName)==0)
                return insertDataIntoTable(strTableName,xml,mapTMPNames,bAppendNullReplacement)
                && replaceNullValues(strTableName,mapTMPNames);
            else
                xml.skipCurrentElement();
        }
    }
     return true;//Maybe the table is empty... do we want to allow this?
}

bool TableAdapter::insertDataIntoTable(const QString strTableName, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bAppendNullReplacement)
{
    //Check if we need to rename this table
    QString strImportedName;
    bool bExists;
    if (!getImportedName(strTableName,strImportedName,bExists)) return false;

    QString strTMPname;
    if (!getMappedTMPName(strImportedName,mapTMPNames,strTMPname)){
        emit showError(tr("Could not obtain a mapped temporary name for this table!"),true);
        return false;
    }

    QString strOldCode=qApp->translate("db", OLDCODE);

    //In case the table has an identity column, we must identify it and exclude it from the inserts!
    QString strIdentity;
    bool bIdentity=false;
    if (!tableHasIdentity(strImportedName,bIdentity)) return false;
    if (bIdentity){
        if (!identityName(strImportedName,strIdentity)) return false;
    }

    //First set this to on, so that we can escape reserved words!
    QSqlQuery query(tr("SET QUOTED_IDENTIFIER ON"));

    QString strQuery, strFields,strValues;//, strId;
    strQuery.append(tr("INSERT INTO ") + strTMPname + tr(" ("));

    //This loop reads the records from the table *only*!!!
    bool bRead=true, bClosed=false;
    while (bRead){
        xml.readNext();
        if (bClosed){
            xml.readNextStartElement();
            if (xml.name().toString()!=strTableName){
                bRead=false;
                break;
            }
        }

        if (xml.isEndElement() && xml.name().toString()==strTableName){

            strFields.remove(strFields.length()-1,1);//remove last comma
            strFields.append(tr(")"));
            strQuery.append(strFields);
            strQuery.append(tr(" VALUES ("));
            strValues.remove(strValues.length()-1,1);//remove last comma
            strValues.append(tr(")"));
            strQuery.append(strValues);

            QSqlQuery query;
            query.prepare(strQuery);
            if (!query.exec()){
                //qDebug() << strQuery << endl;
                emit showError(query.lastError().text(),true);
                return false;
            }

            //clean query strings
            strQuery.clear();
            strQuery.append(tr("INSERT INTO ") + strTMPname + tr(" ("));
            strFields.clear();
            strValues.clear();

            bClosed=true;
        }
        else{
            if (xml.isStartElement() && xml.name().toString()!=strTableName){
                QString strName=xml.name().toString();

                QHash<QString,QString> mapFieldValue;
                QSqlRecord rec;
                mapFieldValue.insert(tr("table_name"),strImportedName);
                mapFieldValue.insert(tr("field_name"),strName);
                bool bTransformedIdColumn=selectValue(tr("change2AutoIncrement"),tr("Info_Fields"),mapFieldValue,rec)
                    && rec.value(0).toBool();

                if (!bIdentity || strIdentity.compare(xml.name().toString())!=0 || bTransformedIdColumn){

                    bool bNull=false;
                    QString strVal=xml.readElementText();
                    QString strType;

                    if (bTransformedIdColumn){
                        strName=strOldCode;
                        if (!selectValue(tr("original_type"), tr("Info_Fields"), mapFieldValue, rec)) return false;
                        strType=rec.value(0).toString();
                    }else{
                        if (!selectValue(tr("reviewed_type"), tr("Info_Fields"), mapFieldValue, rec))
                        {//Could not get type from Info_Fields (it;s not listed! So let's try this:)
                            if (!getFieldType(strTMPname,strName,strType))
                                return false;
                        }
                        else strType=rec.value(0).toString();
                    }

                    if (xml.isWhitespace() || strVal==tr("")||
                        strVal.isEmpty() || strVal.isNull()){//TODO: change null handling later - NO NULLS!
                            bNull=true;
                    }
                    else if ( strType==tr("nvarchar") || strType==tr("varchar") || strType==tr("char")
                        || strType==tr("nchar")){
                        if (!escapeSqlString(strVal)) return false;


                        strVal.prepend(tr("'"));
                        strVal.append(tr("'"));
                    }
                    else if (strType==tr("datetime")){
                        QString strOut;
                        if (!castDate(strVal,strOut))
                            return false;
                        strVal=strOut;
                        strVal.prepend(tr("'"));
                        strVal.append(tr("'"));
                    }
                    else if (strType==tr("bit")){
                        QString strOut;
                        if (!castBoolean(strVal,strOut))
                            return false;
                        strVal=strOut;
                    }
                    if (!bNull){//On null values, we don't do an insert
                        strValues.append(strVal);
                        strValues.append(tr(","));

                        QString strField=strName;
                        //We need to enclosed field names, just in case they have reserved words!
                        strField.prepend(tr("\""));
                        strField.append(tr("\""));

                        strFields.append(strField);
                        strFields.append(tr(","));
                    }

                }
                //else{//Check if we need to
                //}
            }

            bClosed=false;
        }
    }

    if (bAppendNullReplacement)
    {//Searches for a 'n/a' value on the table; if it does not find it, it appends a record
    //n.b.: it must exist a field called 'name'(nvarchar-ish), in order to perform this task

    //TODO: append null values on columns that have FK

        QStringList::const_iterator constIterator;
        for (constIterator = m_NullReplacements.constBegin(); constIterator != m_NullReplacements.constEnd();
            ++constIterator){

            QHash<QString,QString> mapFieldValue;
            mapFieldValue.insert(tr("Name"), *constIterator);
            QSqlRecord rec;
            bool bGotVal=selectValue(tr("Name"), strTMPname, mapFieldValue, rec);
            if (!bGotVal){

                strQuery=tr("INSERT INTO ") + strTMPname + tr("(Name) VALUES('") + *constIterator + tr("')");
                query.prepare(strQuery);
                if (!query.exec()){
                        //qDebug() << strQuery << endl;
                        emit showError(query.lastError().text(),true);
                return false;
                }
            }//if bGotVal
        }//for

    }//if bAppendNullReplacement

    return true;
}

bool TableAdapter::loopThroughXMLFK(const QStringList strTables, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bCreateKeys)
{
    xml.readNextStartElement();//Top element (whatever it is...)
    xml.readNextStartElement();
    if (xml.name()!=tr("schema") 
        || xml.namespaceUri().toString()!=SCHEMA
        ) {
            emit showError(tr("Could not find schema element!!"),true);
            return false;
        }

    while ( !(xml.name().toString().compare(tr("schema"))==0 && xml.isEndElement())
        && !xml.hasError() ){
        xml.readNext();

        if (xml.name().toString()==tr("element") && xml.isStartElement() &&
            xml.attributes().value(tr("name")).toString()==tr("ReferenceExportDataSet")){//Table
                xml.skipCurrentElement();
        }else if (xml.name().toString()==tr("appinfo") && xml.isStartElement()){//Foreign Keys
            if (!search4FK(strTables,xml,mapTMPNames,bCreateKeys)){
                return false;
            }
            break;
        }
    }

    return true;
}

bool TableAdapter::verifyTables2Import(QStringList strTables, QXmlStreamReader& xml)
{
    xml.readNextStartElement();//Top element (whatever it is...)
    xml.readNextStartElement();
    if (xml.name()!=tr("schema") 
        || xml.namespaceUri().toString()!=SCHEMA
        ) {
            emit showError(tr("Could not find schema element!!"),true);
            return false;
        }

    size_t ct=0;
    QStringList strTablesCopy=strTables;

    //Now look for the table and the PK
    while ( !(xml.name().toString().compare(tr("schema"))==0 && xml.isEndElement())
        && !xml.hasError() && !strTablesCopy.isEmpty() ){
        xml.readNext();

        QString strTable=xml.attributes().value(tr("name")).toString();
        if (xml.name().toString()==tr("element") && xml.isStartElement() &&
            strTablesCopy.contains(strTable)){//Table
                if (!verifyTableXML(strTable,xml)){
                    emit showError(tr("Could not import ") + strTable + tr(". This table is not conformed to what is described in the database!"),true);
                    strTables.removeOne(strTable);
                    return false;
                }
                if (!strTablesCopy.removeOne(strTable))
                    return false;
            ct++;
        }

    }

    return true;
}

bool TableAdapter::createTablesFromXml(const QStringList strTables, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames)
{
    bool bReset=true;

    xml.readNextStartElement();//Top element (whatever it is...)
    xml.readNextStartElement();
    if (xml.name()!=tr("schema") 
        || xml.namespaceUri().toString()!=SCHEMA
        ) {
            emit showError(tr("Could not find schema element!!"),true);
            return false;
        }

    size_t ct=0;
    QStringList strTablesCopy=strTables;
    //Now look for the table and the PK
    while ( !(xml.name().toString().compare(tr("schema"))==0 && xml.isEndElement())
        && !xml.hasError()){
        xml.readNext();

        QString strTable=xml.attributes().value(tr("name")).toString();
        if (xml.name().toString()==tr("element") && xml.isStartElement() &&
            strTablesCopy.contains(strTable)){//Table
                if (!readTableXML(strTable,xml,mapTMPNames)){
                    return false;
                }
                if (!strTablesCopy.removeOne(strTable))
                    return false;
            ct++;
        }

        else if (xml.name().toString()==tr("unique") && xml.isStartElement()){//Primary Key
            //reset strTables
            if (bReset){
                strTablesCopy=strTables;
                bReset=false;
            }
                if ( xml.attributes().hasAttribute(strMsdata,tr("PrimaryKey")) &&
                    xml.attributes().value(strMsdata,tr("PrimaryKey")).toString().compare(tr("true"),
                    Qt::CaseInsensitive)==0 ){
                        QString strPKname=xml.attributes().value(tr("name")).toString();
                        xml.readNextStartElement();
                        if (xml.name().toString().compare(tr("selector"))==0){
                            if (!xml.attributes().hasAttribute(tr("xpath"))) return false;
                            QString strPath=xml.attributes().value(tr("xpath")).toString();
                            strPath=strPath.remove(tr(".//mstns:"));//remove the namespace
                            if (strTablesCopy.contains(strPath)){
                                if (!readPKXML(strPath,strPKname,xml,mapTMPNames)){
                                   return false;
                                }
                                if (!strTablesCopy.removeOne(strPath))
                                    return false;
                            }
                        }
                }
        }//unique
    }

    return ct==strTables.size();//We must have a table, but *maybe* we don't have a primary key!
}

bool TableAdapter::search4FK(const QStringList strTables, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames, bool bCreateKeys)
{
    MapFK mapKeys;
    QStringList keyList;
    QSqlQuery query;

    //Check if we need to rename these tables
    QStringList strTablesCopy=strTables;
    QStringList::iterator iterator;
    for (iterator = strTablesCopy.begin(); iterator != strTablesCopy.end();
            ++iterator)
     {
        QString strImportedName;
        bool bExists;
        if (!getImportedName(*iterator,strImportedName,bExists)) return false;
        *iterator=strImportedName;
     }

    while( !(xml.isEndElement() && xml.name().toString()==tr("appinfo")) ) {
            xml.readNext();
            if (xml.isStartElement()){
                QString strImportedName;
                bool bExists;
                if (!getImportedName(xml.attributes().value(strMsdata,tr("child")).toString(),strImportedName,bExists)) return false;
                if (xml.name().toString().compare(tr("Relationship"))==0 && xml.namespaceUri().compare(
                    strMsdata)==0 && xml.attributes().hasAttribute(strMsdata,tr("child")) &&
                    strTablesCopy.contains(strImportedName)){
                        if (!xml.attributes().hasAttribute(tr("name")) || 
                            !xml.attributes().hasAttribute(strMsdata,tr("parent")) ||
                            !xml.attributes().hasAttribute(strMsdata,tr("parentkey")) ||
                            !xml.attributes().hasAttribute(strMsdata,tr("childkey")) )
                                return false;
                        //If parent is not in the table list, we must *not* create the FK!
                        QString strParent=xml.attributes().value(strMsdata,tr("parent")).toString();

                        //Here we try to see if the parent exists as a renamed table or not...
                        QSqlDatabase db=QSqlDatabase::database();
                        QStringList listTables=db.tables();
                        bool bFoundParent=false;
                        if (listTables.contains(strParent)) bFoundParent=true;
                        else{
                            QSqlQuery query(listCASImportTables(strParent));
                            if (query.numRowsAffected()>0){
                                query.first();
                                strParent=query.record().value(tr("imported_name")).toString();
                                bFoundParent=true;
                            }
                        }

                        if (bFoundParent){
                            //Finally we have to check if that table actually exists in the database (althought it should!)
                            if (getObjects(query,strParent) && query.numRowsAffected()>0){
                                mapKeys.insert(xml.attributes().value(tr("name")).toString(),
                                    FK(strParent,
                                    strImportedName,
                                    xml.attributes().value(strMsdata,tr("parentkey")).toString(),
                                    xml.attributes().value(strMsdata,tr("childkey")).toString()));
                                if (!keyList.contains(xml.attributes().value(tr("name")).toString()))
                                        keyList.push_back(xml.attributes().value(tr("name")).toString());
                            }
                            else emit showError(tr("Could not find table ") + strParent + tr(" in the database! Aborting Foreign Key Generation!"),true);
                        }
                }//if
            }//if
        }//while

     //Now loop through the list and retrieve the fields that compose the foreign key from the multimap
     QStringList::const_iterator constIterator;
     for (constIterator = keyList.constBegin(); constIterator != keyList.constEnd();
         ++constIterator){
            QString strSql;
            QString strParentKeys, strChildKeys, strParent, strChild;

             MapFK::iterator i = mapKeys.find(*constIterator);
             strChild=i.value().m_child;

            QString strFkName, strFrkNameOld;
            strFrkNameOld=*constIterator;
            if (!verifyConstraintName(*constIterator,strFkName)) return false;

             strParent=i.value().m_parent;
             bool bTreeRef=strParent.compare(bottomLevelTable)==0;

            if (!bCreateKeys){ //Just update the FK reference

                if (bTreeRef){// //special handling of Tree references
                    if (mapKeys.count(strFrkNameOld)>1) return false;//For now we only support binding with the BottomTable through one field!
                    MapFK::const_iterator it=mapKeys.find(strFrkNameOld);
                    if (it==mapKeys.constEnd()) return false;
                    QString strName=tr("TreeKey");
                    MapFK mapTreeKeys;
                    mapTreeKeys.insert(strName,FK(tr("Tree"),it.value().m_child,tr("id"),it.value().m_childkey));
                     if (!updateFKReferences(strName, mapTreeKeys, mapTMPNames, true)) {
                         emit showError(tr("Could not update the Foreign Key Tree Reference on this table!"),true);
                         return false;
                     }
                 }else{

                     if (convert2PK(strParent)){
                         if (!updateFKReferences(strFrkNameOld, mapKeys, mapTMPNames)) {
                             emit showError(tr("Could not update the Foreign Key Reference on this table!"),true);
                             return false;
                         }
                     }

                 }
            }else{//Just create the keys

                if (bTreeRef){//Sql for constraint referencing Tree
                    //Hardcoded: Tree table, id field on Tree table;
                    strParentKeys.append(tr("ID"));
                    if (mapKeys.count(strFkName)!=1) return false;
                    MapFK::iterator it=mapKeys.find(strFkName);
                    strChildKeys.append(it.value().m_childkey);

                    QHash<QString,QString> mapFieldValue;
                    QSqlRecord rec;
                    mapFieldValue.insert(tr("imported_name"),bottomLevelTable);
                    if (!selectValue(tr("original_name"),tr("Info_Tables_Import"),mapFieldValue,rec)) return false;
                    QString ObottomLevelTable=rec.value(0).toString();
                    strFkName=strFkName.replace(ObottomLevelTable,tr("tree"));
                    strSql.append( tr("ALTER TABLE ")+ strChild +
                        tr(" WITH CHECK ADD CONSTRAINT ") + strFkName + 
                        tr(" FOREIGN KEY(") );

                } else{

                    strSql.append( tr("ALTER TABLE ")+ strChild +
                        tr(" WITH CHECK ADD CONSTRAINT ") + strFkName + 
                        tr(" FOREIGN KEY(") );

                     while (i != mapKeys.end() && i.key() == strFrkNameOld) {
                         strParentKeys.append(i.value().m_parentkey);
                         strParentKeys.append(tr(","));
                         strChildKeys.append(i.value().m_childkey);
                         strChildKeys.append(tr(","));
                         ++i;
                     }//while multimap

                     strParentKeys.remove(strParentKeys.length()-1,1);//remove last comma
                     strChildKeys.remove(strChildKeys.length()-1,1);//remove last comma

                }//else

                strSql.append(strChildKeys + tr(") REFERENCES ") + (bTreeRef?tr("Tree"):strParent) + 
                tr(" (") + strParentKeys + tr(")") );

                if (!query.prepare(strSql)) return false;
                if (!query.exec()) {
                    //qDebug() << strSql << endl;
                    emit showError(query.lastError().text(),true);
                    return false;
                }

            }//create keys
     }//for stringlist

    return true;
}

bool TableAdapter::readPKXML(const QString strTable, const QString strName, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames)
{
    QStringList fieldList;

    QString strFkName;
    if (!verifyConstraintName(strName,strFkName)) return false;

    while( !(xml.isEndElement() && xml.name().toString()==tr("unique")) ) {
        xml.readNext();
        if (xml.isStartElement() && xml.name().toString()==tr("field")){
            if (!xml.attributes().hasAttribute(tr("xpath"))) return false;
            QString strPath=xml.attributes().value(tr("xpath")).toString();
            strPath=strPath.remove(tr("mstns:"));//remove the namespace
            fieldList.push_back(strPath);
        }
    }

    QString strSql;
    //Check if we need to rename this table
    QString strImportedName,strTMPname;
    bool bExists;
    if (!getImportedName(strTable,strImportedName,bExists)) return false;
    if (!getMappedTMPName(strImportedName,mapTMPNames,strTMPname)) return false;

    strSql.append(tr("ALTER TABLE ") + strTMPname + tr(" ADD CONSTRAINT ") + strFkName +
        tr(" PRIMARY KEY NONCLUSTERED ( "));

   QStringList::const_iterator constIterator;
     for (constIterator = fieldList.constBegin(); constIterator != fieldList.constEnd();
         ++constIterator){
            strSql.append(*constIterator);
            strSql.append(" ASC,");

            //Check if field is null: we *cannot* have PK in null fields!
            bool bIsNull;
            QSqlQuery query;
            if (!getIsNullableAndDefault(strTMPname, *constIterator, query)) return false;
             if (query.numRowsAffected()!=1) return false;
             query.first();
             query.value(query.record().indexOf(tr("IS_NULLABLE"))).toString().compare(
                 tr("NO"),Qt::CaseInsensitive)==0? bIsNull=false: bIsNull=true;

             if (bIsNull){
                QString strType=query.value(query.record().indexOf(tr("DATA_TYPE"))).toString();
                    if (strType.compare(tr("nchar"),Qt::CaseInsensitive)==0 || 
                        strType.compare(tr("nvarchar"),Qt::CaseInsensitive)==0 ){
                        //If its a string, we need to append the correct length: otherwise it defaults to 1
                        int idx=query.record().indexOf(tr("CHARACTER_MAXIMUM_LENGTH"));
                        QVariant var=query.record().value(idx);
                        if (var.isNull() || !var.isValid() ) return false;
                        strType.append(tr("(") + var.toString() + tr(")"));
                    }
                if (!nullifyField(strTMPname,*constIterator,strType))
                    return false;
             }

     }
     strSql.remove(strSql.length()-1,1);
     strSql.append(tr(")"));

    QSqlQuery query;
    if (!query.prepare(strSql)) return false;
    if (!query.exec()){
        emit showError(query.lastError().text(),true);
        return false;
    }
    return true;
}

bool TableAdapter::getFieldTypeXML(QXmlStreamReader& xml, QString& strType, int& size, bool bSeparateSize)
{
    if (xml.attributes().hasAttribute(tr("type"))){
        strType=xml.attributes().value(
            tr("type")).toString();
        //Find the appropriated "sql" type
        QMap<QString,QString>::const_iterator it=m_mapXs2Sql.find(strType);
        if (it==m_mapXs2Sql.end())
            return false;
        strType=it.value();
        size=-1;
    }
    else{ //string or decimal
        xml.readNextStartElement();
        if (xml.name().toString()!=tr("simpleType"))
            return false;
        xml.readNextStartElement();
        if (xml.name().toString()!=tr("restriction"))
            return false;
        if (!xml.attributes().hasAttribute(tr("base")))
            return false;
        strType=xml.attributes().value(
            tr("base")).toString();

        //Find the appropriated "sql" type
        QMap<QString,QString>::const_iterator it=m_mapXs2Sql.find(strType);
        if (it==m_mapXs2Sql.end())
            return false;
        strType=it.value();
        xml.readNextStartElement();

        if (strType==tr("nvarchar")||strType==tr("varchar")||strType==tr("char")||strType==tr("nchar")){
            if (xml.name().toString()!=tr("maxLength"))
                return false;
            QString strMaxLength=tr("");
            if (!xml.attributes().hasAttribute(tr("value")))
                return false;
            strMaxLength=xml.attributes().value(tr("value")).toString();
            QString strAmendLength;
            if (!fixStringMaximumLength(strMaxLength,strAmendLength,true,false))
                return false;
            strType=strType + (bSeparateSize?tr(""): tr("(") + strAmendLength + tr(")"));
            size=QVariant(strMaxLength).toInt();
        }else if (strType==tr("decimal")){
            QString strPrecision=tr("");
            QString strScale=tr("");
            while (xml.name().toString()==tr("totalDigits") 
                || xml.name().toString()==tr("fractionDigits")){

                if (!xml.attributes().hasAttribute(tr("value")))
                return false;
                if (xml.name().toString()==tr("totalDigits"))
                    strPrecision=xml.attributes().value(tr("value")).toString(); else
                strScale==xml.attributes().value(tr("value")).toString();
                xml.readNextStartElement();
            }

            //Obrigatory to define scale, when defining precision; precision optional;
            //accept both empty;
            //default precision: t-sql default - 18
            if (!strScale.isEmpty()){
                strType+= tr("(") + (strPrecision.isEmpty()?tr("18"):strPrecision)
                + tr(",") + strScale + tr(")");
            }

        }
        else{
            emit showError(tr("Unkown field type!"));
            return false;
        }

    }

    return true;
}

bool TableAdapter::readTableXML(const QString strTable, QXmlStreamReader& xml, const QMap<QString,QString>& mapTMPNames)
{
    QString strCreateTable;

    //Check if we need to rename this table
    QString strImportedName;
    bool bExists;
    if (!getImportedName(strTable,strImportedName,bExists)){
        emit showError(tr("Could not define a name for this table!"),true);
        return false;
    }

    QString strTMPname;
    if (!getMappedTMPName(strImportedName,mapTMPNames,strTMPname)){
        emit showError(tr("Could not obtain a mapped temporary name for this table!"),true);
        return false;
    }

    if (!dropTableIfExists(strTMPname)){
        emit showError(tr("Could not drop this table!"),true);
        return false;
    }

    //First set this to on, so that we can escape reserved words!
    QSqlQuery query(tr("SET QUOTED_IDENTIFIER ON"));
    QString strOldType,strTMP;
    strCreateTable.append(tr("CREATE TABLE ") + strTMPname + tr(" ("));

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
        xml.name() == "complexType")) {
            xml.readNext();

            if (xml.name().toString()==tr("element") && xml.isStartElement()){

                //compulsory attributes
                if (!xml.attributes().hasAttribute(tr("name")))
                    return false;
                QString strName=xml.attributes().value(
                    tr("name")).toString();

                QString strSeed(tr("")),strStep(tr("")),strType,strDefault;
                bool bNull, bAutoInc, bUnique=false;
                int size;

                if (!getFieldTypeXML(xml,strType,size)) return false;
                strTMP=strType;
                if (!isField2Transform(strImportedName,strName)){
                    //optional attributes
                    if (xml.attributes().hasAttribute(strMsdata,tr("AllowDBNull"))){
                        xml.attributes().value(strMsdata,tr("AllowDBNull")).toString().compare(
                            tr("false"),Qt::CaseInsensitive)==0? bNull=false: bNull=true;
                    }
                    else bNull=true;

                    strDefault=tr("");
                    if (xml.attributes().hasAttribute(strMsdata,tr("DefaultValue"))){
                        strDefault=xml.attributes().value(strMsdata,tr("DefaultValue")).toString();
                    }

                    if (xml.attributes().hasAttribute(strMsdata,tr("AutoIncrement"))){
                        xml.attributes().value(strMsdata,tr("AutoIncrement")).toString().compare(
                            tr("false"),Qt::CaseInsensitive)==0? bAutoInc=false: bAutoInc=true;
                        if (!xml.attributes().hasAttribute(strMsdata,tr("AutoIncrementSeed")))
                            return false;
                        strSeed=xml.attributes().value(strMsdata,tr("AutoIncrementSeed")).toString();
                        if (!xml.attributes().hasAttribute(strMsdata,tr("AutoIncrementStep")))
                            return false;
                        strStep=xml.attributes().value(strMsdata,tr("AutoIncrementStep")).toString();
                    }
                    else bAutoInc=false;
                }
                else {
                    if (!readFieldTransformDefs(strImportedName,strName,strType,bAutoInc,strSeed,strStep,strDefault,bNull,bUnique)){
                        return false;
                    }else{//In a transformed field, we don't use the xml type, but we stored for the backup field
                        if (bAutoInc) strOldType=strTMP;
                    }
                }

                strCreateTable.append( tr("\"") + strName + tr("\"") + tr(" ") + strType + tr(" ") +
                    (strType.contains(tr("nvarchar")) || strType.contains(tr("varchar")) || strType.contains(tr("char"))
                    || strType.contains(tr("nchar"))
                    ?COLLATE + tr(" "):tr("")) + (!bNull?tr("NOT NULL"):tr("")) + (bUnique?tr(" UNIQUE"):tr("")) );
                if (!strDefault.isEmpty()) strCreateTable.append(tr(" DEFAULT ") + strDefault);
                //AutoIncrement=Identity
                if (bAutoInc) strCreateTable.append(tr(" IDENTITY(") + strSeed
                    + tr(",") + strStep + tr(")"));

                strCreateTable.append(tr(","));
            }
    }
    //If this is a conversion table, then we create another field (with the original type) for backing up the original codes!
    QHash<QString,QString> mapFieldValue;
    QSqlRecord rec;
    mapFieldValue.insert(tr("imported_name"),strImportedName);
    if (selectValue(tr("convertPK2Int"),tr("Info_Tables_Import"),mapFieldValue,rec) &&
        rec.value(0).toBool()){
            QString strNull;
            if (!getNullForType(strOldType,tr("Missing"),strNull)){
                emit showError(tr("Could not get null for this type!"),true);
                return false;
            }
            QString strOldCode=qApp->translate("db", OLDCODE);
            QString strOldFieldQuery=strOldCode + tr(" ") + strOldType + tr(" ") +
                    (strOldType.contains(tr("nvarchar")) || strOldType.contains(tr("varchar")) || strOldType.contains(tr("char"))
                    || strOldType.contains(tr("nchar"))
                    ?COLLATE + tr(" "):tr("")) + 
                tr(" NOT NULL DEFAULT '") + strNull +
                tr("',");//Always not null, as we are importing from a PK... and always defaulting to null code
            strCreateTable.append(strOldFieldQuery);
    }

    strCreateTable.remove(strCreateTable.length()-1,1);//remove last comma
    strCreateTable.append(tr(")"));

    if (!query.prepare(strCreateTable)) return false;
    if (!query.exec()) {
        //qDebug() << strCreateTable << endl;
        emit showError(query.lastError().text(),true);
        return false;
    }

    return true;
}

bool TableAdapter::verifyTableXML(const QString strTable, QXmlStreamReader& xml)
{

    //Check if we need to rename this table
    QString strImportedName;
    bool bExists;
    if (!getImportedName(strTable,strImportedName,bExists)){
        emit showError(tr("Could not define a name for this table!"),true);
        return false;
    }

    //If the table exists, it must satisfy a certain structure
    if (bExists){

        //Get fields from database
        QMap<QString,QString> mapTypes,mapXMLTypes;
        QMap<QString,int> mapSizes,mapXMLSizes;
        if (!getImportedFieldsDescription(strImportedName,mapTypes,mapSizes)){
            emit showError(tr("Could not retrieve information about these fields!"),true);
            return false;
        }

        while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == tr("complexType"))) {
                xml.readNext();

                if (xml.name().toString()==tr("element") && xml.isStartElement()){

                    if (!xml.attributes().hasAttribute(tr("name")))
                        return false;
                    QString strName=xml.attributes().value(
                        tr("name")).toString();

                    QString strType;
                    int size;

                    if (!getFieldTypeXML(xml,strType,size,true)) return false;

                    //We only support type,size(strings) and name checking, for now!
                    mapXMLTypes.insert(strName,strType);
                    mapXMLSizes.insert(strName,size);
                    }
        }//while

        //It has to find *exactly* the same items promised on the Info_Fields table!
        if (mapXMLTypes.size()!=mapTypes.size()){//n.b.: it does not matter if we compare the mapTypes or mapSizes as they should be the same!
            emit showError(tr("The field count on the XML file does not match the field count expected on the database!"),true);
            return false;
        }

        QMapIterator<QString, QString> i(mapTypes);
        QMapIterator<QString, int> j(mapSizes);
        while (i.hasNext() && j.hasNext()) {
             i.next();
             j.next();

             //Check the type
             QMap<QString,QString>::const_iterator it=mapXMLTypes.find(i.key());
            if (it!=mapXMLTypes.end()){
                if (it.value()!=i.value()){
                    emit showError(tr("Type of field ") + i.key() + tr(" does not match expected type ") + i.value(),true);
                    return false;
                }
            }else{
                emit showError( tr("Could not find field ")+ i.key() + tr(" in the file!"),true );
                return false;
            }

             //Now check the size
             QMap<QString,int>::const_iterator itt=mapXMLSizes.find(j.key());
            if (itt!=mapXMLSizes.end()){
                if (itt.value()!=j.value()){
                    emit showError(tr("Size of field ") + j.key() + tr(" does not match expected size ") + QVariant(j.value()).toString(),true);
                    return false;
                }
            }else{
                emit showError( tr("Could not find field ")+ j.key() + tr(" in the file!"),true );
                return false;
            }

        }

    }
    else
        emit showError(tr("WARNING: we are importing an *unknown* table into the database: ") + strImportedName
        + tr("! Could not enforce any table policies."),true);

    return true;
}

bool TableAdapter::addVendorFiles(const QString strPath, QStringList& strFiles)
{
    QFile inputFile(":/app_new/msdata.xsd");
    if (!inputFile.open(QIODevice::ReadOnly)) return false;

    //Read
     QTextStream in(&inputFile);
     QString line = in.readAll();
     if (line.size()<=0) return false;

    //check the schema
    QXmlSchema schema;
    schema.load( line.toAscii() );
    if ( !schema.isValid() ) return false;

    //Write
    QString strFile=strPath + tr("/msdata.xsd");
    QFile outputFile(strFile);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    outputFile.write(line.toAscii());

    outputFile.close();
    inputFile.close();

    strFiles.push_back(strFile);

    return strFile.size()>0;
}

void TableAdapter::initTypeMapping()
{
    //declare Schema Data Types
    m_mapQt2Xs.insert(tr("QString"), tr("xs:string"));
    m_mapQt2Xs.insert(tr("int"), tr("xs:int"));
    m_mapQt2Xs.insert(tr("QByteArray"), tr("xs:hexBinary"));
    m_mapQt2Xs.insert(tr("double"), tr("xs:decimal"));
    m_mapQt2Xs.insert(tr("uint"), tr("xs:boolean"));
    m_mapQt2Xs.insert(tr("QDateTime"), tr("xs:dateTime"));
    m_mapQt2Xs.insert(tr("qlonglong"), tr("xs:long"));

    m_mapXs2Sql.insert(tr("xs:string"), tr("nvarchar"));
    m_mapXs2Sql.insert(tr("xs:boolean"), tr("bit"));
    m_mapXs2Sql.insert(tr("xs:integer"), tr("int"));
    m_mapXs2Sql.insert(tr("xs:int"), tr("int"));
    m_mapXs2Sql.insert(tr("xs:long"), tr("bigint"));
    m_mapXs2Sql.insert(tr("xs:decimal"), tr("decimal"));
    m_mapXs2Sql.insert(tr("xs:double"), tr("decimal"));//Keep only for backwards compability!
    m_mapXs2Sql.insert(tr("xs:dateTime"), tr("datetime"));
    m_mapXs2Sql.insert(tr("xs:hexBinary"), tr("timestamp"));//TODO: maybe this is not alwas a timestamp: add new schema data types
}

bool TableAdapter::exportSchema(const QStringList strTables, QXmlStreamWriter& xml)
{
    QFileInfo fi(m_strFileName);
    QString str=qApp->translate("xml", URI);

    xml.writeStartElement(tr("http://www.w3.org/2001/XMLSchema"), tr("schema") );

    xml.writeAttribute(tr("id"),tr("ReferencedExportedDataset"));

    xml.writeNamespace( tr("urn:schemas-microsoft-com:xml-msdata"),tr("msdata"));

    xml.writeAttribute(tr("urn:schemas-microsoft-com:xml-msdata"),
        tr("schemaLocation"),tr("urn:schemas-microsoft-com:xml-msdata msdata.xsd"));

    xml.writeNamespace( str + tr("ReferenceExportDataSet"), tr("mstns"));

    xml.writeAttribute(tr("targetNamespace"), str + tr("ReferenceExportDataSet"));
    xml.writeAttribute(tr("attributeFormDefault"),tr("qualified"));
    xml.writeAttribute(tr("elementFormDefault"),tr("qualified"));
        xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"), tr("element") );
        xml.writeAttribute(tr("name"),tr("ReferenceExportDataSet"));
        xml.writeAttribute(tr("urn:schemas-microsoft-com:xml-msdata"),
            tr("IsDataSet"),tr("true"));
        xml.writeAttribute(tr("urn:schemas-microsoft-com:xml-msdata"),
            tr("UseCurrentLocale"),tr("true"));

                    xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"), tr("complexType") );
                        xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"), tr("choice") );
                        xml.writeAttribute(tr("minOccurs"),tr("0"));
                        xml.writeAttribute(tr("maxOccurs"),tr("unbounded"));
                        //Loop for the field defs
                         for (QStringList::const_iterator constIterator = strTables.constBegin(); constIterator != strTables.constEnd();
                             ++constIterator){

                                xml.writeStartElement(tr("http://www.w3.org/2001/XMLSchema"),
                                    tr("element"));
                                xml.writeAttribute(tr("name"),*constIterator);
                                exportFieldDefs(*constIterator, xml);
                                xml.writeEndElement();//element
                         }

                        xml.writeEndElement();//choice
            xml.writeEndElement();//complex type

            //Loop for the primary keys
            //TODO: sort out primary keys with multiple columns
             for (QStringList::const_iterator constIterator = strTables.constBegin(); constIterator != strTables.constEnd();
                 ++constIterator){
                    QSqlQueryModel model;
                    model.setQuery(selectPKConstraints(*constIterator));
                    QStringList fieldList;

                    //N.b.: always do this to force retrieving the column count, as the SQL server driver
                    // has a limit of 256 rows!!!!
                    while (model.canFetchMore())
                    {
                        model.fetchMore();
                    }

                    for (size_t i=0; i < (size_t)model.rowCount();++i){
                        QString strField=
                            model.record(i).value(tr("COLUMN_NAME")).toString();
                        fieldList.push_back(strField);

                        if (model.record(i).value(tr("CONSTRAINT_NAME"))!=
                            model.record(i+1).value(tr("CONSTRAINT_NAME"))){
                            if (!exportPK(model.record(i),*constIterator,fieldList,xml)) return false;
                            fieldList.clear();
                        }
                    }
             }

        xml.writeEndElement();//element

        xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"), tr("annotation") );
            xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"), tr("appinfo") );

            //Loop for the foreign keys
             for (QStringList::const_iterator constIterator = strTables.constBegin(); constIterator != strTables.constEnd();
                 ++constIterator){

                QSqlQueryModel model;
                //qDebug() << selectFKConstraints(*constIterator,true)<< endl;
                model.setQuery(selectFKConstraints(*constIterator,true));

                //N.b.: always do this to force retrieving the column count, as the SQL server driver
                // has a limit of 256 rows!!!!
                while (model.canFetchMore())
                {
                    model.fetchMore();
                }

                for (size_t i=0; i < (size_t)model.rowCount();++i){
                    if (!exportFK(model.record(i),xml)) return false;
                }

             }

            xml.writeEndElement();//annotation
        xml.writeEndElement();//appinfo

    xml.writeEndElement();//schema

    return true;
}

bool TableAdapter::exportPK(const QSqlRecord rec, const QString strTable, const QStringList fieldList, QXmlStreamWriter& xml)
{
    QString strPkName, strXpathSel, strXpathFld, strField;

    if ( rec.field(tr("COLUMN_NAME")).value().isNull() || !rec.field(tr("COLUMN_NAME")).value().isValid()
        || rec.field(tr("CONSTRAINT_NAME")).value().isNull() || 
        !rec.field(tr("CONSTRAINT_NAME")).value().isValid())
            return false;

    strPkName=rec.field(tr("CONSTRAINT_NAME")).value().toString();

    //Primary Keys
    xml.writeStartElement(tr("http://www.w3.org/2001/XMLSchema"), tr("unique"));
    xml.writeAttribute(tr("name"),strPkName);
    xml.writeAttribute(tr("urn:schemas-microsoft-com:xml-msdata"),
        tr("PrimaryKey"),tr("true"));
    xml.writeStartElement(tr("http://www.w3.org/2001/XMLSchema"), tr("selector"));
        xml.writeAttribute(tr("xpath"),buildSelectorPath(strTable));
        xml.writeEndElement();//selector

     QStringList::const_iterator constIterator;
     for (constIterator = fieldList.constBegin(); constIterator != fieldList.constEnd();
         ++constIterator){
            xml.writeStartElement(tr("http://www.w3.org/2001/XMLSchema"), tr("field"));
            xml.writeAttribute(tr("xpath"),buildFieldPath(*constIterator));
            xml.writeEndElement();//field
     }
    xml.writeEndElement();//unique

    return true;
}

QString TableAdapter::buildSelectorPath(const QString str)
{
    return tr(".//mstns:") + str;
}

QString TableAdapter::buildFieldPath(const QString str)
{
        return tr("mstns:") + str;
}


bool TableAdapter::exportFK(const QSqlRecord rec, QXmlStreamWriter& xml)
{
    QString fkName=rec.value(tr("CONSTRAINT_NAME")).toString();

    QString strParent=rec.value(tr("PK_Table")).toString();
    QString strParentKey=rec.value(tr("PK_Column")).toString();
    QString strChild=rec.value(tr("FK_Table")).toString();
    QString strChildKey=rec.value(tr("FK_Column")).toString();

    xml.writeStartElement( tr("urn:schemas-microsoft-com:xml-msdata"), tr("Relationship") );
    xml.writeAttribute(tr("name"),fkName);
    xml.writeAttribute(tr("urn:schemas-microsoft-com:xml-msdata"),tr("parent"),strParent);
    xml.writeAttribute(tr("urn:schemas-microsoft-com:xml-msdata"),tr("child"),strChild);
    xml.writeAttribute(tr("urn:schemas-microsoft-com:xml-msdata"),tr("parentkey"),strParentKey);
    xml.writeAttribute(tr("urn:schemas-microsoft-com:xml-msdata"),tr("childkey"),strChildKey);
    xml.writeEndElement();//Relationship

    return true;
}

bool TableAdapter::addExtraAttributes(const QString strTable, const QString strField,
                                      QXmlStreamWriter& xml)
{
   //! Add more column attributes
    /*!
    This function adds some more attributes of the column:
    auto increment related properties (identity), default value (in case it has one!)
    and nullability; we are ignoring the minOccurs attribute 4 now, since it has always been set to 0...
    \par QString table name
    \par QString field name
    \par QXmlStreamWriter xml stream writer
    \return bool as success or failure of the two operations
    */

    QSqlQuery query;

    //Grabbing the object id
    if (!getObjects(query)) return false;

    bool bIdentity, bIsNull;
    QString seed,increment;
    QVariant varDefault=QVariant(QVariant::Invalid);
    int objectID=-1;
     while (query.next()) {
         if (query.value(query.record().indexOf(tr("TableName"))).toString()==strTable
             && query.value(query.record().indexOf(tr("name"))).toString()==strField){
                objectID=query.value(query.record().indexOf(tr("object_id"))).toInt();
                bIdentity=query.value(query.record().indexOf(tr("is_identity"))).toBool();
                break;
         }
     }

     if (objectID!=-1){
         if (bIdentity){
            //IDENTITY COLUMN = TRUE
            //AUTOINCREMENT COLUMN = TRUE
             if (!getAutoIncrementInfo(objectID, query)) return false;
            //Sometimes this query is returning -1, so lets ignore the size()!
             if (query.size()!=-1 && query.size()!=1) return false;
             query.first();
             seed=query.value(0).toString();//Casted seed value
             increment=query.value(1).toString(); //Casted increment value

             //TODO: ADD IDENTITY?
            xml.writeAttribute(strMsdata,tr("ReadOnly"), tr("true"));
            xml.writeAttribute(strMsdata,tr("AutoIncrement"), tr("true"));
            xml.writeAttribute(strMsdata,tr("AutoIncrementSeed"), seed);
            xml.writeAttribute(strMsdata,tr("AutoIncrementStep"), increment);
         }
        if (!getIsNullableAndDefault(strTable, strField, query)) return false;

        //Sometimes this query is returning -1, so lets ignore the size()!
        if (query.size()!=-1 && query.size()!=1) return false;
         query.first();
         query.value(query.record().indexOf(tr("IS_NULLABLE"))).toString().compare(
             tr("NO"),Qt::CaseInsensitive)==0? bIsNull=false: bIsNull=true;
         if (!bIsNull){
            xml.writeAttribute(strMsdata,tr("AllowDBNull"), tr("false"));
         }else{
            xml.writeAttribute(tr("nillable"),tr("true"));
         }

         if (!query.value(query.record().indexOf(tr("COLUMN_DEFAULT"))).isNull()){
             varDefault=query.value(query.record().indexOf(tr("COLUMN_DEFAULT")));
             xml.writeAttribute(strMsdata,tr("DefaultValue"), varDefault.toString());
         }

        return true;
     }

     return false;
}

bool TableAdapter::exportFieldDefs(const QString strTable, QXmlStreamWriter& xml)
{
    // Do not export *Diagrams*!!
    if (strTable.compare(tr("sysdiagrams"))==0) return false;

    xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"),tr("complexType"));
        xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"),tr("sequence"));

        //Instantiate table model on the fly, to retrieve the fields
         QSqlQueryModel model;
         model.setQuery(selectAllRecordsFromTable(strTable));

        //N.b.: always do this to force retrieving the column count, as the SQL server driver
        // has a limit of 256 rows!!!!
        while (model.canFetchMore())
        {
            model.fetchMore();
        }

         QSqlRecord rec=model.record();

         for (size_t i=0; i < (size_t)rec.count(); ++i){
            QSqlField field=rec.field(rec.fieldName(i));
            if (field.name().compare(tr("upsize_ts"))!=0 && field.name().compare(tr("OLD_CODE"),
                Qt::CaseInsensitive)!=0){//This is an automatic internal field: don't export it!
                xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"),tr("element"));
                xml.writeAttribute(tr("name"),field.name());
                if (addExtraAttributes(strTable,field.name(),xml))
                {
                    QString strType;
                    if (!getSchemaType(field.type(),m_mapQt2Xs,strType)){
                        emit showError(QVariant::typeToName(field.type()) + tr(": data type not mapped!"),true);
                    }
                    else{
                        if (strType.compare(tr("xs:boolean"))==0 || strType.compare(tr("xs:integer"))==0 || strType.compare(tr("xs:int"))==0
                            || strType.compare(tr("xs:double"))==0 || 
                            strType.compare(tr("xs:long"))==0 || strType.compare(tr("xs:dateTime"))==0){
                            xml.writeAttribute(tr("type"),strType);

                        }else if (strType.compare(tr("xs:hexBinary"))==0 ||
                            strType.compare(tr("xs:string"))==0 || strType.compare(tr("xs:decimal"))==0){
                            xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"),tr("simpleType"));
                                xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"),tr("restriction"));
                                    xml.writeAttribute(tr("base"),strType);

                                    if (strType.compare(tr("xs:string"))==0){
                                        xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"),
                                            tr("maxLength"));
                                        QString strAmendLength;
                                        QString strMaximumLength=QVariant(field.length()).toString();
                                        if (fixStringMaximumLength(strMaximumLength,strAmendLength,false,false)){
                                            xml.writeAttribute(tr("value"),strAmendLength);
                                        }
                                        else emit showError(tr("Could not find string length for field ") + field.name() + tr("!"),true);
                                        xml.writeEndElement();//maxlength

                                    }else if (strType.compare(tr("xs:decimal"))==0){
                                        QString strPrecision,strScale;
                                        if (getFieldPrecision(strTable,rec.fieldName(i),strPrecision,strScale))
                                            xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"),
                                                tr("totalDigits"));
                                            xml.writeAttribute(tr("value"),strPrecision);
                                            xml.writeEndElement();//totalDigits
                                            xml.writeStartElement( tr("http://www.w3.org/2001/XMLSchema"),
                                                tr("fractionDigits"));
                                            xml.writeAttribute(tr("value"),strScale);
                                            xml.writeEndElement();//fractionDigits
                                    }else emit showError(tr("Could not find decimal precision for field ") + field.name() + tr("!"),true);


                                xml.writeEndElement();//restriction
                            xml.writeEndElement();//simpletype
                        }
                        else{
                            emit showError(strType + tr(": data type not mapped!"),true);
                        }
                    }
                }
                xml.writeEndElement();//element
                }
         }

        xml.writeEndElement();//sequence
    xml.writeEndElement();//complextype

    return true;
}

bool TableAdapter::dumpSchema(QXmlStreamReader& reader, QXmlStreamWriter& writer)
{
    if (!reader.attributes().hasAttribute(tr("id"))) return false;
    //if (!reader.attributes().hasAttribute(strMsdata, tr("schemaLocation"))) return false;//n.b.: This is optional!
    if (!reader.attributes().hasAttribute(tr("targetNamespace"))) return false;

    writer.writeCurrentToken(reader);

    if (!dumpXML(tr("schema"),reader,writer)) return false;

   if (reader.hasError()) {
         return false;
   }

    return true;
}

bool TableAdapter::readTableNames(QXmlStreamReader& xml, QStringList& tableList)
{
    xml.readNextStartElement();//Top element (whatever it is...)
    xml.readNextStartElement();
    if (xml.name()!=tr("schema") 
        || xml.namespaceUri().toString()!=SCHEMA
        ) {
            emit showError(tr("Could not find schema element!!"),true);
            return false;
        }

    xml.readNextStartElement();//skip the name of the dataset
    while (!xml.isEndDocument() && !xml.hasError() ){
        xml.readNext();
        if (xml.name().toString()==tr("element") && xml.isStartElement()){
                tableList << xml.attributes().value(tr("name")).toString();
                xml.skipCurrentElement();
        }
    }
    return true;
}