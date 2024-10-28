#include "HCM1035-widget.h"

#include <QStandardItemModel>
#include <QTreeView>
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


extern QStringList itemNames;
extern QStringList regNames;

QWidget* HCM1035Widget::createComboBoxWidgetLable(const QString &labelText, const QStringList &options) {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *label = new QLabel(labelText);
    layout->addWidget(label);

    QComboBox *comboBox = new QComboBox();
    QVariant propertyValue = comboBox->setProperty("ComboBoxName", labelText);
    comboBox->addItems(options);
    layout->addWidget(comboBox);

    widget->setLayout(layout);

    return widget;
}

QCheckBox* HCM1035Widget::createCheckBoxWidget(const QString &labelText, CheckBoxState state) {
    QCheckBox *checkBox = new QCheckBox(labelText);

    switch (state) {
        case Unchecked:
            checkBox->setChecked(false);
            checkBox->setTristate(false);
            break;
        case Checked:
            checkBox->setChecked(true);
            checkBox->setTristate(false);
            break;
        case Undefined:
            checkBox->setCheckState(Qt::PartiallyChecked);
            checkBox->setTristate(true);
            break;
    }

    return checkBox;
}

QWidget* HCM1035Widget::LineEdit(const QString& labelText, const QString& placeholderText){

    QLabel *label = new QLabel(labelText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(label);

    QLabel *text = new QLabel(placeholderText);
    hLayout->addWidget(text);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
}

QWidget* HCM1035Widget::createLineEditWithSaveButton(int rowIndex, double valueLimit, double minLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholderText);
    lineEdit->setProperty("lineEditName", placeholderText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *saveButton = new QPushButton("Сохранить");

    connect(saveButton, &QPushButton::clicked, [this, lineEdit, valueLimit, minLimit, errorMsg, defaultText]() {
        QString inputValue = lineEdit->text();
        bool ok;
        double doubleValue = inputValue.toDouble(&ok);

        if (ok && doubleValue >= 0.0 && doubleValue <= valueLimit && minLimit <= doubleValue) {
                if (doubleValue) {
                    QString processedValue = QString::number(doubleValue, 'f', 2);
                    lineEdit->setText(processedValue);
                    lineEdit->setStyleSheet("color: green;");
                }
        } else {
            QMessageBox::warning(this, "Ошибка", "Введенное значение должно быть десятичным в пределах " + QString::number(minLimit) + "-" + QString::number(valueLimit));
            lineEdit->setText(defaultText);
        }
    });

    hLayout->addWidget(lineEdit);
    hLayout->addWidget(saveButton);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
}

void HCM1035Widget::onParentItemClicked(const QModelIndex& index) {

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
    QStandardItem* item = model->itemFromIndex(index);
    if (item != nullptr) {
        disconnect(save_elem, &QPushButton::clicked, this, nullptr);
        connect(save_elem, &QPushButton::clicked, this, [this, item]() {
            saveItem(item);
        });
    }

}

void HCM1035Widget::hasChildren (QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Value &jsonItem, QStandardItemModel* model, QTreeView* treeView, bool HCMflag) {

    rapidjson::Value dataArray(rapidjson::kArrayType);

    for (int j = 0; j < selectedItem->rowCount(); j++) {
        QStandardItem* child = selectedItem->child(j);

        if (child) {
            rapidjson::Value combinedArray(rapidjson::kArrayType);

            QModelIndex index = model->index(j, 1, selectedItem->index());
            QWidget* widget = treeView->indexWidget(index);

            if (widget && index.isValid()) {

                QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
                if (!lineEdits.isEmpty()) {
                    for (QLineEdit* lineEdit : lineEdits) {
                        if (lineEdit) {
                            rapidjson::Value lineEditObj(rapidjson::kObjectType);
                            QVariant propertyValue = lineEdit->property("lineEditName");
                            if (propertyValue.isValid()) lineEditObj.AddMember("Text", rapidjson::Value(propertyValue.toString().toStdString().c_str(), allocator), allocator);
                            lineEditObj.AddMember("Value", rapidjson::Value(lineEdit->text().toStdString().c_str(), allocator), allocator);
                            combinedArray.PushBack(lineEditObj, allocator);
                        }
                    }
                }

                QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
                for (QCheckBox* checkBox : checkBoxes) {
                    if (checkBox) {
                        rapidjson::Value checkBoxObj(rapidjson::kObjectType);
                        checkBoxObj.AddMember("Text", rapidjson::Value(checkBox->text().toStdString().c_str(), allocator), allocator);
                        std::string checkBoxValue;
                        if (checkBox->checkState() == Qt::PartiallyChecked)
                            checkBoxValue = "None";
                        else if (checkBox->isChecked())
                            checkBoxValue = "True";
                        else checkBoxValue = "False";
                        checkBoxObj.AddMember("Value", rapidjson::Value(checkBoxValue.c_str(), allocator), allocator);
                        combinedArray.PushBack(checkBoxObj, allocator);
                    }
                }

                QList<QComboBox*> comboBoxes = widget->findChildren<QComboBox*>();
                if (!comboBoxes.isEmpty()) {
                    for (QComboBox* comboBox : comboBoxes) {
                        if (comboBox) {
                            QString comboBoxText = comboBox->currentText();
                            QStringList parts = comboBoxText.split(" ");
                            QString numericPart = parts.isEmpty() ? QString() : parts[0];

                            QWidget *parentWidget = comboBox->parentWidget();
                            QLabel *label = parentWidget ? parentWidget->findChild<QLabel*>() : nullptr;
                            QString labelText = label ? label->text() : QString();
                            QVariant propertyValue = comboBox->property("ComboBoxName");
                            if (labelText.isEmpty() && propertyValue.isValid()) labelText = propertyValue.toString();

                            rapidjson::Value comboBoxObj(rapidjson::kObjectType);
                            comboBoxObj.AddMember("Text", rapidjson::Value(labelText.toStdString().c_str(), allocator), allocator);
                            comboBoxObj.AddMember("Value", rapidjson::Value(numericPart.toStdString().c_str(), allocator), allocator);
                            combinedArray.PushBack(comboBoxObj, allocator);
                        }
                    }

                }
                for (rapidjson::Value& item : combinedArray.GetArray()) {
                    dataArray.PushBack(item, allocator);
                }

            }
        }
    }
    jsonItem.AddMember("Data", dataArray, allocator);


//    rapidjson::Value children(rapidjson::kArrayType);

//    for (int j = 0; j < selectedItem->rowCount(); j++) {
//        QStandardItem* child = selectedItem->child(j);

//        if (child) {

//            rapidjson::Value jsonChild(rapidjson::kObjectType);
//            QModelIndex index = model->index(j, 1, selectedItem->index());
//            QWidget* widget = treeView->indexWidget(index);

//            if (widget && index.isValid()) {

//                rapidjson::Value lineEditsArray(rapidjson::kArrayType);
//                QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
//                if (!lineEdits.isEmpty()) {
//                    for (QLineEdit* lineEdit : lineEdits) {
//                        if (lineEdit) {
//                            rapidjson::Value lineEditObj(rapidjson::kObjectType);
//                            QVariant propertyValue = lineEdit->property("lineEditName");
//                            if (propertyValue.isValid()) lineEditObj.AddMember("le_Text", rapidjson::Value(propertyValue.toString().toStdString().c_str(), allocator), allocator);
//                            lineEditObj.AddMember("le_Value", rapidjson::Value(lineEdit->text().toStdString().c_str(), allocator), allocator);
//                            lineEditsArray.PushBack(lineEditObj, allocator);
//                        }
//                    }

//                    if (lineEditsArray.Size() > 0) {
//                        jsonChild.AddMember("le", lineEditsArray, allocator);
//                    }
//                }

//                rapidjson::Value checkBoxesArray(rapidjson::kArrayType);
//                QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
//                for (QCheckBox* checkBox : checkBoxes) {
//                    if (checkBox) {
//                        rapidjson::Value checkBoxObj(rapidjson::kObjectType);
//                        checkBoxObj.AddMember("chb_Text", rapidjson::Value(checkBox->text().toStdString().c_str(), allocator), allocator);
//                        std::string checkBoxValue;
//                        if (checkBox->checkState() == Qt::PartiallyChecked)
//                            checkBoxValue = "Undefined";
//                        else if (checkBox->isChecked())
//                            checkBoxValue = "Checked";
//                        else checkBoxValue = "Unchecked";

//                        checkBoxObj.AddMember("chb_value", rapidjson::Value(checkBoxValue.c_str(), allocator), allocator);
//                        checkBoxesArray.PushBack(checkBoxObj, allocator);
//                    } else {
//                        qDebug() << "Found nullptr in checkBoxes.";
//                    }
//                }
//                if (checkBoxesArray.Size() > 0) jsonChild.AddMember("chb", checkBoxesArray, allocator);

//                rapidjson::Value comboBoxesArray(rapidjson::kArrayType);
//                QList<QComboBox*> comboBoxes = widget->findChildren<QComboBox*>();
//                if (!comboBoxes.isEmpty()) {
//                    for (QComboBox* comboBox : comboBoxes) {
//                        if (comboBox) {
//                            QString comboBoxText = comboBox->currentText();
//                            QStringList parts = comboBoxText.split(" ");
//                            QString numericPart = parts.isEmpty() ? QString() : parts[0];

//                            QWidget *parentWidget = comboBox->parentWidget();
//                            QLabel *label = parentWidget ? parentWidget->findChild<QLabel*>() : nullptr;
//                            QString labelText = label ? label->text() : QString();

//                            rapidjson::Value comboBoxObj(rapidjson::kObjectType);
//                            comboBoxObj.AddMember("cb_Text", rapidjson::Value(labelText.toStdString().c_str(), allocator), allocator);
//                            comboBoxObj.AddMember("cb_Value", rapidjson::Value(numericPart.toStdString().c_str(), allocator), allocator);
//                            comboBoxesArray.PushBack(comboBoxObj, allocator);
//                        }
//                    } if (comboBoxesArray.Size() > 0)  jsonChild.AddMember("cb", comboBoxesArray, allocator);
//                }
//                children.PushBack(jsonChild, allocator);
//            }
//        }
//    }
//    if (HCMflag) jsonItem.AddMember("subChildren", children, allocator);
//    else jsonItem.AddMember("children", children, allocator);


}

void HCM1035Widget::saveItem(QStandardItem *selectedItem) {

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

    rapidjson::Value items(rapidjson::kArrayType);
    rapidjson::Value jsonParent(rapidjson::kObjectType);

//    if (HCMflag) {
//        QString selparent = selectedItem->parent()->text();
//        jsonParent.AddMember(
//            rapidjson::Value(("column" + QString::number(0)).toStdString().c_str(), allocator),
//            rapidjson::Value(selparent.toStdString().c_str(), allocator),
//            allocator);
//    }

    rapidjson::Value children(rapidjson::kArrayType);

    rapidjson::Value jsonItem(rapidjson::kObjectType);
    QString itemData = selectedItem->text();

    jsonItem.AddMember(
        rapidjson::Value("Name", allocator),
        rapidjson::Value(itemData.toStdString().c_str(), allocator),
        allocator);

    if (selectedItem->hasChildren()) hasChildren(selectedItem, allocator, jsonItem, model, treeView, HCMflag);

    if (HCMflag) {
        children.PushBack(jsonItem, allocator);

        jsonParent.AddMember("children", children, allocator);
        items.PushBack(jsonParent, allocator);
    } else items.PushBack(jsonItem, allocator);

    document.AddMember("Registers", items, allocator);
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

void HCM1035Widget::on_save_button_clicked()
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
    QStandardItem* rootItem = model->invisibleRootItem();
    rapidjson::Value items(rapidjson::kArrayType);

    for (int i = 0; i < rootItem->rowCount(); ++i) {
        QStandardItem* item = rootItem->child(i);
        if (item->text() == "PLL" || item->text() == "VCO Subsystem") HCMflag = 1;
        if (!item) continue;
        rapidjson::Value jsonItem(rapidjson::kObjectType);

        for (int col = 0; col < model->columnCount(); ++col) {
            if (model->item(i, col)) {
                QString itemData = model->item(i, col)->text();
                jsonItem.AddMember(
                    rapidjson::Value("Name", allocator),
                    rapidjson::Value(itemData.toStdString().c_str(), allocator),
                    allocator);
            }
        }
        if (item->hasChildren())  {
            if (HCMflag) {
                rapidjson::Value children(rapidjson::kArrayType);
                for (int j = 0; j < item->rowCount(); j++) {
                    QStandardItem* child = item->child(j);

                    if (child) {
                        rapidjson::Value jsonChild(rapidjson::kObjectType);
                        QString childData = child->text();
                        jsonChild.AddMember(
                            rapidjson::Value("Name", allocator),
                            rapidjson::Value(childData.toStdString().c_str(), allocator),
                            allocator
                        );

                        if (child->hasChildren()) {
                            hasChildren(child, allocator, jsonChild, model, treeView, HCMflag);
                            children.PushBack(jsonChild, allocator);
                         }
                     }
                }
                jsonItem.AddMember("Data", children, allocator);
            } else hasChildren(item, allocator, jsonItem, model, treeView, HCMflag);
        }
    items.PushBack(jsonItem, allocator);
    }

    document.AddMember("Registers", items, allocator);
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



//    rapidjson::Document document;
//    document.SetObject();
//    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
//    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
//    QStandardItem* rootItem = model->invisibleRootItem();
//    rapidjson::Value items(rapidjson::kArrayType);

//    for (int i = 0; i < rootItem->rowCount(); ++i) {
//        QStandardItem* item = rootItem->child(i);
//        qDebug() << item->text();
//        if (item->text() == "PLL" || item->text() == "VCO Subsystem") HCMflag = 1;
//        if (!item) continue;
//        rapidjson::Value jsonItem(rapidjson::kObjectType);

//        for (int col = 0; col < model->columnCount(); ++col) {
//            if (model->item(i, col)) {
//                QString itemData = model->item(i, col)->text();
//                jsonItem.AddMember(
//                    rapidjson::Value(("column" + QString::number(col)).toStdString().c_str(), allocator),
//                    rapidjson::Value(itemData.toStdString().c_str(), allocator),
//                    allocator);
//            }
//        }
//        if (item->hasChildren())  {
//            if (HCMflag) {
//                rapidjson::Value children(rapidjson::kArrayType);
//                for (int j = 0; j < item->rowCount(); j++) {
//                    QStandardItem* child = item->child(j);

//                    if (child) {
//                        rapidjson::Value jsonChild(rapidjson::kObjectType);
//                        QString childData = child->text();
//                        jsonChild.AddMember(
//                            rapidjson::Value(("column" + QString::number(0)).toStdString().c_str(), allocator),
//                            rapidjson::Value(childData.toStdString().c_str(), allocator),
//                            allocator
//                        );

//                        if (child->hasChildren()) {
//                            hasChildren(child, allocator, jsonChild, model, treeView, HCMflag);
//                            children.PushBack(jsonChild, allocator);
//                         }
//                     }
//                }
//                jsonItem.AddMember("children", children, allocator);
//            } else hasChildren(item, allocator, jsonItem, model, treeView, HCMflag);
//        }
//    items.PushBack(jsonItem, allocator);
//    }

//    document.AddMember("Registers", items, allocator);
//    rapidjson::StringBuffer buffer;
//    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
//    document.Accept(writer);

//    QString filePath = "output.json";
//    std::ofstream file(filePath.toStdString());

//    if (file.is_open()) {
//        file << buffer.GetString();
//        file.close();
//        QMessageBox::information(this, "Успех", "Файл успешно сохранен: " + filePath);
//    } else {
//        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
//    }

}

void HCM1035Widget::updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& dataArray, QStandardItem* parentItem) {
    if (!dataArray.IsArray()) {
        qDebug() << "dataArray не является массивом";
        QMessageBox::warning(this, "Ошибка", "Неверная структура файла");
        return;
    }

    if (dataArray.Empty()) return;

    for (int j = 0; j < dataArray.Size(); j++) {

        for (int i = 0; i < dataArray.Size(); ++i) {
            const rapidjson::Value& subChild = dataArray[i];
            if (!subChild.IsObject()) {
                qDebug() << "subChild не является объектом";
                continue;
            }


            if (subChild.HasMember("Text") && subChild.HasMember("Value")) {
                QString text = QString::fromStdString(subChild["Text"].GetString());
                QString value = QString::fromStdString(subChild["Value"].GetString());

                QModelIndex index = model->index(j, 1, parentItem->index());
                QWidget* widget = treeView->indexWidget(index);

                QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
                if (!lineEdits.isEmpty()) {
                    for (QLineEdit* lineEdit : lineEdits) {
                        if (lineEdit && lineEdit->property("lineEditName") == text) {
                            lineEdit->setText(value);
                        } else continue;
                    }
                }

                QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
                for (QCheckBox* checkBox : checkBoxes) {
                    if (checkBox && checkBox->property("checkBoxName") == text) {
                        if (value == "True") {
                            qDebug() << "setChecked(true)" << value;
                            checkBox->setChecked(true);
                        } else if (value == "False") {
                            checkBox->setChecked(false);
                            qDebug() << "setChecked(false)" << value;
                        } else if (value == "None") {
                            checkBox->setCheckState(Qt::PartiallyChecked);
                            qDebug() << "setCheckState(Qt::PartiallyChecked)" << value;
                        }
                    } else continue;
                }


                QList<QComboBox*> comboBoxes = widget->findChildren<QComboBox*>();
                if (!comboBoxes.isEmpty()) {
                    for (QComboBox* comboBox : comboBoxes) {
                        if (comboBox && comboBox->property("ComboBoxName") == text) {
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
                            break;
                        } else continue;
                    }
                }
            }
        }
    }


//    if (dataArray.Size() != parentItem->rowCount()) {
//        QMessageBox::warning(this, "Ошибка", "Не удалось считать файл - таблицы не совпадают!");
//        return;
//    }

//    for (int j = 0; j < parentItem->rowCount(); j++) {
//        QStandardItem* child = parentItem->child(j);

//        if (child) {
//            rapidjson::Value combinedArray(rapidjson::kArrayType);

//            const rapidjson::Value& subChild = dataArray[j];
//            if (!subChild.IsObject()) {
//                qDebug() << "subChild не является объектом";
//                continue;
//            }

//            if (subChild.HasMember("Text") && subChild.HasMember("Value")) {
//                QString text = QString::fromStdString(subChild["Text"].GetString());
//                QString value = QString::fromStdString(subChild["Value"].GetString());

//                QModelIndex index = model->index(j, 1, parentItem->index());
//                QWidget* widget = treeView->indexWidget(index);

//                if (widget && index.isValid()) {

//                    QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
//                    if (!lineEdits.isEmpty()) {
//                        for (QLineEdit* lineEdit : lineEdits) {
//                            if (lineEdit && lineEdit->property("lineEditName") == text) {
//                                lineEdit->setText(value);
//                            } else {
//                                QMessageBox::warning(this, "Ошибка", "Неверная структура файла - невозможно заполнить элемент " + text);
//                                break;
//                            }
//                        }
//                    }

//                    QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
//                    for (QCheckBox* checkBox : checkBoxes) {
//                        if (checkBox) {
//                            if (value == "True") {
//                                checkBox->setChecked(true);
//                            } else if (value == "False") {
//                                checkBox->setChecked(false);
//                            } else if (value == "None") {
//                                checkBox->setCheckState(Qt::PartiallyChecked);
//                            }
//                            break;
//                        }
//                    }

//                    QList<QComboBox*> comboBoxes = widget->findChildren<QComboBox*>();
//                    if (!comboBoxes.isEmpty()) {
//                        for (QComboBox* comboBox : comboBoxes) {
//                            if (comboBox && comboBox->property("ComboBoxName") == text) {
//                                bool valueFound = false;
//                                for (int i = 0; i < comboBox->count(); ++i) {
//                                    QString existingText = comboBox->itemText(i);
//                                    QString textBeforeSpace = existingText.split(" ").first();
//                                    if (textBeforeSpace == value) {
//                                        valueFound = true;
//                                        comboBox->setCurrentText(existingText);
//                                        break;
//                                    }
//                                }
//                                if (!valueFound) {
//                                    comboBox->addItem(value);
//                                    comboBox->setCurrentText(value);
//                                }
//                                break;
//                            } else {
//                                QMessageBox::warning(this, "Ошибка", "Неверная структура файла - невозможно заполнить элемент " + text);
//                                break;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }





//    if (!subChildrenArray.IsArray()) {
//         qDebug() << "subchildrenArray не является массивом";
//        QMessageBox::warning(this, "Ошибка", " Неверная структура файла");
//        return;
//    }

//    for (rapidjson::SizeType i = 0; i < subChildrenArray.Size(); ++i) {
//        const rapidjson::Value& subChild = subChildrenArray[i];
//        if (!subChild.IsObject()) {
//            continue;
//        }

//        QModelIndex index = model->index(i, 1, parentItem->index());
//        QWidget* containerWidget = treeView->indexWidget(index);

//        if (!containerWidget) {
//            continue;
//        }

//        QList<QLineEdit*> lineEdits = containerWidget->findChildren<QLineEdit*>();
//        QList<QCheckBox*> checkBoxes = containerWidget->findChildren<QCheckBox*>();
//        QList<QComboBox*> comboBoxes = containerWidget->findChildren<QComboBox*>();

//        if (subChild.HasMember("le") && subChild["le"].IsArray()) {
//            const rapidjson::Value& lineEditsArray = subChild["le"];
//            for (size_t i = 0; i < lineEditsArray.Size(); ++i) {
//                const rapidjson::Value& lineEditObj = lineEditsArray[i];
//                if (lineEditObj.IsObject() && lineEditObj.HasMember("le_Text") && lineEditObj.HasMember("le_Value")) {
//                    QString lineEditText = QString::fromStdString(lineEditObj["le_Text"].GetString());
//                    QString lineEditValue = QString::fromStdString(lineEditObj["le_Value"].GetString());
//                    for (QLineEdit* lineEdit : lineEdits) {
//                        if (lineEdit && lineEdit->property("lineEditName") == lineEditText) {
//                            lineEdit->setText(lineEditValue);
//                            break;
//                        }
//                    }
//                }
//            }
//        }

//        if (subChild.HasMember("chb") && subChild["chb"].IsArray()) {
//            const rapidjson::Value& checkBoxesArray = subChild["chb"];
//            for (rapidjson::SizeType j = 0; j < checkBoxesArray.Size(); ++j) {
//                const rapidjson::Value& checkBoxObj = checkBoxesArray[j];
//                if (checkBoxObj.HasMember("chb_Text")) {
//                    QString checkBoxText = QString::fromStdString(checkBoxObj["chb_Text"].GetString());
//                    QString checkBoxValue = QString::fromStdString(checkBoxObj.HasMember("chb_value") ? checkBoxObj["chb_value"].GetString() : "Unchecked");

//                    bool checkBoxFound = false;

//                    for (QCheckBox* checkBox : checkBoxes) {
//                        if (checkBox->text() == checkBoxText) {
//                            checkBoxFound = true;
//                            if (checkBoxValue == "Checked") {
//                                checkBox->setChecked(true);
//                            } else if (checkBoxValue == "Unchecked") {
//                                checkBox->setChecked(false);
//                            } else if (checkBoxValue == "Undefined") {
//                                checkBox->setCheckState(Qt::PartiallyChecked);
//                            }
//                            break;
//                        }
//                    }

//                    if (!checkBoxFound) {
//                        qDebug() << "Checkbox with text" << checkBoxText << "not found.";
//                    }
//                } else {
//                    QMessageBox::warning(this, "Ошибка", "Неверные значения в файле");
//                }
//            }
//        }

//        if (subChild.HasMember("cb") && subChild["cb"].IsArray()) {

//            const rapidjson::Value& comboBoxesArray = subChild["cb"];
//            for (rapidjson::SizeType k = 0; k < comboBoxesArray.Size(); ++k) {
//                const rapidjson::Value& comboBoxObj = comboBoxesArray[k];
//                if (comboBoxObj.HasMember("cb_Text")) {
//                    QString labelText = QString::fromStdString(comboBoxObj["cb_Text"].GetString());
//                    QString comboBoxValue = QString::fromStdString(comboBoxObj["cb_Value"].GetString());

//                    for (QComboBox* comboBox : comboBoxes) {
//                        QWidget* parentWidget = comboBox->parentWidget();
//                        QLabel* associatedLabel = parentWidget ? parentWidget->findChild<QLabel*>() : nullptr;
//                        QString currentLabelText = associatedLabel ? associatedLabel->text() : QString();
//                        if (currentLabelText == labelText) {

//                            bool valueFound = false;
//                            for (int i = 0; i < comboBox->count(); ++i) {
//                                QString existingText = comboBox->itemText(i);
//                                QString textBeforeSpace = existingText.split(" ").first();
//                                if (textBeforeSpace == comboBoxValue) {
//                                    valueFound = true;
//                                    comboBox->setCurrentText(existingText);
//                                    break;
//                                }
//                            }
//                            if (!valueFound) {
//                                comboBox->addItem(comboBoxValue);
//                                comboBox->setCurrentText(comboBoxValue);
//                            }
//                            break;
//                        }
//                    }
//                }


//        }

//}

//}

}

void HCM1035Widget::load_all() {
    load("output.json");
}

void HCM1035Widget:: load_element() {
    load("save_element.json");
}

void HCM1035Widget::load(const QString& filePath)
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

    if (jsonArray.Size() != model->rowCount()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось считать файл - таблицы не совпадают!");
        return;
    }

    for (rapidjson::SizeType i = 0; i < jsonArray.Size(); ++i) {
        const rapidjson::Value& value = jsonArray[i];

        if (!value.IsObject()) {
            continue;
        }

        QString readItem = QString::fromStdString(value["Name"].GetString());
        QStandardItem* Item = nullptr;

        for (int j = 0; j < model->rowCount(); ++j) {
            if (model->item(j)->text() == readItem) {
                Item = model->item(j);
                break;
            }
        }

        if (!Item) {
            QMessageBox::warning(this, "Ошибка", "Не удалось считать файл - таблицы не совпадают!");
            break;
        }

        if (value.HasMember("Data") && value["Data"].IsArray()) {
            const rapidjson::Value& dataArray = value["Data"];
//            updateChildWidgets(model, dataArray, Item);

            if (HCMflag && (Item->text() == "PLL" || Item->text() == "VCO Subsystem")) {
                for (rapidjson::SizeType k = 0; k < dataArray.Size(); ++k) {
                    const rapidjson::Value& childValue = dataArray[k];
                    QStandardItem* Item_sec = nullptr;
                    Item_sec = Item->child(k);
//                    qDebug() << Item_sec->text();

                    if (childValue.IsObject() && childValue.HasMember("Data") && childValue["Data"].IsArray()) {
                        const rapidjson::Value& grandChildArray = childValue["Data"];
                        updateChildWidgets(model, grandChildArray, Item_sec);
                    }
                }
            } else if (!HCMflag) updateChildWidgets(model, dataArray, Item);
              else {
                QMessageBox::warning(this, "Ошибка", "Не удалось считать файл - таблицы не совпадают!");
                break;
            }
        }

    }




//    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());

//    QFile file(filePath);
//    if (!file.open(QIODevice::ReadOnly)) {
//        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения!");
//        return;
//    }

//    QByteArray jsonData = file.readAll();
//    file.close();

//    rapidjson::Document jsonDoc;
//    jsonDoc.Parse(jsonData.constData());

//    if (jsonDoc.HasParseError()) {
//        QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл");
//        qDebug() << "JSON parse error at offset:" << jsonDoc.GetErrorOffset();
//        return;
//    }

//    if (!jsonDoc.IsObject()) {
//        qWarning() << "Корневой элемент не является объектом.";
//        return;
//    }

//    if (!jsonDoc.HasMember("Registers") || !jsonDoc["Registers"].IsArray()) {
//        qWarning() << "'Registers' не найден или не является массивом.";
//        return;
//    }

//    const rapidjson::Value& jsonArray = jsonDoc["Registers"];

//    for (rapidjson::SizeType i = 0; i < jsonArray.Size(); ++i) {
//        const rapidjson::Value& value = jsonArray[i];

//        if (!value.IsObject()) {
//            continue;
//        }

//        QString parentIdentifier = QString::fromStdString(value["column0"].GetString());
//        QStandardItem* parentItem = nullptr;

//        for (int j = 0; j < model->rowCount(); ++j) {
//            if (model->item(j)->text() == parentIdentifier) {
//                parentItem = model->item(j);
//                break;
//            }
//        }

//        if (!parentItem) {
//            qWarning() << "Родительский элемент" << parentIdentifier << "не найден.";
//            QMessageBox::warning(this, "Ошибка", "Не удалось считать файл - таблицы не совпадают!");
//            break;
//        }

//        if (value.HasMember("children") && value["children"].IsArray()) {
//            const rapidjson::Value& childrenArray = value["children"];
//            updateChildWidgets(model, childrenArray, parentItem);

//            for (rapidjson::SizeType k = 0; k < childrenArray.Size(); ++k) {
//                const rapidjson::Value& jsonChild = childrenArray[k];
//                QString childIdentifier = QString::fromStdString(jsonChild["column0"].GetString());
//                bool foundMatchingChild = false;

//                QStandardItem *currentChildItem = nullptr;
//                for (int j = 0; j < parentItem->rowCount(); ++j) {
//                    if (parentItem->child(j)->text() == childIdentifier) {
//                        foundMatchingChild = true;
//                        currentChildItem = parentItem->child(j);
//                        break;
//                    }
//                }

//                if (!foundMatchingChild) {
//                    qWarning() << "Ошибка: Дочерний элемент с идентификатором" << childIdentifier << "не соответствует ни одному дочернему элементу родителя" << parentItem->text();
//                }

//                if (jsonChild.HasMember("subChildren") && jsonChild["subChildren"].IsArray()) {
//                    const rapidjson::Value& subChildrenArray = jsonChild["subChildren"];
//                    updateChildWidgets(model, subChildrenArray, currentChildItem);
//                }
//            }
//        }
//    }

}

void HCM1035Widget::setEditableFlags(QStandardItem *item, bool editable) {
    if (!item) return;

    if (editable) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } else {
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    }

    for (int row = 0; row < item->rowCount(); ++row) {
        QStandardItem *childItem = item->child(row);
        setEditableFlags(childItem, editable);
    }
}

void HCM1035Widget::blockEditing(QStandardItemModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *rootItem = model->item(row);
        setEditableFlags(rootItem, false);
    }
}

void HCM1035Widget::on_toggle_button_clicked()
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

QStringList itemNames = {"PLL", "VCO Subsystem"};

QStringList childName1 = {
    "00h ID Register", "00h Open Mode Read Address/RST Strobe Register", "01h RST Register", "02h REFDIV Register", "03h Frequency Register - Integer Part",
    "04h Frequency Register - Fractional Part", "05h VCO SPI Register", "06h SD CFG Register", "07h Lock Detect Register", "08h Analog EN Register",
    "09h Charge Pump Register", "0Ah VCO AutoCal Configuration Register", "0Bh PD Register", "0Ch Exact Frequency Mode Register", "0Fh GPO_LD/SDO Register",
    "10h VCO Tune Register", "11h SAR Register", "12h GPO2 Register", "13h BIST Register"
};

QStringList childName2 = {
    "00h Tuning", "01h Enables", "02h Biases", "03h Config", "04h Cal/Bias",
    "05h CF_Cal", "06h MSB Cal", "07h MSB Cal"
};










