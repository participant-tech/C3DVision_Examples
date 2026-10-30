/****************************************************************************
** Meta object code from reading C++ file 'qt_mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/core/qt_mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__QtMainWindow_t {
    QByteArrayData data[21];
    char stringdata0[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__QtMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__QtMainWindow_t qt_meta_stringdata_VSN__QtVision__QtMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 27), // "VSN::QtVision::QtMainWindow"
QT_MOC_LITERAL(1, 28, 12), // "openNewModel"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 17), // "MxModelExtension*"
QT_MOC_LITERAL(4, 60, 5), // "model"
QT_MOC_LITERAL(5, 66, 24), // "currentIndexThemeChanged"
QT_MOC_LITERAL(6, 91, 5), // "index"
QT_MOC_LITERAL(7, 97, 18), // "setVisibleProgress"
QT_MOC_LITERAL(8, 116, 13), // "buildProgress"
QT_MOC_LITERAL(9, 130, 16), // "setProgressRange"
QT_MOC_LITERAL(10, 147, 7), // "minimum"
QT_MOC_LITERAL(11, 155, 7), // "maximum"
QT_MOC_LITERAL(12, 163, 13), // "resetProgress"
QT_MOC_LITERAL(13, 177, 4), // "open"
QT_MOC_LITERAL(14, 182, 4), // "save"
QT_MOC_LITERAL(15, 187, 6), // "saveAs"
QT_MOC_LITERAL(16, 194, 23), // "updateRecentFileActions"
QT_MOC_LITERAL(17, 218, 14), // "openRecentFile"
QT_MOC_LITERAL(18, 233, 20), // "setCurrentIndexTheme"
QT_MOC_LITERAL(19, 254, 24), // "setVisibleInfoAboutScene"
QT_MOC_LITERAL(20, 279, 9) // "isVisible"

    },
    "VSN::QtVision::QtMainWindow\0openNewModel\0"
    "\0MxModelExtension*\0model\0"
    "currentIndexThemeChanged\0index\0"
    "setVisibleProgress\0buildProgress\0"
    "setProgressRange\0minimum\0maximum\0"
    "resetProgress\0open\0save\0saveAs\0"
    "updateRecentFileActions\0openRecentFile\0"
    "setCurrentIndexTheme\0setVisibleInfoAboutScene\0"
    "isVisible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__QtMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    1,   82,    2, 0x06 /* Public */,
       7,    1,   85,    2, 0x06 /* Public */,
       8,    1,   88,    2, 0x06 /* Public */,
       9,    2,   91,    2, 0x06 /* Public */,
      12,    0,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   97,    2, 0x0a /* Public */,
      14,    0,   98,    2, 0x0a /* Public */,
      15,    0,   99,    2, 0x0a /* Public */,
      16,    0,  100,    2, 0x0a /* Public */,
      17,    0,  101,    2, 0x0a /* Public */,
      18,    1,  102,    2, 0x0a /* Public */,
      19,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,   20,

       0        // eod
};

void VSN::QtVision::QtMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openNewModel((*reinterpret_cast< MxModelExtension*(*)>(_a[1]))); break;
        case 1: _t->currentIndexThemeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setVisibleProgress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->buildProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setProgressRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->resetProgress(); break;
        case 6: _t->open(); break;
        case 7: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->saveAs(); break;
        case 9: _t->updateRecentFileActions(); break;
        case 10: _t->openRecentFile(); break;
        case 11: _t->setCurrentIndexTheme((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setVisibleInfoAboutScene((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtMainWindow::*)(MxModelExtension * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtMainWindow::openNewModel)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtMainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtMainWindow::currentIndexThemeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QtMainWindow::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtMainWindow::setVisibleProgress)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QtMainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtMainWindow::buildProgress)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QtMainWindow::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtMainWindow::setProgressRange)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QtMainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtMainWindow::resetProgress)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::QtMainWindow::staticMetaObject = { {
    &QtAppMainWindow::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__QtMainWindow.data,
    qt_meta_data_VSN__QtVision__QtMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::QtMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::QtMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__QtMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QtAppMainWindow::qt_metacast(_clname);
}

int VSN::QtVision::QtMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtAppMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void VSN::QtVision::QtMainWindow::openNewModel(MxModelExtension * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::QtMainWindow::currentIndexThemeChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::QtMainWindow::setVisibleProgress(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VSN::QtVision::QtMainWindow::buildProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VSN::QtVision::QtMainWindow::setProgressRange(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VSN::QtVision::QtMainWindow::resetProgress()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
