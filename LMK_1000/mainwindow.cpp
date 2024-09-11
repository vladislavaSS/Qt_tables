#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <fstream>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

QHash<QModelIndex, WidgetPointers> widgetMap;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), treeView(new QTreeView(this)), model(new QStandardItemModel(this)), treeExpanded(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viewTree();

    treeView -> setColumnWidth(0, 200);
}

MainWindow::~MainWindow()
{
    delete ui;
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

QWidget* MainWindow::createLineEditWithSaveButton(int valueLimit, int modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholderText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *saveButton = new QPushButton("save");

    connect(saveButton, &QPushButton::clicked, [this, lineEdit, valueLimit, modulo, errorMsg, defaultText](){
        onClicked(lineEdit, valueLimit, modulo, errorMsg, defaultText);
    });

    hLayout->addWidget(lineEdit);
    hLayout->addWidget(saveButton);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
}

void MainWindow::onClicked(QLineEdit* lineEdit, int valueLimit, int modulo, const QString& errorMsg, const QString& defaultText) {
        QString inputValue = lineEdit->text();

        if (inputValue.isEmpty()) {
            lineEdit->setText(defaultText);
            return;
        }
            if (inputValue.toInt()) {
                if (!((inputValue.toInt() <= valueLimit) && ((inputValue.toInt() % modulo) == 0))) {
                    QMessageBox::warning(this, "Ошибка", errorMsg);
                    lineEdit->setText(defaultText);
                } else {
                    QString processedValue = QString::number(inputValue.toInt());

                    lineEdit->setText(processedValue);
                    lineEdit->setStyleSheet("color: green;");
                }
            } else {
                QMessageBox::warning(this, "Ошибка", errorMsg);
                lineEdit->setText(defaultText);
            }
}

void MainWindow::setupWidgets(QStandardItem *itm, int rowIndex, QModelIndex lineEditIndex) {

    if (rowIndex == 2) {
        QWidget *widget = createLineEditWithSaveButton(510, 2,
            "Введите значение делителя тактового выхода (0-510)...",
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
//            qDebug() << "Widget set for index:" << lineEditIndex; // Выводим сообщение об успехе
        }

    } else if (rowIndex == 3) {
        QWidget *widget = createLineEditWithSaveButton(2250, 150,
            "Введите значение задержки тактового выхода (0-2250)...",
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
//            qDebug() << "Widget set for index:" << lineEditIndex;
        }
    } else {
        QWidget *container = new QWidget();
        QComboBox *comboBox = new QComboBox(container);

        comboBox->clear();
        switch (rowIndex) {
            case 0:
                comboBox->addItems({"0 - Bypassed (0 ps)", "1 - Divided (100 ps)", "2 - Delayed (400 ps)", "3 - Divided and Delayed (500 ps)"});
                break;
            case 1:
                comboBox->addItems({"0 - Disabled", "1 - Enabled"});
                break;
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

void MainWindow::viewTree()
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

    model->appendRow(QList<QStandardItem*>() << itm0 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm1 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm2 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm3 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm4 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm5 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm6 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm7 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm9 << new QStandardItem(" "));
    model->appendRow(QList<QStandardItem*>() << itm14 << new QStandardItem(" "));

    treeView->setModel(model);

    if (model) blockEditing(model);

    for (int i = 0; i < itm0->rowCount(); i++) {
        QModelIndex index = model->index(i, 1, itm0->index());
        QWidget *container = new QWidget();


        if (i == 0) {
            QComboBox *comboBox = new QComboBox(container);
            comboBox->addItems({"0 - No reset", "1 - Reset"});

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
                comboBox->addItems({"0 - Normal Operation", "1 - Entire Device Powered Down"});
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(comboBox);
                treeView->setIndexWidget(index, container);

                break;
            } case 1: {
                QWidget *container = new QWidget();
                QComboBox *comboBox = new QComboBox(container);
                comboBox->addItems({"1 - Normal Operation", "0 - All Off"});
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(comboBox);
                treeView->setIndexWidget(index, container);

                break;
            } case 2: {
                QWidget *container = new QWidget();
                QComboBox *comboBox = new QComboBox(container);
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

    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::on_toggle_button_clicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::on_save_button_clicked);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::on_load_button_clicked);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

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

            for (int col = 0; col < model->columnCount(); ++col) {
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

void MainWindow::updateChildWidgets(QStandardItemModel* model, const rapidjson::Value& childrenArray, QStandardItem* parentItem) {
    if (!childrenArray.IsArray()) {
        qWarning() << "childrenArray не является массивом";
        return;
    } /*else qDebug() << "it is massiv";*/

//    qDebug() << "size of children: " << childrenArray.Size();

    for (rapidjson::SizeType i = 0; i < childrenArray.Size(); ++i) {
        const rapidjson::Value& value = childrenArray[i];
        if (!value.IsObject()) {
            continue;
        } /*qDebug() << "is object";*/

        QString childIdentifier = value.HasMember("column0") ? QString::fromStdString(value["column0"].GetString()) : QString();
        QString newValue;
        if (value.HasMember("column1")) {
            if (value["column1"].IsString()) newValue = QString::fromStdString(value["column1"].GetString());
            else if (value["column1"].IsInt()) newValue = QString::number(value["column1"].GetInt());
            else newValue = "N/A";
        } else newValue = "N/A";

//        qDebug() << "rows: "<< parentItem->rowCount();

        bool childFound = false;
        for (int j = 0; j < parentItem->rowCount(); ++j) {
            QStandardItem* childItem = parentItem->child(j);
            if (childItem->text() == childIdentifier) {
                childFound = true;

//                qDebug() << "i'm here";

                if (childItem->index().siblingAtColumn(1).data().toString() != newValue) {

                    QModelIndex index = model->index(j, 1, parentItem->index());
//                    QWidget *widget = treeView->indexWidget(index);

//                    qDebug() << index.isValid();
//                    qDebug() << parentItem->index().isValid();

//                    if (!widget) {
//                        qDebug() << "No widget found for index" << index;
//                    } else {
//                        qDebug() << "Widget found, type:" << widget->metaObject()->className();
//                    }

                    QWidget *containerWidget = treeView->indexWidget(index);
                    if (!containerWidget) {
//                        qDebug() << "Container widget is nullptr.";
                        return;
                    }

                    QList<QLineEdit*> lineEdits = containerWidget->findChildren<QLineEdit*>();
                    for (QLineEdit *lineEdit : lineEdits) {
                        lineEdit->setText(newValue);
//                        qDebug() << "Text set in QLineEdit: " << lineEdit->text();
                    }

                    QList<QComboBox*> comboBoxes = containerWidget->findChildren<QComboBox*>();
                    for (QComboBox *comboBox : comboBoxes) {
                        bool found = false;
                        for (int i = 0; i < comboBox->count(); ++i) {
                            QString itemText = comboBox->itemText(i);
                            QString prefix = itemText.split(" ").first();

                            if (prefix == newValue) {
                                comboBox->setCurrentIndex(i);
                                found = true;
//                                qDebug() << "Text found in QComboBox: " << newValue;
                                break;
                            }
                        }

                        if (!found) {
                            comboBox->addItem(newValue);
                            comboBox->setCurrentText(newValue);
//                            qDebug() << "New value added to QComboBox: " << newValue;
                        }
                    }
                }
                break;
            }
        }

        if (!childFound) {
            qWarning() << "Дочерний элемент" << childIdentifier << "не найден для родителя" << parentItem->text();
        }
    }
}

void MainWindow::on_load_button_clicked()
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView -> model());
    QString filePath = "output.json";

//    if (!model) qDebug() << "not model";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
//        qWarning() << "Не удалось открыть файл:" << filePath;
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения!");
        return;
    }/* else qWarning() << "Yдалось открыть файл:";*/

    QByteArray jsonData = file.readAll();
    file.close();

    rapidjson::Document jsonDoc;
    jsonDoc.Parse(jsonData.constData());

    if (jsonDoc.HasParseError()) {
        qDebug() << "JSON parse error at offset:" << jsonDoc.GetErrorOffset();
        qDebug() << "Error description:" << rapidjson::GetParseError_En(jsonDoc.GetParseError());
        return;
    } /*else qDebug() << "parsing is ok";*/

    if (!jsonDoc.IsObject()) {
        qWarning() << "Корневой элемент не является объектом.";
        return;
    } /*else qDebug() << "Корневой элемент является объектом";*/

    if (!jsonDoc.HasMember("items") || !jsonDoc["items"].IsArray()) {
        qWarning() << "'items' не найден или не является массивом.";
        return;
    } /*else qDebug() << "'items' найден или является массивом";*/

    const rapidjson::Value& jsonArray = jsonDoc["items"];

//    qDebug() << "Size: " << jsonArray.Size();

    for (rapidjson::SizeType i = 0; i < jsonArray.Size(); ++i) {
        const rapidjson::Value& value = jsonArray[i];

        if (!value.IsObject()) {
            continue;
        } /*else qDebug() << "value is object";*/

        QString parentIdentifier = QString::fromStdString(value["column0"].GetString());
        QStandardItem* parentItem = nullptr;

//        qDebug() << "row count:" << model->rowCount();

        for (int j = 0; j < model->rowCount(); ++j) {
            if (model->item(i)->text() == parentIdentifier) {
//                qDebug() << "it is" << parentItem;
                parentItem = model->item(i);
//                qDebug() << "it is" << parentItem;
                break;
            } /*else qDebug() << "it is never simillar";*/
        }

        if (!parentItem) {
            qWarning() << "Родительский элемент" << parentIdentifier << "не найден.";
            QMessageBox::warning(this, "Ошибка", "Не удалось считать файл - таблицы не совпадают!");
            break;
        } /*else qWarning() << "Родительский элемент" << parentIdentifier << "найден.";*/

        if (value.HasMember("children") && value["children"].IsArray()) {
//            qDebug() << "you have children";
            const rapidjson::Value& childrenArray = value["children"];
            updateChildWidgets(model, childrenArray, parentItem);

//            qDebug() << "size of cildren" << childrenArray.Size();

            for (rapidjson::SizeType k = 0; k < childrenArray.Size(); ++k) {
                const rapidjson::Value& jsonChild = childrenArray[k];
                QString childIdentifier = QString::fromStdString(jsonChild["column0"].GetString());
                bool foundMatchingChild = false;

                for (int j = 0; j < parentItem->rowCount(); ++j) {
                    if (parentItem->child(j)->text() == childIdentifier) {
                        foundMatchingChild = true;
                        break;
                    }
                }

                if (!foundMatchingChild) {
                    qWarning() << "Ошибка: Дочерний элемент с идентификатором" << childIdentifier << "не соответствует ни одному дочернему элементу родителя" << parentItem->text();
                }
            }
        } /*else qDebug() << "you don't have cildren";*/
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
























