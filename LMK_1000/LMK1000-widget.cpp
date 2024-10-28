#include "LMK1000-widget.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>
#include <fstream>
#include <QFile>
#include <cmath>


LMK1000Widget::LMK1000Widget(QWidget *parent)
    : QWidget{parent}, treeView(new QTreeView(this)), model(new QStandardItemModel(this)), treeExpanded(false)
{
    viewTree();
    treeView -> setColumnWidth(0, 200);

}

void LMK1000Widget::setEditableFlags(QStandardItem *item, bool editable) {
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

void LMK1000Widget::blockEditing(QStandardItemModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *rootItem = model->item(row);
        setEditableFlags(rootItem, false);
    }
}

QWidget* LMK1000Widget::createLineEditWithSaveButton(int valueLimit, int modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText) {
    QLineEdit *lineEdit = new QLineEdit();

    lineEdit->setPlaceholderText(placeholderText);
    lineEdit->setProperty("lineEditName", placeholderText);

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

void LMK1000Widget::setupWidgets(QStandardItem *itm, int rowIndex, QModelIndex lineEditIndex) {

    if (rowIndex == 2) {
        QWidget *widget = createLineEditWithSaveButton(510, 2,
            "Clock Output Dividers (0-510)",
            "значение делителя тактового выхода должно быть в диапазоне 0-510 и быть четным",
            "2");
        treeView->setIndexWidget(lineEditIndex, widget);

        if (!widget) {
               qDebug() << "Widget is nullptr!";
               return;
           }

        if (!lineEditIndex.isValid()) {
            qDebug() << "Invalid index!";
        } else if (!widget) {
            qDebug() << "Widget is nullptr!";
        } else {
            treeView->setIndexWidget(lineEditIndex, widget);
        }

    } else if (rowIndex == 3) {
        QWidget *widget = createLineEditWithSaveButton(2250, 150,
            "Clock Output Delays (0-2250)",
            "значение задержки тактового выхода должно быть в диапазоне 0-2250 и быть кратным 150",
            "0");
        treeView->setIndexWidget(lineEditIndex, widget);

        if (!widget) {
               qDebug() << "Widget is nullptr!";
               return;
           }
        if (!lineEditIndex.isValid()) {
            qDebug() << "Invalid index!";
        } else if (!widget) {
            qDebug() << "Widget is nullptr!";
        } else {
            treeView->setIndexWidget(lineEditIndex, widget);
        }
    } else {
        QWidget *container = new QWidget();
        QComboBox *comboBox = new QComboBox(container);

        comboBox->clear();
        switch (rowIndex) {
            case 0: {
                comboBox->addItems({"0 - Bypassed (0 ps)", "1 - Divided (100 ps)", "2 - Delayed (400 ps)", "3 - Divided and Delayed (500 ps)"});
                QVariant propertyValue = comboBox->setProperty("ComboBoxName", "CLKoutX_MUX[1:0]");
                break;
            } case 1: {
                comboBox->addItems({"0 - Disabled", "1 - Enabled"});
                QVariant propertyValue = comboBox->setProperty("ComboBoxName", "CLKoutX_EN");
                break;
            }
        }

        QVBoxLayout *layout = new QVBoxLayout(container);
        layout->addWidget(comboBox);

        treeView->setIndexWidget(lineEditIndex, container);
    }

    if (!lineEditIndex.isValid()) {
           qDebug() << "Invalid index!";
           return;
       }
}

void LMK1000Widget::viewTree()
{
    QVBoxLayout *layout = new QVBoxLayout();

    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Register", "Bit Value"});

    QStandardItem *itm0    = new QStandardItem("R0");
    QStandardItem *child01 = new QStandardItem("RESET");
    QStandardItem *child02 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child03 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child04 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child05 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm0->appendRow(QList<QStandardItem*>() << child01 << new QStandardItem());
    itm0->appendRow(QList<QStandardItem*>() << child02 << new QStandardItem());
    itm0->appendRow(QList<QStandardItem*>() << child03 << new QStandardItem());
    itm0->appendRow(QList<QStandardItem*>() << child04 << new QStandardItem());
    itm0->appendRow(QList<QStandardItem*>() << child05 << new QStandardItem());

    QStandardItem *itm1    = new QStandardItem("R1");
    QStandardItem *child12 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child13 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child14 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child15 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm1->appendRow(QList<QStandardItem*>() << child12 << new QStandardItem());
    itm1->appendRow(QList<QStandardItem*>() << child13 << new QStandardItem());
    itm1->appendRow(QList<QStandardItem*>() << child14 << new QStandardItem());
    itm1->appendRow(QList<QStandardItem*>() << child15 << new QStandardItem());

    QStandardItem *itm2    = new QStandardItem("R2");
    QStandardItem *child22 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child23 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child24 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child25 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm2->appendRow(QList<QStandardItem*>() << child22 << new QStandardItem());
    itm2->appendRow(QList<QStandardItem*>() << child23 << new QStandardItem());
    itm2->appendRow(QList<QStandardItem*>() << child24 << new QStandardItem());
    itm2->appendRow(QList<QStandardItem*>() << child25 << new QStandardItem());

    QStandardItem *itm3    = new QStandardItem("R3");
    QStandardItem *child32 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child33 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child34 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child35 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm3->appendRow(QList<QStandardItem*>() << child32 << new QStandardItem());
    itm3->appendRow(QList<QStandardItem*>() << child33 << new QStandardItem());
    itm3->appendRow(QList<QStandardItem*>() << child34 << new QStandardItem());
    itm3->appendRow(QList<QStandardItem*>() << child35 << new QStandardItem());

    QStandardItem *itm4    = new QStandardItem("R4");
    QStandardItem *child42 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child43 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child44 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child45 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm4->appendRow(QList<QStandardItem*>() << child42 << new QStandardItem());
    itm4->appendRow(QList<QStandardItem*>() << child43 << new QStandardItem());
    itm4->appendRow(QList<QStandardItem*>() << child44 << new QStandardItem());
    itm4->appendRow(QList<QStandardItem*>() << child45 << new QStandardItem());

    QStandardItem *itm5    = new QStandardItem("R5");
    QStandardItem *child52 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child53 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child54 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child55 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm5->appendRow(QList<QStandardItem*>() << child52 << new QStandardItem());
    itm5->appendRow(QList<QStandardItem*>() << child53 << new QStandardItem());
    itm5->appendRow(QList<QStandardItem*>() << child54 << new QStandardItem());
    itm5->appendRow(QList<QStandardItem*>() << child55 << new QStandardItem());

    QStandardItem *itm6    = new QStandardItem("R6");
    QStandardItem *child62 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child63 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child64 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child65 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm6->appendRow(QList<QStandardItem*>() << child62 << new QStandardItem());
    itm6->appendRow(QList<QStandardItem*>() << child63 << new QStandardItem());
    itm6->appendRow(QList<QStandardItem*>() << child64 << new QStandardItem());
    itm6->appendRow(QList<QStandardItem*>() << child65 << new QStandardItem());

    QStandardItem *itm7    = new QStandardItem("R7");
    QStandardItem *child72 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child73 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child74 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child75 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm7->appendRow(QList<QStandardItem*>() << child72 << new QStandardItem());
    itm7->appendRow(QList<QStandardItem*>() << child73 << new QStandardItem());
    itm7->appendRow(QList<QStandardItem*>() << child74 << new QStandardItem());
    itm7->appendRow(QList<QStandardItem*>() << child75 << new QStandardItem());

    QStandardItem *itm9   = new QStandardItem("R9");
    QStandardItem *child9 = new QStandardItem("Vboost");

    itm9->appendRow(QList<QStandardItem*>() << child9 << new QStandardItem());

    QStandardItem *itm14    = new QStandardItem("R14");
    QStandardItem *child142 = new QStandardItem("POWERDOWN");
    QStandardItem *child143 = new QStandardItem("EN_CLKout_Global");
    QStandardItem *child144 = new QStandardItem("CLKin_SELECT");

    itm14->appendRow(QList<QStandardItem*>() << child142 << new QStandardItem());
    itm14->appendRow(QList<QStandardItem*>() << child143 << new QStandardItem());
    itm14->appendRow(QList<QStandardItem*>() << child144 << new QStandardItem());

    model->appendRow(QList<QStandardItem*>() << itm0);
    model->appendRow(QList<QStandardItem*>() << itm1);
    model->appendRow(QList<QStandardItem*>() << itm2);
    model->appendRow(QList<QStandardItem*>() << itm3);
    model->appendRow(QList<QStandardItem*>() << itm4);
    model->appendRow(QList<QStandardItem*>() << itm5);
    model->appendRow(QList<QStandardItem*>() << itm6);
    model->appendRow(QList<QStandardItem*>() << itm7);
    model->appendRow(QList<QStandardItem*>() << itm9);
    model->appendRow(QList<QStandardItem*>() << itm14);

    treeView->setModel(model);

    if (model) blockEditing(model);

    for (int i = 0; i < itm0->rowCount(); i++) {
        QModelIndex index = model->index(i, 1, itm0->index());
        QWidget *container = new QWidget();


        if (i == 0) {
            QComboBox *comboBox = new QComboBox(container);
            comboBox->addItems({"0 - No reset", "1 - Reset"});
            QVariant propertyValue = comboBox->setProperty("ComboBoxName", "RESET");

            QVBoxLayout *layout = new QVBoxLayout(container);
            layout->addWidget(comboBox);
            treeView->setIndexWidget(index, container);

            QModelIndex index = model->index(i, 0);

            connect(comboBox, &QComboBox::currentTextChanged, [=](const QString &text) {
                for (int k = 1; k < itm0->rowCount(); k++) {
                    QModelIndex rowIndex = model->index(k, 1, itm0->index());
                    QStandardItem *item = model->itemFromIndex(rowIndex);
                    QWidget *widget = treeView->indexWidget(rowIndex);

                    if (item) {
                        if (text == "1 - Reset") {
                            item->setBackground(QBrush(Qt::lightGray));

                            if (widget) {
                                QComboBox *nestedComboBox = widget->findChild<QComboBox *>();
                                if (nestedComboBox) {
                                    nestedComboBox->setEnabled(false);
                                }

                                QLineEdit *lineEdit = widget->findChild<QLineEdit *>();
                                if (lineEdit) {
                                    lineEdit->setReadOnly(true);
                                }
                            }
                        } else {
                            item->setBackground(QBrush(Qt::white));

                            if (widget) {
                                QLineEdit *lineEdit = widget->findChild<QLineEdit *>();
                                if (lineEdit) {
                                    lineEdit->setReadOnly(false);
                                }

                                QComboBox *nestedComboBox = widget->findChild<QComboBox *>();
                                if (nestedComboBox) {
                                    nestedComboBox->setEnabled(true);
                                }
                            }
                        }
                    }
                }
            });
        } else {
            if (itm0) setupWidgets(itm0, i-1, index);
            else qDebug() << "itm0 является недействительным";
        }
    }


    QStandardItem* items[] = { itm1, itm2, itm3, itm4, itm5, itm6, itm7 };
    for (int j = 0; j < 7; j++) {
        QStandardItem* currentItem = items[j];
        if (!currentItem) {
            qDebug() << "itm" << (j + 1) << "является недействительным";
            continue;
        }
        for (int i = 0; i < currentItem->rowCount(); i++) {
            QModelIndex index = model->index(i, 1, currentItem->index());
            setupWidgets(currentItem, i, index);
        }
    }

    QModelIndex index = model->index(0, 1, itm9->index());
    QWidget *container = new QWidget();
    QComboBox *comboBox = new QComboBox(container);
    QVariant propertyValue = comboBox->setProperty("ComboBoxName", "Vboost");
    comboBox->addItems({"0", "1"});
    QVBoxLayout *layout9 = new QVBoxLayout(container);
    layout9->addWidget(comboBox);
    treeView->setIndexWidget(index, container);

    for (int i = 0; i < itm14->rowCount(); i++) {
        QModelIndex index = model->index(i, 1, itm14->index());
        switch (i) {
            case 0: {
                QWidget *container = new QWidget();
                QComboBox *comboBox = new QComboBox(container);
                QVariant propertyValue = comboBox->setProperty("ComboBoxName", "POWERDOWN");
                comboBox->addItems({"0 - Normal Operation", "1 - Entire Device Powered Down"});
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(comboBox);
                treeView->setIndexWidget(index, container);

                break;
            } case 1: {
                QWidget *container = new QWidget();
                QComboBox *comboBox = new QComboBox(container);
                QVariant propertyValue = comboBox->setProperty("ComboBoxName", "EN_CLKout_Global");
                comboBox->addItems({"1 - Normal Operation", "0 - All Off"});
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(comboBox);
                treeView->setIndexWidget(index, container);

                break;
            } case 2: {
                QWidget *container = new QWidget();
                QComboBox *comboBox = new QComboBox(container);
                QVariant propertyValue = comboBox->setProperty("ComboBoxName", "CLKin_SELECT");
                comboBox->addItems({"0 - CLKin1", "1 - CLKin0"});
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(comboBox);
                treeView->setIndexWidget(index, container);

                break;
            }
        }
    }

    layout->addWidget(treeView);

    toggleButton = new QPushButton("Expand All");
    layout->addWidget(toggleButton);

    QWidget *buttons = new QWidget();
    QHBoxLayout *layout_buttons = new QHBoxLayout(buttons);

    saveButton = new QPushButton("Save", buttons);
    layout_buttons->addWidget(saveButton);

    loadButton = new QPushButton("Download", buttons);
    layout_buttons->addWidget(loadButton);

    buttons->setLayout(layout_buttons);
    layout->addWidget(buttons);

    QWidget *buttons2 = new QWidget();
    QHBoxLayout *layout_buttons2 = new QHBoxLayout(buttons);

    save_elem = new QPushButton("Save element", buttons);
    layout_buttons2->addWidget(save_elem);

    load_elem = new QPushButton("Download element", buttons);
    layout_buttons2->addWidget(load_elem);

    buttons2->setLayout(layout_buttons2);
    layout->addWidget(buttons2);

    connect(toggleButton, &QPushButton::clicked, this, &LMK1000Widget::on_toggle_button_clicked);
    connect(saveButton, &QPushButton::clicked, this, &LMK1000Widget::on_save_button_clicked);
    connect(treeView, &QTreeView::clicked, this, &LMK1000Widget::onParentItemClicked);
    connect(loadButton, &QPushButton::clicked, this, &LMK1000Widget::load_all);
    connect(load_elem, &QPushButton::clicked, this, &LMK1000Widget::load_element);

    setLayout(layout);

}

void LMK1000Widget::onParentItemClicked(const QModelIndex& index) {

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
    QStandardItem* item = model->itemFromIndex(index);

    if (item != nullptr) {
        disconnect(save_elem, &QPushButton::clicked, this, nullptr);
        connect(save_elem, &QPushButton::clicked, this, [this, item]() {
            saveItem(item);
        });
    }

}

void LMK1000Widget::hasChildren (QStandardItem *selectedItem, rapidjson::Document::AllocatorType &allocator, rapidjson::Value &jsonItem, QStandardItemModel* model, QTreeView* treeView, bool HCMflag) {

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
//                            checkBoxValue = "None";
//                        else if (checkBox->isChecked())
//                            checkBoxValue = "True";
//                        else checkBoxValue = "False";

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

void LMK1000Widget::saveItem(QStandardItem *selectedItem) {

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

void LMK1000Widget::on_save_button_clicked() {

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

}

void LMK1000Widget::updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& dataArray, QStandardItem* parentItem) {

    if (!dataArray.IsArray()) {
        qDebug() << "dataArray не является массивом";
        QMessageBox::warning(this, "Ошибка", "Неверная структура файла");
        return;
    }

    if (dataArray.Size() != parentItem->rowCount()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось считать файл - таблицы не совпадают!");
        return;
    }

    for (int j = 0; j < parentItem->rowCount(); j++) {
        QStandardItem* child = parentItem->child(j);

        if (child) {
            rapidjson::Value combinedArray(rapidjson::kArrayType);

            const rapidjson::Value& subChild = dataArray[j];
            if (!subChild.IsObject()) {
                qDebug() << "subChild не является объектом";
                continue;
            }

            if (subChild.HasMember("Text") && subChild.HasMember("Value")) {
                QString text = QString::fromStdString(subChild["Text"].GetString());
                QString value = QString::fromStdString(subChild["Value"].GetString());

                QModelIndex index = model->index(j, 1, parentItem->index());
                QWidget* widget = treeView->indexWidget(index);

                if (widget && index.isValid()) {

                    QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
                    if (!lineEdits.isEmpty()) {
                        for (QLineEdit* lineEdit : lineEdits) {
                            if (lineEdit && lineEdit->property("lineEditName") == text) {
                                lineEdit->setText(value);
                            } else {
                                QMessageBox::warning(this, "Ошибка", "Неверная структура файла - невозможно заполнить элемент " + text);
                                break;
                            }
                        }
                    }

                    QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
                    for (QCheckBox* checkBox : checkBoxes) {
                        if (checkBox) {
                            if (value == "True") {
                                checkBox->setChecked(true);
                            } else if (value == "False") {
                                checkBox->setChecked(false);
                            } else if (value == "None") {
                                checkBox->setCheckState(Qt::PartiallyChecked);
                            }
                            break;
                        }
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
                            } else {
                                QMessageBox::warning(this, "Ошибка", "Неверная структура файла - невозможно заполнить элемент " + text);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

}

void LMK1000Widget::load_all() {
    load("output.json");
}

void LMK1000Widget:: load_element() {
    load("save_element.json");
}

void LMK1000Widget::load(const QString& filePath)
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

}

void LMK1000Widget::on_toggle_button_clicked()
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
