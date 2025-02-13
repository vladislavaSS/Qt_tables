#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
#include <QWidget>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

class Tables : public QWidget
{
    Q_OBJECT
public:

    explicit Tables(QWidget* parent = nullptr);

    bool read = 0;
    bool treeExpanded = 0;
    bool isBinary(const QString &numericPart);
    bool LMKflag;
    bool HMCflag;
    bool ADflag;

    QTreeView *treeView;

    QStandardItemModel *model;

    QPushButton *toggleButton;
    QPushButton *saveButton;
    QPushButton *loadButton;

    QVBoxLayout *layout;

    int getTotalHeight(QTreeView *treeView, const QModelIndex &index);
    int total = 1050;
    int bitCount;

    QString bin2hex(const QString& binaryStr);
    QString hex2Json(QString& Result, QString& text, int bitNumber, int bitCount);
    QString dec2bin(const QString& decimalStr, int bitWidth);
    QString hex2bin(QString &hexString) ;
    QString bin2dec(const QString& binaryString);
    QString line2hex(QLineEdit *lineEdit, QString value, QString text);
    QString combo2hex(QComboBox *comboBox);
    QString check2hex(QCheckBox *checkBox, QString checkBoxValue);

    void serialized(/*rapidjson::PrettyWriter<rapidjson::StringBuffer> &wr, bool read*/);
    void deserialized(/*const rapidjson::Value& jsonArray*/);
    void loadAll();
    void loadElement();
    void on_toggle_button_clicked();
    void saveItem(QStandardItem *selectedParentItem, rapidjson::PrettyWriter<rapidjson::StringBuffer> &wr);
    void hasChildren(QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Document &document, QStandardItemModel* model, QTreeView* treeView, bool read);
    void onItemClicked(const QModelIndex& index);
    void updateChildWidgets(QStandardItemModel* model, QString dataString, QStandardItem* parentItem, QString readItem);
    void setEditableFlags(QStandardItem *item, bool editable);
    void blockEditing(QStandardItemModel *model);
    void fileForm(rapidjson::Value& resultValue, QString child, const QString& Result, rapidjson::Document::AllocatorType& allocator);
    void setTextLine(QLineEdit *lineEdit, QString data);
    void setTextCombo(QComboBox *comboBox, QString value);

private slots:

signals:

    void needSendState(rapidjson::StringBuffer& sb);
    void heightChanged(int height);

};



#endif // FUNCTIONS_H
