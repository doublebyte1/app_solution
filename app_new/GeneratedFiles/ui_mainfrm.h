/********************************************************************************
** Form generated from reading UI file 'mainfrm.ui'
**
** Created: Wed 29. Jun 17:41:11 2011
**      by: Qt User Interface Compiler version 4.7.0
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
    QAction *actionClose;
    QAction *actionReports;
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionRegions;
    QAction *actionRebuild_Indexes;
    QAction *actionGeneralize_Regions;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QMenuBar *menubar;
    QMenu *menuSampling_Operation;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuMaintenance_Tasks;
    QMenu *menuTransform_Data;
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
        icon2.addFile(QString::fromUtf8(":/app_new/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/app_new/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/app_new/3floppy_unmount.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/app_new/qt-logo.gif"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_Qt->setIcon(icon5);
        actionAbout_this_project = new QAction(MainWindow);
        actionAbout_this_project->setObjectName(QString::fromUtf8("actionAbout_this_project"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/app_new/kontact.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_this_project->setIcon(icon6);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/app_new/fileclose.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon7);
        actionReports = new QAction(MainWindow);
        actionReports->setObjectName(QString::fromUtf8("actionReports"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/app_new/kpresenter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReports->setIcon(icon8);
        actionImport = new QAction(MainWindow);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/app_new/folder_inbox.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport->setIcon(icon9);
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/app_new/folder_outbox.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon10);
        actionRegions = new QAction(MainWindow);
        actionRegions->setObjectName(QString::fromUtf8("actionRegions"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/app_new/tree.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRegions->setIcon(icon11);
        actionRebuild_Indexes = new QAction(MainWindow);
        actionRebuild_Indexes->setObjectName(QString::fromUtf8("actionRebuild_Indexes"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/app_new/configure_toolbars.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRebuild_Indexes->setIcon(icon12);
        actionGeneralize_Regions = new QAction(MainWindow);
        actionGeneralize_Regions->setObjectName(QString::fromUtf8("actionGeneralize_Regions"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/app_new/launch.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGeneralize_Regions->setIcon(icon13);
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
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuMaintenance_Tasks = new QMenu(menuTools);
        menuMaintenance_Tasks->setObjectName(QString::fromUtf8("menuMaintenance_Tasks"));
        menuTransform_Data = new QMenu(menuTools);
        menuTransform_Data->setObjectName(QString::fromUtf8("menuTransform_Data"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSampling_Operation->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuSampling_Operation->addAction(actionNew);
        menuSampling_Operation->addAction(actionLoad);
        menuSampling_Operation->addAction(actionClose);
        menuSampling_Operation->addAction(actionSave);
        menuSampling_Operation->addSeparator();
        menuSampling_Operation->addAction(actionExit);
        menuHelp->addAction(actionAbout_this_project);
        menuView->addAction(actionReports);
        menuView->addAction(actionRegions);
        menuTools->addAction(menuMaintenance_Tasks->menuAction());
        menuTools->addAction(menuTransform_Data->menuAction());
        menuMaintenance_Tasks->addAction(actionImport);
        menuMaintenance_Tasks->addAction(actionExport);
        menuMaintenance_Tasks->addAction(actionRebuild_Indexes);
        menuTransform_Data->addAction(actionGeneralize_Regions);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(newTabs()));

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
        actionLoad->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionLoad->setStatusTip(QApplication::translate("MainWindow", "Open a file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionLoad->setWhatsThis(QApplication::translate("MainWindow", "Opens an existent file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionLoad->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
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
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionClose->setStatusTip(QApplication::translate("MainWindow", "Close file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionClose->setWhatsThis(QApplication::translate("MainWindow", "Close current file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionReports->setText(QApplication::translate("MainWindow", "Reports", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionReports->setStatusTip(QApplication::translate("MainWindow", "View reports", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionReports->setWhatsThis(QApplication::translate("MainWindow", "Shows the reports", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionReports->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionImport->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
        actionImport->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionExport->setText(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
        actionExport->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0, QApplication::UnicodeUTF8));
        actionRegions->setText(QApplication::translate("MainWindow", "Regions", 0, QApplication::UnicodeUTF8));
        actionRegions->setIconText(QApplication::translate("MainWindow", "View tree-model of regions", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRegions->setToolTip(QApplication::translate("MainWindow", "View tree-model of regions", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionRegions->setStatusTip(QApplication::translate("MainWindow", "View tree-model of regions", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionRegions->setWhatsThis(QApplication::translate("MainWindow", "View tree-model of regions", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionRegions->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        actionRebuild_Indexes->setText(QApplication::translate("MainWindow", "Rebuild Indexes", 0, QApplication::UnicodeUTF8));
        actionRebuild_Indexes->setIconText(QApplication::translate("MainWindow", "Compact the Database, by rebuilding the indexes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRebuild_Indexes->setToolTip(QApplication::translate("MainWindow", "Compact the Database, by rebuilding the indexes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionRebuild_Indexes->setStatusTip(QApplication::translate("MainWindow", "Compact the Database, by rebuilding the indexes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionRebuild_Indexes->setWhatsThis(QApplication::translate("MainWindow", "Compacts the Database, by rebuilding the indexes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionRebuild_Indexes->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionGeneralize_Regions->setText(QApplication::translate("MainWindow", "Generalize Regions", 0, QApplication::UnicodeUTF8));
        actionGeneralize_Regions->setIconText(QApplication::translate("MainWindow", "Convert regions on an adjacency list, to a nested set representation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionGeneralize_Regions->setToolTip(QApplication::translate("MainWindow", "Convert regions on an adjacency list, to a nested set representation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionGeneralize_Regions->setStatusTip(QApplication::translate("MainWindow", "Convert regions on an adjacency list, to a nested set representation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionGeneralize_Regions->setWhatsThis(QApplication::translate("MainWindow", "Converts regions on an adjacency list, to a nested set representation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionGeneralize_Regions->setShortcut(QApplication::translate("MainWindow", "Ctrl+G", 0, QApplication::UnicodeUTF8));
        menuSampling_Operation->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuMaintenance_Tasks->setTitle(QApplication::translate("MainWindow", "Maintenance Tasks", 0, QApplication::UnicodeUTF8));
        menuTransform_Data->setTitle(QApplication::translate("MainWindow", "Transform Data", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRM_H
