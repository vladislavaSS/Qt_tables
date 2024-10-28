#ifndef LMK1000WIDGET_H
#define LMK1000WIDGET_H

#include <QMainWindow>
#include <QPushButton>
#include <QTreeView>
#include <QStandardItemModel>

#include "rapidjson/document.h"
//#include "rapidjson/error/en.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

class LMK1000Widget : public QWidget
{
    Q_OBJECT
public:
    explicit LMK1000Widget(QWidget *parent = nullptr);

private slots:

    QWidget* createLineEditWithSaveButton(int valueLimit, int modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText);

    void on_save_button_clicked();

    void load(const QString& filePath);

    void load_all();

    void load_element();

    void on_toggle_button_clicked();

    void saveItem(QStandardItem *selectedParentItem);

    void hasChildren(QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Value &jsonItem, QStandardItemModel* model, QTreeView* treeView, bool HCMflag);

    void onParentItemClicked(const QModelIndex& index);

    void setupWidgets(QStandardItem *itm, int rowIndex, QModelIndex lineEditIndex);

    void setEditableFlags(QStandardItem *item, bool editable);

    void blockEditing(QStandardItemModel *model);

    void updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& dataArray, QStandardItem* parentItem);

private:

    bool HCMflag = 0;

    void viewTree();

    QTreeView *treeView;

    QStandardItemModel *model;

    QPushButton *toggleButton;

    QPushButton *saveButton;

    QPushButton *loadButton;

    QPushButton *save_elem;

    QPushButton *load_elem;

    bool treeExpanded;

};

#endif // LMK1000WIDGET_H
