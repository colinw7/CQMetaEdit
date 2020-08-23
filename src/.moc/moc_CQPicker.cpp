/****************************************************************************
** Meta object code from reading C++ file 'CQPicker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/CQPicker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQPicker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CQPicker_t {
    QByteArrayData data[18];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQPicker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQPicker_t qt_meta_stringdata_CQPicker = {
    {
QT_MOC_LITERAL(0, 0, 8), // "CQPicker"
QT_MOC_LITERAL(1, 9, 13), // "objectTouched"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "pObject"
QT_MOC_LITERAL(4, 32, 13), // "widgetTouched"
QT_MOC_LITERAL(5, 46, 8), // "QWidget*"
QT_MOC_LITERAL(6, 55, 7), // "pWidget"
QT_MOC_LITERAL(7, 63, 9), // "startPick"
QT_MOC_LITERAL(8, 73, 7), // "endPick"
QT_MOC_LITERAL(9, 81, 8), // "position"
QT_MOC_LITERAL(10, 90, 7), // "globalX"
QT_MOC_LITERAL(11, 98, 7), // "globalY"
QT_MOC_LITERAL(12, 106, 6), // "localX"
QT_MOC_LITERAL(13, 113, 6), // "localY"
QT_MOC_LITERAL(14, 120, 14), // "globalPosition"
QT_MOC_LITERAL(15, 135, 12), // "objectPicked"
QT_MOC_LITERAL(16, 148, 12), // "widgetPicked"
QT_MOC_LITERAL(17, 161, 4) // "size"

    },
    "CQPicker\0objectTouched\0\0pObject\0"
    "widgetTouched\0QWidget*\0pWidget\0startPick\0"
    "endPick\0position\0globalX\0globalY\0"
    "localX\0localY\0globalPosition\0objectPicked\0"
    "widgetPicked\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQPicker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       1,   82, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       7,    0,   60,    2, 0x06 /* Public */,
       8,    0,   61,    2, 0x06 /* Public */,
       9,    4,   62,    2, 0x06 /* Public */,
      14,    2,   71,    2, 0x06 /* Public */,
      15,    1,   76,    2, 0x06 /* Public */,
      16,    1,   79,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::QObjectStar,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // properties: name, type, flags
      17, QMetaType::Int, 0x00095103,

       0        // eod
};

void CQPicker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CQPicker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->objectTouched((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 1: _t->widgetTouched((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->startPick(); break;
        case 3: _t->endPick(); break;
        case 4: _t->position((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->globalPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->objectPicked((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: _t->widgetPicked((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CQPicker::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQPicker::objectTouched)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CQPicker::*)(QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQPicker::widgetTouched)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CQPicker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQPicker::startPick)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CQPicker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQPicker::endPick)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CQPicker::*)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQPicker::position)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CQPicker::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQPicker::globalPosition)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CQPicker::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQPicker::objectPicked)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CQPicker::*)(QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CQPicker::widgetPicked)) {
                *result = 7;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CQPicker *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->size(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CQPicker *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSize(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject CQPicker::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_CQPicker.data,
    qt_meta_data_CQPicker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CQPicker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQPicker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CQPicker.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int CQPicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CQPicker::objectTouched(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CQPicker::widgetTouched(QWidget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CQPicker::startPick()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CQPicker::endPick()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CQPicker::position(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CQPicker::globalPosition(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CQPicker::objectPicked(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CQPicker::widgetPicked(QWidget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
