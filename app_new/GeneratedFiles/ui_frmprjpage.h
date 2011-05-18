/********************************************************************************
** Form generated from reading UI file 'frmprjpage.ui'
**
** Created: Wed 18. May 10:30:38 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMPRJPAGE_H
#define UI_FRMPRJPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_frmprjpage
{
public:
    QVBoxLayout *verticalLayout;
    QWebView *webView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushClose;

    void setupUi(QWidget *frmprjpage)
    {
        if (frmprjpage->objectName().isEmpty())
            frmprjpage->setObjectName(QString::fromUtf8("frmprjpage"));
        frmprjpage->resize(614, 428);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/medfisis.ico"), QSize(), QIcon::Normal, QIcon::Off);
        frmprjpage->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(frmprjpage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        webView = new QWebView(frmprjpage);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl("http://www.faomedfisis.org/"));
        webView->setZoomFactor(1);

        verticalLayout->addWidget(webView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushClose = new QPushButton(frmprjpage);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));

        horizontalLayout->addWidget(pushClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(frmprjpage);
        QObject::connect(pushClose, SIGNAL(clicked()), frmprjpage, SLOT(close()));

        QMetaObject::connectSlotsByName(frmprjpage);
    } // setupUi

    void retranslateUi(QWidget *frmprjpage)
    {
        frmprjpage->setWindowTitle(QApplication::translate("frmprjpage", "About this project", 0, QApplication::UnicodeUTF8));
        pushClose->setText(QApplication::translate("frmprjpage", "close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmprjpage: public Ui_frmprjpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMPRJPAGE_H
