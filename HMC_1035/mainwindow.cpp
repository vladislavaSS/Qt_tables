#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), treeView(new QTreeView(this)), model(new QStandardItemModel(this)), treeExpanded(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    viewTree();
    treeView -> setColumnWidth(0, 250);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::viewTree() {
    QVBoxLayout *layout = new QVBoxLayout();

    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Register", "Bits"});

    treeView->setModel(model);

    int regIndex1 = 0;
    int regIndex2 = 0;


    for (int i = 0; i < itemNames.size(); ++i) {
    QString itemText = itemNames.at(i);
    QStandardItem *parentItem = new QStandardItem(itemText);
    model->appendRow(parentItem);

    if (itemText == "PLL") {
        for (int j = 0; j < childName1.size(); j++) {
            QStandardItem *childItem = new QStandardItem(childName1.at(regIndex1));
            parentItem->appendRow(QList<QStandardItem*>() << childItem << new QStandardItem());
            if (regIndex1 < childName1.size()) {
                QStandardItem *grandchildItem = new QStandardItem();
                childItem->appendRow(QList<QStandardItem*>() << grandchildItem << new QStandardItem());
                regIndex1++;
            }
            switch (regIndex1) {
                case 1: {
//                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
//                    QWidget *widget = createLineEditWithSaveButton(parentItem->rowCount()-1, 684453, 684453,
//                        "chip_ID [23:0] Read Only...",
//                        "Read Only",
//                        "684453");
//                    treeView->setIndexWidget(index1, widget);

                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget1 = LineEdit("chip_ID [23:0] (RO register)", "684453");
                    treeView->setIndexWidget(index1, widget1);

                    break;
                } case 2: {
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1048575, 0,
                        "Read Address [4:0]...",
                        "Read Address must be 0-1048575",
                        "");
                    treeView->setIndexWidget(index1, widget1);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox2 = createCheckBoxWidget("Soft Reset", Undefined);
                    treeView->setIndexWidget(index2, checkBox2);

                    childItem->appendRow(new QStandardItem);
/**/                    QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1048575, 0,
                        "Not Defined [23:6]...",
                        "Not Defined must be 0-1048575",
                        "");
                    treeView->setIndexWidget(index3, widget3);

                    break;
            } case 3: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                "Reserved",
                "Reserved",
                "0");
                treeView->setIndexWidget(index1, widget1);

                for (int k = 0; k < 10; k++) {
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index1 = model->index(childItem->rowCount()-2, 1, childItem->index());
/**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index1, widget1);
            }
                break;
            } case 4: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1389561, 29,
                "rdiv [13:0] (29-1389561)...",
                "rdiv [13:0] must be 29-1389561",
                "1");
                treeView->setIndexWidget(index1, widget1);

                break;
            } case 5: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 524244, 365,
                "intg [18:0] (365-524244)...",
                "intg [18:0] must be 365-524244",
                "605");
                treeView->setIndexWidget(index1, widget1);

                break;
            } case 6: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16777215, 13,
                "frac [23:0] (13-16777215)...",
                "frac [23:0] must be 13-16777215",
                "0");
                treeView->setIndexWidget(index1, widget1);

                break;
            } case 7: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "VCO Subsystem_ID [2:0] (0-0)...",
                "VCO Subsystem_ID [2:0] must be 0-0",
                "0");
                treeView->setIndexWidget(index1, widget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "VCO Subsystem register address [6:3] (0-0)...",
                "VCO Subsystem register address [6:3] must be 0-0",
                "0");
                treeView->setIndexWidget(index2, widget2);

                childItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "VCO Subsystem data [15:7] (0-0)...",
                "VCO Subsystem data [15:7] must be 0-0",
                "0");
                treeView->setIndexWidget(index3, widget3);

                break;
            } case 8: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("seed [1:0]", {"00 - 0 seed",
                                                                                    "01 - lsb seed",
                                                                                    "02 - B29D08h seed",
                                                                                    "03 - 50F1CDh seed"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index11 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                QWidget *widget11 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "2");
                treeView->setIndexWidget(index11, widget11);

                childItem->appendRow(new QStandardItem);
                QModelIndex index12 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                QWidget *widget12 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "4");
                treeView->setIndexWidget(index12, widget12);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("frac_bypass", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                for (int k = 0; k < 3; k++) {
                    if (k == 2) {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved5",
                        "0");
                        treeView->setIndexWidget(index1, widget1);
                    } else {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        treeView->setIndexWidget(index1, widget1);
                    }
                }

                childItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("SD Enable", Checked);
                treeView->setIndexWidget(index3, checkBox3);

                for (int k = 0; k < 8; k++) {
                    if (k == 6) {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        treeView->setIndexWidget(index1, widget1);
                    } else {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "0");
                        treeView->setIndexWidget(index1, widget1);
                    }
                }

                break;
            } case 9: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("lkd_wincnt_max [2:0]", {"default: 93",
                                                                                              "0: 5",
                                                                                              "1: 32",
                                                                                              "2: 96",
                                                                                              "3: 256",
                                                                                              "4: 512",
                                                                                              "5: 2048",
                                                                                              "6: 8192",
                                                                                              "7: 65535"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("Enable Internal Lock Detect", Checked);
                treeView->setIndexWidget(index2, checkBox2);

                childItem->appendRow(new QStandardItem);
                QModelIndex index6 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                "Reserved",
                "Reserved",
                "0");
                treeView->setIndexWidget(index6, widget6);

                childItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Lock Detect Window type", Checked);
                treeView->setIndexWidget(index3, checkBox3);

                childItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("LD Digital Window duration [9:7]", {"2: 2 cycles",
                                                                                                          "0: 1/2 cycle",
                                                                                                          "1: 1 cycle",
                                                                                                          "3: 4 cycles",
                                                                                                          "4: 8 cycles",
                                                                                                          "5: 16 cycles",
                                                                                                          "6: 32 cycles",
                                                                                                          "7: 64 cycles"});
                treeView->setIndexWidget(index4, comboBoxWidget4);

                childItem->appendRow(new QStandardItem);
                QModelIndex index5 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget5 = createComboBoxWidgetLable("LD Digital Timer Frequency Control [11:10]", {"00 - fastest",
                                                                                                                    "01",
                                                                                                                    "10",
                                                                                                                    "11 - slowest"});
                treeView->setIndexWidget(index5, comboBoxWidget5);

                for (int k = 0; k < 2; k++) {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "0");
                        treeView->setIndexWidget(index1, widget1);
                    }
                break;
            } case 10: {
                for (int k = 0; k < 5; k++) {
                    if (k == 0) {
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
    /**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        treeView->setIndexWidget(index1, widget1);
                    } else {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        treeView->setIndexWidget(index1, widget1);
                    }
                }

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("gpo_pad_en", Checked);
                treeView->setIndexWidget(index2, checkBox2);

                for (int k = 0; k < 3; k++) {
                    if (k == 2) {
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "0");
                        treeView->setIndexWidget(index1, widget1);
                    } else {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        treeView->setIndexWidget(index1, widget1);
                    }
                }

                childItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/            QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Prescaler Clock enable",
                "Reserved",
                "1");
                treeView->setIndexWidget(index3, widget3);

                childItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/            QWidget *widget4 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "VCO Buffer and Prescaler Bias Enable",
                "Reserved",
                "1");
                treeView->setIndexWidget(index4, widget4);

                for (int k = 0; k < 9; k++) {
                    if (k == 2 || k == 1) {
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "17");
                        treeView->setIndexWidget(index1, widget1);
                    } else if (k == 0 || k == 7 || k == 8){
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        treeView->setIndexWidget(index1, widget1);
                    } else {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "0");
                        treeView->setIndexWidget(index1, widget1);
                    }
                }
                break;
            } case 11: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2540, 0,
                "CP DN Gain (0-2540 µA)...",
                "CP DN Gain must be 0-2540 µA",
/**/      "4109");
                treeView->setIndexWidget(index1, widget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2540, 0,
                "CP UP Gain (0-2540 µA)...",
                "CP UP Gain must be 0-2540 µA",
/**/      "4109");
                treeView->setIndexWidget(index2, widget2);

                childItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 635, 0,
                "Offset Magnitude (0-635 µA)...",
                "Offset Magnitude must be 0-635 µA",
                "0");
                treeView->setIndexWidget(index3, widget3);

                childItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("Offset UP enable", Unchecked);
                treeView->setIndexWidget(index4, checkBox4);

                childItem->appendRow(new QStandardItem);
                QModelIndex index5 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox5 = createCheckBoxWidget("Offset DN enable", Checked);
                treeView->setIndexWidget(index5, checkBox5);

                childItem->appendRow(new QStandardItem);
                QModelIndex index6 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/            QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "1");
                 treeView->setIndexWidget(index6, widget6);

                break;
            } case 12: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("Vtune Resolution", {"5: 64",
                                                                                          "0: 1",
                                                                                          "1: 2",
                                                                                          "2: 4",
                                                                                          "3: 8",
                                                                                          "4: 32",
                                                                                          "6: 128 Program this value",
                                                                                          "7: 256"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                for (int k = 0; k < 3; k++) {
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index1, widget1);
                }

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/            QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Bypass VCO Tuning",
                "error",
                "0");
                treeView->setIndexWidget(index2, widget2);

                childItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("No VSPI Trigger", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                childItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("FSM/VSPI Clock Select", {"1: Input Crystal Reference/4",
                                                                                               "0: Input Crystal Reference",
                                                                                               "2: Input Crystal Reference/16",
                                                                                               "3: Input Crystal Reference/32"});
                treeView->setIndexWidget(index4, comboBoxWidget4);

                for (int k = 0; k < 2; k++) {
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index1, widget1);
                }

                break;
            } case 13: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 273, 0,
                "PD_del_sel (0-273)...",
                "PD_del_sel must be 0-273",
                "1");
                treeView->setIndexWidget(index1, widget1);

                for (int k = 0; k < 2; k++) {
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index1, widget1);
                }

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
                "PD_up_en (0-16)...",
                "PD_up_en must be 0-16",
                "1");
                treeView->setIndexWidget(index2, widget2);

                childItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
                "PD_dn_en (0-16)...",
                "PD_dn_en must be 0-16",
                "1");
                treeView->setIndexWidget(index3, widget3);

                childItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("CSP Mode", {"0 - Disabled",
                                                                                  "1 - 5.4ns",
                                                                                  "2 - 14.4ns",
                                                                                  "3 - 24.1ns"});
                treeView->setIndexWidget(index4, comboBoxWidget4);

                childItem->appendRow(new QStandardItem);
                QModelIndex index5 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox5 = createCheckBoxWidget("Force CP UP", Unchecked);
                treeView->setIndexWidget(index5, checkBox5);

                childItem->appendRow(new QStandardItem);
                QModelIndex index6 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox6 = createCheckBoxWidget("Force CP DN", Unchecked);
                treeView->setIndexWidget(index6, checkBox6);

                childItem->appendRow(new QStandardItem);
                QModelIndex index7 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                QWidget *widget7 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reservedl",
                "Reserved",
                "0");
                treeView->setIndexWidget(index7, widget7);

                childItem->appendRow(new QStandardItem);
                QModelIndex index8 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                QWidget *widget8 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0");
                treeView->setIndexWidget(index8, widget8);

                for (int k = 0; k < 2; k++) {
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index9 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget9 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                    "Reserved",
                    "Reserved",
                    "3");
                    treeView->setIndexWidget(index9, widget9);
                }

                childItem->appendRow(new QStandardItem);
                QModelIndex index9 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget9 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                "Reserved",
                "Reserved",
                "1");
                treeView->setIndexWidget(index9, widget9);

                for (int k = 0; k < 2; k++) {
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index9 = model->index(childItem->rowCount()-1, 1, childItem->index());
/**/                    QWidget *widget9 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index9, widget9);
                }

                break;
            } case 14: {

                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("CSP Mode", {"0 - Disabled",
                                                                                  "1 - Disabled",
                                                                                  "2 - 16383d (3FFFh)"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                break;
            } case 15: {

                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("gpo_select", {"26 - 29 Not Used",
                                                                                    "0 - Data from Reg0F[5]",
                                                                                    "1 - Lock Detect Output",
                                                                                    "2 - Lock Detect Trigger",
                                                                                    "3 - Lock Detect Window Output",
                                                                                    "4 - Ring Osc Test",
                                                                                    "5 - Pullup Hard from CSP",
                                                                                    "6 - PullDN hard from CSP",
                                                                                    "7 - Reserved",
                                                                                    "8 - Reference Buffer Output",
                                                                                    "9 - Ref Divider Output",
                                                                                    "10 - VCO divider Output",
                                                                                    "11 - Modulator Clock from VCO divider",
                                                                                    "12 - Auxiliary Clock",
                                                                                    "13 - Aux SPI Clock",
                                                                                    "14 - Aux SPI Enable",
                                                                                    "15 - Aux SPI Data Out",
                                                                                    "16 - PD DN",
                                                                                    "17 - PD UP",
                                                                                    "18 - SD3 Clock Delay",
                                                                                    "19 - SD3 Core Clock",
                                                                                    "20 - AutoStrobe Integer Write",
                                                                                    "21 - Autostrobe Frac Write",
                                                                                    "22 - Autostrobe Aux SPI",
                                                                                    "23 - SPI Latch Enable",
                                                                                    "24 - VCO Divider Sync Reset",
                                                                                    "25 - Seed Load Strobe",
                                                                                    "30 - SPI Output Buffer En",
                                                                                    "31 - Soft RSTB"});
                treeView->setIndexWidget(index1, comboBoxWidget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("GPO Test Data", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                break;
            } case 16: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox1 = createCheckBoxWidget("Prevent Automux SDO", Unchecked);
                treeView->setIndexWidget(index1, checkBox1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox2 = createCheckBoxWidget("LDO Driver Always On", Unchecked);
                treeView->setIndexWidget(index2, checkBox2);

                childItem->appendRow(new QStandardItem);
                QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox3 = createCheckBoxWidget("Disable PFET", Unchecked);
                treeView->setIndexWidget(index3, checkBox3);

                childItem->appendRow(new QStandardItem);
                QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QCheckBox *checkBox4 = createCheckBoxWidget("Disable NFET", Unchecked);
                treeView->setIndexWidget(index4, checkBox4);

                break;
            } case 17: {

                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
//                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 256, 0,
//                "VCO Switch Setting 0 = highest frequency, 255 = lowest frequency",
//                "VCO Switch Setting read only register",
///**/                "50");

/**/                QWidget *widget1 = LineEdit("VCO Switch Setting (RO register)", "50");
                treeView->setIndexWidget(index1, widget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
//                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
//                "AutoCal Busy (0-16)",
//                "AutoCal Busy read only register",
//                "0");
                QWidget *widget2 = LineEdit("AutoCal Busy (RO register)", "0");
                treeView->setIndexWidget(index2, widget2);

                break;
            } case 18: {

                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget1 = LineEdit("SAR Error Mag Counts (RO register)", "2<sup>19</sup>-1");
                treeView->setIndexWidget(index1, widget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget2 = LineEdit("SAR Error Sign (RO register)", "0");
                treeView->setIndexWidget(index2, widget2);

                break;
            } case 19: {

                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget1 = LineEdit("GPO (RO register)", "0");
                treeView->setIndexWidget(index1, widget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget2 = LineEdit("Lock Detect (RO register)", "0");
                treeView->setIndexWidget(index2, widget2);

                break;
            } case 20: {
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget1 = LineEdit("Reserved (RO register)", "288149");
                treeView->setIndexWidget(index1, widget1);

                childItem->appendRow(new QStandardItem);
                QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                QWidget *widget2 = LineEdit("Reserved (RO register)", "0");
                treeView->setIndexWidget(index2, widget2);
            }

            }
        }
    }

    if (itemText == "VCO Subsystem") {
        for (int j = 0; j < childName2.size(); j++) {
            QStandardItem *childItem = new QStandardItem(childName2.at(regIndex2));
            parentItem->appendRow(QList<QStandardItem*>() << childItem << new QStandardItem());
            if (regIndex2 < childName2.size()) {
                QStandardItem *grandchildItem = new QStandardItem();
                childItem->appendRow(QList<QStandardItem*>() << grandchildItem << new QStandardItem());
                regIndex2++;
            }

            switch (regIndex2) {
                case 1: {
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
                    "Cal [0] (0-16)",
                    "Cal [0] ",
                    "0");
                    treeView->setIndexWidget(index1, widget1);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 22, 0,
                    "CAPS [8:1] (0 - max frequency, 22 - min frequency.)",
                    "CAPS [8:1] ",
                    "0");
                    treeView->setIndexWidget(index2, widget2);



                    break;
                } case 2: {

                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16777215, 0,
                    "RF Divide ratio [5:0] (0 - >62) ...",
                    "RF Divide ratio [5:0] must be 0 - >62",
                    "1");
                    treeView->setIndexWidget(index1, widget1);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [7:6] ...",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index2, widget2);

                    QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
                    "Don’t Care [8] (0-16) ...",
                    "Don’t Care [8] must be 0-16",
                    "0");
                    treeView->setIndexWidget(index3, widget3);

                    break;
                } case 3: {

                    childItem->appendRow(new QStandardItem);
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox3 = createCheckBoxWidget("Master Enable VCO Subsystem [0]", Checked);
                    treeView->setIndexWidget(index3, checkBox3);

                    childItem->appendRow(new QStandardItem);
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox4 = createCheckBoxWidget("VCO Enable [1]", Checked);
                    treeView->setIndexWidget(index4, checkBox4);

                    childItem->appendRow(new QStandardItem);
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index5 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox5 = createCheckBoxWidget("PLL Buffer Enable [2]", Checked);
                    treeView->setIndexWidget(index5, checkBox5);

                    childItem->appendRow(new QStandardItem);
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index6 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox6 = createCheckBoxWidget("IO Master Enable [3]", Checked);
                    treeView->setIndexWidget(index6, checkBox6);

                    childItem->appendRow(new QStandardItem);
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index7 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox7 = createCheckBoxWidget("Spare [4]", Checked);
                    treeView->setIndexWidget(index7, checkBox7);

                    childItem->appendRow(new QStandardItem);
                    childItem->appendRow(new QStandardItem);
                    QModelIndex index8 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox8 = createCheckBoxWidget("Output Stage Enable [5]", Checked);
                    treeView->setIndexWidget(index8, checkBox8);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index10 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget10 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved...",
                    "Reserved",
                    "17");
                    treeView->setIndexWidget(index10, widget10);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index9 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox9 = createCheckBoxWidget("don’t care [8]", Checked);
                    treeView->setIndexWidget(index9, checkBox9);

                    break;
                } case 4: {

                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *comboBoxWidget1 = createComboBoxWidgetLable("Power- Performance Priroirty", {"01 - Not supported",
                                                                                                          "00 - Not supported",
                                                                                                          "01 - Power Priority",
                                                                                                          "11 - Performance Priority"});
                    treeView->setIndexWidget(index1, comboBoxWidget1);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox2 = createCheckBoxWidget("RF_P output enable [2]", Unchecked);
                    treeView->setIndexWidget(index2, checkBox2);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox3 = createCheckBoxWidget("RF_N output enable [3]", Unchecked);
                    treeView->setIndexWidget(index3, checkBox3);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox4 = createCheckBoxWidget("Internal Termination Enable [4]", Checked);
                    treeView->setIndexWidget(index4, checkBox4);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index5 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QCheckBox *checkBox5 = createCheckBoxWidget("Increase Internal Output Resistance [5]", Unchecked);
                    treeView->setIndexWidget(index5, checkBox5);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index6 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved...",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index6, widget6);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index7 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *comboBoxWidget7 = createComboBoxWidgetLable("Mute Mode [8:7]", {"01 - During VCO Calibration",
                                                                                             "00 - Mute enabled when divide ratio",
                                                                                             "01 - During VCO Calibration or when Lock Detect/GPO output is off",
                                                                                             "11 - Mute always On"});
                    treeView->setIndexWidget(index7, comboBoxWidget7);

                    break;

                } case 5: {

                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [0] ...",
                    "Reserved",
                    "1");
                    treeView->setIndexWidget(index1, widget1);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index2 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [1] ...",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index2, widget2);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [2] ...",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index3, widget3);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index4 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget4 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [4:3] ...",
                    "Reserved",
                    "1");
                    treeView->setIndexWidget(index4, widget4);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index5 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2, 2,
                    "Reserved [6:5] ...",
                    "Reserved",
                    "2");
                    treeView->setIndexWidget(index5, widget5);

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index6 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [8:7] ...",
                    "Reserved",
                    "1");
                    treeView->setIndexWidget(index6, widget6);

                    break;

                } case 6: {

                    for (int i = 0; i < 4; i++) {
                        if (i == 0) {
                            QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2, 2,
                            "Reserved...",
                            "Reserved",
                            "2");
                            treeView->setIndexWidget(index1, widget1);
                        } else {
                            childItem->appendRow(new QStandardItem);
                            QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2, 2,
                            "Reserved...",
                            "Reserved",
                            "2");
                            treeView->setIndexWidget(index1, widget1);
                        }
                    }

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved...",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index1, widget1);

                    break;

                } case 7: {

                    for (int i = 0; i < 4; i++) {
                        if (i == 0) {
                            QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                            "Reserved...",
                            "Reserved",
                            "3");
                            treeView->setIndexWidget(index1, widget1);
                        } else {
                            childItem->appendRow(new QStandardItem);
                            QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                            "Reserved...",
                            "Reserved",
                            "3");
                            treeView->setIndexWidget(index1, widget1);
                        }
                    }

                    childItem->appendRow(new QStandardItem);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved...",
                    "Reserved",
                    "0");
                    treeView->setIndexWidget(index1, widget1);

                    break;

                } case 8: {
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                    "Output Stage Gain Control (0-15)...",
                    "Output Stage Gain Control must be 0-15",
                    "1");
                    treeView->setIndexWidget(index1, widget1);

                    for (int i = 0; i < 4; i++) {
                        if (i == 1) {
                            QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                            "Reserved...",
                            "Reserved",
                            "3");
                            treeView->setIndexWidget(index1, widget1);
                        } if (i == 3) {
                            QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                            "Reserved...",
                            "Reserved",
                            "0");
                            treeView->setIndexWidget(index1, widget1);
                        } else {
                            childItem->appendRow(new QStandardItem);
                            QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                            "Reserved...",
                            "Reserved",
                            "1");
                            treeView->setIndexWidget(index1, widget1);
                        }
                    }

                    break;
                }
            }


        }
    }
}






    if (model) blockEditing(model);

    layout->addWidget(treeView);

    toggleButton = new QPushButton("Expand All");
    layout->addWidget(toggleButton);

    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::on_toggle_button_clicked);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);





}



















