/********************************************************************************
** Form generated from reading UI file 'frmvesseltype.ui'
**
** Created: Wed 4. May 11:44:18 2011
**      by: Qt User Interface Compiler version 4.6.3
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
    QGridLayout *gridLayout;
    QLabel *label_11;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_7;
    QSpinBox *spinNE;
    QSpinBox *spinNC;
    QPlainTextEdit *plainTextEdit;
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
        gridLayout = new QGridLayout(groupTotals);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_11 = new QLabel(groupTotals);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 0, 0, 2, 2);

        label_4 = new QLabel(groupTotals);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_4, 0, 2, 2, 1);

        label_5 = new QLabel(groupTotals);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_5, 0, 3, 2, 1);

        label_2 = new QLabel(groupTotals);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 4, 1, 1);

        label_7 = new QLabel(groupTotals);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 1, 2, 1);

        spinNE = new QSpinBox(groupTotals);
        spinNE->setObjectName(QString::fromUtf8("spinNE"));
        sizePolicy.setHeightForWidth(spinNE->sizePolicy().hasHeightForWidth());
        spinNE->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinNE, 2, 2, 1, 1);

        spinNC = new QSpinBox(groupTotals);
        spinNC->setObjectName(QString::fromUtf8("spinNC"));
        spinNC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinNC->sizePolicy().hasHeightForWidth());
        spinNC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinNC, 2, 3, 1, 1);

        plainTextEdit = new QPlainTextEdit(groupTotals);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 2, 4, 4, 2);

        label_8 = new QLabel(groupTotals);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 3, 1, 1, 1);

        spinAE = new QSpinBox(groupTotals);
        spinAE->setObjectName(QString::fromUtf8("spinAE"));
        sizePolicy.setHeightForWidth(spinAE->sizePolicy().hasHeightForWidth());
        spinAE->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinAE, 3, 2, 1, 1);

        spinAC = new QSpinBox(groupTotals);
        spinAC->setObjectName(QString::fromUtf8("spinAC"));
        spinAC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinAC->sizePolicy().hasHeightForWidth());
        spinAC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinAC, 3, 3, 1, 1);

        label_9 = new QLabel(groupTotals);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 4, 1, 1, 1);

        spinIE = new QSpinBox(groupTotals);
        spinIE->setObjectName(QString::fromUtf8("spinIE"));
        sizePolicy.setHeightForWidth(spinIE->sizePolicy().hasHeightForWidth());
        spinIE->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinIE, 4, 2, 1, 1);

        spinIC = new QSpinBox(groupTotals);
        spinIC->setObjectName(QString::fromUtf8("spinIC"));
        spinIC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinIC->sizePolicy().hasHeightForWidth());
        spinIC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinIC, 4, 3, 1, 1);

        label_10 = new QLabel(groupTotals);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 5, 1, 1, 1);

        spinOE = new QSpinBox(groupTotals);
        spinOE->setObjectName(QString::fromUtf8("spinOE"));
        sizePolicy.setHeightForWidth(spinOE->sizePolicy().hasHeightForWidth());
        spinOE->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinOE, 5, 2, 1, 1);

        spinOC = new QSpinBox(groupTotals);
        spinOC->setObjectName(QString::fromUtf8("spinOC"));
        spinOC->setEnabled(false);
        sizePolicy.setHeightForWidth(spinOC->sizePolicy().hasHeightForWidth());
        spinOC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(spinOC, 5, 3, 1, 1);

        buttonBox = new QDialogButtonBox(groupTotals);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        gridLayout->addWidget(buttonBox, 6, 5, 1, 1);


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

#ifndef QT_NO_SHORTCUT
        label->setBuddy(listTypes);
        label_4->setBuddy(spinNE);
        label_5->setBuddy(spinNC);
        label_2->setBuddy(plainTextEdit);
        label_7->setBuddy(spinNE);
        label_8->setBuddy(spinAE);
        label_9->setBuddy(spinIE);
        label_10->setBuddy(spinOE);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(listTypes, spinNE);
        QWidget::setTabOrder(spinNE, spinNC);
        QWidget::setTabOrder(spinNC, spinAE);
        QWidget::setTabOrder(spinAE, spinAC);
        QWidget::setTabOrder(spinAC, spinIE);
        QWidget::setTabOrder(spinIE, spinIC);
        QWidget::setTabOrder(spinIC, spinOE);
        QWidget::setTabOrder(spinOE, spinOC);
        QWidget::setTabOrder(spinOC, plainTextEdit);
        QWidget::setTabOrder(plainTextEdit, buttonBox);
        QWidget::setTabOrder(buttonBox, pushPrevious);
        QWidget::setTabOrder(pushPrevious, pushNext);

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
