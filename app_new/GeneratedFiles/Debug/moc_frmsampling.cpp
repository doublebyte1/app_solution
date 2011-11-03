/****************************************************************************
** Meta object code from reading C++ file 'frmsampling.h'
**
** Created: Thu 3. Nov 16:25:18 2011
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
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   13,   12,   12, 0x05,
      53,   49,   12,   12, 0x05,
      89,   73,   12,   12, 0x05,
     113,   49,   12,   12, 0x25,

 // slots: signature, parameters, type, tag, flags
     138,  132,   12,   12, 0x0a,
     172,  165,   12,   12, 0x0a,
     205,   12,   12,   12, 0x08,
     212,   12,   12,   12, 0x08,
     226,  220,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmSampling[] = {
    "FrmSampling\0\0bNotSubmitted\0"
    "hideFrmSampling(bool)\0str\0showStatus(QString)\0"
    "str,bShowMsgBox\0showError(QString,bool)\0"
    "showError(QString)\0aMode\0"
    "setMode(FrmSampling::MODE)\0bApply\0"
    "onApplyChanges2FrmSampling(bool)\0"
    "back()\0apply()\0index\0initRecords(int)\0"
};

const QMetaObject FrmSampling::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrmSampling,
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
    return QWidget::qt_metacast(_clname);
}

int FrmSampling::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hideFrmSampling((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 3: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: setMode((*reinterpret_cast< const FrmSampling::MODE(*)>(_a[1]))); break;
        case 5: onApplyChanges2FrmSampling((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 6: back(); break;
        case 7: apply(); break;
        case 8: initRecords((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void FrmSampling::hideFrmSampling(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FrmSampling::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FrmSampling::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
