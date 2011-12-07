#include <QtGui>
#include <QtSql>
#include "conf_app.h"
#include "frmtip.h"

#include "ui_login.h"

#ifndef LOGIN_H
#define LOGIN_H

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! Login Class
/*!
This class contains an instantiation of the UI Login class;
This is the actual the startup of our application! It is very simple class
and it has only one method: "validate" where it validates the username and password
agains the static strings stored in the implementation of this class; if everything
 goes ok, we can show the next forms (conf_app and eventually frmTip)
*/

class Login : public QWidget, public Ui::frmLogin
{
    Q_OBJECT

    public:
        Login(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~Login();

    public slots:
        //! Validate
        /*! This method validates the username and password provided
        */
        void                                validate();
        //! Load Forms
        /*! This method loads the main form of the application (and eventually an information dialog!)
        */
        void                                loadForms();

    private:
        conf_app*                           m_conf_app;//!< Pointer to the main form
        FrmTip*                             m_frmTip;//!< Pointer to the information dialog

};

#endif // LOGIN_H
