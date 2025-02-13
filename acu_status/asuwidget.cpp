#include "asuwidget.h"

asuWidget::asuWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    setLayout(layout);

    layout->addWidget(tabWidgetK);
    layout->addWidget(tabWidgetZ);

    tableK();
    tableZ();
    deserialized(path);

}

void asuWidget::tableK() {

    QTableView *tableViewK = new QTableView();
    model1 = new QStandardItemModel(0, 5);
    model1->setHorizontalHeaderLabels({"name", "addr", "capacity", "voltage", "power"});
    tableViewK->setModel(model1);
    tabWidgetK->addTab(tableViewK, "k");

}

void asuWidget::tableZ() {

    QTableView *tableViewZ = new QTableView();
    model2 = new QStandardItemModel(0, 5);
    model2->setHorizontalHeaderLabels({"name", "addr", "capacity", "voltage", "power"});
    tableViewZ->setModel(model2);
    tabWidgetZ->addTab(tableViewZ, "z");

}

void asuWidget::deserialized(QString path){

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "Не удалось открыть файл для чтения!";
      return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    rapidjson::Document jsonDoc;
    jsonDoc.Parse(jsonData.constData());

    if (jsonDoc.HasParseError()) {
      qDebug() << "Не удалось прочитать файл";
      qDebug() << "JSON parse error at offset:" << jsonDoc.GetErrorOffset();
      return;
    }

    while (model1->rowCount() > 0) model1->removeRow(0);
    while (model2->rowCount() > 0) model2->removeRow(0);

    const rapidjson::Value& jsonArrayK = jsonDoc["k"];

    for (size_t i = 0; i < jsonArrayK.Size(); ++i) {
        const rapidjson::Value& jsonObject = jsonArrayK[i];

        if (jsonObject.IsObject()) {

            QStandardItem *nameItem = new QStandardItem(QString::fromStdString(jsonObject["name"].GetString()));
            QStandardItem *addrItem = new QStandardItem(QString::fromStdString(jsonObject["addr"].GetString()));
            QStandardItem *capacityItem = new QStandardItem(QString::number(jsonObject["c"].GetDouble()));
            QStandardItem *voltageItem = new QStandardItem(QString::number(jsonObject["v"].GetDouble()));
            QStandardItem *powerItem = new QStandardItem(QString::number(jsonObject["p"].GetDouble()));

            model1->appendRow({nameItem, addrItem, capacityItem, voltageItem, powerItem});
        }

    }

    const rapidjson::Value& jsonArrayZ = jsonDoc["z"];

    for (size_t i = 0; i < jsonArrayZ.Size(); ++i) {
        const rapidjson::Value& jsonObject = jsonArrayZ[i];

        if (jsonObject.IsObject()) {
            QStandardItem *nameItem = new QStandardItem(QString::fromStdString(jsonObject["name"].GetString()));
            QStandardItem *addrItem = new QStandardItem(QString::fromStdString(jsonObject["addr"].GetString()));
            QStandardItem *capacityItem = new QStandardItem(QString::number(jsonObject["c"].GetDouble()));
            QStandardItem *voltageItem = new QStandardItem(QString::number(jsonObject["v"].GetDouble()));
            QStandardItem *powerItem = new QStandardItem(QString::number(jsonObject["p"].GetDouble()));

            model2->appendRow({nameItem, addrItem, capacityItem, voltageItem, powerItem});
        }
    }


}






