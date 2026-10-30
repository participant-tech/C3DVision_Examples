/****************************************************************************
** Meta object code from reading C++ file 'qt_buttonpropertybrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/propbrowser/qt_buttonpropertybrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_buttonpropertybrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__ButtonPropBrowser_t {
    QByteArrayData data[9];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__ButtonPropBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__ButtonPropBrowser_t qt_meta_stringdata_VSN__QtVision__ButtonPropBrowser = {
    {
QT_MOC_LITERAL(0, 0, 32), // "VSN::QtVision::ButtonPropBrowser"
QT_MOC_LITERAL(1, 33, 9), // "collapsed"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 12), // "BrowserItem*"
QT_MOC_LITERAL(4, 57, 4), // "item"
QT_MOC_LITERAL(5, 62, 8), // "expanded"
QT_MOC_LITERAL(6, 71, 10), // "slotUpdate"
QT_MOC_LITERAL(7, 82, 19), // "slotEditorDestroyed"
QT_MOC_LITERAL(8, 102, 11) // "slotToggled"

    },
    "VSN::QtVision::ButtonPropBrowser\0"
    "collapsed\0\0BrowserItem*\0item\0expanded\0"
    "slotUpdate\0slotEditorDestroyed\0"
    "slotToggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__ButtonPropBrowser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    1,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void VSN::QtVision::ButtonPropBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ButtonPropBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->collapsed((*reinterpret_cast< BrowserItem*(*)>(_a[1]))); break;
        case 1: _t->expanded((*reinterpret_cast< BrowserItem*(*)>(_a[1]))); break;
        case 2: _t->slotUpdate(); break;
        case 3: _t->slotEditorDestroyed(); break;
        case 4: _t->slotToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ButtonPropBrowser::*)(BrowserItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonPropBrowser::collapsed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ButtonPropBrowser::*)(BrowserItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonPropBrowser::expanded)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::ButtonPropBrowser::staticMetaObject = { {
    &AbsPropBrowser::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__ButtonPropBrowser.data,
    qt_meta_data_VSN__QtVision__ButtonPropBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::ButtonPropBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::ButtonPropBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__ButtonPropBrowser.stringdata0))
        return static_cast<void*>(this);
    return AbsPropBrowser::qt_metacast(_clname);
}

int VSN::QtVision::ButtonPropBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsPropBrowser::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::ButtonPropBrowser::collapsed(BrowserItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::ButtonPropBrowser::expanded(BrowserItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
