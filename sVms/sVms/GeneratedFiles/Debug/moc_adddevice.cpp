/****************************************************************************
** Meta object code from reading C++ file 'adddevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../adddevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adddevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddDevice_t {
    QByteArrayData data[7];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddDevice_t qt_meta_stringdata_AddDevice = {
    {
QT_MOC_LITERAL(0, 0, 9), // "AddDevice"
QT_MOC_LITERAL(1, 10, 18), // "on_btnSure_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 29), // "on_radioButton_paragr_clicked"
QT_MOC_LITERAL(4, 60, 27), // "on_radioButton_name_clicked"
QT_MOC_LITERAL(5, 88, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(6, 109, 19) // "on_btnClose_clicked"

    },
    "AddDevice\0on_btnSure_clicked\0\0"
    "on_radioButton_paragr_clicked\0"
    "on_radioButton_name_clicked\0"
    "on_btnCancel_clicked\0on_btnClose_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddDevice *_t = static_cast<AddDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnSure_clicked(); break;
        case 1: _t->on_radioButton_paragr_clicked(); break;
        case 2: _t->on_radioButton_name_clicked(); break;
        case 3: _t->on_btnCancel_clicked(); break;
        case 4: _t->on_btnClose_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AddDevice::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AddDevice.data,
      qt_meta_data_AddDevice,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AddDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AddDevice.stringdata0))
        return static_cast<void*>(const_cast< AddDevice*>(this));
    return QWidget::qt_metacast(_clname);
}

int AddDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
