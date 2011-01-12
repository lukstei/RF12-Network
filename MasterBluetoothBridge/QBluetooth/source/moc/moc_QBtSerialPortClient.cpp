/****************************************************************************
** Meta object code from reading C++ file 'QBtSerialPortClient.h'
**
** Created: Tue 11. Jan 20:18:21 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Connection/SerialPort/Client/QBtSerialPortClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtSerialPortClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtSerialPortClient[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      46,   20,   20,   20, 0x05,
      70,   20,   20,   20, 0x05,
      90,   20,   20,   20, 0x05,
     106,  101,   20,   20, 0x05,
     134,  128,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     199,  172,   20,   20, 0x0a,
     229,   20,   20,   20, 0x0a,
     242,  101,   20,   20, 0x0a,
     260,  101,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QBtSerialPortClient[] = {
    "QBtSerialPortClient\0\0disconnectedFromServer()\0"
    "connectionResetByPeer()\0connectedToServer()\0"
    "dataSent()\0data\0dataReceived(QString)\0"
    "error\0error(QBtSerialPortClient::ErrorCode)\0"
    "remoteDevice,remoteService\0"
    "connect(QBtDevice,QBtService)\0"
    "disconnect()\0sendData(QString)\0"
    "sendData(QByteArray)\0"
};

const QMetaObject QBtSerialPortClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtSerialPortClient,
      qt_meta_data_QBtSerialPortClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtSerialPortClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtSerialPortClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtSerialPortClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtSerialPortClient))
        return static_cast<void*>(const_cast< QBtSerialPortClient*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtSerialPortClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: disconnectedFromServer(); break;
        case 1: connectionResetByPeer(); break;
        case 2: connectedToServer(); break;
        case 3: dataSent(); break;
        case 4: dataReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: error((*reinterpret_cast< QBtSerialPortClient::ErrorCode(*)>(_a[1]))); break;
        case 6: connect((*reinterpret_cast< const QBtDevice(*)>(_a[1])),(*reinterpret_cast< const QBtService(*)>(_a[2]))); break;
        case 7: disconnect(); break;
        case 8: sendData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: sendData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QBtSerialPortClient::disconnectedFromServer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QBtSerialPortClient::connectionResetByPeer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtSerialPortClient::connectedToServer()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QBtSerialPortClient::dataSent()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QBtSerialPortClient::dataReceived(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QBtSerialPortClient::error(QBtSerialPortClient::ErrorCode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
