/********************************************************************************
** Form generated from reading UI file 'frmconnect.ui'
**
** Created: Thu 26. May 16:39:37 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCONNECT_H
#define UI_FRMCONNECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_frmconnect
{
public:
    QGridLayout *gridLayout;
    QLabel *lbHost;
    QLineEdit *lineHost;
    QVBoxLayout *vboxLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem;
    QLabel *lbDataSource;
    QLineEdit *lineDataSource;
    QLabel *lbUsername;
    QLineEdit *lineUsername;
    QLabel *lbPassword;
    QLineEdit *linePassword;
    QLabel *lbAlias;
    QLineEdit *lineAlias;
    QLabel *lbDriver;
    QComboBox *cmbDriver;

    void setupUi(QDialog *frmconnect)
    {
        if (frmconnect->objectName().isEmpty())
            frmconnect->setObjectName(QString::fromUtf8("frmconnect"));
        frmconnect->setWindowModality(Qt::ApplicationModal);
        frmconnect->resize(394, 230);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/medfisis.ico"), QSize(), QIcon::Normal, QIcon::Off);
        frmconnect->setWindowIcon(icon);
        gridLayout = new QGridLayout(frmconnect);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbHost = new QLabel(frmconnect);
        lbHost->setObjectName(QString::fromUtf8("lbHost"));
        lbHost->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbHost, 0, 0, 1, 1);

        lineHost = new QLineEdit(frmconnect);
        lineHost->setObjectName(QString::fromUtf8("lineHost"));

        gridLayout->addWidget(lineHost, 0, 1, 1, 1);

        vboxLayout = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        okButton = new QPushButton(frmconnect);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon1);

        vboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(frmconnect);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon2);

        vboxLayout->addWidget(cancelButton);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);


        gridLayout->addLayout(vboxLayout, 0, 2, 3, 1);

        lbDataSource = new QLabel(frmconnect);
        lbDataSource->setObjectName(QString::fromUtf8("lbDataSource"));
        lbDataSource->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbDataSource, 1, 0, 1, 1);

        lineDataSource = new QLineEdit(frmconnect);
        lineDataSource->setObjectName(QString::fromUtf8("lineDataSource"));

        gridLayout->addWidget(lineDataSource, 1, 1, 1, 1);

        lbUsername = new QLabel(frmconnect);
        lbUsername->setObjectName(QString::fromUtf8("lbUsername"));
        lbUsername->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbUsername, 2, 0, 1, 1);

        lineUsername = new QLineEdit(frmconnect);
        lineUsername->setObjectName(QString::fromUtf8("lineUsername"));

        gridLayout->addWidget(lineUsername, 2, 1, 1, 1);

        lbPassword = new QLabel(frmconnect);
        lbPassword->setObjectName(QString::fromUtf8("lbPassword"));

        gridLayout->addWidget(lbPassword, 3, 0, 1, 1);

        linePassword = new QLineEdit(frmconnect);
        linePassword->setObjectName(QString::fromUtf8("linePassword"));
        linePassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(linePassword, 3, 1, 1, 1);

        lbAlias = new QLabel(frmconnect);
        lbAlias->setObjectName(QString::fromUtf8("lbAlias"));
        lbAlias->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbAlias, 4, 0, 1, 1);

        lineAlias = new QLineEdit(frmconnect);
        lineAlias->setObjectName(QString::fromUtf8("lineAlias"));

        gridLayout->addWidget(lineAlias, 4, 1, 1, 1);

        lbDriver = new QLabel(frmconnect);
        lbDriver->setObjectName(QString::fromUtf8("lbDriver"));

        gridLayout->addWidget(lbDriver, 5, 0, 1, 1);

        cmbDriver = new QComboBox(frmconnect);
        cmbDriver->setObjectName(QString::fromUtf8("cmbDriver"));

        gridLayout->addWidget(cmbDriver, 5, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        lbHost->setBuddy(lineHost);
        lbDataSource->setBuddy(lineDataSource);
        lbUsername->setBuddy(lineUsername);
        lbPassword->setBuddy(linePassword);
        lbAlias->setBuddy(lineAlias);
        lbDriver->setBuddy(cmbDriver);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineHost, lineDataSource);
        QWidget::setTabOrder(lineDataSource, lineUsername);
        QWidget::setTabOrder(lineUsername, linePassword);
        QWidget::setTabOrder(linePassword, lineAlias);
        QWidget::setTabOrder(lineAlias, cmbDriver);
        QWidget::setTabOrder(cmbDriver, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(frmconnect);
        QObject::connect(okButton, SIGNAL(clicked()), frmconnect, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), frmconnect, SLOT(reject()));

        QMetaObject::connectSlotsByName(frmconnect);
    } // setupUi

    void retranslateUi(QDialog *frmconnect)
    {
        frmconnect->setWindowTitle(QApplication::translate("frmconnect", "Connect to Database", 0, QApplication::UnicodeUTF8));
        lbHost->setText(QApplication::translate("frmconnect", "Host", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("frmconnect", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("frmconnect", "Cancel", 0, QApplication::UnicodeUTF8));
        lbDataSource->setText(QApplication::translate("frmconnect", "Data Source", 0, QApplication::UnicodeUTF8));
        lbUsername->setText(QApplication::translate("frmconnect", "Username", 0, QApplication::UnicodeUTF8));
        lbPassword->setText(QApplication::translate("frmconnect", "Password", 0, QApplication::UnicodeUTF8));
        lbAlias->setText(QApplication::translate("frmconnect", "Alias", 0, QApplication::UnicodeUTF8));
        lbDriver->setText(QApplication::translate("frmconnect", "Driver", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmconnect: public Ui_frmconnect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCONNECT_H
