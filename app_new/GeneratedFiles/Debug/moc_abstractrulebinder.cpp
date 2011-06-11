/****************************************************************************
** Meta object code from reading C++ file 'abstractrulebinder.h'
**
** Created: Fri 10. Jun 16:18:37 2011
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
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      45,   32,   19,   19, 0x05,
      86,   66,   19,   19, 0x05,
     120,  116,   19,   19, 0x05,
     146,  116,   19,   19, 0x05,
     170,   19,   19,   19, 0x05,
     189,  185,   19,   19, 0x05,
     225,  209,   19,   19, 0x05,
     249,  185,   19,   19, 0x25,

 // slots: signature, parameters, type, tag, flags
     273,   19,  268,   19, 0x08,
     292,   19,   19,   19, 0x08,
     324,  308,   19,   19, 0x08,
     369,  360,   19,   19, 0x28,
     396,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AbstractRuleBinder[] = {
    "AbstractRuleBinder\0\0addRecord()\0"
    "strTableName\0recordAdded(QString)\0"
    "strTableName,varPar\0recordAdded(QString,QVariant)\0"
    "bOk\0finishedPostTrigger(bool)\0"
    "finishedPreSubmit(bool)\0submitRecord()\0"
    "str\0showStatus(QString)\0str,bShowMsgBox\0"
    "showError(QString,bool)\0showError(QString)\0"
    "bool\0getDefaultValues()\0onFireTrigger()\0"
    "strTable,varPar\0onFirePostTrigger(QString,QVariant)\0"
    "strTable\0onFirePostTrigger(QString)\0"
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
        case 1: recordAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: recordAdded((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 3: finishedPostTrigger((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: finishedPreSubmit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: submitRecord(); break;
        case 6: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 8: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { bool _r = getDefaultValues();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: onFireTrigger(); break;
        case 11: onFirePostTrigger((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 12: onFirePostTrigger((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: getPreSubmitValidation(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void AbstractRuleBinder::addRecord()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void AbstractRuleBinder::recordAdded(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AbstractRuleBinder::recordAdded(const QString _t1, const QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AbstractRuleBinder::finishedPostTrigger(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AbstractRuleBinder::finishedPreSubmit(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AbstractRuleBinder::submitRecord()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void AbstractRuleBinder::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AbstractRuleBinder::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
