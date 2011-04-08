/****************************************************************************
** Meta object code from reading C++ file 'generictab.h'
**
** Created: Fri 8. Apr 11:46:57 2011
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
static const uint qt_meta_data_NullRelationalDelegate[] = {

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

static const char qt_meta_stringdata_NullRelationalDelegate[] = {
    "NullRelationalDelegate\0"
};

const QMetaObject NullRelationalDelegate::staticMetaObject = {
    { &QSqlRelationalDelegate::staticMetaObject, qt_meta_stringdata_NullRelationalDelegate,
      qt_meta_data_NullRelationalDelegate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NullRelationalDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NullRelationalDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NullRelationalDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NullRelationalDelegate))
        return static_cast<void*>(const_cast< NullRelationalDelegate*>(this));
    return QSqlRelationalDelegate::qt_metacast(_clname);
}

int NullRelationalDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlRelationalDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_GenericTab[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   12,   11,   11, 0x05,
      72,   63,   11,   11, 0x05,
     108,   98,   11,   11, 0x05,
     127,   11,   11,   11, 0x05,
     171,  146,   11,   11, 0x05,
     248,  244,   11,   11, 0x05,
     284,  268,   11,   11, 0x05,
     308,  244,   11,   11, 0x25,

 // slots: signature, parameters, type, tag, flags
     327,  244,   11,   11, 0x0a,
     359,  347,   11,   11, 0x0a,
     384,   11,   11,   11, 0x08,
     393,   11,   11,   11, 0x08,
     405,   12,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GenericTab[] = {
    "GenericTab\0\0bLock,lWidgets\0"
    "lockControls(bool,QList<QWidget*>&)\0"
    "str,data\0forward(QString,QVariant)\0"
    "bNext,idx\0navigate(bool,int)\0"
    "hideFrameDetails()\0mode,persistence,frameId\0"
    "showFrameDetails(FrmFrameDetails::Mode,FrmFrameDetails::Persistence,in"
    "t)\0"
    "str\0showStatus(QString)\0str,bShowMsgBox\0"
    "showError(QString,bool)\0showError(QString)\0"
    "fillHeader(QString)\0str,varData\0"
    "getPar(QString,QVariant)\0goBack()\0"
    "goForward()\0onLockControls(bool,QList<QWidget*>&)\0"
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
        case 0: lockControls((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QList<QWidget*>(*)>(_a[2]))); break;
        case 1: forward((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 2: navigate((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: hideFrameDetails(); break;
        case 4: showFrameDetails((*reinterpret_cast< const FrmFrameDetails::Mode(*)>(_a[1])),(*reinterpret_cast< const FrmFrameDetails::Persistence(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 5: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 7: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: fillHeader((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: getPar((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 10: goBack(); break;
        case 11: goForward(); break;
        case 12: onLockControls((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QList<QWidget*>(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void GenericTab::lockControls(bool _t1, QList<QWidget*> & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GenericTab::forward(const QString _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GenericTab::navigate(const bool _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GenericTab::hideFrameDetails()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void GenericTab::showFrameDetails(const FrmFrameDetails::Mode _t1, const FrmFrameDetails::Persistence _t2, const int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GenericTab::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GenericTab::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
