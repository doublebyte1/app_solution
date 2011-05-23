/********************************************************************************
** Form generated from reading UI file 'frmchangereasons.ui'
**
** Created: Mon 23. May 12:37:44 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCHANGEREASONS_H
#define UI_FRMCHANGEREASONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FrmChangeReasons
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *cmbChanges;
    QTextEdit *textChanges;
    QLabel *lbChangeCoordinates;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FrmChangeReasons)
    {
        if (FrmChangeReasons->objectName().isEmpty())
            FrmChangeReasons->setObjectName(QString::fromUtf8("FrmChangeReasons"));
        FrmChangeReasons->setWindowModality(Qt::ApplicationModal);
        FrmChangeReasons->resize(395, 258);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/medfisis.ico"), QSize(), QIcon::Normal, QIcon::Off);
        FrmChangeReasons->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(FrmChangeReasons);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(FrmChangeReasons);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        cmbChanges = new QComboBox(FrmChangeReasons);
        cmbChanges->setObjectName(QString::fromUtf8("cmbChanges"));

        verticalLayout->addWidget(cmbChanges);

        textChanges = new QTextEdit(FrmChangeReasons);
        textChanges->setObjectName(QString::fromUtf8("textChanges"));

        verticalLayout->addWidget(textChanges);

        lbChangeCoordinates = new QLabel(FrmChangeReasons);
        lbChangeCoordinates->setObjectName(QString::fromUtf8("lbChangeCoordinates"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        lbChangeCoordinates->setFont(font);
        lbChangeCoordinates->setTextFormat(Qt::LogText);
        lbChangeCoordinates->setWordWrap(true);

        verticalLayout->addWidget(lbChangeCoordinates);

        buttonBox = new QDialogButtonBox(FrmChangeReasons);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::No|QDialogButtonBox::Yes);

        verticalLayout->addWidget(buttonBox);


        horizontalLayout->addLayout(verticalLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(cmbChanges);
#endif // QT_NO_SHORTCUT

        retranslateUi(FrmChangeReasons);
        QObject::connect(buttonBox, SIGNAL(accepted()), FrmChangeReasons, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FrmChangeReasons, SLOT(reject()));

        QMetaObject::connectSlotsByName(FrmChangeReasons);
    } // setupUi

    void retranslateUi(QDialog *FrmChangeReasons)
    {
        FrmChangeReasons->setWindowTitle(QApplication::translate("FrmChangeReasons", "Change Reasons", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmChangeReasons", "Input reasons for this change:", 0, QApplication::UnicodeUTF8));
        lbChangeCoordinates->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FrmChangeReasons: public Ui_FrmChangeReasons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCHANGEREASONS_H
