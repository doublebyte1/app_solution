/****************************************************************************
** Meta object code from reading C++ file 'mainfrm.h'
**
** Created: Mon 3. Dec 12:45:19 2012
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
static const uint qt_meta_data_RebuildIndexesThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   22,   21,   21, 0x05,
      62,   46,   21,   21, 0x05,
      86,   22,   21,   21, 0x25,

       0        // eod
};

static const char qt_meta_stringdata_RebuildIndexesThread[] = {
    "RebuildIndexesThread\0\0str\0showStatus(QString)\0"
    "str,bShowMsgBox\0showError(QString,bool)\0"
    "showError(QString)\0"
};

const QMetaObject RebuildIndexesThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_RebuildIndexesThread,
      qt_meta_data_RebuildIndexesThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RebuildIndexesThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RebuildIndexesThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RebuildIndexesThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RebuildIndexesThread))
        return static_cast<void*>(const_cast< RebuildIndexesThread*>(this));
    return QThread::qt_metacast(_clname);
}

int RebuildIndexesThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 2: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RebuildIndexesThread::showStatus(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RebuildIndexesThread::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_MainFrm[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,    9,    8,    8, 0x08,
      36,    8,    8,    8, 0x28,
      60,   50,    8,    8, 0x08,
      82,    8,    8,    8, 0x08,
     102,   92,    8,    8, 0x08,
     174,  132,    8,    8, 0x08,
     267,    8,    8,    8, 0x08,
     286,    8,    8,    8, 0x08,
     304,    8,    8,    8, 0x08,
     326,  322,    8,    8, 0x08,
     346,  322,    8,    8, 0x08,
     388,  367,    8,    8, 0x08,
     415,    8,    8,    8, 0x08,
     433,    8,    8,    8, 0x08,
     452,    8,    8,    8, 0x08,
     475,  468,    8,    8, 0x08,
     498,    8,    8,    8, 0x08,
     509,    8,    8,    8, 0x08,
     526,    8,    8,    8, 0x08,
     538,    8,    8,    8, 0x08,
     550,    8,    8,    8, 0x08,
     574,  570,    8,    8, 0x08,
     607,    8,    8,    8, 0x08,
     626,  570,    8,    8, 0x08,
     658,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainFrm[] = {
    "MainFrm\0\0bDisable\0disableTabs(bool)\0"
    "disableTabs()\0strHelpId\0setCurHelpId(QString)\0"
    "newTabs()\0bNext,idx\0navigateThroughTabs(bool,int)\0"
    "mode,persistence,sample,blackList,options\0"
    "showFrameDetails(FrmFrameDetails::Mode,FrmFrameDetails::Persistence,Sa"
    "mple*,QList<int>&,int)\0"
    "hideFrameDetails()\0showFrmSampling()\0"
    "hideFrmSampling()\0str\0statusShow(QString)\0"
    "statusClean(QString)\0strError,bShowMsgBox\0"
    "displayError(QString,bool)\0cleanupMsgBoxes()\0"
    "aboutThisProject()\0callAssistant()\0"
    "bReady\0rulesInitialized(bool)\0loadFile()\0"
    "openRecentFile()\0closeFile()\0writeFile()\0"
    "closeSecondaryFrm()\0frm\0"
    "closeSecondaryFrm(SecondaryFrm*)\0"
    "loadSecondaryFrm()\0loadSecondaryFrm(SecondaryFrm*)\0"
    "RebuildIndexes()\0"
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
        case 0: disableTabs((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: disableTabs(); break;
        case 2: setCurHelpId((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: newTabs(); break;
        case 4: navigateThroughTabs((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 5: showFrameDetails((*reinterpret_cast< const FrmFrameDetails::Mode(*)>(_a[1])),(*reinterpret_cast< const FrmFrameDetails::Persistence(*)>(_a[2])),(*reinterpret_cast< Sample*(*)>(_a[3])),(*reinterpret_cast< QList<int>(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5]))); break;
        case 6: hideFrameDetails(); break;
        case 7: showFrmSampling(); break;
        case 8: hideFrmSampling(); break;
        case 9: statusShow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: statusClean((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: displayError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 12: cleanupMsgBoxes(); break;
        case 13: aboutThisProject(); break;
        case 14: callAssistant(); break;
        case 15: rulesInitialized((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: loadFile(); break;
        case 17: openRecentFile(); break;
        case 18: closeFile(); break;
        case 19: writeFile(); break;
        case 20: closeSecondaryFrm(); break;
        case 21: closeSecondaryFrm((*reinterpret_cast< SecondaryFrm*(*)>(_a[1]))); break;
        case 22: loadSecondaryFrm(); break;
        case 23: loadSecondaryFrm((*reinterpret_cast< SecondaryFrm*(*)>(_a[1]))); break;
        case 24: RebuildIndexes(); break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
