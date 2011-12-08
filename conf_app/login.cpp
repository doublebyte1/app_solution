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
    QString strError;
    QString strStyleSheet="background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));";
    bool gotUser=lineUser->text().compare(strUsername)==0;
    bool gotPasswd=linePasswd->text().compare(strPassword)==0;

    lineUser->setStyleSheet("");
    linePasswd->setStyleSheet("");

    if (!gotUser){
            lineUser->setStyleSheet(strStyleSheet);
            strError=tr("Wrong username!");
            QMessageBox msgBox(QMessageBox::Critical,tr("Authentication Error"),
            strError,QMessageBox::Ok,0);
            msgBox.exec();
    } 
    if (!gotPasswd){
            linePasswd->setStyleSheet(strStyleSheet);
            strError=tr("Wrong password!");
            QMessageBox msgBox(QMessageBox::Critical,tr("Authentication Error"),
            strError,QMessageBox::Ok,0);
            msgBox.exec();
    }if (gotUser && gotPasswd){
        loadForms();
    }

}