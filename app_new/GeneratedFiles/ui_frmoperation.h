/********************************************************************************
** Form generated from reading UI file 'frmoperation.ui'
**
** Created: Fri 27. May 17:55:56 2011
**      by: Qt User Interface Compiler version 4.6.3
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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
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
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lbHeader;
    QLabel *lbSource;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_4;
    QTableView *tableView;
    QPushButton *pushNew;
    QGroupBox *groupDetails;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *spinOrder;
    QLabel *label_4;
    QComboBox *cmbFishingZone;
    QLabel *label;
    CustomTimeCtrl *customDtStart;
    QLabel *label_2;
    CustomTimeCtrl *customDtEnd;
    QLabel *label_8;
    QPlainTextEdit *textComments;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupGear;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QComboBox *cmbGear;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpinBox *spinNoUnits;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinSize;
    QGroupBox *groupCatch;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_9;
    CatchInputCtrl *catchInputCtrl;
    QLabel *label_10;
    QListView *listView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
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
        FrmOperation->resize(790, 785);
        verticalLayout_5 = new QVBoxLayout(FrmOperation);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
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


        verticalLayout_5->addLayout(horizontalLayout_9);

        label_23 = new QLabel(FrmOperation);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        verticalLayout_5->addWidget(label_23);

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


        verticalLayout_5->addLayout(horizontalLayout_4);

        groupDetails = new QGroupBox(FrmOperation);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupDetails->sizePolicy().hasHeightForWidth());
        groupDetails->setSizePolicy(sizePolicy3);
        horizontalLayout_6 = new QHBoxLayout(groupDetails);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupDetails);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_3);

        spinOrder = new QSpinBox(groupDetails);
        spinOrder->setObjectName(QString::fromUtf8("spinOrder"));

        horizontalLayout_5->addWidget(spinOrder);

        label_4 = new QLabel(groupDetails);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_4);

        cmbFishingZone = new QComboBox(groupDetails);
        cmbFishingZone->setObjectName(QString::fromUtf8("cmbFishingZone"));
        cmbFishingZone->setEditable(true);

        horizontalLayout_5->addWidget(cmbFishingZone);


        verticalLayout_4->addLayout(horizontalLayout_5);

        label = new QLabel(groupDetails);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(label);

        customDtStart = new CustomTimeCtrl(groupDetails);
        customDtStart->setObjectName(QString::fromUtf8("customDtStart"));

        verticalLayout_4->addWidget(customDtStart);

        label_2 = new QLabel(groupDetails);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(label_2);

        customDtEnd = new CustomTimeCtrl(groupDetails);
        customDtEnd->setObjectName(QString::fromUtf8("customDtEnd"));

        verticalLayout_4->addWidget(customDtEnd);

        label_8 = new QLabel(groupDetails);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_8);

        textComments = new QPlainTextEdit(groupDetails);
        textComments->setObjectName(QString::fromUtf8("textComments"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(textComments->sizePolicy().hasHeightForWidth());
        textComments->setSizePolicy(sizePolicy4);

        verticalLayout_4->addWidget(textComments);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
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

        spinNoUnits = new QSpinBox(groupGear);
        spinNoUnits->setObjectName(QString::fromUtf8("spinNoUnits"));

        horizontalLayout_2->addWidget(spinNoUnits);

        label_7 = new QLabel(groupGear);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_7);

        doubleSpinSize = new QDoubleSpinBox(groupGear);
        doubleSpinSize->setObjectName(QString::fromUtf8("doubleSpinSize"));

        horizontalLayout_2->addWidget(doubleSpinSize);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupGear);

        groupCatch = new QGroupBox(groupDetails);
        groupCatch->setObjectName(QString::fromUtf8("groupCatch"));
        verticalLayout_2 = new QVBoxLayout(groupCatch);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_9 = new QLabel(groupCatch);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_2->addWidget(label_9);

        catchInputCtrl = new CatchInputCtrl(groupCatch);
        catchInputCtrl->setObjectName(QString::fromUtf8("catchInputCtrl"));

        verticalLayout_2->addWidget(catchInputCtrl);

        label_10 = new QLabel(groupCatch);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_2->addWidget(label_10);

        listView = new QListView(groupCatch);
        listView->setObjectName(QString::fromUtf8("listView"));
        sizePolicy4.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy4);

        verticalLayout_2->addWidget(listView);


        verticalLayout_3->addWidget(groupCatch);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout_3->addLayout(horizontalLayout);


        horizontalLayout_6->addLayout(verticalLayout_3);


        verticalLayout_5->addWidget(groupDetails);

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


        verticalLayout_5->addLayout(horizontalLayout_16);

#ifndef QT_NO_SHORTCUT
        label_23->setBuddy(tableView);
        label_3->setBuddy(spinOrder);
        label_4->setBuddy(cmbFishingZone);
        label_5->setBuddy(cmbGear);
        label_6->setBuddy(spinNoUnits);
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
        label_2->setText(QApplication::translate("FrmOperation", "End", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FrmOperation", "Comments", 0, QApplication::UnicodeUTF8));
        groupGear->setTitle(QApplication::translate("FrmOperation", "Gear", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FrmOperation", "Gear", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FrmOperation", "Units", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FrmOperation", "Size", 0, QApplication::UnicodeUTF8));
        groupCatch->setTitle(QApplication::translate("FrmOperation", "Totals", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FrmOperation", "Catch", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FrmOperation", "Commercial category/categories", 0, QApplication::UnicodeUTF8));
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
