/****************************************************************************
** Meta object code from reading C++ file 'xmltable.h'
**
** Created: Sun 26. Jun 15:39:54 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../xmltable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xmltable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XmlTable[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_XmlTable[] = {
    "XmlTable\0\0doRollbackImport()\0"
};

const QMetaObject XmlTable::staticMetaObject = {
    { &AbstractTableFormat::staticMetaObject, qt_meta_stringdata_XmlTable,
      qt_meta_data_XmlTable, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XmlTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XmlTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XmlTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XmlTable))
        return static_cast<void*>(const_cast< XmlTable*>(this));
    return AbstractTableFormat::qt_metacast(_clname);
}

int XmlTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractTableFormat::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: doRollbackImport(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE