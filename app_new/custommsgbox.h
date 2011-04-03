#ifndef CUSTOMMSGBOX_H
#define CUSTOMMSGBOX_H

#include <QtGui>
#include "ui_msgbox.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! CustomMsgBox Class
/*!
//This custom msgbox is used to display errors to the user, without exiting the event loop;
regular messageboxes, exit the event loop, causing the application to crash on errors;
I don't know why, but the icon does not come ok when inside Visual Studio (bug?)!
*/

class CustomMsgBox: public QDialog, public Ui::CustomMsgBoxDialog
{
	Q_OBJECT

	public:
		CustomMsgBox(QWidget *parent = 0);
		~CustomMsgBox();

		void fillDialog(QString strTitle, QString strMessage);

};

#endif // CUSTOMMSGBOX_H
