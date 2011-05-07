/********************************************************************************
** Form generated from reading UI file 'frmvesseltype.ui'
**
** Created: Sat 7. May 19:10:33 2011
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
    QLabel *lbHeader;
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
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *FrmVesselType)
    {
        if (FrmVesselType->objectName().isEmpty())
            FrmVesselType->setObjectName(QString::fromUtf8("FrmVesselType"));
        FrmVesselType->resize(710, 413);
        verticalLayout = new QVBoxLayout(FrmVesselType);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbHeader = new QLabel(FrmVesselType);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        verticalLayout->addWidget(lbHeader);

        label = new QLabel(FrmVesselType);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(FrmVesselType);
        tableView->setObjectName(QString::fromUtf8("tableView"));

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
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_4, 1, 1, 1, 2);

        label_5 = new QLabel(groupDetails);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        label_2 = new QLabel(groupDetails);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 4, 1, 1);

        label_7 = new QLabel(groupDetails);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        spinNE = new QSpinBox(groupDetails);
        spinNE->setObjectName(QString::fromUtf8("spinNE"));
        sizePolicy.setHeightForWidth(spinNE->sizePolicy().hasHeightForWidth());
        spinNE->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinNE, 2, 2, 1, 1);

        spinNC = new QSpinBox(groupDetails);
        spinNC->setObjectName(QString::fromUtf8("spinNC"));
        spinNC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinNC->sizePolicy().hasHeightForWidth());
        spinNC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinNC, 2, 3, 1, 1);

        textComments = new QPlainTextEdit(groupDetails);
        textComments->setObjectName(QString::fromUtf8("textComments"));

        gridLayout->addWidget(textComments, 2, 4, 4, 2);

        label_8 = new QLabel(groupDetails);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        spinAE = new QSpinBox(groupDetails);
        spinAE->setObjectName(QString::fromUtf8("spinAE"));
        sizePolicy.setHeightForWidth(spinAE->sizePolicy().hasHeightForWidth());
        spinAE->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinAE, 3, 2, 1, 1);

        spinAC = new QSpinBox(groupDetails);
        spinAC->setObjectName(QString::fromUtf8("spinAC"));
        spinAC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinAC->sizePolicy().hasHeightForWidth());
        spinAC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinAC, 3, 3, 1, 1);

        label_9 = new QLabel(groupDetails);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        spinIE = new QSpinBox(groupDetails);
        spinIE->setObjectName(QString::fromUtf8("spinIE"));
        sizePolicy.setHeightForWidth(spinIE->sizePolicy().hasHeightForWidth());
        spinIE->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinIE, 4, 2, 1, 1);

        spinIC = new QSpinBox(groupDetails);
        spinIC->setObjectName(QString::fromUtf8("spinIC"));
        spinIC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinIC->sizePolicy().hasHeightForWidth());
        spinIC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinIC, 4, 3, 1, 1);

        label_10 = new QLabel(groupDetails);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 5, 0, 1, 2);

        spinOE = new QSpinBox(groupDetails);
        spinOE->setObjectName(QString::fromUtf8("spinOE"));
        sizePolicy.setHeightForWidth(spinOE->sizePolicy().hasHeightForWidth());
        spinOE->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinOE, 5, 2, 1, 1);

        spinOC = new QSpinBox(groupDetails);
        spinOC->setObjectName(QString::fromUtf8("spinOC"));
        spinOC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinOC->sizePolicy().hasHeightForWidth());
        spinOC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinOC, 5, 3, 1, 1);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        gridLayout->addWidget(buttonBox, 6, 5, 1, 1);


        verticalLayout->addWidget(groupDetails);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        pushPrevious = new QPushButton(FrmVesselType);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon1);

        horizontalLayout_6->addWidget(pushPrevious);

        pushNext = new QPushButton(FrmVesselType);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon2);

        horizontalLayout_6->addWidget(pushNext);


        verticalLayout->addLayout(horizontalLayout_6);

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
        pushPrevious->setText(QApplication::translate("FrmVesselType", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("FrmVesselType", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmVesselType: public Ui_FrmVesselType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMVESSELTYPE_H
