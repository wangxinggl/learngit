/****************************************************************************
** Meta object code from reading C++ file 'ConfigNetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ConfigNetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfigNetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigNetwork_t {
    QByteArrayData data[13];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigNetwork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigNetwork_t qt_meta_stringdata_ConfigNetwork = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ConfigNetwork"
QT_MOC_LITERAL(1, 14, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(4, 54, 21), // "on_btnUpGrade_clicked"
QT_MOC_LITERAL(5, 76, 28), // "on_lineEdit_MAC6_textChanged"
QT_MOC_LITERAL(6, 105, 4), // "arg1"
QT_MOC_LITERAL(7, 110, 31), // "on_lineEdit_TCPPORT_textChanged"
QT_MOC_LITERAL(8, 142, 32), // "on_lineEdit_HTTPPORT_textChanged"
QT_MOC_LITERAL(9, 175, 22), // "on_btnDownSave_clicked"
QT_MOC_LITERAL(10, 198, 30), // "on_checkBox_DHCPEnable_clicked"
QT_MOC_LITERAL(11, 229, 21), // "on_btnDNSSave_clicked"
QT_MOC_LITERAL(12, 251, 20) // "on_btnIPSave_clicked"

    },
    "ConfigNetwork\0on_btnClose_clicked\0\0"
    "on_btnSave_clicked\0on_btnUpGrade_clicked\0"
    "on_lineEdit_MAC6_textChanged\0arg1\0"
    "on_lineEdit_TCPPORT_textChanged\0"
    "on_lineEdit_HTTPPORT_textChanged\0"
    "on_btnDownSave_clicked\0"
    "on_checkBox_DHCPEnable_clicked\0"
    "on_btnDNSSave_clicked\0on_btnIPSave_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigNetwork[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    1,   67,    2, 0x08 /* Private */,
       7,    1,   70,    2, 0x08 /* Private */,
       8,    1,   73,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConfigNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConfigNetwork *_t = static_cast<ConfigNetwork *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnClose_clicked(); break;
        case 1: _t->on_btnSave_clicked(); break;
        case 2: _t->on_btnUpGrade_clicked(); break;
        case 3: _t->on_lineEdit_MAC6_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_lineEdit_TCPPORT_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_lineEdit_HTTPPORT_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_btnDownSave_clicked(); break;
        case 7: _t->on_checkBox_DHCPEnable_clicked(); break;
        case 8: _t->on_btnDNSSave_clicked(); break;
        case 9: _t->on_btnIPSave_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ConfigNetwork::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConfigNetwork.data,
      qt_meta_data_ConfigNetwork,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConfigNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigNetwork.stringdata0))
        return static_cast<void*>(const_cast< ConfigNetwork*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConfigNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
