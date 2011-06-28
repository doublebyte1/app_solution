#include "frmregions.h"

FrmRegions::FrmRegions(QWidget *parent, Qt::WFlags flags):
SecondaryFrm(parent, flags){

    setupUi(this);

    connect(pushClose, SIGNAL(clicked()), this,
    SIGNAL(hideFrm()));

    treePtr=0;
    reload();
    //if (!readXML()) emit showError(tr("Could not read XML Fr_Tree from database!"));
    //else emit showStatus(tr("Finished reading XML Fr_Tree from Database"));
}

FrmRegions::~FrmRegions()
{
    if (treePtr!=0) delete treePtr;
}

void FrmRegions::Ok()
{
    if (!treePtr) return;

    if (!writeXML()) emit showError(tr("Could not write XML document from tree!"));
    else emit showStatus(tr("Finished writing XML Tree from application"));
}

void FrmRegions::reload()
{
    //Initialize Tree
    treeWidget->clear();
    if (treePtr!=0){
        delete treePtr;
        treePtr=0;
    }
    treePtr=new Tree(treeWidget);

    if (!readXML()) emit showError(tr("Could not read XML tree from database!"));
    else emit showStatus(tr("Finished reading XML Tree from Database"));
}

bool FrmRegions::writeXML()
{
    bool bOk;
    QString strXml;
    bOk=treePtr->writeXML(&strXml);

#ifdef _DEBUG
    QFile file("tree.xml");
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return false;
    file.write(strXml.toAscii(), qstrlen(strXml.toAscii()));        // write to stderr
    file.close();
#endif

    MapNodes mapNodes;
    MapProperties mapProperties;
    MapProperties mapFields;
    if (!treePtr->writeNestedModel(mapNodes,mapProperties,mapFields)) bOk=false;
    if (!createDBModel(mapNodes,mapProperties,mapFields)) bOk=false;

    return bOk;
}

bool FrmRegions::insertDBLevel(const int id, const MapProperties& mapProperties, const MapProperties& mapFields)
{
    //! Insert New Level
    /*!
    This function initializes a new Level (Fr_Node_Description table);
    at the same time, the Tree table, with the topology of the model is also filled;
    n.b.: id is inserted automatically as identity value!
    \par mapFields container with the fields;
    \par mapProperties container with the properties (e.g.: name, name_eng, description)
    \return booleans as success or failure
    \sa insertNodeIntoDBTree(const size_t lft, const size_t rgt)
    */

    QString strQuery=tr("INSERT INTO Fr_Node_Description (");

    //loop to construct the string
    MapProperties::const_iterator it = mapFields.find(0);//n.b.: be carefull because the property container only has one record!
    while (it != mapFields.end() && it.key() == 0) {
            strQuery.append(it.value().toString());
            strQuery.append(tr(","));
        ++it;
    }
    strQuery.remove(strQuery.length()-1,1);//Remove last coma!
    strQuery.append(tr(") VALUES ("));
    for (size_t i=0; i < (size_t)mapFields.count(); ++i)    strQuery.append(tr("?,"));
    strQuery.remove(strQuery.length()-1,1);//Remove last coma!
    strQuery.append(tr(")"));

    //loop to bind the values
    QSqlQuery query;
    query.prepare(strQuery);

    it = mapProperties.find(id);
    while (it != mapProperties.end() && it.key() == id) {
        QString str=it.value().toString();
        str.remove(tr("\""));//Remove quotes from XML
        query.addBindValue(str);
        ++it;
    }
    query.exec();

    return query.numRowsAffected()>0;
}

bool FrmRegions::insertNodeIntoDBTree(const size_t lft, const size_t rgt)
{
    //! Insert Record into Tree
    /*!
    This function creates the reference table for the Nested Set Model (Tree), by filling
    the values: lft,rgt and id; at the same time, the Fr_Node_Description table is also filled;
    n.b.: id is inserted automatically as identity value!
    \par lft left value of the node on Celko's Nested Model;
    \par rgt right value of the node on Celko's Nested Model;
    \return booleans as success or failure
    \sa insertDBLevel(const int id, const MapProperties& mapProperties, const MapProperties& mapFields)
    */

    //Query for LEFT AND RIGHT
    QSqlQuery query;
    QString strQuery=tr("INSERT INTO Fr_Tree (lft,rgt,depth) VALUES(?,?,-1)");
    query.prepare(strQuery);
    query.addBindValue(lft);
    query.addBindValue(rgt);
    query.exec();
    return query.numRowsAffected()>0;
}

bool FrmRegions::updateParent(const int id)
{
    //! Update Parent Node
    /*!
    This function transforms the nested set model into an adjacency model, by filling the parent value;
    For that we use a self join query, using left and right values of the node to find the hierarchy.
    N.b: This function affects one record *only*!
    \par id id of the node.
    \return booleans as success or failure
    */

    //Query for Parent
    QSqlQuery query;
    QString strQuery=tr("SELECT TOP (1) hp.id as parent FROM Fr_Tree hc JOIN Fr_Tree hp ON hc.lft BETWEEN hp.lft AND hp.rgt WHERE hc.id=? AND hp.id<>? ORDER BY hp.lft DESC");
    query.prepare(strQuery);
    query.addBindValue(id);
    query.addBindValue(id);
    query.exec();

    int result;
    //It has a parent
    if (query.numRowsAffected()>0){
        query.first();
        result=query.value(query.record().indexOf(tr("parent"))).toInt();
    }else//It's the root
        result=-1;

    //Update
    strQuery=tr("UPDATE Fr_Tree Set parent=? WHERE id=?");
    query.prepare(strQuery);
    query.addBindValue(result);
    query.addBindValue(id);
    query.exec();

    return query.numRowsAffected()==1;
}

bool FrmRegions::createDBModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields)
{
    //! Creates Database Model from the Tree
    /*!
    This function initializes tables Tree and Fr_Node_Description from the Tree structure;
    This tables are connected and should be filled on one block, as they reflect the 
    topology and content of the Nested Set Model, and for this reason it is *desirable* to use this instead of
    updateDBModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields)
    In this function, we also update extra fields
    parent (with the node ancestor) and depth (indentation).
    \par mapFields container with the fields;
    \par mapProperties container with the properties (e.g.: name, name_eng, description)
    \return booleans as success or failure
    \sa updateDBModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields)
    */

    //clean Table(s)
    if (!clearDBTable(tr("Fr_Tree"))) return false;
    if (!clearDBTable(tr("Fr_Node_Description"))) return false;

    QString strQuery;

    MapNodes::const_iterator itt;
    for (itt = mapNodes.constBegin(); itt != mapNodes.constEnd(); ++itt){

        if (!insertDBLevel(itt.key(),mapProperties,mapFields)) return false;
        if (!insertNodeIntoDBTree(itt.value().m_lft,itt.value().m_rgt)) return false;
        if (!updateParent(itt.key())) return false;
        if(!updateDepth(itt.key())) return false;

    }

    return true;
}

bool FrmRegions::updateDBModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields)
{
    //! Updates Database Model from the Tree
    /*!
    This function uses sql queries to update the database representation of the tree;
    It supports changes only on the non-topological properties (Fr_Node_Description): name, name_eng and description
    \return booleans as success or failure
    \sa createDBModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields)
    */

    QString strQuery;

    MapNodes::const_iterator itt;
    for (itt = mapNodes.constBegin(); itt != mapNodes.constEnd(); ++itt){

        strQuery=tr("UPDATE Fr_Node_Description SET ");

        //loop to construct the string
        MapProperties::iterator it = mapFields.find(0);//n.b.: be carefull because the property container only has one record!
        while (it != mapFields.end() && it.key() == 0) {
                strQuery.append(it.value().toString());
                strQuery.append(tr("=?,"));
            ++it;
        }
        strQuery.remove(strQuery.length()-1,1);//Remove last coma!
        strQuery.append(tr(" WHERE id=?"));

        //loop to bind the values
        QSqlQuery query;
        query.prepare(strQuery);

        it = mapProperties.find(itt.key());
        while (it != mapProperties.end() && it.key() == itt.key()) {
            QString str=it.value().toString();
            str.remove(tr("\""));//Remove quotes from XML
            query.addBindValue(str);
            ++it;
        }

        query.addBindValue(itt.key());
        query.exec();
        if (query.numRowsAffected() <1) return false;

        //Query for LEFT AND RIGHT
        strQuery=tr("UPDATE Fr_Tree SET lft=?, rgt=? WHERE id=?");
        query.prepare(strQuery);
        query.addBindValue(itt.value().m_lft);
        query.addBindValue(itt.value().m_rgt);
        query.addBindValue(itt.key());

        query.exec();
        if (query.numRowsAffected() <1) return false;
    }
    return true;
}

bool FrmRegions::readXML()
{
    //! Creates an XML document from a Tree
    /*!
    This function executes an sql statement that transforms the nested set representation
    of a tree in a XML document.
    \return booleans as success or failure
    */
    //QString strQuery=tr("SELECT xml1.xmltext FROM (SELECT lft, xmltext = '<node id=\"' + CAST(Fr_Node_Description.id AS nvarchar(50)) + '\"><name>\"' + Fr_Node_Description.name + '\"</name>' + '<name_eng>\"' + Fr_Node_Description.name_eng + '\"</name_eng>' + '<description>\"' + Fr_Node_Description.description + '\"</description>' FROM Fr_Tree INNER JOIN Fr_Node_Description ON Fr_Tree.id=Fr_Node_Description.id UNION ALL SELECT rgt, xmltext = '</node>' FROM Fr_Tree) AS xml1 ORDER BY xml1.lft"
    QString strQuery=tr("SELECT xml1.xmltext FROM (SELECT lft, xmltext = '<node id=\"' + CAST(Fr_Node_Description.id AS nvarchar(50)) + '\"><name>\"' + Fr_Node_Description.name + '\"</name>' + '<name_eng>\"' + Fr_Node_Description.name_eng + '\"</name_eng>' + '<description>\"' + Fr_Node_Description.description + '\"</description>'+ '<OLD_CODE>\"' + Fr_Node_Description.OLD_CODE + '\"</OLD_CODE>' FROM Fr_Tree INNER JOIN Fr_Node_Description ON Fr_Tree.id=Fr_Node_Description.id UNION ALL SELECT rgt, xmltext = '</node>' FROM Fr_Tree) AS xml1 ORDER BY xml1.lft"
        );
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    if (!query.exec()) return false;

    QString strXml;
    QXmlStreamWriter xml;
    QByteArray data;
    QBuffer buffer;
    buffer.setBuffer(&data);
    buffer.open(QBuffer::ReadWrite);
    xml.setDevice(&buffer);
    xml.writeStartDocument();

    strXml.append(data.data());
    while (query.next()) {
       strXml.append(query.value(0).toString());
    }

    buffer.close();

    /* // DEBUG CODE
    QFile file(tr("dump.xml"));
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(strXml.toAscii());
    file.close();
    */

   return treePtr->readXML(&strXml);
}

