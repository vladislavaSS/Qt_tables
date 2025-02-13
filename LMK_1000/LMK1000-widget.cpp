#include "LMK1000-widget.h"

LMK1000Widget::LMK1000Widget(Tables* tablesInstance, QWidget *parent)
    : QWidget(parent),
      tablesInstance(tablesInstance),
      treeView(tablesInstance->treeView),
      model(tablesInstance->model),
      treeExpanded(tablesInstance->treeExpanded)
{
    layout = new QVBoxLayout(this);
    setLayout(layout);
    viewTree();
    treeView->setColumnWidth(0, 200);

    tablesInstance->LMKflag = 1;
    tablesInstance->ADflag = 1;
    tablesInstance->bitCount = 32;

}

void LMK1000Widget::setupWidgets(QStandardItem *itm, int rowIndex, QModelIndex lineEditIndex) {

    if (rowIndex == 2) {
        QWidget *widget = tables.createLineEditWithSaveButton(rowIndex, 510, 2,
            "Clock Output Dividers (0-510)",
            "значение делителя тактового выхода должно быть в диапазоне 0-510 и быть четным",
            "2", 15, 8);
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
        QWidget *widget = tables.createLineEditWithSaveButton(rowIndex, 2250, 150,
            "Clock Output Delays (0-2250)",
            "значение задержки тактового выхода должно быть в диапазоне 0-2250 и быть кратным 150",
            "0", 7, 4);
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
                comboBox->addItems({"00 - Bypassed (0 ps)", "01 - Divided (100 ps)", "10 - Delayed (400 ps)", "11 - Divided and Delayed (500 ps)"});
                comboBox->setProperty("ComboBoxName", "CLKoutX_MUX[1:0]");
                comboBox->setProperty("bitNumber", 18);
                comboBox->setProperty("bitWidth", 2);
                break;
            } case 1: {
                comboBox->addItems({"0 - Disabled", "1 - Enabled"});
                comboBox->setProperty("ComboBoxName", "CLKoutX_EN");
                comboBox->setProperty("bitNumber", 16);
                comboBox->setProperty("bitWidth", 1);
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

void LMK1000Widget::viewTree() {

    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Register", "Bit Value"});

    QStandardItem *itm0    = new QStandardItem("0x00");
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

    QStandardItem *itm1    = new QStandardItem("0x01");
    QStandardItem *child12 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child13 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child14 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child15 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm1->appendRow(QList<QStandardItem*>() << child12 << new QStandardItem());
    itm1->appendRow(QList<QStandardItem*>() << child13 << new QStandardItem());
    itm1->appendRow(QList<QStandardItem*>() << child14 << new QStandardItem());
    itm1->appendRow(QList<QStandardItem*>() << child15 << new QStandardItem());

    QStandardItem *itm2    = new QStandardItem("0x02");
    QStandardItem *child22 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child23 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child24 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child25 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm2->appendRow(QList<QStandardItem*>() << child22 << new QStandardItem());
    itm2->appendRow(QList<QStandardItem*>() << child23 << new QStandardItem());
    itm2->appendRow(QList<QStandardItem*>() << child24 << new QStandardItem());
    itm2->appendRow(QList<QStandardItem*>() << child25 << new QStandardItem());

    QStandardItem *itm3    = new QStandardItem("0x03");
    QStandardItem *child32 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child33 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child34 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child35 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm3->appendRow(QList<QStandardItem*>() << child32 << new QStandardItem());
    itm3->appendRow(QList<QStandardItem*>() << child33 << new QStandardItem());
    itm3->appendRow(QList<QStandardItem*>() << child34 << new QStandardItem());
    itm3->appendRow(QList<QStandardItem*>() << child35 << new QStandardItem());

    QStandardItem *itm4    = new QStandardItem("0x04");
    QStandardItem *child42 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child43 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child44 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child45 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm4->appendRow(QList<QStandardItem*>() << child42 << new QStandardItem());
    itm4->appendRow(QList<QStandardItem*>() << child43 << new QStandardItem());
    itm4->appendRow(QList<QStandardItem*>() << child44 << new QStandardItem());
    itm4->appendRow(QList<QStandardItem*>() << child45 << new QStandardItem());

    QStandardItem *itm5    = new QStandardItem("0x05");
    QStandardItem *child52 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child53 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child54 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child55 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm5->appendRow(QList<QStandardItem*>() << child52 << new QStandardItem());
    itm5->appendRow(QList<QStandardItem*>() << child53 << new QStandardItem());
    itm5->appendRow(QList<QStandardItem*>() << child54 << new QStandardItem());
    itm5->appendRow(QList<QStandardItem*>() << child55 << new QStandardItem());

    QStandardItem *itm6    = new QStandardItem("0x06");
    QStandardItem *child62 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child63 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child64 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child65 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm6->appendRow(QList<QStandardItem*>() << child62 << new QStandardItem());
    itm6->appendRow(QList<QStandardItem*>() << child63 << new QStandardItem());
    itm6->appendRow(QList<QStandardItem*>() << child64 << new QStandardItem());
    itm6->appendRow(QList<QStandardItem*>() << child65 << new QStandardItem());

    QStandardItem *itm7    = new QStandardItem("0x07");
    QStandardItem *child72 = new QStandardItem("CLKoutX_MUX [1:0]");
    QStandardItem *child73 = new QStandardItem("CLKoutX_EN");
    QStandardItem *child74 = new QStandardItem("CLKoutX_DIV [7:0]");
    QStandardItem *child75 = new QStandardItem("CLKoutX_DLY [3:0]");

    itm7->appendRow(QList<QStandardItem*>() << child72 << new QStandardItem());
    itm7->appendRow(QList<QStandardItem*>() << child73 << new QStandardItem());
    itm7->appendRow(QList<QStandardItem*>() << child74 << new QStandardItem());
    itm7->appendRow(QList<QStandardItem*>() << child75 << new QStandardItem());

    QStandardItem *itm9   = new QStandardItem("0x09");
    QStandardItem *child9 = new QStandardItem("Vboost");

    itm9->appendRow(QList<QStandardItem*>() << child9 << new QStandardItem());

    QStandardItem *itm14    = new QStandardItem("0x14");
    QStandardItem *child142 = new QStandardItem("CLKin_SELECT");
    QStandardItem *child143 = new QStandardItem("EN_CLKout_Global");
    QStandardItem *child144 = new QStandardItem("POWERDOWN");

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

    if (model) tables.blockEditing(model);

    for (int i = 0; i < itm0->rowCount(); i++) {
        QModelIndex index = model->index(i, 1, itm0->index());
        QWidget *container = new QWidget();


        if (i == 0) {
            QComboBox *comboBox = new QComboBox(container);
            comboBox->addItems({"0 - No reset", "1 - Reset"});
            comboBox->setProperty("bitNumber", 31);
            comboBox->setProperty("bitWidth", 1);
            comboBox->setProperty("ComboBoxName", "RESET");

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
    comboBox->setProperty("bitNumber", 16);
    comboBox->setProperty("bitWidth", 1);
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
                QVariant propertyValue = comboBox->setProperty("ComboBoxName", "CLKin_SELECT");
                comboBox->addItems({"0 - CLKin1", "1 - CLKin0"});
                comboBox->setProperty("bitNumber", 29);
                comboBox->setProperty("bitWidth", 1);
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(comboBox);
                treeView->setIndexWidget(index, container);

                break;
            } case 1: {
                QWidget *container = new QWidget();
                QComboBox *comboBox = new QComboBox(container);
                QVariant propertyValue = comboBox->setProperty("ComboBoxName", "EN_CLKout_Global");
                comboBox->addItems({"1 - Normal Operation", "0 - All Off"});
                comboBox->setProperty("bitNumber", 27);
                comboBox->setProperty("bitWidth", 1);
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(comboBox);
                treeView->setIndexWidget(index, container);

                break;
            } case 2: {
                QWidget *container = new QWidget();
                QComboBox *comboBox = new QComboBox(container);
                QVariant propertyValue = comboBox->setProperty("ComboBoxName", "POWERDOWN");
                comboBox->addItems({"0 - Normal Operation", "1 - Entire Device Powered Down"});
                comboBox->setProperty("bitNumber", 26);
                comboBox->setProperty("bitWidth", 1);
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(comboBox);
                treeView->setIndexWidget(index, container);

                break;
            }
        }
    }

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

