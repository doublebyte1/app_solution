/********************************************************************************
** Form generated from reading UI file 'frmreports.ui'
**
** Created: Wed 5. Dec 16:55:30 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMREPORTS_H
#define UI_FRMREPORTS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmreports
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QListWidget *listWidget;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineOpen;
    QPushButton *pushOpen;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *lbPixmap;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *lbName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLabel *lbAuthor;
    QLabel *label_6;
    QTextBrowser *textDescription;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushClose;

    void setupUi(QWidget *frmreports)
    {
        if (frmreports->objectName().isEmpty())
            frmreports->setObjectName(QString::fromUtf8("frmreports"));
        frmreports->resize(775, 445);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        frmreports->setFont(font);
        gridLayout_2 = new QGridLayout(frmreports);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(frmreports);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        listWidget = new QListWidget(frmreports);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidget->setAlternatingRowColors(true);
        listWidget->setWordWrap(true);
        listWidget->setSortingEnabled(true);

        verticalLayout->addWidget(listWidget);

        label_3 = new QLabel(frmreports);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineOpen = new QLineEdit(frmreports);
        lineOpen->setObjectName(QString::fromUtf8("lineOpen"));

        horizontalLayout->addWidget(lineOpen);

        pushOpen = new QPushButton(frmreports);
        pushOpen->setObjectName(QString::fromUtf8("pushOpen"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushOpen->sizePolicy().hasHeightForWidth());
        pushOpen->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushOpen->setIcon(icon);

        horizontalLayout->addWidget(pushOpen);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 2, 1);

        frame = new QFrame(frmreports);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbPixmap = new QLabel(frame);
        lbPixmap->setObjectName(QString::fromUtf8("lbPixmap"));
        sizePolicy.setHeightForWidth(lbPixmap->sizePolicy().hasHeightForWidth());
        lbPixmap->setSizePolicy(sizePolicy);
        lbPixmap->setMaximumSize(QSize(51, 51));
        lbPixmap->setPixmap(QPixmap(QString::fromUtf8(":/app_new/kpresenter.png")));
        lbPixmap->setScaledContents(true);

        gridLayout->addWidget(lbPixmap, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        lbName = new QLabel(frame);
        lbName->setObjectName(QString::fromUtf8("lbName"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbName->sizePolicy().hasHeightForWidth());
        lbName->setSizePolicy(sizePolicy1);
        lbName->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(lbName);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        lbAuthor = new QLabel(frame);
        lbAuthor->setObjectName(QString::fromUtf8("lbAuthor"));
        lbAuthor->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(lbAuthor);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 2);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        textDescription = new QTextBrowser(frame);
        textDescription->setObjectName(QString::fromUtf8("textDescription"));

        gridLayout->addWidget(textDescription, 4, 0, 1, 2);


        gridLayout_2->addWidget(frame, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushClose = new QPushButton(frmreports);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));

        horizontalLayout_2->addWidget(pushClose);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        label_3->setBuddy(lineOpen);
        label_6->setBuddy(textDescription);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(listWidget, textDescription);
        QWidget::setTabOrder(textDescription, lineOpen);
        QWidget::setTabOrder(lineOpen, pushOpen);
        QWidget::setTabOrder(pushOpen, pushClose);

        retranslateUi(frmreports);
        QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), frmreports, SLOT(previewItem(QListWidgetItem*)));
        QObject::connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), frmreports, SLOT(loadItem(QListWidgetItem*)));
        QObject::connect(pushOpen, SIGNAL(clicked()), frmreports, SLOT(browseFiles()));

        QMetaObject::connectSlotsByName(frmreports);
    } // setupUi

    void retranslateUi(QWidget *frmreports)
    {
        frmreports->setWindowTitle(QApplication::translate("frmreports", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmreports", "Choose one report from the list:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("frmreports", "Browse to load a report:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushOpen->setToolTip(QApplication::translate("frmreports", "Open report", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushOpen->setStatusTip(QApplication::translate("frmreports", "Browse files to load a report from non-standard location", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushOpen->setWhatsThis(QApplication::translate("frmreports", "Browse files to load a report from non-standard location", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushOpen->setText(QString());
#ifndef QT_NO_TOOLTIP
        lbPixmap->setToolTip(QApplication::translate("frmreports", "Report Icon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lbPixmap->setStatusTip(QApplication::translate("frmreports", "Report Icon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        lbPixmap->setWhatsThis(QApplication::translate("frmreports", "Report Icon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        lbPixmap->setText(QString());
        label->setText(QApplication::translate("frmreports", "Name:", 0, QApplication::UnicodeUTF8));
        lbName->setText(QApplication::translate("frmreports", "-> TYPE SOMETHING HERE", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmreports", "Author:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lbAuthor->setToolTip(QApplication::translate("frmreports", "Report Author", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lbAuthor->setStatusTip(QApplication::translate("frmreports", "Report Author", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        lbAuthor->setWhatsThis(QApplication::translate("frmreports", "Report Author", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        lbAuthor->setText(QApplication::translate("frmreports", "-> TYPE SOMETHING HERE", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("frmreports", "Description:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        textDescription->setToolTip(QApplication::translate("frmreports", "Report description", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        textDescription->setStatusTip(QApplication::translate("frmreports", "Report description", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        textDescription->setWhatsThis(QApplication::translate("frmreports", "Report description", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        pushClose->setToolTip(QApplication::translate("frmreports", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushClose->setStatusTip(QApplication::translate("frmreports", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushClose->setWhatsThis(QApplication::translate("frmreports", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushClose->setText(QApplication::translate("frmreports", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmreports: public Ui_frmreports {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMREPORTS_H
