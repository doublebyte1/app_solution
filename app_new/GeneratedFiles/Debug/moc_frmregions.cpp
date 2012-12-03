/****************************************************************************
** Meta object code from reading C++ file 'frmregions.h'
**
** Created: Mon 3. Dec 12:45:27 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmregions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmregions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmRegions[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      20,   11,   11,   11, 0x08,
      29,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmRegions[] = {
    "FrmRegions\0\0Apply()\0reload()\0treeEdited()\0"
};

const QMetaObject FrmRegions::staticMetaObject = {
    { &SecondaryFrm::staticMetaObject, qt_meta_stringdata_FrmRegions,
      qt_meta_data_FrmRegions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmRegions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmRegions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmRegions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmRegions))
        return static_cast<void*>(const_cast< FrmRegions*>(this));
    if (!strcmp(_clname, "Ui::frmRegions"))
        return static_cast< Ui::frmRegions*>(const_cast< FrmRegions*>(this));
    return SecondaryFrm::qt_metacast(_clname);
}

int FrmRegions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SecondaryFrm::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Apply(); break;
        case 1: reload(); break;
        case 2: treeEdited(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
