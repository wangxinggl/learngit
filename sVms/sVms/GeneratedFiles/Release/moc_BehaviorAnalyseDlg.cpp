/****************************************************************************
** Meta object code from reading C++ file 'BehaviorAnalyseDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BehaviorAnalyseDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BehaviorAnalyseDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BehaviorAnalyseDlg_t {
    QByteArrayData data[15];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BehaviorAnalyseDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BehaviorAnalyseDlg_t qt_meta_stringdata_BehaviorAnalyseDlg = {
    {
QT_MOC_LITERAL(0, 0, 18), // "BehaviorAnalyseDlg"
QT_MOC_LITERAL(1, 19, 25), // "OnlineTreeViewDoubleClick"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 5), // "index"
QT_MOC_LITERAL(4, 52, 20), // "on_btnEncode_clicked"
QT_MOC_LITERAL(5, 73, 17), // "on_btnWeb_clicked"
QT_MOC_LITERAL(6, 91, 21), // "on_btnUpGrade_clicked"
QT_MOC_LITERAL(7, 113, 18), // "on_btnArea_clicked"
QT_MOC_LITERAL(8, 132, 18), // "on_btnFace_clicked"
QT_MOC_LITERAL(9, 151, 21), // "on_btnWarning_clicked"
QT_MOC_LITERAL(10, 173, 21), // "on_btnNetWork_clicked"
QT_MOC_LITERAL(11, 195, 8), // "searchIP"
QT_MOC_LITERAL(12, 204, 26), // "on_btnVideoWarning_clicked"
QT_MOC_LITERAL(13, 231, 22), // "on_btnImageSet_clicked"
QT_MOC_LITERAL(14, 254, 25) // "on_btnordinarySet_clicked"

    },
    "BehaviorAnalyseDlg\0OnlineTreeViewDoubleClick\0"
    "\0index\0on_btnEncode_clicked\0"
    "on_btnWeb_clicked\0on_btnUpGrade_clicked\0"
    "on_btnArea_clicked\0on_btnFace_clicked\0"
    "on_btnWarning_clicked\0on_btnNetWork_clicked\0"
    "searchIP\0on_btnVideoWarning_clicked\0"
    "on_btnImageSet_clicked\0on_btnordinarySet_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BehaviorAnalyseDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       4,    0,   77,    2, 0x08 /* Private */,
       5,    0,   78,    2, 0x08 /* Private */,
       6,    0,   79,    2, 0x08 /* Private */,
       7,    0,   80,    2, 0x08 /* Private */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
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

void BehaviorAnalyseDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BehaviorAnalyseDlg *_t = static_cast<BehaviorAnalyseDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnlineTreeViewDoubleClick((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_btnEncode_clicked(); break;
        case 2: _t->on_btnWeb_clicked(); break;
        case 3: _t->on_btnUpGrade_clicked(); break;
        case 4: _t->on_btnArea_clicked(); break;
        case 5: _t->on_btnFace_clicked(); break;
        case 6: _t->on_btnWarning_clicked(); break;
        case 7: _t->on_btnNetWork_clicked(); break;
        case 8: _t->searchIP(); break;
        case 9: _t->on_btnVideoWarning_clicked(); break;
        case 10: _t->on_btnImageSet_clicked(); break;
        case 11: _t->on_btnordinarySet_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject BehaviorAnalyseDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BehaviorAnalyseDlg.data,
      qt_meta_data_BehaviorAnalyseDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BehaviorAnalyseDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BehaviorAnalyseDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BehaviorAnalyseDlg.stringdata0))
        return static_cast<void*>(const_cast< BehaviorAnalyseDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int BehaviorAnalyseDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
