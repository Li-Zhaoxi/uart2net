/****************************************************************************
** Meta object code from reading C++ file 'uart2net.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "uart2net.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uart2net.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UART2NET_t {
    QByteArrayData data[12];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UART2NET_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UART2NET_t qt_meta_stringdata_UART2NET = {
    {
QT_MOC_LITERAL(0, 0, 8), // "UART2NET"
QT_MOC_LITERAL(1, 9, 22), // "signals_reconnect_host"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 23), // "transport_serial_to_tcp"
QT_MOC_LITERAL(4, 57, 10), // "serialdata"
QT_MOC_LITERAL(5, 68, 23), // "transport_tcp_to_serial"
QT_MOC_LITERAL(6, 92, 7), // "tcpdata"
QT_MOC_LITERAL(7, 100, 18), // "uart2net_safe_quit"
QT_MOC_LITERAL(8, 119, 15), // "send_heartbeats"
QT_MOC_LITERAL(9, 135, 11), // "judge_alive"
QT_MOC_LITERAL(10, 147, 9), // "reconnect"
QT_MOC_LITERAL(11, 157, 18) // "slots_about_toquit"

    },
    "UART2NET\0signals_reconnect_host\0\0"
    "transport_serial_to_tcp\0serialdata\0"
    "transport_tcp_to_serial\0tcpdata\0"
    "uart2net_safe_quit\0send_heartbeats\0"
    "judge_alive\0reconnect\0slots_about_toquit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UART2NET[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   55,    2, 0x0a /* Public */,
       5,    1,   58,    2, 0x0a /* Public */,
       7,    0,   61,    2, 0x0a /* Public */,
       8,    0,   62,    2, 0x0a /* Public */,
       9,    0,   63,    2, 0x0a /* Public */,
      10,    0,   64,    2, 0x0a /* Public */,
      11,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UART2NET::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UART2NET *_t = static_cast<UART2NET *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signals_reconnect_host(); break;
        case 1: _t->transport_serial_to_tcp((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->transport_tcp_to_serial((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->uart2net_safe_quit(); break;
        case 4: _t->send_heartbeats(); break;
        case 5: _t->judge_alive(); break;
        case 6: _t->reconnect(); break;
        case 7: _t->slots_about_toquit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (UART2NET::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UART2NET::signals_reconnect_host)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject UART2NET::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UART2NET.data,
      qt_meta_data_UART2NET,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UART2NET::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UART2NET::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UART2NET.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UART2NET::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void UART2NET::signals_reconnect_host()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
