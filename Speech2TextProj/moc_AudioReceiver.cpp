/****************************************************************************
** Meta object code from reading C++ file 'AudioReceiver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "component/AudioReceiver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioReceiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AudioReceiver_t {
    QByteArrayData data[14];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioReceiver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioReceiver_t qt_meta_stringdata_AudioReceiver = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AudioReceiver"
QT_MOC_LITERAL(1, 14, 13), // "processBuffer"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "QAudioBuffer"
QT_MOC_LITERAL(4, 42, 6), // "buffer"
QT_MOC_LITERAL(5, 49, 14), // "updateProgress"
QT_MOC_LITERAL(6, 64, 8), // "duration"
QT_MOC_LITERAL(7, 73, 12), // "updateStatus"
QT_MOC_LITERAL(8, 86, 22), // "QMediaRecorder::Status"
QT_MOC_LITERAL(9, 109, 6), // "status"
QT_MOC_LITERAL(10, 116, 14), // "onStateChanged"
QT_MOC_LITERAL(11, 131, 21), // "QMediaRecorder::State"
QT_MOC_LITERAL(12, 153, 5), // "state"
QT_MOC_LITERAL(13, 159, 19) // "displayErrorMessage"

    },
    "AudioReceiver\0processBuffer\0\0QAudioBuffer\0"
    "buffer\0updateProgress\0duration\0"
    "updateStatus\0QMediaRecorder::Status\0"
    "status\0onStateChanged\0QMediaRecorder::State\0"
    "state\0displayErrorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioReceiver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       7,    1,   45,    2, 0x0a /* Public */,
      10,    1,   48,    2, 0x0a /* Public */,
      13,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void AudioReceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AudioReceiver *_t = static_cast<AudioReceiver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processBuffer((*reinterpret_cast< const QAudioBuffer(*)>(_a[1]))); break;
        case 1: _t->updateProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 2: _t->updateStatus((*reinterpret_cast< QMediaRecorder::Status(*)>(_a[1]))); break;
        case 3: _t->onStateChanged((*reinterpret_cast< QMediaRecorder::State(*)>(_a[1]))); break;
        case 4: _t->displayErrorMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudioBuffer >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaRecorder::Status >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaRecorder::State >(); break;
            }
            break;
        }
    }
}

const QMetaObject AudioReceiver::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AudioReceiver.data,
      qt_meta_data_AudioReceiver,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AudioReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioReceiver.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AudioReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
