/********************************************************************************
** Form generated from reading UI file 'frmframe.ui'
**
** Created: Wed 11. May 13:06:52 2011
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
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "customtimectrl.h"

QT_BEGIN_NAMESPACE

class Ui_frmframe
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupPhysical;
    QGridLayout *gridLayout_2;
    QComboBox *cmbPrexistent;
    QToolButton *toolView;
    QGroupBox *groupNew;
    QGridLayout *gridLayout;
    QRadioButton *radioCreate;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *radioCopy;
    QComboBox *cmbCopy;
    QToolButton *toolEdit;
    QLabel *label_3;
    QLabel *label_4;
    QGroupBox *groupTime;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLabel *label_2;
    CustomTimeCtrl *customDtStart;
    CustomTimeCtrl *customDtEnd;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBackNext;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushPrevious;
    QPushButton *pushApply;
    QPushButton *pushNext;

    void setupUi(QWidget *frmframe)
    {
        if (frmframe->objectName().isEmpty())
            frmframe->setObjectName(QString::fromUtf8("frmframe"));
        frmframe->resize(770, 520);
        gridLayout_4 = new QGridLayout(frmframe);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupPhysical = new QGroupBox(frmframe);
        groupPhysical->setObjectName(QString::fromUtf8("groupPhysical"));
        gridLayout_2 = new QGridLayout(groupPhysical);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cmbPrexistent = new QComboBox(groupPhysical);
        cmbPrexistent->setObjectName(QString::fromUtf8("cmbPrexistent"));

        gridLayout_2->addWidget(cmbPrexistent, 0, 1, 1, 1);

        toolView = new QToolButton(groupPhysical);
        toolView->setObjectName(QString::fromUtf8("toolView"));

        gridLayout_2->addWidget(toolView, 0, 2, 1, 1);

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


        gridLayout_2->addWidget(groupNew, 2, 1, 1, 2);

        toolEdit = new QToolButton(groupPhysical);
        toolEdit->setObjectName(QString::fromUtf8("toolEdit"));

        gridLayout_2->addWidget(toolEdit, 3, 2, 1, 1);

        label_3 = new QLabel(groupPhysical);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(groupPhysical);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupPhysical, 0, 0, 1, 2);

        groupTime = new QGroupBox(frmframe);
        groupTime->setObjectName(QString::fromUtf8("groupTime"));
        gridLayout_3 = new QGridLayout(groupTime);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(groupTime);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupTime);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_2, 0, 2, 1, 1);

        customDtStart = new CustomTimeCtrl(groupTime);
        customDtStart->setObjectName(QString::fromUtf8("customDtStart"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(customDtStart->sizePolicy().hasHeightForWidth());
        customDtStart->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(customDtStart, 1, 1, 1, 1);

        customDtEnd = new CustomTimeCtrl(groupTime);
        customDtEnd->setObjectName(QString::fromUtf8("customDtEnd"));
        sizePolicy1.setHeightForWidth(customDtEnd->sizePolicy().hasHeightForWidth());
        customDtEnd->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(customDtEnd, 1, 2, 1, 1);


        gridLayout_4->addWidget(groupTime, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(484, 45, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 2, 0, 1, 1);

        groupBackNext = new QGroupBox(frmframe);
        groupBackNext->setObjectName(QString::fromUtf8("groupBackNext"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBackNext->sizePolicy().hasHeightForWidth());
        groupBackNext->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(groupBackNext);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushPrevious = new QPushButton(groupBackNext);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        pushPrevious->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon);

        horizontalLayout_2->addWidget(pushPrevious);

        pushApply = new QPushButton(groupBackNext);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));

        horizontalLayout_2->addWidget(pushApply);

        pushNext = new QPushButton(groupBackNext);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon1);

        horizontalLayout_2->addWidget(pushNext);


        gridLayout_4->addWidget(groupBackNext, 2, 1, 1, 1);

        QWidget::setTabOrder(cmbPrexistent, toolView);
        QWidget::setTabOrder(toolView, radioCreate);
        QWidget::setTabOrder(radioCreate, radioCopy);
        QWidget::setTabOrder(radioCopy, cmbCopy);
        QWidget::setTabOrder(cmbCopy, toolEdit);
        QWidget::setTabOrder(toolEdit, pushPrevious);

        retranslateUi(frmframe);
        QObject::connect(radioCreate, SIGNAL(clicked(bool)), cmbCopy, SLOT(setDisabled(bool)));
        QObject::connect(radioCopy, SIGNAL(clicked(bool)), cmbCopy, SLOT(setEnabled(bool)));
        QObject::connect(pushApply, SIGNAL(clicked()), frmframe, SLOT(apply()));
        QObject::connect(pushNext, SIGNAL(clicked()), frmframe, SLOT(next()));

        QMetaObject::connectSlotsByName(frmframe);
    } // setupUi

    void retranslateUi(QWidget *frmframe)
    {
        frmframe->setWindowTitle(QApplication::translate("frmframe", "Form", 0, QApplication::UnicodeUTF8));
        groupPhysical->setTitle(QApplication::translate("frmframe", "Physical Frame", 0, QApplication::UnicodeUTF8));
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
        label_3->setText(QApplication::translate("frmframe", "Create New", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmframe", "Choose frame", 0, QApplication::UnicodeUTF8));
        groupTime->setTitle(QApplication::translate("frmframe", "Time Frame", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmframe", "Start Date", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmframe", "End Date", 0, QApplication::UnicodeUTF8));
        groupBackNext->setTitle(QString());
        pushPrevious->setText(QApplication::translate("frmframe", "Previous", 0, QApplication::UnicodeUTF8));
        pushApply->setText(QApplication::translate("frmframe", "Apply", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("frmframe", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmframe: public Ui_frmframe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFRAME_H
