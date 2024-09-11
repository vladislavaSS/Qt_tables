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


void MainWindow::viewTree() {
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

        if (itemText == "Event Flag") {
            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
            for (int i = 0; i < 6; i++) parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem() << new QStandardItem());

            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
        } else if (itemText == "Sync Control" || itemText == "FIFO Status") {
            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
            parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem() << new QStandardItem());
            parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem() << new QStandardItem());
            parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem() << new QStandardItem());
            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
        } else if (itemText == "PLL Status" || itemText == "Sync Status") {
            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem() << new QStandardItem());
                regIndex++;
            }
            if (regIndex < regNames.size()) {
                parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex)) << new QStandardItem());
                regIndex++;
            }
        } else if (itemText == "PLL Control") {
            for (int j = 0; j < 3; ++j) {
                if (regIndex < regNames.size()) {
                    parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem(regNames.at(regIndex++)) << new QStandardItem());
                    switch (j){
                    case 0: {
                        parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem() << new QStandardItem());
                    }
                    case 1: {
                    }
                    case 2: {
                        parentItem->appendRow(QList<QStandardItem*>() << new QStandardItem() << new QStandardItem());
                        }
                    }
                }

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

                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("SDIO", Unchecked);
                QVBoxLayout *layout = new QVBoxLayout(container);
                layout->addWidget(checkBox1);
//                treeView->setIndexWidget(index1, container);

//                parentItem->appendRow(new QStandardItem);
//                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("LSB_FIRST", Unchecked);
                layout->addWidget(checkBox2);
//                treeView->setIndexWidget(index1, container);

                //                parentItem->appendRow(new QStandardItem);
//                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
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
//                treeView->setIndexWidget(index1, checkBox1);

//                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Power down Q DAC", Unchecked);
                layout->addWidget(checkBox2);
//                treeView->setIndexWidget(index2, checkBox2);

//                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Power down data receiver", Unchecked);
                layout->addWidget(checkBox3);
//                treeView->setIndexWidget(index3, checkBox3);

//                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("Power down auxiliary ADC", Checked);
                layout->addWidget(checkBox4);
                treeView->setIndexWidget(index1, container);

                break;
            }
            case 2:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Binary data format", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Q data first", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("MSB swap", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("Data Bus Width[1:0]", {"00",
                                                                                             "01",
                                                                                             "10",
                                                                                             "11"});
                treeView->setIndexWidget(index4, comboBoxWidget4);

                break;
            }
            case 3:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Enable PLL lock lost", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Enable PLL locked", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Enable sync signal lost", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("Enable sync signal locked", Unchecked);
                treeView->setIndexWidget(index4, checkBox4);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox5 = createCheckBoxWidget("Enable FIFO Warning 1", Unchecked);
                treeView->setIndexWidget(index5, checkBox5);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index6 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox6 = createCheckBoxWidget("Enable FIFO Warning 2", Unchecked);
                treeView->setIndexWidget(index6, checkBox6);

                break;
            }
            case 4:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 1,
                    "Interrupt Enable (0-7)...",
                    "Interrupt Enable must be 0-7",
                    "0");
                treeView->setIndexWidget(index1, widget);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Enable AED compare pass", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Enable AED compare fail", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("Enable SED compare fail", Unchecked);
                treeView->setIndexWidget(index4, checkBox4);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget5 = createComboBoxWidgetLable("Set to 0", {"00",
                                                                                  "01",
                                                                                  "10",
                                                                                  "11"});
                treeView->setIndexWidget(index5, comboBoxWidget5);

                break;
            }
            case 5:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-8, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Enable PLL lock lost", Undefined);
                treeView->setIndexWidget(index1, checkBox1);

                QModelIndex index2 = model->index(parentItem->rowCount()-7, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Enable PLL locked", Undefined);
                treeView->setIndexWidget(index2, checkBox2);

                QModelIndex index3 = model->index(parentItem->rowCount()-6, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Enable sync signal lost", Undefined);
                treeView->setIndexWidget(index3, checkBox3);
                parentItem->appendRow(new QStandardItem);

                QModelIndex index4 = model->index(parentItem->rowCount()-6, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("Enable sync signal locked", Undefined);
                treeView->setIndexWidget(index4, checkBox4);

                QModelIndex index5 = model->index(parentItem->rowCount()-5, 1, parentItem->index());
                QCheckBox *checkBox5 = createCheckBoxWidget("Enable FIFO Warning 1", Undefined);
                treeView->setIndexWidget(index5, checkBox5);

                QModelIndex index6 = model->index(parentItem->rowCount()-4, 1, parentItem->index());
                QCheckBox *checkBox6 = createCheckBoxWidget("Enable FIFO Warning 2", Undefined);
                treeView->setIndexWidget(index6, checkBox6);

                QModelIndex index11 = model->index(parentItem->rowCount()-2, 1, parentItem->index());
                QCheckBox *checkBox11 = createCheckBoxWidget("AED compare pass", Undefined);
                treeView->setIndexWidget(index11, checkBox11);

                QModelIndex index12 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox12 = createCheckBoxWidget("AED compare fail", Undefined);
                treeView->setIndexWidget(index12, checkBox12);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index13 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox13 = createCheckBoxWidget("SED compare fail", Undefined);
                treeView->setIndexWidget(index13, checkBox13);

                break;
            }
            case 6:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("DACCLK duty correction", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("REFCLK duty correction", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("DACCLK cross-correction", Checked);
                treeView->setIndexWidget(index3, checkBox3);
                parentItem->appendRow(new QStandardItem);

                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("REFCLK cross-correction", Checked);
                treeView->setIndexWidget(index4, checkBox4);

                break;
            }
            case 7:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-7, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("PLL enable", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                QModelIndex index2 = model->index(parentItem->rowCount()-6, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("PLL manual enable", Checked);
                treeView->setIndexWidget(index2, checkBox2);

                QModelIndex index3 = model->index(parentItem->rowCount()-5, 1, parentItem->index());
                QWidget *widget = createLineEditWithSaveButton(parentItem->rowCount()-1, 63, 1,
                    "Manual VCO Band[5:0] (0-63)...",
                    "Manual VCO Band[5:0] must be 0-63",
                    "0");
                treeView->setIndexWidget(index3, widget);

                QModelIndex index4 = model->index(parentItem->rowCount()-4, 1, parentItem->index());
                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("PLL Loop Bandwidth[1:0]", {"11 - narrowest bandwidth",
                                                                                                 "10",
                                                                                                 "01",
                                                                                                 "00 - widest bandwidth"});
                treeView->setIndexWidget(index4, comboBoxWidget4);

                QModelIndex index5 = model->index(parentItem->rowCount()-3, 1, parentItem->index());
                QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 31, 1,
                    "PLL Charge Pump Current[4:0](0-31)...",
                    "PLL Charge Pump Current[4:0] must be 0-31",
                    "17");
                treeView->setIndexWidget(index5, widget5);

                QModelIndex index6 = model->index(parentItem->rowCount()-2, 1, parentItem->index());
                QWidget *comboBoxWidget1 =  createComboBoxWidgetLable("N2[1:0]", {"11 - fDACCLK/fPC_CLK = 16",
                                                                                  "10 - fDACCLK/fPC_CLK = 8",
                                                                                  "01 - fDACCLK/fPC_CLK = 4",
                                                                                  "00 - fDACCLK/fPC_CLK = 2"});
                treeView->setIndexWidget(index6, comboBoxWidget1);

                QModelIndex index7 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox7 = createCheckBoxWidget("PLL manual enable", Checked);
                treeView->setIndexWidget(index7, checkBox7);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index8 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget8 =  createComboBoxWidgetLable("N0[1:0]", {"10 - fVCO/fDACCLK = 4",
                                                                                  "00 - fVCO/fDACCLK = 1",
                                                                                  "01 - fVCO/fDACCLK = 2",
                                                                                  "11 - fVCO/fDACCLK = 4"});
                treeView->setIndexWidget(index8, comboBoxWidget8);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index9 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget9 =  createComboBoxWidgetLable("N1[1:0]", {"01 - fVCO/fDACCLK = 4",
                                                                                  "00 - fVCO/fDACCLK = 2",
                                                                                  "10 - fVCO/fDACCLK = 8",
                                                                                  "11 - fVCO/fDACCLK = 16"});
                treeView->setIndexWidget(index9, comboBoxWidget9);

                break;
            }
            case 8:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-3, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("PLL locked", Undefined);
                treeView->setIndexWidget(index1, checkBox1);

                QModelIndex index2 = model->index(parentItem->rowCount()-2, 1, parentItem->index());
                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 1,
                    "VCO Control Voltage (0-15)...",
                    "VCO Control Voltage must be 0-15",
                    " ");
                treeView->setIndexWidget(index2, widget2);

                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 63, 1,
                    "VCO Band Readback (0-63)...",
                    "VCO Band Readback 0-63",
                    " ");
                treeView->setIndexWidget(index3, widget3);

                break;
            }
            case 9:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-5, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Sync enable", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                QModelIndex index2 = model->index(parentItem->rowCount()-4, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Data/FIFO rate toggle", Checked);
                treeView->setIndexWidget(index2, checkBox2);

                QModelIndex index3 = model->index(parentItem->rowCount()-3, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Rising edge sync", Checked);
                treeView->setIndexWidget(index3, checkBox3);

                QString defaultText = "0";
                int valueLimit = 128;
                QString errorMsg = "Sync Averaging must be power of 2 (0-128)";
                QString placeholderText = "Sync Averaging 0-128";
                QModelIndex index4 = model->index(parentItem->rowCount()-2, 1, parentItem->index());
                QWidget *widget4 = LineOfPower(parentItem->rowCount()-1, valueLimit, placeholderText, errorMsg, defaultText);
                treeView->setIndexWidget(index4, widget4);

                QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 63, 1,
                    "Sync Phase Request (0-63 DACCLK cycles)...",
                    "Sync Phase Request must be 0-63 DACCLK cycles",
                    "0");
                treeView->setIndexWidget(index5, widget5);

                break;
            }
            case 10:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-3, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Sync lost", Undefined);
                treeView->setIndexWidget(index1, checkBox1);

                QModelIndex index2 = model->index(parentItem->rowCount()-2, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Sync locked", Undefined);
                treeView->setIndexWidget(index2, checkBox2);

                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 63.75, 0.25,
                    "Sync Phase Request (0-63.75)...",
                    "Sync Phase Request must be 0-63.75",
                    "");
                treeView->setIndexWidget(index3, widget3);

                break;
            }
            case 11:
            {
            QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
            QCheckBox *checkBox1 = createCheckBoxWidget("LVDS FRAME level high", Undefined);
            treeView->setIndexWidget(index1, checkBox1);

            parentItem->appendRow(new QStandardItem);
            QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
            QCheckBox *checkBox2 = createCheckBoxWidget("LVDS FRAME level low", Undefined);
            treeView->setIndexWidget(index2, checkBox2);

            parentItem->appendRow(new QStandardItem);
            QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
            QCheckBox *checkBox3 = createCheckBoxWidget("LVDS DCI level high", Undefined);
            treeView->setIndexWidget(index3, checkBox3);

            parentItem->appendRow(new QStandardItem);
            QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
            QCheckBox *checkBox4 = createCheckBoxWidget("LVDS DCI level low", Undefined);
            treeView->setIndexWidget(index4, checkBox4);

            parentItem->appendRow(new QStandardItem);
            QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
            QCheckBox *checkBox5 = createCheckBoxWidget("LVDS data level high", Undefined);
            treeView->setIndexWidget(index5, checkBox5);

            parentItem->appendRow(new QStandardItem);
            QModelIndex index6 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
            QCheckBox *checkBox6 = createCheckBoxWidget("LVDS data level low", Undefined);
            treeView->setIndexWidget(index6, checkBox6);

            break;
            }
            case 12:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("DCI Delay[1:0]", {"00 - 350 ps",
                                                                                        "01 - 590 ps",
                                                                                        "10 - 800 ps",
                                                                                        "11 - 925 ps"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                break;
            }
            case 13:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 1,
                    "FIFO Phase Offset (0-7)...",
                    "FIFO Phase Offset must be 0-7",
                    "4");
                treeView->setIndexWidget(index1, widget1);


                break;

            }
            case 14:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-5, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("FIFO Warning 1", Undefined);
                treeView->setIndexWidget(index1, checkBox1);

                QModelIndex index2 = model->index(parentItem->rowCount()-4, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("FIFO Warning 2", Undefined);
                treeView->setIndexWidget(index2, checkBox2);

                QModelIndex index3 = model->index(parentItem->rowCount()-3, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("FIFO soft align acknowledge", Undefined);
                treeView->setIndexWidget(index3, checkBox3);

                QModelIndex index4 = model->index(parentItem->rowCount()-2, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("FIFO soft align request", Unchecked);
                treeView->setIndexWidget(index4, checkBox4);

                QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FIFO Level (0-255)...",
                    "FIFO Level must be 0-255",
                    "");
                treeView->setIndexWidget(index5, widget5);

                break;
            }
            case 15:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Bypass premod", Checked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Bypass sinc−1", Checked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Bypass NCO", Checked);
                treeView->setIndexWidget(index3, checkBox3);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("NCO gain", Unchecked);
                treeView->setIndexWidget(index4, checkBox4);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox5 = createCheckBoxWidget("Bypass phase compensation and dc offset", Checked);
                treeView->setIndexWidget(index5, checkBox5);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index6 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox6 = createCheckBoxWidget("Select sideband", Unchecked);
                treeView->setIndexWidget(index6, checkBox6);


                parentItem->appendRow(new QStandardItem);
                QModelIndex index7 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox7 = createCheckBoxWidget("Send I data to Q data", Unchecked);
                treeView->setIndexWidget(index7, checkBox7);
                break;
            }
            case 16:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("HB1[1:0]", {"00 - input signal not modulated",
                                                                                  "01 - input signal not modulated",
                                                                                  "10 - input signal modulated by fIN1",
                                                                                  "11 - input signal modulated by fIN1"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Bypass HB1", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                break;
            }
            case 17:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("HB2[5:0]", {"000000 - input signal not modulated",
                                                                                  "001001 - input signal not modulated",
                                                                                  "010010 - input signal not modulated",
                                                                                  "011011 - input signal not modulated",
                                                                                  "100100 - input signal modulated by fIN2",
                                                                                  "101101 - input signal modulated by fIN2",
                                                                                  "110110 - input signal modulated by fIN2",
                                                                                  "111111 - input signal modulated by fIN2"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Bypass HB2", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                break;

            break;
            }
            case 18:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("HB3[5:0]", {"000000 - input signal not modulated",
                                                                                  "001001 - input signal not modulated",
                                                                                  "010010 - input signal not modulated",
                                                                                  "011011 - input signal not modulated",
                                                                                  "100100 - input signal modulated by fIN3",
                                                                                  "101101 - input signal modulated by fIN3",
                                                                                  "110110 - input signal modulated by fIN3",
                                                                                  "111111 - input signal modulated by fIN3"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Bypass HB3", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                break;
            }
            case 19:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Chip ID (0-255)...",
                    "Chip ID must be 0-255",
                    "8");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 20:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FTW [7:0] (0-255)...",
                    "FTW [7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 21:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FTW [15:8] (0-255)...",
                    "FTW [15:8] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 22:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FTW [23:16] (0-255)...",
                    "FTW [23:16] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;

            }
            case 23:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "FTW [31:24] (0-255)...",
                    "FTW [31:24] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;

            }
            case 24:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "NCO Phase Offset [7:0] (0-255)...",
                    "NCO Phase Offset [7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 25:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "NCO Phase Offset[15:8] (0-255)...",
                    "NCO Phase Offset[15:8] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 26:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("FRAME FTW acknowledge", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("FRAME FTW request", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Update FTW acknowledge", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("Update FTW request", Unchecked);
                treeView->setIndexWidget(index4, checkBox4);

                break;
            }
            case 27:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I Phase Adj[7:0] (0-255)...",
                    "I Phase Adj[7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 28:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 1,
                    "I Phase Adj[9:8] (0-3)...",
                    "I Phase Adj[9:8] must be 0-3",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 29:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q Phase Adj[7:0] (0-255)...",
                    "Q Phase Adj[7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 30:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 1,
                    "I Phase Adj[9:8] (0-3)...",
                    "I Phase Adj[9:8] must be 0-3",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 31:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I DAC Offset[7:0] (0-255)...",
                    "I DAC Offset[7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 32:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I DAC Offset[15:8] (0-255)...",
                    "I DAC Offset[15:8] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 33:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q DAC Offset[7:0] (0-255)...",
                    "Q DAC Offset[7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 34:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q DAC Offset[15:8] (0-255)...",
                    "Q DAC Offset[15:8] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 35:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I DAC FS Adj[7:0] (0-255)...",
                    "I DAC FS Adj[7:0] must be 0-255",
                    "249");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 36:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("I DAC sleep", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget2 = createComboBoxWidgetLable("I Aux DAC[9:8]", {"01",
                                                                                        "00",
                                                                                        "10",
                                                                                        "11"});
                treeView->setIndexWidget(index2, comboBoxWidget2);

                break;
            }
            case 37:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "I Aux DAC (0-255)...",
                    "I Aux DAC must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 38:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("I aux DAC sign", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("I aux DAC current direction", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("I aux DAC sleep", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("I Aux DAC[9:8]", {"00",
                                                                                        "01",
                                                                                        "10",
                                                                                        "11"});
                treeView->setIndexWidget(index4, comboBoxWidget4);


                break;
            }
            case 39:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q DAC FS Adj[7:0] (0-255)...",
                    "Q DAC FS Adj[7:0] must be 0-255",
                    "249");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 40:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Q DAC sleep", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("Q DAC FS Adj[9:8]", {"00",
                                                                                           "01",
                                                                                           "10",
                                                                                           "11"});
                treeView->setIndexWidget(index4, comboBoxWidget4);
                break;
            }
            case 41:
            {

                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Q Aux DAC[7:0](0-255)...",
                    "Q Aux DAC[7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 42:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Q aux DAC sign", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("I aux DAC current direction", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Q aux DAC sleep", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("Q Aux DAC[9:8]", {"00",
                                                                                        "01",
                                                                                        "10",
                                                                                        "11"});
                treeView->setIndexWidget(index4, comboBoxWidget4);

                break;
            }
            case 43:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 1,
                    "FS Current[2:0] (0-7)...",
                    "FS Current[2:0] must be 0-7",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 1,
                    "Reference Current[2:0] (0-7)...",
                    "Reference Current[2:0] must be 0-7",
                    "1");
                treeView->setIndexWidget(index2, widget2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Capacitor value", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                break;
            }
            case 44:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Die Temp[7:0] (0-255)...",
                    "Die Temp[7:0] must be 0-255",
                    "");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 45:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Die Temp[15:8] (0-255)...",
                    "Die Temp[15:8] must be 0-255",
                    "");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 46:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("SED compare enable", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Sample error detected", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Autoclear enable", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("Compare fail", Unchecked);
                treeView->setIndexWidget(index4, checkBox4);

                parentItem->appendRow(new QStandardItem);
                QModelIndex index5 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QCheckBox *checkBox5 = createCheckBoxWidget("Compare pass", Unchecked);
                treeView->setIndexWidget(index5, checkBox5);

                break;
            }
            case 47:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value I0[7:0] (0-255)...",
                    "Compare Value I0[7:0] must be 0-255",
                    "182");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 48:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value I0[15:8] (0-255)...",
                    "Compare Value I0[15:8] must be 0-255",
                    "122");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 49:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value Q0[7:0] (0-255)...",
                    "Compare Value Q0[7:0] must be 0-255",
                    "65");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 50:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value Q0[15:8] (0-255)...",
                    "Compare Value Q0[15:8] must be 0-255",
                    "234");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 51:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value I1[7:0] (0-255)...",
                    "Compare Value I1[7:0] must be 0-255",
                    "22");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 52:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value I1[15:8] (0-255)...",
                    "Compare Value I1[15:8] must be 0-255",
                    "26");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 53:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value Q1[7:0] (0-255)...",
                    "Compare Value Q1[7:0] must be 0-255",
                    "198");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 54:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Compare Value Q1[15:8] (0-255)...",
                    "Compare Value Q1[15:8] must be 0-255",
                    "170");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 55:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Errors Detected I_BITS[7:0] (0-255)...",
                    "Errors Detected I_BITS[7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }

            case 56:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Errors Detected I_BITS[15:8] (0-255)...",
                    "Errors Detected I_BITS[15:8] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 57:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Errors Detected Q_BITS[7:0] (0-255)...",
                    "Errors Detected Q_BITS[7:0] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 58:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Errors Detected Q_BITS[15:8] (0-255)...",
                    "Errors Detected Q_BITS[15:8] must be 0-255",
                    "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
            case 59:
            {
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "Revision[3:0] (0-255)...",
                    "Revision[3:0] must be 0-255",
                    "15");
                treeView->setIndexWidget(index1, widget1);

                break;
            }
        }
    }

    if (model) blockEditing(model);

    layout->addWidget(treeView);

    toggleButton = new QPushButton("Expand All");
    layout->addWidget(toggleButton);

    saveButton = new QPushButton("Save");
    layout->addWidget(saveButton);


    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::on_toggle_button_clicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::on_save_button_clicked);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

}













