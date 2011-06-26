/****************************************************************************
** Meta object code from reading C++ file 'mainfrm.h'
**
** Created: Sun 26. Jun 18:36:43 2011
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
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      25,    8,    8,    8, 0x08,
      49,   41,    8,    8, 0x08,
      66,    8,    8,    8, 0x08,
      86,   76,    8,    8, 0x08,
     158,  116,    8,    8, 0x08,
     272,    8,    8,    8, 0x08,
     295,  291,    8,    8, 0x08,
     315,  291,    8,    8, 0x08,
     357,  336,    8,    8, 0x08,
     384,    8,    8,    8, 0x08,
     411,  402,    8,    8, 0x08,
     431,    8,    8,    8, 0x08,
     457,  450,    8,    8, 0x08,
     480,    8,    8,    8, 0x08,
     491,    8,    8,    8, 0x08,
     503,    8,    8,    8, 0x08,
     515,    8,    8,    8, 0x08,
     529,    8,    8,    8, 0x08,
     553,  549,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainFrm[] = {
    "MainFrm\0\0LoadExportFrm()\0LoadImportFrm()\0"
    "idx,bOk\0addTab(int,bool)\0newTabs()\0"
    "bNext,idx\0navigateThroughTabs(bool,int)\0"
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
    "closeSecondaryFrm()\0frm\0"
    "closeSecondaryFrm(QWidget*)\0"
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
        case 0: LoadExportFrm(); break;
        case 1: LoadImportFrm(); break;
        case 2: addTab((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: newTabs(); break;
        case 4: navigateThroughTabs((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 5: showFrameDetails((*reinterpret_cast< const FrmFrameDetails::Mode(*)>(_a[1])),(*reinterpret_cast< const FrmFrameDetails::Persistence(*)>(_a[2])),(*reinterpret_cast< Sample*(*)>(_a[3])),(*reinterpret_cast< QList<int>(*)>(_a[4])),(*reinterpret_cast< const FrmFrameDetails::Options(*)>(_a[5]))); break;
        case 6: hideFrameDetails(); break;
        case 7: statusShow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: statusClean((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: displayError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 10: cleanupMsgBoxes(); break;
        case 11: rearrangeTabs((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: aboutThisProject(); break;
        case 13: rulesInitialized((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: loadFile(); break;
        case 15: closeFile(); break;
        case 16: writeFile(); break;
        case 17: loadReports(); break;
        case 18: closeSecondaryFrm(); break;
        case 19: closeSecondaryFrm((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
