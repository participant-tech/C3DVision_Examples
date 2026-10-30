/****************************************************************************
** Meta object code from reading C++ file 'qt_materialprop.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/propeditor/qt_materialprop.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_materialprop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__MaterialPropManager_t {
    QByteArrayData data[16];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__MaterialPropManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__MaterialPropManager_t qt_meta_stringdata_VSN__QtVision__MaterialPropManager = {
    {
QT_MOC_LITERAL(0, 0, 34), // "VSN::QtVision::MaterialPropMa..."
QT_MOC_LITERAL(1, 35, 13), // "applyMaterial"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 8), // "Material"
QT_MOC_LITERAL(4, 59, 8), // "material"
QT_MOC_LITERAL(5, 68, 15), // "materialChanged"
QT_MOC_LITERAL(6, 84, 15), // "const Material*"
QT_MOC_LITERAL(7, 100, 19), // "modificationChanged"
QT_MOC_LITERAL(8, 120, 1), // "m"
QT_MOC_LITERAL(9, 122, 11), // "setMaterial"
QT_MOC_LITERAL(10, 134, 11), // "setModified"
QT_MOC_LITERAL(11, 146, 10), // "isModified"
QT_MOC_LITERAL(12, 157, 19), // "slotPropertyChanged"
QT_MOC_LITERAL(13, 177, 19), // "QtVision::Property*"
QT_MOC_LITERAL(14, 197, 8), // "property"
QT_MOC_LITERAL(15, 206, 17) // "slotApplyMaterial"

    },
    "VSN::QtVision::MaterialPropManager\0"
    "applyMaterial\0\0Material\0material\0"
    "materialChanged\0const Material*\0"
    "modificationChanged\0m\0setMaterial\0"
    "setModified\0isModified\0slotPropertyChanged\0"
    "QtVision::Property*\0property\0"
    "slotApplyMaterial"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__MaterialPropManager[] = {

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
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   63,    2, 0x0a /* Public */,
      10,    1,   66,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x2a /* Public | MethodCloned */,
      12,    1,   70,    2, 0x09 /* Protected */,
      15,    0,   73,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, QMetaType::Bool,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void VSN::QtVision::MaterialPropManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MaterialPropManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->applyMaterial((*reinterpret_cast< const Material(*)>(_a[1]))); break;
        case 1: _t->materialChanged((*reinterpret_cast< const Material*(*)>(_a[1]))); break;
        case 2: _t->modificationChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setMaterial((*reinterpret_cast< const Material*(*)>(_a[1]))); break;
        case 4: _t->setModified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setModified(); break;
        case 6: _t->slotPropertyChanged((*reinterpret_cast< QtVision::Property*(*)>(_a[1]))); break;
        case 7: _t->slotApplyMaterial(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MaterialPropManager::*)(const Material & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MaterialPropManager::applyMaterial)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MaterialPropManager::*)(const Material * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MaterialPropManager::materialChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MaterialPropManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MaterialPropManager::modificationChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::MaterialPropManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__MaterialPropManager.data,
    qt_meta_data_VSN__QtVision__MaterialPropManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::MaterialPropManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::MaterialPropManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__MaterialPropManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VSN::QtVision::MaterialPropManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::MaterialPropManager::applyMaterial(const Material & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSN::QtVision::MaterialPropManager::materialChanged(const Material * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VSN::QtVision::MaterialPropManager::modificationChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
