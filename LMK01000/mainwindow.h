#define MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>

#include <QDebug>
#include <QPushButton>


#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QComboBox>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <QXmlStreamWriter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}
using namespace rapidjson;

struct WidgetPointers {
    QComboBox* comboBox;
    QLineEdit* lineEdit;

    WidgetPointers() : comboBox(nullptr), lineEdit(nullptr) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_save_button_clicked();

    void on_load_button_clicked();

    QWidget* createLineEditWithSaveButton(int valueLimit, int modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText);

    void setupWidgets(QStandardItem *itm, int rowIndex, QModelIndex lineEditIndex);

    void on_toggle_button_clicked();

    void setEditableFlags(QStandardItem *item, bool editable);

    void blockEditing(QStandardItemModel *model);

    void updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& childrenArray, QStandardItem* parentItem);

    void onClicked(QLineEdit* lineEdit, int valueLimit, int modulo, const QString& errorMsg, const QString& defaultText);

private:
    Ui::MainWindow *ui;

    void viewTree();

    QTreeView *treeView;

    QStandardItemModel *model;

    QComboBox *comboBox;

    QString selectedValueFromCase1;

    QPushButton *toggleButton;

    QPushButton *saveButton;

    QPushButton *loadButton;

    bool treeExpanded;

};
