/****************************************************************************
** Meta object code from reading C++ file 'ParamMeteSet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ParamMeteSet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParamMeteSet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParamMeteSet_t {
    QByteArrayData data[10];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParamMeteSet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParamMeteSet_t qt_meta_stringdata_ParamMeteSet = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ParamMeteSet"
QT_MOC_LITERAL(1, 13, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 30), // "on_comboBox_SNAPMODE_activated"
QT_MOC_LITERAL(4, 65, 5), // "index"
QT_MOC_LITERAL(5, 71, 33), // "on_comboBox_FACEPICNAME_activ..."
QT_MOC_LITERAL(6, 105, 31), // "on_comboBox_PRIVATEUP_activated"
QT_MOC_LITERAL(7, 137, 29), // "on_comboBox_PICMODE_activated"
QT_MOC_LITERAL(8, 167, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(9, 186, 20) // "on_btnUpdate_clicked"

    },
    "ParamMeteSet\0on_btnClose_clicked\0\0"
    "on_comboBox_SNAPMODE_activated\0index\0"
    "on_comboBox_FACEPICNAME_activated\0"
    "on_comboBox_PRIVATEUP_activated\0"
    "on_comboBox_PICMODE_activated\0"
    "on_btnSave_clicked\0on_btnUpdate_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParamMeteSet[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    1,   50,    2, 0x08 /* Private */,
       5,    1,   53,    2, 0x08 /* Private */,
       6,    1,   56,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ParamMeteSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParamMeteSet *_t = static_cast<ParamMeteSet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnClose_clicked(); break;
        case 1: _t->on_comboBox_SNAPMODE_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_comboBox_FACEPICNAME_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_comboBox_PRIVATEUP_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_comboBox_PICMODE_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_btnSave_clicked(); break;
        case 6: _t->on_btnUpdate_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ParamMeteSet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ParamMeteSet.data,
      qt_meta_data_ParamMeteSet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ParamMeteSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParamMeteSet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ParamMeteSet.stringdata0))
        return static_cast<void*>(const_cast< ParamMeteSet*>(this));
    return QDialog::qt_metacast(_clname);
}

int ParamMeteSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
