#include <QtGui>
#include <QtSql>
#include "generictab.h"
#include "ui_frmreports.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef FRMREPORTS_H
#define FRMREPORTS_H

class SecondaryFrm;

//! Frm Reports Class
/*!
This class implements a form where we can load reports, using the Exaro report engine;
*/

class FrmReports : public SecondaryFrm, public Ui::frmreports
{
    Q_OBJECT

    public:
        FrmReports(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmReports();

    private slots:
        void                        browseFiles();
        void                        previewItem(QListWidgetItem* item);
        void                        loadItem(QListWidgetItem* item);
        void                        loadItem(const QString strFilename);

    private:
        void                        showEvent ( QShowEvent * event );
        bool                        readReportNames ();
        bool                        parseXMLFile(const QString itemName, QString& strName, QString& strAuthor,
                                                        QString& strPixmap, QString& strDescription);
        bool                        readProperties(QXmlStreamReader& xml, QString& strName, QString& strAuthor, QString& 
                                                        strPixmap, QString& strDescription);
};
#endif //FRMREPORTS_H