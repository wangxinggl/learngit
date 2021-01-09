/****************************************************************************
** Meta object code from reading C++ file 'cpumemorylabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cpumemorylabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cpumemorylabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CpuMemoryLabel_t {
    QByteArrayData data[17];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CpuMemoryLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CpuMemoryLabel_t qt_meta_stringdata_CpuMemoryLabel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CpuMemoryLabel"
QT_MOC_LITERAL(1, 15, 11), // "textChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "text"
QT_MOC_LITERAL(4, 33, 12), // "valueChanged"
QT_MOC_LITERAL(5, 46, 10), // "cpuPercent"
QT_MOC_LITERAL(6, 57, 13), // "memoryPercent"
QT_MOC_LITERAL(7, 71, 9), // "memoryAll"
QT_MOC_LITERAL(8, 81, 9), // "memoryUse"
QT_MOC_LITERAL(9, 91, 10), // "memoryFree"
QT_MOC_LITERAL(10, 102, 6), // "getCPU"
QT_MOC_LITERAL(11, 109, 9), // "getMemory"
QT_MOC_LITERAL(12, 119, 8), // "readData"
QT_MOC_LITERAL(13, 128, 7), // "setData"
QT_MOC_LITERAL(14, 136, 5), // "start"
QT_MOC_LITERAL(15, 142, 8), // "interval"
QT_MOC_LITERAL(16, 151, 4) // "stop"

    },
    "CpuMemoryLabel\0textChanged\0\0text\0"
    "valueChanged\0cpuPercent\0memoryPercent\0"
    "memoryAll\0memoryUse\0memoryFree\0getCPU\0"
    "getMemory\0readData\0setData\0start\0"
    "interval\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CpuMemoryLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    5,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   68,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,
      12,    0,   70,    2, 0x08 /* Private */,
      13,    0,   71,    2, 0x08 /* Private */,
      14,    1,   72,    2, 0x0a /* Public */,
      16,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,    8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,

       0        // eod
};

void CpuMemoryLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CpuMemoryLabel *_t = static_cast<CpuMemoryLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->valueChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->getCPU(); break;
        case 3: _t->getMemory(); break;
        case 4: _t->readData(); break;
        case 5: _t->setData(); break;
        case 6: _t->start((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CpuMemoryLabel::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CpuMemoryLabel::textChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CpuMemoryLabel::*_t)(int , int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CpuMemoryLabel::valueChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CpuMemoryLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_CpuMemoryLabel.data,
      qt_meta_data_CpuMemoryLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CpuMemoryLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CpuMemoryLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CpuMemoryLabel.stringdata0))
        return static_cast<void*>(const_cast< CpuMemoryLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int CpuMemoryLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CpuMemoryLabel::textChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CpuMemoryLabel::valueChanged(int _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
