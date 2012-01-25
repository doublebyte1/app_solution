/****************************************************************************
** Meta object code from reading C++ file 'conf_app.h'
**
** Created: Tue 24. Jan 09:47:47 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../conf_app.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'conf_app.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_conf_app[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      34,   30,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   54,    9,    9, 0x08,
      82,    9,    9,    9, 0x08,
     103,    9,    9,    9, 0x08,
     115,    9,    9,    9, 0x08,
     130,    9,    9,    9, 0x08,
     151,   30,    9,    9, 0x08,
     184,  173,    9,    9, 0x08,
     205,    9,    9,    9, 0x08,
     213,    9,    9,    9, 0x08,
     235,  227,    9,    9, 0x08,
     265,  259,    9,    9, 0x08,
     288,    9,    9,    9, 0x08,
     300,    9,    9,    9, 0x08,
     312,    9,    9,    9, 0x08,
     323,    9,    9,    9, 0x08,
     335,    9,    9,    9, 0x08,
     354,    9,    9,    9, 0x08,
     374,    9,    9,    9, 0x08,
     392,    9,    9,    9, 0x08,
     415,    9,    9,    9, 0x08,
     429,    9,    9,    9, 0x08,
     458,    9,    9,    9, 0x08,
     480,  259,    9,    9, 0x08,
     502,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_conf_app[] = {
    "conf_app\0\0connectionChanged()\0str\0"
    "statusShow(QString)\0strTable\0"
    "showTable(QString)\0applyChanges2Table()\0"
    "connectDB()\0disconnectDB()\0"
    "onConnectionChange()\0onStatusShow(QString)\0"
    "strCountry\0filterModel(QString)\0apply()\0"
    "enableApply()\0bNoShow\0onShowStartupMsgI(bool)\0"
    "bShow\0onShowStartupMsg(bool)\0insertRow()\0"
    "removeRow()\0doBackup()\0doRestore()\0"
    "readProcessError()\0readProcessOutput()\0"
    "processFinished()\0finishedReadingNames()\0"
    "parseParams()\0finishedCheckingBackupFile()\0"
    "parseBackupFileInfo()\0showSqlMessages(bool)\0"
    "finishedRestore()\0"
};

const QMetaObject conf_app::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_conf_app,
      qt_meta_data_conf_app, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &conf_app::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *conf_app::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *conf_app::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_conf_app))
        return static_cast<void*>(const_cast< conf_app*>(this));
    if (!strcmp(_clname, "Ui::conf_appClass"))
        return static_cast< Ui::conf_appClass*>(const_cast< conf_app*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int conf_app::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connectionChanged(); break;
        case 1: statusShow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: showTable((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: applyChanges2Table(); break;
        case 4: connectDB(); break;
        case 5: disconnectDB(); break;
        case 6: onConnectionChange(); break;
        case 7: onStatusShow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: filterModel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: apply(); break;
        case 10: enableApply(); break;
        case 11: onShowStartupMsgI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: onShowStartupMsg((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 13: insertRow(); break;
        case 14: removeRow(); break;
        case 15: doBackup(); break;
        case 16: doRestore(); break;
        case 17: readProcessError(); break;
        case 18: readProcessOutput(); break;
        case 19: processFinished(); break;
        case 20: finishedReadingNames(); break;
        case 21: parseParams(); break;
        case 22: finishedCheckingBackupFile(); break;
        case 23: parseBackupFileInfo(); break;
        case 24: showSqlMessages((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: finishedRestore(); break;
        default: ;
        }
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void conf_app::connectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void conf_app::statusShow(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
