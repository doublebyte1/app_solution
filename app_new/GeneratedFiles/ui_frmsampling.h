/********************************************************************************
** Form generated from reading UI file 'frmsampling.ui'
**
** Created: Fri 9. Dec 10:57:54 2011
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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmSampling
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lbSource;
    QGroupBox *groupTechnique;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineName;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QPlainTextEdit *textDescription;
    QLabel *label_8;
    QPlainTextEdit *textComments;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QComboBox *cmbStrategy;
    QLabel *label_5;
    QSpinBox *spinSample;
    QLabel *label_6;
    QSpinBox *spinPopulation;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QPushButton *pushInsert;
    QPushButton *pushRemove;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushBack;
    QPushButton *pushApply;

    void setupUi(QWidget *FrmSampling)
    {
        if (FrmSampling->objectName().isEmpty())
            FrmSampling->setObjectName(QString::fromUtf8("FrmSampling"));
        FrmSampling->resize(774, 377);
        verticalLayout_3 = new QVBoxLayout(FrmSampling);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(FrmSampling);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lbSource = new QLabel(FrmSampling);
        lbSource->setObjectName(QString::fromUtf8("lbSource"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbSource->sizePolicy().hasHeightForWidth());
        lbSource->setSizePolicy(sizePolicy);
        lbSource->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(220, 220, 220, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));\n"
"font: 75 10pt \"Fixedsys\";"));
        lbSource->setFrameShape(QFrame::StyledPanel);
        lbSource->setFrameShadow(QFrame::Raised);
        lbSource->setScaledContents(true);

        horizontalLayout_2->addWidget(lbSource);


        verticalLayout_3->addLayout(horizontalLayout_2);

        groupTechnique = new QGroupBox(FrmSampling);
        groupTechnique->setObjectName(QString::fromUtf8("groupTechnique"));
        verticalLayout_2 = new QVBoxLayout(groupTechnique);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(groupTechnique);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineName = new QLineEdit(groupTechnique);
        lineName->setObjectName(QString::fromUtf8("lineName"));

        horizontalLayout_3->addWidget(lineName);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(groupTechnique);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        textDescription = new QPlainTextEdit(groupTechnique);
        textDescription->setObjectName(QString::fromUtf8("textDescription"));

        horizontalLayout_4->addWidget(textDescription);

        label_8 = new QLabel(groupTechnique);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_4->addWidget(label_8);

        textComments = new QPlainTextEdit(groupTechnique);
        textComments->setObjectName(QString::fromUtf8("textComments"));

        horizontalLayout_4->addWidget(textComments);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(groupTechnique);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        cmbStrategy = new QComboBox(groupTechnique);
        cmbStrategy->setObjectName(QString::fromUtf8("cmbStrategy"));

        horizontalLayout_5->addWidget(cmbStrategy);

        label_5 = new QLabel(groupTechnique);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        spinSample = new QSpinBox(groupTechnique);
        spinSample->setObjectName(QString::fromUtf8("spinSample"));
        spinSample->setMaximum(100000);

        horizontalLayout_5->addWidget(spinSample);

        label_6 = new QLabel(groupTechnique);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        spinPopulation = new QSpinBox(groupTechnique);
        spinPopulation->setObjectName(QString::fromUtf8("spinPopulation"));
        spinPopulation->setMaximum(100000);

        horizontalLayout_5->addWidget(spinPopulation);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_7 = new QLabel(groupTechnique);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label_7);

        pushInsert = new QPushButton(groupTechnique);
        pushInsert->setObjectName(QString::fromUtf8("pushInsert"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushInsert->setIcon(icon);

        verticalLayout->addWidget(pushInsert);

        pushRemove = new QPushButton(groupTechnique);
        pushRemove->setObjectName(QString::fromUtf8("pushRemove"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushRemove->setIcon(icon1);

        verticalLayout->addWidget(pushRemove);


        horizontalLayout_6->addLayout(verticalLayout);

        tableView = new QTableView(groupTechnique);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_6->addWidget(tableView);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_3->addWidget(groupTechnique);

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


        verticalLayout_3->addLayout(horizontalLayout);

#ifndef QT_NO_SHORTCUT
        label_3->setBuddy(textDescription);
        label_4->setBuddy(cmbStrategy);
        label_5->setBuddy(spinSample);
        label_6->setBuddy(spinPopulation);
        label_7->setBuddy(tableView);
#endif // QT_NO_SHORTCUT

        retranslateUi(FrmSampling);
        QObject::connect(pushApply, SIGNAL(clicked()), FrmSampling, SLOT(apply()));
        QObject::connect(pushBack, SIGNAL(clicked()), FrmSampling, SLOT(back()));
        QObject::connect(pushInsert, SIGNAL(clicked()), FrmSampling, SLOT(insertRow()));
        QObject::connect(pushRemove, SIGNAL(clicked()), FrmSampling, SLOT(removeRow()));
        QObject::connect(tableView, SIGNAL(entered(QModelIndex)), tableView, SLOT(resizeColumnsToContents()));

        QMetaObject::connectSlotsByName(FrmSampling);
    } // setupUi

    void retranslateUi(QWidget *FrmSampling)
    {
        FrmSampling->setWindowTitle(QApplication::translate("FrmSampling", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmSampling", "Source", 0, QApplication::UnicodeUTF8));
        lbSource->setText(QApplication::translate("FrmSampling", "[SOURCE]", 0, QApplication::UnicodeUTF8));
        groupTechnique->setTitle(QString());
        label_2->setText(QApplication::translate("FrmSampling", "Name", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FrmSampling", "Description", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FrmSampling", "Comments", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FrmSampling", "Global Strategy", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FrmSampling", "Sample Size", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FrmSampling", "Population Size", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FrmSampling", "Levels", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushInsert->setToolTip(QApplication::translate("FrmSampling", "Insert row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushInsert->setStatusTip(QApplication::translate("FrmSampling", "Insert row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushInsert->setWhatsThis(QApplication::translate("FrmSampling", "Inserts row into table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushInsert->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushRemove->setToolTip(QApplication::translate("FrmSampling", "Remove row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushRemove->setStatusTip(QApplication::translate("FrmSampling", "Remove row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushRemove->setWhatsThis(QApplication::translate("FrmSampling", "Removes row into table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushRemove->setText(QString());
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
