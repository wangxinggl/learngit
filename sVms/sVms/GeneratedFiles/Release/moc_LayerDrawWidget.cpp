/****************************************************************************
** Meta object code from reading C++ file 'LayerDrawWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LayerDrawWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LayerDrawWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LayerDrawInfo_t {
    QByteArrayData data[5];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LayerDrawInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LayerDrawInfo_t qt_meta_stringdata_LayerDrawInfo = {
    {
QT_MOC_LITERAL(0, 0, 13), // "LayerDrawInfo"
QT_MOC_LITERAL(1, 14, 23), // "signalUpdateScrollWidth"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 23), // "signalUpdateCurrentTime"
QT_MOC_LITERAL(4, 63, 23) // "signalNotifyUpdatePaint"

    },
    "LayerDrawInfo\0signalUpdateScrollWidth\0"
    "\0signalUpdateCurrentTime\0"
    "signalNotifyUpdatePaint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LayerDrawInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    1,   32,    2, 0x06 /* Public */,
       4,    0,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QTime,    2,
    QMetaType::Void,

       0        // eod
};

void LayerDrawInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LayerDrawInfo *_t = static_cast<LayerDrawInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateScrollWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalUpdateCurrentTime((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 2: _t->signalNotifyUpdatePaint(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LayerDrawInfo::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LayerDrawInfo::signalUpdateScrollWidth)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LayerDrawInfo::*_t)(QTime );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LayerDrawInfo::signalUpdateCurrentTime)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (LayerDrawInfo::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LayerDrawInfo::signalNotifyUpdatePaint)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject LayerDrawInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LayerDrawInfo.data,
      qt_meta_data_LayerDrawInfo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LayerDrawInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LayerDrawInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LayerDrawInfo.stringdata0))
        return static_cast<void*>(const_cast< LayerDrawInfo*>(this));
    return QObject::qt_metacast(_clname);
}

int LayerDrawInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void LayerDrawInfo::signalUpdateScrollWidth(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LayerDrawInfo::signalUpdateCurrentTime(QTime _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LayerDrawInfo::signalNotifyUpdatePaint()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
struct qt_meta_stringdata_TimeLineWidget_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimeLineWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimeLineWidget_t qt_meta_stringdata_TimeLineWidget = {
    {
QT_MOC_LITERAL(0, 0, 14) // "TimeLineWidget"

    },
    "TimeLineWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimeLineWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void TimeLineWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject TimeLineWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TimeLineWidget.data,
      qt_meta_data_TimeLineWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TimeLineWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimeLineWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TimeLineWidget.stringdata0))
        return static_cast<void*>(const_cast< TimeLineWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TimeLineWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_LayerDrawWidget_t {
    QByteArrayData data[18];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LayerDrawWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LayerDrawWidget_t qt_meta_stringdata_LayerDrawWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "LayerDrawWidget"
QT_MOC_LITERAL(1, 16, 23), // "signalUpdateScrollWidth"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 5), // "width"
QT_MOC_LITERAL(4, 47, 30), // "signalUpdateScrollCurrentValue"
QT_MOC_LITERAL(5, 78, 5), // "value"
QT_MOC_LITERAL(6, 84, 18), // "signalClickedIndex"
QT_MOC_LITERAL(7, 103, 28), // "signalMouseClickeInVideoArea"
QT_MOC_LITERAL(8, 132, 18), // "onTimeScaleChanged"
QT_MOC_LITERAL(9, 151, 10), // "scaleValue"
QT_MOC_LITERAL(10, 162, 14), // "onMoveTimeLine"
QT_MOC_LITERAL(11, 177, 11), // "isMoveRight"
QT_MOC_LITERAL(12, 189, 20), // "onScrollValueChanged"
QT_MOC_LITERAL(13, 210, 17), // "onStartMoveNeedle"
QT_MOC_LITERAL(14, 228, 17), // "VideoSegmentInfo&"
QT_MOC_LITERAL(15, 246, 4), // "data"
QT_MOC_LITERAL(16, 251, 16), // "onStopMoveNeedle"
QT_MOC_LITERAL(17, 268, 11) // "onTimerMove"

    },
    "LayerDrawWidget\0signalUpdateScrollWidth\0"
    "\0width\0signalUpdateScrollCurrentValue\0"
    "value\0signalClickedIndex\0"
    "signalMouseClickeInVideoArea\0"
    "onTimeScaleChanged\0scaleValue\0"
    "onMoveTimeLine\0isMoveRight\0"
    "onScrollValueChanged\0onStartMoveNeedle\0"
    "VideoSegmentInfo&\0data\0onStopMoveNeedle\0"
    "onTimerMove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LayerDrawWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,
       7,    0,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   79,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      12,    1,   85,    2, 0x0a /* Public */,
      13,    1,   88,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      16,    0,   92,    2, 0x0a /* Public */,
      17,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LayerDrawWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LayerDrawWidget *_t = static_cast<LayerDrawWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateScrollWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalUpdateScrollCurrentValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalClickedIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalMouseClickeInVideoArea(); break;
        case 4: _t->onTimeScaleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onMoveTimeLine((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onScrollValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onStartMoveNeedle((*reinterpret_cast< VideoSegmentInfo(*)>(_a[1]))); break;
        case 8: _t->onStartMoveNeedle(); break;
        case 9: _t->onStopMoveNeedle(); break;
        case 10: _t->onTimerMove(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LayerDrawWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LayerDrawWidget::signalUpdateScrollWidth)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LayerDrawWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LayerDrawWidget::signalUpdateScrollCurrentValue)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (LayerDrawWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LayerDrawWidget::signalClickedIndex)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (LayerDrawWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LayerDrawWidget::signalMouseClickeInVideoArea)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject LayerDrawWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LayerDrawWidget.data,
      qt_meta_data_LayerDrawWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LayerDrawWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LayerDrawWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LayerDrawWidget.stringdata0))
        return static_cast<void*>(const_cast< LayerDrawWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int LayerDrawWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void LayerDrawWidget::signalUpdateScrollWidth(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LayerDrawWidget::signalUpdateScrollCurrentValue(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LayerDrawWidget::signalClickedIndex(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LayerDrawWidget::signalMouseClickeInVideoArea()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
