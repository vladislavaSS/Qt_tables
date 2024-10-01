#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HCM1035-widget.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <QXmlStreamWriter>

//extern QStringList itemNames;
//extern QStringList childName1;
//extern QStringList childName2;
//enum CheckBoxState {
//    Unchecked = 0,
//    Checked = 1,
//    Undefined = 2
//};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); /*: QMainWindow(parent) {
            NewWidget *newWidget = new NewWidget(this);

            setCentralWidget(newWidget);
        }*/



//private slots:

//    void on_save_button_clicked();

//    void on_load_button_clicked();

//    void updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& childrenArray, QStandardItem* parentItem);

//    void on_toggle_button_clicked();

//    void setEditableFlags(QStandardItem *item, bool editable);

//    void blockEditing(QStandardItemModel *model);

//    QWidget* createLineEditWithSaveButton(int rowIndex, double valueLimit, double minLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText);

//    QCheckBox* createCheckBoxWidget(const QString &labelText, CheckBoxState state);

//    QWidget* createComboBoxWidgetLable(const QString &labelText, const QStringList &options);

//    QWidget* LineEdit(const QString& labelText, const QString& placeholderText);

//private:
    Ui::MainWindow *ui;

//    void viewTree();

//    QTreeView *treeView;

//    QStandardItemModel *model;

//    QPushButton *toggleButton;

//    QPushButton *saveButton;

//    QPushButton *loadButton;

//    bool treeExpanded;
};
#endif // MAINWINDOW_H
