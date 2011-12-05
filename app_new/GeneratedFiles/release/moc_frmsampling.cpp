/****************************************************************************
** Meta object code from reading C++ file 'frmsampling.h'
**
** Created: Mon 5. Dec 08:43:25 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmsampling.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmsampling.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomModel[] = {

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

static const char qt_meta_stringdata_CustomModel[] = {
    "CustomModel\0"
};

const QMetaObject CustomModel::staticMetaObject = {
    { &QSqlRelationalTableModel::staticMetaObject, qt_meta_stringdata_CustomModel,
      qt_meta_data_CustomModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomModel))
        return static_cast<void*>(const_cast< CustomModel*>(this));
    return QSqlRelationalTableModel::qt_metacast(_clname);
}

int CustomModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlRelationalTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FrmSampling[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   44,   12,   12, 0x0a,
      77,   12,   12,   12, 0x08,
      89,   12,   84,   12, 0x08,
      96,   12,   12,   12, 0x08,
     108,   12,   12,   12, 0x08,
     127,  120,   12,   12, 0x08,
     160,   12,   84,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmSampling[] = {
    "FrmSampling\0\0AppliedChanges2SamplingFrame()\0"
    "aMode\0setMode(FrmSampling::MODE)\0"
    "back()\0bool\0next()\0insertRow()\0"
    "removeRow()\0bApply\0onApplyChanges2FrmSampling(bool)\0"
    "IReallyApply()\0"
};

const QMetaObject FrmSampling::staticMetaObject = {
    { &GenericTab::staticMetaObject, qt_meta_stringdata_FrmSampling,
      qt_meta_data_FrmSampling, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmSampling::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmSampling::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmSampling::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmSampling))
        return static_cast<void*>(const_cast< FrmSampling*>(this));
    if (!strcmp(_clname, "Ui::FrmSampling"))
        return static_cast< Ui::FrmSampling*>(const_cast< FrmSampling*>(this));
    return GenericTab::qt_metacast(_clname);
}

int FrmSampling::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GenericTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: AppliedChanges2SamplingFrame(); break;
        case 1: setMode((*reinterpret_cast< const FrmSampling::MODE(*)>(_a[1]))); break;
        case 2: back(); break;
        case 3: { bool _r = next();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: insertRow(); break;
        case 5: removeRow(); break;
        case 6: onApplyChanges2FrmSampling((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 7: { bool _r = IReallyApply();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void FrmSampling::AppliedChanges2SamplingFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
