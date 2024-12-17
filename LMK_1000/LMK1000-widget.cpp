#include "LMK1000-widget.h"

LMK1000Widget::LMK1000Widget(QWidget *parent)
    : QWidget{parent}, treeView(new QTreeView(this)), model(new QStandardItemModel(this)), treeExpanded(false)
{
    layout = new QVBoxLayout(this);
    setLayout(layout);
    viewTree();
    treeView->setColumnWidth(0, 200);
}

void LMK1000Widget::viewTree()
{
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

    if (model) blockEditing(model);

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
//    QHBoxLayout *layout_buttons2 = new QHBoxLayout(buttons);

    save_elem = new QPushButton("Save element", buttons);
    layout_buttons->addWidget(save_elem);

    load_elem = new QPushButton("Download element", buttons);
    layout_buttons->addWidget(load_elem);

    buttons2->setLayout(layout_buttons);
    layout->addWidget(buttons2);

    connect(toggleButton, &QPushButton::clicked, this, &LMK1000Widget::on_toggle_button_clicked);
    connect(saveButton, &QPushButton::clicked, this, &LMK1000Widget::saveData);
    connect(treeView, &QTreeView::clicked, this, &LMK1000Widget::onParentItemClicked);
    connect(loadButton, &QPushButton::clicked, this, &LMK1000Widget::load_all);
    connect(load_elem, &QPushButton::clicked, this, &LMK1000Widget::load_element);

    setLayout(layout);

}

