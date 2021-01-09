/****************************************************************************
** Meta object code from reading C++ file 'systemset.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../systemset.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_systemSet_t {
    QByteArrayData data[13];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_systemSet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_systemSet_t qt_meta_stringdata_systemSet = {
    {
QT_MOC_LITERAL(0, 0, 9), // "systemSet"
QT_MOC_LITERAL(1, 10, 26), // "on_toolButton_Face_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 28), // "on_toolButton_screen_clicked"
QT_MOC_LITERAL(4, 67, 30), // "on_toolButton_download_clicked"
QT_MOC_LITERAL(5, 98, 17), // "on_btnSet_clicked"
QT_MOC_LITERAL(6, 116, 23), // "on_btnRecordSet_clicked"
QT_MOC_LITERAL(7, 140, 23), // "on_btnAlarmOpen_clicked"
QT_MOC_LITERAL(8, 164, 22), // "on_btnAlarmSet_clicked"
QT_MOC_LITERAL(9, 187, 20), // "on_btnpreSet_clicked"
QT_MOC_LITERAL(10, 208, 26), // "CbnSelchangeCmbAlarmsource"
QT_MOC_LITERAL(11, 235, 4), // "nSel"
QT_MOC_LITERAL(12, 240, 19) // "on_btnClose_clicked"

    },
    "systemSet\0on_toolButton_Face_clicked\0"
    "\0on_toolButton_screen_clicked\0"
    "on_toolButton_download_clicked\0"
    "on_btnSet_clicked\0on_btnRecordSet_clicked\0"
    "on_btnAlarmOpen_clicked\0on_btnAlarmSet_clicked\0"
    "on_btnpreSet_clicked\0CbnSelchangeCmbAlarmsource\0"
    "nSel\0on_btnClose_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_systemSet[] = {

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
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    1,   72,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,

       0        // eod
};

void systemSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        systemSet *_t = static_cast<systemSet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_toolButton_Face_clicked(); break;
        case 1: _t->on_toolButton_screen_clicked(); break;
        case 2: _t->on_toolButton_download_clicked(); break;
        case 3: _t->on_btnSet_clicked(); break;
        case 4: _t->on_btnRecordSet_clicked(); break;
        case 5: _t->on_btnAlarmOpen_clicked(); break;
        case 6: _t->on_btnAlarmSet_clicked(); break;
        case 7: _t->on_btnpreSet_clicked(); break;
        case 8: _t->CbnSelchangeCmbAlarmsource((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_btnClose_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject systemSet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_systemSet.data,
      qt_meta_data_systemSet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *systemSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *systemSet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_systemSet.stringdata0))
        return static_cast<void*>(const_cast< systemSet*>(this));
    return QDialog::qt_metacast(_clname);
}

int systemSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
