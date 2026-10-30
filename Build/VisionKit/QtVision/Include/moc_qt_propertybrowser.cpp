/****************************************************************************
** Meta object code from reading C++ file 'qt_propertybrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../VisionKit/QtVision/Include/qt_propertybrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_propertybrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__AbsPropertyManager_t {
    QByteArrayData data[10];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__AbsPropertyManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__AbsPropertyManager_t qt_meta_stringdata_VSN__QtVision__AbsPropertyManager = {
    {
QT_MOC_LITERAL(0, 0, 33), // "VSN::QtVision::AbsPropertyMan..."
QT_MOC_LITERAL(1, 34, 16), // "propertyInserted"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 9), // "Property*"
QT_MOC_LITERAL(4, 62, 8), // "property"
QT_MOC_LITERAL(5, 71, 6), // "parent"
QT_MOC_LITERAL(6, 78, 5), // "after"
QT_MOC_LITERAL(7, 84, 15), // "propertyChanged"
QT_MOC_LITERAL(8, 100, 15), // "propertyRemoved"
QT_MOC_LITERAL(9, 116, 17) // "propertyDestroyed"

    },
    "VSN::QtVision::AbsPropertyManager\0"
    "propertyInserted\0\0Property*\0property\0"
    "parent\0after\0propertyChanged\0"
    "propertyRemoved\0propertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__AbsPropertyManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       7,    1,   41,    2, 0x06 /* Public */,
       8,    2,   44,    2, 0x06 /* Public */,
       9,    1,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void VSN::QtVision::AbsPropertyManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AbsPropertyManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->propertyInserted((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< Property*(*)>(_a[2])),(*reinterpret_cast< Property*(*)>(_a[3]))); break;
        case 1: _t->propertyChanged((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        case 2: _t->propertyRemoved((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< Property*(*)>(_a[2]))); break;
        case 3: _t->propertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AbsPropertyManager::*)(Property * , Property * , Property * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbsPropertyManager::propertyInserted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AbsPropertyManager::*)(Property * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbsPropertyManager::propertyChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AbsPropertyManager::*)(Property * , Property * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbsPropertyManager::propertyRemoved)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AbsPropertyManager::*)(Property * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbsPropertyManager::propertyDestroyed)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::AbsPropertyManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__AbsPropertyManager.data,
    qt_meta_data_VSN__QtVision__AbsPropertyManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::AbsPropertyManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::AbsPropertyManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__AbsPropertyManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VSN::QtVision::AbsPropertyManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::AbsPropertyManager::propertyInserted(Property * _t1, Property * _t2, Property * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::AbsPropertyManager::propertyChanged(Property * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::AbsPropertyManager::propertyRemoved(Property * _t1, Property * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VSN::QtVision::AbsPropertyManager::propertyDestroyed(Property * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_VSN__QtVision__AbsEditorFactoryBase_t {
    QByteArrayData data[4];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__AbsEditorFactoryBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__AbsEditorFactoryBase_t qt_meta_stringdata_VSN__QtVision__AbsEditorFactoryBase = {
    {
QT_MOC_LITERAL(0, 0, 35), // "VSN::QtVision::AbsEditorFacto..."
QT_MOC_LITERAL(1, 36, 16), // "managerDestroyed"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 7) // "manager"

    },
    "VSN::QtVision::AbsEditorFactoryBase\0"
    "managerDestroyed\0\0manager"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__AbsEditorFactoryBase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar,    3,

       0        // eod
};

void VSN::QtVision::AbsEditorFactoryBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AbsEditorFactoryBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->managerDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::AbsEditorFactoryBase::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__AbsEditorFactoryBase.data,
    qt_meta_data_VSN__QtVision__AbsEditorFactoryBase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::AbsEditorFactoryBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::AbsEditorFactoryBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__AbsEditorFactoryBase.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VSN::QtVision::AbsEditorFactoryBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__AbsPropBrowser_t {
    QByteArrayData data[14];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__AbsPropBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__AbsPropBrowser_t qt_meta_stringdata_VSN__QtVision__AbsPropBrowser = {
    {
QT_MOC_LITERAL(0, 0, 29), // "VSN::QtVision::AbsPropBrowser"
QT_MOC_LITERAL(1, 30, 18), // "currentItemChanged"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 12), // "BrowserItem*"
QT_MOC_LITERAL(4, 63, 11), // "addProperty"
QT_MOC_LITERAL(5, 75, 9), // "Property*"
QT_MOC_LITERAL(6, 85, 8), // "property"
QT_MOC_LITERAL(7, 94, 14), // "insertProperty"
QT_MOC_LITERAL(8, 109, 13), // "afterProperty"
QT_MOC_LITERAL(9, 123, 14), // "removeProperty"
QT_MOC_LITERAL(10, 138, 20), // "slotPropertyInserted"
QT_MOC_LITERAL(11, 159, 19), // "slotPropertyRemoved"
QT_MOC_LITERAL(12, 179, 21), // "slotPropertyDestroyed"
QT_MOC_LITERAL(13, 201, 23) // "slotPropertyDataChanged"

    },
    "VSN::QtVision::AbsPropBrowser\0"
    "currentItemChanged\0\0BrowserItem*\0"
    "addProperty\0Property*\0property\0"
    "insertProperty\0afterProperty\0"
    "removeProperty\0slotPropertyInserted\0"
    "slotPropertyRemoved\0slotPropertyDestroyed\0"
    "slotPropertyDataChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__AbsPropBrowser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   57,    2, 0x0a /* Public */,
       7,    2,   60,    2, 0x0a /* Public */,
       9,    1,   65,    2, 0x0a /* Public */,
      10,    3,   68,    2, 0x08 /* Private */,
      11,    2,   75,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      13,    1,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    0x80000000 | 3, 0x80000000 | 5,    6,
    0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 5,    6,    8,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void VSN::QtVision::AbsPropBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AbsPropBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentItemChanged((*reinterpret_cast< BrowserItem*(*)>(_a[1]))); break;
        case 1: { BrowserItem* _r = _t->addProperty((*reinterpret_cast< Property*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< BrowserItem**>(_a[0]) = std::move(_r); }  break;
        case 2: { BrowserItem* _r = _t->insertProperty((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< Property*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< BrowserItem**>(_a[0]) = std::move(_r); }  break;
        case 3: _t->removeProperty((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        case 4: _t->slotPropertyInserted((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< Property*(*)>(_a[2])),(*reinterpret_cast< Property*(*)>(_a[3]))); break;
        case 5: _t->slotPropertyRemoved((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< Property*(*)>(_a[2]))); break;
        case 6: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        case 7: _t->slotPropertyDataChanged((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AbsPropBrowser::*)(BrowserItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbsPropBrowser::currentItemChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::AbsPropBrowser::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__AbsPropBrowser.data,
    qt_meta_data_VSN__QtVision__AbsPropBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::AbsPropBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::AbsPropBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__AbsPropBrowser.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VSN::QtVision::AbsPropBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::AbsPropBrowser::currentItemChanged(BrowserItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
