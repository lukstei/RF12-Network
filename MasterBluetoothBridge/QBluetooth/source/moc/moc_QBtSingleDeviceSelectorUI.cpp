/****************************************************************************
** Meta object code from reading C++ file 'QBtSingleDeviceSelectorUI.h'
**
** Created: Tue 11. Jan 20:18:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DeviceDiscoverer/QBtSingleDeviceSelectorUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtSingleDeviceSelectorUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtSingleDeviceSelectorUI[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      42,   27,   26,   26, 0x05,
      72,   26,   26,   26, 0x05,
      91,   26,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
     106,   26,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QBtSingleDeviceSelectorUI[] = {
    "QBtSingleDeviceSelectorUI\0\0selectedDevice\0"
    "discoveryCompleted(QBtDevice)\0"
    "discoveryStarted()\0userCanceled()\0"
    "show()\0"
};

const QMetaObject QBtSingleDeviceSelectorUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtSingleDeviceSelectorUI,
      qt_meta_data_QBtSingleDeviceSelectorUI, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtSingleDeviceSelectorUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtSingleDeviceSelectorUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtSingleDeviceSelectorUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtSingleDeviceSelectorUI))
        return static_cast<void*>(const_cast< QBtSingleDeviceSelectorUI*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtSingleDeviceSelectorUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: discoveryCompleted((*reinterpret_cast< const QBtDevice(*)>(_a[1]))); break;
        case 1: discoveryStarted(); break;
        case 2: userCanceled(); break;
        case 3: show(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QBtSingleDeviceSelectorUI::discoveryCompleted(const QBtDevice & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QBtSingleDeviceSelectorUI::discoveryStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtSingleDeviceSelectorUI::userCanceled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
