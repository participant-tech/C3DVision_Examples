/****************************************************************************
** Meta object code from reading C++ file 'qt_treepropertybrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../VisionKit/QtVision/Include/qt_treepropertybrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_treepropertybrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__TreePropBrowser_t {
    QByteArrayData data[24];
    char stringdata0[356];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__TreePropBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__TreePropBrowser_t qt_meta_stringdata_VSN__QtVision__TreePropBrowser = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::TreePropBrowser"
QT_MOC_LITERAL(1, 31, 9), // "collapsed"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 12), // "BrowserItem*"
QT_MOC_LITERAL(4, 55, 4), // "item"
QT_MOC_LITERAL(5, 60, 8), // "expanded"
QT_MOC_LITERAL(6, 69, 13), // "slotCollapsed"
QT_MOC_LITERAL(7, 83, 11), // "QModelIndex"
QT_MOC_LITERAL(8, 95, 12), // "slotExpanded"
QT_MOC_LITERAL(9, 108, 29), // "slotCurrentBrowserItemChanged"
QT_MOC_LITERAL(10, 138, 26), // "slotCurrentTreeItemChanged"
QT_MOC_LITERAL(11, 165, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(12, 182, 11), // "indentation"
QT_MOC_LITERAL(13, 194, 15), // "rootIsDecorated"
QT_MOC_LITERAL(14, 210, 20), // "alternatingRowColors"
QT_MOC_LITERAL(15, 231, 13), // "headerVisible"
QT_MOC_LITERAL(16, 245, 10), // "resizeMode"
QT_MOC_LITERAL(17, 256, 10), // "ResizeMode"
QT_MOC_LITERAL(18, 267, 16), // "splitterPosition"
QT_MOC_LITERAL(19, 284, 28), // "propertiesWithoutValueMarked"
QT_MOC_LITERAL(20, 313, 11), // "Interactive"
QT_MOC_LITERAL(21, 325, 7), // "Stretch"
QT_MOC_LITERAL(22, 333, 5), // "Fixed"
QT_MOC_LITERAL(23, 339, 16) // "ResizeToContents"

    },
    "VSN::QtVision::TreePropBrowser\0collapsed\0"
    "\0BrowserItem*\0item\0expanded\0slotCollapsed\0"
    "QModelIndex\0slotExpanded\0"
    "slotCurrentBrowserItemChanged\0"
    "slotCurrentTreeItemChanged\0QTreeWidgetItem*\0"
    "indentation\0rootIsDecorated\0"
    "alternatingRowColors\0headerVisible\0"
    "resizeMode\0ResizeMode\0splitterPosition\0"
    "propertiesWithoutValueMarked\0Interactive\0"
    "Stretch\0Fixed\0ResizeToContents"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__TreePropBrowser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       7,   64, // properties
       1,   85, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   50,    2, 0x08 /* Private */,
       8,    1,   53,    2, 0x08 /* Private */,
       9,    1,   56,    2, 0x08 /* Private */,
      10,    2,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11,    2,    2,

 // properties: name, type, flags
      12, QMetaType::Int, 0x00095103,
      13, QMetaType::Bool, 0x00095103,
      14, QMetaType::Bool, 0x00095103,
      15, QMetaType::Bool, 0x00095103,
      16, 0x80000000 | 17, 0x0009510b,
      18, QMetaType::Int, 0x00095103,
      19, QMetaType::Bool, 0x00095103,

 // enums: name, alias, flags, count, data
      17,   17, 0x0,    4,   90,

 // enum data: key, value
      20, uint(VSN::QtVision::TreePropBrowser::Interactive),
      21, uint(VSN::QtVision::TreePropBrowser::Stretch),
      22, uint(VSN::QtVision::TreePropBrowser::Fixed),
      23, uint(VSN::QtVision::TreePropBrowser::ResizeToContents),

       0        // eod
};

void VSN::QtVision::TreePropBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TreePropBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->collapsed((*reinterpret_cast< BrowserItem*(*)>(_a[1]))); break;
        case 1: _t->expanded((*reinterpret_cast< BrowserItem*(*)>(_a[1]))); break;
        case 2: _t->slotCollapsed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->slotExpanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->slotCurrentBrowserItemChanged((*reinterpret_cast< BrowserItem*(*)>(_a[1]))); break;
        case 5: _t->slotCurrentTreeItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TreePropBrowser::*)(BrowserItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TreePropBrowser::collapsed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TreePropBrowser::*)(BrowserItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TreePropBrowser::expanded)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TreePropBrowser *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->indentation(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->rootIsDecorated(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->alternatingRowColors(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isHeaderVisible(); break;
        case 4: *reinterpret_cast< ResizeMode*>(_v) = _t->resizeMode(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->splitterPosition(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->propertiesWithoutValueMarked(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TreePropBrowser *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIndentation(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setRootIsDecorated(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setAlternatingRowColors(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setHeaderVisible(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setResizeMode(*reinterpret_cast< ResizeMode*>(_v)); break;
        case 5: _t->setSplitterPosition(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setPropertiesWithoutValueMarked(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::TreePropBrowser::staticMetaObject = { {
    &AbsPropBrowser::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__TreePropBrowser.data,
    qt_meta_data_VSN__QtVision__TreePropBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::TreePropBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::TreePropBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__TreePropBrowser.stringdata0))
        return static_cast<void*>(this);
    return AbsPropBrowser::qt_metacast(_clname);
}

int VSN::QtVision::TreePropBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void VSN::QtVision::TreePropBrowser::collapsed(BrowserItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::TreePropBrowser::expanded(BrowserItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
