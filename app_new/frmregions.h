#ifndef FRMREGIONS_H
#define FRMREGIONS_H

#include <QtGui>
#include <QtSql>
#include "ui_frmregions.h"
#include "tree.h"
#include "generictab.h"
#include "sql.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! Regions Class
/*!
This is the form that contains the region setup;
it queries the database and creates trees from XML generated from the Nested Set Model.
*/

class SecondaryFrm;

class FrmRegions : public SecondaryFrm, public Ui::frmRegions
{
    Q_OBJECT

    public:
        FrmRegions(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmRegions();

    private:
        bool        readXML();
        bool        writeXML();
        bool        updateDBModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields);
        bool        createDBModel(MapNodes& mapNodes, MapProperties& mapProperties, MapProperties& mapFields);
        bool        insertDBLevel(const int id, const MapProperties& mapProperties, const MapProperties& mapFields);
        bool        insertNodeIntoDBTree(const size_t lft, const size_t rgt);
        bool        updateParent(const int id);

        Tree*       treePtr;

    private slots:
        void        Ok();
        //TODO: maybe implement and undo later
        void        reload();

};

#endif // FRMREGIONS_H

