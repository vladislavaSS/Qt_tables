#include "gthe3.h"
#include <QPair>


GTHE3::GTHE3(QWidget *parent)
  : QWidget (parent)
{
  tableView = new QTableView(this);
  model = new QStandardItemModel(this);
  layout = new QVBoxLayout(this);
  layout->addWidget(tableView);
  setLayout(layout);
  model->setHorizontalHeaderLabels(QStringList() << "DRP Address (Hex)" << " Attribute Name" << "Attribute Encoding");
  tableView->setModel(model);

  tableView->setColumnWidth(0, 200);
  tableView->setColumnWidth(1, 200);
  tableView->setColumnWidth(2, 200);
  tableView->setMinimumSize(800, 600);

//  loadJsonData("GTHE3_COMMON.json");
//  loadJsonData("GTHE3_CHANNEL.json");
  loadJsonData("GTHE4_CHANNEL.json");

  connect(model, &QStandardItemModel::itemChanged, this, [this](QStandardItem *item) {
    CustomItem *customItem = dynamic_cast<CustomItem*>(item);
    customItem->validate(item);
  });

  saveButton = new QPushButton("Save");
  layout->addWidget(saveButton);
  loadButton = new QPushButton("Load");
  layout->addWidget(loadButton);

  connect(saveButton, &QPushButton::clicked, this, &GTHE3::saveData);
  connect(loadButton, &QPushButton::clicked, this, &GTHE3::loadData);

}

QString GTHE3::hex2bin(QString &hexString) {

  bool ok;
  hexString = hexString.remove("0x").toUpper();
  int value = hexString.toLongLong(&ok, 16);
  if (!ok) return QString();
  QString binaryString = QString::number(value, 2);

  return binaryString.rightJustified(16, '0');

}

QString GTHE3::bin2dec(const QString& binaryString) {
  bool ok;
  long long decimalValue = binaryString.toLongLong(&ok, 2);
  if (!ok) return "";

  return QString::number(decimalValue);
}

QString GTHE3::bin2hex(const QString& binaryStr) {

  for (QChar c : binaryStr) if (c != '0' && c != '1') return QString();

  bool ok;
  quint64 decimalValue = binaryStr.toULongLong(&ok, 2);
  if (!ok) return QString();

  QString hexStr = QString::number(decimalValue, 16).toUpper();
  return hexStr;
}

QString GTHE3::dec2bin(const QString& decimalStr, int bitWidth) {

  bool ok;
  int decimalValue = decimalStr.toInt(&ok);
  if (!ok) return QString();
  QString binaryStr;
  if (decimalValue == 0) binaryStr = "0";
  else {
    while (decimalValue > 0) {
      binaryStr.prepend(QString::number(decimalValue % 2));
      decimalValue /= 2;
    }
  }

  if (binaryStr.size() < bitWidth) binaryStr = QString(bitWidth - binaryStr.size(), '0') + binaryStr;
  return binaryStr;

}

void GTHE3::loadJsonData(const QString &fileName) {

  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) return;

  QByteArray jsonData = file.readAll();
  file.close();

  QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));

  QJsonObject jsonObject = jsonDoc.object();
  QStandardItem *rootItem = model->invisibleRootItem();

  if (jsonObject.contains("fields")) {
    QJsonObject fieldsObject = jsonObject["fields"].toObject();

    if (fieldsObject.contains("registers")) {
      QJsonArray registersArray = fieldsObject["registers"].toArray();
      for (int row = 0; row < registersArray.size(); ++row) {
        QJsonObject registerObject = registersArray[row].toObject();

        QStandardItem *registerItem = new QStandardItem(registerObject["name"].toString());
        QStandardItem *addressItem = new QStandardItem(registerObject["address"].toString());
        registerItem->setFlags(registerItem->flags() & ~Qt::ItemIsEditable);
        addressItem->setFlags(registerItem->flags() & ~Qt::ItemIsEditable);

        QList<QStandardItem *> rowItems;
        rowItems.append(addressItem);
        rowItems.append(registerItem);

        CustomItem *valueItem = new CustomItem();

        if (registerObject.contains("data")) {
          QVariantList comboOptions;
          QJsonArray dataArray = registerObject["data"].toArray();
          for (const QJsonValue &dataValue : dataArray) {
              if (dataValue.isString()) {
                  QStringList splitValues = dataValue.toString().split(" - ");
                  for (const QString &value : splitValues) {
                      comboOptions.append(value.trimmed());
                  }
              }
          }

          if (!comboOptions.isEmpty()) {
            valueItem->setPropertyList("data", comboOptions);
            comboOptions.clear();
          }
        }

        rowItems.append(valueItem);

        QString attr = registerObject["Attribute Bits"].toString();
        QString drp = registerObject["DRP Bits"].toString();
        valueItem->setProperty("attrbits", attr);
        valueItem->setProperty("drpbits", drp);

        if (registerObject.contains("condition")) {
            QString cond = registerObject["condition"].toString();
            QString cond2 = "";

            if (cond.contains(',')) {
                QStringList parts = cond.split(',');
                if (parts.size() == 2) {
                    cond = parts[0];
                    cond2 = parts[1];

                }
            } else if (!cond.contains(" - ")) {
                cond2 = cond;
                cond = "";
            }

            if (!cond.isEmpty()) valueItem->setProperty("range", cond);
            if (!cond2.isEmpty()) valueItem->setProperty("diff", cond2);
        }

        rootItem->appendRow(rowItems);
      }
    }
  }



}

QString GTHE3::dec2hex(QString data, QStandardItem *item){

    CustomItem *customItem = dynamic_cast<CustomItem*>(item);
    QString attr = customItem->getProperty("attrbits").toString();
    QString drp = customItem->getProperty("drpbits").toString();

    int num1attr = 0;
    int num2attr = 0;
    int num1drp = 0;
    int num2drp = 0;
    int bitWidth = 0;
    if (attr.contains(":")) {
        QPair<int, int> pair(cust->split(attr, ":"));
        num1attr = pair.first;
        num2attr = pair.second;
    }
    if (drp.contains(":")) {
        QPair<int, int> pair(cust->split(drp, ":"));
        num1drp = pair.first;
        num2drp = pair.second;
    }

    if ((num1attr - num2attr) == (num1drp - num2drp) && !data.isEmpty())
        bitWidth = num1attr - num2attr + 1;

    //to bin
    data = dec2bin(data, bitWidth);
    data = data + QString(num2drp, '0');
    //to hex
    data = bin2hex(QString(15-data.size(), '0') + data);

    return data;
}

void GTHE3::saveData() {

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> wr(buffer);

    wr.StartObject();

    wr.Key("registers");
    wr.StartArray();
    for (int row = 0; row < model->rowCount(); ++row) {

      QStandardItem *addr = model->item(row, 0);
      QStandardItem *value = model->item(row, 2);

      if (value->data(Qt::ForegroundRole) == QColor("Red") && !value->text().isEmpty()) {
          qDebug() << "fault";
          return;
      }

      if (addr && value) {
        wr.StartObject();
          wr.Key("addr");
          wr.String(addr->text().toUtf8().constData());

          wr.Key("data");

          QString data = "0x" + dec2hex(cust->tbl2js(value), value);
          if (!value->text().isEmpty()) wr.String(data.toUtf8().constData());
          else wr.String("");

        wr.EndObject();
      }

    }
    wr.EndArray();
    wr.EndObject();


    QFile file("output.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(buffer.GetString(), buffer.GetSize());
    file.close();


}

void GTHE3::loadData() {

    QFile file("output.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file for reading");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();
    if (!jsonObject.contains("registers") || !jsonObject["registers"].isArray()) {
        qWarning("JSON does not contain 'registers' array");
        return;
    }

    QJsonArray jsonArray = jsonObject["registers"].toArray();
    for (int i = 0; i < model->rowCount(); ++i) {
        QJsonValue value = jsonArray[i];
        QJsonObject registerObject = value.toObject();
        QString addr = registerObject["addr"].toString();
        QStandardItem *item = model->item(i, 0);

        if (addr == item->text()) {
            QString data = registerObject["data"].toString();
            data = hex2bin(data);

            CustomItem *customItem = dynamic_cast<CustomItem*>(model->item(i, 2));
            QString limit = customItem->getProperty("drpbits").toString();
            QPair<int, int> pair(cust->split(limit, ":"));
            int max = pair.first;
            int min = pair.second;
            QString decTxt = cust->getData(model->item(i, 2), bin2dec(data.mid(15-max, max-min+1)));
            model->item(i, 2)->setText(decTxt);
        } else {
            qDebug() << "isn't register " << item->text() << "stop load";
            return;
        }

    }



}







