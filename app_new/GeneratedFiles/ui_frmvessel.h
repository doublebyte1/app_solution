/********************************************************************************
** Form generated from reading UI file 'frmvessel.ui'
**
** Created: Fri 6. May 16:25:25 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMVESSEL_H
#define UI_FRMVESSEL_H

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
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmVessel
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *lbHeader;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *pushNew;
    QToolButton *toolButton;
    QGroupBox *groupDetails;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cmbVessel;
    QGroupBox *groupFT;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QSpinBox *spinET;
    QSpinBox *spinCT;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QLabel *label_3;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *frmVessel)
    {
        if (frmVessel->objectName().isEmpty())
            frmVessel->setObjectName(QString::fromUtf8("frmVessel"));
        frmVessel->resize(703, 545);
        verticalLayout_2 = new QVBoxLayout(frmVessel);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lbHeader = new QLabel(frmVessel);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        verticalLayout_2->addWidget(lbHeader);

        label_5 = new QLabel(frmVessel);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(frmVessel);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushNew = new QPushButton(frmVessel);
        pushNew->setObjectName(QString::fromUtf8("pushNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNew->setIcon(icon);

        verticalLayout->addWidget(pushNew);

        toolButton = new QToolButton(frmVessel);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        verticalLayout->addWidget(toolButton);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        groupDetails = new QGroupBox(frmVessel);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        gridLayout = new QGridLayout(groupDetails);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupDetails);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cmbVessel = new QComboBox(groupDetails);
        cmbVessel->setObjectName(QString::fromUtf8("cmbVessel"));

        gridLayout->addWidget(cmbVessel, 0, 1, 1, 1);

        groupFT = new QGroupBox(groupDetails);
        groupFT->setObjectName(QString::fromUtf8("groupFT"));
        sizePolicy.setHeightForWidth(groupFT->sizePolicy().hasHeightForWidth());
        groupFT->setSizePolicy(sizePolicy);
        groupFT->setFlat(true);
        gridLayout_2 = new QGridLayout(groupFT);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupFT);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        spinET = new QSpinBox(groupFT);
        spinET->setObjectName(QString::fromUtf8("spinET"));

        gridLayout_2->addWidget(spinET, 1, 1, 1, 1);

        spinCT = new QSpinBox(groupFT);
        spinCT->setObjectName(QString::fromUtf8("spinCT"));

        gridLayout_2->addWidget(spinCT, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(411, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 3, 1, 1);

        label_4 = new QLabel(groupFT);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        label_3 = new QLabel(groupFT);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_3, 0, 1, 1, 1);


        gridLayout->addWidget(groupFT, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);


        verticalLayout_2->addWidget(groupDetails);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushPrevious = new QPushButton(frmVessel);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon1);

        horizontalLayout_2->addWidget(pushPrevious);

        pushNext = new QPushButton(frmVessel);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon2);

        horizontalLayout_2->addWidget(pushNext);


        verticalLayout_2->addLayout(horizontalLayout_2);

#ifndef QT_NO_SHORTCUT
        label_5->setBuddy(tableView);
        label->setBuddy(cmbVessel);
        label_2->setBuddy(spinET);
        label_4->setBuddy(spinCT);
        label_3->setBuddy(spinET);
#endif // QT_NO_SHORTCUT

        retranslateUi(frmVessel);

        QMetaObject::connectSlotsByName(frmVessel);
    } // setupUi

    void retranslateUi(QWidget *frmVessel)
    {
        frmVessel->setWindowTitle(QApplication::translate("frmVessel", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("frmVessel", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("frmVessel", "Select sampled vessel:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushNew->setToolTip(QApplication::translate("frmVessel", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNew->setStatusTip(QApplication::translate("frmVessel", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNew->setWhatsThis(QApplication::translate("frmVessel", "Creates new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNew->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton->setToolTip(QApplication::translate("frmVessel", "Add vessel not present on this list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolButton->setStatusTip(QApplication::translate("frmVessel", "Add vessel not present on this list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        toolButton->setWhatsThis(QApplication::translate("frmVessel", "This tool allows to setup temporary frame changes concerning adding new vessels or importing them from another port", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolButton->setText(QApplication::translate("frmVessel", "...", 0, QApplication::UnicodeUTF8));
        groupDetails->setTitle(QApplication::translate("frmVessel", "Details", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmVessel", "Choose vessel:", 0, QApplication::UnicodeUTF8));
        groupFT->setTitle(QString());
        label_2->setText(QApplication::translate("frmVessel", "Number of fishing trips:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmVessel", "Calculated", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("frmVessel", "Estimated", 0, QApplication::UnicodeUTF8));
        pushPrevious->setText(QApplication::translate("frmVessel", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("frmVessel", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmVessel: public Ui_frmVessel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMVESSEL_H
