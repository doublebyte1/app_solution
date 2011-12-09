/********************************************************************************
** Form generated from reading UI file 'frmframedetails.ui'
**
** Created: Fri 9. Dec 10:57:50 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMFRAMEDETAILS_H
#define UI_FRMFRAMEDETAILS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmframedetails
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineName;
    QLabel *label_4;
    QComboBox *cmbType;
    QLabel *label_5;
    QLabel *lbPersistence;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QPlainTextEdit *textDesc;
    QLabel *label_6;
    QPlainTextEdit *textComments;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkClone;
    QLabel *label_3;
    QComboBox *cmbCloned;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushExpand;
    QPushButton *pushCollapse;
    QPushButton *pushLegend;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushBack;
    QPushButton *pushVerify;
    QPushButton *pushApply;
    QPushButton *pushUndo;

    void setupUi(QWidget *frmframedetails)
    {
        if (frmframedetails->objectName().isEmpty())
            frmframedetails->setObjectName(QString::fromUtf8("frmframedetails"));
        frmframedetails->resize(726, 591);
        gridLayout = new QGridLayout(frmframedetails);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(frmframedetails);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(16777215, 200));
        groupBox->setFlat(true);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineName = new QLineEdit(groupBox);
        lineName->setObjectName(QString::fromUtf8("lineName"));

        horizontalLayout_2->addWidget(lineName);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        cmbType = new QComboBox(groupBox);
        cmbType->setObjectName(QString::fromUtf8("cmbType"));

        horizontalLayout_2->addWidget(cmbType);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lbPersistence = new QLabel(groupBox);
        lbPersistence->setObjectName(QString::fromUtf8("lbPersistence"));
        lbPersistence->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255)"));
        lbPersistence->setFrameShape(QFrame::StyledPanel);
        lbPersistence->setFrameShadow(QFrame::Plain);

        horizontalLayout_2->addWidget(lbPersistence);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_2);

        textDesc = new QPlainTextEdit(groupBox);
        textDesc->setObjectName(QString::fromUtf8("textDesc"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textDesc->sizePolicy().hasHeightForWidth());
        textDesc->setSizePolicy(sizePolicy1);
        textDesc->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(textDesc);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_6);

        textComments = new QPlainTextEdit(groupBox);
        textComments->setObjectName(QString::fromUtf8("textComments"));
        sizePolicy1.setHeightForWidth(textComments->sizePolicy().hasHeightForWidth());
        textComments->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(textComments);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkClone = new QCheckBox(groupBox);
        checkClone->setObjectName(QString::fromUtf8("checkClone"));
        checkClone->setEnabled(false);

        horizontalLayout_4->addWidget(checkClone);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(false);

        horizontalLayout_4->addWidget(label_3);

        cmbCloned = new QComboBox(groupBox);
        cmbCloned->setObjectName(QString::fromUtf8("cmbCloned"));
        cmbCloned->setEnabled(false);

        horizontalLayout_4->addWidget(cmbCloned);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        frame = new QFrame(frmframedetails);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));

        gridLayout->addWidget(frame, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushExpand = new QPushButton(frmframedetails);
        pushExpand->setObjectName(QString::fromUtf8("pushExpand"));

        horizontalLayout->addWidget(pushExpand);

        pushCollapse = new QPushButton(frmframedetails);
        pushCollapse->setObjectName(QString::fromUtf8("pushCollapse"));

        horizontalLayout->addWidget(pushCollapse);

        pushLegend = new QPushButton(frmframedetails);
        pushLegend->setObjectName(QString::fromUtf8("pushLegend"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/kcoloredit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushLegend->setIcon(icon);

        horizontalLayout->addWidget(pushLegend);

        horizontalSpacer = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushBack = new QPushButton(frmframedetails);
        pushBack->setObjectName(QString::fromUtf8("pushBack"));

        horizontalLayout->addWidget(pushBack);

        pushVerify = new QPushButton(frmframedetails);
        pushVerify->setObjectName(QString::fromUtf8("pushVerify"));

        horizontalLayout->addWidget(pushVerify);

        pushApply = new QPushButton(frmframedetails);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));

        horizontalLayout->addWidget(pushApply);

        pushUndo = new QPushButton(frmframedetails);
        pushUndo->setObjectName(QString::fromUtf8("pushUndo"));

        horizontalLayout->addWidget(pushUndo);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineName);
        label_4->setBuddy(cmbType);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineName, cmbType);
        QWidget::setTabOrder(cmbType, textDesc);
        QWidget::setTabOrder(textDesc, checkClone);
        QWidget::setTabOrder(checkClone, pushExpand);
        QWidget::setTabOrder(pushExpand, pushCollapse);
        QWidget::setTabOrder(pushCollapse, pushBack);

        retranslateUi(frmframedetails);
        QObject::connect(pushApply, SIGNAL(clicked()), frmframedetails, SLOT(apply()));
        QObject::connect(pushBack, SIGNAL(clicked()), frmframedetails, SLOT(back()));
        QObject::connect(pushUndo, SIGNAL(clicked()), frmframedetails, SLOT(undo()));
        QObject::connect(pushVerify, SIGNAL(clicked()), frmframedetails, SLOT(verify()));
        QObject::connect(cmbCloned, SIGNAL(currentIndexChanged(QString)), frmframedetails, SLOT(isClonedFromPreviousFrame(QString)));
        QObject::connect(pushLegend, SIGNAL(clicked()), frmframedetails, SLOT(showLegend()));

        QMetaObject::connectSlotsByName(frmframedetails);
    } // setupUi

    void retranslateUi(QWidget *frmframedetails)
    {
        frmframedetails->setWindowTitle(QApplication::translate("frmframedetails", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("frmframedetails", "Name", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmframedetails", "Type", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("frmframedetails", "Persistence", 0, QApplication::UnicodeUTF8));
        lbPersistence->setText(QApplication::translate("frmframedetails", "TYPE SOMETHING HERE <--", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmframedetails", "Description", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("frmframedetails", "Comments", 0, QApplication::UnicodeUTF8));
        checkClone->setText(QApplication::translate("frmframedetails", "Clone from Previous Frame", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("frmframedetails", "Cloned Frame", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        frame->setToolTip(QApplication::translate("frmframedetails", "Press edit key F2 to edit items", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushExpand->setText(QApplication::translate("frmframedetails", "Expand All", 0, QApplication::UnicodeUTF8));
        pushCollapse->setText(QApplication::translate("frmframedetails", "Collapse All", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushLegend->setToolTip(QApplication::translate("frmframedetails", "View legend", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushLegend->setStatusTip(QApplication::translate("frmframedetails", "View legend", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushLegend->setWhatsThis(QApplication::translate("frmframedetails", "View legend", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushLegend->setText(QApplication::translate("frmframedetails", "Legend", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushBack->setToolTip(QApplication::translate("frmframedetails", "Go back", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushBack->setStatusTip(QApplication::translate("frmframedetails", "Go back to previous form", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushBack->setWhatsThis(QApplication::translate("frmframedetails", "Goes back to previous form", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushBack->setText(QApplication::translate("frmframedetails", "Back", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushVerify->setToolTip(QApplication::translate("frmframedetails", "Verify changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushVerify->setStatusTip(QApplication::translate("frmframedetails", "Verify", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushVerify->setWhatsThis(QApplication::translate("frmframedetails", "Verifies changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushVerify->setText(QApplication::translate("frmframedetails", "Verify", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushApply->setToolTip(QApplication::translate("frmframedetails", "Apply changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushApply->setStatusTip(QApplication::translate("frmframedetails", "Apply", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushApply->setWhatsThis(QApplication::translate("frmframedetails", "Applies changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushApply->setText(QApplication::translate("frmframedetails", "Apply", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushUndo->setToolTip(QApplication::translate("frmframedetails", "Undo applying changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushUndo->setStatusTip(QApplication::translate("frmframedetails", "Undo", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushUndo->setWhatsThis(QApplication::translate("frmframedetails", "Undo changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushUndo->setText(QApplication::translate("frmframedetails", "Undo Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmframedetails: public Ui_frmframedetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFRAMEDETAILS_H
