#ifndef FRMIMPORTREGIONS_H
#define FRMIMPORTREGIONS_H

#include <QtGui>
#include <QtSql>
#include "ui_frmImportRegions.h"
#include "generictab.h"
#include "sql.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

class SecondaryFrm;

//! Import Regions Class
/*!
This is the form that allows us to collect parameters for converting
a generic Adjacency Model to a Nested Set Model (Celkos, J.);
*/

class FrmImportRegions : public SecondaryFrm, public Ui::frmImportRegions
{
    Q_OBJECT

    public:
        FrmImportRegions(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmImportRegions();

    private:
        void                    showEvent ( QShowEvent * event );
        void                    Init();
        int                     m_ctr;//!< It's better to allow an int here, than a size_t since we want to allow negative levels...
        HashNodeRef              m_mapTablesFields;

    private slots:
        void                    Apply();
        void                    Cancel();
        void                    adjustButtons();
        void                    refreshFields(QString strTable);
        void                    addItems2List();
};

#endif // FRMIMPORTREGIONS_H

