/********************************************************************************
** Form generated from reading UI file 'frmminorstrata.ui'
**
** Created: Mon 4. Apr 15:57:47 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMINORSTRATA_H
#define UI_FRMMINORSTRATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmminorstrata
{
public:
    QGridLayout *gridLayout_3;
    QLabel *lbHeader;
    QRadioButton *radioPreexistent;
    QTableView *tableView;
    QRadioButton *radioNew;
    QLineEdit *lineNew;
    QPushButton *pushDetails;
    QGroupBox *groupDetails;
    QGridLayout *gridLayout;
    QGroupBox *groupActivity;
    QGridLayout *gridLayout_2;
    QRadioButton *radioActive;
    QRadioButton *radioInactive;
    QComboBox *comboBox;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_3;
    QComboBox *cmbGLS;
    QLabel *label;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEdit_2;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBackNext;
    QFormLayout *formLayout;
    QPushButton *pushPrevious;
    QPushButton *pushNext;

    void setupUi(QWidget *frmminorstrata)
    {
        if (frmminorstrata->objectName().isEmpty())
            frmminorstrata->setObjectName(QString::fromUtf8("frmminorstrata"));
        frmminorstrata->resize(711, 489);
        gridLayout_3 = new QGridLayout(frmminorstrata);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lbHeader = new QLabel(frmminorstrata);
        lbHeader->setObjectName(QString::fromUtf8("lbHeader"));
        lbHeader->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));

        gridLayout_3->addWidget(lbHeader, 0, 0, 1, 4);

        radioPreexistent = new QRadioButton(frmminorstrata);
        radioPreexistent->setObjectName(QString::fromUtf8("radioPreexistent"));

        gridLayout_3->addWidget(radioPreexistent, 1, 0, 1, 1);

        tableView = new QTableView(frmminorstrata);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_3->addWidget(tableView, 1, 1, 1, 2);

        radioNew = new QRadioButton(frmminorstrata);
        radioNew->setObjectName(QString::fromUtf8("radioNew"));

        gridLayout_3->addWidget(radioNew, 2, 0, 1, 1);

        lineNew = new QLineEdit(frmminorstrata);
        lineNew->setObjectName(QString::fromUtf8("lineNew"));

        gridLayout_3->addWidget(lineNew, 2, 1, 1, 2);

        pushDetails = new QPushButton(frmminorstrata);
        pushDetails->setObjectName(QString::fromUtf8("pushDetails"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushDetails->sizePolicy().hasHeightForWidth());
        pushDetails->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/kview.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushDetails->setIcon(icon);
        pushDetails->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(pushDetails, 3, 3, 1, 1);

        groupDetails = new QGroupBox(frmminorstrata);
        groupDetails->setObjectName(QString::fromUtf8("groupDetails"));
        gridLayout = new QGridLayout(groupDetails);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupActivity = new QGroupBox(groupDetails);
        groupActivity->setObjectName(QString::fromUtf8("groupActivity"));
        gridLayout_2 = new QGridLayout(groupActivity);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioActive = new QRadioButton(groupActivity);
        radioActive->setObjectName(QString::fromUtf8("radioActive"));

        gridLayout_2->addWidget(radioActive, 0, 0, 1, 2);

        radioInactive = new QRadioButton(groupActivity);
        radioInactive->setObjectName(QString::fromUtf8("radioInactive"));

        gridLayout_2->addWidget(radioInactive, 1, 0, 1, 1);

        comboBox = new QComboBox(groupActivity);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 1, 1, 1, 1);


        gridLayout->addWidget(groupActivity, 0, 4, 3, 4);

        plainTextEdit = new QPlainTextEdit(groupDetails);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 5, 2, 1, 2);

        label_3 = new QLabel(groupDetails);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 1, 1, 1);

        cmbGLS = new QComboBox(groupDetails);
        cmbGLS->setObjectName(QString::fromUtf8("cmbGLS"));

        gridLayout->addWidget(cmbGLS, 1, 2, 1, 1);

        label = new QLabel(groupDetails);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 1, 1, 1);

        label_4 = new QLabel(groupDetails);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 1, 1, 1);

        dateTimeEdit = new QDateTimeEdit(groupDetails);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setCalendarPopup(true);

        gridLayout->addWidget(dateTimeEdit, 3, 2, 1, 1);

        label_2 = new QLabel(groupDetails);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 4, 1, 1);

        dateTimeEdit_2 = new QDateTimeEdit(groupDetails);
        dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));
        dateTimeEdit_2->setCalendarPopup(true);

        gridLayout->addWidget(dateTimeEdit_2, 3, 6, 1, 1);

        buttonBox = new QDialogButtonBox(groupDetails);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 5, 6, 1, 1);


        gridLayout_3->addWidget(groupDetails, 4, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(379, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 5, 1, 1, 1);

        groupBackNext = new QGroupBox(frmminorstrata);
        groupBackNext->setObjectName(QString::fromUtf8("groupBackNext"));
        sizePolicy.setHeightForWidth(groupBackNext->sizePolicy().hasHeightForWidth());
        groupBackNext->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(groupBackNext);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        pushPrevious = new QPushButton(groupBackNext);
        pushPrevious->setObjectName(QString::fromUtf8("pushPrevious"));
        pushPrevious->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushPrevious->setIcon(icon1);

        formLayout->setWidget(0, QFormLayout::LabelRole, pushPrevious);

        pushNext = new QPushButton(groupBackNext);
        pushNext->setObjectName(QString::fromUtf8("pushNext"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNext->setIcon(icon2);

        formLayout->setWidget(0, QFormLayout::FieldRole, pushNext);


        gridLayout_3->addWidget(groupBackNext, 5, 2, 1, 2);

#ifndef QT_NO_SHORTCUT
        label_3->setBuddy(cmbGLS);
        label->setBuddy(dateTimeEdit);
        label_2->setBuddy(dateTimeEdit_2);
#endif // QT_NO_SHORTCUT

        retranslateUi(frmminorstrata);

        QMetaObject::connectSlotsByName(frmminorstrata);
    } // setupUi

    void retranslateUi(QWidget *frmminorstrata)
    {
        frmminorstrata->setWindowTitle(QApplication::translate("frmminorstrata", "Form", 0, QApplication::UnicodeUTF8));
        lbHeader->setText(QApplication::translate("frmminorstrata", "WRITE SOMETHING HERE LATER <---", 0, QApplication::UnicodeUTF8));
        radioPreexistent->setText(QApplication::translate("frmminorstrata", "Choose Pre-existent", 0, QApplication::UnicodeUTF8));
        radioNew->setText(QApplication::translate("frmminorstrata", "Create New", 0, QApplication::UnicodeUTF8));
        pushDetails->setText(QString());
        groupDetails->setTitle(QApplication::translate("frmminorstrata", "Details", 0, QApplication::UnicodeUTF8));
        groupActivity->setTitle(QApplication::translate("frmminorstrata", "Activity Status", 0, QApplication::UnicodeUTF8));
        radioActive->setText(QApplication::translate("frmminorstrata", "Active", 0, QApplication::UnicodeUTF8));
        radioInactive->setText(QApplication::translate("frmminorstrata", "Inactive", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("frmminorstrata", "Group of Landing Sites", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmminorstrata", "Start Date", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmminorstrata", "Comments", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmminorstrata", "End Date", 0, QApplication::UnicodeUTF8));
        groupBackNext->setTitle(QString());
        pushPrevious->setText(QApplication::translate("frmminorstrata", "Previous", 0, QApplication::UnicodeUTF8));
        pushNext->setText(QApplication::translate("frmminorstrata", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmminorstrata: public Ui_frmminorstrata {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMINORSTRATA_H
