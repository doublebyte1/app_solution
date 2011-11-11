/********************************************************************************
** Form generated from reading UI file 'frmframe.ui'
**
** Created: Wed 9. Nov 11:05:25 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMFRAME_H
#define UI_FRMFRAME_H

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
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "customtimectrl.h"

QT_BEGIN_NAMESPACE

class Ui_frmframe
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_3;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushNew;
    QPushButton *pushEdit;
    QPushButton *pushRemove;
    QGroupBox *groupDetails;
    QGridLayout *gridLayout_4;
    QGroupBox *groupPhysical;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QComboBox *cmbPrexistent;
    QToolButton *toolView;
    QLabel *label_3;
    QGroupBox *groupNew;
    QGridLayout *gridLayout;
    QRadioButton *radioCreate;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *radioCopy;
    QComboBox *cmbCopy;
    QToolButton *toolEdit;
    QGroupBox *groupTime;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLabel *label_2;
    CustomTimeCtrl *customDtStart;
    CustomTimeCtrl *customDtEnd;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupProcess;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QToolButton *toolProcess;
    QLabel *lbHeader;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBackNext;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *frmframe)
    {
        if (frmframe->objectName().isEmpty())
            frmframe->setObjectName(QString::fromUtf8("frmframe"));
        frmframe->resize(814, 536);
        verticalLayout_4 = new QVBoxLayout(frmframe);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_6 = new QLabel(frmframe);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout_2);

        tableView = new QTableView(frmframe);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(tableView);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushNew = new QPushButton(frmframe);
        pushNew->setObjectName(QString::fromUtf8("pushNew"));
        sizePolicy.setHeightForWidth(pushNew->sizePolicy().hasHeightForWidth());
        pushNew->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNew->setIcon(icon);

        verticalLayout_3->addWidget(pushNew);

        pushEdit = new QPushButton(frmframe);
        pushEdit->setObjectName(QString::fromUtf8("pushEdit"));
        sizePolicy.setHeightForWidth(pushEdit->sizePolicy().hasHeightForWidth());
        pushEdit->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushEdit->setIcon(icon1);
        pushEdit->setCheckable(true);

        verticalLayout_3->addWidget(pushEdit);

        pushRemove = new QPushButton(frmframe);
        pushRemove->setObjectName(QString::fromUtf8("pushRemove"));
        sizePolicy.setHeightForWidth(pushRemove->sizePolicy().hasHeightForWidth());
        pushRemove->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushRemove->setIcon(icon2);

        verticalLayout_3->addWidget(pushRemove);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        groupDetails = new QGroupBox(frmframe);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        gridLayout_4 = new QGridLayout(groupDetails);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupPhysical = new QGroupBox(groupDetails);
        groupPhysical->setObjectName(QString::fromUtf8("groupPhysical"));
        gridLayout_2 = new QGridLayout(groupPhysical);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(groupPhysical);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        cmbPrexistent = new QComboBox(groupPhysical);
        cmbPrexistent->setObjectName(QString::fromUtf8("cmbPrexistent"));

        gridLayout_2->addWidget(cmbPrexistent, 0, 1, 1, 1);

        toolView = new QToolButton(groupPhysical);
        toolView->setObjectName(QString::fromUtf8("toolView"));

        gridLayout_2->addWidget(toolView, 0, 2, 1, 1);

        label_3 = new QLabel(groupPhysical);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        groupNew = new QGroupBox(groupPhysical);
        groupNew->setObjectName(QString::fromUtf8("groupNew"));
        gridLayout = new QGridLayout(groupNew);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioCreate = new QRadioButton(groupNew);
        radioCreate->setObjectName(QString::fromUtf8("radioCreate"));

        gridLayout->addWidget(radioCreate, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        radioCopy = new QRadioButton(groupNew);
        radioCopy->setObjectName(QString::fromUtf8("radioCopy"));

        gridLayout->addWidget(radioCopy, 1, 0, 1, 1);

        cmbCopy = new QComboBox(groupNew);
        cmbCopy->setObjectName(QString::fromUtf8("cmbCopy"));

        gridLayout->addWidget(cmbCopy, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupNew, 1, 1, 2, 1);

        toolEdit = new QToolButton(groupPhysical);
        toolEdit->setObjectName(QString::fromUtf8("toolEdit"));

        gridLayout_2->addWidget(toolEdit, 2, 2, 1, 1);


        gridLayout_4->addWidget(groupPhysical, 0, 0, 1, 2);

        groupTime = new QGroupBox(groupDetails);
        groupTime->setObjectName(QString::fromUtf8("groupTime"));
        gridLayout_3 = new QGridLayout(groupTime);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(groupTime);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupTime);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        customDtStart = new CustomTimeCtrl(groupTime);
        customDtStart->setObjectName(QString::fromUtf8("customDtStart"));
        sizePolicy1.setHeightForWidth(customDtStart->sizePolicy().hasHeightForWidth());
        customDtStart->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(customDtStart, 1, 0, 1, 1);

        customDtEnd = new CustomTimeCtrl(groupTime);
        customDtEnd->setObjectName(QString::fromUtf8("customDtEnd"));
        sizePolicy1.setHeightForWidth(customDtEnd->sizePolicy().hasHeightForWidth());
        customDtEnd->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(customDtEnd, 1, 1, 1, 1);


        gridLayout_4->addWidget(groupTime, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupProcess = new QGroupBox(groupDetails);
        groupProcess->setObjectName(QString::fromUtf8("groupProcess"));
        groupProcess->setFlat(true);
        horizontalLayout_4 = new QHBoxLayout(groupProcess);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(groupProcess);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        toolProcess = new QToolButton(groupProcess);
        toolProcess->setObjectName(QString::fromUtf8("toolProcess"));

        horizontalLayout_3->addWidget(toolProcess);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(groupProcess);

        lbHeader = new QLabel(groupDetails);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));

        verticalLayout->addWidget(lbHeader);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        gridLayout_4->addLayout(verticalLayout, 1, 1, 1, 1);


        verticalLayout_4->addWidget(groupDetails);

        groupBackNext = new QGroupBox(frmframe);
        groupBackNext->setObjectName(QString::fromUtf8("groupBackNext"));
        sizePolicy.setHeightForWidth(groupBackNext->sizePolicy().hasHeightForWidth());
        groupBackNext->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(groupBackNext);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushPrevious = new QPushButton(groupBackNext);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        pushPrevious->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon3);

        horizontalLayout_2->addWidget(pushPrevious);

        pushNext = new QPushButton(groupBackNext);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        pushNext->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon4);

        horizontalLayout_2->addWidget(pushNext);


        verticalLayout_4->addWidget(groupBackNext);

#ifndef QT_NO_SHORTCUT
        label_6->setBuddy(tableView);
#endif // QT_NO_SHORTCUT

        retranslateUi(frmframe);
        QObject::connect(pushNext, SIGNAL(clicked()), frmframe, SLOT(next()));
        QObject::connect(pushNew, SIGNAL(clicked()), frmframe, SLOT(createRecord()));
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), frmframe, SLOT(onButtonClick(QAbstractButton*)));
        QObject::connect(pushEdit, SIGNAL(clicked(bool)), frmframe, SLOT(editRecord(bool)));
        QObject::connect(pushRemove, SIGNAL(clicked()), frmframe, SLOT(removeRecord()));
        QObject::connect(cmbPrexistent, SIGNAL(currentIndexChanged(int)), frmframe, SLOT(adjustFrmSamplingMode()));

        QMetaObject::connectSlotsByName(frmframe);
    } // setupUi

    void retranslateUi(QWidget *frmframe)
    {
        frmframe->setWindowTitle(QApplication::translate("frmframe", "Form", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("frmframe", "Choose Sampling Frame:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushNew->setToolTip(QApplication::translate("frmframe", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNew->setStatusTip(QApplication::translate("frmframe", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNew->setWhatsThis(QApplication::translate("frmframe", "Creates new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNew->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushEdit->setToolTip(QApplication::translate("frmframe", "Edit record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushEdit->setStatusTip(QApplication::translate("frmframe", "Edit record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushEdit->setWhatsThis(QApplication::translate("frmframe", "Edits record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushEdit->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushRemove->setToolTip(QApplication::translate("frmframe", "Remove record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushRemove->setStatusTip(QApplication::translate("frmframe", "Remove record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushRemove->setWhatsThis(QApplication::translate("frmframe", "Removes record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushRemove->setText(QString());
        groupDetails->setTitle(QApplication::translate("frmframe", "Details", 0, QApplication::UnicodeUTF8));
        groupPhysical->setTitle(QApplication::translate("frmframe", "Physical Frame", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmframe", "Choose frame", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolView->setToolTip(QApplication::translate("frmframe", "View Frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolView->setStatusTip(QApplication::translate("frmframe", "View Frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        toolView->setWhatsThis(QApplication::translate("frmframe", "Allows viewing this frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolView->setText(QApplication::translate("frmframe", "...", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("frmframe", "Create New", 0, QApplication::UnicodeUTF8));
        groupNew->setTitle(QString());
        radioCreate->setText(QApplication::translate("frmframe", "Create from Scratch", 0, QApplication::UnicodeUTF8));
        radioCopy->setText(QApplication::translate("frmframe", "Copy from pre-existent", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolEdit->setToolTip(QApplication::translate("frmframe", "Edit Frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolEdit->setStatusTip(QApplication::translate("frmframe", "Edit Frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        toolEdit->setWhatsThis(QApplication::translate("frmframe", "Allows editing this frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        toolEdit->setText(QApplication::translate("frmframe", "...", 0, QApplication::UnicodeUTF8));
        groupTime->setTitle(QApplication::translate("frmframe", "Time Frame", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmframe", "Start Date", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmframe", "End Date", 0, QApplication::UnicodeUTF8));
        groupProcess->setTitle(QString());
        label_5->setText(QApplication::translate("frmframe", "Sampling Technique", 0, QApplication::UnicodeUTF8));
        toolProcess->setText(QApplication::translate("frmframe", "...", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("frmframe", "LBHEADER", 0, QApplication::UnicodeUTF8));
        groupBackNext->setTitle(QString());
        pushPrevious->setText(QApplication::translate("frmframe", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("frmframe", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmframe: public Ui_frmframe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFRAME_H
