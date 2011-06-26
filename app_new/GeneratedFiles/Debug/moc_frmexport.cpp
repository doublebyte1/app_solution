/****************************************************************************
** Meta object code from reading C++ file 'frmexport.h'
**
** Created: Sun 26. Jun 18:36:41 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmexport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmexport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmExport[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      25,   21,   10,   10, 0x05,
      61,   45,   10,   10, 0x05,
      85,   21,   10,   10, 0x25,

 // slots: signature, parameters, type, tag, flags
     104,   10,   10,   10, 0x08,
     109,   10,   10,   10, 0x08,
     123,  118,   10,   10, 0x08,
     149,   10,   10,   10, 0x08,
     159,   10,   10,   10, 0x08,
     178,  172,   10,   10, 0x08,
     200,   10,  195,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmExport[] = {
    "FrmExport\0\0hideFrm()\0str\0showStatus(QString)\0"
    "str,bShowMsgBox\0showError(QString,bool)\0"
    "showError(QString)\0Ok()\0Cancel()\0item\0"
    "preview(QListWidgetItem*)\0preview()\0"
    "chooseFile()\0bHide\0hideAppend(bool)\0"
    "bool\0readTableNames()\0"
};

const QMetaObject FrmExport::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrmExport,
      qt_meta_data_FrmExport, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmExport::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmExport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmExport::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmExport))
        return static_cast<void*>(const_cast< FrmExport*>(this));
    if (!strcmp(_clname, "Ui::frmTables"))
        return static_cast< Ui::frmTables*>(const_cast< FrmExport*>(this));
    return QWidget::qt_metacast(_clname);
}

int FrmExport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hideFrm(); break;
        case 1: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 3: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: Ok(); break;
        case 5: Cancel(); break;
        case 6: preview((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: preview(); break;
        case 8: chooseFile(); break;
        case 9: hideAppend((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: { bool _r = readTableNames();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void FrmExport::hideFrm()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FrmExport::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FrmExport::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
