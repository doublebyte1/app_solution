/****************************************************************************
** Meta object code from reading C++ file 'frmreports.h'
**
** Created: Tue 29. Nov 10:23:49 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmreports.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmreports.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmReports[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      31,   26,   11,   11, 0x08,
      61,   26,   11,   11, 0x08,
     100,   88,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmReports[] = {
    "FrmReports\0\0browseFiles()\0item\0"
    "previewItem(QListWidgetItem*)\0"
    "loadItem(QListWidgetItem*)\0strFilename\0"
    "loadItem(QString)\0"
};

const QMetaObject FrmReports::staticMetaObject = {
    { &SecondaryFrm::staticMetaObject, qt_meta_stringdata_FrmReports,
      qt_meta_data_FrmReports, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmReports::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmReports::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmReports::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmReports))
        return static_cast<void*>(const_cast< FrmReports*>(this));
    if (!strcmp(_clname, "Ui::frmreports"))
        return static_cast< Ui::frmreports*>(const_cast< FrmReports*>(this));
    return SecondaryFrm::qt_metacast(_clname);
}

int FrmReports::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SecondaryFrm::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: browseFiles(); break;
        case 1: previewItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: loadItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: loadItem((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
