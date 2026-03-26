/****************************************************************************
** Meta object code from reading C++ file 'shelfconfig.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/shelfconfig.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shelfconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN11ShelfConfigE_t {};
} // unnamed namespace

template <> constexpr inline auto ShelfConfig::qt_create_metaobjectdata<qt_meta_tag_ZN11ShelfConfigE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ShelfConfig",
        "iconSizeChanged",
        "",
        "maxZoomChanged",
        "zoomRangeChanged",
        "iconSpacingChanged",
        "dockHeightChanged",
        "pinnedLaunchersChanged",
        "iconSize",
        "maxZoom",
        "zoomRange",
        "iconSpacing",
        "dockHeight",
        "pinnedLaunchers"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'iconSizeChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maxZoomChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'zoomRangeChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'iconSpacingChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'dockHeightChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'pinnedLaunchersChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'iconSize'
        QtMocHelpers::PropertyData<int>(8, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'maxZoom'
        QtMocHelpers::PropertyData<qreal>(9, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'zoomRange'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'iconSpacing'
        QtMocHelpers::PropertyData<int>(11, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'dockHeight'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags, 4),
        // property 'pinnedLaunchers'
        QtMocHelpers::PropertyData<QStringList>(13, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ShelfConfig, qt_meta_tag_ZN11ShelfConfigE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ShelfConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ShelfConfigE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ShelfConfigE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11ShelfConfigE_t>.metaTypes,
    nullptr
} };

void ShelfConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ShelfConfig *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->iconSizeChanged(); break;
        case 1: _t->maxZoomChanged(); break;
        case 2: _t->zoomRangeChanged(); break;
        case 3: _t->iconSpacingChanged(); break;
        case 4: _t->dockHeightChanged(); break;
        case 5: _t->pinnedLaunchersChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ShelfConfig::*)()>(_a, &ShelfConfig::iconSizeChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShelfConfig::*)()>(_a, &ShelfConfig::maxZoomChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShelfConfig::*)()>(_a, &ShelfConfig::zoomRangeChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShelfConfig::*)()>(_a, &ShelfConfig::iconSpacingChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShelfConfig::*)()>(_a, &ShelfConfig::dockHeightChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShelfConfig::*)()>(_a, &ShelfConfig::pinnedLaunchersChanged, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->iconSize(); break;
        case 1: *reinterpret_cast<qreal*>(_v) = _t->maxZoom(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->zoomRange(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->iconSpacing(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->dockHeight(); break;
        case 5: *reinterpret_cast<QStringList*>(_v) = _t->pinnedLaunchers(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIconSize(*reinterpret_cast<int*>(_v)); break;
        case 1: _t->setMaxZoom(*reinterpret_cast<qreal*>(_v)); break;
        case 2: _t->setZoomRange(*reinterpret_cast<int*>(_v)); break;
        case 3: _t->setIconSpacing(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setPinnedLaunchers(*reinterpret_cast<QStringList*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *ShelfConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShelfConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ShelfConfigE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ShelfConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ShelfConfig::iconSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ShelfConfig::maxZoomChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ShelfConfig::zoomRangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ShelfConfig::iconSpacingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ShelfConfig::dockHeightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ShelfConfig::pinnedLaunchersChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
