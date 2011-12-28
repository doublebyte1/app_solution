/********************************************************************************
** Form generated from reading UI file 'frmTip.ui'
**
** Created: Wed 28. Dec 09:37:46 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTIP_H
#define UI_FRMTIP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_frmtip
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushOk;
    QCheckBox *checkShow;

    void setupUi(QDialog *frmtip)
    {
        if (frmtip->objectName().isEmpty())
            frmtip->setObjectName(QString::fromUtf8("frmtip"));
        frmtip->setWindowModality(Qt::ApplicationModal);
        frmtip->resize(400, 180);
        verticalLayout = new QVBoxLayout(frmtip);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(frmtip);
        label->setObjectName(QString::fromUtf8("label"));
        label->setTextFormat(Qt::LogText);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        pushOk = new QPushButton(frmtip);
        pushOk->setObjectName(QString::fromUtf8("pushOk"));

        verticalLayout->addWidget(pushOk);

        checkShow = new QCheckBox(frmtip);
        checkShow->setObjectName(QString::fromUtf8("checkShow"));
        checkShow->setChecked(false);

        verticalLayout->addWidget(checkShow);


        retranslateUi(frmtip);
        QObject::connect(pushOk, SIGNAL(clicked()), frmtip, SLOT(accept()));

        QMetaObject::connectSlotsByName(frmtip);
    } // setupUi

    void retranslateUi(QDialog *frmtip)
    {
        frmtip->setWindowTitle(QApplication::translate("frmtip", "Welcome", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmtip", "Welcome to the Medfisis Configurator! \n"
" Here you can change the connection settings, and costumize global settings of the database (such as the location).\n"
" All the values will be stored in the registry for use of all the products of the Medfisis suite.\n"
" If you do not wish to see this message again, please make sure to check the box bellow.", 0, QApplication::UnicodeUTF8));
        pushOk->setText(QApplication::translate("frmtip", "OK", 0, QApplication::UnicodeUTF8));
        checkShow->setText(QApplication::translate("frmtip", "Don't show this again", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmtip: public Ui_frmtip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTIP_H
