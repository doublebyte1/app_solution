/****************************************************************************
** Meta object code from reading C++ file 'conf_app.h'
**
** Created: Thu 16. Aug 14:22:13 2012
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
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      34,   30,    9,    9, 0x05,
     102,   54,    9,    9, 0x05,
     192,  182,    9,    9, 0x05,
     243,  222,    9,    9, 0x05,
     274,  264,    9,    9, 0x25,

 // slots: signature, parameters, type, tag, flags
     299,  290,    9,    9, 0x08,
     318,    9,    9,    9, 0x08,
     339,    9,    9,    9, 0x08,
     351,    9,    9,    9, 0x08,
     366,    9,    9,    9, 0x08,
     387,   30,    9,    9, 0x08,
     420,  409,    9,    9, 0x08,
     441,    9,    9,    9, 0x08,
     449,    9,    9,    9, 0x08,
     471,  463,    9,    9, 0x08,
     501,  495,    9,    9, 0x08,
     524,    9,    9,    9, 0x08,
     536,    9,    9,    9, 0x08,
     548,    9,    9,    9, 0x08,
     559,    9,    9,    9, 0x08,
     571,    9,    9,    9, 0x08,
     580,    9,    9,    9, 0x08,
     590,    9,    9,    9, 0x08,
     609,    9,    9,    9, 0x08,
     629,    9,    9,    9, 0x08,
     647,    9,    9,    9, 0x08,
     670,    9,    9,    9, 0x08,
     684,    9,    9,    9, 0x08,
     713,    9,    9,    9, 0x08,
     735,  495,    9,    9, 0x08,
     757,    9,    9,    9, 0x08,
     787,  780,  775,    9, 0x08,
     819,    9,    9,    9, 0x08,
     834,   54,  775,    9, 0x08,
     918,  182,    9,    9, 0x08,
    1016,  950,    9,    9, 0x08,
    1146,  222,    9,    9, 0x08,
    1175, 1169,    9,    9, 0x08,
    1197,    9,    9,    9, 0x08,
    1217, 1169,    9,    9, 0x08,
    1245, 1242,  775,    9, 0x08,
    1260,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_conf_app[] = {
    "conf_app\0\0connectionChanged()\0str\0"
    "statusShow(QString)\0"
    "aMapper,aButtonBox,aGroupBox,viewModel,strQuery\0"
    "submit(QDataWidgetMapper*,QDialogButtonBox*,QGroupBox*,QSqlQueryModel*"
    ",QString)\0"
    "bLock,box\0lockControls(bool,QGroupBox*)\0"
    "bFinished,bDiscarded\0editLeave(bool,bool)\0"
    "bFinished\0editLeave(bool)\0strTable\0"
    "showTable(QString)\0applyChanges2Table()\0"
    "connectDB()\0disconnectDB()\0"
    "onConnectionChange()\0onStatusShow(QString)\0"
    "strCountry\0filterModel(QString)\0apply()\0"
    "enableApply()\0bNoShow\0onShowStartupMsgI(bool)\0"
    "bShow\0onShowStartupMsg(bool)\0insertRow()\0"
    "removeRow()\0doBackup()\0doRestore()\0"
    "doDump()\0doPatch()\0readProcessError()\0"
    "readProcessOutput()\0processFinished()\0"
    "finishedReadingNames()\0parseParams()\0"
    "finishedCheckingBackupFile()\0"
    "parseBackupFileInfo()\0showSqlMessages(bool)\0"
    "finishedRestore()\0bool\0button\0"
    "onButtonClick(QAbstractButton*)\0"
    "createRecord()\0"
    "ApplyModel(QDataWidgetMapper*,QDialogButtonBox*,QGroupBox*,QSqlQueryMo"
    "del*,QString)\0"
    "onLockControls(bool,QGroupBox*)\0"
    "index,aMapper,aPushNew,aPushEdit,aPushRemove,group,buttons,aModel\0"
    "previewRecord(QModelIndex,QDataWidgetMapper*,QPushButton*,QPushButton*"
    ",QPushButton*,QGroupBox*,QDialogButtonBox*,QSqlTableModel*)\0"
    "onEditLeave(bool,bool)\0index\0"
    "resizeUsersTable(int)\0adjustUserEnables()\0"
    "previewUser(QModelIndex)\0on\0editUser(bool)\0"
    "removeUser()\0"
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
        case 4: editLeave((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 5: editLeave((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 6: showTable((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: applyChanges2Table(); break;
        case 8: connectDB(); break;
        case 9: disconnectDB(); break;
        case 10: onConnectionChange(); break;
        case 11: onStatusShow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: filterModel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: apply(); break;
        case 14: enableApply(); break;
        case 15: onShowStartupMsgI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: onShowStartupMsg((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 17: insertRow(); break;
        case 18: removeRow(); break;
        case 19: doBackup(); break;
        case 20: doRestore(); break;
        case 21: doDump(); break;
        case 22: doPatch(); break;
        case 23: readProcessError(); break;
        case 24: readProcessOutput(); break;
        case 25: processFinished(); break;
        case 26: finishedReadingNames(); break;
        case 27: parseParams(); break;
        case 28: finishedCheckingBackupFile(); break;
        case 29: parseBackupFileInfo(); break;
        case 30: showSqlMessages((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: finishedRestore(); break;
        case 32: { bool _r = onButtonClick((*reinterpret_cast< QAbstractButton*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 33: createRecord(); break;
        case 34: { bool _r = ApplyModel((*reinterpret_cast< QDataWidgetMapper*(*)>(_a[1])),(*reinterpret_cast< QDialogButtonBox*(*)>(_a[2])),(*reinterpret_cast< QGroupBox*(*)>(_a[3])),(*reinterpret_cast< QSqlQueryModel*(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 35: onLockControls((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QGroupBox*(*)>(_a[2]))); break;
        case 36: previewRecord((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< QDataWidgetMapper*(*)>(_a[2])),(*reinterpret_cast< QPushButton*(*)>(_a[3])),(*reinterpret_cast< QPushButton*(*)>(_a[4])),(*reinterpret_cast< QPushButton*(*)>(_a[5])),(*reinterpret_cast< QGroupBox*(*)>(_a[6])),(*reinterpret_cast< QDialogButtonBox*(*)>(_a[7])),(*reinterpret_cast< QSqlTableModel*(*)>(_a[8]))); break;
        case 37: onEditLeave((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 38: resizeUsersTable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: adjustUserEnables(); break;
        case 40: previewUser((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 41: { bool _r = editUser((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 42: removeUser(); break;
        default: ;
        }
        _id -= 43;
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

// SIGNAL 4
void conf_app::editLeave(const bool _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
