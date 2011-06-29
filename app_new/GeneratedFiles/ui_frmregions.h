/********************************************************************************
** Form generated from reading UI file 'frmregions.ui'
**
** Created: Wed 29. Jun 13:42:40 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMREGIONS_H
#define UI_FRMREGIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmRegions
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushRefresh;
    QPushButton *pushApply;
    QPushButton *pushClose;

    void setupUi(QWidget *frmRegions)
    {
        if (frmRegions->objectName().isEmpty())
            frmRegions->setObjectName(QString::fromUtf8("frmRegions"));
        frmRegions->resize(559, 431);
        gridLayout = new QGridLayout(frmRegions);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeWidget = new QTreeWidget(frmRegions);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setAlternatingRowColors(true);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(268, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushRefresh = new QPushButton(frmRegions);
        pushRefresh->setObjectName(QString::fromUtf8("pushRefresh"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushRefresh->setIcon(icon);

        horizontalLayout->addWidget(pushRefresh);

        pushApply = new QPushButton(frmRegions);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushApply->sizePolicy().hasHeightForWidth());
        pushApply->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushApply);

        pushClose = new QPushButton(frmRegions);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));
        sizePolicy.setHeightForWidth(pushClose->sizePolicy().hasHeightForWidth());
        pushClose->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushClose);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        QWidget::setTabOrder(treeWidget, pushRefresh);
        QWidget::setTabOrder(pushRefresh, pushApply);
        QWidget::setTabOrder(pushApply, pushClose);

        retranslateUi(frmRegions);
        QObject::connect(pushApply, SIGNAL(clicked()), frmRegions, SLOT(Apply()));
        QObject::connect(pushRefresh, SIGNAL(clicked()), frmRegions, SLOT(reload()));
        QObject::connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), frmRegions, SLOT(treeEdited()));

        QMetaObject::connectSlotsByName(frmRegions);
    } // setupUi

    void retranslateUi(QWidget *frmRegions)
    {
        frmRegions->setWindowTitle(QApplication::translate("frmRegions", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        treeWidget->setToolTip(QApplication::translate("frmRegions", "This widget allows to view and edit the Regions model; this is a nested set representation of the regions, and therefore it supports an infinite number of levels; to edit any item property, just double-click over it;", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        treeWidget->setStatusTip(QApplication::translate("frmRegions", "This widget allows to view and edit the Regions model;", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        treeWidget->setWhatsThis(QApplication::translate("frmRegions", "This widget allows to view and edit the Regions model; this is a nested set representation of the regions, and therefore it supports an infinite number of levels; to edit any item property, just double-click over it;", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        pushRefresh->setToolTip(QApplication::translate("frmRegions", "Reload Tree", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushRefresh->setStatusTip(QApplication::translate("frmRegions", "Reloads Tree from the Database", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        pushRefresh->setText(QApplication::translate("frmRegions", "&Reload", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushApply->setToolTip(QApplication::translate("frmRegions", "Accept Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushApply->setStatusTip(QApplication::translate("frmRegions", "Accept Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushApply->setWhatsThis(QApplication::translate("frmRegions", "Accepts Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushApply->setText(QApplication::translate("frmRegions", "&Apply", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushClose->setToolTip(QApplication::translate("frmRegions", "Cancel Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushClose->setStatusTip(QApplication::translate("frmRegions", "Cancel Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushClose->setWhatsThis(QApplication::translate("frmRegions", "Cancels Changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushClose->setText(QApplication::translate("frmRegions", "&Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmRegions: public Ui_frmRegions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMREGIONS_H
