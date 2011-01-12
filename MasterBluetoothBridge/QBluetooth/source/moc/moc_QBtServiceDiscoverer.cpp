/****************************************************************************
** Meta object code from reading C++ file 'QBtServiceDiscoverer.h'
**
** Created: Tue 11. Jan 20:18:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ServiceDiscoverer/QBtServiceDiscoverer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtServiceDiscoverer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtServiceDiscoverer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      41,   21,   21,   21, 0x05,
      81,   60,   21,   21, 0x05,
     125,  119,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     189,  176,   21,   21, 0x0a,
     215,  176,   21,   21, 0x0a,
     245,  176,   21,   21, 0x0a,
     295,  277,   21,   21, 0x0a,
     348,  329,   21,   21, 0x0a,
     389,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QBtServiceDiscoverer[] = {
    "QBtServiceDiscoverer\0\0discoveryStarted()\0"
    "discoveryStopped()\0targetDevice,service\0"
    "newServiceFound(QBtDevice,QBtService)\0"
    "error\0error(QBtServiceDiscoverer::ServiceDiscoveryError)\0"
    "targetDevice\0startDiscovery(QBtDevice)\0"
    "startObexDiscovery(QBtDevice)\0"
    "startRfcommDiscovery(QBtDevice)\0"
    "targetDevice,uuid\0startDiscovery(QBtDevice,QBtUuid)\0"
    "targetDevice,uuids\0"
    "startDiscovery(QBtDevice,QList<QBtUuid>)\0"
    "stopDiscovery()\0"
};

const QMetaObject QBtServiceDiscoverer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtServiceDiscoverer,
      qt_meta_data_QBtServiceDiscoverer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtServiceDiscoverer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtServiceDiscoverer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtServiceDiscoverer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtServiceDiscoverer))
        return static_cast<void*>(const_cast< QBtServiceDiscoverer*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtServiceDiscoverer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: discoveryStarted(); break;
        case 1: discoveryStopped(); break;
        case 2: newServiceFound((*reinterpret_cast< const QBtDevice(*)>(_a[1])),(*reinterpret_cast< const QBtService(*)>(_a[2]))); break;
        case 3: error((*reinterpret_cast< QBtServiceDiscoverer::ServiceDiscoveryError(*)>(_a[1]))); break;
        case 4: startDiscovery((*reinterpret_cast< const QBtDevice(*)>(_a[1]))); break;
        case 5: startObexDiscovery((*reinterpret_cast< const QBtDevice(*)>(_a[1]))); break;
        case 6: startRfcommDiscovery((*reinterpret_cast< const QBtDevice(*)>(_a[1]))); break;
        case 7: startDiscovery((*reinterpret_cast< const QBtDevice(*)>(_a[1])),(*reinterpret_cast< const QBtUuid(*)>(_a[2]))); break;
        case 8: startDiscovery((*reinterpret_cast< const QBtDevice(*)>(_a[1])),(*reinterpret_cast< const QList<QBtUuid>(*)>(_a[2]))); break;
        case 9: stopDiscovery(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QBtServiceDiscoverer::discoveryStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QBtServiceDiscoverer::discoveryStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtServiceDiscoverer::newServiceFound(const QBtDevice & _t1, const QBtService & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QBtServiceDiscoverer::error(QBtServiceDiscoverer::ServiceDiscoveryError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
