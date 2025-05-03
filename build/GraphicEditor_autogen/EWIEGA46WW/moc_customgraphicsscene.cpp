/****************************************************************************
** Meta object code from reading C++ file 'customgraphicsscene.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Qt-git2004-Qt-lr5_without_additional/customgraphicsscene.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customgraphicsscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN19CustomGraphicsSceneE_t {};
} // unnamed namespace

template <> constexpr inline auto CustomGraphicsScene::qt_create_metaobjectdata<qt_meta_tag_ZN19CustomGraphicsSceneE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CustomGraphicsScene",
        "sceneMousePressed",
        "",
        "pos",
        "sceneMouseMoved",
        "sceneMouseReleased"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sceneMousePressed'
        QtMocHelpers::SignalData<void(const QPointF &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QPointF, 3 },
        }}),
        // Signal 'sceneMouseMoved'
        QtMocHelpers::SignalData<void(const QPointF &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QPointF, 3 },
        }}),
        // Signal 'sceneMouseReleased'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CustomGraphicsScene, qt_meta_tag_ZN19CustomGraphicsSceneE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CustomGraphicsScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19CustomGraphicsSceneE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19CustomGraphicsSceneE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19CustomGraphicsSceneE_t>.metaTypes,
    nullptr
} };

void CustomGraphicsScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CustomGraphicsScene *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sceneMousePressed((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 1: _t->sceneMouseMoved((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 2: _t->sceneMouseReleased(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CustomGraphicsScene::*)(const QPointF & )>(_a, &CustomGraphicsScene::sceneMousePressed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomGraphicsScene::*)(const QPointF & )>(_a, &CustomGraphicsScene::sceneMouseMoved, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomGraphicsScene::*)()>(_a, &CustomGraphicsScene::sceneMouseReleased, 2))
            return;
    }
}

const QMetaObject *CustomGraphicsScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomGraphicsScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19CustomGraphicsSceneE_t>.strings))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int CustomGraphicsScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CustomGraphicsScene::sceneMousePressed(const QPointF & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void CustomGraphicsScene::sceneMouseMoved(const QPointF & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void CustomGraphicsScene::sceneMouseReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
