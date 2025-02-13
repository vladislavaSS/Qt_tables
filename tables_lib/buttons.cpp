#include "functions.h"
#include <iostream>


#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

int Tables::getTotalHeight(QTreeView *treeView, const QModelIndex &index) {

    int totalHeight = 0;

    for (int row = 0; row < index.model()->rowCount(index); ++row) {
        QModelIndex childIndex = index.model()->index(row, 1, index);
        QWidget *widget = treeView->indexWidget(childIndex);
        if (widget)
            totalHeight += widget->sizeHint().height();
    }
    return totalHeight;

}

void Tables::on_toggle_button_clicked()
{
  if (treeExpanded) {
    treeView->collapseAll();
//    if (ADflag) {
//      treeView->setMinimumHeight(1050);
//      emit heightChanged(1100);
//    } if (LMKflag) {
//      treeView->setMinimumHeight(200);
//      emit heightChanged(250);
//    }
    toggleButton->setText("Expand All");

  } else {
    treeView->expandAll();
    toggleButton->setText("Collapse All");
  }

  total = treeView->size().height();
  treeExpanded = !treeExpanded;

}

void Tables::onItemClicked(const QModelIndex& index) {

  QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
  QStandardItem* item = model->itemFromIndex(index);

  if (item != nullptr) {

      rapidjson::StringBuffer buf;
      rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
      saveItem(item, writer);

//      qDebug() << "JSON Document:" << buf.GetString();

      if (buf.GetSize())
        emit needSendState(buf);

      buf.Clear();
  }
}

void Tables::hasChildren (QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Document &document, QStandardItemModel* model, QTreeView* treeView, bool read) {

  QString Result;
  bool reg_flag = false;

  if (LMKflag) Result = "";

  if (selectedItem->text() == "Clock Receiver Control" || selectedItem->text() == "CLKin_SELECT" || selectedItem->text() == "0x09" || selectedItem->text() == "0x14")
    reg_flag = true;

  int bitNumber = 0;
  QString text = "";

  for (int j = 0; j < selectedItem->rowCount(); j++) {
    QStandardItem* child = selectedItem->child(j);

    if (child) {

      QModelIndex index = model->index(j, 1, selectedItem->index());
      QWidget* widget = treeView->indexWidget(index);

      if (widget && index.isValid()) {
          if (!LMKflag) Result = "";
          int countWid = 0;

          for (QWidget* child : widget->findChildren<QWidget*>()) {
            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(child)) {

              countWid += 1;
              QString value;

              text = line2hex(lineEdit, value, text);

              if (!LMKflag) Result = hex2Json(Result, text, lineEdit->property("bitNumber").toInt(), bitCount);
              else Result = hex2Json(Result, text, lineEdit->property("bitNumber").toInt(), bitCount);

            } else if (QCheckBox* checkBox = qobject_cast<QCheckBox*>(child)) {

              countWid += 1;
              QString checkBoxValue;
              checkBoxValue = check2hex(checkBox, checkBoxValue);
              if (reg_flag && (checkBox->property("bitName") == "Vboost"))
                  Result = QString(bitCount - bitNumber - 2, '0') + checkBoxValue + '1';
              Result = hex2Json(Result, checkBoxValue, checkBox->property("bitNumber").toInt(), bitCount);

            } else if (QComboBox* comboBox = qobject_cast<QComboBox*>(child)) {

              countWid += 1;
              QString numericPart = combo2hex(comboBox);
              if (!LMKflag) Result = hex2Json(Result, numericPart, comboBox->property("bitNumber").toInt(), bitCount);
              else Result = hex2Json(Result, numericPart, comboBox->property("bitNumber").toInt(), bitCount);

            }
          }

          if (ADflag || HMCflag) {

            for (QChar ch : Result) {
              if (ch == "?") {
                Result = "N/A";
                break;
              }
            }

            if (Result.size() < bitCount && !Result.isEmpty() && Result != "N/A") {
              if (reg_flag) Result += QString(bitCount - Result.size(), '1');
              if (countWid == 1) Result = QString(bitCount - Result.size(), '0') + Result;
              else if (ADflag) Result += QString(bitCount - Result.size(), '0');

            }

            if (Result.isEmpty()) Result = "N/A";
            if (!bin2hex(Result).isEmpty()) Result = "0x" + bin2hex(Result);

          } else if (LMKflag && reg_flag) {
            QString last = dec2bin(selectedItem->text().remove("0x"), 4);
            if (child->text() == "Vboost") {
              Result += "001010100000" + last;
              Result = "0x" + bin2hex(Result);
            } else if (j == 2){
              Result = '1' + Result.mid(2) + QString(22, '0') + last;
              Result = "0x" + bin2hex(Result);
            }
          }

          rapidjson::Value resultValue(rapidjson::kObjectType);

          if (HMCflag && selectedItem->text() == "0x05") Result = "0x05 " + Result;

          if (!LMKflag) {

            fileForm(resultValue, child->text(), Result, allocator);
            document.PushBack(resultValue, allocator);
          }
          if (LMKflag && (selectedItem->text() == "0x09" || (selectedItem->text() == "0x14" && j == 2)) && Result != "N/A") {

            fileForm(resultValue, selectedItem->text(), Result, allocator);
            document.PushBack(resultValue, allocator);
          }
        }
    }
  }
  if (LMKflag && !reg_flag && Result != "N/A") {

    QString last = dec2bin(selectedItem->text().remove("0x0"), 4);
    if (last.size() < 4) last = QString(4 - last.size(), '0') + last;
    Result = Result + last;
    Result = "0x" + bin2hex(Result);
    QString addr = selectedItem->text().remove('R');

    rapidjson::Value finalResult(rapidjson::kObjectType);

    fileForm(finalResult, addr, Result, allocator);
    document.PushBack(finalResult, allocator);
  }


}

void Tables::saveItem(QStandardItem *selectedItem, rapidjson::PrettyWriter<rapidjson::StringBuffer> &wr) {

  rapidjson::Document document;
  document.SetArray();
  rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

  QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());

  hasChildren(selectedItem, allocator, document, model, treeView, read);

  if (!document.Empty()) document.Accept(wr);

}

void Tables::serialized(/*rapidjson::PrettyWriter<rapidjson::StringBuffer> &wr, bool read*/) {

  rapidjson::Document document;
  document.SetArray();
  rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

  QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
  QStandardItem* rootItem = model->invisibleRootItem();

  for (int i = 0; i < rootItem->rowCount(); ++i) {
    QStandardItem* item = rootItem->child(i);

//    if (item->child(0)) hasChildren(item, allocator, document, model, treeView, read);
    if (item->child(0)->text() == "0x05" ) hasChildren(item->child(0), allocator, document, model, treeView, read);
  }

//  document.Accept(wr);

  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  document.Accept(writer);

//  qDebug() << "JSON Document:" << buffer.GetString();

  QFile file("output.json");
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      out << buffer.GetString();
      file.close();
  }

}

void Tables::updateChildWidgets(QStandardItemModel* model, QString dataString, QStandardItem* item, QString readItem) {

    for (int i = 0; i < item->rowCount(); i++) {
      for (int j = 0; j < item->columnCount(); j++) {

     QStandardItem* item_sec;

     if (!LMKflag) item_sec = item->child(i, j);
     else item_sec = item;


     if (item_sec && item_sec->text() == readItem) {
       if (dataString.startsWith("0x05 ")) dataString = dataString.remove("0x05 ");

       QString binaryData = hex2bin(dataString);

       QModelIndex index = model->index(i, 1, item->index());
       QWidget* widget = treeView->indexWidget(index);

       if (widget && index.isValid()) {

        for (QWidget* child : widget->findChildren<QWidget*>()) {

          if (!binaryData.isEmpty() && binaryData != "N/A") {

            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(child)) {

              int bitNumber = lineEdit->property("bitNumber").toInt();
              int bitWidth = lineEdit->property("bitWidth").toInt();

              QString data = binaryData.mid(bitCount - bitNumber - 1, bitWidth);
              if (readItem != "0x003") data = bin2dec(data);
              setTextLine(lineEdit, data);

            } else if (QCheckBox* checkBox = qobject_cast<QCheckBox*>(child)) {

              int bitNumber = checkBox->property("bitNumber").toInt();
              QString data = binaryData.mid(bitCount - bitNumber - 1, 1);

              if (data == "1") {
                checkBox->setChecked(true);
              } else if (data == "0") {
                checkBox->setChecked(false);
              }

            }
            else if (QComboBox* comboBox = qobject_cast<QComboBox*>(child)) {

              int bitNumber = comboBox->property("bitNumber").toInt();
              int bitWidth = comboBox->property("bitWidth").toInt();
              QString value = binaryData.mid(bitCount - bitNumber - 1, bitWidth);

              if (readItem == "0x003" || readItem == "0x1D" || readItem == "0x1E") value = bin2dec(value);
              setTextCombo(comboBox, value);
            }

          } else if (binaryData == "N/A") {

            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(child)) {
              lineEdit->setText(bin2dec(lineEdit->property("default").toString()));

            } else if (QCheckBox* checkBox = qobject_cast<QCheckBox*>(child)) {
              QString property = checkBox->property("default").toString();

              switch (property.toInt()) {
                  case 0: { checkBox->setChecked(0); break;
                } case 1: { checkBox->setChecked(1); break;
                } case 2: {
                    checkBox->setCheckState(Qt::PartiallyChecked);
                    checkBox->setTristate(true);
                    break;
                }
              }
            }
            else if (QComboBox* comboBox = qobject_cast<QComboBox*>(child))
              comboBox->setCurrentText(comboBox->property("default").toString());

          } else continue;
        }
      }
    }
  }
}


}

void Tables::deserialized(/*const rapidjson::Value& jsonArray*/)
{

    QFile file("output.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file for reading");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    if (!jsonDoc.isArray()) {
        qWarning("JSON is not an array");
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView->model());

    for (int i = 0; i < model->rowCount(); ++i) {
        QStandardItem* item = model->item(i);
        if (item && item->hasChildren()) {
            QStringList addresses;
            QStringList datalist;

            QStringList childAddresses;
            QStringList childDatalist;

            bool childflag = 0;

            for (const auto& value : jsonArray) {
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    if (obj.contains("Data") && obj["Data"].isString()) {
                        if (obj["Data"].toString().startsWith("0x05 ")) {
                            childDatalist.append(obj["Data"].toString());
                            childflag = 1; }
                        else datalist.append(obj["Data"].toString());
                    }

                    if (obj.contains("Addr") && obj["Addr"].isString()) {
                        if (!childflag) addresses.append(obj["Addr"].toString());
                        else childAddresses.append(obj["Addr"].toString());
                        childflag = 0;
                    }
                }
            }

            for (int index = 0; index < qMin(addresses.size(), datalist.size()); ++index) {
                if ((item->text() == addresses[index] && LMKflag) || !LMKflag) {
                    updateChildWidgets(model, datalist[index], item, addresses[index]);
                }
            }

            if (item->hasChildren()) {

              for (int j = 0; j < item->rowCount(); ++j) {
                  if (item->child(j)->hasChildren())
                    for (int k = 0; k < item->child(j)->rowCount(); ++k) {

                        for (int index = 0; index < qMin(childAddresses.size(), childDatalist.size()); ++index) {
                            if (item->child(j)->child(k)->text() == childAddresses[index]) {
                                updateChildWidgets(model, childDatalist[index], item->child(j), childAddresses[index]);
                            }
                        }
                    }
               }
            }

        }
    }




//  QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());

//  QString readItem = "";
//  QString data = "";

//  for (int i = 0; i < model->rowCount(); ++i) {
//    QStandardItem* item = model->item(i);
//    if (item && item->hasChildren()) {
//      QStringList addresses;
//      QStringList datalist;

//      for (const auto& value : jsonArray.GetArray()) {
//        if (value.HasMember("Addr") && value["Addr"].IsString()) {
//          addresses.append(QString::fromStdString(value["Addr"].GetString()));
//        }

//        if (value.HasMember("Data") && value["Data"].IsString()) {
//          datalist.append(QString::fromStdString(value["Data"].GetString()));
//        }
//      }

//      for (int index = 0; index < qMin(addresses.size(), datalist.size()); ++index) {
//        if ((item->text() == addresses[index] && LMKflag) || !LMKflag) updateChildWidgets(model, datalist[index], item, addresses[index]);
//      }
//    }
//  }


}


