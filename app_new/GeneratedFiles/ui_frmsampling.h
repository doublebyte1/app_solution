/********************************************************************************
** Form generated from reading UI file 'frmsampling.ui'
**
** Created: Thu 29. Sep 12:05:25 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSAMPLING_H
#define UI_FRMSAMPLING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmSampling
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cmbSource;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushBack;
    QPushButton *pushApply;

    void setupUi(QWidget *FrmSampling)
    {
        if (FrmSampling->objectName().isEmpty())
            FrmSampling->setObjectName(QString::fromUtf8("FrmSampling"));
        FrmSampling->resize(630, 434);
        verticalLayout = new QVBoxLayout(FrmSampling);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(FrmSampling);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        cmbSource = new QComboBox(FrmSampling);
        cmbSource->setObjectName(QString::fromUtf8("cmbSource"));

        horizontalLayout_2->addWidget(cmbSource);


        verticalLayout->addLayout(horizontalLayout_2);

        tableView = new QTableView(FrmSampling);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::NoSelection);
        tableView->horizontalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(308, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushBack = new QPushButton(FrmSampling);
        pushBack->setObjectName(QString::fromUtf8("pushBack"));

        horizontalLayout->addWidget(pushBack);

        pushApply = new QPushButton(FrmSampling);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));

        horizontalLayout->addWidget(pushApply);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FrmSampling);

        QMetaObject::connectSlotsByName(FrmSampling);
    } // setupUi

    void retranslateUi(QWidget *FrmSampling)
    {
        FrmSampling->setWindowTitle(QApplication::translate("FrmSampling", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmSampling", "Source", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushBack->setToolTip(QApplication::translate("FrmSampling", "Go back", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushBack->setStatusTip(QApplication::translate("FrmSampling", "Go back to previous form", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushBack->setWhatsThis(QApplication::translate("FrmSampling", "Goes back to previous form", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushBack->setText(QApplication::translate("FrmSampling", "Back", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushApply->setToolTip(QApplication::translate("FrmSampling", "Apply changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushApply->setStatusTip(QApplication::translate("FrmSampling", "Apply", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushApply->setWhatsThis(QApplication::translate("FrmSampling", "Applies changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushApply->setText(QApplication::translate("FrmSampling", "Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmSampling: public Ui_FrmSampling {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSAMPLING_H
