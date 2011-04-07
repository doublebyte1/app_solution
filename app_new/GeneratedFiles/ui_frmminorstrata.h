/********************************************************************************
** Form generated from reading UI file 'frmminorstrata.ui'
**
** Created: Wed 6. Apr 18:35:36 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMINORSTRATA_H
#define UI_FRMMINORSTRATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QWidget>
#include "customtimectrl.h"

QT_BEGIN_NAMESPACE

class Ui_frmminorstrata
{
public:
    QGridLayout *gridLayout_2;
    QLabel *lbHeader;
    QLabel *label_6;
    QTableView *tableView;
    QPushButton *pushDetails;
    QLabel *label_5;
    QLineEdit *lineNew;
    QGroupBox *groupDetails;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *cmbGLS;
    QGroupBox *groupActivity;
    QGridLayout *gridLayout_3;
    QRadioButton *radioActive;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioInactive;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_4;
    QPlainTextEdit *plainTextEdit;
    QLabel *label;
    QLabel *label_2;
    CustomTimeCtrl *customDtStart;
    CustomTimeCtrl *customDtEnd;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBackNext;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *frmminorstrata)
    {
        if (frmminorstrata->objectName().isEmpty())
            frmminorstrata->setObjectName(QString::fromUtf8("frmminorstrata"));
        frmminorstrata->resize(711, 609);
        gridLayout_2 = new QGridLayout(frmminorstrata);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lbHeader = new QLabel(frmminorstrata);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        gridLayout_2->addWidget(lbHeader, 0, 0, 1, 2);

        label_6 = new QLabel(frmminorstrata);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        tableView = new QTableView(frmminorstrata);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_2->addWidget(tableView, 1, 1, 2, 1);

        pushDetails = new QPushButton(frmminorstrata);
        pushDetails->setObjectName(QString::fromUtf8("pushDetails"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushDetails->sizePolicy().hasHeightForWidth());
        pushDetails->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/mail_find.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushDetails->setIcon(icon);
        pushDetails->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(pushDetails, 2, 2, 2, 1);

        label_5 = new QLabel(frmminorstrata);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        lineNew = new QLineEdit(frmminorstrata);
        lineNew->setObjectName(QString::fromUtf8("lineNew"));

        gridLayout_2->addWidget(lineNew, 3, 1, 1, 1);

        groupDetails = new QGroupBox(frmminorstrata);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        gridLayout = new QGridLayout(groupDetails);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(groupDetails);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        cmbGLS = new QComboBox(groupDetails);
        cmbGLS->setObjectName(QString::fromUtf8("cmbGLS"));

        horizontalLayout_2->addWidget(cmbGLS);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 3);

        groupActivity = new QGroupBox(groupDetails);
        groupActivity->setObjectName(QString::fromUtf8("groupActivity"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupActivity->sizePolicy().hasHeightForWidth());
        groupActivity->setSizePolicy(sizePolicy2);
        gridLayout_3 = new QGridLayout(groupActivity);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioActive = new QRadioButton(groupActivity);
        radioActive->setObjectName(QString::fromUtf8("radioActive"));

        gridLayout_3->addWidget(radioActive, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioInactive = new QRadioButton(groupActivity);
        radioInactive->setObjectName(QString::fromUtf8("radioInactive"));

        horizontalLayout->addWidget(radioInactive);

        comboBox = new QComboBox(groupActivity);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);


        gridLayout->addWidget(groupActivity, 0, 3, 2, 2);

        label_4 = new QLabel(groupDetails);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(groupDetails);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(plainTextEdit, 1, 1, 1, 1);

        label = new QLabel(groupDetails);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 2);

        label_2 = new QLabel(groupDetails);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 3, 1, 1);

        customDtStart = new CustomTimeCtrl(groupDetails);
        customDtStart->setObjectName(QString::fromUtf8("customDtStart"));

        gridLayout->addWidget(customDtStart, 3, 0, 2, 2);

        customDtEnd = new CustomTimeCtrl(groupDetails);
        customDtEnd->setObjectName(QString::fromUtf8("customDtEnd"));

        gridLayout->addWidget(customDtEnd, 3, 2, 2, 3);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 4, 1, 1);


        gridLayout_2->addWidget(groupDetails, 4, 0, 1, 3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(488, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        groupBackNext = new QGroupBox(frmminorstrata);
        groupBackNext->setObjectName(QString::fromUtf8("groupBackNext"));
        sizePolicy1.setHeightForWidth(groupBackNext->sizePolicy().hasHeightForWidth());
        groupBackNext->setSizePolicy(sizePolicy1);
        horizontalLayout_3 = new QHBoxLayout(groupBackNext);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushPrevious = new QPushButton(groupBackNext);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        pushPrevious->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon1);

        horizontalLayout_3->addWidget(pushPrevious);

        pushNext = new QPushButton(groupBackNext);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon2);

        horizontalLayout_3->addWidget(pushNext);


        horizontalLayout_4->addWidget(groupBackNext);


        gridLayout_2->addLayout(horizontalLayout_4, 5, 0, 1, 3);

#ifndef QT_NO_SHORTCUT
        label_6->setBuddy(tableView);
        label_5->setBuddy(lineNew);
        label_3->setBuddy(cmbGLS);
#endif // QT_NO_SHORTCUT

        retranslateUi(frmminorstrata);
        QObject::connect(pushDetails, SIGNAL(clicked()), frmminorstrata, SLOT(showDetails()));

        QMetaObject::connectSlotsByName(frmminorstrata);
    } // setupUi

    void retranslateUi(QWidget *frmminorstrata)
    {
        frmminorstrata->setWindowTitle(QApplication::translate("frmminorstrata", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("frmminorstrata", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("frmminorstrata", "Choose Minor Strata", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushDetails->setToolTip(QApplication::translate("frmminorstrata", "Show Details", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushDetails->setStatusTip(QApplication::translate("frmminorstrata", "Show Details", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushDetails->setWhatsThis(QApplication::translate("frmminorstrata", "Shows Details", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushDetails->setText(QString());
        label_5->setText(QApplication::translate("frmminorstrata", "Create New", 0, QApplication::UnicodeUTF8));
        groupDetails->setTitle(QApplication::translate("frmminorstrata", "Details", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("frmminorstrata", "Group of Landing Sites", 0, QApplication::UnicodeUTF8));
        groupActivity->setTitle(QApplication::translate("frmminorstrata", "Activity Status", 0, QApplication::UnicodeUTF8));
        radioActive->setText(QApplication::translate("frmminorstrata", "Active", 0, QApplication::UnicodeUTF8));
        radioInactive->setText(QApplication::translate("frmminorstrata", "Inactive", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmminorstrata", "Comments", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmminorstrata", "Start Date", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmminorstrata", "End Date", 0, QApplication::UnicodeUTF8));
        groupBackNext->setTitle(QString());
        pushPrevious->setText(QApplication::translate("frmminorstrata", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("frmminorstrata", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmminorstrata: public Ui_frmminorstrata {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMINORSTRATA_H
