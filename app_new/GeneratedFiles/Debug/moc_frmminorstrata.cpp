/****************************************************************************
** Meta object code from reading C++ file 'frmminorstrata.h'
**
** Created: Fri 23. Sep 10:26:00 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmminorstrata.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmminorstrata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmMinorStrata[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      34,   31,   15,   15, 0x08,
      57,   51,   15,   15, 0x08,
      81,   15,   15,   15, 0x08,
     104,   15,   15,   15, 0x08,
     137,  129,   15,   15, 0x08,
     159,   15,   15,   15, 0x08,
     180,   15,   15,   15, 0x08,
     198,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmMinorStrata[] = {
    "FrmMinorStrata\0\0createRecord()\0on\0"
    "editRecord(bool)\0index\0previewRow(QModelIndex)\0"
    "blockCustomDateCtrls()\0unblockCustomDateCtrls()\0"
    "bActive\0setActiveReason(bool)\0"
    "disableReasonCombo()\0onItemSelection()\0"
    "onShowFrameDetails()\0"
};

const QMetaObject FrmMinorStrata::staticMetaObject = {
    { &PreviewTab::staticMetaObject, qt_meta_stringdata_FrmMinorStrata,
      qt_meta_data_FrmMinorStrata, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmMinorStrata::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmMinorStrata::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmMinorStrata::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmMinorStrata))
        return static_cast<void*>(const_cast< FrmMinorStrata*>(this));
    if (!strcmp(_clname, "Ui::frmminorstrata"))
        return static_cast< Ui::frmminorstrata*>(const_cast< FrmMinorStrata*>(this));
    return PreviewTab::qt_metacast(_clname);
}

int FrmMinorStrata::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreviewTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createRecord(); break;
        case 1: editRecord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: previewRow((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: blockCustomDateCtrls(); break;
        case 4: unblockCustomDateCtrls(); break;
        case 5: setActiveReason((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: disableReasonCombo(); break;
        case 7: onItemSelection(); break;
        case 8: onShowFrameDetails(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
