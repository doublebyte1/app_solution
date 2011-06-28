#include "tree.h"

//Static constants for translating
static const char *StatStrRegions = QT_TRANSLATE_NOOP("Tree", "Regions");
static const char *StatStrNode = QT_TRANSLATE_NOOP("Tree", "node");
static const char *statStrId = QT_TRANSLATE_NOOP("Tree", "id");
static const char *statStrP1 = QT_TRANSLATE_NOOP("Tree", "name");
static const char *statStrP2 = QT_TRANSLATE_NOOP("Tree", "name_eng");
static const char *statStrP3 = QT_TRANSLATE_NOOP("Tree", "description");
static const char *statStrP4 = QT_TRANSLATE_NOOP("Tree", "OLD_CODE");

Tree::Tree(QTreeWidget *treeWidget)
: treeWidget(treeWidget){

    QStringList labels;
    labels << StatStrRegions;

    treeWidget->header()->setResizeMode(QHeaderView::Stretch);
    treeWidget->setHeaderLabels(labels);

    folderIcon.addPixmap(QPixmap(QString::fromUtf8(":/app_new/konqueror.png")),
        QIcon::Normal, QIcon::On);

    folderIcon.addPixmap(QPixmap(QString::fromUtf8(":/app_new/kget.png")),
                         QIcon::Normal, QIcon::Off);

    //treeWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
    m_propertyList << statStrP1 << statStrP2 << statStrP3 << statStrP4;

}

Tree::~Tree()
{

}

bool Tree::writeNestedModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields)
{
    //! Converts an XML Tree into a Nested Set Model
    /*!
    This function reads the DOM model and converts it into a map with ids and
    left, right values that allow to recreate the Nested Model in the database.
    \return booleans as success or failure
    */

    bool bOk=true;

    //reset containers
    if (mapNodes.size()>0) mapNodes.clear();
    if (mapProperties.size()>0) mapProperties.clear();
    if (mapFields.size()>0) mapFields.clear();

    int i=0;

    if (!readFields(treeWidget->topLevelItem(0),mapFields)) bOk=false;
    if (!transverseTree(treeWidget->topLevelItem(0),mapNodes,mapProperties,i)) bOk=false;

    return bOk;
}

bool Tree::readFields(QTreeWidgetItem *item, MapProperties& mapFields)
{
    //! Read Fields from Top-Level Item
    /*!
    We want to store the field names in the same kind of container where
    we store the properties, so the *order* is the same!
    \return booleans as success or failure
    */
    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == StatStrNode) {
        for (int i = 0; i < item->childCount(); ++i){
            QString tagName = item->child(i)->data(0, Qt::UserRole).toString();
            if (tagName != StatStrNode && m_propertyList.size()>0 && m_propertyList.contains(
                tagName)){
                    mapFields.insertMulti(0,tagName);
            }//if
        }//for
    }//if

    return true;
}

bool Tree::transverseTree(QTreeWidgetItem *item, MapNodes& mapNodes, MapProperties& mapProperties, int& cnt)
{
    bool bOk=true;

    ++cnt;

    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == StatStrNode) {
        size_t id=item->text(0).toInt();


        mapNodes.insert(id,node(cnt));// Left
        //And recursively write siblings
        for (int i = 0; i < item->childCount(); ++i){
            QString tagName = item->child(i)->data(0, Qt::UserRole).toString();
            if (tagName == StatStrNode) {
                if (!transverseTree(item->child(i),mapNodes,mapProperties,cnt)) bOk=false;
            }//if
            else{
                if (!mapProperty(item->child(i),mapProperties,id)) bOk=false;
            }
        }//for
        ++cnt;
        if (mapNodes.find(item->text(0).toInt())==mapNodes.end()) return false;
        mapNodes.find(item->text(0).toInt()).value().setRgt(cnt);
    }//if

    return bOk;
}

bool Tree::mapProperty(QTreeWidgetItem *item, MapProperties& mapProperties,const size_t id)
{
    //N.b: Be carefull with order: most recent item comes last!
    if (m_propertyList.size()>0 && m_propertyList.contains(
        item->data(0, Qt::UserRole).toString()
        ))
            mapProperties.insertMulti(id,item->text(0));

    return true;
}

bool Tree::readXML(QString* data)
{
    treeWidget->clear();//reset tree
    xmlr.addData(*data);

    xmlr.readNextStartElement();
    return readNode(0);
}

bool Tree::readNode(QTreeWidgetItem *item)
{
    bool bOk=true;

    if (xmlr.name()==StatStrNode){
        QTreeWidgetItem *child = createChildItem(item);
        child->setFlags(child->flags() | Qt::ItemIsEditable);
        child->setText(0, xmlr.attributes().value(statStrId).toString());
        child->setIcon(0, folderIcon);
        treeWidget->setItemExpanded(child, true);

        while (xmlr.readNextStartElement()) {
            if (!readNode(child)) bOk=false;
        }
    }
    else if (!readLeafNode(item)) bOk=false;

    return bOk;
}

bool Tree::readLeafNode(QTreeWidgetItem *item)
{
    bool bOk=true;

    //Checks if its an "authorized" property!
    if (m_propertyList.size()>0 && m_propertyList.contains(xmlr.name().toString())){
        QTreeWidgetItem *child = createChildItem(item);
        child->setFlags(child->flags() | Qt::ItemIsEditable);
        QString title = xmlr.readElementText();
        child->setText(0, title);
        treeWidget->setItemExpanded(child, true);
    }

    return bOk;
}

QTreeWidgetItem *Tree::createChildItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *childItem;
    if (item) {
        childItem = new QTreeWidgetItem(item);
    } else {
        childItem = new QTreeWidgetItem(treeWidget);
    }
    childItem->setData(0, Qt::UserRole, xmlr.name().toString());
    return childItem;
}

bool Tree::writeXML(QString* strXml)
{
    QByteArray data;
    QBuffer buffer;
    buffer.setBuffer(&data);
     buffer.open(QBuffer::ReadWrite);
     xmlw.setDevice(&buffer);

    xmlw.writeStartDocument();
    writeItem(treeWidget->topLevelItem(0));

    xmlw.writeEndDocument();

    *strXml= data.data();

    buffer.close();
    return true;
}

bool Tree::writeProperty(QTreeWidgetItem *item)
{
    if (m_propertyList.size()>0 && m_propertyList.contains(
        item->data(0, Qt::UserRole).toString()
        )){
            xmlw.writeTextElement(item->data(0, Qt::UserRole).toString(), item->text(0));
    }
    return true;
}

bool Tree::writeItem(QTreeWidgetItem *item)
{
    bool bOk=true;

    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == StatStrNode) {
        xmlw.writeStartElement(tagName);
        xmlw.writeAttribute(statStrId, item->text(0));

        //And recursively write siblings
        for (int i = 0; i < item->childCount(); ++i){
            QString tagName = item->child(i)->data(0, Qt::UserRole).toString();
            if (tagName == StatStrNode) {
                if (!writeItem(item->child(i))) bOk=false;
            }//if
            else
                writeProperty(item->child(i));
        }//for
        xmlw.writeEndElement();
    }//if

    return bOk;
}