#include "AD9122-widget.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>
#include <cmath>
#include <QLabel>
#include <QFile>
#include <fstream>


void AD9122Widget::onItemChanged(QStandardItem* changedItem) {

    if (!changedItem) return;
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView->model());
    if (!model) return;

    qDebug() << "Item changed:" << changedItem->text();
}

QWidget* AD9122Widget::LineOfPower(int rowIndex, int valueLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholderText);
    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *saveButton = new QPushButton("Сохранить");

    connect(saveButton, &QPushButton::clicked, [this, lineEdit, valueLimit, errorMsg, defaultText]() {
        QString inputValue = lineEdit->text();
        int in_val = inputValue.toInt();
        if (inputValue.toInt()) {
            if (!((in_val >= 0) && ((in_val & (in_val - 1)) == 0)) || (in_val > valueLimit)) {
                QMessageBox::warning(this, "Ошибка", errorMsg);
                lineEdit->setText(defaultText);
            } else {
                QString processedValue = QString::number(inputValue.toInt());
                lineEdit->setText(processedValue);
                lineEdit->setStyleSheet("color: green;");
            }
        } else {
            lineEdit->setText(defaultText);
        }
    });

    hLayout->addWidget(lineEdit);
    hLayout->addWidget(saveButton);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);
    return widget;
}

QWidget* AD9122Widget::LineEdit(const QString& labelText, const QString& placeholderText){

    QLabel *label = new QLabel(labelText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(label);

    QLabel *text = new QLabel(placeholderText);
    hLayout->addWidget(text);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
}

QWidget* AD9122Widget::createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText, int bitNumber) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholderText);
    lineEdit->setProperty("lineEditName", placeholderText);
    lineEdit->setProperty("bitNumber", bitNumber);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *saveButton = new QPushButton("Сохранить");

    connect(saveButton, &QPushButton::clicked, [this, lineEdit, valueLimit, modulo, errorMsg, defaultText]() {
        QString inputValue = lineEdit->text();
        bool ok;
        double doubleValue = inputValue.toDouble(&ok);

        if (ok && doubleValue >= 0.0 && doubleValue <= valueLimit) {
            if (modulo != 0) {
                if (fmod(doubleValue, modulo) == 0.0) {
                    QString processedValue = QString::number(doubleValue, 'f', 2);
                    lineEdit->setText(processedValue);
                    lineEdit->setStyleSheet("color: green;");
                } else {
                    QMessageBox::warning(this, "Ошибка", "Введенное значение должно быть в пределах 0-" + QString::number(valueLimit) + "." + " и делиться на " + QString::number(modulo));
                    lineEdit->setText(defaultText);
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Недопустимый модуль: деление на ноль.");
                lineEdit->setText(defaultText);
            }
        } else {
                QMessageBox::warning(this, "Ошибка", "Введенное значение должно быть в пределах 0-" + QString::number(valueLimit) + ".");
                lineEdit->setText(defaultText);
        }
    });

    hLayout->addWidget(lineEdit);
    hLayout->addWidget(saveButton);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
}

QWidget* AD9122Widget::createComboBoxWidgetLable(const QString &labelText, const QStringList &options, int bitNumber) {

    QWidget *widget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(widget);

        QLabel *label = new QLabel(labelText);
        layout->addWidget(label);

        QComboBox *comboBox = new QComboBox();
        /*QVariant propertyValue =*/ comboBox->setProperty("ComboBoxName", labelText);
        /*QVariant propertyValue2 =*/ comboBox->setProperty("bitNumber", bitNumber);
        comboBox->addItems(options);
        layout->addWidget(comboBox);

        widget->setLayout(layout);

        return widget;
}

QCheckBox* AD9122Widget::createCheckBoxWidget(const QString &labelText, CheckBoxState state, int bitNumber) {
    QCheckBox *checkBox = new QCheckBox(labelText);
    checkBox->setProperty("checkBoxName", labelText);
    checkBox->setProperty("bitNumber", bitNumber);

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

void AD9122Widget::setEditableFlags(QStandardItem *item, bool editable) {
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

void AD9122Widget::blockEditing(QStandardItemModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *rootItem = model->item(row);
        setEditableFlags(rootItem, false);
    }
}

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

void AD9122Widget::hasChildren (QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Value &jsonItem, QStandardItemModel* model, QTreeView* treeView, bool HCMflag) {

//    qDebug() << selectedItem->text();

    rapidjson::Value dataArray(rapidjson::kArrayType);

    for (int j = 0; j < selectedItem->rowCount(); j++) {
        QStandardItem* child = selectedItem->child(j);
//        rapidjson::Value jsonAddr(rapidjson::kObjectType);

//        if (!child->text().isEmpty()) {
//            jsonAddr.AddMember(
//                rapidjson::Value("Addr", allocator),
//                rapidjson::Value(child->text().toStdString().c_str(), allocator),
//                allocator);
//        } dataArray.PushBack(jsonAddr, allocator);

        if (child) {
            rapidjson::Value combinedArray(rapidjson::kArrayType);

            QModelIndex index = model->index(j, 1, selectedItem->index());
            QWidget* widget = treeView->indexWidget(index);

            if (widget && index.isValid() /*&& selectedItem->text() == "Interrupt Enable"*/) {

                QString Result;

                QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
//                qDebug() << lineEdits;
                if (!lineEdits.isEmpty()) {
                    for (QLineEdit* lineEdit : lineEdits) {
                        if (lineEdit) {
//                            qDebug() << lineEdit->text();

                            Result += lineEdit->text();
//                            rapidjson::Value lineEditObj(rapidjson::kObjectType);
//                            QVariant propertyValue = lineEdit->property("lineEditName");
//                            if (propertyValue.isValid()) lineEditObj.AddMember("Text", rapidjson::Value(propertyValue.toString().toStdString().c_str(), allocator), allocator);
//                            lineEditObj.AddMember("Value", rapidjson::Value(lineEdit->text().toStdString().c_str(), allocator), allocator);
//                            combinedArray.PushBack(lineEditObj, allocator);
                        }
                    }
                }

                QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
                for (QCheckBox* checkBox : checkBoxes) {
                    if (checkBox) {
//                        rapidjson::Value checkBoxObj(rapidjson::kObjectType);
//                        checkBoxObj.AddMember("Text", rapidjson::Value(checkBox->text().toStdString().c_str(), allocator), allocator);
                        QString checkBoxValue;
                        if (checkBox->checkState() == Qt::PartiallyChecked)
                            checkBoxValue = "?"/*"None"*/;
                        else if (checkBox->isChecked())
                            checkBoxValue = "1"/*"True"*/;
                        else checkBoxValue = "0"/*"False"*/;
//                        qDebug() << checkBoxValue;
                        Result += checkBoxValue;

//                        checkBoxObj.AddMember("Value", rapidjson::Value(checkBoxValue.c_str(), allocator), allocator);
//                        combinedArray.PushBack(checkBoxObj, allocator);
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

//                            qDebug() << numericPart;
                            Result += numericPart;

//                            rapidjson::Value comboBoxObj(rapidjson::kObjectType);
//                            comboBoxObj.AddMember("Text", rapidjson::Value(labelText.toStdString().c_str(), allocator), allocator);
//                            comboBoxObj.AddMember("Value", rapidjson::Value(numericPart.toStdString().c_str(), allocator), allocator);
//                            combinedArray.PushBack(comboBoxObj, allocator);
                        }
                    }

                }
                rapidjson::Value resObj(rapidjson::kObjectType);
                rapidjson::Value resultValue(rapidjson::kStringType);
                resultValue.SetString(Result.toStdString().c_str(), static_cast<rapidjson::SizeType>(Result.size()), allocator);
                jsonItem.AddMember("Data", resultValue, allocator);
//                combinedArray.PushBack(resObj, allocator);
//                qDebug() << Result;

//                for (rapidjson::Value& item : combinedArray.GetArray()) {
//                    dataArray.PushBack(item, allocator);
//                }

            }
        }
    }
//    jsonItem.AddMember("Data", dataArray, allocator);





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









//    if (selectedItem->parent() != nullptr) {
//        if (selectedItem->parent()->text() == "PLL" || selectedItem->parent()->text() == "VCO Subsystem") HCMflag = 1;
//        else {
//            QMessageBox::warning(this, "Ошибка", "Выберете регистр");
//            return;
//        }
//    } else if (selectedItem->text() == "PLL" || selectedItem->text() == "VCO Subsystem") {
//        QMessageBox::warning(this, "Ошибка", "Выберете регистр");
//        return;
//    } else selectedItem = selectedItem;


//    rapidjson::Document document;
//    document.SetObject();
//    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

//    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());

//    rapidjson::Value items(rapidjson::kArrayType);
//    rapidjson::Value jsonParent(rapidjson::kObjectType);

//    if (HCMflag) {
//        QString selparent = selectedItem->parent()->text();
//        jsonParent.AddMember(
//            rapidjson::Value(("column" + QString::number(0)).toStdString().c_str(), allocator),
//            rapidjson::Value(selparent.toStdString().c_str(), allocator),
//            allocator);
//    }

//    rapidjson::Value children(rapidjson::kArrayType);

//    rapidjson::Value jsonItem(rapidjson::kObjectType);
//    QString itemData = selectedItem->text();

//    jsonItem.AddMember(
//        rapidjson::Value(("column" + QString::number(0)).toStdString().c_str(), allocator),
//        rapidjson::Value(itemData.toStdString().c_str(), allocator),
//        allocator);

//    if (selectedItem->hasChildren()) hasChildren(selectedItem, allocator, jsonItem, model, treeView, HCMflag);

//    if (HCMflag) {
//        children.PushBack(jsonItem, allocator);

//        jsonParent.AddMember("children", children, allocator);
//        items.PushBack(jsonParent, allocator);
//    } else items.PushBack(jsonItem, allocator);

//    document.AddMember("Registers", items, allocator);
//    rapidjson::StringBuffer buffer;
//    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
//    document.Accept(writer);

//    QString filePath = "save_element.json";
//    std::ofstream file(filePath.toStdString());

//    if (file.is_open()) {
//        file << buffer.GetString();
//        file.close();
//        QMessageBox::information(this, "Успех", "Файл успешно сохранен: " + filePath);
//    } else {
//        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи!");
//    }


}

void AD9122Widget::on_save_button_clicked()
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
        rapidjson::Value jsonAddr(rapidjson::kObjectType);

//        for (int col = 0; col < model->columnCount(); ++col) {
//            if (model->item(i, col)) {
//                QString itemData = model->item(i, col)->text();
//                jsonItem.AddMember(
//                    rapidjson::Value("Name", allocator),
//                    rapidjson::Value(itemData.toStdString().c_str(), allocator),
//                    allocator);
//            }
//        }

        for (int j = 0; j < model->item(i, 0)->rowCount(); j++) {
            QStandardItem* child = model->item(i, 0)->child(j);

            if (!child->text().isEmpty()) {
                jsonItem.AddMember(
                    rapidjson::Value("Addr", allocator),
                    rapidjson::Value(child->text().toStdString().c_str(), allocator),
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

void AD9122Widget::updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& dataArray, QStandardItem* parentItem) {

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

    if (jsonArray.Size() != model->rowCount()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось считать файл - таблицы не совпадают!");
        return;
    }

    for (rapidjson::SizeType i = 0; i < jsonArray.Size(); ++i) {
        const rapidjson::Value& value = jsonArray[i];

        if (!value.IsObject()) {
            continue;
        }

        QString raedItem = QString::fromStdString(value["Name"].GetString());
        QStandardItem* Item = nullptr;

        for (int j = 0; j < model->rowCount(); ++j) {
            if (model->item(j)->text() == raedItem) {
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
            updateChildWidgets(model, dataArray, Item);
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

QStringList itemNames = {
    "Comm", "Power Control", "Data Format", "Interrupt Enable", "Interrupt Enable",
    "Event Flag", "Clock Receiver Control", "PLL Control", "PLL Status",
    "Sync Control", "Sync Status", "Data Receiver Status", "DCI Delay", "FIFO Control",
    "FIFO Status", "Datapath Control", "HB1 Control", "HB2 Control", "HB3 Control",
    "Chip ID", "FTW LSB", "FTW", "FTW", "FTW MSB",
    "NCO Phase Offset LSB", "NCO Phase Offset MSB", "NCO FTW Update", "I Phase Adj LSB", "I Phase Adj MSB",
    "Q Phase Adj LSB", "Q Phase Adj MSB", "I DAC Offset LSB", "I DAC Offset MSB", "Q DAC Offset LSB", "Q DAC Offset MSB", "I DAC FS Adjust",
    "I DAC Control", "I Aux DAC Data", "I Aux DAC Control", "Q DAC FS Adjust", "Q DAC Control", "Q Aux DAC Data", "Q Aux DAC Control",
    "Die Temp Range Control", "Die Temp LSB", "Die Temp MSB", "SED Control",
    "Compare I0 LSBs", "Compare I0 MSBs", "Compare Q0 LSBs", "Compare Q0 MSBs",
    "Compare I1 LSBs", "Compare I1 MSBs", "Compare Q1 LSBs", "Compare Q1 MSBs",
    "SED I LSBs", "SED I MSBs", "SED Q LSBs", "SED Q MSBs",
    "Revision"
};

QStringList regNames = {
    "0x00", "0x01", "0x03", "0x04", "0x05",
    "0x06", "0x07", "0x08", "0x0A", "0x0C",
    "0x0D", "0x0E", "0x0F", "0x10", "0x11",
    "0x12", "0x13", "0x15", "0x16", "0x17",
    "0x18", "0x19", "0x1B", "0x1C", "0x1D",
    "0x1E", "0x1F", "0x30", "0x31", "0x32",
    "0x33", "0x34", "0x35", "0x36", "0x38",
    "0x39", "0x3A", "0x3B", "0x3C", "0x3D",
    "0x3E", "0x3F", "0x40", "0x41", "0x42",
    "0x43", "0x44", "0x45", "0x46", "0x47",
    "0x48", "0x49", "0x4A", "0x67", "0x68",
    "0x69", "0x6A", "0x6B", "0x6C", "0x6D",
    "0x6E", "0x6F", "0x70", "0x71", "0x72",
    "0x73", "0x7F"
};
