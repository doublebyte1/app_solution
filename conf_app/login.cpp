#include "login.h"

static QString strUsername="admin";
static QString strPassword="adminXyz";

Login::Login(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags){

    m_conf_app=0;
    m_frmTip=0;
    setupUi(this);

}

Login::~Login()
{
    /*!
    //Clean Pointers here!
    */
    if (m_conf_app!=0) delete m_conf_app;
    if (m_frmTip!=0) delete m_frmTip;
}

void Login::loadForms()
{
        hide();
        if (m_conf_app==0) m_conf_app=new conf_app();
        m_conf_app->show();
        m_conf_app->repaint();

        if (queryShowStartupMsg()){
            if (m_frmTip==0) m_frmTip=new FrmTip();
            m_frmTip->show();
            m_frmTip->repaint();

           connect(this->m_frmTip, SIGNAL(showStartupMsg(bool)), m_conf_app,
                SLOT(onShowStartupMsgI(bool)));
        }
}

void Login::validate()
{
    bool gotUser=lineUser->text().compare(strUsername)==0;
    bool gotPasswd=linePasswd->text().compare(strPassword)==0;

    if (!gotUser){
            QMessageBox msgBox(QMessageBox::Critical,tr("Authentication Error"),
                tr("Wrong username!"),QMessageBox::Ok,0);
            msgBox.exec();
    } else if (!gotPasswd){
            QMessageBox msgBox(QMessageBox::Critical,tr("Authentication Error"),
                tr("Wrong password!"),QMessageBox::Ok,0);
            msgBox.exec();
    }else{
        loadForms();
    }
}