#ifndef TREE_H
#define TREE_H

#include <QtSql>
#include <QtGui>

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

#define EMPTY -1 //!< This is the null value, for left/right properties of the node

struct node {
    //! Constructor.
        /*!
        */
    node(int lft=EMPTY, int rgt=EMPTY, int parent=EMPTY):m_lft(lft),
        m_rgt(rgt), m_parent(parent)
    {}
    void               setLft(int lft){m_lft=lft;}
    void               setRgt(int rgt){m_rgt=rgt;}
    void               setParent(int parent){m_parent=parent;}

    int             m_lft;
    int             m_rgt;
    int             m_parent;
};

/////////////////////////////////////////////
typedef QMap<size_t,node>                   MapNodes;//!< typedef for storing a list of nodes, with left and right values
typedef QMultiMap<size_t,QVariant>          MapProperties;//!< typedef for storing the properties of the nodes

//! Tree Class
/*!
This class generates an XML structure, with the tree from the Database
*/

class Tree
{
    public:
        Tree(QTreeWidget *treeWidget);
        ~Tree();

        bool                    readXML(QString* data);
        //! Write XML
        /*!
        TODO: addd description to this later
        */
        bool                    writeXML(QString* strXml);
        bool                    writeNestedModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields);

    private:
        bool                    readFields(QTreeWidgetItem *item, MapProperties& mapFields);
        bool                    readNode(QTreeWidgetItem *item);
        bool                    readLeafNode(QTreeWidgetItem *item);
        QTreeWidgetItem         *createChildItem(QTreeWidgetItem *item);
        bool                    writeItem(QTreeWidgetItem *item);
        bool                    writeProperty(QTreeWidgetItem *item);
        bool                    transverseTree(QTreeWidgetItem *item, MapNodes& mapNodes, MapProperties& mapProperties, int& cnt);
        bool                    mapProperty(QTreeWidgetItem *item, MapProperties& mapProperties, const size_t id);

        QXmlStreamReader        xmlr;
        QXmlStreamWriter        xmlw;
        QTreeWidget             *treeWidget;
        QIcon                   folderIcon;
        QStringList             m_propertyList;

};

#endif // TREE_H

