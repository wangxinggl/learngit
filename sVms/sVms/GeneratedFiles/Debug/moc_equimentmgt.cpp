/****************************************************************************
** Meta object code from reading C++ file 'equimentmgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../equimentmgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'equimentmgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_equimentMgt_t {
    QByteArrayData data[15];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_equimentMgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_equimentMgt_t qt_meta_stringdata_equimentMgt = {
    {
QT_MOC_LITERAL(0, 0, 11), // "equimentMgt"
QT_MOC_LITERAL(1, 12, 13), // "startMyThread"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 21), // "on_btnRefresh_clicked"
QT_MOC_LITERAL(4, 49, 20), // "on_btnSearch_clicked"
QT_MOC_LITERAL(5, 70, 17), // "on_btnAdd_clicked"
QT_MOC_LITERAL(6, 88, 20), // "on_btnAddall_clicked"
QT_MOC_LITERAL(7, 109, 17), // "on_btnDel_clicked"
QT_MOC_LITERAL(8, 127, 20), // "slotRowDoubleClicked"
QT_MOC_LITERAL(9, 148, 19), // "on_btnClear_clicked"
QT_MOC_LITERAL(10, 168, 19), // "on_btnaddEq_clicked"
QT_MOC_LITERAL(11, 188, 20), // "on_btnModify_clicked"
QT_MOC_LITERAL(12, 209, 24), // "on_checkBox_stateChanged"
QT_MOC_LITERAL(13, 234, 5), // "state"
QT_MOC_LITERAL(14, 240, 22) // "on_btnSearchIP_clicked"

    },
    "equimentMgt\0startMyThread\0\0"
    "on_btnRefresh_clicked\0on_btnSearch_clicked\0"
    "on_btnAdd_clicked\0on_btnAddall_clicked\0"
    "on_btnDel_clicked\0slotRowDoubleClicked\0"
    "on_btnClear_clicked\0on_btnaddEq_clicked\0"
    "on_btnModify_clicked\0on_checkBox_stateChanged\0"
    "state\0on_btnSearchIP_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_equimentMgt[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    1,   84,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

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
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,

       0        // eod
};

void equimentMgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        equimentMgt *_t = static_cast<equimentMgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startMyThread(); break;
        case 1: _t->on_btnRefresh_clicked(); break;
        case 2: _t->on_btnSearch_clicked(); break;
        case 3: _t->on_btnAdd_clicked(); break;
        case 4: _t->on_btnAddall_clicked(); break;
        case 5: _t->on_btnDel_clicked(); break;
        case 6: _t->slotRowDoubleClicked(); break;
        case 7: _t->on_btnClear_clicked(); break;
        case 8: _t->on_btnaddEq_clicked(); break;
        case 9: _t->on_btnModify_clicked(); break;
        case 10: _t->on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_btnSearchIP_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (equimentMgt::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&equimentMgt::startMyThread)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject equimentMgt::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_equimentMgt.data,
      qt_meta_data_equimentMgt,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *equimentMgt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *equimentMgt::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_equimentMgt.stringdata0))
        return static_cast<void*>(const_cast< equimentMgt*>(this));
    return QWidget::qt_metacast(_clname);
}

int equimentMgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void equimentMgt::startMyThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
