/********************************************************************************
** Form generated from reading UI file 'frmtrip.ui'
**
** Created: Fri 24. Jun 14:32:21 2011
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
#include <QtGui/QGridLayout>
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

class Ui_FrmTrip
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lbHeader;
    QLabel *lbSource;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_15;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushNew;
    QGroupBox *groupDetails;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QComboBox *cmbSampler;
    QLabel *label_2;
    QComboBox *cmbSite;
    QLabel *label_22;
    QSpinBox *spinProf;
    QLabel *label_24;
    QSpinBox *spinPart;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_14;
    CustomTimeCtrl *customDtStart;
    QLabel *label_25;
    CustomTimeCtrl *customDtEnd;
    QPlainTextEdit *textComments;
    QLabel *label_13;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupTotals;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinNOE;
    QSpinBox *spinNOC;
    CatchInputCtrl *catchInputCtrl;
    QLabel *label_5;
    QComboBox *cmbFishingZone;
    QListView *listGears;
    QLabel *label_7;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_12;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_16;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *FrmTrip)
    {
        if (FrmTrip->objectName().isEmpty())
            FrmTrip->setObjectName(QString::fromUtf8("FrmTrip"));
        FrmTrip->resize(752, 767);
        verticalLayout_4 = new QVBoxLayout(FrmTrip);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
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


        verticalLayout_4->addLayout(horizontalLayout_9);

        label_23 = new QLabel(FrmTrip);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        verticalLayout_4->addWidget(label_23);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        tableView = new QTableView(FrmTrip);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy2);

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


        verticalLayout_4->addLayout(horizontalLayout_15);

        groupDetails = new QGroupBox(FrmTrip);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupDetails->sizePolicy().hasHeightForWidth());
        groupDetails->setSizePolicy(sizePolicy3);
        verticalLayout_3 = new QVBoxLayout(groupDetails);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_6 = new QLabel(groupDetails);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_6);

        cmbSampler = new QComboBox(groupDetails);
        cmbSampler->setObjectName(QString::fromUtf8("cmbSampler"));

        horizontalLayout_11->addWidget(cmbSampler);

        label_2 = new QLabel(groupDetails);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_2);

        cmbSite = new QComboBox(groupDetails);
        cmbSite->setObjectName(QString::fromUtf8("cmbSite"));

        horizontalLayout_11->addWidget(cmbSite);

        label_22 = new QLabel(groupDetails);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy);
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_22);

        spinProf = new QSpinBox(groupDetails);
        spinProf->setObjectName(QString::fromUtf8("spinProf"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(spinProf->sizePolicy().hasHeightForWidth());
        spinProf->setSizePolicy(sizePolicy4);
        spinProf->setMaximum(1000);

        horizontalLayout_11->addWidget(spinProf);

        label_24 = new QLabel(groupDetails);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        sizePolicy.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy);
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_24);

        spinPart = new QSpinBox(groupDetails);
        spinPart->setObjectName(QString::fromUtf8("spinPart"));
        sizePolicy4.setHeightForWidth(spinPart->sizePolicy().hasHeightForWidth());
        spinPart->setSizePolicy(sizePolicy4);
        spinPart->setMaximum(1000);

        horizontalLayout_11->addWidget(spinPart);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_14 = new QLabel(groupDetails);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_14);

        customDtStart = new CustomTimeCtrl(groupDetails);
        customDtStart->setObjectName(QString::fromUtf8("customDtStart"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(customDtStart->sizePolicy().hasHeightForWidth());
        customDtStart->setSizePolicy(sizePolicy5);

        verticalLayout->addWidget(customDtStart);

        label_25 = new QLabel(groupDetails);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_25);

        customDtEnd = new CustomTimeCtrl(groupDetails);
        customDtEnd->setObjectName(QString::fromUtf8("customDtEnd"));
        sizePolicy5.setHeightForWidth(customDtEnd->sizePolicy().hasHeightForWidth());
        customDtEnd->setSizePolicy(sizePolicy5);

        verticalLayout->addWidget(customDtEnd);

        textComments = new QPlainTextEdit(groupDetails);
        textComments->setObjectName(QString::fromUtf8("textComments"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(textComments->sizePolicy().hasHeightForWidth());
        textComments->setSizePolicy(sizePolicy6);

        verticalLayout->addWidget(textComments);

        label_13 = new QLabel(groupDetails);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_13);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupTotals = new QGroupBox(groupDetails);
        groupTotals->setObjectName(QString::fromUtf8("groupTotals"));
        sizePolicy5.setHeightForWidth(groupTotals->sizePolicy().hasHeightForWidth());
        groupTotals->setSizePolicy(sizePolicy5);
        gridLayout_2 = new QGridLayout(groupTotals);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupTotals);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 4, 1, 1);

        label_3 = new QLabel(groupTotals);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 5, 1, 1);

        label_4 = new QLabel(groupTotals);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 1, 1, 1);

        spinNOE = new QSpinBox(groupTotals);
        spinNOE->setObjectName(QString::fromUtf8("spinNOE"));
        spinNOE->setMaximum(1000);

        gridLayout_2->addWidget(spinNOE, 1, 4, 1, 1);

        spinNOC = new QSpinBox(groupTotals);
        spinNOC->setObjectName(QString::fromUtf8("spinNOC"));
        spinNOC->setEnabled(false);
        spinNOC->setMaximum(1000);

        gridLayout_2->addWidget(spinNOC, 1, 5, 1, 1);

        catchInputCtrl = new CatchInputCtrl(groupTotals);
        catchInputCtrl->setObjectName(QString::fromUtf8("catchInputCtrl"));
        sizePolicy5.setHeightForWidth(catchInputCtrl->sizePolicy().hasHeightForWidth());
        catchInputCtrl->setSizePolicy(sizePolicy5);

        gridLayout_2->addWidget(catchInputCtrl, 3, 1, 1, 5);

        label_5 = new QLabel(groupTotals);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 4, 1, 1);

        cmbFishingZone = new QComboBox(groupTotals);
        cmbFishingZone->setObjectName(QString::fromUtf8("cmbFishingZone"));
        cmbFishingZone->setEditable(false);

        gridLayout_2->addWidget(cmbFishingZone, 4, 5, 1, 1);

        listGears = new QListView(groupTotals);
        listGears->setObjectName(QString::fromUtf8("listGears"));
        listGears->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listGears->setAlternatingRowColors(false);
        listGears->setSelectionMode(QAbstractItemView::MultiSelection);
        listGears->setSelectionBehavior(QAbstractItemView::SelectRows);
        listGears->setResizeMode(QListView::Adjust);
        listGears->setWordWrap(true);

        gridLayout_2->addWidget(listGears, 4, 3, 1, 1);

        label_7 = new QLabel(groupTotals);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 4, 1, 1, 1);

        label_8 = new QLabel(groupTotals);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 2, 1, 1, 1);


        verticalLayout_2->addWidget(groupTotals);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        horizontalLayout_12->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_12);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupDetails);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        groupBox_2 = new QGroupBox(FrmTrip);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        horizontalLayout_10 = new QHBoxLayout(groupBox_2);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer);

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


        verticalLayout_4->addLayout(horizontalLayout_16);

#ifndef QT_NO_SHORTCUT
        label_23->setBuddy(tableView);
        label_22->setBuddy(spinProf);
        label_24->setBuddy(spinPart);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tableView, pushNew);
        QWidget::setTabOrder(pushNew, spinProf);
        QWidget::setTabOrder(spinProf, spinPart);
        QWidget::setTabOrder(spinPart, buttonBox);
        QWidget::setTabOrder(buttonBox, pushPrevious);
        QWidget::setTabOrder(pushPrevious, pushNext);

        retranslateUi(FrmTrip);
        QObject::connect(pushNew, SIGNAL(clicked()), FrmTrip, SLOT(createRecord()));
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), FrmTrip, SLOT(onButtonClick(QAbstractButton*)));
        QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), FrmTrip, SLOT(previewRow(QModelIndex)));

        QMetaObject::connectSlotsByName(FrmTrip);
    } // setupUi

    void retranslateUi(QWidget *FrmTrip)
    {
        FrmTrip->setWindowTitle(QApplication::translate("FrmTrip", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("FrmTrip", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        lbSource->setText(QApplication::translate("FrmTrip", "[SOURCE]", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("FrmTrip", "Choose Fishing Trip:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tableView->setToolTip(QApplication::translate("FrmTrip", "Choose sampled fishing trip (or create a new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tableView->setStatusTip(QApplication::translate("FrmTrip", "Choose sampled fishing trip (or create a new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        tableView->setWhatsThis(QApplication::translate("FrmTrip", "In this widget we can choose a sampled fishing trip, or create a new one", 0, QApplication::UnicodeUTF8));
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
        label_6->setText(QApplication::translate("FrmTrip", "Sampler", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmbSampler->setToolTip(QApplication::translate("FrmTrip", "Choose sampler", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cmbSampler->setStatusTip(QApplication::translate("FrmTrip", "Choose sampler", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        cmbSampler->setWhatsThis(QApplication::translate("FrmTrip", "In this widget we can choose a sampler", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_2->setText(QApplication::translate("FrmTrip", "Landing Site", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmbSite->setToolTip(QApplication::translate("FrmTrip", "Choose Landing Site", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cmbSite->setStatusTip(QApplication::translate("FrmTrip", "Choose Landing Site", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        cmbSite->setWhatsThis(QApplication::translate("FrmTrip", "In this widget we can select a landing site", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_22->setText(QApplication::translate("FrmTrip", "No of professional fishermen", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinProf->setToolTip(QApplication::translate("FrmTrip", "Number of professional fishermen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        spinProf->setStatusTip(QApplication::translate("FrmTrip", "Number of professional fishermen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        spinProf->setWhatsThis(QApplication::translate("FrmTrip", "Input the number of professional fishermen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_24->setText(QApplication::translate("FrmTrip", "No part-time fishermen", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinPart->setToolTip(QApplication::translate("FrmTrip", "Part-time fishermen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        spinPart->setStatusTip(QApplication::translate("FrmTrip", "Part-time fishermen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        spinPart->setWhatsThis(QApplication::translate("FrmTrip", "Input the number of part-time fishermen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_14->setText(QApplication::translate("FrmTrip", "Start", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        customDtStart->setToolTip(QApplication::translate("FrmTrip", "Start datetime", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        customDtStart->setWhatsThis(QApplication::translate("FrmTrip", "Input the starting datetime of the fishing trip", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_25->setText(QApplication::translate("FrmTrip", "End", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        customDtEnd->setToolTip(QApplication::translate("FrmTrip", "End datetime", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        customDtEnd->setWhatsThis(QApplication::translate("FrmTrip", "Input the finishing datetime of the fishing trip", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        textComments->setToolTip(QApplication::translate("FrmTrip", "Comments", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        textComments->setStatusTip(QApplication::translate("FrmTrip", "Comments", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        textComments->setWhatsThis(QApplication::translate("FrmTrip", "Input comments", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_13->setText(QApplication::translate("FrmTrip", "Comments:", 0, QApplication::UnicodeUTF8));
        groupTotals->setTitle(QApplication::translate("FrmTrip", "Totals", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmTrip", "Estimated", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FrmTrip", "Calculated", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FrmTrip", "No of operations", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinNOE->setToolTip(QApplication::translate("FrmTrip", "Number of fishing operations (estimated)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        spinNOE->setStatusTip(QApplication::translate("FrmTrip", "Number of fishing operations (estimated)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        spinNOE->setWhatsThis(QApplication::translate("FrmTrip", "Number of fishing operations (estimated)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        spinNOC->setToolTip(QApplication::translate("FrmTrip", "Number of fishing operations (calculated)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        spinNOC->setStatusTip(QApplication::translate("FrmTrip", "Number of fishing operations (calculated)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        spinNOC->setWhatsThis(QApplication::translate("FrmTrip", "Number of fishing operations (calculated)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_5->setText(QApplication::translate("FrmTrip", "Fishing Zone", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmbFishingZone->setToolTip(QApplication::translate("FrmTrip", "Select the fishing zone of this fishing trip", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cmbFishingZone->setStatusTip(QApplication::translate("FrmTrip", "Select the fishing zone of this fishing trip", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        cmbFishingZone->setWhatsThis(QApplication::translate("FrmTrip", "Select the fishing zone of this fishing trip", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        listGears->setToolTip(QApplication::translate("FrmTrip", "Select the gear(s) used during this fishing trip", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        listGears->setStatusTip(QApplication::translate("FrmTrip", "Select the gear(s) used during this fishing trip", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        listGears->setWhatsThis(QApplication::translate("FrmTrip", "Select the gear(s) used during this fishing trip", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_7->setText(QApplication::translate("FrmTrip", "Gear(s) used", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FrmTrip", "Catch", 0, QApplication::UnicodeUTF8));
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
