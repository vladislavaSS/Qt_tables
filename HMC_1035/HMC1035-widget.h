#ifndef NEWWIDGET_H
#define NEWWIDGET_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QCheckBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QComboBox>
#include <QCheckBox>
#include <cmath>
#include <QLabel>
#include <QFile>
#include <fstream>

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

class HMC1035Widget : public QWidget
{
    Q_OBJECT
public:
    explicit HMC1035Widget(QWidget *parent = nullptr);

    bool ADflag = 0;

    bool LMKflag = 0;

    QTreeView *treeView;

    QStandardItemModel *model;

    QPushButton *toggleButton;

    QPushButton *saveButton;

    QPushButton *loadButton;

    QPushButton *save_elem;

    QPushButton *load_elem;

    bool treeExpanded;

private slots:

    QWidget* createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText, int bitNumber, int bitWidth);

    QWidget* createComboBoxWidgetLable(const QString &labelText, const QStringList &options, int bitNumber, int bitWidth);

    QWidget* LineEdit(const QString& labelText, const QString& placeholderText);

    QCheckBox* createCheckBoxWidget(const QString &labelText, CheckBoxState state, int bitNumber, int bitWidth);

    QString bin2hex(const QString& binaryStr);

    QString hex2Json(QString& Result, QString& text, int bitNumber, int bitCount);

    QString dec2bin(const QString& decimalStr, int bitWidth);

    QString hex2bin(QString &hexString);

    QString bin2dec(const QString& binaryString);

    bool isBinary(const QString &numericPart);

    void on_save_button_clicked();

    void load(const QString& filePath);

    void load_all();

    void load_element();

    void on_toggle_button_clicked();

    void saveItem(QStandardItem *selectedParentItem);

    void hasChildren(QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Value &jsonArray, QStandardItemModel* model, QTreeView* treeView);

    void onParentItemClicked(const QModelIndex& index);

    void updateChildWidgets(QStandardItemModel* model, QString dataString, QStandardItem* parentItem, QString readItem);

    void setEditableFlags(QStandardItem *item, bool editable);

    void blockEditing(QStandardItemModel *model);

private:

    bool HMCflag = 1;

    int bitCount = 24;

    void viewTree();

signals:

};

#endif // NEWWIDGET_H
