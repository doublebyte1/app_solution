/********************************************************************************
** Form generated from reading UI file 'frmcatch.ui'
**
** Created: Fri 17. Jun 17:12:14 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCATCH_H
#define UI_FRMCATCH_H

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

QT_BEGIN_NAMESPACE

class Ui_FrmCatch
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lbHeader;
    QLabel *lbSource;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_4;
    QTableView *tableView;
    QPushButton *pushNew;
    QGroupBox *groupDetails;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QComboBox *cmbCategory;
    QGroupBox *groupCatch;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    CatchInputCtrl *catchInputCtrl;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupGear;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QSpinBox *spinNoInd;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinWeight;
    QLabel *label;
    QComboBox *cmbUnits;
    QLabel *label_8;
    QPlainTextEdit *textComments;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *FrmCatch)
    {
        if (FrmCatch->objectName().isEmpty())
            FrmCatch->setObjectName(QString::fromUtf8("FrmCatch"));
        FrmCatch->resize(770, 648);
        verticalLayout_4 = new QVBoxLayout(FrmCatch);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lbHeader = new QLabel(FrmCatch);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        horizontalLayout_5->addWidget(lbHeader);

        lbSource = new QLabel(FrmCatch);
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

        horizontalLayout_5->addWidget(lbSource);


        verticalLayout_4->addLayout(horizontalLayout_5);

        label_23 = new QLabel(FrmCatch);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        verticalLayout_4->addWidget(label_23);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        tableView = new QTableView(FrmCatch);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(tableView);

        pushNew = new QPushButton(FrmCatch);
        pushNew->setObjectName(QString::fromUtf8("pushNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNew->setIcon(icon);

        horizontalLayout_4->addWidget(pushNew);


        verticalLayout_4->addLayout(horizontalLayout_4);

        groupDetails = new QGroupBox(FrmCatch);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupDetails->sizePolicy().hasHeightForWidth());
        groupDetails->setSizePolicy(sizePolicy3);
        horizontalLayout_3 = new QHBoxLayout(groupDetails);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupDetails);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_4);

        cmbCategory = new QComboBox(groupDetails);
        cmbCategory->setObjectName(QString::fromUtf8("cmbCategory"));
        cmbCategory->setEditable(false);

        horizontalLayout_2->addWidget(cmbCategory);


        verticalLayout_3->addLayout(horizontalLayout_2);

        groupCatch = new QGroupBox(groupDetails);
        groupCatch->setObjectName(QString::fromUtf8("groupCatch"));
        verticalLayout = new QVBoxLayout(groupCatch);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_9 = new QLabel(groupCatch);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);

        catchInputCtrl = new CatchInputCtrl(groupCatch);
        catchInputCtrl->setObjectName(QString::fromUtf8("catchInputCtrl"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(catchInputCtrl->sizePolicy().hasHeightForWidth());
        catchInputCtrl->setSizePolicy(sizePolicy4);

        verticalLayout->addWidget(catchInputCtrl);


        verticalLayout_3->addWidget(groupCatch);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupGear = new QGroupBox(groupDetails);
        groupGear->setObjectName(QString::fromUtf8("groupGear"));
        gridLayout = new QGridLayout(groupGear);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(groupGear);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        spinNoInd = new QSpinBox(groupGear);
        spinNoInd->setObjectName(QString::fromUtf8("spinNoInd"));
        spinNoInd->setMaximum(1000);

        gridLayout->addWidget(spinNoInd, 0, 1, 1, 1);

        label_7 = new QLabel(groupGear);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        doubleSpinWeight = new QDoubleSpinBox(groupGear);
        doubleSpinWeight->setObjectName(QString::fromUtf8("doubleSpinWeight"));
        doubleSpinWeight->setMaximum(1e+07);

        gridLayout->addWidget(doubleSpinWeight, 1, 1, 1, 1);

        label = new QLabel(groupGear);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        cmbUnits = new QComboBox(groupGear);
        cmbUnits->setObjectName(QString::fromUtf8("cmbUnits"));

        gridLayout->addWidget(cmbUnits, 2, 1, 1, 1);


        verticalLayout_2->addWidget(groupGear);

        label_8 = new QLabel(groupDetails);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_8);

        textComments = new QPlainTextEdit(groupDetails);
        textComments->setObjectName(QString::fromUtf8("textComments"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(textComments->sizePolicy().hasHeightForWidth());
        textComments->setSizePolicy(sizePolicy5);

        verticalLayout_2->addWidget(textComments);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addWidget(groupDetails);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_2 = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_2);

        groupBox_2 = new QGroupBox(FrmCatch);
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


        verticalLayout_4->addLayout(horizontalLayout_16);

#ifndef QT_NO_SHORTCUT
        label_23->setBuddy(tableView);
        label_4->setBuddy(cmbCategory);
        label_6->setBuddy(spinNoInd);
        label_7->setBuddy(doubleSpinWeight);
        label->setBuddy(cmbUnits);
        label_8->setBuddy(textComments);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tableView, pushNew);
        QWidget::setTabOrder(pushNew, cmbCategory);
        QWidget::setTabOrder(cmbCategory, spinNoInd);
        QWidget::setTabOrder(spinNoInd, doubleSpinWeight);
        QWidget::setTabOrder(doubleSpinWeight, cmbUnits);
        QWidget::setTabOrder(cmbUnits, textComments);
        QWidget::setTabOrder(textComments, buttonBox);
        QWidget::setTabOrder(buttonBox, pushPrevious);
        QWidget::setTabOrder(pushPrevious, pushNext);

        retranslateUi(FrmCatch);
        QObject::connect(pushNew, SIGNAL(clicked()), FrmCatch, SLOT(createRecord()));
        QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), FrmCatch, SLOT(previewRow(QModelIndex)));
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), FrmCatch, SLOT(onButtonClick(QAbstractButton*)));

        QMetaObject::connectSlotsByName(FrmCatch);
    } // setupUi

    void retranslateUi(QWidget *FrmCatch)
    {
        FrmCatch->setWindowTitle(QApplication::translate("FrmCatch", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("FrmCatch", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        lbSource->setText(QApplication::translate("FrmCatch", "[SOURCE]", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("FrmCatch", "Choose Catch:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tableView->setToolTip(QApplication::translate("FrmCatch", "Choose sampled catch (or create a new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tableView->setStatusTip(QApplication::translate("FrmCatch", "Choose sampled catch (or create a new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        tableView->setWhatsThis(QApplication::translate("FrmCatch", "In this widget we can choose a sampled catch, or create a new one", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        pushNew->setToolTip(QApplication::translate("FrmCatch", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNew->setStatusTip(QApplication::translate("FrmCatch", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNew->setWhatsThis(QApplication::translate("FrmCatch", "Creates new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNew->setText(QString());
        groupDetails->setTitle(QApplication::translate("FrmCatch", "Details", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FrmCatch", "Commercial Category", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmbCategory->setToolTip(QApplication::translate("FrmCatch", "Choose commercial category for this catch", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cmbCategory->setStatusTip(QApplication::translate("FrmCatch", "Choose commercial category for this catch", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        cmbCategory->setWhatsThis(QApplication::translate("FrmCatch", "Choose commercial category for this catch", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupCatch->setTitle(QApplication::translate("FrmCatch", "Totals", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FrmCatch", "Catch", 0, QApplication::UnicodeUTF8));
        groupGear->setTitle(QApplication::translate("FrmCatch", "Sample", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FrmCatch", "No individuals", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinNoInd->setToolTip(QApplication::translate("FrmCatch", "Number of individuals on the sample", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        spinNoInd->setStatusTip(QApplication::translate("FrmCatch", "Number of individuals on the sample", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        spinNoInd->setWhatsThis(QApplication::translate("FrmCatch", "Number of individuals on the sample", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_7->setText(QApplication::translate("FrmCatch", "Weight", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        doubleSpinWeight->setToolTip(QApplication::translate("FrmCatch", "Weight per sampled individual", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        doubleSpinWeight->setStatusTip(QApplication::translate("FrmCatch", "Weight per sampled individual", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        doubleSpinWeight->setWhatsThis(QApplication::translate("FrmCatch", "Weight per sampled individual", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("FrmCatch", "Weight units", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmbUnits->setToolTip(QApplication::translate("FrmCatch", "Choose weight units", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cmbUnits->setStatusTip(QApplication::translate("FrmCatch", "Choose weight units", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        cmbUnits->setWhatsThis(QApplication::translate("FrmCatch", "Choose weight units", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_8->setText(QApplication::translate("FrmCatch", "Comments", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        textComments->setToolTip(QApplication::translate("FrmCatch", "Introduce your comments here", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        textComments->setStatusTip(QApplication::translate("FrmCatch", "Introduce your comments here", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        textComments->setWhatsThis(QApplication::translate("FrmCatch", "Introduce your comments here", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupBox_2->setTitle(QString());
        pushPrevious->setText(QApplication::translate("FrmCatch", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("FrmCatch", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmCatch: public Ui_FrmCatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCATCH_H
