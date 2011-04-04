/****************************************************************************
** Meta object code from reading C++ file 'frameview.h'
**
** Created: Mon 4. Apr 15:57:45 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frameview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frameview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomAction[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   43,   13,   13, 0x0a,
      73,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CustomAction[] = {
    "CustomAction\0\0index\0triggered(QModelIndex)\0"
    "curIdx\0setCurIdx(QModelIndex)\0"
    "emitCurIdx()\0"
};

const QMetaObject CustomAction::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_CustomAction,
      qt_meta_data_CustomAction, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomAction))
        return static_cast<void*>(const_cast< CustomAction*>(this));
    return QAction::qt_metacast(_clname);
}

int CustomAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: triggered((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: setCurIdx((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: emitCurIdx(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CustomAction::triggered(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ComboBoxItem[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ComboBoxItem[] = {
    "ComboBoxItem\0\0changeItem(int)\0"
};

const QMetaObject ComboBoxItem::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_ComboBoxItem,
      qt_meta_data_ComboBoxItem, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ComboBoxItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ComboBoxItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ComboBoxItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ComboBoxItem))
        return static_cast<void*>(const_cast< ComboBoxItem*>(this));
    return QComboBox::qt_metacast(_clname);
}

int ComboBoxItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_TreeItemDelegate[] = {

 // content:
       4,       // revision
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

static const char qt_meta_stringdata_TreeItemDelegate[] = {
    "TreeItemDelegate\0"
};

const QMetaObject TreeItemDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_TreeItemDelegate,
      qt_meta_data_TreeItemDelegate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TreeItemDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TreeItemDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TreeItemDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeItemDelegate))
        return static_cast<void*>(const_cast< TreeItemDelegate*>(this));
    return QStyledItemDelegate::qt_metacast(_clname);
}

int TreeItemDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FrameView[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      35,   25,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   78,   10,   10, 0x0a,
     142,  108,  104,   10, 0x08,
     216,  209,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrameView[] = {
    "FrameView\0\0DragStarted()\0idx,level\0"
    "PromptReason(QModelIndex,TreeModel::Level)\0"
    "index\0expand(QModelIndex)\0int\0"
    "indexTo,strItems,strParents,level\0"
    "showFrmChangeReasons(QModelIndex,QString,QString,TreeModel::Level)\0"
    "parent\0insertNewItem(QModelIndex)\0"
};

const QMetaObject FrameView::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_FrameView,
      qt_meta_data_FrameView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrameView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrameView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrameView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrameView))
        return static_cast<void*>(const_cast< FrameView*>(this));
    return QTreeView::qt_metacast(_clname);
}

int FrameView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: DragStarted(); break;
        case 1: PromptReason((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const TreeModel::Level(*)>(_a[2]))); break;
        case 2: expand((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: { int _r = showFrmChangeReasons((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const TreeModel::Level(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: insertNewItem((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FrameView::DragStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FrameView::PromptReason(const QModelIndex & _t1, const TreeModel::Level _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_NullRelationalDelegate[] = {

 // content:
       4,       // revision
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
QT_END_MOC_NAMESPACE
