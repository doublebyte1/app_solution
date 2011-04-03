#ifndef FRMCONNECT_H
#define FRMCONNECT_H

#include <QtGui>
#include <QtSql>
#include "ui_frmconnect.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! Connect Class
/*!
This class contains an instantiation of the UI FrmConnect class;
This is where we stablish the connection string.
*/

class FrmConnect : public QDialog, public Ui::frmconnect
{
	Q_OBJECT

	public:
		FrmConnect(QWidget *parent = 0, Qt::WFlags flags = 0);
		~FrmConnect();

	signals:
		void ok(const QString& strHost,const QString& strDataSource,
			const QString& strUsername,const QString& strPassword,const QString& strAlias, const QString& strDriver);

	public slots:
		void accept();
		void reject();

};

#endif // FRMCONNECT_H

