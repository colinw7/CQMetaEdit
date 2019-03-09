/****************************************************************************
** Meta object code from reading C++ file 'CQMetaEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/CQMetaEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQMetaEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CQMetaEdit_t {
    QByteArrayData data[13];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQMetaEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQMetaEdit_t qt_meta_stringdata_CQMetaEdit = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CQMetaEdit"
QT_MOC_LITERAL(1, 11, 12), // "setInherited"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 14), // "loadObjectName"
QT_MOC_LITERAL(4, 40, 10), // "loadParent"
QT_MOC_LITERAL(5, 51, 10), // "pickObject"
QT_MOC_LITERAL(6, 62, 6), // "object"
QT_MOC_LITERAL(7, 69, 12), // "snapshotSlot"
QT_MOC_LITERAL(8, 82, 16), // "focusChangedSlot"
QT_MOC_LITERAL(9, 99, 8), // "QWidget*"
QT_MOC_LITERAL(10, 108, 4), // "oldW"
QT_MOC_LITERAL(11, 113, 4), // "newW"
QT_MOC_LITERAL(12, 118, 9) // "inherited"

    },
    "CQMetaEdit\0setInherited\0\0loadObjectName\0"
    "loadParent\0pickObject\0object\0snapshotSlot\0"
    "focusChangedSlot\0QWidget*\0oldW\0newW\0"
    "inherited"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQMetaEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       1,   58, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       3,    0,   47,    2, 0x08 /* Private */,
       4,    0,   48,    2, 0x08 /* Private */,
       5,    1,   49,    2, 0x08 /* Private */,
       7,    0,   52,    2, 0x08 /* Private */,
       8,    2,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,   10,   11,

 // properties: name, type, flags
      12, QMetaType::Bool, 0x00095103,

       0        // eod
};

void CQMetaEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQMetaEdit *_t = static_cast<CQMetaEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setInherited((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->loadObjectName(); break;
        case 2: _t->loadParent(); break;
        case 3: _t->pickObject((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 4: _t->snapshotSlot(); break;
        case 5: _t->focusChangedSlot((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        CQMetaEdit *_t = static_cast<CQMetaEdit *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->inherited(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CQMetaEdit *_t = static_cast<CQMetaEdit *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setInherited(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject CQMetaEdit::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CQMetaEdit.data,
      qt_meta_data_CQMetaEdit,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CQMetaEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQMetaEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CQMetaEdit.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int CQMetaEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
