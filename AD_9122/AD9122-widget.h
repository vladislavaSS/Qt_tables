#ifndef AD9122WIDGET_H
#define AD9122WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <fstream>
#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
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
    void on_save_button_clicked();

    void on_load_button_clicked();

    void on_toggle_button_clicked();

    void updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& childrenArray, QStandardItem* parentItem);

    QWidget* createComboBoxWidgetLable(const QString &labelText, const QStringList &options);

    QCheckBox* createCheckBoxWidget(const QString &labelText, CheckBoxState state);

    QWidget* createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText);

    QWidget* LineOfPower(int rowIndex, int valueLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText);

    void setEditableFlags(QStandardItem *item, bool editable);

    void blockEditing(QStandardItemModel *model);

private:

    void viewTree();

    QTreeView *treeView;

    QStandardItemModel *model;

    QPushButton *toggleButton;

    QPushButton *saveButton;

    QPushButton *loadButton;

    bool treeExpanded;

};

#endif // AD9122WIDGET_H
