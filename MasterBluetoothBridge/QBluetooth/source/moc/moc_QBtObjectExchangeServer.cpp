/****************************************************************************
** Meta object code from reading C++ file 'QBtObjectExchangeServer.h'
**
** Created: Tue 11. Jan 20:18:22 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Connection/ObjectExchange/Server/QBtObjectExchangeServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtObjectExchangeServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtObjectExchangeServer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,
      41,   24,   24,   24, 0x05,
      62,   57,   24,   24, 0x05,
     104,   79,   24,   24, 0x05,
     133,   24,   24,   24, 0x05,
     169,  152,   24,   24, 0x05,
     195,   24,   24,   24, 0x05,
     242,  218,   24,   24, 0x05,
     295,  274,   24,   24, 0x05,
     324,  274,   24,   24, 0x05,
     353,   24,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
     403,  381,   24,   24, 0x0a,
     442,  432,   24,   24, 0x2a,
     463,   24,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QBtObjectExchangeServer[] = {
    "QBtObjectExchangeServer\0\0serverStarted()\0"
    "serverStopped()\0code\0error(ErrorCode)\0"
    "overalDataSize,bytesSent\0"
    "receivingObjectInfo(int,int)\0"
    "receivingStarted()\0receivedFileName\0"
    "receivingStopped(QString)\0"
    "transmittingRejected()\0overalDataSize,byteSent\0"
    "transmittingObjectInfo(int,int)\0"
    "transmittingfileName\0transmittingStarted(QString)\0"
    "transmittingStopped(QString)\0"
    "clientAbortedTransmittion()\0"
    "serviceId,serviceName\0"
    "startServer(QBtUuid,QString)\0serviceId\0"
    "startServer(QBtUuid)\0stopServer()\0"
};

const QMetaObject QBtObjectExchangeServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtObjectExchangeServer,
      qt_meta_data_QBtObjectExchangeServer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtObjectExchangeServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtObjectExchangeServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtObjectExchangeServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtObjectExchangeServer))
        return static_cast<void*>(const_cast< QBtObjectExchangeServer*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtObjectExchangeServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: serverStarted(); break;
        case 1: serverStopped(); break;
        case 2: error((*reinterpret_cast< ErrorCode(*)>(_a[1]))); break;
        case 3: receivingObjectInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: receivingStarted(); break;
        case 5: receivingStopped((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: transmittingRejected(); break;
        case 7: transmittingObjectInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: transmittingStarted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: transmittingStopped((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: clientAbortedTransmittion(); break;
        case 11: startServer((*reinterpret_cast< const QBtUuid(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: startServer((*reinterpret_cast< const QBtUuid(*)>(_a[1]))); break;
        case 13: stopServer(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void QBtObjectExchangeServer::serverStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QBtObjectExchangeServer::serverStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtObjectExchangeServer::error(ErrorCode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QBtObjectExchangeServer::receivingObjectInfo(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QBtObjectExchangeServer::receivingStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QBtObjectExchangeServer::receivingStopped(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QBtObjectExchangeServer::transmittingRejected()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void QBtObjectExchangeServer::transmittingObjectInfo(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QBtObjectExchangeServer::transmittingStarted(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QBtObjectExchangeServer::transmittingStopped(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QBtObjectExchangeServer::clientAbortedTransmittion()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
QT_END_MOC_NAMESPACE
