#ifndef AD9122WIDGET_H
#define AD9122WIDGET_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
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

    QWidget* createComboBoxWidgetLable(const QString &labelText, const QStringList &options, int bitNumber, int bitWidth);

    QWidget* createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText, int bitNumber, int bitWidth);

    QWidget* LineOfPower(int rowIndex, int valueLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText);

    QWidget* LineEdit(const QString& labelText, const QString& placeholderText);

    QCheckBox* createCheckBoxWidget(const QString &labelText, CheckBoxState state, int bitNumber, int bitWidth);

    QString bin2hex(const QString& binaryStr);

    QString hex2Json(QString& Result, QString& text, int bitNumber, int bitCount);

    QString dec2bin(const QString& decimalStr, int bitWidth);

    QString hex2bin(QString &hexString);

    QString bin2dec(const QString& binaryString);

    bool isBinary(const QString &numericPart);

    void on_save_button_clicked(rapidjson::PrettyWriter<rapidjson::StringBuffer> &wr);

    void saveData();

    void load(const rapidjson::Value& jsonArray);

    void load_all();

    void load_element();

    void on_toggle_button_clicked();

    void saveItem(QStandardItem *selectedParentItem, rapidjson::PrettyWriter<rapidjson::StringBuffer> &wr);

    void hasChildren(QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Document &document, QStandardItemModel* model, QTreeView* treeView);

    void onParentItemClicked(const QModelIndex& index);

    void updateChildWidgets(QStandardItemModel* model, QString dataString, QStandardItem* parentItem, QString readItem);

//    void onItemChanged(QStandardItem* item);

    void setEditableFlags(QStandardItem *item, bool editable);

    void blockEditing(QStandardItemModel *model);

signals:

    void needSendState(rapidjson::StringBuffer& sb);

private:

    rapidjson::StringBuffer buf;

    QTreeView *treeView;

    QStandardItemModel *model;

    QPushButton *toggleButton;

    QPushButton *saveButton;

    QPushButton *loadButton;

    QPushButton *save_elem;

    QPushButton *load_elem;

    bool treeExpanded;

    bool HCMflag = 0;

    bool LMKflag = 0;

    bool ADflag = 1;

    int bitCount = 8;

    QVBoxLayout *layout;

    void viewTree();

};

#endif // AD9122WIDGET_H
