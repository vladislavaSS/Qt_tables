#ifndef LMK1000WIDGET_H
#define LMK1000WIDGET_H

#include <QMainWindow>
#include <QPushButton>
#include <QTreeView>
#include <QStandardItemModel>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>
#include <fstream>
#include <QFile>
#include <cmath>


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

    bool HCMflag = 0;

    bool ADflag = 0;

private slots:

    QWidget* createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText, int bitNumber, int bitWidth);

    QString bin2hex(const QString& binaryStr);

    QString hex2Json(QString& Result, QString& text, int bitNumber, int bitCount);

    QString dec2bin(const QString& decimalStr, int bitWidth);

    QString hex2bin(QString &hexString);

    QString bin2dec(const QString& binaryString);

    bool isBinary(const QString &numericPart);

    void setupWidgets(QStandardItem *itm, int rowIndex, QModelIndex lineEditIndex);

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

    bool LMKflag = 1;

    int bitCount = 32;

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
