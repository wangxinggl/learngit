/****************************************************************************
** Meta object code from reading C++ file 'StreamSet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../StreamSet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StreamSet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StreamSet_t {
    QByteArrayData data[9];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StreamSet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StreamSet_t qt_meta_stringdata_StreamSet = {
    {
QT_MOC_LITERAL(0, 0, 9), // "StreamSet"
QT_MOC_LITERAL(1, 10, 28), // "on_comboBox_ChanNo_activated"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "index"
QT_MOC_LITERAL(4, 46, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(5, 65, 21), // "on_btnUpGrade_clicked"
QT_MOC_LITERAL(6, 87, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(7, 107, 32), // "on_comboBox_CodeFormat_activated"
QT_MOC_LITERAL(8, 140, 28) // "on_comboBox_Expand_activated"

    },
    "StreamSet\0on_comboBox_ChanNo_activated\0"
    "\0index\0on_btnSave_clicked\0"
    "on_btnUpGrade_clicked\0on_btnClose_clicked\0"
    "on_comboBox_CodeFormat_activated\0"
    "on_comboBox_Expand_activated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StreamSet[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    0,   47,    2, 0x08 /* Private */,
       5,    0,   48,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,
       7,    1,   50,    2, 0x08 /* Private */,
       8,    1,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void StreamSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StreamSet *_t = static_cast<StreamSet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_comboBox_ChanNo_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_btnSave_clicked(); break;
        case 2: _t->on_btnUpGrade_clicked(); break;
        case 3: _t->on_btnClose_clicked(); break;
        case 4: _t->on_comboBox_CodeFormat_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_comboBox_Expand_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject StreamSet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StreamSet.data,
      qt_meta_data_StreamSet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StreamSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StreamSet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StreamSet.stringdata0))
        return static_cast<void*>(const_cast< StreamSet*>(this));
    return QDialog::qt_metacast(_clname);
}

int StreamSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
