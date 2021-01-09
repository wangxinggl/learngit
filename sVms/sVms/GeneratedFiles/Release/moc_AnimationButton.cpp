/****************************************************************************
** Meta object code from reading C++ file 'AnimationButton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AnimationButton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnimationButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AnimationButton_t {
    QByteArrayData data[10];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnimationButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnimationButton_t qt_meta_stringdata_AnimationButton = {
    {
QT_MOC_LITERAL(0, 0, 15), // "AnimationButton"
QT_MOC_LITERAL(1, 16, 14), // "widget_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "enterImageChanged"
QT_MOC_LITERAL(4, 50, 5), // "index"
QT_MOC_LITERAL(5, 56, 17), // "leaveImageChanged"
QT_MOC_LITERAL(6, 74, 7), // "setText"
QT_MOC_LITERAL(7, 82, 4), // "text"
QT_MOC_LITERAL(8, 87, 8), // "setImage"
QT_MOC_LITERAL(9, 96, 5) // "image"

    },
    "AnimationButton\0widget_clicked\0\0"
    "enterImageChanged\0index\0leaveImageChanged\0"
    "setText\0text\0setImage\0image"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnimationButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    1,   46,    2, 0x0a /* Public */,
       8,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariant,    4,
    QMetaType::Void, QMetaType::QVariant,    4,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void AnimationButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnimationButton *_t = static_cast<AnimationButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->widget_clicked(); break;
        case 1: _t->enterImageChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 2: _t->leaveImageChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AnimationButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnimationButton::widget_clicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AnimationButton::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AnimationButton.data,
      qt_meta_data_AnimationButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AnimationButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnimationButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AnimationButton.stringdata0))
        return static_cast<void*>(const_cast< AnimationButton*>(this));
    return QWidget::qt_metacast(_clname);
}

int AnimationButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void AnimationButton::widget_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
