/****************************************************************************
** Meta object code from reading C++ file 'frmoperation.h'
**
** Created: Fri 23. Dec 17:57:42 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmoperation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmoperation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmOperation[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      35,   29,   13,   13, 0x08,
      59,   13,   13,   13, 0x08,
      77,   13,   13,   13, 0x08,
     100,   13,   13,   13, 0x08,
     146,  125,   13,   13, 0x08,
     169,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmOperation[] = {
    "FrmOperation\0\0createRecord()\0index\0"
    "previewRow(QModelIndex)\0onItemSelection()\0"
    "blockCustomDateCtrls()\0unblockCustomDateCtrls()\0"
    "bFinished,bDiscarded\0onEditLeave(bool,bool)\0"
    "editFinished()\0"
};

const QMetaObject FrmOperation::staticMetaObject = {
    { &PreviewTab::staticMetaObject, qt_meta_stringdata_FrmOperation,
      qt_meta_data_FrmOperation, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmOperation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmOperation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmOperation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmOperation))
        return static_cast<void*>(const_cast< FrmOperation*>(this));
    if (!strcmp(_clname, "Ui::FrmOperation"))
        return static_cast< Ui::FrmOperation*>(const_cast< FrmOperation*>(this));
    return PreviewTab::qt_metacast(_clname);
}

int FrmOperation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreviewTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createRecord(); break;
        case 1: previewRow((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: onItemSelection(); break;
        case 3: blockCustomDateCtrls(); break;
        case 4: unblockCustomDateCtrls(); break;
        case 5: onEditLeave((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 6: editFinished(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
