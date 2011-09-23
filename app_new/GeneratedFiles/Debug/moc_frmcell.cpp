/****************************************************************************
** Meta object code from reading C++ file 'frmcell.h'
**
** Created: Fri 23. Sep 10:17:31 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmcell.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmcell.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmCell[] = {

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
       9,    8,    8,    8, 0x08,
      27,   24,    8,    8, 0x08,
      50,   44,    8,    8, 0x08,
      74,    8,    8,    8, 0x08,
      95,    8,    8,    8, 0x08,
     113,    8,    8,    8, 0x08,
     136,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmCell[] = {
    "FrmCell\0\0createRecord()\0on\0editRecord(bool)\0"
    "index\0previewRow(QModelIndex)\0"
    "onShowFrameDetails()\0onItemSelection()\0"
    "blockCustomDateCtrls()\0unblockCustomDateCtrls()\0"
};

const QMetaObject FrmCell::staticMetaObject = {
    { &PreviewTab::staticMetaObject, qt_meta_stringdata_FrmCell,
      qt_meta_data_FrmCell, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmCell::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmCell::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmCell::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmCell))
        return static_cast<void*>(const_cast< FrmCell*>(this));
    if (!strcmp(_clname, "Ui::frmCell"))
        return static_cast< Ui::frmCell*>(const_cast< FrmCell*>(this));
    return PreviewTab::qt_metacast(_clname);
}

int FrmCell::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreviewTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createRecord(); break;
        case 1: editRecord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: previewRow((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: onShowFrameDetails(); break;
        case 4: onItemSelection(); break;
        case 5: blockCustomDateCtrls(); break;
        case 6: unblockCustomDateCtrls(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
