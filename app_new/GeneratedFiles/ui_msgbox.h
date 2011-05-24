/********************************************************************************
** Form generated from reading UI file 'msgbox.ui'
**
** Created: Tue 24. May 08:58:00 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGBOX_H
#define UI_MSGBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CustomMsgBoxDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *lbMsg;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushOk;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *CustomMsgBoxDialog)
    {
        if (CustomMsgBoxDialog->objectName().isEmpty())
            CustomMsgBoxDialog->setObjectName(QString::fromUtf8("CustomMsgBoxDialog"));
        CustomMsgBoxDialog->setWindowModality(Qt::ApplicationModal);
        CustomMsgBoxDialog->resize(610, 94);
        CustomMsgBoxDialog->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app/MedFisis.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CustomMsgBoxDialog->setWindowIcon(icon);
        CustomMsgBoxDialog->setModal(true);
        verticalLayout = new QVBoxLayout(CustomMsgBoxDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CustomMsgBoxDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAutoFillBackground(true);
        label->setPixmap(QPixmap(QString::fromUtf8(":/app/qmessagebox-crit.ico")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        lbMsg = new QLabel(CustomMsgBoxDialog);
        lbMsg->setObjectName(QString::fromUtf8("lbMsg"));
        lbMsg->setScaledContents(true);

        horizontalLayout->addWidget(lbMsg);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushOk = new QPushButton(CustomMsgBoxDialog);
        pushOk->setObjectName(QString::fromUtf8("pushOk"));
        sizePolicy.setHeightForWidth(pushOk->sizePolicy().hasHeightForWidth());
        pushOk->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(pushOk);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CustomMsgBoxDialog);
        QObject::connect(pushOk, SIGNAL(clicked()), CustomMsgBoxDialog, SLOT(hide()));

        QMetaObject::connectSlotsByName(CustomMsgBoxDialog);
    } // setupUi

    void retranslateUi(QDialog *CustomMsgBoxDialog)
    {
        CustomMsgBoxDialog->setWindowTitle(QApplication::translate("CustomMsgBoxDialog", "Title", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        lbMsg->setText(QString());
        pushOk->setText(QApplication::translate("CustomMsgBoxDialog", "&Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CustomMsgBoxDialog: public Ui_CustomMsgBoxDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGBOX_H
