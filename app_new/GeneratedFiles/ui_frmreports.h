/********************************************************************************
** Form generated from reading UI file 'frmreports.ui'
**
** Created: Wed 22. Jun 18:16:36 2011
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
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmreports
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QListView *listView;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineOpen;
    QPushButton *pushOpen;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *lbAuthor;
    QLabel *lbPixmap;
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
        horizontalLayout_3 = new QHBoxLayout(frmreports);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(frmreports);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        listView = new QListView(frmreports);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setAlternatingRowColors(true);

        verticalLayout->addWidget(listView);

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


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(frmreports);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        verticalLayout_2->addWidget(label);

        frame = new QFrame(frmreports);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 1, 1, 1);

        lbAuthor = new QLabel(frame);
        lbAuthor->setObjectName(QString::fromUtf8("lbAuthor"));

        gridLayout->addWidget(lbAuthor, 1, 0, 1, 1);

        lbPixmap = new QLabel(frame);
        lbPixmap->setObjectName(QString::fromUtf8("lbPixmap"));
        sizePolicy.setHeightForWidth(lbPixmap->sizePolicy().hasHeightForWidth());
        lbPixmap->setSizePolicy(sizePolicy);
        lbPixmap->setPixmap(QPixmap(QString::fromUtf8(":/app_new/kpresenter.png")));
        lbPixmap->setScaledContents(true);

        gridLayout->addWidget(lbPixmap, 1, 1, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        textDescription = new QTextBrowser(frame);
        textDescription->setObjectName(QString::fromUtf8("textDescription"));

        gridLayout->addWidget(textDescription, 3, 0, 1, 2);


        verticalLayout_2->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushClose = new QPushButton(frmreports);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));

        horizontalLayout_2->addWidget(pushClose);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(listView);
        label_3->setBuddy(lineOpen);
        label_6->setBuddy(textDescription);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(listView, textDescription);
        QWidget::setTabOrder(textDescription, lineOpen);
        QWidget::setTabOrder(lineOpen, pushOpen);
        QWidget::setTabOrder(pushOpen, pushClose);

        retranslateUi(frmreports);

        QMetaObject::connectSlotsByName(frmreports);
    } // setupUi

    void retranslateUi(QWidget *frmreports)
    {
        frmreports->setWindowTitle(QApplication::translate("frmreports", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmreports", "Choose one report from the list:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        listView->setToolTip(QApplication::translate("frmreports", "Available reports", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        listView->setStatusTip(QApplication::translate("frmreports", "Available reports on the report directory", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        listView->setWhatsThis(QApplication::translate("frmreports", "Lists the available reports on the report directory", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
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
        label->setText(QApplication::translate("frmreports", "Report Properties", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmreports", "Author:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("frmreports", "Icon:", 0, QApplication::UnicodeUTF8));
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
