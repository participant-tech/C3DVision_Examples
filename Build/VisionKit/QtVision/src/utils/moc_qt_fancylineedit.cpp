/****************************************************************************
** Meta object code from reading C++ file 'qt_fancylineedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/utils/qt_fancylineedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_fancylineedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__IconButton_t {
    QByteArrayData data[3];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__IconButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__IconButton_t qt_meta_stringdata_VSN__QtVision__IconButton = {
    {
QT_MOC_LITERAL(0, 0, 25), // "VSN::QtVision::IconButton"
QT_MOC_LITERAL(1, 26, 11), // "iconOpacity"
QT_MOC_LITERAL(2, 38, 8) // "autoHide"

    },
    "VSN::QtVision::IconButton\0iconOpacity\0"
    "autoHide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__IconButton[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Float, 0x00095103,
       2, QMetaType::Bool, 0x00095103,

       0        // eod
};

void VSN::QtVision::IconButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<IconButton *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->iconOpacity(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->hasAutoHide(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<IconButton *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIconOpacity(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setAutoHide(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::IconButton::staticMetaObject = { {
    &QAbstractButton::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__IconButton.data,
    qt_meta_data_VSN__QtVision__IconButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::IconButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::IconButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__IconButton.stringdata0))
        return static_cast<void*>(this);
    return QAbstractButton::qt_metacast(_clname);
}

int VSN::QtVision::IconButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_VSN__QtVision__FancyLineEdit_t {
    QByteArrayData data[14];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__FancyLineEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__FancyLineEdit_t qt_meta_stringdata_VSN__QtVision__FancyLineEdit = {
    {
QT_MOC_LITERAL(0, 0, 28), // "VSN::QtVision::FancyLineEdit"
QT_MOC_LITERAL(1, 29, 13), // "buttonClicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 19), // "FancyLineEdit::Side"
QT_MOC_LITERAL(4, 64, 4), // "side"
QT_MOC_LITERAL(5, 69, 17), // "leftButtonClicked"
QT_MOC_LITERAL(6, 87, 18), // "rightButtonClicked"
QT_MOC_LITERAL(7, 106, 13), // "filterChanged"
QT_MOC_LITERAL(8, 120, 12), // "validChanged"
QT_MOC_LITERAL(9, 133, 10), // "validState"
QT_MOC_LITERAL(10, 144, 18), // "validReturnPressed"
QT_MOC_LITERAL(11, 163, 4), // "Side"
QT_MOC_LITERAL(12, 168, 4), // "Left"
QT_MOC_LITERAL(13, 173, 5) // "Right"

    },
    "VSN::QtVision::FancyLineEdit\0buttonClicked\0"
    "\0FancyLineEdit::Side\0side\0leftButtonClicked\0"
    "rightButtonClicked\0filterChanged\0"
    "validChanged\0validState\0validReturnPressed\0"
    "Side\0Left\0Right"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__FancyLineEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       1,   56, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       6,    0,   48,    2, 0x06 /* Public */,
       7,    1,   49,    2, 0x06 /* Public */,
       8,    1,   52,    2, 0x06 /* Public */,
      10,    0,   55,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
      11,   11, 0x0,    2,   61,

 // enum data: key, value
      12, uint(VSN::QtVision::FancyLineEdit::Left),
      13, uint(VSN::QtVision::FancyLineEdit::Right),

       0        // eod
};

void VSN::QtVision::FancyLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FancyLineEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonClicked((*reinterpret_cast< FancyLineEdit::Side(*)>(_a[1]))); break;
        case 1: _t->leftButtonClicked(); break;
        case 2: _t->rightButtonClicked(); break;
        case 3: _t->filterChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->validChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->validReturnPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FancyLineEdit::*)(FancyLineEdit::Side );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FancyLineEdit::buttonClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FancyLineEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FancyLineEdit::leftButtonClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FancyLineEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FancyLineEdit::rightButtonClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FancyLineEdit::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FancyLineEdit::filterChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FancyLineEdit::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FancyLineEdit::validChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FancyLineEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FancyLineEdit::validReturnPressed)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::FancyLineEdit::staticMetaObject = { {
    &CompletingLineEdit::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__FancyLineEdit.data,
    qt_meta_data_VSN__QtVision__FancyLineEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::FancyLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::FancyLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__FancyLineEdit.stringdata0))
        return static_cast<void*>(this);
    return CompletingLineEdit::qt_metacast(_clname);
}

int VSN::QtVision::FancyLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CompletingLineEdit::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::FancyLineEdit::buttonClicked(FancyLineEdit::Side _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::FancyLineEdit::leftButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VSN::QtVision::FancyLineEdit::rightButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void VSN::QtVision::FancyLineEdit::filterChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VSN::QtVision::FancyLineEdit::validChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VSN::QtVision::FancyLineEdit::validReturnPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
