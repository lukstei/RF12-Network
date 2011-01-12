/****************************************************************************
** Meta object code from reading C++ file 'QBtDeviceDiscoverer.h'
**
** Created: Tue 11. Jan 20:18:19 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DeviceDiscoverer/QBtDeviceDiscoverer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtDeviceDiscoverer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtDeviceDiscoverer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   21,   20,   20, 0x05,
      60,   20,   20,   20, 0x05,
      79,   20,   20,   20, 0x05,
     104,   98,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     154,   20,   20,   20, 0x0a,
     171,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QBtDeviceDiscoverer[] = {
    "QBtDeviceDiscoverer\0\0remoteDevice\0"
    "newDeviceFound(QBtDevice)\0discoveryStopped()\0"
    "discoveryStarted()\0error\0"
    "error(QBtDeviceDiscoverer::DeviceDiscoveryErrors)\0"
    "startDiscovery()\0stopDiscovery()\0"
};

const QMetaObject QBtDeviceDiscoverer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtDeviceDiscoverer,
      qt_meta_data_QBtDeviceDiscoverer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtDeviceDiscoverer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtDeviceDiscoverer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtDeviceDiscoverer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtDeviceDiscoverer))
        return static_cast<void*>(const_cast< QBtDeviceDiscoverer*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtDeviceDiscoverer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newDeviceFound((*reinterpret_cast< const QBtDevice(*)>(_a[1]))); break;
        case 1: discoveryStopped(); break;
        case 2: discoveryStarted(); break;
        case 3: error((*reinterpret_cast< QBtDeviceDiscoverer::DeviceDiscoveryErrors(*)>(_a[1]))); break;
        case 4: startDiscovery(); break;
        case 5: stopDiscovery(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QBtDeviceDiscoverer::newDeviceFound(const QBtDevice & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QBtDeviceDiscoverer::discoveryStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtDeviceDiscoverer::discoveryStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QBtDeviceDiscoverer::error(QBtDeviceDiscoverer::DeviceDiscoveryErrors _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
