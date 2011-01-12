/****************************************************************************
** Meta object code from reading C++ file 'QBtObjectExchangeClient.h'
**
** Created: Tue 11. Jan 20:18:22 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Connection/ObjectExchange/Client/QBtObjectExchangeClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtObjectExchangeClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtObjectExchangeClient[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   25,   24,   24, 0x05,
      72,   24,   24,   24, 0x05,
      92,   24,   24,   24, 0x05,
     117,   24,   24,   24, 0x05,
     139,  130,   24,   24, 0x05,
     166,  161,   24,   24, 0x05,
     200,  191,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
     223,   24,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QBtObjectExchangeClient[] = {
    "QBtObjectExchangeClient\0\0code\0"
    "error(QBtObjectExchangeClient::ErrorCode)\0"
    "connectedToServer()\0disconnectedFromServer()\0"
    "objectSent()\0fileName\0fileReceived(QString)\0"
    "data\0dataReceived(QByteArray)\0pathName\0"
    "remotePathSet(QString)\0disconnect()\0"
};

const QMetaObject QBtObjectExchangeClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtObjectExchangeClient,
      qt_meta_data_QBtObjectExchangeClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtObjectExchangeClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtObjectExchangeClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtObjectExchangeClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtObjectExchangeClient))
        return static_cast<void*>(const_cast< QBtObjectExchangeClient*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtObjectExchangeClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: error((*reinterpret_cast< QBtObjectExchangeClient::ErrorCode(*)>(_a[1]))); break;
        case 1: connectedToServer(); break;
        case 2: disconnectedFromServer(); break;
        case 3: objectSent(); break;
        case 4: fileReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: dataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 6: remotePathSet((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: disconnect(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QBtObjectExchangeClient::error(QBtObjectExchangeClient::ErrorCode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QBtObjectExchangeClient::connectedToServer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtObjectExchangeClient::disconnectedFromServer()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QBtObjectExchangeClient::objectSent()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QBtObjectExchangeClient::fileReceived(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QBtObjectExchangeClient::dataReceived(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QBtObjectExchangeClient::remotePathSet(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
