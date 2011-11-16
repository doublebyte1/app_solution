/********************************************************************************
** Form generated from reading UI file 'frmvesseltype.ui'
**
** Created: Wed 16. Nov 19:44:57 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMVESSELTYPE_H
#define UI_FRMVESSELTYPE_H

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
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmVesselType
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbHeader;
    QLabel *lbSource;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QPushButton *pushNew;
    QGroupBox *groupDetails;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QComboBox *cmbTypes;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_7;
    QSpinBox *spinNE;
    QSpinBox *spinNC;
    QPlainTextEdit *textComments;
    QLabel *label_8;
    QSpinBox *spinAE;
    QSpinBox *spinAC;
    QLabel *label_9;
    QSpinBox *spinIE;
    QSpinBox *spinIC;
    QLabel *label_10;
    QSpinBox *spinOE;
    QSpinBox *spinOC;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *FrmVesselType)
    {
        if (FrmVesselType->objectName().isEmpty())
            FrmVesselType->setObjectName(QString::fromUtf8("FrmVesselType"));
        FrmVesselType->resize(710, 438);
        verticalLayout = new QVBoxLayout(FrmVesselType);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lbHeader = new QLabel(FrmVesselType);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        horizontalLayout_2->addWidget(lbHeader);

        lbSource = new QLabel(FrmVesselType);
        lbSource->setObjectName(QString::fromUtf8("lbSource"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbSource->sizePolicy().hasHeightForWidth());
        lbSource->setSizePolicy(sizePolicy1);
        lbSource->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(220, 220, 220, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));\n"
"font: 75 10pt \"Fixedsys\";"));
        lbSource->setFrameShape(QFrame::StyledPanel);
        lbSource->setFrameShadow(QFrame::Raised);
        lbSource->setScaledContents(true);

        horizontalLayout_2->addWidget(lbSource);


        verticalLayout->addLayout(horizontalLayout_2);

        label = new QLabel(FrmVesselType);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(FrmVesselType);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout->addWidget(tableView);

        pushNew = new QPushButton(FrmVesselType);
        pushNew->setObjectName(QString::fromUtf8("pushNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNew->setIcon(icon);

        horizontalLayout->addWidget(pushNew);


        verticalLayout->addLayout(horizontalLayout);

        groupDetails = new QGroupBox(FrmVesselType);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        gridLayout = new QGridLayout(groupDetails);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(groupDetails);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        cmbTypes = new QComboBox(groupDetails);
        cmbTypes->setObjectName(QString::fromUtf8("cmbTypes"));

        gridLayout->addWidget(cmbTypes, 0, 5, 1, 1);

        label_4 = new QLabel(groupDetails);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_4, 1, 1, 1, 2);

        label_5 = new QLabel(groupDetails);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        label_2 = new QLabel(groupDetails);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 4, 1, 1);

        label_7 = new QLabel(groupDetails);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        spinNE = new QSpinBox(groupDetails);
        spinNE->setObjectName(QString::fromUtf8("spinNE"));
        sizePolicy2.setHeightForWidth(spinNE->sizePolicy().hasHeightForWidth());
        spinNE->setSizePolicy(sizePolicy2);
        spinNE->setMaximum(1000);

        gridLayout->addWidget(spinNE, 2, 2, 1, 1);

        spinNC = new QSpinBox(groupDetails);
        spinNC->setObjectName(QString::fromUtf8("spinNC"));
        spinNC->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinNC->sizePolicy().hasHeightForWidth());
        spinNC->setSizePolicy(sizePolicy2);
        spinNC->setMaximum(1000);

        gridLayout->addWidget(spinNC, 2, 3, 1, 1);

        textComments = new QPlainTextEdit(groupDetails);
        textComments->setObjectName(QString::fromUtf8("textComments"));

        gridLayout->addWidget(textComments, 2, 4, 4, 2);

        label_8 = new QLabel(groupDetails);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        spinAE = new QSpinBox(groupDetails);
        spinAE->setObjectName(QString::fromUtf8("spinAE"));
        sizePolicy2.setHeightForWidth(spinAE->sizePolicy().hasHeightForWidth());
        spinAE->setSizePolicy(sizePolicy2);
        spinAE->setMaximum(1000);

        gridLayout->addWidget(spinAE, 3, 2, 1, 1);

        spinAC = new QSpinBox(groupDetails);
        spinAC->setObjectName(QString::fromUtf8("spinAC"));
        spinAC->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinAC->sizePolicy().hasHeightForWidth());
        spinAC->setSizePolicy(sizePolicy2);
        spinAC->setMaximum(1000);

        gridLayout->addWidget(spinAC, 3, 3, 1, 1);

        label_9 = new QLabel(groupDetails);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        spinIE = new QSpinBox(groupDetails);
        spinIE->setObjectName(QString::fromUtf8("spinIE"));
        sizePolicy2.setHeightForWidth(spinIE->sizePolicy().hasHeightForWidth());
        spinIE->setSizePolicy(sizePolicy2);
        spinIE->setMaximum(1000);

        gridLayout->addWidget(spinIE, 4, 2, 1, 1);

        spinIC = new QSpinBox(groupDetails);
        spinIC->setObjectName(QString::fromUtf8("spinIC"));
        spinIC->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinIC->sizePolicy().hasHeightForWidth());
        spinIC->setSizePolicy(sizePolicy2);
        spinIC->setMaximum(1000);

        gridLayout->addWidget(spinIC, 4, 3, 1, 1);

        label_10 = new QLabel(groupDetails);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 5, 0, 1, 2);

        spinOE = new QSpinBox(groupDetails);
        spinOE->setObjectName(QString::fromUtf8("spinOE"));
        sizePolicy2.setHeightForWidth(spinOE->sizePolicy().hasHeightForWidth());
        spinOE->setSizePolicy(sizePolicy2);
        spinOE->setMaximum(1000);

        gridLayout->addWidget(spinOE, 5, 2, 1, 1);

        spinOC = new QSpinBox(groupDetails);
        spinOC->setObjectName(QString::fromUtf8("spinOC"));
        spinOC->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinOC->sizePolicy().hasHeightForWidth());
        spinOC->setSizePolicy(sizePolicy2);
        spinOC->setMaximum(1000);

        gridLayout->addWidget(spinOC, 5, 3, 1, 1);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        gridLayout->addWidget(buttonBox, 6, 5, 1, 1);


        verticalLayout->addWidget(groupDetails);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        groupBox = new QGroupBox(FrmVesselType);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushPrevious = new QPushButton(groupBox);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon1);

        horizontalLayout_3->addWidget(pushPrevious);

        pushNext = new QPushButton(groupBox);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon2);

        horizontalLayout_3->addWidget(pushNext);


        horizontalLayout_4->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout_4);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(tableView);
        label_3->setBuddy(cmbTypes);
        label_4->setBuddy(spinNE);
        label_5->setBuddy(spinNC);
        label_2->setBuddy(textComments);
        label_7->setBuddy(spinNE);
        label_8->setBuddy(spinAE);
        label_9->setBuddy(spinIE);
        label_10->setBuddy(spinOE);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tableView, pushNew);
        QWidget::setTabOrder(pushNew, cmbTypes);
        QWidget::setTabOrder(cmbTypes, spinNE);
        QWidget::setTabOrder(spinNE, spinNC);
        QWidget::setTabOrder(spinNC, spinAE);
        QWidget::setTabOrder(spinAE, spinAC);
        QWidget::setTabOrder(spinAC, spinIE);
        QWidget::setTabOrder(spinIE, spinIC);
        QWidget::setTabOrder(spinIC, spinOE);
        QWidget::setTabOrder(spinOE, spinOC);
        QWidget::setTabOrder(spinOC, textComments);
        QWidget::setTabOrder(textComments, buttonBox);
        QWidget::setTabOrder(buttonBox, pushPrevious);
        QWidget::setTabOrder(pushPrevious, pushNext);

        retranslateUi(FrmVesselType);
        QObject::connect(pushNew, SIGNAL(clicked()), FrmVesselType, SLOT(createRecord()));
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), FrmVesselType, SLOT(onButtonClick(QAbstractButton*)));
        QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), FrmVesselType, SLOT(previewRow(QModelIndex)));

        QMetaObject::connectSlotsByName(FrmVesselType);
    } // setupUi

    void retranslateUi(QWidget *FrmVesselType)
    {
        FrmVesselType->setWindowTitle(QApplication::translate("FrmVesselType", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("FrmVesselType", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        lbSource->setText(QApplication::translate("FrmVesselType", "[SOURCE]", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmVesselType", "Choose cell vessel type:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tableView->setToolTip(QApplication::translate("FrmVesselType", "Choose cell (or create new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tableView->setStatusTip(QApplication::translate("FrmVesselType", "Choose cell (or create new one)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        tableView->setWhatsThis(QApplication::translate("FrmVesselType", "In this widget we can choose a cell, or create a new one", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        pushNew->setToolTip(QApplication::translate("FrmVesselType", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNew->setStatusTip(QApplication::translate("FrmVesselType", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNew->setWhatsThis(QApplication::translate("FrmVesselType", "Creates new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNew->setText(QString());
        groupDetails->setTitle(QApplication::translate("FrmVesselType", "Details", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FrmVesselType", "Vessel type", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FrmVesselType", "Estimated", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FrmVesselType", "Calculated", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FrmVesselType", "Comments:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FrmVesselType", "No of Vessels", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FrmVesselType", "Active Vessels", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FrmVesselType", "Inactive Vessels", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FrmVesselType", "Vessels from Outside", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        pushPrevious->setText(QApplication::translate("FrmVesselType", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("FrmVesselType", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmVesselType: public Ui_FrmVesselType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMVESSELTYPE_H
