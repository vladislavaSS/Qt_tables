#include "AD9122-widget.h"
#include "CustomLineEdit.h"

AD9122Widget::AD9122Widget(QWidget *parent)
    : QWidget (parent),
      tablesInstance(new Tables()),
      treeView(tablesInstance->treeView),
      model(tablesInstance->model),
      treeExpanded(tablesInstance->treeExpanded)
{
    layout = new QVBoxLayout(this);
    layout->addWidget(treeView);
    setLayout(layout);
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels(QStringList() << "Name" << "value");
    treeView->setModel(model);


//    viewTree();
    treeView->setColumnWidth(0, 200);
    treeView->setMinimumSize(800, 600);

//    tablesInstance->ADflag = 1;
//    tablesInstance->LMKflag = 0;
//    tablesInstance->bitCount = 8;

//    tablesInstance->ADflag = 0;
//    tablesInstance->LMKflag = 1;
//    tablesInstance->bitCount = 32;

    tablesInstance->HMCflag = 1;
    tablesInstance->ADflag = 0;
    tablesInstance->LMKflag = 0;
    tablesInstance->bitCount = 24;

//    loadJsonData("AD9518.json");
//    loadJsonData("AD9122.json");
//    loadJsonData("LMK1000.json");
    loadJsonData("HMC1035.json");

    if (model) tablesInstance->blockEditing(model);

    layout->addWidget(treeView);

    tablesInstance->toggleButton = new QPushButton("Expand All");
    layout->addWidget(tablesInstance->toggleButton);

    QWidget *buttons = new QWidget();
    QHBoxLayout *layout_buttons = new QHBoxLayout(buttons);

    tablesInstance->saveButton = new QPushButton("Save", buttons);
    layout_buttons->addWidget(tablesInstance->saveButton);

    tablesInstance->loadButton = new QPushButton("Download", buttons);
    layout_buttons->addWidget(tablesInstance->loadButton);

    buttons->setLayout(layout_buttons);
    layout->addWidget(buttons);

    QWidget *buttons2 = new QWidget();

    tablesInstance->saveButton = new QPushButton("Save element", buttons);
    layout_buttons->addWidget(tablesInstance->saveButton);

    tablesInstance->loadButton = new QPushButton("Download element", buttons);
    layout_buttons->addWidget(tablesInstance->loadButton);

    buttons2->setLayout(layout_buttons);
    layout->addWidget(buttons2);

    connect(tablesInstance->toggleButton, &QPushButton::clicked, tablesInstance, &Tables::on_toggle_button_clicked);
    connect(tablesInstance->saveButton, &QPushButton::clicked, tablesInstance, &Tables::saveButton);
    connect(tablesInstance->treeView, &QTreeView::clicked, tablesInstance, &Tables::onItemClicked);
    connect(tablesInstance->loadButton, &QPushButton::clicked, tablesInstance, &Tables::loadAll);
    connect(tablesInstance->loadButton, &QPushButton::clicked, tablesInstance, &Tables::loadElement);

    setLayout(layout);

    connect(model, &QStandardItemModel::itemChanged, this, [this](QStandardItem *item) {
      QModelIndex index = model->indexFromItem(item);
      tablesInstance->onItemClicked(index);
    });

}



void AD9122Widget::createWidgets(QJsonObject bitObject, QWidget *container, QVBoxLayout *layout, QStandardItem *registerItem) {

    QString bit = bitObject["bit"].toString();
    QStringList parts = bit.split(':');
    int bit_int = 1;
    if (!parts.isEmpty()){
        bit_int = parts[0].toInt();
        bit = QString::number(bit_int);
    }
    QString bitName = bitObject["name"].toString();
    QString bitDef = bitObject["default"].toString();
    QString method = bitObject["method"].toString();
    QString access = bitObject["access"].toString();
    int bitW = 0;
    if (parts.size() == 2) {
        bool ok1, ok2;
        int bitStart = parts[0].toInt(&ok1);
        int bitEnd = parts[1].toInt(&ok2);

        if (ok1 && ok2) {
            bitW = bitStart - bitEnd + 1;
        }
    }

    QModelIndex index1 = model->index(registerItem->rowCount()-1, 1, registerItem->index());

    if (method == "CheckBox") {

        if (bitDef.isEmpty()) bitDef = "2";
        QCheckBox *checkBox = new QCheckBox(bitName);
        checkBox->setProperty("bitName", bitName);
        checkBox->setProperty("bitNumber", bit);
        checkBox->setProperty("bitWidth", 1);
        checkBox->setProperty("default", bitDef);

        switch (bitDef.toInt()) {
          case 0:
            checkBox->setChecked(false);
            checkBox->setTristate(false);
            break;
          case 1:
            checkBox->setChecked(true);
            checkBox->setTristate(false);
            break;
          case 2:
            checkBox->setCheckState(Qt::PartiallyChecked);
            checkBox->setTristate(true);
            break;
        }

        if (access == "RO") checkBox->setEnabled(false);

        layout->addWidget(checkBox);
        treeView->setIndexWidget(index1, container);

        connect(checkBox,&QCheckBox::clicked, model,[&,registerItem](){ emit model->itemChanged(registerItem); });

    } else if (method == "ComboBox") {

        QComboBox *comboBox = new QComboBox();
        comboBox->setProperty("bitName", bitName);
        comboBox->setProperty("bitNumber", bit);
        comboBox->setProperty("bitWidth", 1);
        comboBox->setProperty("default", bitDef);
        comboBox->setProperty("bitWidth", bitW);

        if (!tablesInstance->LMKflag){
            QLabel *label = new QLabel(bitName);
            layout->addWidget(label);
        }

        QJsonValue dataValue = bitObject["data"];
        QStringList list;

        if (dataValue.isArray()) {
            QJsonArray dataArray = dataValue.toArray();

            for (const QJsonValue &value : dataArray)
                if (value.isString()) comboBox->addItem(value.toString());
        }

        if (access == "RO") comboBox->setEnabled(false);

        layout->addWidget(comboBox);
        treeView->setIndexWidget(index1, container);

        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&, registerItem]() { emit model->itemChanged(registerItem); });

    } else if (method == "LineEdit") {

        CustomLineEdit *lineEdit = new CustomLineEdit();
        lineEdit->setProperty("bitName", bitName);
        lineEdit->setProperty("bitNumber", bit);
        lineEdit->setProperty("bitWidth", bitW);
        lineEdit->setProperty("default", bitDef);

        if (!tablesInstance->LMKflag){
            QLabel *label = new QLabel(bitName);
            layout->addWidget(label);
        }

        if (access == "RO") lineEdit->setEnabled(false);

        layout->addWidget(lineEdit);
        treeView->setIndexWidget(index1, container);

        connect(lineEdit, &CustomLineEdit::textChanged, [&, registerItem]() { emit model->itemChanged(registerItem); });
    }

}

void AD9122Widget::loadJsonData(const QString &fileName) {

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
    if (jsonDoc.isNull()) {
        qDebug() << "Ошибка чтения JSON";
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();
    QStandardItem *rootItem = model->invisibleRootItem();

    if (jsonObject.contains("fields")) {
        QJsonObject fieldsObject = jsonObject["fields"].toObject();

        if (fieldsObject.contains("registers")) {
            QJsonArray registersArray = fieldsObject["registers"].toArray();
            for (const QJsonValue &value : registersArray) {
                QJsonObject registerObject = value.toObject();
                QString regName = registerObject["name"].toString();

                QStandardItem *registerItem = new QStandardItem(regName);
                rootItem->appendRow(registerItem);

                if (registerObject.contains("addresses")) {
                    QJsonArray registersArray = registerObject["addresses"].toArray();

                    for (const QJsonValue &regValue : registersArray) {
                        QJsonObject addressObject = regValue.toObject();
                        QString regAddress = addressObject["address"].toString();

                        QStandardItem *addressItem = new QStandardItem(regAddress);

                        QWidget *container = new QWidget();
                        QVBoxLayout *layout = new QVBoxLayout(container);
                        container->setLayout(layout);

                        registerItem->appendRow(QList<QStandardItem*>() << addressItem << new QStandardItem());

                        if (addressObject.contains("bits")) {
                            QJsonArray bitsArray = addressObject["bits"].toArray();
                            for (const QJsonValue &bitValue : bitsArray) {
                                QJsonObject bitObject = bitValue.toObject();
                                createWidgets(bitObject, container, layout, registerItem);
                            }
                        }
                    }
                } else {

                    QString regAddress = registerObject["address"].toString();
                    QStandardItem *addressItem = new QStandardItem(regAddress);

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    container->setLayout(layout);

                    registerItem->appendRow(QList<QStandardItem*>() << addressItem << new QStandardItem());

                    if (registerObject.contains("bits")) {
                        QJsonArray bitsArray = registerObject["bits"].toArray();
                        for (const QJsonValue &bitValue : bitsArray) {
                            QJsonObject bitObject = bitValue.toObject();
                            createWidgets(bitObject, container, layout, registerItem);
                        }
                    }
                }
            }
        }
    }



}




void AD9122Widget::viewTree() {

    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Register (address - hex)", "Bits (7-0)"});

    treeView->setModel(model);
    layout->addWidget(treeView);

    int regIndex = 0;

    for (int i = 0; i < itemNames.size(); ++i) {
        QString itemText = itemNames.at(i);
        QStandardItem *item = new QStandardItem(itemText);
        model->appendRow(item);

        if (itemText == "PLL Status" || itemText == "Sync Status" || itemText == "Event Flag" || itemText == "Sync Control" || itemText == "FIFO Status") {
            if (regIndex < regNames.size()) {
                item->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
            if (regIndex < regNames.size()) {
                item->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
        } else if (itemText == "PLL Control") {
            for (int j = 0; j < 3; ++j) {
                if (regIndex < regNames.size()) item->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex++)) << new QStandardItem());
            }
        } else {
            if (regIndex < regNames.size()) {
                item->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex++)) << new QStandardItem());
            }
        }

        switch (i) {
            case 0:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("SDIO", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("LSB_FIRST", Unchecked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox = tables.createCheckBoxWidget("reset", Unchecked, 5, 1);
                layout->addWidget(checkBox);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 1:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Power down I DAC", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Power down Q DAC", Unchecked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Power down data receiver", Unchecked, 5, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("Power down auxiliary ADC", Checked, 4, 1);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 2:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Binary data format", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Q data first", Unchecked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("MSB swap", Unchecked, 5, 1);
                layout->addWidget(checkBox3);

                QWidget *comboBoxWidget4 = tables.createComboBoxWidgetLable("Data Bus Width[1:0]", {"00",
                                                                                             "01",
                                                                                             "10",
                                                                                             "11"}, 1, 2);
                layout->addWidget(comboBoxWidget4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 3:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Enable PLL lock lost", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Enable PLL locked", Unchecked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Enable sync signal lost", Unchecked, 5, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("Enable sync signal locked", Unchecked, 4, 1);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = tables.createCheckBoxWidget("Enable FIFO Warning 1", Unchecked, 1, 1);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = tables.createCheckBoxWidget("Enable FIFO Warning 2", Unchecked, 0, 1);
                layout->addWidget(checkBox6);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 4:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Enable AED compare pass", Unchecked, 3, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Enable AED compare fail", Unchecked, 2, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("Enable SED compare fail", Unchecked, 1, 1);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                break;

            }
            case 5:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-2, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Enable PLL lock lost", Undefined, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Enable PLL locked", Undefined, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Enable sync signal lost", Undefined, 5, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("Enable sync signal locked", Undefined, 4, 1);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = tables.createCheckBoxWidget("Enable FIFO Warning 1", Undefined, 1, 1);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = tables.createCheckBoxWidget("Enable FIFO Warning 2", Undefined, 0, 1);
                layout->addWidget(checkBox6);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox11 = tables.createCheckBoxWidget("AED compare pass", Undefined, 4, 1);
                layout2->addWidget(checkBox11);

                QCheckBox *checkBox12 = tables.createCheckBoxWidget("AED compare fail", Undefined, 3, 1);
                layout2->addWidget(checkBox12);

                QCheckBox *checkBox13 = tables.createCheckBoxWidget("SED compare fail", Undefined, 2, 1);
                layout2->addWidget(checkBox13);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 6:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("DACCLK duty correction", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QModelIndex index2 = model->index(item->rowCount()-1, 1, item->index());
                QCheckBox *checkBox2 = tables.createCheckBoxWidget("REFCLK duty correction", Unchecked, 6, 1);
                layout->addWidget(checkBox2);

                QModelIndex index3 = model->index(item->rowCount()-1, 1, item->index());
                QCheckBox *checkBox3 = tables.createCheckBoxWidget("DACCLK cross-correction", Checked, 5, 1);
                layout->addWidget(checkBox3);

                QModelIndex index4 = model->index(item->rowCount()-1, 1, item->index());
                QCheckBox *checkBox4 = tables.createCheckBoxWidget("REFCLK cross-correction", Checked, 4, 1);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 7:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-3, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("PLL enable", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("PLL manual enable", Checked, 6, 1);
                layout->addWidget(checkBox2);

                QWidget *widget = tables.createLineEditWithSaveButton(item->rowCount()-1, 63, 1,
                    "Manual VCO Band[5:0] (0-63)...",
                    "Manual VCO Band[5:0] must be 0-63",
                    "0", 5, 6);
                layout->addWidget(widget);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(item->rowCount()-2, 1, item->index());

                QWidget *comboBoxWidget4 = tables.createComboBoxWidgetLable("PLL Loop Bandwidth[1:0]", {"11 - narrowest bandwidth",
                                                                                                 "10",
                                                                                                 "01",
                                                                                                 "00 - widest bandwidth"}, 7, 2);
                layout2->addWidget(comboBoxWidget4);

                QModelIndex index5 = model->index(item->rowCount()-1, 1, item->index());
                QWidget *widget5 = tables.createLineEditWithSaveButton(item->rowCount()-1, 31, 1,
                    "PLL Charge Pump Current[4:0](0-31)...",
                    "PLL Charge Pump Current[4:0] must be 0-31",
                    "17", 4, 5);
                layout2->addWidget(widget5);

                treeView->setIndexWidget(index2, container2);

                QWidget *container3 = new QWidget();
                QVBoxLayout *layout3 = new QVBoxLayout(container3);
                QModelIndex index3 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *comboBoxWidget1 =  tables.createComboBoxWidgetLable("N2[1:0]", {"11 - fDACCLK/fPC_CLK = 16",
                                                                                  "10 - fDACCLK/fPC_CLK = 8",
                                                                                  "01 - fDACCLK/fPC_CLK = 4",
                                                                                  "00 - fDACCLK/fPC_CLK = 2"}, 7, 2);
                layout3->addWidget(comboBoxWidget1);

                QCheckBox *checkBox7 = tables.createCheckBoxWidget("PLL manual enable", Checked, 4, 1);
                layout3->addWidget(checkBox7);

                QWidget *comboBoxWidget8 =  tables.createComboBoxWidgetLable("N0[1:0]", {"10 - fVCO/fDACCLK = 4",
                                                                                  "00 - fVCO/fDACCLK = 1",
                                                                                  "01 - fVCO/fDACCLK = 2",
                                                                                  "11 - fVCO/fDACCLK = 4"}, 3, 2);
                layout3->addWidget(comboBoxWidget8);

                QWidget *comboBoxWidget9 =  tables.createComboBoxWidgetLable("N1[1:0]", {"01 - fVCO/fDACCLK = 4",
                                                                                  "00 - fVCO/fDACCLK = 2",
                                                                                  "10 - fVCO/fDACCLK = 8",
                                                                                  "11 - fVCO/fDACCLK = 16"}, 1, 2);
                layout3->addWidget(comboBoxWidget9);

                treeView->setIndexWidget(index3, container3);

                break;
            }
            case 8:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-2, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("PLL locked", Undefined, 7, 1);
                layout->addWidget(checkBox1);

                QWidget *widget2 = tables.createLineEditWithSaveButton(item->rowCount()-1, 15, 1,
                    "VCO Control Voltage (0-15)...",
                    "VCO Control Voltage must be 0-15",
                    "", 3, 4);
                layout->addWidget(widget2);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget3 = tables.createLineEditWithSaveButton(item->rowCount()-1, 63, 1,
                    "VCO Band Readback (0-63)...",
                    "VCO Band Readback 0-63",
                    "", 5, 6);
                layout2->addWidget(widget3);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 9:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-2, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Sync enable", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Data/FIFO rate toggle", Checked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Rising edge sync", Checked, 3, 1);
                layout->addWidget(checkBox3);

                QWidget *widget4 = tables.createLineEditWithSaveButton(item->rowCount()-2, 128, 1,
                    "Sync Averaging 0-128...",
                    "Sync Averaging must be power of 2 (0-128)",
                    "0", 2, 3);
                layout->addWidget(widget4);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(item->rowCount()-1, 1, item->index());

                QModelIndex index5 = model->index(item->rowCount()-1, 1, item->index());
                QWidget *widget5 = tables.createLineEditWithSaveButton(item->rowCount()-1, 63, 1,
                    "Sync Phase Request (0-63 DACCLK cycles)...",
                    "Sync Phase Request must be 0-63 DACCLK cycles",
                    "0", 5, 6);
                layout2->addWidget(widget5);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 10:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-2, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Sync lost", Undefined, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Sync locked", Undefined, 6, 1);
                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget3 = tables.createLineEditWithSaveButton(item->rowCount()-1, 63.75, 0.25,
                    "Sync Phase Readback[7:0] (0-63.75)...",
                    "Sync Phase Readback must be 0-63.75",
                    "", 7, 8);
                layout2->addWidget(widget3);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 11:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("LVDS FRAME level high", Undefined, 5, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("LVDS FRAME level low", Undefined, 4, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("LVDS DCI level high", Undefined, 3, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("LVDS DCI level low", Undefined, 2, 1);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = tables.createCheckBoxWidget("LVDS data level high", Undefined, 1, 1);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = tables.createCheckBoxWidget("LVDS data level low", Undefined, 0, 1);
                layout->addWidget(checkBox6);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 12:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *comboBoxWidget1 = tables.createComboBoxWidgetLable("DCI Delay[1:0]", {"00 - 350 ps",
                                                                                        "01 - 590 ps",
                                                                                        "10 - 800 ps",
                                                                                        "11 - 925 ps"}, 1, 2);
                layout->addWidget(comboBoxWidget1);

                treeView->setIndexWidget(index1, container);


                break;
            }
            case 13:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 7, 1,
                    "FIFO Phase Offset (0-7)...",
                    "FIFO Phase Offset must be 0-7",
                    "4", 2, 3);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);


                break;

            }
            case 14:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-2, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("FIFO Warning 1", Undefined, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("FIFO Warning 2", Undefined, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("FIFO soft align acknowledge", Undefined, 2, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("FIFO soft align request", Unchecked, 1, 1);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget5 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "FIFO Level (0-255)...",
                    "FIFO Level must be 0-255",
                    "", 7, 8);
                layout2->addWidget(widget5);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 15:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Bypass premod", Checked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Bypass sinc−1", Checked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Bypass NCO", Checked, 5, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("NCO gain", Unchecked, 3, 1);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = tables.createCheckBoxWidget("Bypass phase compensation and dc offset", Checked, 2, 1);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = tables.createCheckBoxWidget("Select sideband", Unchecked, 1, 1);
                layout->addWidget(checkBox6);

                QCheckBox *checkBox7 = tables.createCheckBoxWidget("Send I data to Q data", Unchecked, 0, 1);
                layout->addWidget(checkBox7);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 16:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *comboBoxWidget1 = tables.createComboBoxWidgetLable("HB1[1:0]", {"00 - input signal not modulated",
                                                                                  "01 - input signal not modulated",
                                                                                  "10 - input signal modulated by fIN1",
                                                                                  "11 - input signal modulated by fIN1"}, 2, 2);
                layout->addWidget(comboBoxWidget1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Bypass HB1", Unchecked, 0, 1);
                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 17:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *comboBoxWidget1 = tables.createComboBoxWidgetLable("HB2[5:0]", {"0 - input signal not modulated",
                                                                                  "9 - input signal not modulated",
                                                                                  "18 - input signal not modulated",
                                                                                  "27 - input signal not modulated",
                                                                                  "36 - input signal modulated by fIN2",
                                                                                  "45 - input signal modulated by fIN2",
                                                                                  "54 - input signal modulated by fIN2",
                                                                                  "63 - input signal modulated by fIN2"}, 6, 6);
                layout->addWidget(comboBoxWidget1);

                QModelIndex index2 = model->index(item->rowCount()-1, 1, item->index());
                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Bypass HB2", Unchecked, 0, 1);
                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 18:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *comboBoxWidget1 = tables.createComboBoxWidgetLable("HB3[5:0]", {"0 - input signal not modulated",
                                                                                  "9 - input signal not modulated",
                                                                                  "18 - input signal not modulated",
                                                                                  "27 - input signal not modulated",
                                                                                  "36 - input signal modulated by fIN3",
                                                                                  "45 - input signal modulated by fIN3",
                                                                                  "54 - input signal modulated by fIN3",
                                                                                  "63 - input signal modulated by fIN3"}, 6, 6);
                layout->addWidget(comboBoxWidget1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Bypass HB3", Unchecked, 0, 1);
                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 19:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 0, 1,
                    "Chip ID...",
                    "Chip ID must be 0-0",
                    "8", 3, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 20:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "FTW [7:0] (0-255)...",
                    "FTW [7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 21:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "FTW [15:8] (0-255)...",
                    "FTW [15:8] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 22:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "FTW [23:16] (0-255)...",
                    "FTW [23:16] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;

            }
            case 23:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "FTW [31:24] (0-255)...",
                    "FTW [31:24] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;

            }
            case 24:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "NCO Phase Offset [7:0] (0-255)...",
                    "NCO Phase Offset [7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 25:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "NCO Phase Offset[15:8] (0-255)...",
                    "NCO Phase Offset[15:8] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 26:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("FRAME FTW acknowledge", Unchecked, 5, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("FRAME FTW request", Unchecked, 4, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Update FTW acknowledge", Unchecked, 1, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("Update FTW request", Unchecked, 0, 1);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 27:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "I Phase Adj[7:0] (0-255)...",
                    "I Phase Adj[7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 28:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 3, 1,
                    "I Phase Adj[9:8] (0-3)...",
                    "I Phase Adj[9:8] must be 0-3",
                    "0", 1, 2);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 29:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Q Phase Adj[7:0] (0-255)...",
                    "Q Phase Adj[7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 30:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 3, 1,
                    "I Phase Adj[9:8] (0-3)...",
                    "I Phase Adj[9:8] must be 0-3",
                    "0", 1, 2);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 31:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "I DAC Offset[7:0] (0-255)...",
                    "I DAC Offset[7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 32:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "I DAC Offset[15:8] (0-255)...",
                    "I DAC Offset[15:8] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 33:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Q DAC Offset[7:0] (0-255)...",
                    "Q DAC Offset[7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 34:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Q DAC Offset[15:8] (0-255)...",
                    "Q DAC Offset[15:8] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 35:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "I DAC FS Adj[7:0] (0-255)...",
                    "I DAC FS Adj[7:0] must be 0-255",
                    "249", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 36:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("I DAC sleep", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QWidget *comboBoxWidget2 = tables.createComboBoxWidgetLable("I Aux DAC[9:8]", {"01",
                                                                                        "00",
                                                                                        "10",
                                                                                        "11"}, 1, 2);
                layout->addWidget(comboBoxWidget2);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 37:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "I Aux DAC (0-255)...",
                    "I Aux DAC must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 38:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("I aux DAC sign", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("I aux DAC current direction", Unchecked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("I aux DAC sleep", Unchecked, 5, 1);
                layout->addWidget(checkBox3);

                QWidget *comboBoxWidget4 = tables.createComboBoxWidgetLable("I Aux DAC[9:8]", {"00",
                                                                                        "01",
                                                                                        "10",
                                                                                        "11"}, 1, 2);
                layout->addWidget(comboBoxWidget4);

                treeView->setIndexWidget(index1, container);


                break;
            }
            case 39:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Q DAC FS Adj[7:0] (0-255)...",
                    "Q DAC FS Adj[7:0] must be 0-255",
                    "249", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 40:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Q DAC sleep", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QWidget *comboBoxWidget4 = tables.createComboBoxWidgetLable("Q DAC FS Adj[9:8]", {"01",
                                                                                           "00",
                                                                                           "10",
                                                                                           "11"}, 1, 2);
                layout->addWidget(comboBoxWidget4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 41:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Q Aux DAC[7:0](0-255)...",
                    "Q Aux DAC[7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 42:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("Q aux DAC sign", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("I aux DAC current direction", Unchecked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Q aux DAC sleep", Unchecked, 5, 1);
                layout->addWidget(checkBox3);

                QWidget *comboBoxWidget4 = tables.createComboBoxWidgetLable("Q Aux DAC[9:8]", {"00",
                                                                                        "01",
                                                                                        "10",
                                                                                        "11"}, 1, 2);
                layout->addWidget(comboBoxWidget4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 43:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 7, 1,
                    "FS Current[2:0] (0-7)...",
                    "FS Current[2:0] must be 0-7",
                    "0", 6, 3);
                layout->addWidget(widget1);

                QWidget *widget2 = tables.createLineEditWithSaveButton(item->rowCount()-1, 7, 1,
                    "Reference Current[2:0] (0-7)...",
                    "Reference Current[2:0] must be 0-7",
                    "1", 3, 3);
                layout->addWidget(widget2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Capacitor value", Unchecked, 0, 1);
                layout->addWidget(checkBox3);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 44:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Die Temp[7:0] (0-255)...",
                    "Die Temp[7:0] must be 0-255",
                    "", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 45:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Die Temp[15:8] (0-255)...",
                    "Die Temp[15:8] must be 0-255",
                    "", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 46:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QCheckBox *checkBox1 = tables.createCheckBoxWidget("SED compare enable", Unchecked, 7, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = tables.createCheckBoxWidget("Sample error detected", Unchecked, 5, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = tables.createCheckBoxWidget("Autoclear enable", Unchecked, 3, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = tables.createCheckBoxWidget("Compare fail", Unchecked, 1, 1);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = tables.createCheckBoxWidget("Compare pass", Unchecked, 0, 1);
                layout->addWidget(checkBox5);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 47:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Compare Value I0[7:0] (0-255)...",
                    "Compare Value I0[7:0] must be 0-255",
                    "182", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 48:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Compare Value I0[15:8] (0-255)...",
                    "Compare Value I0[15:8] must be 0-255",
                    "122", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 49:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Compare Value Q0[7:0] (0-255)...",
                    "Compare Value Q0[7:0] must be 0-255",
                    "69", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 50:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Compare Value Q0[15:8] (0-255)...",
                    "Compare Value Q0[15:8] must be 0-255",
                    "234", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 51:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Compare Value I1[7:0] (0-255)...",
                    "Compare Value I1[7:0] must be 0-255",
                    "22", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 52:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Compare Value I1[15:8] (0-255)...",
                    "Compare Value I1[15:8] must be 0-255",
                    "26", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 53:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Compare Value Q1[7:0] (0-255)...",
                    "Compare Value Q1[7:0] must be 0-255",
                    "198", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 54:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Compare Value Q1[15:8] (0-255)...",
                    "Compare Value Q1[15:8] must be 0-255",
                    "170", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 55:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Errors Detected I_BITS[7:0] (0-255)...",
                    "Errors Detected I_BITS[7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }

            case 56:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Errors Detected I_BITS[15:8] (0-255)...",
                    "Errors Detected I_BITS[15:8] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 57:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Errors Detected Q_BITS[7:0] (0-255)...",
                    "Errors Detected Q_BITS[7:0] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 58:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Errors Detected Q_BITS[15:8] (0-255)...",
                    "Errors Detected Q_BITS[15:8] must be 0-255",
                    "0", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 59:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(item->rowCount()-1, 1, item->index());

                QWidget *widget1 = tables.createLineEditWithSaveButton(item->rowCount()-1, 255, 1,
                    "Revision[3:0] (0-255)...",
                    "Revision[3:0] must be 0-255",
                    "", 5, 4);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
        }
    }

    if (model) tablesInstance->blockEditing(model);

    layout->addWidget(treeView);

    tablesInstance->toggleButton = new QPushButton("Expand All");
    layout->addWidget(tablesInstance->toggleButton);

    QWidget *buttons = new QWidget();
    QHBoxLayout *layout_buttons = new QHBoxLayout(buttons);

    tablesInstance->saveButton = new QPushButton("Save", buttons);
    layout_buttons->addWidget(tablesInstance->saveButton);

    tablesInstance->loadButton = new QPushButton("Download", buttons);
    layout_buttons->addWidget(tablesInstance->loadButton);

    buttons->setLayout(layout_buttons);
    layout->addWidget(buttons);

    QWidget *buttons2 = new QWidget();

    tablesInstance->save_elem = new QPushButton("Save element", buttons);
    layout_buttons->addWidget(tablesInstance->save_elem);

    tablesInstance->load_elem = new QPushButton("Download element", buttons);
    layout_buttons->addWidget(tablesInstance->load_elem);

    buttons2->setLayout(layout_buttons);
    layout->addWidget(buttons2);

    connect(tablesInstance->toggleButton, &QPushButton::clicked, tablesInstance, &Tables::on_toggle_button_clicked);
    connect(tablesInstance->saveButton, &QPushButton::clicked, tablesInstance, &Tables::saveData);
    connect(tablesInstance->treeView, &QTreeView::clicked, tablesInstance, &Tables::onItemClicked);
    connect(tablesInstance->loadButton, &QPushButton::clicked, tablesInstance, &Tables::loadAll);
    connect(tablesInstance->load_elem, &QPushButton::clicked, tablesInstance, &Tables::loadElement);

    setLayout(layout);

}
