/****************************************************************************
** Meta object code from reading C++ file 'QBtSerialPortServer.h'
**
** Created: Tue 11. Jan 20:18:21 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Connection/SerialPort/Server/QBtSerialPortServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtSerialPortServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtSerialPortServer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      37,   20,   20,   20, 0x05,
      67,   53,   20,   20, 0x05,
      95,   20,   20,   20, 0x05,
     116,   20,   20,   20, 0x05,
     132,  127,   20,   20, 0x05,
     159,  154,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     219,  197,   20,   20, 0x0a,
     258,  248,   20,   20, 0x2a,
     279,   20,   20,   20, 0x0a,
     292,  127,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QBtSerialPortServer[] = {
    "QBtSerialPortServer\0\0serverStarted()\0"
    "serverStopped()\0clientAddress\0"
    "clientConnected(QBtAddress)\0"
    "clientDisconnected()\0dataSent()\0data\0"
    "dataReceived(QString)\0code\0"
    "error(QBtSerialPortServer::ErrorCode)\0"
    "serviceId,serviceName\0"
    "startServer(QBtUuid,QString)\0serviceId\0"
    "startServer(QBtUuid)\0stopServer()\0"
    "sendData(QString)\0"
};

const QMetaObject QBtSerialPortServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtSerialPortServer,
      qt_meta_data_QBtSerialPortServer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtSerialPortServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtSerialPortServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtSerialPortServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtSerialPortServer))
        return static_cast<void*>(const_cast< QBtSerialPortServer*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtSerialPortServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: serverStarted(); break;
        case 1: serverStopped(); break;
        case 2: clientConnected((*reinterpret_cast< const QBtAddress(*)>(_a[1]))); break;
        case 3: clientDisconnected(); break;
        case 4: dataSent(); break;
        case 5: dataReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: error((*reinterpret_cast< QBtSerialPortServer::ErrorCode(*)>(_a[1]))); break;
        case 7: startServer((*reinterpret_cast< const QBtUuid(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: startServer((*reinterpret_cast< const QBtUuid(*)>(_a[1]))); break;
        case 9: stopServer(); break;
        case 10: sendData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QBtSerialPortServer::serverStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QBtSerialPortServer::serverStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtSerialPortServer::clientConnected(const QBtAddress & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QBtSerialPortServer::clientDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QBtSerialPortServer::dataSent()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QBtSerialPortServer::dataReceived(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QBtSerialPortServer::error(QBtSerialPortServer::ErrorCode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
