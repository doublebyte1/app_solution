/********************************************************************************
** Form generated from reading UI file 'frmframe.ui'
**
** Created: Mon 4. Apr 09:43:42 2011
**      by: Qt User Interface Compiler version 4.6.3
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
#include <QtGui/QFormLayout>
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

QT_BEGIN_NAMESPACE

class Ui_frmframe
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupPhysical;
    QGridLayout *gridLayout_2;
    QRadioButton *radioPreExistent;
    QComboBox *cmbPrexistent;
    QToolButton *toolView;
    QRadioButton *radioNew;
    QGroupBox *groupNew;
    QGridLayout *gridLayout;
    QRadioButton *radioCreate;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *radioCopy;
    QComboBox *cmbCopy;
    QToolButton *toolEdit;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupTime;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBackNext;
    QFormLayout *formLayout;
    QPushButton *pushPrevious;
    QPushButton *pushNext;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *frmframe)
    {
        if (frmframe->objectName().isEmpty())
            frmframe->setObjectName(QString::fromUtf8("frmframe"));
        frmframe->resize(747, 520);
        gridLayout_3 = new QGridLayout(frmframe);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupPhysical = new QGroupBox(frmframe);
        groupPhysical->setObjectName(QString::fromUtf8("groupPhysical"));
        gridLayout_2 = new QGridLayout(groupPhysical);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioPreExistent = new QRadioButton(groupPhysical);
        radioPreExistent->setObjectName(QString::fromUtf8("radioPreExistent"));

        gridLayout_2->addWidget(radioPreExistent, 0, 0, 1, 1);

        cmbPrexistent = new QComboBox(groupPhysical);
        cmbPrexistent->setObjectName(QString::fromUtf8("cmbPrexistent"));

        gridLayout_2->addWidget(cmbPrexistent, 0, 1, 1, 1);

        toolView = new QToolButton(groupPhysical);
        toolView->setObjectName(QString::fromUtf8("toolView"));

        gridLayout_2->addWidget(toolView, 0, 2, 1, 1);

        radioNew = new QRadioButton(groupPhysical);
        radioNew->setObjectName(QString::fromUtf8("radioNew"));

        gridLayout_2->addWidget(radioNew, 1, 0, 1, 1);

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

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupPhysical, 1, 0, 1, 2);

        groupTime = new QGroupBox(frmframe);
        groupTime->setObjectName(QString::fromUtf8("groupTime"));
        horizontalLayout = new QHBoxLayout(groupTime);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupTime);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(groupTime);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);


        gridLayout_3->addWidget(groupTime, 2, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(542, 45, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 4, 0, 1, 1);

        groupBackNext = new QGroupBox(frmframe);
        groupBackNext->setObjectName(QString::fromUtf8("groupBackNext"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBackNext->sizePolicy().hasHeightForWidth());
        groupBackNext->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(groupBackNext);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        pushPrevious = new QPushButton(groupBackNext);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        pushPrevious->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon);

        formLayout->setWidget(1, QFormLayout::LabelRole, pushPrevious);

        pushNext = new QPushButton(groupBackNext);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon1);

        formLayout->setWidget(1, QFormLayout::FieldRole, pushNext);


        gridLayout_3->addWidget(groupBackNext, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 3, 1, 1, 1);

        QWidget::setTabOrder(radioPreExistent, cmbPrexistent);
        QWidget::setTabOrder(cmbPrexistent, toolView);
        QWidget::setTabOrder(toolView, radioNew);
        QWidget::setTabOrder(radioNew, radioCreate);
        QWidget::setTabOrder(radioCreate, radioCopy);
        QWidget::setTabOrder(radioCopy, cmbCopy);
        QWidget::setTabOrder(cmbCopy, toolEdit);
        QWidget::setTabOrder(toolEdit, pushPrevious);
        QWidget::setTabOrder(pushPrevious, pushNext);

        retranslateUi(frmframe);
        QObject::connect(radioPreExistent, SIGNAL(clicked()), frmframe, SLOT(onChoosePreExistent()));
        QObject::connect(radioNew, SIGNAL(clicked()), frmframe, SLOT(onCreateNew()));

        QMetaObject::connectSlotsByName(frmframe);
    } // setupUi

    void retranslateUi(QWidget *frmframe)
    {
        frmframe->setWindowTitle(QApplication::translate("frmframe", "Form", 0, QApplication::UnicodeUTF8));
        groupPhysical->setTitle(QApplication::translate("frmframe", "Physical Frame", 0, QApplication::UnicodeUTF8));
        radioPreExistent->setText(QApplication::translate("frmframe", "Choose pre-existent", 0, QApplication::UnicodeUTF8));
        toolView->setText(QApplication::translate("frmframe", "...", 0, QApplication::UnicodeUTF8));
        radioNew->setText(QApplication::translate("frmframe", "Create New", 0, QApplication::UnicodeUTF8));
        groupNew->setTitle(QString());
        radioCreate->setText(QApplication::translate("frmframe", "Create from Scratch", 0, QApplication::UnicodeUTF8));
        radioCopy->setText(QApplication::translate("frmframe", "Copy from pre-existent", 0, QApplication::UnicodeUTF8));
        toolEdit->setText(QApplication::translate("frmframe", "...", 0, QApplication::UnicodeUTF8));
        groupTime->setTitle(QApplication::translate("frmframe", "Time Frame", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmframe", "Start Date", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmframe", "End Date", 0, QApplication::UnicodeUTF8));
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
