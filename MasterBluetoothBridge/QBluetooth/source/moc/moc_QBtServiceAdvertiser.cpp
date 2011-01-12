/****************************************************************************
** Meta object code from reading C++ file 'QBtServiceAdvertiser.h'
**
** Created: Tue 11. Jan 20:18:21 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ServiceAdvertiser/QBtServiceAdvertiser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBtServiceAdvertiser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBtServiceAdvertiser[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   22,   21,   21, 0x05,
      61,   21,   21,   21, 0x05,
      87,   82,   21,   21, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QBtServiceAdvertiser[] = {
    "QBtServiceAdvertiser\0\0service\0"
    "advertisingStarted(QBtService)\0"
    "advertisingStopped()\0code\0"
    "error(QBtServiceAdvertiser::ErrorCodes)\0"
};

const QMetaObject QBtServiceAdvertiser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QBtServiceAdvertiser,
      qt_meta_data_QBtServiceAdvertiser, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBtServiceAdvertiser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBtServiceAdvertiser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBtServiceAdvertiser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBtServiceAdvertiser))
        return static_cast<void*>(const_cast< QBtServiceAdvertiser*>(this));
    return QObject::qt_metacast(_clname);
}

int QBtServiceAdvertiser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: advertisingStarted((*reinterpret_cast< const QBtService(*)>(_a[1]))); break;
        case 1: advertisingStopped(); break;
        case 2: error((*reinterpret_cast< QBtServiceAdvertiser::ErrorCodes(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QBtServiceAdvertiser::advertisingStarted(const QBtService & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QBtServiceAdvertiser::advertisingStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QBtServiceAdvertiser::error(QBtServiceAdvertiser::ErrorCodes _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
