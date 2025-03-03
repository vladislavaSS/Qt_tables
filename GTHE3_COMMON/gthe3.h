#ifndef GTHE3_H
#define GTHE3_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QPushButton>

#include "CustomItem.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

class GTHE3 : public QWidget
{
    Q_OBJECT
public:

    explicit GTHE3(QWidget *parent = nullptr);
    QString dec2hex(QString data, QStandardItem *item);
    QString dec2bin(const QString& decimalStr, int bitWidth);
    QString bin2hex(const QString& binaryStr);
    QString bin2dec(const QString& binaryString);
    QString hex2bin(QString &hexString);

private:

    QTableView *tableView;
    QStandardItemModel *model;
    QVBoxLayout *layout;

    QPushButton *saveButton;
    QPushButton *loadButton;

    CustomItem *cust = new CustomItem();

private slots:

    void loadJsonData(const QString &fileName);

    void saveData();
    void loadData();

};


#endif // GTHE3_H
