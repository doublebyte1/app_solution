/****************************************************************************
** Meta object code from reading C++ file 'frmimport.h'
**
** Created: Tue 28. Jun 09:49:43 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmimport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmimport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmImport[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      21,   10,   10,   10, 0x05,
      42,   38,   10,   10, 0x05,
      78,   62,   10,   10, 0x05,
     102,   38,   10,   10, 0x25,

 // slots: signature, parameters, type, tag, flags
     126,  121,   10,   10, 0x08,
     158,   10,  153,   10, 0x08,
     183,  175,  153,   10, 0x08,
     226,  220,   10,   10, 0x08,
     243,   10,   10,   10, 0x08,
     248,   10,   10,   10, 0x08,
     257,  121,   10,   10, 0x08,
     283,   10,   10,   10, 0x08,
     293,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmImport[] = {
    "FrmImport\0\0hideFrm()\0rollbackImport()\0"
    "str\0showStatus(QString)\0str,bShowMsgBox\0"
    "showError(QString,bool)\0showError(QString)\0"
    "item\0loadItem(QListWidgetItem*)\0bool\0"
    "readTableNames()\0aFormat\0"
    "readTableNames(AbstractTableFormat*)\0"
    "bHide\0hideAppend(bool)\0Ok()\0Cancel()\0"
    "preview(QListWidgetItem*)\0preview()\0"
    "chooseFile()\0"
};

const QMetaObject FrmImport::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrmImport,
      qt_meta_data_FrmImport, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmImport::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmImport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmImport::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmImport))
        return static_cast<void*>(const_cast< FrmImport*>(this));
    if (!strcmp(_clname, "Ui::frmTables"))
        return static_cast< Ui::frmTables*>(const_cast< FrmImport*>(this));
    return QWidget::qt_metacast(_clname);
}

int FrmImport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hideFrm(); break;
        case 1: rollbackImport(); break;
        case 2: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 4: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: loadItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: { bool _r = readTableNames();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = readTableNames((*reinterpret_cast< AbstractTableFormat*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: hideAppend((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: Ok(); break;
        case 10: Cancel(); break;
        case 11: preview((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 12: preview(); break;
        case 13: chooseFile(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void FrmImport::hideFrm()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FrmImport::rollbackImport()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void FrmImport::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FrmImport::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
