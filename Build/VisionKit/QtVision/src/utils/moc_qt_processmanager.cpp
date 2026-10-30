/****************************************************************************
** Meta object code from reading C++ file 'qt_processmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../VisionKit/QtVision/src/utils/qt_processmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_processmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VSN__QtVision__ProcessManager_t {
    QByteArrayData data[12];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSN__QtVision__ProcessManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSN__QtVision__ProcessManager_t qt_meta_stringdata_VSN__QtVision__ProcessManager = {
    {
QT_MOC_LITERAL(0, 0, 29), // "VSN::QtVision::ProcessManager"
QT_MOC_LITERAL(1, 30, 21), // "suspendProcessChanged"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 11), // "ProcessType"
QT_MOC_LITERAL(4, 65, 6), // "pt_Pan"
QT_MOC_LITERAL(5, 72, 8), // "pt_Orbit"
QT_MOC_LITERAL(6, 81, 9), // "pt_Rotate"
QT_MOC_LITERAL(7, 91, 18), // "pt_ComplexRotation"
QT_MOC_LITERAL(8, 110, 7), // "pt_Zoom"
QT_MOC_LITERAL(9, 118, 10), // "pt_ZoomBox"
QT_MOC_LITERAL(10, 129, 13), // "pt_AllProcess"
QT_MOC_LITERAL(11, 143, 12) // "ProcessTypes"

    },
    "VSN::QtVision::ProcessManager\0"
    "suspendProcessChanged\0\0ProcessType\0"
    "pt_Pan\0pt_Orbit\0pt_Rotate\0pt_ComplexRotation\0"
    "pt_Zoom\0pt_ZoomBox\0pt_AllProcess\0"
    "ProcessTypes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSN__QtVision__ProcessManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       2,   20, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // enums: name, alias, flags, count, data
       3,    3, 0x0,    7,   30,
      11,    3, 0x1,    7,   44,

 // enum data: key, value
       4, uint(VSN::QtVision::ProcessManager::pt_Pan),
       5, uint(VSN::QtVision::ProcessManager::pt_Orbit),
       6, uint(VSN::QtVision::ProcessManager::pt_Rotate),
       7, uint(VSN::QtVision::ProcessManager::pt_ComplexRotation),
       8, uint(VSN::QtVision::ProcessManager::pt_Zoom),
       9, uint(VSN::QtVision::ProcessManager::pt_ZoomBox),
      10, uint(VSN::QtVision::ProcessManager::pt_AllProcess),
       4, uint(VSN::QtVision::ProcessManager::pt_Pan),
       5, uint(VSN::QtVision::ProcessManager::pt_Orbit),
       6, uint(VSN::QtVision::ProcessManager::pt_Rotate),
       7, uint(VSN::QtVision::ProcessManager::pt_ComplexRotation),
       8, uint(VSN::QtVision::ProcessManager::pt_Zoom),
       9, uint(VSN::QtVision::ProcessManager::pt_ZoomBox),
      10, uint(VSN::QtVision::ProcessManager::pt_AllProcess),

       0        // eod
};

void VSN::QtVision::ProcessManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProcessManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->suspendProcessChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProcessManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProcessManager::suspendProcessChanged)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VSN::QtVision::ProcessManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VSN__QtVision__ProcessManager.data,
    qt_meta_data_VSN__QtVision__ProcessManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VSN::QtVision::ProcessManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSN::QtVision::ProcessManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VSN__QtVision__ProcessManager.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Object"))
        return static_cast< Object*>(this);
    return QObject::qt_metacast(_clname);
}

int VSN::QtVision::ProcessManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void VSN::QtVision::ProcessManager::suspendProcessChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
