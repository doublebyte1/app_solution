/********************************************************************************
** Form generated from reading UI file 'frmTables.ui'
**
** Created: Fri 9. Dec 10:57:53 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTABLES_H
#define UI_FRMTABLES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmTables
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QGroupBox *groupType;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioDefinition;
    QRadioButton *radioData;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupOptions;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkShowViews;
    QCheckBox *checkValidate;
    QCheckBox *checkVerify;
    QCheckBox *checkCreate;
    QCheckBox *checkBackups;
    QCheckBox *checkAppend;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton;
    QLabel *lbFile;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QTableView *previewTable;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushAll;
    QPushButton *pushNone;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushOk;
    QPushButton *pushClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *frmTables)
    {
        if (frmTables->objectName().isEmpty())
            frmTables->setObjectName(QString::fromUtf8("frmTables"));
        frmTables->resize(650, 497);
        gridLayout = new QGridLayout(frmTables);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget = new QListWidget(frmTables);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 3, 1);

        groupType = new QGroupBox(frmTables);
        groupType->setObjectName(QString::fromUtf8("groupType"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupType->sizePolicy().hasHeightForWidth());
        groupType->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupType);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        radioDefinition = new QRadioButton(groupType);
        radioDefinition->setObjectName(QString::fromUtf8("radioDefinition"));

        verticalLayout_2->addWidget(radioDefinition);

        radioData = new QRadioButton(groupType);
        radioData->setObjectName(QString::fromUtf8("radioData"));

        verticalLayout_2->addWidget(radioData);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        gridLayout->addWidget(groupType, 0, 1, 1, 1);

        groupOptions = new QGroupBox(frmTables);
        groupOptions->setObjectName(QString::fromUtf8("groupOptions"));
        verticalLayout = new QVBoxLayout(groupOptions);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkShowViews = new QCheckBox(groupOptions);
        checkShowViews->setObjectName(QString::fromUtf8("checkShowViews"));

        verticalLayout->addWidget(checkShowViews);

        checkValidate = new QCheckBox(groupOptions);
        checkValidate->setObjectName(QString::fromUtf8("checkValidate"));

        verticalLayout->addWidget(checkValidate);

        checkVerify = new QCheckBox(groupOptions);
        checkVerify->setObjectName(QString::fromUtf8("checkVerify"));
        checkVerify->setIconSize(QSize(16, 14));

        verticalLayout->addWidget(checkVerify);

        checkCreate = new QCheckBox(groupOptions);
        checkCreate->setObjectName(QString::fromUtf8("checkCreate"));

        verticalLayout->addWidget(checkCreate);

        checkBackups = new QCheckBox(groupOptions);
        checkBackups->setObjectName(QString::fromUtf8("checkBackups"));

        verticalLayout->addWidget(checkBackups);

        checkAppend = new QCheckBox(groupOptions);
        checkAppend->setObjectName(QString::fromUtf8("checkAppend"));

        verticalLayout->addWidget(checkAppend);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButton = new QToolButton(groupOptions);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout_2->addWidget(toolButton);

        lbFile = new QLabel(groupOptions);
        lbFile->setObjectName(QString::fromUtf8("lbFile"));

        horizontalLayout_2->addWidget(lbFile);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalSpacer = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(groupOptions, 1, 1, 1, 1);

        previewTable = new QTableView(frmTables);
        previewTable->setObjectName(QString::fromUtf8("previewTable"));

        gridLayout->addWidget(previewTable, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushAll = new QPushButton(frmTables);
        pushAll->setObjectName(QString::fromUtf8("pushAll"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushAll->sizePolicy().hasHeightForWidth());
        pushAll->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushAll);

        pushNone = new QPushButton(frmTables);
        pushNone->setObjectName(QString::fromUtf8("pushNone"));
        sizePolicy1.setHeightForWidth(pushNone->sizePolicy().hasHeightForWidth());
        pushNone->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushNone);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushOk = new QPushButton(frmTables);
        pushOk->setObjectName(QString::fromUtf8("pushOk"));
        sizePolicy1.setHeightForWidth(pushOk->sizePolicy().hasHeightForWidth());
        pushOk->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushOk);

        pushClose = new QPushButton(frmTables);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));
        sizePolicy1.setHeightForWidth(pushClose->sizePolicy().hasHeightForWidth());
        pushClose->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushClose);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(260, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        lbFile->setBuddy(toolButton);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(listWidget, radioDefinition);
        QWidget::setTabOrder(radioDefinition, radioData);
        QWidget::setTabOrder(radioData, checkShowViews);
        QWidget::setTabOrder(checkShowViews, checkValidate);
        QWidget::setTabOrder(checkValidate, checkVerify);
        QWidget::setTabOrder(checkVerify, checkCreate);
        QWidget::setTabOrder(checkCreate, checkBackups);
        QWidget::setTabOrder(checkBackups, checkAppend);
        QWidget::setTabOrder(checkAppend, toolButton);
        QWidget::setTabOrder(toolButton, previewTable);
        QWidget::setTabOrder(previewTable, pushAll);
        QWidget::setTabOrder(pushAll, pushNone);
        QWidget::setTabOrder(pushNone, pushOk);
        QWidget::setTabOrder(pushOk, pushClose);

        retranslateUi(frmTables);
        QObject::connect(pushAll, SIGNAL(clicked()), listWidget, SLOT(selectAll()));
        QObject::connect(pushNone, SIGNAL(clicked()), listWidget, SLOT(clearSelection()));
        QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), frmTables, SLOT(preview(QListWidgetItem*)));
        QObject::connect(pushNone, SIGNAL(clicked()), previewTable, SLOT(hide()));
        QObject::connect(pushAll, SIGNAL(clicked()), previewTable, SLOT(hide()));
        QObject::connect(pushOk, SIGNAL(clicked()), frmTables, SLOT(Ok()));
        QObject::connect(toolButton, SIGNAL(clicked()), frmTables, SLOT(chooseFile()));
        QObject::connect(checkCreate, SIGNAL(clicked(bool)), frmTables, SLOT(hideAppend(bool)));
        QObject::connect(checkShowViews, SIGNAL(clicked()), frmTables, SLOT(readTableNames()));
        QObject::connect(checkCreate, SIGNAL(clicked(bool)), checkBackups, SLOT(setVisible(bool)));
        QObject::connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), frmTables, SLOT(loadItem(QListWidgetItem*)));

        QMetaObject::connectSlotsByName(frmTables);
    } // setupUi

    void retranslateUi(QWidget *frmTables)
    {
        frmTables->setWindowTitle(QApplication::translate("frmTables", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupType->setToolTip(QApplication::translate("frmTables", "Type of Operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        groupType->setStatusTip(QApplication::translate("frmTables", "Type of Operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        groupType->setWhatsThis(QApplication::translate("frmTables", "Type of Operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupType->setTitle(QApplication::translate("frmTables", "Preview", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioDefinition->setToolTip(QApplication::translate("frmTables", "Table Definition", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioDefinition->setStatusTip(QApplication::translate("frmTables", "Table Definition", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        radioDefinition->setWhatsThis(QApplication::translate("frmTables", "Table Definition", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        radioDefinition->setText(QApplication::translate("frmTables", "Definition", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioData->setToolTip(QApplication::translate("frmTables", "Table Contents", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioData->setStatusTip(QApplication::translate("frmTables", "Table Contents", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        radioData->setWhatsThis(QApplication::translate("frmTables", "Table Contents", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        radioData->setText(QApplication::translate("frmTables", "Data", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupOptions->setToolTip(QApplication::translate("frmTables", "Import Options", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        groupOptions->setStatusTip(QApplication::translate("frmTables", "Import Options", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        groupOptions->setWhatsThis(QApplication::translate("frmTables", "Import Options", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupOptions->setTitle(QApplication::translate("frmTables", "Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkShowViews->setToolTip(QApplication::translate("frmTables", "Show Views", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        checkShowViews->setStatusTip(QApplication::translate("frmTables", "Show Views", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        checkShowViews->setWhatsThis(QApplication::translate("frmTables", "Show Views", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        checkShowViews->setText(QApplication::translate("frmTables", "Show Views", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkValidate->setToolTip(QApplication::translate("frmTables", "Schema validation (may not work for extremely large files!)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        checkValidate->setStatusTip(QApplication::translate("frmTables", "Schema validation (may not work for extremely large files!)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        checkValidate->setWhatsThis(QApplication::translate("frmTables", "Schema validation (may not work for extremely large files!)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        checkValidate->setText(QApplication::translate("frmTables", "Schema Validation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkVerify->setToolTip(QApplication::translate("frmTables", "Verify Table Structure in the Database", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        checkVerify->setStatusTip(QApplication::translate("frmTables", "Verify Table Structure in the Database", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        checkVerify->setWhatsThis(QApplication::translate("frmTables", "Verifies Table Structure in the Database", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        checkVerify->setText(QApplication::translate("frmTables", "Enforce Table Structure Policies", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkCreate->setToolTip(QApplication::translate("frmTables", "Create new table(s), deleting existing one(s)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        checkCreate->setStatusTip(QApplication::translate("frmTables", "Create new table(s), deleting existing one(s)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        checkCreate->setWhatsThis(QApplication::translate("frmTables", "Create new table(s), deleting existing one(s)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        checkCreate->setText(QApplication::translate("frmTables", "Create Table(s)", 0, QApplication::UnicodeUTF8));
        checkBackups->setText(QApplication::translate("frmTables", "Backup Table(s)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkAppend->setToolTip(QApplication::translate("frmTables", "Append data, keeping existing one", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        checkAppend->setStatusTip(QApplication::translate("frmTables", "Append data, keeping existing one", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        checkAppend->setWhatsThis(QApplication::translate("frmTables", "Append data, keeping existing one", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        checkAppend->setText(QApplication::translate("frmTables", "Append Data to Existing Table(s)", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("frmTables", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lbFile->setToolTip(QApplication::translate("frmTables", "Select File to Import From", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lbFile->setStatusTip(QApplication::translate("frmTables", "Select File to Import From", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        lbFile->setWhatsThis(QApplication::translate("frmTables", "Select File to Import From", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        lbFile->setText(QApplication::translate("frmTables", "Choose File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushAll->setToolTip(QApplication::translate("frmTables", "Select All", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushAll->setStatusTip(QApplication::translate("frmTables", "Select All", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushAll->setWhatsThis(QApplication::translate("frmTables", "Selects All", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushAll->setText(QApplication::translate("frmTables", "Select &All", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushNone->setToolTip(QApplication::translate("frmTables", "Select None", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNone->setStatusTip(QApplication::translate("frmTables", "Select None", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNone->setWhatsThis(QApplication::translate("frmTables", "Selects None", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNone->setText(QApplication::translate("frmTables", "Select &None", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushOk->setToolTip(QApplication::translate("frmTables", "Apply Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushOk->setStatusTip(QApplication::translate("frmTables", "Apply Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushOk->setWhatsThis(QApplication::translate("frmTables", "Applies Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushOk->setText(QApplication::translate("frmTables", "&Ok", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushClose->setToolTip(QApplication::translate("frmTables", "Cancel Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushClose->setStatusTip(QApplication::translate("frmTables", "Cancel Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushClose->setWhatsThis(QApplication::translate("frmTables", "Cancels Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushClose->setText(QApplication::translate("frmTables", "&Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmTables: public Ui_frmTables {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTABLES_H
