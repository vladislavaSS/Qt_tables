#ifndef NEWWIDGET_H
#define NEWWIDGET_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QCheckBox>

#include "rapidjson/document.h"
//#include "rapidjson/error/en.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

extern QStringList itemNames;
extern QStringList childName1;
extern QStringList childName2;
enum CheckBoxState {
    Unchecked = 0,
    Checked = 1,
    Undefined = 2
};

class HCM1035Widget : public QWidget
{
    Q_OBJECT
public:
    explicit HCM1035Widget(QWidget *parent = nullptr);

    void viewTree();

private slots:

    QWidget* createLineEditWithSaveButton(int rowIndex, double valueLimit, double minLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText);

    QWidget* createComboBoxWidgetLable(const QString &labelText, const QStringList &options);

    QWidget* LineEdit(const QString& labelText, const QString& placeholderText);

    QCheckBox* createCheckBoxWidget(const QString &labelText, CheckBoxState state);

    void on_save_button_clicked();

    void load(const QString& filePath);

    void load_all();

    void load_element();

    void on_toggle_button_clicked();

    void saveItem(QStandardItem *selectedParentItem);

    void hasChildren(QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Value &jsonItem, QStandardItemModel* model, QTreeView* treeView, bool HCMflag);

    void onParentItemClicked(const QModelIndex& index);

    void updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& dataArray, QStandardItem* parentItem);

    void setEditableFlags(QStandardItem *item, bool editable);

    void blockEditing(QStandardItemModel *model);

private:

    bool HCMflag = 0;

    QTreeView *treeView;

    QStandardItemModel *model;

    QPushButton *toggleButton;

    QPushButton *saveButton;

    QPushButton *loadButton;

    QPushButton *save_elem;

    QPushButton *load_elem;

    bool treeExpanded;

signals:

};

#endif // NEWWIDGET_H
