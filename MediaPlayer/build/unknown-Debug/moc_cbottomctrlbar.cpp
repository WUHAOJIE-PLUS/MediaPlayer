/****************************************************************************
** Meta object code from reading C++ file 'cbottomctrlbar.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cbottomctrlbar.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cbottomctrlbar.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14CBottomCtrlBarE_t {};
} // unnamed namespace

template <> constexpr inline auto CBottomCtrlBar::qt_create_metaobjectdata<qt_meta_tag_ZN14CBottomCtrlBarE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CBottomCtrlBar",
        "sig_play",
        "",
        "sig_stop",
        "sig_pre",
        "sig_next",
        "sig_fullScreen",
        "sig_volume",
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
        // Signal 'open_file'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CBottomCtrlBar, qt_meta_tag_ZN14CBottomCtrlBarE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CBottomCtrlBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CBottomCtrlBarE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CBottomCtrlBarE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14CBottomCtrlBarE_t>.metaTypes,
    nullptr
} };

void CBottomCtrlBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CBottomCtrlBar *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_play(); break;
        case 1: _t->sig_stop(); break;
        case 2: _t->sig_pre(); break;
        case 3: _t->sig_next(); break;
        case 4: _t->sig_fullScreen(); break;
        case 5: _t->sig_volume((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->open_file(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CBottomCtrlBar::*)()>(_a, &CBottomCtrlBar::sig_play, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CBottomCtrlBar::*)()>(_a, &CBottomCtrlBar::sig_stop, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CBottomCtrlBar::*)()>(_a, &CBottomCtrlBar::sig_pre, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (CBottomCtrlBar::*)()>(_a, &CBottomCtrlBar::sig_next, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (CBottomCtrlBar::*)()>(_a, &CBottomCtrlBar::sig_fullScreen, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (CBottomCtrlBar::*)(int )>(_a, &CBottomCtrlBar::sig_volume, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (CBottomCtrlBar::*)()>(_a, &CBottomCtrlBar::open_file, 6))
            return;
    }
}

const QMetaObject *CBottomCtrlBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CBottomCtrlBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CBottomCtrlBarE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CBottomCtrlBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CBottomCtrlBar::sig_play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CBottomCtrlBar::sig_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CBottomCtrlBar::sig_pre()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CBottomCtrlBar::sig_next()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CBottomCtrlBar::sig_fullScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CBottomCtrlBar::sig_volume(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void CBottomCtrlBar::open_file()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
