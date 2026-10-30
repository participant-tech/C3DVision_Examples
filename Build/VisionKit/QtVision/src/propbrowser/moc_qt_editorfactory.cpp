/****************************************************************************
** Meta object code from reading C++ file 'qt_editorfactory.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/propbrowser/qt_editorfactory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_editorfactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__SpinBoxFactory_t {
    QByteArrayData data[8];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__SpinBoxFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__SpinBoxFactory_t qt_meta_stringdata_VSN__QtVision__SpinBoxFactory = {
    {
QT_MOC_LITERAL(0, 0, 29), // "VSN::QtVision::SpinBoxFactory"
QT_MOC_LITERAL(1, 30, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 9), // "Property*"
QT_MOC_LITERAL(4, 61, 16), // "slotRangeChanged"
QT_MOC_LITERAL(5, 78, 21), // "slotSingleStepChanged"
QT_MOC_LITERAL(6, 100, 12), // "slotSetValue"
QT_MOC_LITERAL(7, 113, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::SpinBoxFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotRangeChanged\0slotSingleStepChanged\0"
    "slotSetValue\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__SpinBoxFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       4,    3,   44,    2, 0x08 /* Private */,
       5,    2,   51,    2, 0x08 /* Private */,
       6,    1,   56,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::SpinBoxFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpinBoxFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->slotSingleStepChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotSetValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::SpinBoxFactory::staticMetaObject = { {
    &AbsEditorFactory<IntPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__SpinBoxFactory.data,
    qt_meta_data_VSN__QtVision__SpinBoxFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::SpinBoxFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::SpinBoxFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__SpinBoxFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<IntPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::SpinBoxFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<IntPropManager>::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__SliderFactory_t {
    QByteArrayData data[8];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__SliderFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__SliderFactory_t qt_meta_stringdata_VSN__QtVision__SliderFactory = {
    {
QT_MOC_LITERAL(0, 0, 28), // "VSN::QtVision::SliderFactory"
QT_MOC_LITERAL(1, 29, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 9), // "Property*"
QT_MOC_LITERAL(4, 60, 16), // "slotRangeChanged"
QT_MOC_LITERAL(5, 77, 21), // "slotSingleStepChanged"
QT_MOC_LITERAL(6, 99, 12), // "slotSetValue"
QT_MOC_LITERAL(7, 112, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::SliderFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotRangeChanged\0slotSingleStepChanged\0"
    "slotSetValue\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__SliderFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       4,    3,   44,    2, 0x08 /* Private */,
       5,    2,   51,    2, 0x08 /* Private */,
       6,    1,   56,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::SliderFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SliderFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->slotSingleStepChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotSetValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::SliderFactory::staticMetaObject = { {
    &AbsEditorFactory<IntPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__SliderFactory.data,
    qt_meta_data_VSN__QtVision__SliderFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::SliderFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::SliderFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__SliderFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<IntPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::SliderFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<IntPropManager>::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__ScrollBarFactory_t {
    QByteArrayData data[8];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__ScrollBarFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__ScrollBarFactory_t qt_meta_stringdata_VSN__QtVision__ScrollBarFactory = {
    {
QT_MOC_LITERAL(0, 0, 31), // "VSN::QtVision::ScrollBarFactory"
QT_MOC_LITERAL(1, 32, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 9), // "Property*"
QT_MOC_LITERAL(4, 63, 16), // "slotRangeChanged"
QT_MOC_LITERAL(5, 80, 21), // "slotSingleStepChanged"
QT_MOC_LITERAL(6, 102, 12), // "slotSetValue"
QT_MOC_LITERAL(7, 115, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::ScrollBarFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotRangeChanged\0slotSingleStepChanged\0"
    "slotSetValue\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__ScrollBarFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       4,    3,   44,    2, 0x08 /* Private */,
       5,    2,   51,    2, 0x08 /* Private */,
       6,    1,   56,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::ScrollBarFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScrollBarFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->slotSingleStepChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotSetValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::ScrollBarFactory::staticMetaObject = { {
    &AbsEditorFactory<IntPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__ScrollBarFactory.data,
    qt_meta_data_VSN__QtVision__ScrollBarFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::ScrollBarFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::ScrollBarFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__ScrollBarFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<IntPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::ScrollBarFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<IntPropManager>::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__CheckBoxFactory_t {
    QByteArrayData data[6];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__CheckBoxFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__CheckBoxFactory_t qt_meta_stringdata_VSN__QtVision__CheckBoxFactory = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::CheckBoxFactory"
QT_MOC_LITERAL(1, 31, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 9), // "Property*"
QT_MOC_LITERAL(4, 62, 12), // "slotSetValue"
QT_MOC_LITERAL(5, 75, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::CheckBoxFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotSetValue\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__CheckBoxFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       4,    1,   34,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::CheckBoxFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CheckBoxFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->slotSetValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::CheckBoxFactory::staticMetaObject = { {
    &AbsEditorFactory<BoolPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__CheckBoxFactory.data,
    qt_meta_data_VSN__QtVision__CheckBoxFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::CheckBoxFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::CheckBoxFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__CheckBoxFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<BoolPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::CheckBoxFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<BoolPropManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__DoubleSpinBoxFactory_t {
    QByteArrayData data[9];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__DoubleSpinBoxFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__DoubleSpinBoxFactory_t qt_meta_stringdata_VSN__QtVision__DoubleSpinBoxFactory = {
    {
QT_MOC_LITERAL(0, 0, 35), // "VSN::QtVision::DoubleSpinBoxF..."
QT_MOC_LITERAL(1, 36, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 56, 0), // ""
QT_MOC_LITERAL(3, 57, 9), // "Property*"
QT_MOC_LITERAL(4, 67, 16), // "slotRangeChanged"
QT_MOC_LITERAL(5, 84, 21), // "slotSingleStepChanged"
QT_MOC_LITERAL(6, 106, 19), // "slotDecimalsChanged"
QT_MOC_LITERAL(7, 126, 12), // "slotSetValue"
QT_MOC_LITERAL(8, 139, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::DoubleSpinBoxFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotRangeChanged\0slotSingleStepChanged\0"
    "slotDecimalsChanged\0slotSetValue\0"
    "slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__DoubleSpinBoxFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x08 /* Private */,
       4,    3,   49,    2, 0x08 /* Private */,
       5,    2,   56,    2, 0x08 /* Private */,
       6,    2,   61,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       8,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double, QMetaType::Double,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::DoubleSpinBoxFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoubleSpinBoxFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->slotSingleStepChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->slotDecimalsChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slotSetValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::DoubleSpinBoxFactory::staticMetaObject = { {
    &AbsEditorFactory<DoublePropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__DoubleSpinBoxFactory.data,
    qt_meta_data_VSN__QtVision__DoubleSpinBoxFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::DoubleSpinBoxFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::DoubleSpinBoxFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__DoubleSpinBoxFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<DoublePropManager>::qt_metacast(_clname);
}

int VSN::QtVision::DoubleSpinBoxFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<DoublePropManager>::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__LineEditFactory_t {
    QByteArrayData data[7];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__LineEditFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__LineEditFactory_t qt_meta_stringdata_VSN__QtVision__LineEditFactory = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::LineEditFactory"
QT_MOC_LITERAL(1, 31, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 9), // "Property*"
QT_MOC_LITERAL(4, 62, 17), // "slotRegExpChanged"
QT_MOC_LITERAL(5, 80, 12), // "slotSetValue"
QT_MOC_LITERAL(6, 93, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::LineEditFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotRegExpChanged\0slotSetValue\0"
    "slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__LineEditFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x08 /* Private */,
       4,    2,   39,    2, 0x08 /* Private */,
       5,    1,   44,    2, 0x08 /* Private */,
       6,    1,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QRegularExpression,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::LineEditFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LineEditFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->slotRegExpChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QRegularExpression(*)>(_a[2]))); break;
        case 2: _t->slotSetValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::LineEditFactory::staticMetaObject = { {
    &AbsEditorFactory<StringPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__LineEditFactory.data,
    qt_meta_data_VSN__QtVision__LineEditFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::LineEditFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::LineEditFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__LineEditFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<StringPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::LineEditFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<StringPropManager>::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__DateEditFactory_t {
    QByteArrayData data[7];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__DateEditFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__DateEditFactory_t qt_meta_stringdata_VSN__QtVision__DateEditFactory = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::DateEditFactory"
QT_MOC_LITERAL(1, 31, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 9), // "Property*"
QT_MOC_LITERAL(4, 62, 16), // "slotRangeChanged"
QT_MOC_LITERAL(5, 79, 12), // "slotSetValue"
QT_MOC_LITERAL(6, 92, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::DateEditFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotRangeChanged\0slotSetValue\0"
    "slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__DateEditFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x08 /* Private */,
       4,    3,   39,    2, 0x08 /* Private */,
       5,    1,   46,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDate,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDate, QMetaType::QDate,    2,    2,    2,
    QMetaType::Void, QMetaType::QDate,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::DateEditFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DateEditFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2])),(*reinterpret_cast< const QDate(*)>(_a[3]))); break;
        case 2: _t->slotSetValue((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::DateEditFactory::staticMetaObject = { {
    &AbsEditorFactory<DatePropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__DateEditFactory.data,
    qt_meta_data_VSN__QtVision__DateEditFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::DateEditFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::DateEditFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__DateEditFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<DatePropManager>::qt_metacast(_clname);
}

int VSN::QtVision::DateEditFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<DatePropManager>::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__TimeEditFactory_t {
    QByteArrayData data[6];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__TimeEditFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__TimeEditFactory_t qt_meta_stringdata_VSN__QtVision__TimeEditFactory = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::TimeEditFactory"
QT_MOC_LITERAL(1, 31, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 9), // "Property*"
QT_MOC_LITERAL(4, 62, 12), // "slotSetValue"
QT_MOC_LITERAL(5, 75, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::TimeEditFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotSetValue\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__TimeEditFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       4,    1,   34,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QTime,    2,    2,
    QMetaType::Void, QMetaType::QTime,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::TimeEditFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimeEditFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QTime(*)>(_a[2]))); break;
        case 1: _t->slotSetValue((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 2: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::TimeEditFactory::staticMetaObject = { {
    &AbsEditorFactory<TimePropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__TimeEditFactory.data,
    qt_meta_data_VSN__QtVision__TimeEditFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::TimeEditFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::TimeEditFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__TimeEditFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<TimePropManager>::qt_metacast(_clname);
}

int VSN::QtVision::TimeEditFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<TimePropManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__DateTimeEditFactory_t {
    QByteArrayData data[6];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__DateTimeEditFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__DateTimeEditFactory_t qt_meta_stringdata_VSN__QtVision__DateTimeEditFactory = {
    {
QT_MOC_LITERAL(0, 0, 34), // "VSN::QtVision::DateTimeEditFa..."
QT_MOC_LITERAL(1, 35, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 9), // "Property*"
QT_MOC_LITERAL(4, 66, 12), // "slotSetValue"
QT_MOC_LITERAL(5, 79, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::DateTimeEditFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotSetValue\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__DateTimeEditFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       4,    1,   34,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QDateTime,    2,    2,
    QMetaType::Void, QMetaType::QDateTime,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::DateTimeEditFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DateTimeEditFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QDateTime(*)>(_a[2]))); break;
        case 1: _t->slotSetValue((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 2: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::DateTimeEditFactory::staticMetaObject = { {
    &AbsEditorFactory<DateTimePropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__DateTimeEditFactory.data,
    qt_meta_data_VSN__QtVision__DateTimeEditFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::DateTimeEditFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::DateTimeEditFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__DateTimeEditFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<DateTimePropManager>::qt_metacast(_clname);
}

int VSN::QtVision::DateTimeEditFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<DateTimePropManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__KeySequenceEditorFactory_t {
    QByteArrayData data[6];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__KeySequenceEditorFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__KeySequenceEditorFactory_t qt_meta_stringdata_VSN__QtVision__KeySequenceEditorFactory = {
    {
QT_MOC_LITERAL(0, 0, 39), // "VSN::QtVision::KeySequenceEdi..."
QT_MOC_LITERAL(1, 40, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 60, 0), // ""
QT_MOC_LITERAL(3, 61, 9), // "Property*"
QT_MOC_LITERAL(4, 71, 12), // "slotSetValue"
QT_MOC_LITERAL(5, 84, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::KeySequenceEditorFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotSetValue\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__KeySequenceEditorFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       4,    1,   34,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QKeySequence,    2,    2,
    QMetaType::Void, QMetaType::QKeySequence,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::KeySequenceEditorFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KeySequenceEditorFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QKeySequence(*)>(_a[2]))); break;
        case 1: _t->slotSetValue((*reinterpret_cast< const QKeySequence(*)>(_a[1]))); break;
        case 2: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::KeySequenceEditorFactory::staticMetaObject = { {
    &AbsEditorFactory<KeySequencePropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__KeySequenceEditorFactory.data,
    qt_meta_data_VSN__QtVision__KeySequenceEditorFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::KeySequenceEditorFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::KeySequenceEditorFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__KeySequenceEditorFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<KeySequencePropManager>::qt_metacast(_clname);
}

int VSN::QtVision::KeySequenceEditorFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<KeySequencePropManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__CharEditorFactory_t {
    QByteArrayData data[6];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__CharEditorFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__CharEditorFactory_t qt_meta_stringdata_VSN__QtVision__CharEditorFactory = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::CharEditorFactory"
QT_MOC_LITERAL(1, 33, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 9), // "Property*"
QT_MOC_LITERAL(4, 64, 12), // "slotSetValue"
QT_MOC_LITERAL(5, 77, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::CharEditorFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotSetValue\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__CharEditorFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       4,    1,   34,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QChar,    2,    2,
    QMetaType::Void, QMetaType::QChar,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::CharEditorFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CharEditorFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QChar(*)>(_a[2]))); break;
        case 1: _t->slotSetValue((*reinterpret_cast< const QChar(*)>(_a[1]))); break;
        case 2: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::CharEditorFactory::staticMetaObject = { {
    &AbsEditorFactory<CharPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__CharEditorFactory.data,
    qt_meta_data_VSN__QtVision__CharEditorFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::CharEditorFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::CharEditorFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__CharEditorFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<CharPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::CharEditorFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<CharPropManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__EnumEditorFactory_t {
    QByteArrayData data[9];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__EnumEditorFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__EnumEditorFactory_t qt_meta_stringdata_VSN__QtVision__EnumEditorFactory = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::EnumEditorFactory"
QT_MOC_LITERAL(1, 33, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 9), // "Property*"
QT_MOC_LITERAL(4, 64, 20), // "slotEnumNamesChanged"
QT_MOC_LITERAL(5, 85, 20), // "slotEnumIconsChanged"
QT_MOC_LITERAL(6, 106, 15), // "QMap<int,QIcon>"
QT_MOC_LITERAL(7, 122, 12), // "slotSetValue"
QT_MOC_LITERAL(8, 135, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::EnumEditorFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotEnumNamesChanged\0slotEnumIconsChanged\0"
    "QMap<int,QIcon>\0slotSetValue\0"
    "slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__EnumEditorFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       4,    2,   44,    2, 0x08 /* Private */,
       5,    2,   49,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       8,    1,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QStringList,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 6,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::EnumEditorFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EnumEditorFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotEnumNamesChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 2: _t->slotEnumIconsChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QMap<int,QIcon>(*)>(_a[2]))); break;
        case 3: _t->slotSetValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::EnumEditorFactory::staticMetaObject = { {
    &AbsEditorFactory<EnumPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__EnumEditorFactory.data,
    qt_meta_data_VSN__QtVision__EnumEditorFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::EnumEditorFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::EnumEditorFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__EnumEditorFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<EnumPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::EnumEditorFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<EnumPropManager>::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__CursorEditorFactory_t {
    QByteArrayData data[6];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__CursorEditorFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__CursorEditorFactory_t qt_meta_stringdata_VSN__QtVision__CursorEditorFactory = {
    {
QT_MOC_LITERAL(0, 0, 34), // "VSN::QtVision::CursorEditorFa..."
QT_MOC_LITERAL(1, 35, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 9), // "Property*"
QT_MOC_LITERAL(4, 66, 15), // "slotEnumChanged"
QT_MOC_LITERAL(5, 82, 19) // "slotEditorDestroyed"

    },
    "VSN::QtVision::CursorEditorFactory\0"
    "slotPropertyChanged\0\0Property*\0"
    "slotEnumChanged\0slotEditorDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__CursorEditorFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       4,    2,   34,    2, 0x08 /* Private */,
       5,    1,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QCursor,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,

       0        // eod
};

void VSN::QtVision::CursorEditorFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CursorEditorFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QCursor(*)>(_a[2]))); break;
        case 1: _t->slotEnumChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::CursorEditorFactory::staticMetaObject = { {
    &AbsEditorFactory<CursorPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__CursorEditorFactory.data,
    qt_meta_data_VSN__QtVision__CursorEditorFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::CursorEditorFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::CursorEditorFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__CursorEditorFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<CursorPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::CursorEditorFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<CursorPropManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__ColorEditorFactory_t {
    QByteArrayData data[9];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__ColorEditorFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__ColorEditorFactory_t qt_meta_stringdata_VSN__QtVision__ColorEditorFactory = {
    {
QT_MOC_LITERAL(0, 0, 33), // "VSN::QtVision::ColorEditorFac..."
QT_MOC_LITERAL(1, 34, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 9), // "Property*"
QT_MOC_LITERAL(4, 65, 8), // "property"
QT_MOC_LITERAL(5, 74, 5), // "value"
QT_MOC_LITERAL(6, 80, 19), // "slotEditorDestroyed"
QT_MOC_LITERAL(7, 100, 6), // "object"
QT_MOC_LITERAL(8, 107, 12) // "slotSetValue"

    },
    "VSN::QtVision::ColorEditorFactory\0"
    "slotPropertyChanged\0\0Property*\0property\0"
    "value\0slotEditorDestroyed\0object\0"
    "slotSetValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__ColorEditorFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       6,    1,   34,    2, 0x08 /* Private */,
       8,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QColor,    4,    5,
    QMetaType::Void, QMetaType::QObjectStar,    7,
    QMetaType::Void, QMetaType::QColor,    5,

       0        // eod
};

void VSN::QtVision::ColorEditorFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ColorEditorFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 1: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->slotSetValue((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::ColorEditorFactory::staticMetaObject = { {
    &AbsEditorFactory<ColorPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__ColorEditorFactory.data,
    qt_meta_data_VSN__QtVision__ColorEditorFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::ColorEditorFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::ColorEditorFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__ColorEditorFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<ColorPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::ColorEditorFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<ColorPropManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__FontEditorFactory_t {
    QByteArrayData data[9];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__FontEditorFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__FontEditorFactory_t qt_meta_stringdata_VSN__QtVision__FontEditorFactory = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::FontEditorFactory"
QT_MOC_LITERAL(1, 33, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 9), // "Property*"
QT_MOC_LITERAL(4, 64, 8), // "property"
QT_MOC_LITERAL(5, 73, 5), // "value"
QT_MOC_LITERAL(6, 79, 19), // "slotEditorDestroyed"
QT_MOC_LITERAL(7, 99, 6), // "object"
QT_MOC_LITERAL(8, 106, 12) // "slotSetValue"

    },
    "VSN::QtVision::FontEditorFactory\0"
    "slotPropertyChanged\0\0Property*\0property\0"
    "value\0slotEditorDestroyed\0object\0"
    "slotSetValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__FontEditorFactory[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       6,    1,   34,    2, 0x08 /* Private */,
       8,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QFont,    4,    5,
    QMetaType::Void, QMetaType::QObjectStar,    7,
    QMetaType::Void, QMetaType::QFont,    5,

       0        // eod
};

void VSN::QtVision::FontEditorFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FontEditorFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< Property*(*)>(_a[1])),(*reinterpret_cast< const QFont(*)>(_a[2]))); break;
        case 1: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->slotSetValue((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::FontEditorFactory::staticMetaObject = { {
    &AbsEditorFactory<FontPropManager>::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__FontEditorFactory.data,
    qt_meta_data_VSN__QtVision__FontEditorFactory,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::FontEditorFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::FontEditorFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__FontEditorFactory.stringdata0))
        return static_cast<void*>(this);
    return AbsEditorFactory<FontPropManager>::qt_metacast(_clname);
}

int VSN::QtVision::FontEditorFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsEditorFactory<FontPropManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
