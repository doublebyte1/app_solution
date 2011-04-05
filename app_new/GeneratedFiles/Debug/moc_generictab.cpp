/****************************************************************************
** Meta object code from reading C++ file 'generictab.h'
**
** Created: Tue 5. Apr 15:06:27 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../generictab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'generictab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GenericTab[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      32,   22,   11,   11, 0x05,
      51,   11,   11,   11, 0x05,
      95,   70,   11,   11, 0x05,
     172,  168,   11,   11, 0x05,
     208,  192,   11,   11, 0x05,
     232,  168,   11,   11, 0x25,

 // slots: signature, parameters, type, tag, flags
     251,   11,   11,   11, 0x08,
     260,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GenericTab[] = {
    "GenericTab\0\0forward()\0bNext,idx\0"
    "navigate(bool,int)\0hideFrameDetails()\0"
    "mode,persistence,frameId\0"
    "showFrameDetails(FrmFrameDetails::Mode,FrmFrameDetails::Persistence,in"
    "t)\0"
    "str\0showStatus(QString)\0str,bShowMsgBox\0"
    "showError(QString,bool)\0showError(QString)\0"
    "goBack()\0goForward()\0"
};

const QMetaObject GenericTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GenericTab,
      qt_meta_data_GenericTab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GenericTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GenericTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GenericTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GenericTab))
        return static_cast<void*>(const_cast< GenericTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int GenericTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: forward(); break;
        case 1: navigate((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: hideFrameDetails(); break;
        case 3: showFrameDetails((*reinterpret_cast< const FrmFrameDetails::Mode(*)>(_a[1])),(*reinterpret_cast< const FrmFrameDetails::Persistence(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 4: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 6: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: goBack(); break;
        case 8: goForward(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GenericTab::forward()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GenericTab::navigate(const bool _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GenericTab::hideFrameDetails()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GenericTab::showFrameDetails(const FrmFrameDetails::Mode _t1, const FrmFrameDetails::Persistence _t2, const int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GenericTab::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GenericTab::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
