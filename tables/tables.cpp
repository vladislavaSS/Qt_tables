#include "tables.h"

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

    treeView->setColumnWidth(0, 200);
    treeView->setMinimumSize(800, 600);

    //for AD9122 and AD9518
//    tablesInstance->ADflag = 1;
//    tablesInstance->LMKflag = 0;
//    tablesInstance->HMCflag = 0;
//    tablesInstance->bitCount = 8;

    //for LMK1000
//    tablesInstance->ADflag = 0;
//    tablesInstance->LMKflag = 1;
//    tablesInstance->HMCflag = 0;
//    tablesInstance->bitCount = 32;

    //for HMC1035
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

    connect(model, &QStandardItemModel::itemChanged, this, [this](QStandardItem *item) {
      QModelIndex index = model->indexFromItem(item);
      tablesInstance->onItemClicked(index);
    });

    tablesInstance->toggleButton = new QPushButton("Expand All");
    layout->addWidget(tablesInstance->toggleButton);

    tablesInstance->saveButton = new QPushButton("Save All");
    layout->addWidget(tablesInstance->saveButton);


    tablesInstance->loadButton = new QPushButton("Load All");
    layout->addWidget(tablesInstance->loadButton);


    connect(tablesInstance->toggleButton, &QPushButton::clicked, tablesInstance, &Tables::on_toggle_button_clicked);

    connect(tablesInstance->saveButton, &QPushButton::clicked, tablesInstance, &Tables::serialized); //function with arguments - back it
    connect(tablesInstance->loadButton, &QPushButton::clicked, tablesInstance, &Tables::deserialized); //function with arguments



    setLayout(layout);

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

        QLineEdit *lineEdit = new QLineEdit();
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

        connect(lineEdit, &QLineEdit::textChanged, [&, registerItem]() { emit model->itemChanged(registerItem); });
    }

}

void AD9122Widget::appendRows(QJsonObject registerObject, QStandardItem *rootItem) {

    if (registerObject.contains("addresses")) {
        QJsonArray registersArray = registerObject["addresses"].toArray();

        for (const QJsonValue &regValue : registersArray) {
            QJsonObject addressObject = regValue.toObject();
            QString regAddress = addressObject["address"].toString();

            QStandardItem *addressItem = new QStandardItem(regAddress);

            QWidget *container = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(container);
            container->setLayout(layout);

            rootItem->appendRow(QList<QStandardItem*>() << addressItem << new QStandardItem());

            if (addressObject.contains("bits")) {
                QJsonArray bitsArray = addressObject["bits"].toArray();
                for (const QJsonValue &bitValue : bitsArray) {
                    QJsonObject bitObject = bitValue.toObject();
                    createWidgets(bitObject, container, layout, rootItem);
                }
            }
        }
    } else if (registerObject.contains("address")) {

        QString regAddress = registerObject["address"].toString();
        QStandardItem *addressItem = new QStandardItem(regAddress);

        QWidget *container = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(container);
        container->setLayout(layout);

        rootItem->appendRow(QList<QStandardItem*>() << addressItem << new QStandardItem());

        if (registerObject.contains("bits")) {
            QJsonArray bitsArray = registerObject["bits"].toArray();
            for (const QJsonValue &bitValue : bitsArray) {
                QJsonObject bitObject = bitValue.toObject();
                createWidgets(bitObject, container, layout, rootItem);
            }
        }

        if (registerObject["address"].toString() == "0x05"){

            QString vcoRegtxt = registerObject["child"].toString();
            QString regName = registerObject["name"].toString();
            QJsonArray childArray = registerObject["child"].toArray();
            for (const QJsonValue &childValue : childArray) {
                QJsonObject childObject = childValue.toObject();
                appendRows(childObject, addressItem);
            }
        }

    }
}

void AD9122Widget::loadJsonData(const QString &fileName) {

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
            for (const QJsonValue &value : registersArray) {
                QJsonObject registerObject = value.toObject();

                  QString regName = registerObject["name"].toString();
                  QStandardItem *registerItem = new QStandardItem(regName);

                  rootItem->appendRow(registerItem);
                  appendRows(registerObject, registerItem);

            }
        }
    }



}



