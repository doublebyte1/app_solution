/********************************************************************************
** Form generated from reading UI file 'frmvessel.ui'
**
** Created: Thu 16. Jun 11:01:25 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMVESSEL_H
#define UI_FRMVESSEL_H

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
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmVessel
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lbHeader;
    QLabel *lbSource;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *pushNew;
    QGroupBox *groupDetails;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *cmbVessel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QComboBox *cmbOrigin;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QComboBox *cmbStatus;
    QGroupBox *groupFT;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QSpinBox *spinET;
    QSpinBox *spinCT;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QPlainTextEdit *textComments;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *frmVessel)
    {
        if (frmVessel->objectName().isEmpty())
            frmVessel->setObjectName(QString::fromUtf8("frmVessel"));
        frmVessel->resize(703, 588);
        verticalLayout_5 = new QVBoxLayout(frmVessel);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        lbHeader = new QLabel(frmVessel);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbHeader->sizePolicy().hasHeightForWidth());
        lbHeader->setSizePolicy(sizePolicy);
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        horizontalLayout_7->addWidget(lbHeader);

        lbSource = new QLabel(frmVessel);
        lbSource->setObjectName(QString::fromUtf8("lbSource"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbSource->sizePolicy().hasHeightForWidth());
        lbSource->setSizePolicy(sizePolicy1);
        lbSource->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(220, 220, 220, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));\n"
"font: 75 10pt \"Fixedsys\";"));
        lbSource->setFrameShape(QFrame::StyledPanel);
        lbSource->setFrameShadow(QFrame::Raised);
        lbSource->setScaledContents(true);

        horizontalLayout_7->addWidget(lbSource);


        verticalLayout_5->addLayout(horizontalLayout_7);

        label_5 = new QLabel(frmVessel);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(frmVessel);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushNew = new QPushButton(frmVessel);
        pushNew->setObjectName(QString::fromUtf8("pushNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNew->setIcon(icon);

        verticalLayout->addWidget(pushNew);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_5->addLayout(horizontalLayout);

        groupDetails = new QGroupBox(frmVessel);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        horizontalLayout_6 = new QHBoxLayout(groupDetails);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(groupDetails);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        cmbVessel = new QComboBox(groupDetails);
        cmbVessel->setObjectName(QString::fromUtf8("cmbVessel"));

        horizontalLayout_5->addWidget(cmbVessel);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(groupDetails);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        cmbOrigin = new QComboBox(groupDetails);
        cmbOrigin->setObjectName(QString::fromUtf8("cmbOrigin"));

        horizontalLayout_4->addWidget(cmbOrigin);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(groupDetails);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        cmbStatus = new QComboBox(groupDetails);
        cmbStatus->setObjectName(QString::fromUtf8("cmbStatus"));

        horizontalLayout_3->addWidget(cmbStatus);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(verticalLayout_2);

        groupFT = new QGroupBox(groupDetails);
        groupFT->setObjectName(QString::fromUtf8("groupFT"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupFT->sizePolicy().hasHeightForWidth());
        groupFT->setSizePolicy(sizePolicy2);
        groupFT->setFlat(true);
        gridLayout = new QGridLayout(groupFT);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(groupFT);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(groupFT);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        label_2 = new QLabel(groupFT);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinET = new QSpinBox(groupFT);
        spinET->setObjectName(QString::fromUtf8("spinET"));

        gridLayout->addWidget(spinET, 1, 1, 1, 1);

        spinCT = new QSpinBox(groupFT);
        spinCT->setObjectName(QString::fromUtf8("spinCT"));
        spinCT->setEnabled(false);

        gridLayout->addWidget(spinCT, 1, 2, 1, 1);


        verticalLayout_4->addWidget(groupFT);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_8 = new QLabel(groupDetails);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(label_8);

        textComments = new QPlainTextEdit(groupDetails);
        textComments->setObjectName(QString::fromUtf8("textComments"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(textComments->sizePolicy().hasHeightForWidth());
        textComments->setSizePolicy(sizePolicy4);

        verticalLayout_3->addWidget(textComments);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        verticalLayout_3->addWidget(buttonBox);


        horizontalLayout_6->addLayout(verticalLayout_3);


        verticalLayout_5->addWidget(groupDetails);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        groupBox = new QGroupBox(frmVessel);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushPrevious = new QPushButton(groupBox);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon1);

        horizontalLayout_2->addWidget(pushPrevious);

        pushNext = new QPushButton(groupBox);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon2);

        horizontalLayout_2->addWidget(pushNext);


        horizontalLayout_8->addWidget(groupBox);


        verticalLayout_5->addLayout(horizontalLayout_8);

#ifndef QT_NO_SHORTCUT
        label_5->setBuddy(tableView);
        label->setBuddy(cmbVessel);
        label_6->setBuddy(cmbOrigin);
        label_7->setBuddy(cmbStatus);
        label_3->setBuddy(spinET);
        label_4->setBuddy(spinCT);
        label_2->setBuddy(spinET);
        label_8->setBuddy(textComments);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tableView, pushNew);
        QWidget::setTabOrder(pushNew, cmbVessel);
        QWidget::setTabOrder(cmbVessel, cmbOrigin);
        QWidget::setTabOrder(cmbOrigin, cmbStatus);
        QWidget::setTabOrder(cmbStatus, textComments);
        QWidget::setTabOrder(textComments, spinET);
        QWidget::setTabOrder(spinET, spinCT);
        QWidget::setTabOrder(spinCT, buttonBox);
        QWidget::setTabOrder(buttonBox, pushPrevious);
        QWidget::setTabOrder(pushPrevious, pushNext);

        retranslateUi(frmVessel);
        QObject::connect(pushNew, SIGNAL(clicked()), frmVessel, SLOT(createRecord()));
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), frmVessel, SLOT(onButtonClick(QAbstractButton*)));
        QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), frmVessel, SLOT(previewRow(QModelIndex)));

        QMetaObject::connectSlotsByName(frmVessel);
    } // setupUi

    void retranslateUi(QWidget *frmVessel)
    {
        frmVessel->setWindowTitle(QApplication::translate("frmVessel", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("frmVessel", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        lbSource->setText(QApplication::translate("frmVessel", "[SOURCE]", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("frmVessel", "Select sampled vessel:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushNew->setToolTip(QApplication::translate("frmVessel", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNew->setStatusTip(QApplication::translate("frmVessel", "Create new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNew->setWhatsThis(QApplication::translate("frmVessel", "Creates new record", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNew->setText(QString());
        groupDetails->setTitle(QApplication::translate("frmVessel", "Details", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmVessel", "Vessel:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("frmVessel", "Sample Origin:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("frmVessel", "Status:", 0, QApplication::UnicodeUTF8));
        groupFT->setTitle(QString());
        label_3->setText(QApplication::translate("frmVessel", "Estimated", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmVessel", "Calculated", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmVessel", "Number of fishing trips:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("frmVessel", "Comments:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        pushPrevious->setText(QApplication::translate("frmVessel", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("frmVessel", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmVessel: public Ui_frmVessel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMVESSEL_H
