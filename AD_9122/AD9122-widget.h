#ifndef AD9122WIDGET_H
#define AD9122WIDGET_H

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
#include <QXmlStreamWriter>

extern QStringList itemNames;
extern QStringList regNames;
enum CheckBoxState {
    Unchecked = 0,
    Checked = 1,
    Undefined = 2
};

class AD9122Widget : public QWidget
{
    Q_OBJECT
public:
    explicit AD9122Widget(QWidget *parent = nullptr);

private slots:

    QWidget* createComboBoxWidgetLable(const QString &labelText, const QStringList &options, int bitNumber);

    QWidget* createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText, int bitNumber);

    QWidget* LineOfPower(int rowIndex, int valueLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText);

    QWidget* LineEdit(const QString& labelText, const QString& placeholderText);

    QCheckBox* createCheckBoxWidget(const QString &labelText, CheckBoxState state, int bitNumber);

    void on_save_button_clicked();

    void load(const QString& filePath);

    void load_all();

    void load_element();

    void on_toggle_button_clicked();

    void saveItem(QStandardItem *selectedParentItem);

    void hasChildren(QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Value &jsonItem, QStandardItemModel* model, QTreeView* treeView, bool HCMflag);

    void onParentItemClicked(const QModelIndex& index);

    void updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& dataArray, QStandardItem* parentItem);

    void onItemChanged(QStandardItem* item);

    void setEditableFlags(QStandardItem *item, bool editable);

    void blockEditing(QStandardItemModel *model);

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

#endif // AD9122WIDGET_H
