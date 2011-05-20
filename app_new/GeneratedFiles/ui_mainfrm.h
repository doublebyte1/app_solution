/********************************************************************************
** Form generated from reading UI file 'mainfrm.ui'
**
** Created: Fri 20. May 16:02:59 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRM_H
#define UI_MAINFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionLoad;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionSave;
    QAction *actionAbout_Qt;
    QAction *actionAbout_this_project;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QMenuBar *menubar;
    QMenu *menuSampling_Operation;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app_new/medfisis.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/app_new/empty.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/app_new/editcopy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/app_new/3floppy_unmount.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/app_new/qt-logo.gif"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_Qt->setIcon(icon4);
        actionAbout_this_project = new QAction(MainWindow);
        actionAbout_this_project->setObjectName(QString::fromUtf8("actionAbout_this_project"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/app_new/kontact.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_this_project->setIcon(icon5);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 18));
        menuSampling_Operation = new QMenu(menubar);
        menuSampling_Operation->setObjectName(QString::fromUtf8("menuSampling_Operation"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSampling_Operation->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuSampling_Operation->addAction(actionNew);
        menuSampling_Operation->addAction(actionLoad);
        menuSampling_Operation->addAction(actionSave);
        menuSampling_Operation->addSeparator();
        menuSampling_Operation->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAbout_this_project);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout_Qt);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(initTabs()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionNew->setStatusTip(QApplication::translate("MainWindow", "New sampling operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionNew->setWhatsThis(QApplication::translate("MainWindow", "Starts a new sampling operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionLoad->setStatusTip(QApplication::translate("MainWindow", "Load sampling operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionLoad->setWhatsThis(QApplication::translate("MainWindow", "Loads an existent sampling operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionLoad->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionExit->setStatusTip(QApplication::translate("MainWindow", "Exit app", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionExit->setWhatsThis(QApplication::translate("MainWindow", "Exits application", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About this application", 0, QApplication::UnicodeUTF8));
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionSave->setStatusTip(QApplication::translate("MainWindow", "Save sampling operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionSave->setWhatsThis(QApplication::translate("MainWindow", "Saves this sampling operation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAbout_this_project->setText(QApplication::translate("MainWindow", "About this project", 0, QApplication::UnicodeUTF8));
        actionAbout_this_project->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        menuSampling_Operation->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRM_H
