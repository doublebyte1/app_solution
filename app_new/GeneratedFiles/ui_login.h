/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Wed 28. Dec 09:48:15 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmLogin
{
public:
    QGridLayout *gridLayout;
    QLabel *lbUser;
    QLabel *lbPasswd;
    QLineEdit *linePasswd;
    QPushButton *pushLogin;
    QComboBox *cmbUser;

    void setupUi(QWidget *frmLogin)
    {
        if (frmLogin->objectName().isEmpty())
            frmLogin->setObjectName(QString::fromUtf8("frmLogin"));
        frmLogin->setWindowModality(Qt::ApplicationModal);
        frmLogin->resize(293, 136);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frmLogin->sizePolicy().hasHeightForWidth());
        frmLogin->setSizePolicy(sizePolicy);
        frmLogin->setMaximumSize(QSize(293, 306));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/medfisis.ico"), QSize(), QIcon::Normal, QIcon::Off);
        frmLogin->setWindowIcon(icon);
        gridLayout = new QGridLayout(frmLogin);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbUser = new QLabel(frmLogin);
        lbUser->setObjectName(QString::fromUtf8("lbUser"));

        gridLayout->addWidget(lbUser, 0, 0, 1, 1);

        lbPasswd = new QLabel(frmLogin);
        lbPasswd->setObjectName(QString::fromUtf8("lbPasswd"));

        gridLayout->addWidget(lbPasswd, 1, 0, 1, 1);

        linePasswd = new QLineEdit(frmLogin);
        linePasswd->setObjectName(QString::fromUtf8("linePasswd"));
        linePasswd->setAutoFillBackground(true);
        linePasswd->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(linePasswd, 1, 2, 1, 1);

        pushLogin = new QPushButton(frmLogin);
        pushLogin->setObjectName(QString::fromUtf8("pushLogin"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushLogin->sizePolicy().hasHeightForWidth());
        pushLogin->setSizePolicy(sizePolicy1);
        pushLogin->setAutoFillBackground(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/password.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushLogin->setIcon(icon1);
        pushLogin->setIconSize(QSize(16, 16));
        pushLogin->setAutoDefault(true);

        gridLayout->addWidget(pushLogin, 2, 2, 1, 1);

        cmbUser = new QComboBox(frmLogin);
        cmbUser->setObjectName(QString::fromUtf8("cmbUser"));

        gridLayout->addWidget(cmbUser, 0, 2, 1, 1);

#ifndef QT_NO_SHORTCUT
        lbPasswd->setBuddy(linePasswd);
#endif // QT_NO_SHORTCUT

        retranslateUi(frmLogin);
        QObject::connect(pushLogin, SIGNAL(clicked()), frmLogin, SLOT(validate()));

        QMetaObject::connectSlotsByName(frmLogin);
    } // setupUi

    void retranslateUi(QWidget *frmLogin)
    {
        frmLogin->setWindowTitle(QApplication::translate("frmLogin", "Login", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        frmLogin->setToolTip(QApplication::translate("frmLogin", "Login Dialog", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        frmLogin->setWhatsThis(QApplication::translate("frmLogin", "This is a login dialog.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        lbUser->setText(QApplication::translate("frmLogin", "Username", 0, QApplication::UnicodeUTF8));
        lbPasswd->setText(QApplication::translate("frmLogin", "Password", 0, QApplication::UnicodeUTF8));
        pushLogin->setText(QApplication::translate("frmLogin", "Login", 0, QApplication::UnicodeUTF8));
        pushLogin->setShortcut(QApplication::translate("frmLogin", "Ctrl+L", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmLogin: public Ui_frmLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
