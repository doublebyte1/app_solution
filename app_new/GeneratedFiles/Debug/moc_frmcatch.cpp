/****************************************************************************
** Meta object code from reading C++ file 'frmcatch.h'
**
** Created: Mon 16. Jan 14:53:45 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmcatch.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmcatch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmCatch[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      31,   25,    9,    9, 0x08,
      55,    9,    9,    9, 0x08,
      94,   73,    9,    9, 0x08,
     117,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmCatch[] = {
    "FrmCatch\0\0createRecord()\0index\0"
    "previewRow(QModelIndex)\0onItemSelection()\0"
    "bFinished,bDiscarded\0onEditLeave(bool,bool)\0"
    "editFinished()\0"
};

const QMetaObject FrmCatch::staticMetaObject = {
    { &PreviewTab::staticMetaObject, qt_meta_stringdata_FrmCatch,
      qt_meta_data_FrmCatch, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmCatch::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmCatch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmCatch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmCatch))
        return static_cast<void*>(const_cast< FrmCatch*>(this));
    if (!strcmp(_clname, "Ui::FrmCatch"))
        return static_cast< Ui::FrmCatch*>(const_cast< FrmCatch*>(this));
    return PreviewTab::qt_metacast(_clname);
}

int FrmCatch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreviewTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createRecord(); break;
        case 1: previewRow((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: onItemSelection(); break;
        case 3: onEditLeave((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 4: editFinished(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
