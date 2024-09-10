/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../AD9122/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[28];
    char stringdata0[378];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_save_button_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 22), // "on_load_button_clicked"
QT_MOC_LITERAL(4, 58, 24), // "on_toggle_button_clicked"
QT_MOC_LITERAL(5, 83, 25), // "createComboBoxWidgetLable"
QT_MOC_LITERAL(6, 109, 8), // "QWidget*"
QT_MOC_LITERAL(7, 118, 9), // "labelText"
QT_MOC_LITERAL(8, 128, 7), // "options"
QT_MOC_LITERAL(9, 136, 20), // "createCheckBoxWidget"
QT_MOC_LITERAL(10, 157, 10), // "QCheckBox*"
QT_MOC_LITERAL(11, 168, 13), // "CheckBoxState"
QT_MOC_LITERAL(12, 182, 5), // "state"
QT_MOC_LITERAL(13, 188, 28), // "createLineEditWithSaveButton"
QT_MOC_LITERAL(14, 217, 8), // "rowIndex"
QT_MOC_LITERAL(15, 226, 10), // "valueLimit"
QT_MOC_LITERAL(16, 237, 6), // "modulo"
QT_MOC_LITERAL(17, 244, 15), // "placeholderText"
QT_MOC_LITERAL(18, 260, 8), // "errorMsg"
QT_MOC_LITERAL(19, 269, 11), // "defaultText"
QT_MOC_LITERAL(20, 281, 11), // "LineOfPower"
QT_MOC_LITERAL(21, 293, 16), // "setEditableFlags"
QT_MOC_LITERAL(22, 310, 14), // "QStandardItem*"
QT_MOC_LITERAL(23, 325, 4), // "item"
QT_MOC_LITERAL(24, 330, 8), // "editable"
QT_MOC_LITERAL(25, 339, 12), // "blockEditing"
QT_MOC_LITERAL(26, 352, 19), // "QStandardItemModel*"
QT_MOC_LITERAL(27, 372, 5) // "model"

    },
    "MainWindow\0on_save_button_clicked\0\0"
    "on_load_button_clicked\0on_toggle_button_clicked\0"
    "createComboBoxWidgetLable\0QWidget*\0"
    "labelText\0options\0createCheckBoxWidget\0"
    "QCheckBox*\0CheckBoxState\0state\0"
    "createLineEditWithSaveButton\0rowIndex\0"
    "valueLimit\0modulo\0placeholderText\0"
    "errorMsg\0defaultText\0LineOfPower\0"
    "setEditableFlags\0QStandardItem*\0item\0"
    "editable\0blockEditing\0QStandardItemModel*\0"
    "model"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    2,   62,    2, 0x08 /* Private */,
       9,    2,   67,    2, 0x08 /* Private */,
      13,    6,   72,    2, 0x08 /* Private */,
      20,    5,   85,    2, 0x08 /* Private */,
      21,    2,   96,    2, 0x08 /* Private */,
      25,    1,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 6, QMetaType::QString, QMetaType::QStringList,    7,    8,
    0x80000000 | 10, QMetaType::QString, 0x80000000 | 11,    7,   12,
    0x80000000 | 6, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   16,   17,   18,   19,
    0x80000000 | 6, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   17,   18,   19,
    QMetaType::Void, 0x80000000 | 22, QMetaType::Bool,   23,   24,
    QMetaType::Void, 0x80000000 | 26,   27,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_save_button_clicked(); break;
        case 1: _t->on_load_button_clicked(); break;
        case 2: _t->on_toggle_button_clicked(); break;
        case 3: { QWidget* _r = _t->createComboBoxWidgetLable((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 4: { QCheckBox* _r = _t->createCheckBoxWidget((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< CheckBoxState(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QCheckBox**>(_a[0]) = std::move(_r); }  break;
        case 5: { QWidget* _r = _t->createLineEditWithSaveButton((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 6: { QWidget* _r = _t->LineOfPower((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setEditableFlags((*reinterpret_cast< QStandardItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->blockEditing((*reinterpret_cast< QStandardItemModel*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
