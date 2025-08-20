/****************************************************************************
** Meta object code from reading C++ file 'ccombinationplay.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ccombinationplay.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccombinationplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16CcombinationPlayE_t {};
} // unnamed namespace

template <> constexpr inline auto CcombinationPlay::qt_create_metaobjectdata<qt_meta_tag_ZN16CcombinationPlayE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CcombinationPlay",
        "sig_play",
        "",
        "sig_stop",
        "sig_pre",
        "sig_next",
        "sig_fullScreen",
        "sig_volume",
        "sig_pslider",
        "open_file"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_play'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_stop'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_pre'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_next'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_fullScreen'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_volume'
        QtMocHelpers::SignalData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'sig_pslider'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'open_file'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CcombinationPlay, qt_meta_tag_ZN16CcombinationPlayE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CcombinationPlay::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16CcombinationPlayE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16CcombinationPlayE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16CcombinationPlayE_t>.metaTypes,
    nullptr
} };

void CcombinationPlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CcombinationPlay *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_play(); break;
        case 1: _t->sig_stop(); break;
        case 2: _t->sig_pre(); break;
        case 3: _t->sig_next(); break;
        case 4: _t->sig_fullScreen(); break;
        case 5: _t->sig_volume((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->sig_pslider((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->open_file(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CcombinationPlay::*)()>(_a, &CcombinationPlay::sig_play, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CcombinationPlay::*)()>(_a, &CcombinationPlay::sig_stop, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CcombinationPlay::*)()>(_a, &CcombinationPlay::sig_pre, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (CcombinationPlay::*)()>(_a, &CcombinationPlay::sig_next, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (CcombinationPlay::*)()>(_a, &CcombinationPlay::sig_fullScreen, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (CcombinationPlay::*)(int )>(_a, &CcombinationPlay::sig_volume, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (CcombinationPlay::*)(int )>(_a, &CcombinationPlay::sig_pslider, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (CcombinationPlay::*)()>(_a, &CcombinationPlay::open_file, 7))
            return;
    }
}

const QMetaObject *CcombinationPlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CcombinationPlay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16CcombinationPlayE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CcombinationPlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CcombinationPlay::sig_play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CcombinationPlay::sig_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CcombinationPlay::sig_pre()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CcombinationPlay::sig_next()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CcombinationPlay::sig_fullScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CcombinationPlay::sig_volume(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void CcombinationPlay::sig_pslider(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void CcombinationPlay::open_file()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
