/****************************************************************************
** Meta object code from reading C++ file 'QBtServiceDiscovererForAll.h'
**
** Created: Tue 11. Jan 20:18:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ServiceDiscoverer/QBtServiceDiscovererForAll.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtServiceDiscovererForAll.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtServiceDiscovererForAll[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,
      47,   27,   27,   27, 0x05,
      71,   64,   27,   27, 0x05,
     110,   97,   27,   27, 0x05,
     192,  186,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
     257,   27,   27,   27, 0x0a,
     274,   27,   27,   27, 0x0a,
     295,   27,   27,   27, 0x0a,
     323,  318,   27,   27, 0x0a,
     353,  347,   27,   27, 0x0a,
     384,   27,   27,   27, 0x0a,
     421,  400,   27,   27, 0x08,
     462,   27,   27,   27, 0x08,
     491,   27,   27,   27, 0x08,
     518,  186,   27,   27, 0x08,
     572,   27,   27,   27, 0x08,
     592,   27,   27,   27, 0x08,
     627,  614,   27,   27, 0x08,
     656,  186,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QBtServiceDiscovererForAll[] = {
    "QBtServiceDiscovererForAll\0\0"
    "discoveryStarted()\0discoveryEnded()\0"
    "device\0newDeviceFound(QBtDevice)\0"
    "device,error\0"
    "serviceDiscoveyError(QBtDevice,QBtServiceDiscoverer::ServiceDiscoveryE"
    "rror)\0"
    "error\0"
    "deviceDiscoveryError(QBtDeviceDiscoverer::DeviceDiscoveryErrors)\0"
    "startDiscovery()\0startObexDiscovery()\0"
    "startRfcommDiscovery()\0uuid\0"
    "startDiscovery(QBtUuid)\0uuids\0"
    "startDiscovery(QList<QBtUuid>)\0"
    "stopDiscovery()\0targetDevice,service\0"
    "sd_newServiceFound(QBtDevice,QBtService)\0"
    "sd_serviceDiscoveryStarted()\0"
    "sd_serviceDiscoveryEnded()\0"
    "sd_error(QBtServiceDiscoverer::ServiceDiscoveryError)\0"
    "dd_discoveryEnded()\0dd_discoveryStarted()\0"
    "remoteDevice\0dd_newDeviceFound(QBtDevice)\0"
    "dd_error(QBtDeviceDiscoverer::DeviceDiscoveryErrors)\0"
};

const QMetaObject QBtServiceDiscovererForAll::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtServiceDiscovererForAll,
      qt_meta_data_QBtServiceDiscovererForAll, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtServiceDiscovererForAll::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtServiceDiscovererForAll::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtServiceDiscovererForAll::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtServiceDiscovererForAll))
        return static_cast<void*>(const_cast< QBtServiceDiscovererForAll*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtServiceDiscovererForAll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: discoveryStarted(); break;
        case 1: discoveryEnded(); break;
        case 2: newDeviceFound((*reinterpret_cast< const QBtDevice(*)>(_a[1]))); break;
        case 3: serviceDiscoveyError((*reinterpret_cast< const QBtDevice(*)>(_a[1])),(*reinterpret_cast< QBtServiceDiscoverer::ServiceDiscoveryError(*)>(_a[2]))); break;
        case 4: deviceDiscoveryError((*reinterpret_cast< QBtDeviceDiscoverer::DeviceDiscoveryErrors(*)>(_a[1]))); break;
        case 5: startDiscovery(); break;
        case 6: startObexDiscovery(); break;
        case 7: startRfcommDiscovery(); break;
        case 8: startDiscovery((*reinterpret_cast< const QBtUuid(*)>(_a[1]))); break;
        case 9: startDiscovery((*reinterpret_cast< const QList<QBtUuid>(*)>(_a[1]))); break;
        case 10: stopDiscovery(); break;
        case 11: sd_newServiceFound((*reinterpret_cast< const QBtDevice(*)>(_a[1])),(*reinterpret_cast< const QBtService(*)>(_a[2]))); break;
        case 12: sd_serviceDiscoveryStarted(); break;
        case 13: sd_serviceDiscoveryEnded(); break;
        case 14: sd_error((*reinterpret_cast< QBtServiceDiscoverer::ServiceDiscoveryError(*)>(_a[1]))); break;
        case 15: dd_discoveryEnded(); break;
        case 16: dd_discoveryStarted(); break;
        case 17: dd_newDeviceFound((*reinterpret_cast< const QBtDevice(*)>(_a[1]))); break;
        case 18: dd_error((*reinterpret_cast< QBtDeviceDiscoverer::DeviceDiscoveryErrors(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void QBtServiceDiscovererForAll::discoveryStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QBtServiceDiscovererForAll::discoveryEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtServiceDiscovererForAll::newDeviceFound(const QBtDevice & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QBtServiceDiscovererForAll::serviceDiscoveyError(const QBtDevice & _t1, QBtServiceDiscoverer::ServiceDiscoveryError _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QBtServiceDiscovererForAll::deviceDiscoveryError(QBtDeviceDiscoverer::DeviceDiscoveryErrors _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
