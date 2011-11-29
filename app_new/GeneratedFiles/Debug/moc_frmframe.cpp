/****************************************************************************
** Meta object code from reading C++ file 'frmframe.h'
**
** Created: Tue 29. Nov 10:23:55 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmFrame[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   10,    9,    9, 0x05,
      45,   35,    9,    9, 0x05,
      70,   65,    9,    9, 0x05,
     115,  108,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     146,    9,    9,    9, 0x0a,
     169,    9,    9,    9, 0x0a,
     194,    9,    9,    9, 0x08,
     209,    9,    9,    9, 0x08,
     230,    9,    9,    9, 0x08,
     251,    9,    9,    9, 0x08,
     286,  275,    9,    9, 0x08,
     310,    9,    9,    9, 0x08,
     331,  325,    9,    9, 0x08,
     355,    9,    9,    9, 0x08,
     394,  373,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmFrame[] = {
    "FrmFrame\0\0bLogBook\0isLogBook(bool)\0"
    "index,bOk\0submitted(int,bool)\0mode\0"
    "setFrmSamplingMode(FrmSampling::MODE)\0"
    "bApply\0applyChanges2FrmSampling(bool)\0"
    "blockCustomDateCtrls()\0unblockCustomDateCtrls()\0"
    "editFinished()\0onHideFrameDetails()\0"
    "onShowFrameDetails()\0adjustFrmSamplingMode()\0"
    "bSubmitted\0onHideFrmSampling(bool)\0"
    "createRecord()\0index\0previewRow(QModelIndex)\0"
    "onItemSelection()\0bFinished,bDiscarded\0"
    "onEditLeave(bool,bool)\0"
};

const QMetaObject FrmFrame::staticMetaObject = {
    { &PreviewTab::staticMetaObject, qt_meta_stringdata_FrmFrame,
      qt_meta_data_FrmFrame, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmFrame))
        return static_cast<void*>(const_cast< FrmFrame*>(this));
    if (!strcmp(_clname, "Ui::frmframe"))
        return static_cast< Ui::frmframe*>(const_cast< FrmFrame*>(this));
    return PreviewTab::qt_metacast(_clname);
}

int FrmFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreviewTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: isLogBook((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: submitted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: setFrmSamplingMode((*reinterpret_cast< const FrmSampling::MODE(*)>(_a[1]))); break;
        case 3: applyChanges2FrmSampling((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 4: blockCustomDateCtrls(); break;
        case 5: unblockCustomDateCtrls(); break;
        case 6: editFinished(); break;
        case 7: onHideFrameDetails(); break;
        case 8: onShowFrameDetails(); break;
        case 9: adjustFrmSamplingMode(); break;
        case 10: onHideFrmSampling((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: createRecord(); break;
        case 12: previewRow((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 13: onItemSelection(); break;
        case 14: onEditLeave((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void FrmFrame::isLogBook(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FrmFrame::submitted(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FrmFrame::setFrmSamplingMode(const FrmSampling::MODE _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FrmFrame::applyChanges2FrmSampling(const bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
