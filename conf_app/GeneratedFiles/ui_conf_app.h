/********************************************************************************
** Form generated from reading UI file 'conf_app.ui'
**
** Created: Wed 7. Dec 13:12:20 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONF_APP_H
#define UI_CONF_APP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_conf_appClass
{
public:
    QAction *actionExit;
    QAction *actionShow_startup_message;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QToolBox *toolBox;
    QWidget *page_3;
    QGridLayout *gridLayout;
    QLabel *lbHost;
    QLineEdit *lineHost;
    QLabel *lbDataSource;
    QLineEdit *lineDataSource;
    QLabel *lbUsername;
    QLineEdit *lineUsername;
    QLabel *lbPassword;
    QLineEdit *linePassword;
    QLabel *lbAlias;
    QLineEdit *lineAlias;
    QLabel *lbDriver;
    QComboBox *cmbDriver;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushConnect;
    QPushButton *pushDisconnect;
    QWidget *page_4;
    QGridLayout *gridLayout_2;
    QGroupBox *groupSettings;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cmbCountry;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *cmbCity;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushApply;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *m_statusBar;

    void setupUi(QMainWindow *conf_appClass)
    {
        if (conf_appClass->objectName().isEmpty())
            conf_appClass->setObjectName(QString::fromUtf8("conf_appClass"));
        conf_appClass->resize(514, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/conf_app/conf_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        conf_appClass->setWindowIcon(icon);
        actionExit = new QAction(conf_appClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/conf_app/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionShow_startup_message = new QAction(conf_appClass);
        actionShow_startup_message->setObjectName(QString::fromUtf8("actionShow_startup_message"));
        actionShow_startup_message->setCheckable(true);
        actionShow_startup_message->setChecked(false);
        centralWidget = new QWidget(conf_appClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        toolBox = new QToolBox(centralWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 496, 278));
        gridLayout = new QGridLayout(page_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbHost = new QLabel(page_3);
        lbHost->setObjectName(QString::fromUtf8("lbHost"));
        lbHost->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbHost, 0, 0, 1, 1);

        lineHost = new QLineEdit(page_3);
        lineHost->setObjectName(QString::fromUtf8("lineHost"));

        gridLayout->addWidget(lineHost, 0, 1, 1, 1);

        lbDataSource = new QLabel(page_3);
        lbDataSource->setObjectName(QString::fromUtf8("lbDataSource"));
        lbDataSource->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbDataSource, 1, 0, 1, 1);

        lineDataSource = new QLineEdit(page_3);
        lineDataSource->setObjectName(QString::fromUtf8("lineDataSource"));

        gridLayout->addWidget(lineDataSource, 1, 1, 1, 1);

        lbUsername = new QLabel(page_3);
        lbUsername->setObjectName(QString::fromUtf8("lbUsername"));
        lbUsername->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbUsername, 2, 0, 1, 1);

        lineUsername = new QLineEdit(page_3);
        lineUsername->setObjectName(QString::fromUtf8("lineUsername"));

        gridLayout->addWidget(lineUsername, 2, 1, 1, 1);

        lbPassword = new QLabel(page_3);
        lbPassword->setObjectName(QString::fromUtf8("lbPassword"));

        gridLayout->addWidget(lbPassword, 3, 0, 1, 1);

        linePassword = new QLineEdit(page_3);
        linePassword->setObjectName(QString::fromUtf8("linePassword"));
        linePassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(linePassword, 3, 1, 1, 1);

        lbAlias = new QLabel(page_3);
        lbAlias->setObjectName(QString::fromUtf8("lbAlias"));
        lbAlias->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbAlias, 4, 0, 1, 1);

        lineAlias = new QLineEdit(page_3);
        lineAlias->setObjectName(QString::fromUtf8("lineAlias"));

        gridLayout->addWidget(lineAlias, 4, 1, 1, 1);

        lbDriver = new QLabel(page_3);
        lbDriver->setObjectName(QString::fromUtf8("lbDriver"));

        gridLayout->addWidget(lbDriver, 5, 0, 1, 1);

        cmbDriver = new QComboBox(page_3);
        cmbDriver->setObjectName(QString::fromUtf8("cmbDriver"));

        gridLayout->addWidget(cmbDriver, 5, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushConnect = new QPushButton(page_3);
        pushConnect->setObjectName(QString::fromUtf8("pushConnect"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/conf_app/encrypted.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushConnect->setIcon(icon2);

        horizontalLayout->addWidget(pushConnect);

        pushDisconnect = new QPushButton(page_3);
        pushDisconnect->setObjectName(QString::fromUtf8("pushDisconnect"));
        pushDisconnect->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/conf_app/decrypted.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushDisconnect->setIcon(icon3);

        horizontalLayout->addWidget(pushDisconnect);


        gridLayout->addLayout(horizontalLayout, 6, 1, 1, 1);

        toolBox->addItem(page_3, QString::fromUtf8("Connection Properties"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 496, 278));
        gridLayout_2 = new QGridLayout(page_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupSettings = new QGroupBox(page_4);
        groupSettings->setObjectName(QString::fromUtf8("groupSettings"));
        verticalLayout = new QVBoxLayout(groupSettings);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        cmbCountry = new QComboBox(groupSettings);
        cmbCountry->setObjectName(QString::fromUtf8("cmbCountry"));

        horizontalLayout_2->addWidget(cmbCountry);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupSettings);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        cmbCity = new QComboBox(groupSettings);
        cmbCity->setObjectName(QString::fromUtf8("cmbCity"));

        horizontalLayout_3->addWidget(cmbCity);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushApply = new QPushButton(groupSettings);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));

        horizontalLayout_4->addWidget(pushApply);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout_2->addWidget(groupSettings, 0, 0, 1, 1);

        toolBox->addItem(page_4, QString::fromUtf8("Global Settings"));

        gridLayout_3->addWidget(toolBox, 0, 0, 1, 1);

        conf_appClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(conf_appClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 514, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuOptions = new QMenu(menuTools);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        conf_appClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(conf_appClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        conf_appClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        m_statusBar = new QStatusBar(conf_appClass);
        m_statusBar->setObjectName(QString::fromUtf8("m_statusBar"));
        m_statusBar->setMinimumSize(QSize(0, 18));
        conf_appClass->setStatusBar(m_statusBar);
#ifndef QT_NO_SHORTCUT
        lbHost->setBuddy(lineHost);
        lbDataSource->setBuddy(lineDataSource);
        lbUsername->setBuddy(lineUsername);
        lbPassword->setBuddy(linePassword);
        lbAlias->setBuddy(lineAlias);
        lbDriver->setBuddy(cmbDriver);
        label_2->setBuddy(cmbCountry);
        label->setBuddy(cmbCity);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineHost, lineDataSource);
        QWidget::setTabOrder(lineDataSource, lineUsername);
        QWidget::setTabOrder(lineUsername, linePassword);
        QWidget::setTabOrder(linePassword, lineAlias);
        QWidget::setTabOrder(lineAlias, cmbDriver);
        QWidget::setTabOrder(cmbDriver, pushConnect);
        QWidget::setTabOrder(pushConnect, pushDisconnect);
        QWidget::setTabOrder(pushDisconnect, cmbCountry);
        QWidget::setTabOrder(cmbCountry, cmbCity);
        QWidget::setTabOrder(cmbCity, pushApply);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuFile->addAction(actionExit);
        menuTools->addAction(menuOptions->menuAction());
        menuOptions->addAction(actionShow_startup_message);

        retranslateUi(conf_appClass);
        QObject::connect(actionExit, SIGNAL(triggered()), conf_appClass, SLOT(close()));
        QObject::connect(pushConnect, SIGNAL(clicked()), conf_appClass, SLOT(connectDB()));
        QObject::connect(pushDisconnect, SIGNAL(clicked()), conf_appClass, SLOT(disconnectDB()));
        QObject::connect(cmbCountry, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(filterModel(QString)));
        QObject::connect(pushApply, SIGNAL(clicked()), conf_appClass, SLOT(apply()));
        QObject::connect(cmbCountry, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(enableApply()));
        QObject::connect(cmbCity, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(enableApply()));

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(conf_appClass);
    } // setupUi

    void retranslateUi(QMainWindow *conf_appClass)
    {
        conf_appClass->setWindowTitle(QApplication::translate("conf_appClass", "Medfisis Configurator", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("conf_appClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("conf_appClass", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionShow_startup_message->setText(QApplication::translate("conf_appClass", "Show startup message", 0, QApplication::UnicodeUTF8));
        lbHost->setText(QApplication::translate("conf_appClass", "Host", 0, QApplication::UnicodeUTF8));
        lbDataSource->setText(QApplication::translate("conf_appClass", "Data Source", 0, QApplication::UnicodeUTF8));
        lbUsername->setText(QApplication::translate("conf_appClass", "Username", 0, QApplication::UnicodeUTF8));
        lbPassword->setText(QApplication::translate("conf_appClass", "Password", 0, QApplication::UnicodeUTF8));
        lbAlias->setText(QApplication::translate("conf_appClass", "Alias", 0, QApplication::UnicodeUTF8));
        lbDriver->setText(QApplication::translate("conf_appClass", "Driver", 0, QApplication::UnicodeUTF8));
        pushConnect->setText(QString());
        pushDisconnect->setText(QString());
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("conf_appClass", "Connection Properties", 0, QApplication::UnicodeUTF8));
        groupSettings->setTitle(QString());
        label_2->setText(QApplication::translate("conf_appClass", "Country", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("conf_appClass", "City", 0, QApplication::UnicodeUTF8));
        pushApply->setText(QApplication::translate("conf_appClass", "Apply", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("conf_appClass", "Global Settings", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("conf_appClass", "File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("conf_appClass", "Tools", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("conf_appClass", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class conf_appClass: public Ui_conf_appClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONF_APP_H
