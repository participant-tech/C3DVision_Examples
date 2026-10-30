/****************************************************************************
** Meta object code from reading C++ file 'qt_openglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/core/qt_openglwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_openglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWidget_t {
    QByteArrayData data[9];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWidget_t qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWidget = {
    {
QT_MOC_LITERAL(0, 0, 34), // "VSN::QtVision::QtOpenGLSceneW..."
QT_MOC_LITERAL(1, 35, 19), // "initializeRendering"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 18), // "showCompanyWebSite"
QT_MOC_LITERAL(4, 75, 16), // "viewPortCommands"
QT_MOC_LITERAL(5, 92, 18), // "viewPortRenderMode"
QT_MOC_LITERAL(6, 111, 13), // "setRenderMode"
QT_MOC_LITERAL(7, 125, 10), // "RenderMode"
QT_MOC_LITERAL(8, 136, 4) // "mode"

    },
    "VSN::QtVision::QtOpenGLSceneWidget\0"
    "initializeRendering\0\0showCompanyWebSite\0"
    "viewPortCommands\0viewPortRenderMode\0"
    "setRenderMode\0RenderMode\0mode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__QtOpenGLSceneWidget[] = {

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
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void VSN::QtVision::QtOpenGLSceneWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtOpenGLSceneWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initializeRendering(); break;
        case 1: _t->showCompanyWebSite(); break;
        case 2: _t->viewPortCommands(); break;
        case 3: _t->viewPortRenderMode(); break;
        case 4: _t->setRenderMode((*reinterpret_cast< RenderMode(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtOpenGLSceneWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtOpenGLSceneWidget::initializeRendering)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::QtOpenGLSceneWidget::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWidget.data,
    qt_meta_data_VSN__QtVision__QtOpenGLSceneWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::QtOpenGLSceneWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::QtOpenGLSceneWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__QtOpenGLSceneWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Object"))
        return static_cast< Object*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int VSN::QtVision::QtOpenGLSceneWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::QtOpenGLSceneWidget::initializeRendering()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
