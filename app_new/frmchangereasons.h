#ifndef FRMCHANGEREASONS_H
#define FRMCHANGEREASONS_H

#include <QtGui>
#include <QtSql>
#include "ui_frmchangereasons.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////

//! Frm Change Reasons Class
/*!
This class implements the widget that is shown each time we move
nodes around the tree widget; it connects with the database structure that
stores the reasons for this temporary or permanent change.
*/

class FrmChangeReasons : public QDialog, public Ui::FrmChangeReasons
{
    Q_OBJECT

    public:
        FrmChangeReasons(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmChangeReasons();

        void            setVesselReasons(const bool bVessel){m_VesselReasons=bVessel;};
        bool            getDbIndex(int& id);

    protected:
        void    showEvent ( QShowEvent * event );

    private slots:

    private:
        void             init();
        bool             m_VesselReasons;
        QSqlTableModel*  tChanges;

};
#endif //FRMCHANGEREASONS_H