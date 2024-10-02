#include "AD9122-widget.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>

AD9122Widget::AD9122Widget(QWidget *parent)
    : QWidget{parent}, treeView(new QTreeView(this)), model(new QStandardItemModel(this)), treeExpanded(false)
{
    viewTree();
    treeView -> setColumnWidth(0, 200);

}

void AD9122Widget::viewTree() {
    QVBoxLayout *layout = new QVBoxLayout();

    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Register (address - hex)", "Bits"});

    treeView->setModel(model);

    int regIndex = 0;

    for (int i = 0; i < itemNames.size(); ++i) {
        QString itemText = itemNames.at(i);
        QStandardItem *parentItem = new QStandardItem(itemText);
        model->appendRow(parentItem);

        if (itemText == "PLL Status" || itemText == "Sync Status" || itemText == "Event Flag" || itemText == "Sync Control" || itemText == "FIFO Status") {
            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
        } else if (itemText == "PLL Control") {
            for (int j = 0; j < 3; ++j) {
                if (regIndex < regNames.size()) parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex++)) << new QStandardItem());
            }
        } else {
            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex++)) << new QStandardItem());
            }
        }

        switch (i) {
            case 0:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("SDIO", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("LSB_FIRST", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox = createCheckBoxWidget("reset", Unchecked);
                layout->addWidget(checkBox);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 1:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Power down I DAC", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Power down Q DAC", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Power down data receiver", Unchecked);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("Power down auxiliary ADC", Checked);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 2:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Binary data format", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Q data first", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("MSB swap", Unchecked);
                layout->addWidget(checkBox3);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("Data Bus Width[1:0]", {"0",
                                                                                             "1",
                                                                                             "2",
                                                                                             "3"});
                layout->addWidget(comboBoxWidget4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 3:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Enable PLL lock lost", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Enable PLL locked", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Enable sync signal lost", Unchecked);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("Enable sync signal locked", Unchecked);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = createCheckBoxWidget("Enable FIFO Warning 1", Unchecked);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = createCheckBoxWidget("Enable FIFO Warning 2", Unchecked);
                layout->addWidget(checkBox6);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 4:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 1,
                    "Interrupt Enable (0-7)...",
                    "Interrupt Enable must be 0-7",
                    "0");
                layout->addWidget(widget);

                QCheckBox *checkBox2 = createCheckBoxWidget("Enable AED compare pass", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Enable AED compare fail", Unchecked);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("Enable SED compare fail", Unchecked);
                layout->addWidget(checkBox4);

                QWidget *comboBoxWidget5 = createComboBoxWidgetLable("Set to 0", {"0",
                                                                                  "1",
                                                                                  "2",
                                                                                  "3"});
                layout->addWidget(comboBoxWidget5);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 5:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-2, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Enable PLL lock lost", Undefined);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Enable PLL locked", Undefined);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Enable sync signal lost", Undefined);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("Enable sync signal locked", Undefined);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = createCheckBoxWidget("Enable FIFO Warning 1", Undefined);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = createCheckBoxWidget("Enable FIFO Warning 2", Undefined);
                layout->addWidget(checkBox6);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox11 = createCheckBoxWidget("AED compare pass", Undefined);
                layout2->addWidget(checkBox11);

                QCheckBox *checkBox12 = createCheckBoxWidget("AED compare fail", Undefined);
                layout2->addWidget(checkBox12);

                QCheckBox *checkBox13 = createCheckBoxWidget("SED compare fail", Undefined);
                layout2->addWidget(checkBox13);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 6:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("DACCLK duty correction", Unchecked);
                layout->addWidget(checkBox1);

                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("REFCLK duty correction", Unchecked);
                layout->addWidget(checkBox2);

                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("DACCLK cross-correction", Checked);
                layout->addWidget(checkBox3);

                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("REFCLK cross-correction", Checked);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 7:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-3, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("PLL enable", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("PLL manual enable", Checked);
                layout->addWidget(checkBox2);

                QWidget *widget = createLineEditWithSaveButton(parentItem->rowCount()-1, 63, 1,
                    "Manual VCO Band[5:0] (0-63)...",
                    "Manual VCO Band[5:0] must be 0-63",
                    "0");
                layout->addWidget(widget);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(parentItem->rowCount()-2, 1, parentItem->index());

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("PLL Loop Bandwidth[1:0]", {"3 - narrowest bandwidth",
                                                                                                 "2",
                                                                                                 "1",
                                                                                                 "0 - widest bandwidth"});
                layout2->addWidget(comboBoxWidget4);

                QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 31, 1,
                    "PLL Charge Pump Current[4:0](0-31)...",
                    "PLL Charge Pump Current[4:0] must be 0-31",
                    "17");
                layout2->addWidget(widget5);

                treeView->setIndexWidget(index2, container2);

                QWidget *container3 = new QWidget();
                QVBoxLayout *layout3 = new QVBoxLayout(container3);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *comboBoxWidget1 =  createComboBoxWidgetLable("N2[1:0]", {"3 - fDACCLK/fPC_CLK = 16",
                                                                                  "2 - fDACCLK/fPC_CLK = 8",
                                                                                  "1 - fDACCLK/fPC_CLK = 4",
                                                                                  "0 - fDACCLK/fPC_CLK = 2"});
                layout3->addWidget(comboBoxWidget1);

                QCheckBox *checkBox7 = createCheckBoxWidget("PLL manual enable", Checked);
                layout3->addWidget(checkBox7);

                QWidget *comboBoxWidget8 =  createComboBoxWidgetLable("N0[1:0]", {"2 - fVCO/fDACCLK = 4",
                                                                                  "0 - fVCO/fDACCLK = 1",
                                                                                  "1 - fVCO/fDACCLK = 2",
                                                                                  "3 - fVCO/fDACCLK = 4"});
                layout3->addWidget(comboBoxWidget8);

                QWidget *comboBoxWidget9 =  createComboBoxWidgetLable("N1[1:0]", {"1 - fVCO/fDACCLK = 4",
                                                                                  "0 - fVCO/fDACCLK = 2",
                                                                                  "2 - fVCO/fDACCLK = 8",
                                                                                  "3 - fVCO/fDACCLK = 16"});
                layout3->addWidget(comboBoxWidget9);

                treeView->setIndexWidget(index3, container3);

                break;
            }
            case 8:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-2, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("PLL locked", Undefined);
                layout->addWidget(checkBox1);

                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 1,
                    "VCO Control Voltage (0-15)...",
                    "VCO Control Voltage must be 0-15",
                    " ");
                layout->addWidget(widget2);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 63, 1,
                    "VCO Band Readback (0-63)...",
                    "VCO Band Readback 0-63",
                    " ");
                layout2->addWidget(widget3);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 9:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-2, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Sync enable", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Data/FIFO rate toggle", Checked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Rising edge sync", Checked);
                layout->addWidget(checkBox3);

                QString defaultText = "0";
                int valueLimit = 128;
                QString errorMsg = "Sync Averaging must be power of 2 (0-128)";
                QString placeholderText = "Sync Averaging 0-128";
                QModelIndex index4 = model->index(parentItem->rowCount()-2, 1, parentItem->index());
                QWidget *widget4 = LineOfPower(parentItem->rowCount()-1, valueLimit, placeholderText, errorMsg, defaultText);
                layout->addWidget(widget4);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 63, 1,
                    "Sync Phase Request (0-63 DACCLK cycles)...",
                    "Sync Phase Request must be 0-63 DACCLK cycles",
                    "0");
                layout2->addWidget(widget5);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 10:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-2, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Sync lost", Undefined);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Sync locked", Undefined);
                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 63.75, 0.25,
                    "Sync Phase Request (0-63.75)...",
                    "Sync Phase Request must be 0-63.75",
                    "");
                layout2->addWidget(widget3);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 11:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("LVDS FRAME level high", Undefined);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("LVDS FRAME level low", Undefined);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("LVDS DCI level high", Undefined);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("LVDS DCI level low", Undefined);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = createCheckBoxWidget("LVDS data level high", Undefined);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = createCheckBoxWidget("LVDS data level low", Undefined);
                layout->addWidget(checkBox6);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 12:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("DCI Delay[1:0]", {"0 - 350 ps",
                                                                                        "1 - 590 ps",
                                                                                        "2 - 800 ps",
                                                                                        "3 - 925 ps"});
                layout->addWidget(comboBoxWidget1);

                treeView->setIndexWidget(index1, container);


                break;
            }
            case 13:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 1,
                    "FIFO Phase Offset (0-7)...",
                    "FIFO Phase Offset must be 0-7",
                    "4");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);


                break;

            }
            case 14:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-2, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("FIFO Warning 1", Undefined);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("FIFO Warning 2", Undefined);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("FIFO soft align acknowledge", Undefined);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("FIFO soft align request", Unchecked);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                QWidget *container2 = new QWidget();
                QVBoxLayout *layout2 = new QVBoxLayout(container2);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FIFO Level (0-255)...",
                    "FIFO Level must be 0-255",
                    "");
                layout2->addWidget(widget5);

                treeView->setIndexWidget(index2, container2);

                break;
            }
            case 15:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Bypass premod", Checked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Bypass sinc−1", Checked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Bypass NCO", Checked);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("NCO gain", Unchecked);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = createCheckBoxWidget("Bypass phase compensation and dc offset", Checked);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = createCheckBoxWidget("Select sideband", Unchecked);
                layout->addWidget(checkBox6);

                QCheckBox *checkBox7 = createCheckBoxWidget("Send I data to Q data", Unchecked);
                layout->addWidget(checkBox7);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 16:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("HB1[1:0]", {"0 - input signal not modulated",
                                                                                  "1 - input signal not modulated",
                                                                                  "2 - input signal modulated by fIN1",
                                                                                  "3 - input signal modulated by fIN1"});
                layout->addWidget(comboBoxWidget1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Bypass HB1", Unchecked);
                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 17:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("HB2[5:0]", {"0 - input signal not modulated",
                                                                                  "9 - input signal not modulated",
                                                                                  "18 - input signal not modulated",
                                                                                  "27 - input signal not modulated",
                                                                                  "36 - input signal modulated by fIN2",
                                                                                  "45 - input signal modulated by fIN2",
                                                                                  "54 - input signal modulated by fIN2",
                                                                                  "63 - input signal modulated by fIN2"});
                layout->addWidget(comboBoxWidget1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Bypass HB2", Unchecked);
                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                break;

            break;
            }
            case 18:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("HB3[5:0]", {"0 - input signal not modulated",
                                                                                  "9 - input signal not modulated",
                                                                                  "18 - input signal not modulated",
                                                                                  "27 - input signal not modulated",
                                                                                  "36 - input signal modulated by fIN3",
                                                                                  "45 - input signal modulated by fIN3",
                                                                                  "54 - input signal modulated by fIN3",
                                                                                  "63 - input signal modulated by fIN3"});
                layout->addWidget(comboBoxWidget1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Bypass HB3", Unchecked);
                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 19:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Chip ID (0-255)...",
                    "Chip ID must be 0-255",
                    "8");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 20:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FTW [7:0] (0-255)...",
                    "FTW [7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 21:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FTW [15:8] (0-255)...",
                    "FTW [15:8] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 22:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FTW [23:16] (0-255)...",
                    "FTW [23:16] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;

            }
            case 23:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FTW [31:24] (0-255)...",
                    "FTW [31:24] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;

            }
            case 24:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "NCO Phase Offset [7:0] (0-255)...",
                    "NCO Phase Offset [7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 25:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "NCO Phase Offset[15:8] (0-255)...",
                    "NCO Phase Offset[15:8] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 26:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("FRAME FTW acknowledge", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("FRAME FTW request", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Update FTW acknowledge", Unchecked);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("Update FTW request", Unchecked);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 27:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I Phase Adj[7:0] (0-255)...",
                    "I Phase Adj[7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 28:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 1,
                    "I Phase Adj[9:8] (0-3)...",
                    "I Phase Adj[9:8] must be 0-3",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 29:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q Phase Adj[7:0] (0-255)...",
                    "Q Phase Adj[7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 30:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 1,
                    "I Phase Adj[9:8] (0-3)...",
                    "I Phase Adj[9:8] must be 0-3",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 31:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I DAC Offset[7:0] (0-255)...",
                    "I DAC Offset[7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 32:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I DAC Offset[15:8] (0-255)...",
                    "I DAC Offset[15:8] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 33:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q DAC Offset[7:0] (0-255)...",
                    "Q DAC Offset[7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 34:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q DAC Offset[15:8] (0-255)...",
                    "Q DAC Offset[15:8] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 35:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I DAC FS Adj[7:0] (0-255)...",
                    "I DAC FS Adj[7:0] must be 0-255",
                    "249");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 36:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-2, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("I DAC sleep", Unchecked);
                layout->addWidget(checkBox1);

                QWidget *comboBoxWidget2 = createComboBoxWidgetLable("I Aux DAC[9:8]", {"1",
                                                                                        "0",
                                                                                        "2",
                                                                                        "3"});
                layout->addWidget(comboBoxWidget2);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 37:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I Aux DAC (0-255)...",
                    "I Aux DAC must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 38:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("I aux DAC sign", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("I aux DAC current direction", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("I aux DAC sleep", Unchecked);
                layout->addWidget(checkBox3);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("I Aux DAC[9:8]", {"0",
                                                                                        "1",
                                                                                        "2",
                                                                                        "3"});
                layout->addWidget(comboBoxWidget4);

                treeView->setIndexWidget(index1, container);


                break;
            }
            case 39:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q DAC FS Adj[7:0] (0-255)...",
                    "Q DAC FS Adj[7:0] must be 0-255",
                    "249");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 40:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Q DAC sleep", Unchecked);
                layout->addWidget(checkBox1);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("Q DAC FS Adj[9:8]", {"0",
                                                                                           "1",
                                                                                           "2",
                                                                                           "3"});
                layout->addWidget(comboBoxWidget4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 41:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q Aux DAC[7:0](0-255)...",
                    "Q Aux DAC[7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 42:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Q aux DAC sign", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("I aux DAC current direction", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Q aux DAC sleep", Unchecked);
                layout->addWidget(checkBox3);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("Q Aux DAC[9:8]", {"0",
                                                                                        "1",
                                                                                        "2",
                                                                                        "3"});
                layout->addWidget(comboBoxWidget4);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 43:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 1,
                    "FS Current[2:0] (0-7)...",
                    "FS Current[2:0] must be 0-7",
                    "0");
                layout->addWidget(widget1);

                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 1,
                    "Reference Current[2:0] (0-7)...",
                    "Reference Current[2:0] must be 0-7",
                    "1");
                layout->addWidget(widget2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Capacitor value", Unchecked);
                layout->addWidget(checkBox3);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 44:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Die Temp[7:0] (0-255)...",
                    "Die Temp[7:0] must be 0-255",
                    "");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 45:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Die Temp[15:8] (0-255)...",
                    "Die Temp[15:8] must be 0-255",
                    "");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 46:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("SED compare enable", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Sample error detected", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Autoclear enable", Unchecked);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("Compare fail", Unchecked);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = createCheckBoxWidget("Compare pass", Unchecked);
                layout->addWidget(checkBox5);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 47:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value I0[7:0] (0-255)...",
                    "Compare Value I0[7:0] must be 0-255",
                    "182");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 48:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value I0[15:8] (0-255)...",
                    "Compare Value I0[15:8] must be 0-255",
                    "122");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 49:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value Q0[7:0] (0-255)...",
                    "Compare Value Q0[7:0] must be 0-255",
                    "65");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 50:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value Q0[15:8] (0-255)...",
                    "Compare Value Q0[15:8] must be 0-255",
                    "234");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 51:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value I1[7:0] (0-255)...",
                    "Compare Value I1[7:0] must be 0-255",
                    "22");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 52:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value I1[15:8] (0-255)...",
                    "Compare Value I1[15:8] must be 0-255",
                    "26");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 53:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value Q1[7:0] (0-255)...",
                    "Compare Value Q1[7:0] must be 0-255",
                    "198");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 54:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value Q1[15:8] (0-255)...",
                    "Compare Value Q1[15:8] must be 0-255",
                    "170");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 55:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Errors Detected I_BITS[7:0] (0-255)...",
                    "Errors Detected I_BITS[7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }

            case 56:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Errors Detected I_BITS[15:8] (0-255)...",
                    "Errors Detected I_BITS[15:8] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 57:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Errors Detected Q_BITS[7:0] (0-255)...",
                    "Errors Detected Q_BITS[7:0] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 58:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Errors Detected Q_BITS[15:8] (0-255)...",
                    "Errors Detected Q_BITS[15:8] must be 0-255",
                    "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
            case 59:
            {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Revision[3:0] (0-255)...",
                    "Revision[3:0] must be 0-255",
                    "15");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            }
        }
    }

    if (model) blockEditing(model);

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

    connect(toggleButton, &QPushButton::clicked, this, &AD9122Widget::on_toggle_button_clicked);
    connect(saveButton, &QPushButton::clicked, this, &AD9122Widget::on_save_button_clicked);
    connect(loadButton, &QPushButton::clicked, this, &AD9122Widget::on_load_button_clicked);

    setLayout(layout);

}
