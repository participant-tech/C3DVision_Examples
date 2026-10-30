/****************************************************************************
** Meta object code from reading C++ file 'qt_modeldocument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/modeleditor/qt_modeldocument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_modeldocument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__ModelDocument_t {
    QByteArrayData data[12];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__ModelDocument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__ModelDocument_t qt_meta_stringdata_VSN__QtVision__ModelDocument = {
    {
QT_MOC_LITERAL(0, 0, 28), // "VSN::QtVision::ModelDocument"
QT_MOC_LITERAL(1, 29, 15), // "contentsChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 17), // "MxModelExtension*"
QT_MOC_LITERAL(4, 64, 8), // "pModelEx"
QT_MOC_LITERAL(5, 73, 11), // "modelLoaded"
QT_MOC_LITERAL(6, 85, 18), // "numReadFileChanged"
QT_MOC_LITERAL(7, 104, 7), // "numFile"
QT_MOC_LITERAL(8, 112, 19), // "modificationChanged"
QT_MOC_LITERAL(9, 132, 1), // "m"
QT_MOC_LITERAL(10, 134, 11), // "setModified"
QT_MOC_LITERAL(11, 146, 10) // "isModified"

    },
    "VSN::QtVision::ModelDocument\0"
    "contentsChanged\0\0MxModelExtension*\0"
    "pModelEx\0modelLoaded\0numReadFileChanged\0"
    "numFile\0modificationChanged\0m\0setModified\0"
    "isModified"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__ModelDocument[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       8,    1,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   56,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Bool,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,

       0        // eod
};

void VSN::QtVision::ModelDocument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModelDocument *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->contentsChanged((*reinterpret_cast< MxModelExtension*(*)>(_a[1]))); break;
        case 1: _t->modelLoaded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->numReadFileChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->modificationChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setModified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setModified(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ModelDocument::*)(MxModelExtension * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModelDocument::contentsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ModelDocument::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModelDocument::modelLoaded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ModelDocument::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModelDocument::numReadFileChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ModelDocument::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModelDocument::modificationChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::ModelDocument::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__ModelDocument.data,
    qt_meta_data_VSN__QtVision__ModelDocument,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::ModelDocument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::ModelDocument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__ModelDocument.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VSN::QtVision::ModelDocument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::ModelDocument::contentsChanged(MxModelExtension * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::ModelDocument::modelLoaded(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::ModelDocument::numReadFileChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VSN::QtVision::ModelDocument::modificationChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
