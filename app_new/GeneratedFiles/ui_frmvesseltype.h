/********************************************************************************
** Form generated from reading UI file 'frmvesseltype.ui'
**
** Created: Tue 3. May 17:07:40 2011
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
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmVesselType
{
public:
    QVBoxLayout *verticalLayout_5;
    QLabel *lbHeader;
    QLabel *label;
    QListView *listTypes;
    QGroupBox *groupTotals;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_11;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QSpinBox *spinNE;
    QSpinBox *spinAE;
    QSpinBox *spinIE;
    QSpinBox *spinOE;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QSpinBox *spinNC;
    QSpinBox *spinAC;
    QSpinBox *spinIC;
    QSpinBox *spinOC;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
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
        verticalLayout_5 = new QVBoxLayout(FrmVesselType);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lbHeader = new QLabel(FrmVesselType);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        verticalLayout_5->addWidget(lbHeader);

        label = new QLabel(FrmVesselType);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_5->addWidget(label);

        listTypes = new QListView(FrmVesselType);
        listTypes->setObjectName(QString::fromUtf8("listTypes"));
        listTypes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listTypes->setAlternatingRowColors(true);

        verticalLayout_5->addWidget(listTypes);

        groupTotals = new QGroupBox(FrmVesselType);
        groupTotals->setObjectName(QString::fromUtf8("groupTotals"));
        horizontalLayout_2 = new QHBoxLayout(groupTotals);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_11 = new QLabel(groupTotals);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout->addWidget(label_11);

        label_7 = new QLabel(groupTotals);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(groupTotals);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(groupTotals);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);

        label_10 = new QLabel(groupTotals);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout->addWidget(label_10);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(groupTotals);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label_4);

        spinNE = new QSpinBox(groupTotals);
        spinNE->setObjectName(QString::fromUtf8("spinNE"));
        sizePolicy.setHeightForWidth(spinNE->sizePolicy().hasHeightForWidth());
        spinNE->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(spinNE);

        spinAE = new QSpinBox(groupTotals);
        spinAE->setObjectName(QString::fromUtf8("spinAE"));
        sizePolicy.setHeightForWidth(spinAE->sizePolicy().hasHeightForWidth());
        spinAE->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(spinAE);

        spinIE = new QSpinBox(groupTotals);
        spinIE->setObjectName(QString::fromUtf8("spinIE"));
        sizePolicy.setHeightForWidth(spinIE->sizePolicy().hasHeightForWidth());
        spinIE->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(spinIE);

        spinOE = new QSpinBox(groupTotals);
        spinOE->setObjectName(QString::fromUtf8("spinOE"));
        sizePolicy.setHeightForWidth(spinOE->sizePolicy().hasHeightForWidth());
        spinOE->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(spinOE);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_5 = new QLabel(groupTotals);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_5);

        spinNC = new QSpinBox(groupTotals);
        spinNC->setObjectName(QString::fromUtf8("spinNC"));
        spinNC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinNC->sizePolicy().hasHeightForWidth());
        spinNC->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(spinNC);

        spinAC = new QSpinBox(groupTotals);
        spinAC->setObjectName(QString::fromUtf8("spinAC"));
        spinAC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinAC->sizePolicy().hasHeightForWidth());
        spinAC->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(spinAC);

        spinIC = new QSpinBox(groupTotals);
        spinIC->setObjectName(QString::fromUtf8("spinIC"));
        spinIC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinIC->sizePolicy().hasHeightForWidth());
        spinIC->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(spinIC);

        spinOC = new QSpinBox(groupTotals);
        spinOC->setObjectName(QString::fromUtf8("spinOC"));
        spinOC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinOC->sizePolicy().hasHeightForWidth());
        spinOC->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(spinOC);


        horizontalLayout->addLayout(verticalLayout_3);


        horizontalLayout_2->addLayout(horizontalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(groupTotals);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        verticalLayout_4->addWidget(buttonBox);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_5->addWidget(groupTotals);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        pushPrevious = new QPushButton(FrmVesselType);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon);

        horizontalLayout_6->addWidget(pushPrevious);

        pushNext = new QPushButton(FrmVesselType);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon1);

        horizontalLayout_6->addWidget(pushNext);


        verticalLayout_5->addLayout(horizontalLayout_6);


        retranslateUi(FrmVesselType);

        QMetaObject::connectSlotsByName(FrmVesselType);
    } // setupUi

    void retranslateUi(QWidget *FrmVesselType)
    {
        FrmVesselType->setWindowTitle(QApplication::translate("FrmVesselType", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("FrmVesselType", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmVesselType", "Select cell vessel type:", 0, QApplication::UnicodeUTF8));
        groupTotals->setTitle(QApplication::translate("FrmVesselType", "Totals", 0, QApplication::UnicodeUTF8));
        label_11->setText(QString());
        label_7->setText(QApplication::translate("FrmVesselType", "No of Vessels", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FrmVesselType", "Active Vessels", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FrmVesselType", "Inactive Vessels", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FrmVesselType", "Vessels from Outside", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FrmVesselType", "Estimated", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FrmVesselType", "Calculated", 0, QApplication::UnicodeUTF8));
        pushPrevious->setText(QApplication::translate("FrmVesselType", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("FrmVesselType", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmVesselType: public Ui_FrmVesselType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMVESSELTYPE_H
