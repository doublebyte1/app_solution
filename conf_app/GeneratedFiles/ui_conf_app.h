/********************************************************************************
** Form generated from reading UI file 'conf_app.ui'
**
** Created: Sun 19. Aug 13:56:19 2012
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
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
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
    QAction *actionCreate_backup;
    QAction *actionRestore_backup;
    QAction *actionShow_SQL_message;
    QAction *actionDump_patch;
    QAction *actionApply_patch;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_7;
    QToolBox *toolBox;
    QWidget *page_3;
    QGridLayout *gridLayout;
    QLabel *lbHost;
    QLineEdit *lineHost;
    QLabel *lbDataSource;
    QLineEdit *lineDatabase;
    QLabel *lbUsername;
    QLineEdit *lineUsername;
    QLabel *lbPassword;
    QLineEdit *linePassword;
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
    QWidget *page;
    QGridLayout *gridLayout_4;
    QGroupBox *groupTables;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QComboBox *cmbTables;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushInsert;
    QPushButton *pushRemove;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushApply_2;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupUsers;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_10;
    QTableView *tableUsers;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushNewUser;
    QPushButton *pushEditUser;
    QPushButton *pushRemoveUser;
    QGroupBox *groupUsersDetail;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lineUser;
    QComboBox *comboRole;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *lineUserPassword;
    QLineEdit *lineUserPassword_2;
    QLabel *label_8;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_3;
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *textUserDesc;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuOptions;
    QMenu *menuBackups;
    QMenu *menuPatches;
    QToolBar *toolbar;
    QStatusBar *m_statusBar;

    void setupUi(QMainWindow *conf_appClass)
    {
        if (conf_appClass->objectName().isEmpty())
            conf_appClass->setObjectName(QString::fromUtf8("conf_appClass"));
        conf_appClass->resize(555, 397);
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
        actionCreate_backup = new QAction(conf_appClass);
        actionCreate_backup->setObjectName(QString::fromUtf8("actionCreate_backup"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/conf_app/folder_outbox.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_backup->setIcon(icon2);
        actionRestore_backup = new QAction(conf_appClass);
        actionRestore_backup->setObjectName(QString::fromUtf8("actionRestore_backup"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/conf_app/folder_inbox.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRestore_backup->setIcon(icon3);
        actionShow_SQL_message = new QAction(conf_appClass);
        actionShow_SQL_message->setObjectName(QString::fromUtf8("actionShow_SQL_message"));
        actionShow_SQL_message->setCheckable(true);
        actionShow_SQL_message->setChecked(true);
        actionDump_patch = new QAction(conf_appClass);
        actionDump_patch->setObjectName(QString::fromUtf8("actionDump_patch"));
        actionApply_patch = new QAction(conf_appClass);
        actionApply_patch->setObjectName(QString::fromUtf8("actionApply_patch"));
        centralWidget = new QWidget(conf_appClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_7 = new QVBoxLayout(centralWidget);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        toolBox = new QToolBox(centralWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 537, 221));
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

        lineDatabase = new QLineEdit(page_3);
        lineDatabase->setObjectName(QString::fromUtf8("lineDatabase"));

        gridLayout->addWidget(lineDatabase, 1, 1, 1, 1);

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

        lbDriver = new QLabel(page_3);
        lbDriver->setObjectName(QString::fromUtf8("lbDriver"));

        gridLayout->addWidget(lbDriver, 4, 0, 1, 1);

        cmbDriver = new QComboBox(page_3);
        cmbDriver->setObjectName(QString::fromUtf8("cmbDriver"));

        gridLayout->addWidget(cmbDriver, 4, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushConnect = new QPushButton(page_3);
        pushConnect->setObjectName(QString::fromUtf8("pushConnect"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/conf_app/encrypted.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushConnect->setIcon(icon4);

        horizontalLayout->addWidget(pushConnect);

        pushDisconnect = new QPushButton(page_3);
        pushDisconnect->setObjectName(QString::fromUtf8("pushDisconnect"));
        pushDisconnect->setEnabled(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/conf_app/decrypted.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushDisconnect->setIcon(icon5);

        horizontalLayout->addWidget(pushDisconnect);


        gridLayout->addLayout(horizontalLayout, 5, 1, 1, 1);

        toolBox->addItem(page_3, QString::fromUtf8("Connection Properties"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 161, 121));
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
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 190, 162));
        gridLayout_4 = new QGridLayout(page);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupTables = new QGroupBox(page);
        groupTables->setObjectName(QString::fromUtf8("groupTables"));
        verticalLayout_3 = new QVBoxLayout(groupTables);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupTables);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        cmbTables = new QComboBox(groupTables);
        cmbTables->setObjectName(QString::fromUtf8("cmbTables"));
        cmbTables->setEditable(true);

        horizontalLayout_5->addWidget(cmbTables);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushInsert = new QPushButton(groupTables);
        pushInsert->setObjectName(QString::fromUtf8("pushInsert"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/conf_app/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushInsert->setIcon(icon6);

        verticalLayout_2->addWidget(pushInsert);

        pushRemove = new QPushButton(groupTables);
        pushRemove->setObjectName(QString::fromUtf8("pushRemove"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/conf_app/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushRemove->setIcon(icon7);

        verticalLayout_2->addWidget(pushRemove);


        horizontalLayout_6->addLayout(verticalLayout_2);

        tableView = new QTableView(groupTables);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_6->addWidget(tableView);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        pushApply_2 = new QPushButton(groupTables);
        pushApply_2->setObjectName(QString::fromUtf8("pushApply_2"));

        horizontalLayout_7->addWidget(pushApply_2);


        verticalLayout_3->addLayout(horizontalLayout_7);


        gridLayout_4->addWidget(groupTables, 0, 0, 1, 1);

        toolBox->addItem(page, QString::fromUtf8("Edit Tables"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 371, 308));
        verticalLayout_6 = new QVBoxLayout(page_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupUsers = new QGroupBox(page_2);
        groupUsers->setObjectName(QString::fromUtf8("groupUsers"));
        verticalLayout_9 = new QVBoxLayout(groupUsers);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        tableUsers = new QTableView(groupUsers);
        tableUsers->setObjectName(QString::fromUtf8("tableUsers"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableUsers->sizePolicy().hasHeightForWidth());
        tableUsers->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(tableUsers);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        pushNewUser = new QPushButton(groupUsers);
        pushNewUser->setObjectName(QString::fromUtf8("pushNewUser"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/conf_app/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushNewUser->setIcon(icon8);

        verticalLayout_4->addWidget(pushNewUser);

        pushEditUser = new QPushButton(groupUsers);
        pushEditUser->setObjectName(QString::fromUtf8("pushEditUser"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushEditUser->sizePolicy().hasHeightForWidth());
        pushEditUser->setSizePolicy(sizePolicy1);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/conf_app/pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushEditUser->setIcon(icon9);
        pushEditUser->setCheckable(true);

        verticalLayout_4->addWidget(pushEditUser);

        pushRemoveUser = new QPushButton(groupUsers);
        pushRemoveUser->setObjectName(QString::fromUtf8("pushRemoveUser"));
        sizePolicy1.setHeightForWidth(pushRemoveUser->sizePolicy().hasHeightForWidth());
        pushRemoveUser->setSizePolicy(sizePolicy1);
        pushRemoveUser->setIcon(icon7);

        verticalLayout_4->addWidget(pushRemoveUser);


        horizontalLayout_10->addLayout(verticalLayout_4);


        verticalLayout_9->addLayout(horizontalLayout_10);

        groupUsersDetail = new QGroupBox(groupUsers);
        groupUsersDetail->setObjectName(QString::fromUtf8("groupUsersDetail"));
        gridLayout_6 = new QGridLayout(groupUsersDetail);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_4 = new QLabel(groupUsersDetail);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(groupUsersDetail);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_5->addWidget(label_5, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        lineUser = new QLineEdit(groupUsersDetail);
        lineUser->setObjectName(QString::fromUtf8("lineUser"));

        verticalLayout_8->addWidget(lineUser);

        comboRole = new QComboBox(groupUsersDetail);
        comboRole->setObjectName(QString::fromUtf8("comboRole"));

        verticalLayout_8->addWidget(comboRole);


        gridLayout_6->addLayout(verticalLayout_8, 0, 2, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_6 = new QLabel(groupUsersDetail);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lineUserPassword = new QLineEdit(groupUsersDetail);
        lineUserPassword->setObjectName(QString::fromUtf8("lineUserPassword"));
        lineUserPassword->setEchoMode(QLineEdit::Password);

        verticalLayout_5->addWidget(lineUserPassword);

        lineUserPassword_2 = new QLineEdit(groupUsersDetail);
        lineUserPassword_2->setObjectName(QString::fromUtf8("lineUserPassword_2"));
        lineUserPassword_2->setEchoMode(QLineEdit::Password);

        verticalLayout_5->addWidget(lineUserPassword_2);


        gridLayout_3->addLayout(verticalLayout_5, 0, 1, 2, 1);

        label_8 = new QLabel(groupUsersDetail);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_3, 0, 3, 1, 2);

        label_7 = new QLabel(groupUsersDetail);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_6->addWidget(label_7, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(197, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 2, 2, 1, 2);

        buttonBox = new QDialogButtonBox(groupUsersDetail);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        gridLayout_6->addWidget(buttonBox, 2, 4, 1, 1);

        textUserDesc = new QPlainTextEdit(groupUsersDetail);
        textUserDesc->setObjectName(QString::fromUtf8("textUserDesc"));

        gridLayout_6->addWidget(textUserDesc, 1, 1, 1, 4);


        verticalLayout_9->addWidget(groupUsersDetail);


        verticalLayout_6->addWidget(groupUsers);

        toolBox->addItem(page_2, QString::fromUtf8("User Management"));

        verticalLayout_7->addWidget(toolBox);

        conf_appClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(conf_appClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 555, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuOptions = new QMenu(menuTools);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuBackups = new QMenu(menuTools);
        menuBackups->setObjectName(QString::fromUtf8("menuBackups"));
        menuPatches = new QMenu(menuTools);
        menuPatches->setObjectName(QString::fromUtf8("menuPatches"));
        conf_appClass->setMenuBar(menuBar);
        toolbar = new QToolBar(conf_appClass);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        conf_appClass->addToolBar(Qt::TopToolBarArea, toolbar);
        m_statusBar = new QStatusBar(conf_appClass);
        m_statusBar->setObjectName(QString::fromUtf8("m_statusBar"));
        m_statusBar->setMinimumSize(QSize(0, 18));
        conf_appClass->setStatusBar(m_statusBar);
#ifndef QT_NO_SHORTCUT
        lbHost->setBuddy(lineHost);
        lbDataSource->setBuddy(lineDatabase);
        lbUsername->setBuddy(lineUsername);
        lbPassword->setBuddy(linePassword);
        lbDriver->setBuddy(cmbDriver);
        label_2->setBuddy(cmbCountry);
        label->setBuddy(cmbCity);
        label_3->setBuddy(cmbTables);
        label_4->setBuddy(lineUser);
        label_5->setBuddy(comboRole);
        label_6->setBuddy(lineUserPassword);
        label_8->setBuddy(lineUserPassword);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineHost, lineDatabase);
        QWidget::setTabOrder(lineDatabase, lineUsername);
        QWidget::setTabOrder(lineUsername, linePassword);
        QWidget::setTabOrder(linePassword, cmbDriver);
        QWidget::setTabOrder(cmbDriver, pushConnect);
        QWidget::setTabOrder(pushConnect, pushDisconnect);
        QWidget::setTabOrder(pushDisconnect, cmbCountry);
        QWidget::setTabOrder(cmbCountry, cmbCity);
        QWidget::setTabOrder(cmbCity, pushApply);
        QWidget::setTabOrder(pushApply, cmbTables);
        QWidget::setTabOrder(cmbTables, tableView);
        QWidget::setTabOrder(tableView, pushInsert);
        QWidget::setTabOrder(pushInsert, pushRemove);
        QWidget::setTabOrder(pushRemove, pushApply_2);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuFile->addAction(actionExit);
        menuTools->addAction(menuOptions->menuAction());
        menuTools->addAction(menuBackups->menuAction());
        menuTools->addAction(menuPatches->menuAction());
        menuOptions->addAction(actionShow_startup_message);
        menuOptions->addAction(actionShow_SQL_message);
        menuBackups->addAction(actionCreate_backup);
        menuBackups->addAction(actionRestore_backup);
        menuPatches->addAction(actionDump_patch);
        menuPatches->addAction(actionApply_patch);

        retranslateUi(conf_appClass);
        QObject::connect(actionExit, SIGNAL(triggered()), conf_appClass, SLOT(close()));
        QObject::connect(actionShow_SQL_message, SIGNAL(triggered(bool)), conf_appClass, SLOT(showSqlMessages(bool)));
        QObject::connect(pushConnect, SIGNAL(clicked()), conf_appClass, SLOT(connectDB()));
        QObject::connect(pushDisconnect, SIGNAL(clicked()), conf_appClass, SLOT(disconnectDB()));
        QObject::connect(cmbCountry, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(filterModel(QString)));
        QObject::connect(pushApply, SIGNAL(clicked()), conf_appClass, SLOT(apply()));
        QObject::connect(cmbCountry, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(enableApply()));
        QObject::connect(cmbCity, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(enableApply()));
        QObject::connect(cmbTables, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(showTable(QString)));
        QObject::connect(pushInsert, SIGNAL(clicked()), conf_appClass, SLOT(insertRow()));
        QObject::connect(pushRemove, SIGNAL(clicked()), conf_appClass, SLOT(removeRow()));
        QObject::connect(pushApply_2, SIGNAL(clicked()), conf_appClass, SLOT(applyChanges2Table()));
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), conf_appClass, SLOT(onButtonClick(QAbstractButton*)));
        QObject::connect(pushNewUser, SIGNAL(clicked()), conf_appClass, SLOT(createUserRecord()));
        QObject::connect(tableUsers, SIGNAL(clicked(QModelIndex)), conf_appClass, SLOT(previewUser(QModelIndex)));
        QObject::connect(pushEditUser, SIGNAL(clicked(bool)), conf_appClass, SLOT(editUser(bool)));
        QObject::connect(pushRemoveUser, SIGNAL(clicked()), conf_appClass, SLOT(removeUser()));

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(conf_appClass);
    } // setupUi

    void retranslateUi(QMainWindow *conf_appClass)
    {
        conf_appClass->setWindowTitle(QApplication::translate("conf_appClass", "Medfisis Configurator", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("conf_appClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("conf_appClass", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionShow_startup_message->setText(QApplication::translate("conf_appClass", "Show startup message", 0, QApplication::UnicodeUTF8));
        actionCreate_backup->setText(QApplication::translate("conf_appClass", "Create backup", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCreate_backup->setStatusTip(QApplication::translate("conf_appClass", "Create backup from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionCreate_backup->setWhatsThis(QApplication::translate("conf_appClass", "Creates backup from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionRestore_backup->setText(QApplication::translate("conf_appClass", "Restore backup", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionRestore_backup->setStatusTip(QApplication::translate("conf_appClass", "Restore backup from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionRestore_backup->setWhatsThis(QApplication::translate("conf_appClass", "Restores backup from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionShow_SQL_message->setText(QApplication::translate("conf_appClass", "Show SQL messages", 0, QApplication::UnicodeUTF8));
        actionDump_patch->setText(QApplication::translate("conf_appClass", "Dump patch", 0, QApplication::UnicodeUTF8));
        actionApply_patch->setText(QApplication::translate("conf_appClass", "Apply patch", 0, QApplication::UnicodeUTF8));
        lbHost->setText(QApplication::translate("conf_appClass", "Host", 0, QApplication::UnicodeUTF8));
        lbDataSource->setText(QApplication::translate("conf_appClass", "Database", 0, QApplication::UnicodeUTF8));
        lbUsername->setText(QApplication::translate("conf_appClass", "Username", 0, QApplication::UnicodeUTF8));
        lbPassword->setText(QApplication::translate("conf_appClass", "Password", 0, QApplication::UnicodeUTF8));
        lbDriver->setText(QApplication::translate("conf_appClass", "Driver", 0, QApplication::UnicodeUTF8));
        pushConnect->setText(QString());
        pushDisconnect->setText(QString());
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("conf_appClass", "Connection Properties", 0, QApplication::UnicodeUTF8));
        groupSettings->setTitle(QString());
        label_2->setText(QApplication::translate("conf_appClass", "Country", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("conf_appClass", "City", 0, QApplication::UnicodeUTF8));
        pushApply->setText(QApplication::translate("conf_appClass", "Apply", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("conf_appClass", "Global Settings", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupTables->setToolTip(QApplication::translate("conf_appClass", "This control allows the edition of any database table, including inserting and removing records.\n"
" Choose a table listed in the combo box, edit it by changing values and using the bottoms on the left to add/remove rows, and submit changes by pressing apply.\n"
" To enable edition again, you just have to select another table.\n"
" *Attention*: this function operates directly on the database, so there are no undos - be carefull with any changes you make! ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        groupTables->setStatusTip(QApplication::translate("conf_appClass", "This control allows the edition of any database table, including inserting and removing records. ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        groupTables->setWhatsThis(QApplication::translate("conf_appClass", "This control allows the edition of any database table, including inserting and removing records.\n"
" Choose a table listed in the combo box, edit it by changing values and using the bottoms on the left to add/remove rows, and submit changes by pressing apply.\n"
" To enable edition again, you just have to select another table.\n"
" *Attention*: this function operates directly on the database, so there are no undos - be carefull with any changes you make! ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupTables->setTitle(QString());
        label_3->setText(QApplication::translate("conf_appClass", "Choose Table:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmbTables->setToolTip(QApplication::translate("conf_appClass", "Database tables", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cmbTables->setStatusTip(QApplication::translate("conf_appClass", "Database tables", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        cmbTables->setWhatsThis(QApplication::translate("conf_appClass", "This control lists database tables.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        pushInsert->setToolTip(QApplication::translate("conf_appClass", "Insert row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushInsert->setStatusTip(QApplication::translate("conf_appClass", "Insert row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushInsert->setWhatsThis(QApplication::translate("conf_appClass", "Inserts row into table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushInsert->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushRemove->setToolTip(QApplication::translate("conf_appClass", "Remove row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushRemove->setStatusTip(QApplication::translate("conf_appClass", "Remove row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushRemove->setWhatsThis(QApplication::translate("conf_appClass", "Removes row into table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushRemove->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushApply_2->setToolTip(QApplication::translate("conf_appClass", "Apply changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushApply_2->setStatusTip(QApplication::translate("conf_appClass", "Apply changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushApply_2->setWhatsThis(QApplication::translate("conf_appClass", "Applies changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushApply_2->setText(QApplication::translate("conf_appClass", "Apply", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("conf_appClass", "Edit Tables", 0, QApplication::UnicodeUTF8));
        groupUsers->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        pushNewUser->setToolTip(QApplication::translate("conf_appClass", "Create new user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushNewUser->setStatusTip(QApplication::translate("conf_appClass", "Create new user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushNewUser->setWhatsThis(QApplication::translate("conf_appClass", "Creates new user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushNewUser->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushEditUser->setToolTip(QApplication::translate("conf_appClass", "Edit user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushEditUser->setStatusTip(QApplication::translate("conf_appClass", "Edit user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushEditUser->setWhatsThis(QApplication::translate("conf_appClass", "Edits user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushEditUser->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushRemoveUser->setToolTip(QApplication::translate("conf_appClass", "Remove user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushRemoveUser->setStatusTip(QApplication::translate("conf_appClass", "Remove user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushRemoveUser->setWhatsThis(QApplication::translate("conf_appClass", "Removes user", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushRemoveUser->setText(QString());
        pushRemoveUser->setShortcut(QApplication::translate("conf_appClass", "Del", 0, QApplication::UnicodeUTF8));
        groupUsersDetail->setTitle(QString());
        label_4->setText(QApplication::translate("conf_appClass", "Name", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("conf_appClass", "Role", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("conf_appClass", "Password", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("conf_appClass", "Repeat Password", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("conf_appClass", "Description", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("conf_appClass", "User Management", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("conf_appClass", "File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("conf_appClass", "Tools", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("conf_appClass", "Options", 0, QApplication::UnicodeUTF8));
        menuBackups->setTitle(QApplication::translate("conf_appClass", "Backups", 0, QApplication::UnicodeUTF8));
        menuPatches->setTitle(QApplication::translate("conf_appClass", "Patches", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class conf_appClass: public Ui_conf_appClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONF_APP_H
