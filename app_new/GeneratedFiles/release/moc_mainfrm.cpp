/****************************************************************************
** Meta object code from reading C++ file 'mainfrm.h'
**
** Created: Fri 24. Jun 14:32:03 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainFrm[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,    9,    8,    8, 0x08,
      34,    8,    8,    8, 0x08,
      54,   44,    8,    8, 0x08,
     126,   84,    8,    8, 0x08,
     240,    8,    8,    8, 0x08,
     263,  259,    8,    8, 0x08,
     283,  259,    8,    8, 0x08,
     325,  304,    8,    8, 0x08,
     352,    8,    8,    8, 0x08,
     379,  370,    8,    8, 0x08,
     399,    8,    8,    8, 0x08,
     425,  418,    8,    8, 0x08,
     448,    8,    8,    8, 0x08,
     459,    8,    8,    8, 0x08,
     471,    8,    8,    8, 0x08,
     483,    8,    8,    8, 0x08,
     497,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainFrm[] = {
    "MainFrm\0\0idx,bOk\0addTab(int,bool)\0"
    "newTabs()\0bNext,idx\0navigateThroughTabs(bool,int)\0"
    "mode,persistence,sample,blackList,options\0"
    "showFrameDetails(FrmFrameDetails::Mode,FrmFrameDetails::Persistence,Sa"
    "mple*,QList<int>&,FrmFrameDetails::Options)\0"
    "hideFrameDetails()\0str\0statusShow(QString)\0"
    "statusClean(QString)\0strError,bShowMsgBox\0"
    "displayError(QString,bool)\0cleanupMsgBoxes()\0"
    "bLogBook\0rearrangeTabs(bool)\0"
    "aboutThisProject()\0bReady\0"
    "rulesInitialized(bool)\0loadFile()\0"
    "closeFile()\0writeFile()\0loadReports()\0"
    "closeReports()\0"
};

const QMetaObject MainFrm::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainFrm,
      qt_meta_data_MainFrm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainFrm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainFrm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainFrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainFrm))
        return static_cast<void*>(const_cast< MainFrm*>(this));
    if (!strcmp(_clname, "Ui::MainWindow"))
        return static_cast< Ui::MainWindow*>(const_cast< MainFrm*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainFrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addTab((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: newTabs(); break;
        case 2: navigateThroughTabs((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: showFrameDetails((*reinterpret_cast< const FrmFrameDetails::Mode(*)>(_a[1])),(*reinterpret_cast< const FrmFrameDetails::Persistence(*)>(_a[2])),(*reinterpret_cast< Sample*(*)>(_a[3])),(*reinterpret_cast< QList<int>(*)>(_a[4])),(*reinterpret_cast< const FrmFrameDetails::Options(*)>(_a[5]))); break;
        case 4: hideFrameDetails(); break;
        case 5: statusShow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: statusClean((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: displayError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 8: cleanupMsgBoxes(); break;
        case 9: rearrangeTabs((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: aboutThisProject(); break;
        case 11: rulesInitialized((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: loadFile(); break;
        case 13: closeFile(); break;
        case 14: writeFile(); break;
        case 15: loadReports(); break;
        case 16: closeReports(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
