/********************************************************************************
** Form generated from reading UI file 'frmlegend.ui'
**
** Created: Wed 25. May 13:04:56 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMLEGEND_H
#define UI_FRMLEGEND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FrmLegend
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushClose;

    void setupUi(QDialog *FrmLegend)
    {
        if (FrmLegend->objectName().isEmpty())
            FrmLegend->setObjectName(QString::fromUtf8("FrmLegend"));
        FrmLegend->resize(650, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/kcoloredit.png"), QSize(), QIcon::Normal, QIcon::Off);
        FrmLegend->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(FrmLegend);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget = new QTreeWidget(FrmLegend);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setFrameShape(QFrame::StyledPanel);
        treeWidget->setFrameShadow(QFrame::Sunken);
        treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidget->setProperty("showDropIndicator", QVariant(true));
        treeWidget->setAlternatingRowColors(true);
        treeWidget->setSelectionMode(QAbstractItemView::NoSelection);
        treeWidget->setIconSize(QSize(32, 37));
        treeWidget->setAutoExpandDelay(1);
        treeWidget->setRootIsDecorated(false);
        treeWidget->setWordWrap(true);
        treeWidget->setExpandsOnDoubleClick(false);
        treeWidget->setColumnCount(2);
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushClose = new QPushButton(FrmLegend);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));

        horizontalLayout->addWidget(pushClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FrmLegend);
        QObject::connect(pushClose, SIGNAL(clicked()), FrmLegend, SLOT(close()));

        QMetaObject::connectSlotsByName(FrmLegend);
    } // setupUi

    void retranslateUi(QDialog *FrmLegend)
    {
        FrmLegend->setWindowTitle(QApplication::translate("FrmLegend", "Legend", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushClose->setToolTip(QApplication::translate("FrmLegend", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushClose->setStatusTip(QApplication::translate("FrmLegend", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushClose->setWhatsThis(QApplication::translate("FrmLegend", "Close this form", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushClose->setText(QApplication::translate("FrmLegend", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmLegend: public Ui_FrmLegend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMLEGEND_H
