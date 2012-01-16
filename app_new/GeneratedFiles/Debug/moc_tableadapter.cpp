/****************************************************************************
** Meta object code from reading C++ file 'tableadapter.h'
**
** Created: Mon 16. Jan 14:53:22 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tableadapter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tableadapter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TableAdapter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_TableAdapter[] = {
    "TableAdapter\0"
};

const QMetaObject TableAdapter::staticMetaObject = {
    { &XmlTable::staticMetaObject, qt_meta_stringdata_TableAdapter,
      qt_meta_data_TableAdapter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TableAdapter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TableAdapter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TableAdapter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableAdapter))
        return static_cast<void*>(const_cast< TableAdapter*>(this));
    return XmlTable::qt_metacast(_clname);
}

int TableAdapter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XmlTable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
