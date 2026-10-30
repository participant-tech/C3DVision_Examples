/****************************************************************************
** Meta object code from reading C++ file 'qt_headsuptoolbar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/utils/qt_headsuptoolbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_headsuptoolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__QtToolButton_t {
    QByteArrayData data[3];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__QtToolButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__QtToolButton_t qt_meta_stringdata_VSN__QtVision__QtToolButton = {
    {
QT_MOC_LITERAL(0, 0, 27), // "VSN::QtVision::QtToolButton"
QT_MOC_LITERAL(1, 28, 13), // "currentAction"
QT_MOC_LITERAL(2, 42, 0) // ""

    },
    "VSN::QtVision::QtToolButton\0currentAction\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__QtToolButton[] = {

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
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void VSN::QtVision::QtToolButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtToolButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::QtToolButton::staticMetaObject = { {
    &QToolButton::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__QtToolButton.data,
    qt_meta_data_VSN__QtVision__QtToolButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::QtToolButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::QtToolButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__QtToolButton.stringdata0))
        return static_cast<void*>(this);
    return QToolButton::qt_metacast(_clname);
}

int VSN::QtVision::QtToolButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__QtAutoHideWindow_t {
    QByteArrayData data[7];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__QtAutoHideWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__QtAutoHideWindow_t qt_meta_stringdata_VSN__QtVision__QtAutoHideWindow = {
    {
QT_MOC_LITERAL(0, 0, 31), // "VSN::QtVision::QtAutoHideWindow"
QT_MOC_LITERAL(1, 32, 19), // "allowedAreasChanged"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 16), // "Qt::ToolBarAreas"
QT_MOC_LITERAL(4, 70, 12), // "allowedAreas"
QT_MOC_LITERAL(5, 83, 15), // "iconSizeChanged"
QT_MOC_LITERAL(6, 99, 8) // "iconSize"

    },
    "VSN::QtVision::QtAutoHideWindow\0"
    "allowedAreasChanged\0\0Qt::ToolBarAreas\0"
    "allowedAreas\0iconSizeChanged\0iconSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__QtAutoHideWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x09 /* Protected */,
       5,    1,   27,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QSize,    6,

       0        // eod
};

void VSN::QtVision::QtAutoHideWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtAutoHideWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->allowedAreasChanged((*reinterpret_cast< Qt::ToolBarAreas(*)>(_a[1]))); break;
        case 1: _t->iconSizeChanged((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::QtAutoHideWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__QtAutoHideWindow.data,
    qt_meta_data_VSN__QtVision__QtAutoHideWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::QtAutoHideWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::QtAutoHideWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__QtAutoHideWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VSN::QtVision::QtAutoHideWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
