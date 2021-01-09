/****************************************************************************
** Meta object code from reading C++ file 'changeskin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../changeskin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'changeskin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_changeSkin_t {
    QByteArrayData data[13];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_changeSkin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_changeSkin_t qt_meta_stringdata_changeSkin = {
    {
QT_MOC_LITERAL(0, 0, 10), // "changeSkin"
QT_MOC_LITERAL(1, 11, 22), // "on_black_label_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 20), // "on_mei_label_clicked"
QT_MOC_LITERAL(4, 56, 20), // "on_sky_label_clicked"
QT_MOC_LITERAL(5, 77, 20), // "on_hui_label_clicked"
QT_MOC_LITERAL(6, 98, 21), // "on_gray_label_clicked"
QT_MOC_LITERAL(7, 120, 27), // "on_wathetgray_label_clicked"
QT_MOC_LITERAL(8, 148, 25), // "on_darkgray_label_clicked"
QT_MOC_LITERAL(9, 174, 23), // "on_sliver_label_clicked"
QT_MOC_LITERAL(10, 198, 26), // "on_flatblack_label_clicked"
QT_MOC_LITERAL(11, 225, 26), // "on_darkblack_label_clicked"
QT_MOC_LITERAL(12, 252, 19) // "on_btnClose_clicked"

    },
    "changeSkin\0on_black_label_clicked\0\0"
    "on_mei_label_clicked\0on_sky_label_clicked\0"
    "on_hui_label_clicked\0on_gray_label_clicked\0"
    "on_wathetgray_label_clicked\0"
    "on_darkgray_label_clicked\0"
    "on_sliver_label_clicked\0"
    "on_flatblack_label_clicked\0"
    "on_darkblack_label_clicked\0"
    "on_btnClose_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_changeSkin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void changeSkin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        changeSkin *_t = static_cast<changeSkin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_black_label_clicked(); break;
        case 1: _t->on_mei_label_clicked(); break;
        case 2: _t->on_sky_label_clicked(); break;
        case 3: _t->on_hui_label_clicked(); break;
        case 4: _t->on_gray_label_clicked(); break;
        case 5: _t->on_wathetgray_label_clicked(); break;
        case 6: _t->on_darkgray_label_clicked(); break;
        case 7: _t->on_sliver_label_clicked(); break;
        case 8: _t->on_flatblack_label_clicked(); break;
        case 9: _t->on_darkblack_label_clicked(); break;
        case 10: _t->on_btnClose_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject changeSkin::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_changeSkin.data,
      qt_meta_data_changeSkin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *changeSkin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *changeSkin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_changeSkin.stringdata0))
        return static_cast<void*>(const_cast< changeSkin*>(this));
    return QDialog::qt_metacast(_clname);
}

int changeSkin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
