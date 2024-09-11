#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


QWidget* MainWindow::LineOfPower(int rowIndex, int valueLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText) {
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

QWidget* MainWindow::createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholderText);

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

QWidget* MainWindow::createComboBoxWidgetLable(const QString &labelText, const QStringList &options) {
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

QCheckBox* MainWindow::createCheckBoxWidget(const QString &labelText, CheckBoxState state) {
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

void MainWindow::setEditableFlags(QStandardItem *item, bool editable) {
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

void MainWindow::blockEditing(QStandardItemModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *rootItem = model->item(row);
        setEditableFlags(rootItem, false);
    }
}

void MainWindow::on_toggle_button_clicked()
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

void MainWindow::on_save_button_clicked()
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
                        QModelIndex index = model->index(j, 1, item->index());
                        QWidget* widget = treeView->indexWidget(index);

                        for (int col = 0; col < 1; ++col) {
                         QString childData = item->child(j, col) ? item->child(j, col)->text() : QString();
                         jsonChild.AddMember(
                             rapidjson::Value(("column" + QString::number(col)).toStdString().c_str(), allocator),
                             rapidjson::Value(childData.isEmpty() ? "" : childData.toStdString().c_str(), allocator),
                             allocator);
                        }

//                        if (widget && index.isValid()) {
//                            QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
//                            for (QLineEdit* lineEdit : lineEdits) {
//                                if (lineEdit) {
//                                    jsonChild.AddMember(
//                                        rapidjson::Value(("column" + QString::number(1)).toStdString().c_str(), allocator),
//                                        rapidjson::Value("lineEdit"),
//                                        allocator);
//                                    jsonChild.AddMember(
//                                                rapidjson::Value(("column" + QString::number(1)).toStdString().c_str(), allocator),
//                                                rapidjson::Value(lineEdit->text().toStdString().c_str(), allocator),
//                                                allocator);
//                                } else {
//                                    qDebug() << "Found nullptr in lineEdits.";
//                                }
//                            }

                        if (widget && index.isValid()) {

                            QList<QLineEdit*> lineEdits = widget->findChildren<QLineEdit*>();
                            for (QLineEdit* lineEdit : lineEdits) {
                                if (lineEdit) {
                                    jsonChild.AddMember(
                                                rapidjson::Value(("column" + QString::number(1)).toStdString().c_str(), allocator),
                                                rapidjson::Value(lineEdit->text().toStdString().c_str(), allocator),
                                                allocator);
                                } else {
                                    qDebug() << "Found nullptr in lineEdits.";
                                }
                            }

//                            if (widget && index.isValid()) {
//                                QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
//                                for (QCheckBox* checkBox : checkBoxes) {
//                                    if (checkBox) {
//                                        Qt::CheckState state = checkBox->checkState();
//                                        rapidjson::Value valueToSave;
//                                        if (state == Qt::Checked) {
//                                            valueToSave.SetInt(1);
//                                        } else if (state == Qt::Unchecked) {
//                                            valueToSave.SetInt(0);
//                                        } else if (state == Qt::PartiallyChecked) {
//                                            valueToSave.SetString("");
//                                        }

//                                        jsonChild.AddMember(
//                                            rapidjson::Value(("column" + QString::number(1)).toStdString().c_str(), allocator),
//                                            rapidjson::Value("checkBox"),
//                                            allocator);

//                                        jsonChild.AddMember(
//                                            rapidjson::Value(checkBox->text().toStdString().c_str(), allocator),
//                                            valueToSave,
//                                            allocator);
//                                    } else {
//                                        qDebug() << "Found nullptr in checkBoxes.";
//                                    }
//                                }
//                            }

                            if (widget && index.isValid()) {
                                QList<QCheckBox*> checkBoxes = widget->findChildren<QCheckBox*>();
                                for (QCheckBox* checkBox : checkBoxes) {
                                    if (checkBox) {
                                        Qt::CheckState state = checkBox->checkState();
                                        rapidjson::Value valueToSave;
                                        if (state == Qt::Checked) {
                                            valueToSave.SetInt(1);
                                        } else if (state == Qt::Unchecked) {
                                            valueToSave.SetInt(0);
                                        } else if (state == Qt::PartiallyChecked) {
                                            valueToSave.SetString("");
                                        }

                                        rapidjson::Value checkBoxJson(rapidjson::kObjectType);
                                        checkBoxJson.AddMember("checkBoxText", rapidjson::Value(checkBox->text().toStdString().c_str(), allocator), allocator);
                                        checkBoxJson.AddMember("value", valueToSave, allocator);
                                        jsonChild.AddMember("column1", checkBoxJson, allocator);

                                    } else {
                                        qDebug() << "Found nullptr in checkBoxes.";
                                    }
                                }
                            }

                            QList<QComboBox*> comboBoxes = widget->findChildren<QComboBox*>();
                            for (QComboBox* comboBox : comboBoxes) {
                                if (comboBox) {
                                    QString currentText = comboBox->currentText();
                                    QString numberPart;

                                    for (QChar ch : currentText) {
                                        if (ch.isDigit()) numberPart.append(ch); else break;
                                    }

                                    if (!numberPart.isEmpty()) {
                                        bool isNumber;
                                        int number = numberPart.toInt(&isNumber);

                                        if (isNumber) {
                                            jsonChild.AddMember(
                                                rapidjson::Value(("column" + QString::number(1)).toStdString().c_str(), allocator),
                                                rapidjson::Value(number),
                                                allocator);
                                        }
                                    }
                                } else qDebug() << "Found nullptr in comboBoxes.";
                            }


//                            QList<QComboBox*> comboBoxes = widget->findChildren<QComboBox*>();
//                            for (QComboBox* comboBox : comboBoxes) {
//                                if (comboBox) {
//                                    QString currentText = comboBox->currentText();
//                                    QString numberPart;

//                                    for (QChar ch : currentText) if (ch.isDigit()) numberPart.append(ch); else break;

//                                    if (!numberPart.isEmpty()) {
//                                        bool isNumber;
//                                        int number = numberPart.toInt(&isNumber);

//                                        if (isNumber) {
//                                            jsonChild.AddMember(
//                                                rapidjson::Value(("column" + QString::number(1)).toStdString().c_str(), allocator),
//                                                rapidjson::Value(number),
//                                                allocator);
//                                        }
//                                    }
//                                } else qDebug() << "Found nullptr in comboBoxes.";
//                            }
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


void MainWindow::on_load_button_clicked()
{

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
