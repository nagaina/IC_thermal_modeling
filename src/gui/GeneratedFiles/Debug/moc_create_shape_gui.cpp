/****************************************************************************
** Meta object code from reading C++ file 'create_shape_gui.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../create_shape_gui.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'create_shape_gui.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_create_shape_gui_t {
    QByteArrayData data[15];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_create_shape_gui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_create_shape_gui_t qt_meta_stringdata_create_shape_gui = {
    {
QT_MOC_LITERAL(0, 0, 16), // "create_shape_gui"
QT_MOC_LITERAL(1, 17, 5), // "reset"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "close"
QT_MOC_LITERAL(4, 30, 13), // "shape_changed"
QT_MOC_LITERAL(5, 44, 10), // "createLine"
QT_MOC_LITERAL(6, 55, 10), // "createRect"
QT_MOC_LITERAL(7, 66, 13), // "createEllipse"
QT_MOC_LITERAL(8, 80, 13), // "createPolygon"
QT_MOC_LITERAL(9, 94, 17), // "something_changed"
QT_MOC_LITERAL(10, 112, 14), // "selectByRegion"
QT_MOC_LITERAL(11, 127, 11), // "createShape"
QT_MOC_LITERAL(12, 139, 17), // "pen_color_changed"
QT_MOC_LITERAL(13, 157, 17), // "cap_style_changed"
QT_MOC_LITERAL(14, 175, 18) // "join_style_changed"

    },
    "create_shape_gui\0reset\0\0close\0"
    "shape_changed\0createLine\0createRect\0"
    "createEllipse\0createPolygon\0"
    "something_changed\0selectByRegion\0"
    "createShape\0pen_color_changed\0"
    "cap_style_changed\0join_style_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_create_shape_gui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,
       6,    0,   83,    2, 0x06 /* Public */,
       7,    0,   84,    2, 0x06 /* Public */,
       8,    0,   85,    2, 0x06 /* Public */,
       9,    0,   86,    2, 0x06 /* Public */,
      10,    0,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   88,    2, 0x08 /* Private */,
      12,    1,   91,    2, 0x08 /* Private */,
      13,    1,   94,    2, 0x08 /* Private */,
      14,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void create_shape_gui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        create_shape_gui *_t = static_cast<create_shape_gui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reset(); break;
        case 1: _t->close(); break;
        case 2: _t->shape_changed(); break;
        case 3: _t->createLine(); break;
        case 4: _t->createRect(); break;
        case 5: _t->createEllipse(); break;
        case 6: _t->createPolygon(); break;
        case 7: _t->something_changed(); break;
        case 8: _t->selectByRegion(); break;
        case 9: _t->createShape((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->pen_color_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->cap_style_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->join_style_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::reset)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::close)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::shape_changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::createLine)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::createRect)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::createEllipse)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::createPolygon)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::something_changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (create_shape_gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&create_shape_gui::selectByRegion)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject create_shape_gui::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_create_shape_gui.data,
      qt_meta_data_create_shape_gui,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *create_shape_gui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *create_shape_gui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_create_shape_gui.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int create_shape_gui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void create_shape_gui::reset()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void create_shape_gui::close()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void create_shape_gui::shape_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void create_shape_gui::createLine()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void create_shape_gui::createRect()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void create_shape_gui::createEllipse()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void create_shape_gui::createPolygon()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void create_shape_gui::something_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void create_shape_gui::selectByRegion()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
