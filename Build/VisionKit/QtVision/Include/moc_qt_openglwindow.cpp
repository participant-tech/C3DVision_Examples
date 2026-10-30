/****************************************************************************
** Meta object code from reading C++ file 'qt_openglwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../VisionKit/QtVision/Include/qt_openglwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_openglwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__QtOpenGLWindow_t {
    QByteArrayData data[7];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__QtOpenGLWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__QtOpenGLWindow_t qt_meta_stringdata_VSN__QtVision__QtOpenGLWindow = {
    {
QT_MOC_LITERAL(0, 0, 29), // "VSN::QtVision::QtOpenGLWindow"
QT_MOC_LITERAL(1, 30, 11), // "renderLater"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 9), // "renderNow"
QT_MOC_LITERAL(4, 53, 15), // "onMessageLogged"
QT_MOC_LITERAL(5, 69, 19), // "QOpenGLDebugMessage"
QT_MOC_LITERAL(6, 89, 3) // "msg"

    },
    "VSN::QtVision::QtOpenGLWindow\0renderLater\0"
    "\0renderNow\0onMessageLogged\0"
    "QOpenGLDebugMessage\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__QtOpenGLWindow[] = {

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
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void VSN::QtVision::QtOpenGLWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtOpenGLWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->renderLater(); break;
        case 1: _t->renderNow(); break;
        case 2: _t->onMessageLogged((*reinterpret_cast< const QOpenGLDebugMessage(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::QtOpenGLWindow::staticMetaObject = { {
    &QWindow::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__QtOpenGLWindow.data,
    qt_meta_data_VSN__QtVision__QtOpenGLWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::QtOpenGLWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::QtOpenGLWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__QtOpenGLWindow.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Object"))
        return static_cast< Object*>(this);
    return QWindow::qt_metacast(_clname);
}

int VSN::QtVision::QtOpenGLWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWindow::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWindow_t {
    QByteArrayData data[1];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWindow_t qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWindow = {
    {
QT_MOC_LITERAL(0, 0, 34) // "VSN::QtVision::QtOpenGLSceneW..."

    },
    "VSN::QtVision::QtOpenGLSceneWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__QtOpenGLSceneWindow[] = {

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

void VSN::QtVision::QtOpenGLSceneWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::QtOpenGLSceneWindow::staticMetaObject = { {
    &QtOpenGLWindow::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWindow.data,
    qt_meta_data_VSN__QtVision__QtOpenGLSceneWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::QtOpenGLSceneWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::QtOpenGLSceneWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWindow.stringdata0))
        return static_cast<void*>(this);
    return QtOpenGLWindow::qt_metacast(_clname);
}

int VSN::QtVision::QtOpenGLSceneWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtOpenGLWindow::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
