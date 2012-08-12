/****************************************************************************
** Meta object code from reading C++ file 'conf_app.h'
**
** Created: Sun 12. Aug 18:50:56 2012
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
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      34,   30,    9,    9, 0x05,
     102,   54,    9,    9, 0x05,
     192,  182,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     231,  222,    9,    9, 0x08,
     250,    9,    9,    9, 0x08,
     271,    9,    9,    9, 0x08,
     283,    9,    9,    9, 0x08,
     298,    9,    9,    9, 0x08,
     319,   30,    9,    9, 0x08,
     352,  341,    9,    9, 0x08,
     373,    9,    9,    9, 0x08,
     381,    9,    9,    9, 0x08,
     403,  395,    9,    9, 0x08,
     433,  427,    9,    9, 0x08,
     456,    9,    9,    9, 0x08,
     468,    9,    9,    9, 0x08,
     480,    9,    9,    9, 0x08,
     491,    9,    9,    9, 0x08,
     503,    9,    9,    9, 0x08,
     512,    9,    9,    9, 0x08,
     522,    9,    9,    9, 0x08,
     541,    9,    9,    9, 0x08,
     561,    9,    9,    9, 0x08,
     579,    9,    9,    9, 0x08,
     602,    9,    9,    9, 0x08,
     616,    9,    9,    9, 0x08,
     645,    9,    9,    9, 0x08,
     667,  427,    9,    9, 0x08,
     689,    9,    9,    9, 0x08,
     713,  707,    9,    9, 0x08,
     747,  740,  735,    9, 0x08,
     779,    9,    9,    9, 0x08,
     794,   54,  735,    9, 0x08,
     878,  182,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_conf_app[] = {
    "conf_app\0\0connectionChanged()\0str\0"
    "statusShow(QString)\0"
    "aMapper,aButtonBox,aGroupBox,viewModel,strQuery\0"
    "submit(QDataWidgetMapper*,QDialogButtonBox*,QGroupBox*,QSqlQueryModel*"
    ",QString)\0"
    "bLock,box\0lockControls(bool,QGroupBox*)\0"
    "strTable\0showTable(QString)\0"
    "applyChanges2Table()\0connectDB()\0"
    "disconnectDB()\0onConnectionChange()\0"
    "onStatusShow(QString)\0strCountry\0"
    "filterModel(QString)\0apply()\0enableApply()\0"
    "bNoShow\0onShowStartupMsgI(bool)\0bShow\0"
    "onShowStartupMsg(bool)\0insertRow()\0"
    "removeRow()\0doBackup()\0doRestore()\0"
    "doDump()\0doPatch()\0readProcessError()\0"
    "readProcessOutput()\0processFinished()\0"
    "finishedReadingNames()\0parseParams()\0"
    "finishedCheckingBackupFile()\0"
    "parseBackupFileInfo()\0showSqlMessages(bool)\0"
    "finishedRestore()\0index\0resizeUsersTable(int)\0"
    "bool\0button\0onButtonClick(QAbstractButton*)\0"
    "createRecord()\0"
    "ApplyModel(QDataWidgetMapper*,QDialogButtonBox*,QGroupBox*,QSqlQueryMo"
    "del*,QString)\0"
    "onLockControls(bool,QGroupBox*)\0"
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
        case 2: submit((*reinterpret_cast< QDataWidgetMapper*(*)>(_a[1])),(*reinterpret_cast< QDialogButtonBox*(*)>(_a[2])),(*reinterpret_cast< QGroupBox*(*)>(_a[3])),(*reinterpret_cast< QSqlQueryModel*(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 3: lockControls((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QGroupBox*(*)>(_a[2]))); break;
        case 4: showTable((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: applyChanges2Table(); break;
        case 6: connectDB(); break;
        case 7: disconnectDB(); break;
        case 8: onConnectionChange(); break;
        case 9: onStatusShow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: filterModel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: apply(); break;
        case 12: enableApply(); break;
        case 13: onShowStartupMsgI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: onShowStartupMsg((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 15: insertRow(); break;
        case 16: removeRow(); break;
        case 17: doBackup(); break;
        case 18: doRestore(); break;
        case 19: doDump(); break;
        case 20: doPatch(); break;
        case 21: readProcessError(); break;
        case 22: readProcessOutput(); break;
        case 23: processFinished(); break;
        case 24: finishedReadingNames(); break;
        case 25: parseParams(); break;
        case 26: finishedCheckingBackupFile(); break;
        case 27: parseBackupFileInfo(); break;
        case 28: showSqlMessages((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: finishedRestore(); break;
        case 30: resizeUsersTable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: { bool _r = onButtonClick((*reinterpret_cast< QAbstractButton*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 32: createRecord(); break;
        case 33: { bool _r = ApplyModel((*reinterpret_cast< QDataWidgetMapper*(*)>(_a[1])),(*reinterpret_cast< QDialogButtonBox*(*)>(_a[2])),(*reinterpret_cast< QGroupBox*(*)>(_a[3])),(*reinterpret_cast< QSqlQueryModel*(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 34: onLockControls((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QGroupBox*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 35;
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

// SIGNAL 2
void conf_app::submit(QDataWidgetMapper * _t1, QDialogButtonBox * _t2, QGroupBox * _t3, QSqlQueryModel * _t4, const QString _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void conf_app::lockControls(bool _t1, QGroupBox * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
