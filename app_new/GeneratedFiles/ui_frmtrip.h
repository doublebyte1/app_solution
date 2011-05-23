/********************************************************************************
** Form generated from reading UI file 'frmtrip.ui'
**
** Created: Mon 23. May 12:37:43 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTRIP_H
#define UI_FRMTRIP_H

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
#include "customtimectrl.h"

QT_BEGIN_NAMESPACE

class Ui_FrmTrip
{
public:
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lbHeader;
    QLabel *lbSource;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_15;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushNew;
    QGroupBox *groupDetails;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_2;
    QComboBox *cmbSite;
    QLabel *label_6;
    QComboBox *cmbSampler;
    QLabel *label_22;
    QSpinBox *spinProf;
    QLabel *label_24;
    QSpinBox *spinPart;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_14;
    CustomTimeCtrl *customDtStart;
    QLabel *label_25;
    CustomTimeCtrl *customDtEnd;
    QGroupBox *groupTotals;
    QGridLayout *gridLayout_2;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_16;
    QLabel *label_15;
    QLabel *label_17;
    QDoubleSpinBox *spinCE;
    QDoubleSpinBox *spinCC;
    QComboBox *cmbWeight;
    QLabel *label;
    QLabel *label_19;
    QLabel *label_18;
    QDoubleSpinBox *spinCBE;
    QDoubleSpinBox *spinCBC;
    QDoubleSpinBox *spinWeight;
    QComboBox *cmbBoxes;
    QSpinBox *spinNOC;
    QSpinBox *spinNOE;
    QHBoxLayout *horizontalLayout_12;
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *textComments;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *FrmTrip)
    {
        if (FrmTrip->objectName().isEmpty())
            FrmTrip->setObjectName(QString::fromUtf8("FrmTrip"));
        FrmTrip->resize(750, 594);
        verticalLayout_7 = new QVBoxLayout(FrmTrip);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        lbHeader = new QLabel(FrmTrip);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        horizontalLayout_9->addWidget(lbHeader);

        lbSource = new QLabel(FrmTrip);
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


        verticalLayout_7->addLayout(horizontalLayout_9);

        label_23 = new QLabel(FrmTrip);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        verticalLayout_7->addWidget(label_23);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        tableView = new QTableView(FrmTrip);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout_15->addWidget(tableView);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        pushNew = new QPushButton(FrmTrip);
        pushNew->setObjectName(QString::fromUtf8("pushNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNew->setIcon(icon);

        verticalLayout_5->addWidget(pushNew);


        horizontalLayout_15->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(horizontalLayout_15);

        groupDetails = new QGroupBox(FrmTrip);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        gridLayout_3 = new QGridLayout(groupDetails);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_2 = new QLabel(groupDetails);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_2);

        cmbSite = new QComboBox(groupDetails);
        cmbSite->setObjectName(QString::fromUtf8("cmbSite"));

        horizontalLayout_11->addWidget(cmbSite);

        label_6 = new QLabel(groupDetails);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_6);

        cmbSampler = new QComboBox(groupDetails);
        cmbSampler->setObjectName(QString::fromUtf8("cmbSampler"));

        horizontalLayout_11->addWidget(cmbSampler);

        label_22 = new QLabel(groupDetails);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_22);

        spinProf = new QSpinBox(groupDetails);
        spinProf->setObjectName(QString::fromUtf8("spinProf"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinProf->sizePolicy().hasHeightForWidth());
        spinProf->setSizePolicy(sizePolicy2);

        horizontalLayout_11->addWidget(spinProf);

        label_24 = new QLabel(groupDetails);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_24);

        spinPart = new QSpinBox(groupDetails);
        spinPart->setObjectName(QString::fromUtf8("spinPart"));
        sizePolicy2.setHeightForWidth(spinPart->sizePolicy().hasHeightForWidth());
        spinPart->setSizePolicy(sizePolicy2);

        horizontalLayout_11->addWidget(spinPart);


        gridLayout_3->addLayout(horizontalLayout_11, 0, 0, 1, 2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_14 = new QLabel(groupDetails);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);

        verticalLayout_6->addWidget(label_14);

        customDtStart = new CustomTimeCtrl(groupDetails);
        customDtStart->setObjectName(QString::fromUtf8("customDtStart"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(customDtStart->sizePolicy().hasHeightForWidth());
        customDtStart->setSizePolicy(sizePolicy3);

        verticalLayout_6->addWidget(customDtStart);

        label_25 = new QLabel(groupDetails);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy);

        verticalLayout_6->addWidget(label_25);

        customDtEnd = new CustomTimeCtrl(groupDetails);
        customDtEnd->setObjectName(QString::fromUtf8("customDtEnd"));
        sizePolicy3.setHeightForWidth(customDtEnd->sizePolicy().hasHeightForWidth());
        customDtEnd->setSizePolicy(sizePolicy3);

        verticalLayout_6->addWidget(customDtEnd);


        gridLayout_3->addLayout(verticalLayout_6, 1, 0, 5, 1);

        groupTotals = new QGroupBox(groupDetails);
        groupTotals->setObjectName(QString::fromUtf8("groupTotals"));
        sizePolicy.setHeightForWidth(groupTotals->sizePolicy().hasHeightForWidth());
        groupTotals->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupTotals);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_20 = new QLabel(groupTotals);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_20, 0, 1, 1, 1);

        label_21 = new QLabel(groupTotals);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_21, 0, 2, 1, 2);

        label_16 = new QLabel(groupTotals);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 1, 0, 1, 1);

        label_15 = new QLabel(groupTotals);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 2, 4, 1, 1);

        label_17 = new QLabel(groupTotals);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 3, 0, 1, 1);

        spinCE = new QDoubleSpinBox(groupTotals);
        spinCE->setObjectName(QString::fromUtf8("spinCE"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(spinCE->sizePolicy().hasHeightForWidth());
        spinCE->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(spinCE, 3, 1, 1, 2);

        spinCC = new QDoubleSpinBox(groupTotals);
        spinCC->setObjectName(QString::fromUtf8("spinCC"));
        spinCC->setEnabled(false);
        sizePolicy4.setHeightForWidth(spinCC->sizePolicy().hasHeightForWidth());
        spinCC->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(spinCC, 3, 3, 1, 1);

        cmbWeight = new QComboBox(groupTotals);
        cmbWeight->setObjectName(QString::fromUtf8("cmbWeight"));

        gridLayout_2->addWidget(cmbWeight, 3, 4, 1, 2);

        label = new QLabel(groupTotals);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 4, 4, 1, 1);

        label_19 = new QLabel(groupTotals);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_2->addWidget(label_19, 4, 5, 1, 1);

        label_18 = new QLabel(groupTotals);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setWordWrap(true);

        gridLayout_2->addWidget(label_18, 5, 0, 1, 1);

        spinCBE = new QDoubleSpinBox(groupTotals);
        spinCBE->setObjectName(QString::fromUtf8("spinCBE"));
        sizePolicy4.setHeightForWidth(spinCBE->sizePolicy().hasHeightForWidth());
        spinCBE->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(spinCBE, 5, 1, 1, 2);

        spinCBC = new QDoubleSpinBox(groupTotals);
        spinCBC->setObjectName(QString::fromUtf8("spinCBC"));
        spinCBC->setEnabled(false);

        gridLayout_2->addWidget(spinCBC, 5, 3, 1, 1);

        spinWeight = new QDoubleSpinBox(groupTotals);
        spinWeight->setObjectName(QString::fromUtf8("spinWeight"));
        sizePolicy4.setHeightForWidth(spinWeight->sizePolicy().hasHeightForWidth());
        spinWeight->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(spinWeight, 5, 4, 1, 1);

        cmbBoxes = new QComboBox(groupTotals);
        cmbBoxes->setObjectName(QString::fromUtf8("cmbBoxes"));

        gridLayout_2->addWidget(cmbBoxes, 5, 5, 1, 1);

        spinNOC = new QSpinBox(groupTotals);
        spinNOC->setObjectName(QString::fromUtf8("spinNOC"));
        spinNOC->setEnabled(false);
        sizePolicy4.setHeightForWidth(spinNOC->sizePolicy().hasHeightForWidth());
        spinNOC->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(spinNOC, 1, 3, 1, 1);

        spinNOE = new QSpinBox(groupTotals);
        spinNOE->setObjectName(QString::fromUtf8("spinNOE"));
        sizePolicy4.setHeightForWidth(spinNOE->sizePolicy().hasHeightForWidth());
        spinNOE->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(spinNOE, 1, 1, 1, 2);


        gridLayout_3->addWidget(groupTotals, 1, 1, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        horizontalLayout_12->addWidget(buttonBox);


        gridLayout_3->addLayout(horizontalLayout_12, 5, 1, 1, 1);

        textComments = new QPlainTextEdit(groupDetails);
        textComments->setObjectName(QString::fromUtf8("textComments"));

        gridLayout_3->addWidget(textComments, 3, 1, 1, 1);

        label_13 = new QLabel(groupDetails);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_13, 2, 1, 1, 1);


        verticalLayout_7->addWidget(groupDetails);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_2 = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_2);

        groupBox_2 = new QGroupBox(FrmTrip);
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


        verticalLayout_7->addLayout(horizontalLayout_16);

#ifndef QT_NO_SHORTCUT
        label_23->setBuddy(tableView);
        label_22->setBuddy(spinProf);
        label_24->setBuddy(spinPart);
        label_16->setBuddy(spinNOE);
        label_15->setBuddy(cmbWeight);
        label_17->setBuddy(spinCE);
        label_19->setBuddy(cmbBoxes);
        label_18->setBuddy(spinCBE);
#endif // QT_NO_SHORTCUT

        retranslateUi(FrmTrip);
        QObject::connect(pushNew, SIGNAL(clicked()), FrmTrip, SLOT(createRecord()));

        QMetaObject::connectSlotsByName(FrmTrip);
    } // setupUi

    void retranslateUi(QWidget *FrmTrip)
    {
        FrmTrip->setWindowTitle(QApplication::translate("FrmTrip", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("FrmTrip", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        lbSource->setText(QApplication::translate("FrmTrip", "[SOURCE]", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("FrmTrip", "Choose Fishing Trip:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tableView->setToolTip(QApplication::translate("FrmTrip", "Choose cell (or create a new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tableView->setStatusTip(QApplication::translate("FrmTrip", "Choose cell (or create a new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        tableView->setWhatsThis(QApplication::translate("FrmTrip", "In this widget we can choose cell, or create a new one", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        pushNew->setToolTip(QApplication::translate("FrmTrip", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNew->setStatusTip(QApplication::translate("FrmTrip", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNew->setWhatsThis(QApplication::translate("FrmTrip", "Creates new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNew->setText(QString());
        groupDetails->setTitle(QApplication::translate("FrmTrip", "Details", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FrmTrip", "Landing Site", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FrmTrip", "Sampler", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("FrmTrip", "Number of professional fishermen", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("FrmTrip", "No part-time fishermen", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("FrmTrip", "Start", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("FrmTrip", "End", 0, QApplication::UnicodeUTF8));
        groupTotals->setTitle(QApplication::translate("FrmTrip", "Totals", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("FrmTrip", "Estimated", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("FrmTrip", "Calculated", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("FrmTrip", "No of operations", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("FrmTrip", "Units", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("FrmTrip", "Catch (weight)", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmTrip", "Weight/box", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("FrmTrip", "Units", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("FrmTrip", "Catch (no boxes)", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("FrmTrip", "Comments:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        pushPrevious->setText(QApplication::translate("FrmTrip", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("FrmTrip", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmTrip: public Ui_FrmTrip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTRIP_H
