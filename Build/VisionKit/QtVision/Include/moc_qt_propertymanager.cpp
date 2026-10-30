/****************************************************************************
** Meta object code from reading C++ file 'qt_propertymanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../VisionKit/QtVision/Include/qt_propertymanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_propertymanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__GroupPropManager_t {
    QByteArrayData data[1];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__GroupPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__GroupPropManager_t qt_meta_stringdata_VSN__QtVision__GroupPropManager = {
    {
QT_MOC_LITERAL(0, 0, 31) // "VSN::QtVision::GroupPropManager"

    },
    "VSN::QtVision::GroupPropManager"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__GroupPropManager[] = {

 // content:
       8,       // revision
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

void VSN::QtVision::GroupPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::GroupPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__GroupPropManager.data,
    qt_meta_data_VSN__QtVision__GroupPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::GroupPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::GroupPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__GroupPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::GroupPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__IntPropManager_t {
    QByteArrayData data[16];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__IntPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__IntPropManager_t qt_meta_stringdata_VSN__QtVision__IntPropManager = {
    {
QT_MOC_LITERAL(0, 0, 29), // "VSN::QtVision::IntPropManager"
QT_MOC_LITERAL(1, 30, 12), // "valueChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 9), // "Property*"
QT_MOC_LITERAL(4, 54, 8), // "property"
QT_MOC_LITERAL(5, 63, 3), // "val"
QT_MOC_LITERAL(6, 67, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 80, 6), // "minVal"
QT_MOC_LITERAL(8, 87, 6), // "maxVal"
QT_MOC_LITERAL(9, 94, 17), // "singleStepChanged"
QT_MOC_LITERAL(10, 112, 4), // "step"
QT_MOC_LITERAL(11, 117, 8), // "setValue"
QT_MOC_LITERAL(12, 126, 10), // "setMinimum"
QT_MOC_LITERAL(13, 137, 10), // "setMaximum"
QT_MOC_LITERAL(14, 148, 8), // "setRange"
QT_MOC_LITERAL(15, 157, 13) // "setSingleStep"

    },
    "VSN::QtVision::IntPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "rangeChanged\0minVal\0maxVal\0singleStepChanged\0"
    "step\0setValue\0setMinimum\0setMaximum\0"
    "setRange\0setSingleStep"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__IntPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    3,   59,    2, 0x06 /* Public */,
       9,    2,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   71,    2, 0x0a /* Public */,
      12,    2,   76,    2, 0x0a /* Public */,
      13,    2,   81,    2, 0x0a /* Public */,
      14,    3,   86,    2, 0x0a /* Public */,
      15,    2,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,   10,

       0        // eod
};

void VSN::QtVision::IntPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->singleStepChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->setMinimum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->setMaximum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->setRange((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->setSingleStep((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IntPropManager::*)(Property * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IntPropManager::*)(Property * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntPropManager::rangeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IntPropManager::*)(Property * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntPropManager::singleStepChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::IntPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__IntPropManager.data,
    qt_meta_data_VSN__QtVision__IntPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::IntPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::IntPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__IntPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::IntPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::IntPropManager::valueChanged(Property * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::IntPropManager::rangeChanged(Property * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::IntPropManager::singleStepChanged(Property * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_VSN__QtVision__BoolPropManager_t {
    QByteArrayData data[7];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__BoolPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__BoolPropManager_t qt_meta_stringdata_VSN__QtVision__BoolPropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::BoolPropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 8) // "setValue"

    },
    "VSN::QtVision::BoolPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__BoolPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,

       0        // eod
};

void VSN::QtVision::BoolPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BoolPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BoolPropManager::*)(Property * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BoolPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::BoolPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__BoolPropManager.data,
    qt_meta_data_VSN__QtVision__BoolPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::BoolPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::BoolPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__BoolPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::BoolPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::BoolPropManager::valueChanged(Property * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__DoublePropManager_t {
    QByteArrayData data[19];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__DoublePropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__DoublePropManager_t qt_meta_stringdata_VSN__QtVision__DoublePropManager = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::DoublePropManager"
QT_MOC_LITERAL(1, 33, 12), // "valueChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 9), // "Property*"
QT_MOC_LITERAL(4, 57, 8), // "property"
QT_MOC_LITERAL(5, 66, 3), // "val"
QT_MOC_LITERAL(6, 70, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 83, 6), // "minVal"
QT_MOC_LITERAL(8, 90, 6), // "maxVal"
QT_MOC_LITERAL(9, 97, 17), // "singleStepChanged"
QT_MOC_LITERAL(10, 115, 4), // "step"
QT_MOC_LITERAL(11, 120, 15), // "decimalsChanged"
QT_MOC_LITERAL(12, 136, 4), // "prec"
QT_MOC_LITERAL(13, 141, 8), // "setValue"
QT_MOC_LITERAL(14, 150, 10), // "setMinimum"
QT_MOC_LITERAL(15, 161, 10), // "setMaximum"
QT_MOC_LITERAL(16, 172, 8), // "setRange"
QT_MOC_LITERAL(17, 181, 13), // "setSingleStep"
QT_MOC_LITERAL(18, 195, 11) // "setDecimals"

    },
    "VSN::QtVision::DoublePropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "rangeChanged\0minVal\0maxVal\0singleStepChanged\0"
    "step\0decimalsChanged\0prec\0setValue\0"
    "setMinimum\0setMaximum\0setRange\0"
    "setSingleStep\0setDecimals"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__DoublePropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       6,    3,   69,    2, 0x06 /* Public */,
       9,    2,   76,    2, 0x06 /* Public */,
      11,    2,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    2,   86,    2, 0x0a /* Public */,
      14,    2,   91,    2, 0x0a /* Public */,
      15,    2,   96,    2, 0x0a /* Public */,
      16,    3,  101,    2, 0x0a /* Public */,
      17,    2,  108,    2, 0x0a /* Public */,
      18,    2,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double, QMetaType::Double,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,   10,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double, QMetaType::Double,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,   10,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,   12,

       0        // eod
};

void VSN::QtVision::DoublePropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoublePropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->singleStepChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->decimalsChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: _t->setMinimum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 6: _t->setMaximum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: _t->setRange((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 8: _t->setSingleStep((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: _t->setDecimals((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DoublePropManager::*)(Property * , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoublePropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DoublePropManager::*)(Property * , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoublePropManager::rangeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DoublePropManager::*)(Property * , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoublePropManager::singleStepChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DoublePropManager::*)(Property * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoublePropManager::decimalsChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::DoublePropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__DoublePropManager.data,
    qt_meta_data_VSN__QtVision__DoublePropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::DoublePropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::DoublePropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__DoublePropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::DoublePropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::DoublePropManager::valueChanged(Property * _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::DoublePropManager::rangeChanged(Property * _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::DoublePropManager::singleStepChanged(Property * _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VSN::QtVision::DoublePropManager::decimalsChanged(Property * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_VSN__QtVision__StringPropManager_t {
    QByteArrayData data[10];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__StringPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__StringPropManager_t qt_meta_stringdata_VSN__QtVision__StringPropManager = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::StringPropManager"
QT_MOC_LITERAL(1, 33, 12), // "valueChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 9), // "Property*"
QT_MOC_LITERAL(4, 57, 8), // "property"
QT_MOC_LITERAL(5, 66, 3), // "val"
QT_MOC_LITERAL(6, 70, 13), // "regExpChanged"
QT_MOC_LITERAL(7, 84, 6), // "regExp"
QT_MOC_LITERAL(8, 91, 8), // "setValue"
QT_MOC_LITERAL(9, 100, 9) // "setRegExp"

    },
    "VSN::QtVision::StringPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "regExpChanged\0regExp\0setValue\0setRegExp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__StringPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       6,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   44,    2, 0x0a /* Public */,
       9,    2,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRegularExpression,    4,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRegularExpression,    4,    7,

       0        // eod
};

void VSN::QtVision::StringPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StringPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->regExpChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRegularExpression(*)>(_a[2]))); break;
        case 2: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->setRegExp((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRegularExpression(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StringPropManager::*)(Property * , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StringPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StringPropManager::*)(Property * , const QRegularExpression & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StringPropManager::regExpChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::StringPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__StringPropManager.data,
    qt_meta_data_VSN__QtVision__StringPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::StringPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::StringPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__StringPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::StringPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::StringPropManager::valueChanged(Property * _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::StringPropManager::regExpChanged(Property * _t1, const QRegularExpression & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__DatePropManager_t {
    QByteArrayData data[13];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__DatePropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__DatePropManager_t qt_meta_stringdata_VSN__QtVision__DatePropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::DatePropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 81, 6), // "minVal"
QT_MOC_LITERAL(8, 88, 6), // "maxVal"
QT_MOC_LITERAL(9, 95, 8), // "setValue"
QT_MOC_LITERAL(10, 104, 10), // "setMinimum"
QT_MOC_LITERAL(11, 115, 10), // "setMaximum"
QT_MOC_LITERAL(12, 126, 8) // "setRange"

    },
    "VSN::QtVision::DatePropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "rangeChanged\0minVal\0maxVal\0setValue\0"
    "setMinimum\0setMaximum\0setRange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__DatePropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    3,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   56,    2, 0x0a /* Public */,
      10,    2,   61,    2, 0x0a /* Public */,
      11,    2,   66,    2, 0x0a /* Public */,
      12,    3,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDate,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDate, QMetaType::QDate,    4,    7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDate,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDate,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDate,    4,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDate, QMetaType::QDate,    4,    7,    8,

       0        // eod
};

void VSN::QtVision::DatePropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DatePropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2])),(*reinterpret_cast< const QDate(*)>(_a[3]))); break;
        case 2: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2]))); break;
        case 3: _t->setMinimum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2]))); break;
        case 4: _t->setMaximum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2]))); break;
        case 5: _t->setRange((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2])),(*reinterpret_cast< const QDate(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DatePropManager::*)(Property * , const QDate & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatePropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DatePropManager::*)(Property * , const QDate & , const QDate & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatePropManager::rangeChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::DatePropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__DatePropManager.data,
    qt_meta_data_VSN__QtVision__DatePropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::DatePropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::DatePropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__DatePropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::DatePropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void VSN::QtVision::DatePropManager::valueChanged(Property * _t1, const QDate & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::DatePropManager::rangeChanged(Property * _t1, const QDate & _t2, const QDate & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__TimePropManager_t {
    QByteArrayData data[7];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__TimePropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__TimePropManager_t qt_meta_stringdata_VSN__QtVision__TimePropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::TimePropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 8) // "setValue"

    },
    "VSN::QtVision::TimePropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__TimePropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QTime,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QTime,    4,    5,

       0        // eod
};

void VSN::QtVision::TimePropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimePropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QTime(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QTime(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TimePropManager::*)(Property * , const QTime & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimePropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::TimePropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__TimePropManager.data,
    qt_meta_data_VSN__QtVision__TimePropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::TimePropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::TimePropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__TimePropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::TimePropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::TimePropManager::valueChanged(Property * _t1, const QTime & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__DateTimePropManager_t {
    QByteArrayData data[7];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__DateTimePropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__DateTimePropManager_t qt_meta_stringdata_VSN__QtVision__DateTimePropManager = {
    {
QT_MOC_LITERAL(0, 0, 34), // "VSN::QtVision::DateTimePropMa..."
QT_MOC_LITERAL(1, 35, 12), // "valueChanged"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 9), // "Property*"
QT_MOC_LITERAL(4, 59, 8), // "property"
QT_MOC_LITERAL(5, 68, 3), // "val"
QT_MOC_LITERAL(6, 72, 8) // "setValue"

    },
    "VSN::QtVision::DateTimePropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__DateTimePropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDateTime,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDateTime,    4,    5,

       0        // eod
};

void VSN::QtVision::DateTimePropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DateTimePropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDateTime(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDateTime(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DateTimePropManager::*)(Property * , const QDateTime & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DateTimePropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::DateTimePropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__DateTimePropManager.data,
    qt_meta_data_VSN__QtVision__DateTimePropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::DateTimePropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::DateTimePropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__DateTimePropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::DateTimePropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::DateTimePropManager::valueChanged(Property * _t1, const QDateTime & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__KeySequencePropManager_t {
    QByteArrayData data[7];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__KeySequencePropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__KeySequencePropManager_t qt_meta_stringdata_VSN__QtVision__KeySequencePropManager = {
    {
QT_MOC_LITERAL(0, 0, 37), // "VSN::QtVision::KeySequencePro..."
QT_MOC_LITERAL(1, 38, 12), // "valueChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 9), // "Property*"
QT_MOC_LITERAL(4, 62, 8), // "property"
QT_MOC_LITERAL(5, 71, 3), // "val"
QT_MOC_LITERAL(6, 75, 8) // "setValue"

    },
    "VSN::QtVision::KeySequencePropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__KeySequencePropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QKeySequence,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QKeySequence,    4,    5,

       0        // eod
};

void VSN::QtVision::KeySequencePropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KeySequencePropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QKeySequence(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QKeySequence(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KeySequencePropManager::*)(Property * , const QKeySequence & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KeySequencePropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::KeySequencePropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__KeySequencePropManager.data,
    qt_meta_data_VSN__QtVision__KeySequencePropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::KeySequencePropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::KeySequencePropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__KeySequencePropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::KeySequencePropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::KeySequencePropManager::valueChanged(Property * _t1, const QKeySequence & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__CharPropManager_t {
    QByteArrayData data[7];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__CharPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__CharPropManager_t qt_meta_stringdata_VSN__QtVision__CharPropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::CharPropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 8) // "setValue"

    },
    "VSN::QtVision::CharPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__CharPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QChar,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QChar,    4,    5,

       0        // eod
};

void VSN::QtVision::CharPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CharPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QChar(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QChar(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CharPropManager::*)(Property * , const QChar & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CharPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::CharPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__CharPropManager.data,
    qt_meta_data_VSN__QtVision__CharPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::CharPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::CharPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__CharPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::CharPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::CharPropManager::valueChanged(Property * _t1, const QChar & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__LocalePropManager_t {
    QByteArrayData data[9];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__LocalePropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__LocalePropManager_t qt_meta_stringdata_VSN__QtVision__LocalePropManager = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::LocalePropManager"
QT_MOC_LITERAL(1, 33, 12), // "valueChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 9), // "Property*"
QT_MOC_LITERAL(4, 57, 8), // "property"
QT_MOC_LITERAL(5, 66, 3), // "val"
QT_MOC_LITERAL(6, 70, 8), // "setValue"
QT_MOC_LITERAL(7, 79, 15), // "slotEnumChanged"
QT_MOC_LITERAL(8, 95, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::LocalePropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue\0slotEnumChanged\0slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__LocalePropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   39,    2, 0x0a /* Public */,
       7,    2,   44,    2, 0x08 /* Private */,
       8,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QLocale,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QLocale,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::LocalePropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LocalePropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QLocale(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QLocale(*)>(_a[2]))); break;
        case 2: _t->slotEnumChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LocalePropManager::*)(Property * , const QLocale & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalePropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::LocalePropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__LocalePropManager.data,
    qt_meta_data_VSN__QtVision__LocalePropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::LocalePropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::LocalePropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__LocalePropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::LocalePropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::LocalePropManager::valueChanged(Property * _t1, const QLocale & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__PointPropManager_t {
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__PointPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__PointPropManager_t qt_meta_stringdata_VSN__QtVision__PointPropManager = {
    {
QT_MOC_LITERAL(0, 0, 31), // "VSN::QtVision::PointPropManager"
QT_MOC_LITERAL(1, 32, 12), // "valueChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 9), // "Property*"
QT_MOC_LITERAL(4, 56, 8), // "property"
QT_MOC_LITERAL(5, 65, 3), // "val"
QT_MOC_LITERAL(6, 69, 8), // "setValue"
QT_MOC_LITERAL(7, 78, 14), // "slotIntChanged"
QT_MOC_LITERAL(8, 93, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::PointPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue\0slotIntChanged\0slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__PointPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   39,    2, 0x0a /* Public */,
       7,    2,   44,    2, 0x08 /* Private */,
       8,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPoint,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPoint,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::PointPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PointPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 2: _t->slotIntChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PointPropManager::*)(Property * , const QPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PointPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::PointPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__PointPropManager.data,
    qt_meta_data_VSN__QtVision__PointPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::PointPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::PointPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__PointPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::PointPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::PointPropManager::valueChanged(Property * _t1, const QPoint & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__PointFPropManager_t {
    QByteArrayData data[12];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__PointFPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__PointFPropManager_t qt_meta_stringdata_VSN__QtVision__PointFPropManager = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::PointFPropManager"
QT_MOC_LITERAL(1, 33, 12), // "valueChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 9), // "Property*"
QT_MOC_LITERAL(4, 57, 8), // "property"
QT_MOC_LITERAL(5, 66, 3), // "val"
QT_MOC_LITERAL(6, 70, 15), // "decimalsChanged"
QT_MOC_LITERAL(7, 86, 4), // "prec"
QT_MOC_LITERAL(8, 91, 8), // "setValue"
QT_MOC_LITERAL(9, 100, 11), // "setDecimals"
QT_MOC_LITERAL(10, 112, 17), // "slotDoubleChanged"
QT_MOC_LITERAL(11, 130, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::PointFPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "decimalsChanged\0prec\0setValue\0setDecimals\0"
    "slotDoubleChanged\0slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__PointFPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   54,    2, 0x0a /* Public */,
       9,    2,   59,    2, 0x0a /* Public */,
      10,    2,   64,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::PointFPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PointFPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 1: _t->decimalsChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 3: _t->setDecimals((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slotDoubleChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PointFPropManager::*)(Property * , const QPointF & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PointFPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PointFPropManager::*)(Property * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PointFPropManager::decimalsChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::PointFPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__PointFPropManager.data,
    qt_meta_data_VSN__QtVision__PointFPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::PointFPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::PointFPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__PointFPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::PointFPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void VSN::QtVision::PointFPropManager::valueChanged(Property * _t1, const QPointF & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::PointFPropManager::decimalsChanged(Property * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__SizePropManager_t {
    QByteArrayData data[15];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__SizePropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__SizePropManager_t qt_meta_stringdata_VSN__QtVision__SizePropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::SizePropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 81, 6), // "minVal"
QT_MOC_LITERAL(8, 88, 6), // "maxVal"
QT_MOC_LITERAL(9, 95, 8), // "setValue"
QT_MOC_LITERAL(10, 104, 10), // "setMinimum"
QT_MOC_LITERAL(11, 115, 10), // "setMaximum"
QT_MOC_LITERAL(12, 126, 8), // "setRange"
QT_MOC_LITERAL(13, 135, 14), // "slotIntChanged"
QT_MOC_LITERAL(14, 150, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::SizePropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "rangeChanged\0minVal\0maxVal\0setValue\0"
    "setMinimum\0setMaximum\0setRange\0"
    "slotIntChanged\0slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__SizePropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    3,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   66,    2, 0x0a /* Public */,
      10,    2,   71,    2, 0x0a /* Public */,
      11,    2,   76,    2, 0x0a /* Public */,
      12,    3,   81,    2, 0x0a /* Public */,
      13,    2,   88,    2, 0x08 /* Private */,
      14,    1,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSize,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSize, QMetaType::QSize,    4,    7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSize,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSize,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSize,    4,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSize, QMetaType::QSize,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::SizePropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SizePropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSize(*)>(_a[2]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSize(*)>(_a[2])),(*reinterpret_cast< const QSize(*)>(_a[3]))); break;
        case 2: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSize(*)>(_a[2]))); break;
        case 3: _t->setMinimum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSize(*)>(_a[2]))); break;
        case 4: _t->setMaximum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSize(*)>(_a[2]))); break;
        case 5: _t->setRange((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSize(*)>(_a[2])),(*reinterpret_cast< const QSize(*)>(_a[3]))); break;
        case 6: _t->slotIntChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SizePropManager::*)(Property * , const QSize & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SizePropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SizePropManager::*)(Property * , const QSize & , const QSize & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SizePropManager::rangeChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::SizePropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__SizePropManager.data,
    qt_meta_data_VSN__QtVision__SizePropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::SizePropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::SizePropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__SizePropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::SizePropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::SizePropManager::valueChanged(Property * _t1, const QSize & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::SizePropManager::rangeChanged(Property * _t1, const QSize & _t2, const QSize & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__SizeFPropManager_t {
    QByteArrayData data[18];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__SizeFPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__SizeFPropManager_t qt_meta_stringdata_VSN__QtVision__SizeFPropManager = {
    {
QT_MOC_LITERAL(0, 0, 31), // "VSN::QtVision::SizeFPropManager"
QT_MOC_LITERAL(1, 32, 12), // "valueChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 9), // "Property*"
QT_MOC_LITERAL(4, 56, 8), // "property"
QT_MOC_LITERAL(5, 65, 3), // "val"
QT_MOC_LITERAL(6, 69, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 82, 6), // "minVal"
QT_MOC_LITERAL(8, 89, 6), // "maxVal"
QT_MOC_LITERAL(9, 96, 15), // "decimalsChanged"
QT_MOC_LITERAL(10, 112, 4), // "prec"
QT_MOC_LITERAL(11, 117, 8), // "setValue"
QT_MOC_LITERAL(12, 126, 10), // "setMinimum"
QT_MOC_LITERAL(13, 137, 10), // "setMaximum"
QT_MOC_LITERAL(14, 148, 8), // "setRange"
QT_MOC_LITERAL(15, 157, 11), // "setDecimals"
QT_MOC_LITERAL(16, 169, 17), // "slotDoubleChanged"
QT_MOC_LITERAL(17, 187, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::SizeFPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "rangeChanged\0minVal\0maxVal\0decimalsChanged\0"
    "prec\0setValue\0setMinimum\0setMaximum\0"
    "setRange\0setDecimals\0slotDoubleChanged\0"
    "slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__SizeFPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       6,    3,   69,    2, 0x06 /* Public */,
       9,    2,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   81,    2, 0x0a /* Public */,
      12,    2,   86,    2, 0x0a /* Public */,
      13,    2,   91,    2, 0x0a /* Public */,
      14,    3,   96,    2, 0x0a /* Public */,
      15,    2,  103,    2, 0x0a /* Public */,
      16,    2,  108,    2, 0x08 /* Private */,
      17,    1,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSizeF,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSizeF, QMetaType::QSizeF,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSizeF,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSizeF,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSizeF,    4,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSizeF, QMetaType::QSizeF,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,   10,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::SizeFPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SizeFPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSizeF(*)>(_a[2]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSizeF(*)>(_a[2])),(*reinterpret_cast< const QSizeF(*)>(_a[3]))); break;
        case 2: _t->decimalsChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSizeF(*)>(_a[2]))); break;
        case 4: _t->setMinimum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSizeF(*)>(_a[2]))); break;
        case 5: _t->setMaximum((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSizeF(*)>(_a[2]))); break;
        case 6: _t->setRange((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSizeF(*)>(_a[2])),(*reinterpret_cast< const QSizeF(*)>(_a[3]))); break;
        case 7: _t->setDecimals((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->slotDoubleChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SizeFPropManager::*)(Property * , const QSizeF & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SizeFPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SizeFPropManager::*)(Property * , const QSizeF & , const QSizeF & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SizeFPropManager::rangeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SizeFPropManager::*)(Property * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SizeFPropManager::decimalsChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::SizeFPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__SizeFPropManager.data,
    qt_meta_data_VSN__QtVision__SizeFPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::SizeFPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::SizeFPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__SizeFPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::SizeFPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::SizeFPropManager::valueChanged(Property * _t1, const QSizeF & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::SizeFPropManager::rangeChanged(Property * _t1, const QSizeF & _t2, const QSizeF & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::SizeFPropManager::decimalsChanged(Property * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_VSN__QtVision__RectPropManager_t {
    QByteArrayData data[12];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__RectPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__RectPropManager_t qt_meta_stringdata_VSN__QtVision__RectPropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::RectPropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 17), // "constraintChanged"
QT_MOC_LITERAL(7, 86, 10), // "constraint"
QT_MOC_LITERAL(8, 97, 8), // "setValue"
QT_MOC_LITERAL(9, 106, 13), // "setConstraint"
QT_MOC_LITERAL(10, 120, 14), // "slotIntChanged"
QT_MOC_LITERAL(11, 135, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::RectPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "constraintChanged\0constraint\0setValue\0"
    "setConstraint\0slotIntChanged\0"
    "slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__RectPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   54,    2, 0x0a /* Public */,
       9,    2,   59,    2, 0x0a /* Public */,
      10,    2,   64,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRect,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRect,    4,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRect,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRect,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::RectPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RectPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRect(*)>(_a[2]))); break;
        case 1: _t->constraintChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRect(*)>(_a[2]))); break;
        case 2: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRect(*)>(_a[2]))); break;
        case 3: _t->setConstraint((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRect(*)>(_a[2]))); break;
        case 4: _t->slotIntChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RectPropManager::*)(Property * , const QRect & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RectPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RectPropManager::*)(Property * , const QRect & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RectPropManager::constraintChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::RectPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__RectPropManager.data,
    qt_meta_data_VSN__QtVision__RectPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::RectPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::RectPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__RectPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::RectPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void VSN::QtVision::RectPropManager::valueChanged(Property * _t1, const QRect & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::RectPropManager::constraintChanged(Property * _t1, const QRect & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__RectFPropManager_t {
    QByteArrayData data[15];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__RectFPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__RectFPropManager_t qt_meta_stringdata_VSN__QtVision__RectFPropManager = {
    {
QT_MOC_LITERAL(0, 0, 31), // "VSN::QtVision::RectFPropManager"
QT_MOC_LITERAL(1, 32, 12), // "valueChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 9), // "Property*"
QT_MOC_LITERAL(4, 56, 8), // "property"
QT_MOC_LITERAL(5, 65, 3), // "val"
QT_MOC_LITERAL(6, 69, 17), // "constraintChanged"
QT_MOC_LITERAL(7, 87, 10), // "constraint"
QT_MOC_LITERAL(8, 98, 15), // "decimalsChanged"
QT_MOC_LITERAL(9, 114, 4), // "prec"
QT_MOC_LITERAL(10, 119, 8), // "setValue"
QT_MOC_LITERAL(11, 128, 13), // "setConstraint"
QT_MOC_LITERAL(12, 142, 11), // "setDecimals"
QT_MOC_LITERAL(13, 154, 17), // "slotDoubleChanged"
QT_MOC_LITERAL(14, 172, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::RectFPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "constraintChanged\0constraint\0"
    "decimalsChanged\0prec\0setValue\0"
    "setConstraint\0setDecimals\0slotDoubleChanged\0"
    "slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__RectFPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    2,   59,    2, 0x06 /* Public */,
       8,    2,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   69,    2, 0x0a /* Public */,
      11,    2,   74,    2, 0x0a /* Public */,
      12,    2,   79,    2, 0x0a /* Public */,
      13,    2,   84,    2, 0x08 /* Private */,
      14,    1,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRectF,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRectF,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRectF,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRectF,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    9,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::RectFPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RectFPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRectF(*)>(_a[2]))); break;
        case 1: _t->constraintChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRectF(*)>(_a[2]))); break;
        case 2: _t->decimalsChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRectF(*)>(_a[2]))); break;
        case 4: _t->setConstraint((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRectF(*)>(_a[2]))); break;
        case 5: _t->setDecimals((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->slotDoubleChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RectFPropManager::*)(Property * , const QRectF & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RectFPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RectFPropManager::*)(Property * , const QRectF & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RectFPropManager::constraintChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RectFPropManager::*)(Property * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RectFPropManager::decimalsChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::RectFPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__RectFPropManager.data,
    qt_meta_data_VSN__QtVision__RectFPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::RectFPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::RectFPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__RectFPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::RectFPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::RectFPropManager::valueChanged(Property * _t1, const QRectF & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::RectFPropManager::constraintChanged(Property * _t1, const QRectF & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::RectFPropManager::decimalsChanged(Property * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_VSN__QtVision__EnumPropManager_t {
    QByteArrayData data[14];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__EnumPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__EnumPropManager_t qt_meta_stringdata_VSN__QtVision__EnumPropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::EnumPropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 16), // "enumNamesChanged"
QT_MOC_LITERAL(7, 85, 5), // "names"
QT_MOC_LITERAL(8, 91, 16), // "enumIconsChanged"
QT_MOC_LITERAL(9, 108, 15), // "QMap<int,QIcon>"
QT_MOC_LITERAL(10, 124, 5), // "icons"
QT_MOC_LITERAL(11, 130, 8), // "setValue"
QT_MOC_LITERAL(12, 139, 12), // "setEnumNames"
QT_MOC_LITERAL(13, 152, 12) // "setEnumIcons"

    },
    "VSN::QtVision::EnumPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "enumNamesChanged\0names\0enumIconsChanged\0"
    "QMap<int,QIcon>\0icons\0setValue\0"
    "setEnumNames\0setEnumIcons"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__EnumPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    2,   49,    2, 0x06 /* Public */,
       8,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   59,    2, 0x0a /* Public */,
      12,    2,   64,    2, 0x0a /* Public */,
      13,    2,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QStringList,    4,    7,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 9,    4,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QStringList,    4,    7,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 9,    4,   10,

       0        // eod
};

void VSN::QtVision::EnumPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EnumPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->enumNamesChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 2: _t->enumIconsChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QMap<int,QIcon>(*)>(_a[2]))); break;
        case 3: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->setEnumNames((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 5: _t->setEnumIcons((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QMap<int,QIcon>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EnumPropManager::*)(Property * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnumPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EnumPropManager::*)(Property * , const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnumPropManager::enumNamesChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EnumPropManager::*)(Property * , const QMap<int,QIcon> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnumPropManager::enumIconsChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::EnumPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__EnumPropManager.data,
    qt_meta_data_VSN__QtVision__EnumPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::EnumPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::EnumPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__EnumPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::EnumPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void VSN::QtVision::EnumPropManager::valueChanged(Property * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::EnumPropManager::enumNamesChanged(Property * _t1, const QStringList & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::EnumPropManager::enumIconsChanged(Property * _t1, const QMap<int,QIcon> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_VSN__QtVision__FlagPropManager_t {
    QByteArrayData data[12];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__FlagPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__FlagPropManager_t qt_meta_stringdata_VSN__QtVision__FlagPropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::FlagPropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 16), // "flagNamesChanged"
QT_MOC_LITERAL(7, 85, 5), // "names"
QT_MOC_LITERAL(8, 91, 8), // "setValue"
QT_MOC_LITERAL(9, 100, 12), // "setFlagNames"
QT_MOC_LITERAL(10, 113, 15), // "slotBoolChanged"
QT_MOC_LITERAL(11, 129, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::FlagPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "flagNamesChanged\0names\0setValue\0"
    "setFlagNames\0slotBoolChanged\0"
    "slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__FlagPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   54,    2, 0x0a /* Public */,
       9,    2,   59,    2, 0x0a /* Public */,
      10,    2,   64,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QStringList,    4,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QStringList,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::FlagPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlagPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->flagNamesChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 2: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setFlagNames((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 4: _t->slotBoolChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FlagPropManager::*)(Property * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlagPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlagPropManager::*)(Property * , const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlagPropManager::flagNamesChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::FlagPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__FlagPropManager.data,
    qt_meta_data_VSN__QtVision__FlagPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::FlagPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::FlagPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__FlagPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::FlagPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void VSN::QtVision::FlagPropManager::valueChanged(Property * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::FlagPropManager::flagNamesChanged(Property * _t1, const QStringList & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__SizePolicyPropManager_t {
    QByteArrayData data[10];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__SizePolicyPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__SizePolicyPropManager_t qt_meta_stringdata_VSN__QtVision__SizePolicyPropManager = {
    {
QT_MOC_LITERAL(0, 0, 36), // "VSN::QtVision::SizePolicyProp..."
QT_MOC_LITERAL(1, 37, 12), // "valueChanged"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 9), // "Property*"
QT_MOC_LITERAL(4, 61, 8), // "property"
QT_MOC_LITERAL(5, 70, 3), // "val"
QT_MOC_LITERAL(6, 74, 8), // "setValue"
QT_MOC_LITERAL(7, 83, 14), // "slotIntChanged"
QT_MOC_LITERAL(8, 98, 15), // "slotEnumChanged"
QT_MOC_LITERAL(9, 114, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::SizePolicyPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue\0slotIntChanged\0slotEnumChanged\0"
    "slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__SizePolicyPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   44,    2, 0x0a /* Public */,
       7,    2,   49,    2, 0x08 /* Private */,
       8,    2,   54,    2, 0x08 /* Private */,
       9,    1,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSizePolicy,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSizePolicy,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::SizePolicyPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SizePolicyPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSizePolicy(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QSizePolicy(*)>(_a[2]))); break;
        case 2: _t->slotIntChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotEnumChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SizePolicyPropManager::*)(Property * , const QSizePolicy & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SizePolicyPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::SizePolicyPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__SizePolicyPropManager.data,
    qt_meta_data_VSN__QtVision__SizePolicyPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::SizePolicyPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::SizePolicyPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__SizePolicyPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::SizePolicyPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::SizePolicyPropManager::valueChanged(Property * _t1, const QSizePolicy & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__FontPropManager_t {
    QByteArrayData data[13];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__FontPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__FontPropManager_t qt_meta_stringdata_VSN__QtVision__FontPropManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::FontPropManager"
QT_MOC_LITERAL(1, 31, 12), // "valueChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "Property*"
QT_MOC_LITERAL(4, 55, 8), // "property"
QT_MOC_LITERAL(5, 64, 3), // "val"
QT_MOC_LITERAL(6, 68, 8), // "setValue"
QT_MOC_LITERAL(7, 77, 14), // "slotIntChanged"
QT_MOC_LITERAL(8, 92, 15), // "slotEnumChanged"
QT_MOC_LITERAL(9, 108, 15), // "slotBoolChanged"
QT_MOC_LITERAL(10, 124, 21), // "slotPropertyDestroyed"
QT_MOC_LITERAL(11, 146, 23), // "slotFontDatabaseChanged"
QT_MOC_LITERAL(12, 170, 29) // "slotFontDatabaseDelayedChange"

    },
    "VSN::QtVision::FontPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue\0slotIntChanged\0slotEnumChanged\0"
    "slotBoolChanged\0slotPropertyDestroyed\0"
    "slotFontDatabaseChanged\0"
    "slotFontDatabaseDelayedChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__FontPropManager[] = {

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
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   59,    2, 0x0a /* Public */,
       7,    2,   64,    2, 0x08 /* Private */,
       8,    2,   69,    2, 0x08 /* Private */,
       9,    2,   74,    2, 0x08 /* Private */,
      10,    1,   79,    2, 0x08 /* Private */,
      11,    0,   82,    2, 0x08 /* Private */,
      12,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QFont,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QFont,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VSN::QtVision::FontPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FontPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QFont(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QFont(*)>(_a[2]))); break;
        case 2: _t->slotIntChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotEnumChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slotBoolChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        case 6: _t->slotFontDatabaseChanged(); break;
        case 7: _t->slotFontDatabaseDelayedChange(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FontPropManager::*)(Property * , const QFont & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FontPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::FontPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__FontPropManager.data,
    qt_meta_data_VSN__QtVision__FontPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::FontPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::FontPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__FontPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::FontPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::FontPropManager::valueChanged(Property * _t1, const QFont & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__ColorPropManager_t {
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__ColorPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__ColorPropManager_t qt_meta_stringdata_VSN__QtVision__ColorPropManager = {
    {
QT_MOC_LITERAL(0, 0, 31), // "VSN::QtVision::ColorPropManager"
QT_MOC_LITERAL(1, 32, 12), // "valueChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 9), // "Property*"
QT_MOC_LITERAL(4, 56, 8), // "property"
QT_MOC_LITERAL(5, 65, 3), // "val"
QT_MOC_LITERAL(6, 69, 8), // "setValue"
QT_MOC_LITERAL(7, 78, 14), // "slotIntChanged"
QT_MOC_LITERAL(8, 93, 21) // "slotPropertyDestroyed"

    },
    "VSN::QtVision::ColorPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue\0slotIntChanged\0slotPropertyDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__ColorPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   39,    2, 0x0a /* Public */,
       7,    2,   44,    2, 0x08 /* Private */,
       8,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QColor,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QColor,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void VSN::QtVision::ColorPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ColorPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 2: _t->slotIntChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotPropertyDestroyed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ColorPropManager::*)(Property * , const QColor & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::ColorPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__ColorPropManager.data,
    qt_meta_data_VSN__QtVision__ColorPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::ColorPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::ColorPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__ColorPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::ColorPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::ColorPropManager::valueChanged(Property * _t1, const QColor & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__CursorPropManager_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__CursorPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__CursorPropManager_t qt_meta_stringdata_VSN__QtVision__CursorPropManager = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::CursorPropManager"
QT_MOC_LITERAL(1, 33, 12), // "valueChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 9), // "Property*"
QT_MOC_LITERAL(4, 57, 8), // "property"
QT_MOC_LITERAL(5, 66, 3), // "val"
QT_MOC_LITERAL(6, 70, 8) // "setValue"

    },
    "VSN::QtVision::CursorPropManager\0"
    "valueChanged\0\0Property*\0property\0val\0"
    "setValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__CursorPropManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QCursor,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QCursor,    4,    5,

       0        // eod
};

void VSN::QtVision::CursorPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CursorPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QCursor(*)>(_a[2]))); break;
        case 1: _t->setValue((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QCursor(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CursorPropManager::*)(Property * , const QCursor & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CursorPropManager::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::CursorPropManager::staticMetaObject = { {
    &AbsPropertyManager::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__CursorPropManager.data,
    qt_meta_data_VSN__QtVision__CursorPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::CursorPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::CursorPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__CursorPropManager.stringdata0))
        return static_cast<void*>(this);
    return AbsPropertyManager::qt_metacast(_clname);
}

int VSN::QtVision::CursorPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropertyManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::CursorPropManager::valueChanged(Property * _t1, const QCursor & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
