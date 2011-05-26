/********************************************************************************
** Form generated from reading UI file 'frmoperation.ui'
**
** Created: Thu 26. May 16:39:36 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMOPERATION_H
#define UI_FRMOPERATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "catchinputctrl.h"
#include "customtimectrl.h"

QT_BEGIN_NAMESPACE

class Ui_FrmOperation
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lbHeader;
    QLabel *lbSource;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_4;
    QTableView *tableView;
    QPushButton *pushNew;
    QGroupBox *groupDetails;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QSpinBox *spinOrder;
    QLabel *label_4;
    QComboBox *cmbFishingZone;
    QPlainTextEdit *plainTextEdit;
    QLabel *label;
    QGroupBox *groupGear;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QComboBox *cmbGear;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpinBox *spinBox;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinSize;
    CustomTimeCtrl *customDtStart;
    QGroupBox *groupCatch;
    QVBoxLayout *verticalLayout_2;
    CatchInputCtrl *catchInputCtrl;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QLabel *label_8;
    QLabel *label_2;
    CustomTimeCtrl *customDtEnd;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *FrmOperation)
    {
        if (FrmOperation->objectName().isEmpty())
            FrmOperation->setObjectName(QString::fromUtf8("FrmOperation"));
        FrmOperation->resize(790, 644);
        verticalLayout_3 = new QVBoxLayout(FrmOperation);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        lbHeader = new QLabel(FrmOperation);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        horizontalLayout_9->addWidget(lbHeader);

        lbSource = new QLabel(FrmOperation);
        lbSource->setObjectName(QString::fromUtf8("lbSource"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbSource->sizePolicy().hasHeightForWidth());
        lbSource->setSizePolicy(sizePolicy1);
        lbSource->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(220, 220, 220, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));\n"
"font: 75 10pt \"Fixedsys\";"));
        lbSource->setFrameShape(QFrame::StyledPanel);
        lbSource->setFrameShadow(QFrame::Raised);
        lbSource->setScaledContents(true);

        horizontalLayout_9->addWidget(lbSource);


        verticalLayout_3->addLayout(horizontalLayout_9);

        label_23 = new QLabel(FrmOperation);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        verticalLayout_3->addWidget(label_23);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        tableView = new QTableView(FrmOperation);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(tableView);

        pushNew = new QPushButton(FrmOperation);
        pushNew->setObjectName(QString::fromUtf8("pushNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNew->setIcon(icon);

        horizontalLayout_4->addWidget(pushNew);


        verticalLayout_3->addLayout(horizontalLayout_4);

        groupDetails = new QGroupBox(FrmOperation);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupDetails->sizePolicy().hasHeightForWidth());
        groupDetails->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(groupDetails);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(groupDetails);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        spinOrder = new QSpinBox(groupDetails);
        spinOrder->setObjectName(QString::fromUtf8("spinOrder"));

        gridLayout->addWidget(spinOrder, 0, 1, 1, 1);

        label_4 = new QLabel(groupDetails);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        cmbFishingZone = new QComboBox(groupDetails);
        cmbFishingZone->setObjectName(QString::fromUtf8("cmbFishingZone"));

        gridLayout->addWidget(cmbFishingZone, 0, 3, 1, 1);

        plainTextEdit = new QPlainTextEdit(groupDetails);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(plainTextEdit, 0, 5, 3, 1);

        label = new QLabel(groupDetails);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        groupGear = new QGroupBox(groupDetails);
        groupGear->setObjectName(QString::fromUtf8("groupGear"));
        verticalLayout = new QVBoxLayout(groupGear);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(groupGear);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy5);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_5);

        cmbGear = new QComboBox(groupGear);
        cmbGear->setObjectName(QString::fromUtf8("cmbGear"));

        horizontalLayout_3->addWidget(cmbGear);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(groupGear);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_6);

        spinBox = new QSpinBox(groupGear);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_2->addWidget(spinBox);

        label_7 = new QLabel(groupGear);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_7);

        doubleSpinSize = new QDoubleSpinBox(groupGear);
        doubleSpinSize->setObjectName(QString::fromUtf8("doubleSpinSize"));

        horizontalLayout_2->addWidget(doubleSpinSize);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addWidget(groupGear, 1, 4, 2, 1);

        customDtStart = new CustomTimeCtrl(groupDetails);
        customDtStart->setObjectName(QString::fromUtf8("customDtStart"));

        gridLayout->addWidget(customDtStart, 2, 0, 1, 4);

        groupCatch = new QGroupBox(groupDetails);
        groupCatch->setObjectName(QString::fromUtf8("groupCatch"));
        verticalLayout_2 = new QVBoxLayout(groupCatch);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        catchInputCtrl = new CatchInputCtrl(groupCatch);
        catchInputCtrl->setObjectName(QString::fromUtf8("catchInputCtrl"));

        verticalLayout_2->addWidget(catchInputCtrl);


        gridLayout->addWidget(groupCatch, 3, 4, 3, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        horizontalLayout->addWidget(buttonBox);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 6);

        label_8 = new QLabel(groupDetails);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 0, 4, 1, 1);

        label_2 = new QLabel(groupDetails);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        customDtEnd = new CustomTimeCtrl(groupDetails);
        customDtEnd->setObjectName(QString::fromUtf8("customDtEnd"));

        gridLayout->addWidget(customDtEnd, 5, 0, 1, 4);


        verticalLayout_3->addWidget(groupDetails);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_2 = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_2);

        groupBox_2 = new QGroupBox(FrmOperation);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_2);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        pushPrevious = new QPushButton(groupBox_2);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon1);

        horizontalLayout_10->addWidget(pushPrevious);

        pushNext = new QPushButton(groupBox_2);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        pushNext->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon2);

        horizontalLayout_10->addWidget(pushNext);


        horizontalLayout_16->addWidget(groupBox_2);


        verticalLayout_3->addLayout(horizontalLayout_16);

#ifndef QT_NO_SHORTCUT
        label_23->setBuddy(tableView);
        label_3->setBuddy(spinOrder);
        label_4->setBuddy(cmbFishingZone);
        label_5->setBuddy(cmbGear);
        label_6->setBuddy(spinBox);
        label_7->setBuddy(doubleSpinSize);
#endif // QT_NO_SHORTCUT

        retranslateUi(FrmOperation);
        QObject::connect(pushNew, SIGNAL(clicked()), FrmOperation, SLOT(createRecord()));
        QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), FrmOperation, SLOT(previewRow(QModelIndex)));

        QMetaObject::connectSlotsByName(FrmOperation);
    } // setupUi

    void retranslateUi(QWidget *FrmOperation)
    {
        FrmOperation->setWindowTitle(QApplication::translate("FrmOperation", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("FrmOperation", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        lbSource->setText(QApplication::translate("FrmOperation", "[SOURCE]", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("FrmOperation", "Choose Fishing Operation:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tableView->setToolTip(QApplication::translate("FrmOperation", "Choose sampled fishing trip (or create a new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tableView->setStatusTip(QApplication::translate("FrmOperation", "Choose sampled fishing trip (or create a new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        tableView->setWhatsThis(QApplication::translate("FrmOperation", "In this widget we can choose sampled fishing trip, or create a new one", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        pushNew->setToolTip(QApplication::translate("FrmOperation", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNew->setStatusTip(QApplication::translate("FrmOperation", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNew->setWhatsThis(QApplication::translate("FrmOperation", "Creates new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNew->setText(QString());
        groupDetails->setTitle(QApplication::translate("FrmOperation", "Details", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FrmOperation", "Order Number", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FrmOperation", "Fishing zone", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmOperation", "Start", 0, QApplication::UnicodeUTF8));
        groupGear->setTitle(QApplication::translate("FrmOperation", "Gear", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FrmOperation", "Gear", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FrmOperation", "Units", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FrmOperation", "Size", 0, QApplication::UnicodeUTF8));
        groupCatch->setTitle(QApplication::translate("FrmOperation", "Catch", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FrmOperation", "Comments", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FrmOperation", "End", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        pushPrevious->setText(QApplication::translate("FrmOperation", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("FrmOperation", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmOperation: public Ui_FrmOperation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMOPERATION_H
