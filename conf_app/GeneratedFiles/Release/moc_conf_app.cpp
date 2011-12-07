/****************************************************************************
** Meta object code from reading C++ file 'conf_app.h'
**
** Created: Wed 7. Dec 15:22:18 2011
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
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      34,   30,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,    9,    9,    9, 0x08,
      66,    9,    9,    9, 0x08,
      81,    9,    9,    9, 0x08,
     102,   30,    9,    9, 0x08,
     135,  124,    9,    9, 0x08,
     156,    9,    9,    9, 0x08,
     164,    9,    9,    9, 0x08,
     186,  178,    9,    9, 0x08,
     216,  210,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_conf_app[] = {
    "conf_app\0\0connectionChanged()\0str\0"
    "statusShow(QString)\0connectDB()\0"
    "disconnectDB()\0onConnectionChange()\0"
    "onStatusShow(QString)\0strCountry\0"
    "filterModel(QString)\0apply()\0enableApply()\0"
    "bNoShow\0onShowStartupMsgI(bool)\0bShow\0"
    "onShowStartupMsg(bool)\0"
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
        case 2: connectDB(); break;
        case 3: disconnectDB(); break;
        case 4: onConnectionChange(); break;
        case 5: onStatusShow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: filterModel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: apply(); break;
        case 8: enableApply(); break;
        case 9: onShowStartupMsgI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: onShowStartupMsg((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
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
