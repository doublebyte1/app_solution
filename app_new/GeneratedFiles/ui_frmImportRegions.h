/********************************************************************************
** Form generated from reading UI file 'frmImportRegions.ui'
**
** Created: Wed 5. Dec 16:55:29 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMIMPORTREGIONS_H
#define UI_FRMIMPORTREGIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmImportRegions
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbTables;
    QComboBox *cmbTables;
    QLabel *lbField;
    QComboBox *cmbFields;
    QPushButton *pushMore;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushApply;
    QPushButton *pushCancel;
    QPushButton *pushClose;
    QListWidget *listWidget;

    void setupUi(QWidget *frmImportRegions)
    {
        if (frmImportRegions->objectName().isEmpty())
            frmImportRegions->setObjectName(QString::fromUtf8("frmImportRegions"));
        frmImportRegions->resize(458, 326);
        gridLayout = new QGridLayout(frmImportRegions);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lbTables = new QLabel(frmImportRegions);
        lbTables->setObjectName(QString::fromUtf8("lbTables"));

        horizontalLayout_2->addWidget(lbTables);

        cmbTables = new QComboBox(frmImportRegions);
        cmbTables->setObjectName(QString::fromUtf8("cmbTables"));
        cmbTables->setEditable(true);

        horizontalLayout_2->addWidget(cmbTables);

        lbField = new QLabel(frmImportRegions);
        lbField->setObjectName(QString::fromUtf8("lbField"));

        horizontalLayout_2->addWidget(lbField);

        cmbFields = new QComboBox(frmImportRegions);
        cmbFields->setObjectName(QString::fromUtf8("cmbFields"));
        cmbFields->setEditable(true);

        horizontalLayout_2->addWidget(cmbFields);

        pushMore = new QPushButton(frmImportRegions);
        pushMore->setObjectName(QString::fromUtf8("pushMore"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushMore->sizePolicy().hasHeightForWidth());
        pushMore->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushMore->setIcon(icon);

        horizontalLayout_2->addWidget(pushMore);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushApply = new QPushButton(frmImportRegions);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));

        horizontalLayout->addWidget(pushApply);

        pushCancel = new QPushButton(frmImportRegions);
        pushCancel->setObjectName(QString::fromUtf8("pushCancel"));

        horizontalLayout->addWidget(pushCancel);

        pushClose = new QPushButton(frmImportRegions);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));

        horizontalLayout->addWidget(pushClose);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        listWidget = new QListWidget(frmImportRegions);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidget->setAlternatingRowColors(true);

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        lbTables->setBuddy(cmbTables);
        lbField->setBuddy(cmbFields);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(cmbTables, cmbFields);
        QWidget::setTabOrder(cmbFields, pushMore);
        QWidget::setTabOrder(pushMore, pushApply);
        QWidget::setTabOrder(pushApply, pushClose);

        retranslateUi(frmImportRegions);
        QObject::connect(pushClose, SIGNAL(clicked()), frmImportRegions, SLOT(Cancel()));
        QObject::connect(cmbTables, SIGNAL(currentIndexChanged(QString)), frmImportRegions, SLOT(refreshFields(QString)));
        QObject::connect(pushMore, SIGNAL(clicked()), frmImportRegions, SLOT(addItems2List()));
        QObject::connect(pushApply, SIGNAL(clicked()), frmImportRegions, SLOT(Apply()));
        QObject::connect(pushCancel, SIGNAL(clicked()), frmImportRegions, SLOT(Cancel()));
        QObject::connect(pushMore, SIGNAL(clicked()), frmImportRegions, SLOT(adjustButtons()));

        QMetaObject::connectSlotsByName(frmImportRegions);
    } // setupUi

    void retranslateUi(QWidget *frmImportRegions)
    {
        frmImportRegions->setWindowTitle(QApplication::translate("frmImportRegions", "Form", 0, QApplication::UnicodeUTF8));
        lbTables->setText(QApplication::translate("frmImportRegions", "Choose Node Table", 0, QApplication::UnicodeUTF8));
        lbField->setText(QApplication::translate("frmImportRegions", "Choose Parent Field", 0, QApplication::UnicodeUTF8));
        pushMore->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushApply->setToolTip(QApplication::translate("frmImportRegions", "Ok", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushApply->setStatusTip(QApplication::translate("frmImportRegions", "Ok", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushApply->setWhatsThis(QApplication::translate("frmImportRegions", "Ok", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushApply->setText(QApplication::translate("frmImportRegions", "&Apply", 0, QApplication::UnicodeUTF8));
        pushCancel->setText(QApplication::translate("frmImportRegions", "&Clear", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushClose->setToolTip(QApplication::translate("frmImportRegions", "Cancel", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushClose->setStatusTip(QApplication::translate("frmImportRegions", "Cancel", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushClose->setWhatsThis(QApplication::translate("frmImportRegions", "Cancel", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushClose->setText(QApplication::translate("frmImportRegions", "&Close", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        listWidget->setToolTip(QApplication::translate("frmImportRegions", "This widget allows us to define an adjacency list model, from a set of tables with reference fields. \n"
" We start from the bottom, by indicating the first-level table and the field that references the parent table, and then the parent table, and the field that references the parent of the parent, etc.\n"
" On the last level, we do *not* need to indicate a field, since this is a non-referenced table! \n"
" By pressing apply, there is a transformation from this into a nested set model, that is stored in the db inside a tree-like structure. \n"
" this model can be inspected in this application, by choosing View->Regions, from the main menu.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        listWidget->setStatusTip(QApplication::translate("frmImportRegions", "This widget allows us to define an adjacency list model, from a set of tables with reference fields;", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        listWidget->setWhatsThis(QApplication::translate("frmImportRegions", "This widget allows us to define an adjacency list model, from a set of tables with reference fields. \n"
" We start from the bottom, by indicating the first-level table and the field that references the parent table, and then the parent table, and the field that references the parent of the parent, etc.\n"
" On the last level, we do *not* need to indicate a field, since this is a non-referenced table! \n"
" By pressing apply, there is a transformation from this into a nested set model, that is stored in the db inside a tree-like structure. \n"
" this model can be inspected in this application, by choosing View->Regions, from the main menu.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class frmImportRegions: public Ui_frmImportRegions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMIMPORTREGIONS_H
