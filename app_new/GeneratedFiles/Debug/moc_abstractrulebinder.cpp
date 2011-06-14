/****************************************************************************
** Meta object code from reading C++ file 'abstractrulebinder.h'
**
** Created: Mon 13. Jun 17:14:23 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../abstractrulebinder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractrulebinder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AbstractRuleBinder[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      32,   19,   19,   19, 0x05,
      51,   47,   19,   19, 0x05,
      79,   75,   19,   19, 0x05,
     115,   99,   19,   19, 0x05,
     139,   75,   19,   19, 0x25,

 // slots: signature, parameters, type, tag, flags
     163,   19,  158,   19, 0x08,
     182,   19,   19,   19, 0x08,
     198,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AbstractRuleBinder[] = {
    "AbstractRuleBinder\0\0addRecord()\0"
    "submitRecord()\0bOk\0finishedPreSubmit(bool)\0"
    "str\0showStatus(QString)\0str,bShowMsgBox\0"
    "showError(QString,bool)\0showError(QString)\0"
    "bool\0getDefaultValues()\0onFireTrigger()\0"
    "getPreSubmitValidation()\0"
};

const QMetaObject AbstractRuleBinder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AbstractRuleBinder,
      qt_meta_data_AbstractRuleBinder, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AbstractRuleBinder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AbstractRuleBinder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AbstractRuleBinder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractRuleBinder))
        return static_cast<void*>(const_cast< AbstractRuleBinder*>(this));
    return QObject::qt_metacast(_clname);
}

int AbstractRuleBinder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addRecord(); break;
        case 1: submitRecord(); break;
        case 2: finishedPreSubmit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 5: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: { bool _r = getDefaultValues();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: onFireTrigger(); break;
        case 8: getPreSubmitValidation(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void AbstractRuleBinder::addRecord()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void AbstractRuleBinder::submitRecord()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void AbstractRuleBinder::finishedPreSubmit(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AbstractRuleBinder::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AbstractRuleBinder::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
