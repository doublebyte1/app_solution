/****************************************************************************
** Meta object code from reading C++ file 'frmimportregions.h'
**
** Created: Fri 17. Aug 22:14:57 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmimportregions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmimportregions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmImportRegions[] = {

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
      18,   17,   17,   17, 0x08,
      26,   17,   17,   17, 0x08,
      35,   17,   17,   17, 0x08,
      60,   51,   17,   17, 0x08,
      83,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmImportRegions[] = {
    "FrmImportRegions\0\0Apply()\0Cancel()\0"
    "adjustButtons()\0strTable\0"
    "refreshFields(QString)\0addItems2List()\0"
};

const QMetaObject FrmImportRegions::staticMetaObject = {
    { &SecondaryFrm::staticMetaObject, qt_meta_stringdata_FrmImportRegions,
      qt_meta_data_FrmImportRegions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmImportRegions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmImportRegions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmImportRegions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmImportRegions))
        return static_cast<void*>(const_cast< FrmImportRegions*>(this));
    if (!strcmp(_clname, "Ui::frmImportRegions"))
        return static_cast< Ui::frmImportRegions*>(const_cast< FrmImportRegions*>(this));
    return SecondaryFrm::qt_metacast(_clname);
}

int FrmImportRegions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SecondaryFrm::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Apply(); break;
        case 1: Cancel(); break;
        case 2: adjustButtons(); break;
        case 3: refreshFields((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: addItems2List(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
