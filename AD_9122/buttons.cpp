#include "AD9122-widget.h"

void AD9122Widget::on_toggle_button_clicked()
{
    if (treeExpanded) {
            treeView->collapseAll();
            toggleButton->setText("Expand All");
        } else {
            treeView->expandAll();
            toggleButton->setText("Collapse All");
        }
        treeExpanded = !treeExpanded;
}

void AD9122Widget::onParentItemClicked(const QModelIndex& index) {

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
    QStandardItem* item = model->itemFromIndex(index);
    if (item != nullptr) {
        disconnect(save_elem, &QPushButton::clicked, this, nullptr);
        connect(save_elem, &QPushButton::clicked, this, [this, item]() {
            saveItem(item);
        });
    }

}

void AD9122Widget::hasChildren (QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Value &jsonArray, QStandardItemModel* model, QTreeView* treeView) {

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
                        bitNumber = lineEdit->property("bitNumber").toInt();
                        QString value;

                        if (lineEdit->property("lineEditName") == "Clock Output Dividers (0-510)"){
                            if (lineEdit->text() == "")
                                value = lineEdit->property("default").toString();
                            else value = lineEdit->text();
                            int intValue = value.toInt()/2;
                            value = QString::number(intValue);
                        } else if (lineEdit->property("lineEditName") == "Clock Output Delays (0-2250)") {
                            if (lineEdit->text() == "")
                                value = lineEdit->property("default").toString();
                            else value = lineEdit->text();
                            int intValue = value.toInt()/150;
                            value = QString::number(intValue);
                        } else {
                            if (lineEdit->text() == "")
                                value = lineEdit->property("default").toString();
                            else value = lineEdit->text();
                        }

                        text = dec2bin(value, lineEdit->property("bitWidth").toInt());

                        if (!LMKflag) Result = hex2Json(Result, text, lineEdit->property("bitNumber").toInt(), bitCount);
                        else Result = hex2Json(Result, text, bitNumber, bitCount);

                    } else if (QCheckBox* checkBox = qobject_cast<QCheckBox*>(child)) {

                        countWid += 1;
                        QString checkBoxValue;
                        if (checkBox->checkState() == Qt::PartiallyChecked)
                            checkBoxValue = "?";
                        else if (checkBox->isChecked())
                            checkBoxValue = "1";
                        else checkBoxValue = "0";
                        Result = hex2Json(Result, checkBoxValue, checkBox->property("bitNumber").toInt(), bitCount);

                    } else if (QComboBox* comboBox = qobject_cast<QComboBox*>(child)) {

                        countWid += 1;
                        bitNumber = comboBox->property("bitNumber").toInt();
                        QString comboBoxText = comboBox->currentText();
                        QStringList parts = comboBoxText.split(" ");
                        QString numericPart = parts.isEmpty() ? QString() : parts[0];
                        if (numericPart.size() > 2 || !(isBinary(numericPart))) numericPart = dec2bin(numericPart, comboBox->property("bitWidth").toInt());
                        if (!LMKflag) Result = hex2Json(Result, numericPart, comboBox->property("bitNumber").toInt(), bitCount);
                        else {
                            if (reg_flag && (comboBox->property("ComboBoxName") == "Vboost" || comboBox->property("ComboBoxName") == "CLKin_SELECT"))
                                Result = QString(bitCount - bitNumber - 2, '0') + '1' + numericPart;
                            else Result = hex2Json(Result, numericPart, bitNumber, bitCount);
                        }
                    }
                }

                if (ADflag) {

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

                    } if (Result.isEmpty()) Result = "N/A";

                    if (!bin2hex(Result).isEmpty()) Result = "0x" + bin2hex(Result);

                } else if (LMKflag && reg_flag) {
                    QString last = dec2bin(selectedItem->text().remove("0x"), 4);
                    if (child->text() == "Vboost") {
                        Result += "001010100000" + last;
                        Result = "0x" + bin2hex(Result);
                    } else if (j == 2){
                        Result += QString(22, '0') + last;
                        Result = "0x" + bin2hex(Result);
                    }
                }

                rapidjson::Value resultValue(rapidjson::kObjectType);

                if (!LMKflag) {
                    resultValue.AddMember(
                        rapidjson::Value("Addr", allocator),
                        rapidjson::Value(child->text().toStdString().c_str(), allocator),
                        allocator
                    );

                    resultValue.AddMember(
                        rapidjson::Value("Data", allocator),
                        rapidjson::Value(Result.toStdString().c_str(), allocator),
                        allocator
                    );
                    jsonArray.PushBack(resultValue, allocator);

                }
                if (LMKflag && (selectedItem->text() == "0x09" || (selectedItem->text() == "0x14" && j == 2))) {

                    resultValue.AddMember(
                        rapidjson::Value("Addr", allocator),
                        rapidjson::Value(selectedItem->text().toStdString().c_str(), allocator),
                        allocator
                    );

                    resultValue.AddMember(
                        rapidjson::Value("Data", allocator),
                        rapidjson::Value(Result.toStdString().c_str(), allocator),
                        allocator
                    );
                    jsonArray.PushBack(resultValue, allocator);

                }
            }
        }
    }
    if (LMKflag && !reg_flag) {

        QString last = dec2bin(selectedItem->text().remove("0x0"), 4);
        if (last.size() < 4) last = QString(4 - last.size(), '0') + last;
        Result = Result + last;
        Result = "0x" + bin2hex(Result);
        QString addr = selectedItem->text().remove('R');

        rapidjson::Value finalResult(rapidjson::kObjectType);
        finalResult.AddMember(
            rapidjson::Value("Addr", allocator),
            rapidjson::Value(addr.toStdString().c_str(), allocator),
            allocator);

        finalResult.AddMember(
            rapidjson::Value("Data", allocator),
            rapidjson::Value(Result.toStdString().c_str(), allocator),
            allocator
        );

        jsonArray.PushBack(finalResult, allocator);
    }

}

void AD9122Widget::saveItem(QStandardItem *selectedItem) {

    if (selectedItem->parent() != nullptr) {
        if (selectedItem->parent()->text() == "PLL" || selectedItem->parent()->text() == "VCO Subsystem") HCMflag = 1;
        else {
            QMessageBox::warning(this, "Ошибка", "Выберете регистр");
            return;
        }
    } else if (selectedItem->text() == "PLL" || selectedItem->text() == "VCO Subsystem") {
        QMessageBox::warning(this, "Ошибка", "Выберете регистр");
        return;
    } else selectedItem = selectedItem;


    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());

    rapidjson::Value jsonArray(rapidjson::kArrayType);

    if (HCMflag) hasChildren(selectedItem->parent(), allocator, jsonArray, model, treeView);
    else hasChildren(selectedItem, allocator, jsonArray, model, treeView);

    document.AddMember("Registers", jsonArray, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    QString filePath = "save_element.json";
    std::ofstream file(filePath.toStdString());

    if (file.is_open()) {
        file << buffer.GetString();
        file.close();
        QMessageBox::information(this, "Успех", "Файл успешно сохранен: " + filePath);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
    }


}

void AD9122Widget::on_save_button_clicked()
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
    QStandardItem* rootItem = model->invisibleRootItem();

    rapidjson::Value jsonArray(rapidjson::kArrayType);

    for (int i = 0; i < rootItem->rowCount(); ++i) {
        QStandardItem* item = rootItem->child(i);

        if (!item) continue;

        if (item->child(0)) hasChildren(item, allocator, jsonArray, model, treeView);
    }

    document.AddMember("Registers", jsonArray, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    QString filePath = "output.json";
    std::ofstream file(filePath.toStdString());

    if (file.is_open()) {
        file << buffer.GetString();
        file.close();
        QMessageBox::information(this, "Успех", "Файл успешно сохранен: " + filePath);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
    }

}

void AD9122Widget::updateChildWidgets(QStandardItemModel* model, QString dataString, QStandardItem* item, QString readItem) {

    for (int i = 0; i < item->rowCount(); i++) {
         for (int j = 0; j < item->columnCount(); j++) {

             QStandardItem* item_sec;

             if (!LMKflag) item_sec = item->child(i, j);
             else item_sec = item;

             if (item_sec && item_sec->text() == readItem) {

                 QString binaryData = hex2bin(dataString);

                 QModelIndex index = model->index(i, 1, item->index());
                 QWidget* widget = treeView->indexWidget(index);

                if (widget && index.isValid()) {

                    for (QWidget* child : widget->findChildren<QWidget*>()) {

                        if (!binaryData.isEmpty()) {

                            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(child)) {

                                int bitNumber = lineEdit->property("bitNumber").toInt();
                                int bitWidth = lineEdit->property("bitWidth").toInt();

                                QString data = binaryData.mid(bitCount - bitNumber - 1, bitWidth);
                                data = bin2dec(data);

                                if (lineEdit->property("lineEditName") == "Clock Output Dividers (0-510)") {
                                    int intdata = data.toInt()*2;
                                    lineEdit->setText(QString::number(intdata));
                                } else if (lineEdit->property("lineEditName") == "Clock Output Delays (0-2250)") {
                                    int intdata = data.toInt()*150;
                                    lineEdit->setText(QString::number(intdata));
                                } else lineEdit->setText(data);

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

                                if (value.size() > 2) value = bin2dec(value);
                                bool valueFound = false;
                                for (int i = 0; i < comboBox->count(); ++i) {
                                    QString existingText = comboBox->itemText(i);
                                    QString textBeforeSpace = existingText.split(" ").first();
                                    if (textBeforeSpace == value) {
                                        valueFound = true;
                                        comboBox->setCurrentText(existingText);
                                        break;
                                    }
                                }
                                if (!valueFound) {
                                    comboBox->addItem(value);
                                    comboBox->setCurrentText(value);

                                }

                            }

                        } else continue;
                    }
                }
            }
        }
    }


}

void AD9122Widget::load_all() {
    load("output.json");
}

void AD9122Widget:: load_element() {
    load("save_element.json");
}

void AD9122Widget::load(const QString& filePath)
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения!");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    rapidjson::Document jsonDoc;
    jsonDoc.Parse(jsonData.constData());

    if (jsonDoc.HasParseError()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл");
        qDebug() << "JSON parse error at offset:" << jsonDoc.GetErrorOffset();
        return;
    }

    if (!jsonDoc.IsObject()) {
        qWarning() << "Корневой элемент не является объектом.";
        return;
    }

    if (!jsonDoc.HasMember("Registers") || !jsonDoc["Registers"].IsArray()) {
        qWarning() << "'Registers' не найден или не является массивом.";
        return;
    }

    const rapidjson::Value& jsonArray = jsonDoc["Registers"];

    QStandardItem* Item = nullptr;
    QString readItem = "";
    QString data = "";

    for (int i = 0; i < model->rowCount(); ++i) {
        QStandardItem* item = model->item(i);
        if (item && item->hasChildren()) {
            QStringList addresses;
            QStringList datalist;

            for (const auto& value : jsonArray.GetArray()) {
                if (value.HasMember("Addr") && value["Addr"].IsString()) {
                    addresses.append(QString::fromStdString(value["Addr"].GetString()));
                }

                if (value.HasMember("Data") && value["Data"].IsString()) {
                    datalist.append(QString::fromStdString(value["Data"].GetString()));
                }
            }

            for (int index = 0; index < qMin(addresses.size(), datalist.size()); ++index) {
                if ((item->text() == addresses[index] && LMKflag) || !LMKflag) updateChildWidgets(model, datalist[index], item, addresses[index]);
            }
        }
    }


}
