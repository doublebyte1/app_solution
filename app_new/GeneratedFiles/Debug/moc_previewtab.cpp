/****************************************************************************
** Meta object code from reading C++ file 'previewtab.h'
**
** Created: Tue 22. Nov 14:22:08 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../previewtab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'previewtab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PreviewTab[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   12,   11,   11, 0x05,
      46,   39,   11,   11, 0x05,
      93,   72,   11,   11, 0x05,
     124,  114,   11,   11, 0x25,

 // slots: signature, parameters, type, tag, flags
     140,   11,   11,   11, 0x0a,
     161,  158,  153,   11, 0x0a,
     228,  178,  153,   11, 0x0a,
     298,   72,   11,   11, 0x08,
     330,  321,   11,   11, 0x08,
     344,   11,   11,   11, 0x08,
     359,   11,   11,   11, 0x08,
     380,  374,   11,   11, 0x08,
     411,  404,  153,   11, 0x08,
     443,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PreviewTab[] = {
    "PreviewTab\0\0bIsLogbook\0isLogBook(bool)\0"
    "bBlock\0blockCatchUISignals(bool)\0"
    "bFinished,bDiscarded\0editLeave(bool,bool)\0"
    "bFinished\0editLeave(bool)\0onShowForm()\0"
    "bool\0on\0editRecord(bool)\0"
    "curTable,curStartDt,curEndDt,strTable,id,strError\0"
    "checkDependantDates(QString,QDateTime,QDateTime,QString,int,QString&)\0"
    "onEditLeave(bool,bool)\0bLogbook\0"
    "setTips(bool)\0createRecord()\0"
    "removeRecord()\0index\0previewRow(QModelIndex)\0"
    "button\0onButtonClick(QAbstractButton*)\0"
    "onItemSelection()\0"
};

const QMetaObject PreviewTab::staticMetaObject = {
    { &GenericTab::staticMetaObject, qt_meta_stringdata_PreviewTab,
      qt_meta_data_PreviewTab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PreviewTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PreviewTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PreviewTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PreviewTab))
        return static_cast<void*>(const_cast< PreviewTab*>(this));
    return GenericTab::qt_metacast(_clname);
}

int PreviewTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GenericTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: isLogBook((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: blockCatchUISignals((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 2: editLeave((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 3: editLeave((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 4: onShowForm(); break;
        case 5: { bool _r = editRecord((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = checkDependantDates((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QDateTime(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: onEditLeave((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 8: setTips((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 9: createRecord(); break;
        case 10: removeRecord(); break;
        case 11: previewRow((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 12: { bool _r = onButtonClick((*reinterpret_cast< QAbstractButton*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: onItemSelection(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void PreviewTab::isLogBook(const bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PreviewTab::blockCatchUISignals(const bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PreviewTab::editLeave(const bool _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
