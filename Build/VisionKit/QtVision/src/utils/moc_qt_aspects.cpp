/****************************************************************************
** Meta object code from reading C++ file 'qt_aspects.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/utils/qt_aspects.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_aspects.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__BaseAspect_t {
    QByteArrayData data[5];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__BaseAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__BaseAspect_t qt_meta_stringdata_VSN__QtVision__BaseAspect = {
    {
QT_MOC_LITERAL(0, 0, 25), // "VSN::QtVision::BaseAspect"
QT_MOC_LITERAL(1, 26, 7), // "changed"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "labelLinkActivated"
QT_MOC_LITERAL(4, 54, 4) // "link"

    },
    "VSN::QtVision::BaseAspect\0changed\0\0"
    "labelLinkActivated\0link"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__BaseAspect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    1,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void VSN::QtVision::BaseAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseAspect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->labelLinkActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BaseAspect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseAspect::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BaseAspect::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseAspect::labelLinkActivated)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::BaseAspect::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__BaseAspect.data,
    qt_meta_data_VSN__QtVision__BaseAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::BaseAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::BaseAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__BaseAspect.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VSN::QtVision::BaseAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::BaseAspect::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VSN::QtVision::BaseAspect::labelLinkActivated(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__BoolAspect_t {
    QByteArrayData data[5];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__BoolAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__BoolAspect_t qt_meta_stringdata_VSN__QtVision__BoolAspect = {
    {
QT_MOC_LITERAL(0, 0, 25), // "VSN::QtVision::BoolAspect"
QT_MOC_LITERAL(1, 26, 12), // "valueChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 8), // "newValue"
QT_MOC_LITERAL(4, 49, 20) // "volatileValueChanged"

    },
    "VSN::QtVision::BoolAspect\0valueChanged\0"
    "\0newValue\0volatileValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__BoolAspect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void VSN::QtVision::BoolAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BoolAspect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->volatileValueChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BoolAspect::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BoolAspect::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BoolAspect::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BoolAspect::volatileValueChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::BoolAspect::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__BoolAspect.data,
    qt_meta_data_VSN__QtVision__BoolAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::BoolAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::BoolAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__BoolAspect.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::BoolAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::BoolAspect::valueChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::BoolAspect::volatileValueChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__SelectionAspect_t {
    QByteArrayData data[4];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__SelectionAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__SelectionAspect_t qt_meta_stringdata_VSN__QtVision__SelectionAspect = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::SelectionAspect"
QT_MOC_LITERAL(1, 31, 20), // "volatileValueChanged"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 8) // "newValue"

    },
    "VSN::QtVision::SelectionAspect\0"
    "volatileValueChanged\0\0newValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__SelectionAspect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void VSN::QtVision::SelectionAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectionAspect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->volatileValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SelectionAspect::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectionAspect::volatileValueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::SelectionAspect::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__SelectionAspect.data,
    qt_meta_data_VSN__QtVision__SelectionAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::SelectionAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::SelectionAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__SelectionAspect.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::SelectionAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void VSN::QtVision::SelectionAspect::volatileValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__MultiSelectionAspect_t {
    QByteArrayData data[1];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__MultiSelectionAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__MultiSelectionAspect_t qt_meta_stringdata_VSN__QtVision__MultiSelectionAspect = {
    {
QT_MOC_LITERAL(0, 0, 35) // "VSN::QtVision::MultiSelection..."

    },
    "VSN::QtVision::MultiSelectionAspect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__MultiSelectionAspect[] = {

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

void VSN::QtVision::MultiSelectionAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::MultiSelectionAspect::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__MultiSelectionAspect.data,
    qt_meta_data_VSN__QtVision__MultiSelectionAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::MultiSelectionAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::MultiSelectionAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__MultiSelectionAspect.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::MultiSelectionAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__StringAspect_t {
    QByteArrayData data[5];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__StringAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__StringAspect_t qt_meta_stringdata_VSN__QtVision__StringAspect = {
    {
QT_MOC_LITERAL(0, 0, 27), // "VSN::QtVision::StringAspect"
QT_MOC_LITERAL(1, 28, 14), // "checkedChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 12), // "valueChanged"
QT_MOC_LITERAL(4, 57, 8) // "newValue"

    },
    "VSN::QtVision::StringAspect\0checkedChanged\0"
    "\0valueChanged\0newValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__StringAspect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    1,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void VSN::QtVision::StringAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StringAspect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checkedChanged(); break;
        case 1: _t->valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StringAspect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StringAspect::checkedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StringAspect::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StringAspect::valueChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::StringAspect::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__StringAspect.data,
    qt_meta_data_VSN__QtVision__StringAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::StringAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::StringAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__StringAspect.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::StringAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::StringAspect::checkedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VSN::QtVision::StringAspect::valueChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_VSN__QtVision__IntegerAspect_t {
    QByteArrayData data[1];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__IntegerAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__IntegerAspect_t qt_meta_stringdata_VSN__QtVision__IntegerAspect = {
    {
QT_MOC_LITERAL(0, 0, 28) // "VSN::QtVision::IntegerAspect"

    },
    "VSN::QtVision::IntegerAspect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__IntegerAspect[] = {

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

void VSN::QtVision::IntegerAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::IntegerAspect::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__IntegerAspect.data,
    qt_meta_data_VSN__QtVision__IntegerAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::IntegerAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::IntegerAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__IntegerAspect.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::IntegerAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__DoubleAspect_t {
    QByteArrayData data[1];
    char stringdata0[28];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__DoubleAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__DoubleAspect_t qt_meta_stringdata_VSN__QtVision__DoubleAspect = {
    {
QT_MOC_LITERAL(0, 0, 27) // "VSN::QtVision::DoubleAspect"

    },
    "VSN::QtVision::DoubleAspect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__DoubleAspect[] = {

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

void VSN::QtVision::DoubleAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::DoubleAspect::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__DoubleAspect.data,
    qt_meta_data_VSN__QtVision__DoubleAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::DoubleAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::DoubleAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__DoubleAspect.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::DoubleAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__TriStateAspect_t {
    QByteArrayData data[1];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__TriStateAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__TriStateAspect_t qt_meta_stringdata_VSN__QtVision__TriStateAspect = {
    {
QT_MOC_LITERAL(0, 0, 29) // "VSN::QtVision::TriStateAspect"

    },
    "VSN::QtVision::TriStateAspect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__TriStateAspect[] = {

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

void VSN::QtVision::TriStateAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::TriStateAspect::staticMetaObject = { {
    &SelectionAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__TriStateAspect.data,
    qt_meta_data_VSN__QtVision__TriStateAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::TriStateAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::TriStateAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__TriStateAspect.stringdata0))
        return static_cast<void*>(this);
    return SelectionAspect::qt_metacast(_clname);
}

int VSN::QtVision::TriStateAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SelectionAspect::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__StringListAspect_t {
    QByteArrayData data[1];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__StringListAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__StringListAspect_t qt_meta_stringdata_VSN__QtVision__StringListAspect = {
    {
QT_MOC_LITERAL(0, 0, 31) // "VSN::QtVision::StringListAspect"

    },
    "VSN::QtVision::StringListAspect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__StringListAspect[] = {

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

void VSN::QtVision::StringListAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::StringListAspect::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__StringListAspect.data,
    qt_meta_data_VSN__QtVision__StringListAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::StringListAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::StringListAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__StringListAspect.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::StringListAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__IntegersAspect_t {
    QByteArrayData data[5];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__IntegersAspect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__IntegersAspect_t qt_meta_stringdata_VSN__QtVision__IntegersAspect = {
    {
QT_MOC_LITERAL(0, 0, 29), // "VSN::QtVision::IntegersAspect"
QT_MOC_LITERAL(1, 30, 12), // "valueChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 10), // "QList<int>"
QT_MOC_LITERAL(4, 55, 6) // "values"

    },
    "VSN::QtVision::IntegersAspect\0"
    "valueChanged\0\0QList<int>\0values"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__IntegersAspect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void VSN::QtVision::IntegersAspect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntegersAspect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< const QList<int>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IntegersAspect::*)(const QList<int> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegersAspect::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::IntegersAspect::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__IntegersAspect.data,
    qt_meta_data_VSN__QtVision__IntegersAspect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::IntegersAspect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::IntegersAspect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__IntegersAspect.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::IntegersAspect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::IntegersAspect::valueChanged(const QList<int> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VSN__QtVision__TextDisplay_t {
    QByteArrayData data[1];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__TextDisplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__TextDisplay_t qt_meta_stringdata_VSN__QtVision__TextDisplay = {
    {
QT_MOC_LITERAL(0, 0, 26) // "VSN::QtVision::TextDisplay"

    },
    "VSN::QtVision::TextDisplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__TextDisplay[] = {

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

void VSN::QtVision::TextDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::TextDisplay::staticMetaObject = { {
    &BaseAspect::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__TextDisplay.data,
    qt_meta_data_VSN__QtVision__TextDisplay,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::TextDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::TextDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__TextDisplay.stringdata0))
        return static_cast<void*>(this);
    return BaseAspect::qt_metacast(_clname);
}

int VSN::QtVision::TextDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAspect::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__AspectContainer_t {
    QByteArrayData data[4];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__AspectContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__AspectContainer_t qt_meta_stringdata_VSN__QtVision__AspectContainer = {
    {
QT_MOC_LITERAL(0, 0, 30), // "VSN::QtVision::AspectContainer"
QT_MOC_LITERAL(1, 31, 7), // "applied"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 15) // "fromMapFinished"

    },
    "VSN::QtVision::AspectContainer\0applied\0"
    "\0fromMapFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__AspectContainer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VSN::QtVision::AspectContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AspectContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->applied(); break;
        case 1: _t->fromMapFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AspectContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AspectContainer::applied)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AspectContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AspectContainer::fromMapFinished)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::AspectContainer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__AspectContainer.data,
    qt_meta_data_VSN__QtVision__AspectContainer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::AspectContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::AspectContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__AspectContainer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VSN::QtVision::AspectContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::AspectContainer::applied()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VSN::QtVision::AspectContainer::fromMapFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
