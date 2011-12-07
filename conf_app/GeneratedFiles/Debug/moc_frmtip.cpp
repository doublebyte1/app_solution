/****************************************************************************
** Meta object code from reading C++ file 'frmtip.h'
**
** Created: Wed 7. Dec 15:38:36 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmtip.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmtip.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmTip[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FrmTip[] = {
    "FrmTip\0\0bShow\0showStartupMsg(bool)\0"
};

const QMetaObject FrmTip::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FrmTip,
      qt_meta_data_FrmTip, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmTip::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmTip::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmTip::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmTip))
        return static_cast<void*>(const_cast< FrmTip*>(this));
    if (!strcmp(_clname, "Ui::frmtip"))
        return static_cast< Ui::frmtip*>(const_cast< FrmTip*>(this));
    return QDialog::qt_metacast(_clname);
}

int FrmTip::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showStartupMsg((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void FrmTip::showStartupMsg(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
