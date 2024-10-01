#include "HCM1035-widget.h"
//#include "./ui_HCM1035Widget.h"

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

extern QStringList itemNames;
extern QStringList regNames;

QWidget* HCM1035Widget::createComboBoxWidgetLable(const QString &labelText, const QStringList &options) {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *label = new QLabel(labelText);
    layout->addWidget(label);

    QComboBox *comboBox = new QComboBox();
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
        if (!item) continue;

        rapidjson::Value jsonItem(rapidjson::kObjectType);

        for (int col = 0; col < rootItem->columnCount(); ++col) {
            if (model->item(i, col)) {
                QString itemData = model->item(i, col)->text();

                jsonItem.AddMember(
                    rapidjson::Value(("column" + QString::number(col)).toStdString().c_str(), allocator),
                    rapidjson::Value(itemData.toStdString().c_str(), allocator),
                    allocator);
            }
        }

        if (item->hasChildren()) {

        rapidjson::Value children(rapidjson::kArrayType);
        for (int j = 0; j < item->rowCount(); j++) {
            QStandardItem* child = item->child(j);

            if (child) {
                rapidjson::Value jsonChild(rapidjson::kObjectType);
                QString childData = child->text();
                jsonChild.AddMember(
                    rapidjson::Value(("column" + QString::number(0)).toStdString().c_str(), allocator),
                    rapidjson::Value(childData.toStdString().c_str(), allocator),
                    allocator
                );

                if (child->hasChildren()) {

                    rapidjson::Value subChildren(rapidjson::kArrayType);
                    for (int k = 0; k < child->rowCount(); k++) {
                        QStandardItem* subChild = child->child(k);

                        if (subChild) {
                            rapidjson::Value jsonSubChild(rapidjson::kObjectType);
                            QModelIndex index = model->index(k, 1, child->index());
                            QWidget* widget = treeView->indexWidget(index);

                            //код рабочий - сохраняет все элементы, но не по прорядку, сохраняет в порядке проверки, но нет проблем с загрузкой

                            if (widget && index.isValid()) {

                                rapidjson::Value lineEditsArray(rapidjson::kArrayType);
                                QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
                                if (!lineEdits.isEmpty()) {
                                    for (QLineEdit* lineEdit : lineEdits) {
                                        if (lineEdit) {
                                            rapidjson::Value lineEditObj(rapidjson::kObjectType);
                                            QVariant propertyValue = lineEdit->property("lineEditName");
                                            if (propertyValue.isValid()) lineEditObj.AddMember("lineEditText", rapidjson::Value(propertyValue.toString().toStdString().c_str(), allocator), allocator);
                                            lineEditObj.AddMember("lineEditValue", rapidjson::Value(lineEdit->text().toStdString().c_str(), allocator), allocator);
                                            lineEditsArray.PushBack(lineEditObj, allocator);
                                        }
                                    }

                                    if (lineEditsArray.Size() > 0) {
                                        jsonSubChild.AddMember("lineEdit", lineEditsArray, allocator);
                                    }
                                }
                            }

                            rapidjson::Value checkBoxesArray(rapidjson::kArrayType);
                            QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
                            for (QCheckBox* checkBox : checkBoxes) {
                                if (checkBox) {
                                    rapidjson::Value checkBoxObj(rapidjson::kObjectType);
                                    checkBoxObj.AddMember("checkBoxText", rapidjson::Value(checkBox->text().toStdString().c_str(), allocator), allocator);

                                    std::string checkBoxValue;
                                    if (checkBox->checkState() == Qt::PartiallyChecked)
                                        checkBoxValue = "Undefined";
                                    else if (checkBox->isChecked())
                                        checkBoxValue = "Checked";
                                    else
                                        checkBoxValue = "Unchecked";

                                    checkBoxObj.AddMember("value", rapidjson::Value(checkBoxValue.c_str(), allocator), allocator);
                                    checkBoxesArray.PushBack(checkBoxObj, allocator);
                                } else {
                                    qDebug() << "Found nullptr in checkBoxes.";
                                }
                            }
                            if (checkBoxesArray.Size() > 0) jsonSubChild.AddMember("checkBoxes", checkBoxesArray, allocator);

                            rapidjson::Value comboBoxesArray(rapidjson::kArrayType);
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

                                        rapidjson::Value comboBoxObj(rapidjson::kObjectType);
                                        comboBoxObj.AddMember("comboBoxText", rapidjson::Value(labelText.toStdString().c_str(), allocator), allocator);
                                        comboBoxObj.AddMember("comboBoxValue", rapidjson::Value(numericPart.toStdString().c_str(), allocator), allocator);
                                        comboBoxesArray.PushBack(comboBoxObj, allocator);
                                    }
                                } if (comboBoxesArray.Size() > 0)  jsonSubChild.AddMember("comboBox", comboBoxesArray, allocator);
                            }





                            // рабочий код - сохраняет в json файл все правильно, все объекты находятся внутри массива widgets, но присутствуют проблемы с загрузкой из за этого

//                            if (widget && index.isValid()) {
//                                rapidjson::Value widgetsArray(rapidjson::kArrayType);

//                                QList<QWidget*> allWidgets = widget->findChildren<QWidget*>();
//                                for (QWidget* w : allWidgets) {

//                                    if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(w)) {
//                                        rapidjson::Value lineEditObj(rapidjson::kObjectType);
//                                        lineEditObj.AddMember("lineEditValue",
//                                            rapidjson::Value(lineEdit->text().toStdString().c_str(), allocator), allocator);
//                                        widgetsArray.PushBack(lineEditObj, allocator);
//                                    }

//                                    else if (QCheckBox* checkBox = qobject_cast<QCheckBox*>(w)) {
//                                        rapidjson::Value checkBoxObj(rapidjson::kObjectType);
//                                        checkBoxObj.AddMember("checkBoxText", rapidjson::Value(checkBox->text().toStdString().c_str(), allocator), allocator);
//                                        std::string checkBoxValue;
//                                        if (checkBox->checkState() == Qt::PartiallyChecked)
//                                            checkBoxValue = "Undefined";
//                                        else if (checkBox->isChecked())
//                                            checkBoxValue = "Checked";
//                                        else checkBoxValue = "Unchecked";

//                                        checkBoxObj.AddMember("value", rapidjson::Value(checkBoxValue.c_str(), allocator), allocator);
//                                        widgetsArray.PushBack(checkBoxObj, allocator);
//                                    }

//                                    else if (QComboBox* comboBox = qobject_cast<QComboBox*>(w)) {
//                                        QString comboBoxText = comboBox->currentText();
//                                        QStringList parts = comboBoxText.split(" ");
//                                        QString numericPart = parts.isEmpty() ? QString() : parts[0];
//                                        QWidget* parentWidget = comboBox->parentWidget();
//                                        QLabel* label = parentWidget ? parentWidget->findChild<QLabel*>() : nullptr;
//                                        QString labelText = label ? label->text() : QString();

//                                        rapidjson::Value comboBoxObj(rapidjson::kObjectType);
//                                        comboBoxObj.AddMember("labelText",
//                                            rapidjson::Value(labelText.toStdString().c_str(), allocator), allocator);
//                                        comboBoxObj.AddMember("comboBoxValue",
//                                            rapidjson::Value(numericPart.toStdString().c_str(), allocator), allocator);
//                                        widgetsArray.PushBack(comboBoxObj, allocator);
//                                    }
//                                }

//                                if (widgetsArray.Size() > 0) {
//                                    jsonSubChild.AddMember("widgets", widgetsArray, allocator);
//                                }
//                            }
                            subChildren.PushBack(jsonSubChild, allocator);
                        }
                    }
                    jsonChild.AddMember("subChildren", subChildren, allocator);
                }
             children.PushBack(jsonChild, allocator);
            }
        }
        jsonItem.AddMember("children", children, allocator);
    }
    items.PushBack(jsonItem, allocator);
    }

    document.AddMember("items", items, allocator);
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

void HCM1035Widget::updateChildWidgets(QStandardItemModel* model, const rapidjson::Value&  subChildrenArray, QStandardItem* parentItem) {
    if (!subChildrenArray.IsArray()) {
         qDebug() << "subchildrenArray не является массивом";
        QMessageBox::warning(this, "Ошибка", " Неверная структура файла");
        return;
    }

    for (rapidjson::SizeType i = 0; i < subChildrenArray.Size(); ++i) {
        const rapidjson::Value& subChild = subChildrenArray[i];

        if (!subChild.IsObject()) {
            continue;
        }

        QModelIndex index = model->index(i, 1, parentItem->index());
        QWidget* containerWidget = treeView->indexWidget(index);

        if (!containerWidget) {
            continue;
        }

        QList<QLineEdit*> lineEdits = containerWidget->findChildren<QLineEdit*>();
        QList<QCheckBox*> checkBoxes = containerWidget->findChildren<QCheckBox*>();

        if (subChild.HasMember("lineEdit") && subChild["lineEdit"].IsArray()) {
            const rapidjson::Value& lineEditsArray = subChild["lineEdit"];
            for (size_t i = 0; i < lineEditsArray.Size(); ++i) {
                const rapidjson::Value& lineEditObj = lineEditsArray[i];
                if (lineEditObj.IsObject() && lineEditObj.HasMember("lineEditText") && lineEditObj.HasMember("lineEditValue")) {
                    QString lineEditText = QString::fromStdString(lineEditObj["lineEditText"].GetString());
                    QString lineEditValue = QString::fromStdString(lineEditObj["lineEditValue"].GetString());
                    for (QLineEdit* lineEdit : lineEdits) {
                        if (lineEdit && lineEdit->property("lineEditName") == lineEditText) {
                            lineEdit->setText(lineEditValue);
                            qDebug() << "Set line edit text to:" << lineEditValue;
                            break;
                        }
                    }
                }
            }
        }

        if (subChild.HasMember("checkBoxes") && subChild["checkBoxes"].IsArray()) {
            const rapidjson::Value& checkBoxesArray = subChild["checkBoxes"];
            for (rapidjson::SizeType j = 0; j < checkBoxesArray.Size(); ++j) {
                const rapidjson::Value& checkBoxObj = checkBoxesArray[j];
                if (checkBoxObj.HasMember("checkBoxText")) {
                    QString checkBoxText = QString::fromStdString(checkBoxObj["checkBoxText"].GetString());
                    QString checkBoxValue = QString::fromStdString(checkBoxObj.HasMember("value") ? checkBoxObj["value"].GetString() : "Unchecked");

                    bool checkBoxFound = false;

                    for (QCheckBox* checkBox : checkBoxes) {
                        if (checkBox->text() == checkBoxText) {
                            checkBoxFound = true;
                            if (checkBoxValue == "Checked") {
                                checkBox->setChecked(true);
                            } else if (checkBoxValue == "Unchecked") {
                                checkBox->setChecked(false);
                            } else if (checkBoxValue == "Undefined") {
                                checkBox->setCheckState(Qt::PartiallyChecked);
                            }
                            qDebug() << "Set checkbox" << checkBoxText << "to" << checkBoxValue;
                            break;
                        }
                    }

                    if (!checkBoxFound) {
                        qDebug() << "Checkbox with text" << checkBoxText << "not found.";
                    }
                } else {
                    QMessageBox::warning(this, "Ошибка", "Неверные значения в файле");
                }
            }
        }






        //работает (не совсем) при сохранении с массивом Виджеты

//        if (subChild.HasMember("widgets") && subChild["widgets"].IsArray()) {
//            const rapidjson::Value& widgetsArray = subChild["widgets"];

//            for (rapidjson::SizeType j = 0; j < widgetsArray.Size(); ++j) {
//                const rapidjson::Value& widget = widgetsArray[j];

//                qDebug() << "in for of widget array";

//                QModelIndex index = model->index(j, 1, parentItem->index());
//                QWidget* containerWidget = treeView->indexWidget(index);
//                if (!containerWidget) {
//                    continue;
//                }

//                if (subChild.HasMember("widgets") && subChild["widgets"].IsArray()) {
//                    const rapidjson::Value& widgetsArray = subChild["widgets"];

//                    QList<QLineEdit*> lineEdits = containerWidget->findChildren<QLineEdit*>();
//                    QList<QCheckBox*> checkBoxes = containerWidget->findChildren<QCheckBox*>();

//                    for (rapidjson::SizeType j = 0; j < widgetsArray.Size(); ++j) {
//                        const rapidjson::Value& widget = widgetsArray[j];

//                        if (widget.HasMember("lineEditValue")) {
//                            QString lineEditValue = QString::fromStdString(widget["lineEditValue"].GetString());

//                            if (j < lineEdits.size()) {
//                                lineEdits[j]->setText(lineEditValue);
//                                qDebug() << "Set line edit text to:" << lineEditValue;
//                            } else {
//                                qDebug() << "No line edit found for index:" << j;
//                            }
//                        }

//                        if (widget.HasMember("checkBoxText")) {
//                            QString checkBoxText = QString::fromStdString(widget["checkBoxText"].GetString());
//                            QString checkBoxValue = QString::fromStdString(widget.HasMember("value") ? widget["value"].GetString() : "Unchecked");

//                            for (QCheckBox* checkBox : checkBoxes) {
//                                if (checkBox->text() == checkBoxText) {
//                                    if (checkBoxValue == "Checked") {
//                                        checkBox->setChecked(true);
//                                    } else if (checkBoxValue == "Unchecked") {
//                                        checkBox->setChecked(false);
//                                    } else if (checkBoxValue == "Undefined") {
//                                        checkBox->setCheckState(Qt::PartiallyChecked);
//                                    }
//                                    qDebug() << "Set checkbox" << checkBoxText << "to" << checkBoxValue;
//                                    break;
//                                } else {
//                                    QMessageBox::warning(this, "Ошибка", " Неверные значения в файле");
//                                    break;
//                                }
//                            }
//                        }
//                    }
//                }






                    // часть где идет проверка для лайнэдита и чекбокса - экспериментальный код

//                    for (rapidjson::SizeType j = 0; j < widgetsArray.Size(); ++j) {
//                        const rapidjson::Value& widget = widgetsArray[j];
//                        qDebug() << "in for of widget array index:" << j;

//                        QModelIndex index = model->index(j, 1, parentItem->index());
//                        QWidget* containerWidget = treeView->indexWidget(index);
//                        if (!containerWidget) {
//                            qDebug() << "containerWidget is null for index:" << index;
//                            continue;
//                        }

//                        if (widget.HasMember("lineEditValue")) {
//                            qDebug() << "found lineedit at index:" << j;
//                            QString lineEditValue = QString::fromStdString(widget["lineEditValue"].GetString());
//                            QList<QLineEdit*> lineEdits = containerWidget->findChildren<QLineEdit*>();
//                            qDebug() << "Found" << lineEdits.size() << "line edits";

//                            for (QLineEdit* lineEdit : lineEdits) {
//                                lineEdit->setText(lineEditValue);
//                                qDebug() << "Set line edit text to:" << lineEditValue;
//                                break;
//                            }
//                        }
//                        qDebug() << "out of lineedit";

//                        if (widget.HasMember("checkBoxText")) {
//                            qDebug() << "found checkbox at index:" << j;
//                            QString checkBoxText = QString::fromStdString(widget["checkBoxText"].GetString());
//                            QString checkBoxValue = QString::fromStdString(widget.HasMember("value") ? widget["value"].GetString() : "Unchecked");
//                            QList<QCheckBox*> checkBoxes = containerWidget->findChildren<QCheckBox*>();
//                            qDebug() << "Found" << checkBoxes.size() << "check boxes";

//                            for (QCheckBox* checkBox : checkBoxes) {
//                                if (checkBox->text() == checkBoxText) {
//                                    if (checkBoxValue == "Checked") {
//                                        checkBox->setChecked(true);
//                                    } else if (checkBoxValue == "Unchecked") {
//                                        checkBox->setChecked(false);
//                                    } else if (checkBoxValue == "Undefined") {
//                                        checkBox->setCheckState(Qt::PartiallyChecked);
//                                    }
//                                    qDebug() << "Set checkbox" << checkBoxText << "to" << checkBoxValue;
//                                }
//                            }
//                        }
//                        qDebug() << "out of checkbox";
//                    }
//                }









                    // часть где идет проверка для всех элементов - основной код (не работает для всех элементов, но логика рабочая)


//                if (widget.HasMember("lineEditValue")) { qDebug() << "found lineedit";

//                    QString lineEditValue = QString::fromStdString(widget["lineEditValue"].GetString());
//                    QList<QLineEdit*> lineEdits = containerWidget->findChildren<QLineEdit*>();
//                    for (QLineEdit* lineEdit : lineEdits) {
//                        lineEdit->setText(lineEditValue);
//                        break;
//                    }
//                } qDebug() << "out of lineedit";

//                if (widget.HasMember("checkBoxText")) {  qDebug() << "found checkbox";

//                    QString checkBoxText = QString::fromStdString(widget["checkBoxText"].GetString());
//                    QString checkBoxValue = QString::fromStdString(widget.HasMember("value") ? widget["value"].GetString() : "Unchecked");

//                    QList<QCheckBox*> checkBoxes = containerWidget->findChildren<QCheckBox*>();
//                    for (QCheckBox* checkBox : checkBoxes) {
//                        if (checkBox->text() == checkBoxText) {
//                            if (checkBoxValue == "Checked") {
//                                checkBox->setChecked(true);
//                            } else if (checkBoxValue == "Unchecked") {
//                                checkBox->setChecked(false);
//                            } else if (checkBoxValue == "Undefined") {
//                                checkBox->setCheckState(Qt::PartiallyChecked);
//                            }
//                        }
//                    } break;
//                } qDebug() << "out of checkbox";


//                if (widget.HasMember("labelText") && widget.HasMember("comboBoxValue")) {  qDebug() << "found combobox";

//                    QString labelText = QString::fromStdString(widget["labelText"].GetString());
//                    QString comboBoxValue = QString::fromStdString(widget["comboBoxValue"].GetString());

//                    QList<QComboBox*> comboBoxes = containerWidget->findChildren<QComboBox*>();
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
//                }  qDebug() << "out of combobox";
//            }



//        }
    }





}

void HCM1035Widget::on_load_button_clicked()
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
    QString filePath = "output.json";

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
        qDebug() << "Error description:" << rapidjson::GetParseError_En(jsonDoc.GetParseError());
        return;
    }

    if (!jsonDoc.IsObject()) {
         qDebug() << "Корневой элемент не является объектом.";
        QMessageBox::warning(this, "Ошибка", " Неверная структура файла");
        return;
    }

    if (!jsonDoc.HasMember("items") || !jsonDoc["items"].IsArray()) {
        QMessageBox::warning(this, "Ошибка", "Неверная структура файла");
         qDebug() << "'items' не найден или не является массивом.";
        return;
    }

    const rapidjson::Value& itemsArray = jsonDoc["items"];

    for (rapidjson::SizeType i = 0; i < itemsArray.Size(); ++i) {
        const rapidjson::Value& item = itemsArray[i];

        if (!item.IsObject()) {
            continue;
        }

        QString parentIdentifier = QString::fromStdString(item["column0"].GetString());
        QStandardItem* parentItem = nullptr;

        for (int j = 0; j < model->rowCount(); j++) {
            if (model->item(i)->text() == parentIdentifier) {
                parentItem = model->item(i);
                break;
            } else { QMessageBox::warning(this, "Ошибка", "Неверная структура файла - таблицы не совпадают!"); qDebug() << "parentItem" <<  parentIdentifier;}
        }

        if (!parentItem) {
            qDebug() << "Родительский элемент" << parentIdentifier << "не найден.";
            QMessageBox::warning(this, "Ошибка", "Неверная структура файла - таблицы не совпадают!");
            break;
        }

        if (item.HasMember("children") && item["children"].IsArray()) {
            const rapidjson::Value& childrenArray = item["children"];

            for (rapidjson::SizeType k = 0; k < childrenArray.Size(); k++) {
                const rapidjson::Value& jsonChild = childrenArray[k];
                QString childIdentifier = QString::fromStdString(jsonChild["column0"].GetString());
                bool foundMatchingChild = false;

                QStandardItem *currentChildItem = nullptr;
                for (int j = 0; j < parentItem->rowCount(); j++) {
                    if (parentItem->child(j)->text() == childIdentifier) {
                        foundMatchingChild = true;
                        currentChildItem = parentItem->child(j);
                        break;
                    }
                }

                if (!foundMatchingChild) {
                    QMessageBox::warning(this, "Ошибка", "Неверная структура файла - таблицы не совпадают!");
                    qDebug() << "foundMatchingChild";
                    break;
                }

                if (jsonChild.HasMember("subChildren") && jsonChild["subChildren"].IsArray()) {
                    const rapidjson::Value& subChildrenArray = jsonChild["subChildren"];
                    updateChildWidgets(model, subChildrenArray, currentChildItem);
                } else QMessageBox::warning(this, "Ошибка", "Неверная структура файла - not children");
            }
        } else QMessageBox::warning(this, "Ошибка", "Неверная структура файла - not subChildren");
    }





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










