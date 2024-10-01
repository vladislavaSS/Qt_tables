#include "HCM1035-widget.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QDebug>
#include <QVBoxLayout>

HCM1035Widget::HCM1035Widget(QWidget *parent)
    : QWidget{parent}, treeView(new QTreeView(this)), model(new QStandardItemModel(this)), treeExpanded(false)
{

    viewTree();
    treeView -> setColumnWidth(0, 250);
    setMaximumSize(900,900);
}


void HCM1035Widget::viewTree() {
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

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = LineEdit("chip_ID [23:0] (RO register)", "684453");

                layout->addWidget(widget1);
                treeView->setIndexWidget(index1, container);

                break;
            } case 2: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1048575, 0,
                "Read Address [4:0]...",
                "Read Address must be 0-1048575",
                "");

                layout->addWidget(widget1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Soft Reset", Undefined);
                layout->addWidget(checkBox2);

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1048575, 0,
                    "Not Defined [23:6]...",
                    "Not Defined must be 0-1048575",
                    "");
                layout->addWidget(widget3);

                treeView->setIndexWidget(index1, container);

                break;
            } case 3: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                "Reserved",
                "Reserved",
                "0");
                layout->addWidget(widget1);

                for (int k = 0; k < 10; k++) {
                    QModelIndex index1 = model->index(childItem->rowCount()-2, 1, childItem->index());
                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    layout->addWidget(widget1);
                }

                treeView->setIndexWidget(index1, container);

                break;
            } case 4: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1389561, 29,
                "rdiv [13:0] (29-1389561)...",
                "rdiv [13:0] must be 29-1389561",
                "1");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 5: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 524244, 365,
                "intg [18:0] (365-524244)...",
                "intg [18:0] must be 365-524244",
                "605");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 6: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16777215, 13,
                "frac [23:0] (13-16777215)...",
                "frac [23:0] must be 13-16777215",
                "0");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 7: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "VCO Subsystem_ID [2:0] (0-0)...",
                "VCO Subsystem_ID [2:0] must be 0-0",
                "0");
                layout->addWidget(widget1);

                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "VCO Subsystem register address [6:3] (0-0)...",
                "VCO Subsystem register address [6:3] must be 0-0",
                "0");
                layout->addWidget(widget2);

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "VCO Subsystem data [15:7] (0-0)...",
                "VCO Subsystem data [15:7] must be 0-0",
                "0");
                layout->addWidget(widget3);

                treeView->setIndexWidget(index1, container);

                break;
            } case 8: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("seed [1:0]", {"00 - 0 seed",
                                                                                    "01 - lsb seed",
                                                                                    "02 - B29D08h seed",
                                                                                    "03 - 50F1CDh seed"});
                layout->addWidget(comboBoxWidget1);

                QWidget *widget11 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "2");
                layout->addWidget(widget11);

                QWidget *widget12 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "4");
                layout->addWidget(widget12);

                QCheckBox *checkBox2 = createCheckBoxWidget("frac_bypass", Unchecked);
                layout->addWidget(checkBox2);

                for (int k = 0; k < 3; k++) {
                    if (k == 2) {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved5",
                        "0");
                        layout->addWidget(widget1);
                    } else {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        layout->addWidget(widget1);
                    }
                }

                QCheckBox *checkBox3 = createCheckBoxWidget("SD Enable", Checked);
                layout->addWidget(checkBox3);

                for (int k = 0; k < 8; k++) {
                    if (k == 6) {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        layout->addWidget(widget1);
                    } else {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "0");
                        layout->addWidget(widget1);
                    }
                }

                treeView->setIndexWidget(index1, container);

                break;
            } case 9: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
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
                layout->addWidget(comboBoxWidget1);

                QCheckBox *checkBox2 = createCheckBoxWidget("Enable Internal Lock Detect", Checked);
                layout->addWidget(checkBox2);

                QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                "Reserved",
                "Reserved",
                "0");
                layout->addWidget(widget6);

                QCheckBox *checkBox3 = createCheckBoxWidget("Lock Detect Window type", Checked);
                layout->addWidget(checkBox3);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("LD Digital Window duration [9:7]", {"2: 2 cycles",
                                                                                                          "0: 1/2 cycle",
                                                                                                          "1: 1 cycle",
                                                                                                          "3: 4 cycles",
                                                                                                          "4: 8 cycles",
                                                                                                          "5: 16 cycles",
                                                                                                          "6: 32 cycles",
                                                                                                          "7: 64 cycles"});
                layout->addWidget(comboBoxWidget4);

                QWidget *comboBoxWidget5 = createComboBoxWidgetLable("LD Digital Timer Frequency Control [11:10]", {"00 - fastest",
                                                                                                                    "01",
                                                                                                                    "10",
                                                                                                                    "11 - slowest"});
                layout->addWidget(comboBoxWidget5);

                for (int k = 0; k < 2; k++) {
/**/                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "0");
                        layout->addWidget(widget1);
                    }

                treeView->setIndexWidget(index1, container);

                break;
            } case 10: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                for (int k = 0; k < 5; k++) {
                    if (k == 0) {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        layout->addWidget(widget1);
                    } else {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        layout->addWidget(widget1);
                    }
                }

                QCheckBox *checkBox2 = createCheckBoxWidget("gpo_pad_en", Checked);
                layout->addWidget(checkBox2);

                for (int k = 0; k < 3; k++) {
                    if (k == 2) {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "0");
                        layout->addWidget(widget1);
                    } else {
                        childItem->appendRow(new QStandardItem);
                        QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        layout->addWidget(widget1);
                    }
                }

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Prescaler Clock enable",
                "Reserved",
                "1");
                layout->addWidget(widget3);

                QWidget *widget4 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "VCO Buffer and Prescaler Bias Enable",
                "Reserved",
                "1");
                layout->addWidget(widget4);

                for (int k = 0; k < 9; k++) {
                    if (k == 2 || k == 1) {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "17");
                        layout->addWidget(widget1);
                    } else if (k == 0 || k == 7 || k == 8){
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "1");
                        layout->addWidget(widget1);
                    } else {
                        QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                        "Reserved",
                        "Reserved",
                        "0");
                        layout->addWidget(widget1);
                    }
                }

                treeView->setIndexWidget(index1, container);

                break;
            } case 11: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2540, 0,
                "CP DN Gain (0-2540 µA)...",
                "CP DN Gain must be 0-2540 µA",
    /**/  "4109");
                layout->addWidget(widget1);

                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2540, 0,
                "CP UP Gain (0-2540 µA)...",
                "CP UP Gain must be 0-2540 µA",
    /**/  "4109");
                layout->addWidget(widget2);

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 635, 0,
                "Offset Magnitude (0-635 µA)...",
                "Offset Magnitude must be 0-635 µA",
                "0");
                layout->addWidget(widget3);

                QCheckBox *checkBox4 = createCheckBoxWidget("Offset UP enable", Unchecked);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox5 = createCheckBoxWidget("Offset DN enable", Checked);
                layout->addWidget(checkBox5);

    /**/        QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "1");

                layout->addWidget(widget6);

                treeView->setIndexWidget(index1, container);

                break;
            } case 12: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("Vtune Resolution", {"5: 64",
                                                                                          "0: 1",
                                                                                          "1: 2",
                                                                                          "2: 4",
                                                                                          "3: 8",
                                                                                          "4: 32",
                                                                                          "6: 128 Program this value",
                                                                                          "7: 256"});
                layout->addWidget(comboBoxWidget1);

                for (int k = 0; k < 3; k++) {
    /**/                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    layout->addWidget(widget1);
                }

    /**/        QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Bypass VCO Tuning",
                "error",
                "0");
                layout->addWidget(widget2);

                QCheckBox *checkBox3 = createCheckBoxWidget("No VSPI Trigger", Unchecked);
                layout->addWidget(checkBox3);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("FSM/VSPI Clock Select", {"1: Input Crystal Reference/4",
                                                                                               "0: Input Crystal Reference",
                                                                                               "2: Input Crystal Reference/16",
                                                                                               "3: Input Crystal Reference/32"});
                layout->addWidget(comboBoxWidget4);

                for (int k = 0; k < 2; k++) {
    /**/            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    layout->addWidget(widget1);
                }

                treeView->setIndexWidget(index1, container);

                break;
            } case 13: {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 273, 0,
                "PD_del_sel (0-273)...",
                "PD_del_sel must be 0-273",
                "1");
                layout->addWidget(widget1);

                for (int k = 0; k < 2; k++) {
    /**/            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    layout->addWidget(widget1);
                }

    /**/            QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
                "PD_up_en (0-16)...",
                "PD_up_en must be 0-16",
                "1");
                layout->addWidget(widget2);

    /**/            QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
                "PD_dn_en (0-16)...",
                "PD_dn_en must be 0-16",
                "1");
                layout->addWidget(widget3);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("CSP Mode", {"0 - Disabled",
                                                                                  "1 - 5.4ns",
                                                                                  "2 - 14.4ns",
                                                                                  "3 - 24.1ns"});
                layout->addWidget(comboBoxWidget4);

                QCheckBox *checkBox5 = createCheckBoxWidget("Force CP UP", Unchecked);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = createCheckBoxWidget("Force CP DN", Unchecked);
                layout->addWidget(checkBox6);

    /**/            QWidget *widget7 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reservedl",
                "Reserved",
                "0");
                layout->addWidget(widget7);

    /**/            QWidget *widget8 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0");
                layout->addWidget(widget8);

                for (int k = 0; k < 2; k++) {
    /**/                QWidget *widget9 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                    "Reserved",
                    "Reserved",
                    "3");
                    layout->addWidget(widget9);
                }

    /**/                QWidget *widget9 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                "Reserved",
                "Reserved",
                "1");
                layout->addWidget(widget9);

                for (int k = 0; k < 2; k++) {
    /**/                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved",
                    "Reserved",
                    "0");
                    layout->addWidget(widget1);
                }

                treeView->setIndexWidget(index1, container);

                break;
            } case 14: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("CSP Mode", {"0 - Disabled",
                                                                                  "1 - Disabled",
                                                                                  "2 - 16383d (3FFFh)"});

                layout->addWidget(comboBoxWidget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 15: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
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
                layout->addWidget(comboBoxWidget1);

                QCheckBox *checkBox2 = createCheckBoxWidget("GPO Test Data", Unchecked);

                layout->addWidget(checkBox2);

                treeView->setIndexWidget(index1, container);

                break;
            } case 16: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("Prevent Automux SDO", Unchecked);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox2 = createCheckBoxWidget("LDO Driver Always On", Unchecked);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox3 = createCheckBoxWidget("Disable PFET", Unchecked);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox4 = createCheckBoxWidget("Disable NFET", Unchecked);
                layout->addWidget(checkBox4);

                treeView->setIndexWidget(index1, container);

                break;
            } case 17: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

/**/                QWidget *widget1 = LineEdit("VCO Switch Setting (RO register)", "50");
                layout->addWidget(widget1);

                QWidget *widget2 = LineEdit("AutoCal Busy (RO register)", "0");
                layout->addWidget(widget2);

                treeView->setIndexWidget(index1, container);

                break;
            } case 18: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = LineEdit("SAR Error Mag Counts (RO register)", "2<sup>19</sup>-1");
                layout->addWidget(widget1);

                QWidget *widget2 = LineEdit("SAR Error Sign (RO register)", "0");
                layout->addWidget(widget2);

                treeView->setIndexWidget(index1, container);

                break;
            } case 19: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = LineEdit("GPO (RO register)", "0");
                layout->addWidget(widget1);

                QWidget *widget2 = LineEdit("Lock Detect (RO register)", "0");
                layout->addWidget(widget2);

                treeView->setIndexWidget(index1, container);

                break;
            } case 20: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                QWidget *widget1 = LineEdit("Reserved (RO register)", "288149");
                layout->addWidget(widget1);

                QWidget *widget2 = LineEdit("Reserved (RO register)", "0");
                layout->addWidget(widget2);

                treeView->setIndexWidget(index1, container);

                break;
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

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
                    "Cal [0] (0-16)",
                    "Cal [0] ",
                    "0");
                    layout->addWidget(widget1);

                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 22, 0,
                    "CAPS [8:1] (0 - max frequency, 22 - min frequency.)",
                    "CAPS [8:1] ",
                    "0");
                    layout->addWidget(widget2);

                    treeView->setIndexWidget(index1, container);

                    break;
                } case 2: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16777215, 0,
                    "RF Divide ratio [5:0] (0 - >62) ...",
                    "RF Divide ratio [5:0] must be 0 - >62",
                    "1");
                    layout->addWidget(widget1);

                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [7:6] ...",
                    "Reserved",
                    "0");
                    layout->addWidget(widget2);

                    QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16, 0,
                    "Don’t Care [8] (0-16) ...",
                    "Don’t Care [8] must be 0-16",
                    "0");
                    layout->addWidget(widget3);

                    treeView->setIndexWidget(index1, container);

                    break;
                } case 3: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index3 = model->index(childItem->rowCount()-1, 1, childItem->index());

                    QCheckBox *checkBox3 = createCheckBoxWidget("Master Enable VCO Subsystem [0]", Checked);
                    layout->addWidget(checkBox3);

                    QCheckBox *checkBox4 = createCheckBoxWidget("VCO Enable [1]", Checked);
                    layout->addWidget(checkBox4);

                    QCheckBox *checkBox5 = createCheckBoxWidget("PLL Buffer Enable [2]", Checked);
                    layout->addWidget(checkBox5);

                    QCheckBox *checkBox6 = createCheckBoxWidget("IO Master Enable [3]", Checked);
                    layout->addWidget(checkBox6);

                    QCheckBox *checkBox7 = createCheckBoxWidget("Spare [4]", Checked);
                    layout->addWidget(checkBox7);

                    QCheckBox *checkBox8 = createCheckBoxWidget("Output Stage Enable [5]", Checked);
                    layout->addWidget(checkBox8);

                    QWidget *widget10 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved...",
                    "Reserved",
                    "17");
                    layout->addWidget(widget10);

                    QCheckBox *checkBox9 = createCheckBoxWidget("don’t care [8]", Checked);
                    layout->addWidget(checkBox9);

                    treeView->setIndexWidget(index3, container);

                    break;
                } case 4: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                    QWidget *comboBoxWidget1 = createComboBoxWidgetLable("Power- Performance Priroirty", {"01 - Not supported",
                                                                                                          "00 - Not supported",
                                                                                                          "01 - Power Priority",
                                                                                                          "11 - Performance Priority"});
                    layout->addWidget(comboBoxWidget1);

                    QCheckBox *checkBox2 = createCheckBoxWidget("RF_P output enable [2]", Unchecked);
                    layout->addWidget(checkBox2);

                    QCheckBox *checkBox3 = createCheckBoxWidget("RF_N output enable [3]", Unchecked);
                    layout->addWidget(checkBox3);

                    QCheckBox *checkBox4 = createCheckBoxWidget("Internal Termination Enable [4]", Checked);
                    layout->addWidget(checkBox4);

                    QCheckBox *checkBox5 = createCheckBoxWidget("Increase Internal Output Resistance [5]", Unchecked);
                    layout->addWidget(checkBox5);

                    QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved...",
                    "Reserved",
                    "0");
                    layout->addWidget(widget6);

                    QWidget *comboBoxWidget7 = createComboBoxWidgetLable("Mute Mode [8:7]", {"01 - During VCO Calibration",
                                                                                             "00 - Mute enabled when divide ratio",
                                                                                             "01 - During VCO Calibration or when Lock Detect/GPO output is off",
                                                                                             "11 - Mute always On"});
                    layout->addWidget(comboBoxWidget7);

                    treeView->setIndexWidget(index1, container);

                    break;

                } case 5: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [0] ...",
                    "Reserved",
                    "1");
                    layout->addWidget(widget1);

                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [1] ...",
                    "Reserved",
                    "0");
                    layout->addWidget(widget2);

                    QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [2] ...",
                    "Reserved",
                    "0");
                    layout->addWidget(widget3);

                    QWidget *widget4 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [4:3] ...",
                    "Reserved",
                    "1");
                    layout->addWidget(widget4);

                    QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2, 2,
                    "Reserved [6:5] ...",
                    "Reserved",
                    "2");
                    layout->addWidget(widget5);

                    QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [8:7] ...",
                    "Reserved",
                    "1");
                    layout->addWidget(widget6);

                    treeView->setIndexWidget(index1, container);

                    break;

                } case 6: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                    for (int i = 0; i < 4; i++) {
                        if (i == 0) {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2, 2,
                            "Reserved...",
                            "Reserved",
                            "2");
                            layout->addWidget(widget1);
                        } else {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2, 2,
                            "Reserved...",
                            "Reserved",
                            "2");
                            layout->addWidget(widget1);
                        }
                    }

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved...",
                    "Reserved",
                    "0");
                    layout->addWidget(widget1);

                    treeView->setIndexWidget(index1, container);

                    break;

                } case 7: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                    for (int i = 0; i < 4; i++) {
                        if (i == 0) {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                            "Reserved...",
                            "Reserved",
                            "3");
                            layout->addWidget(widget1);
                        } else {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                            "Reserved...",
                            "Reserved",
                            "3");
                            layout->addWidget(widget1);
                        }
                    }

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved...",
                    "Reserved",
                    "0");
                    layout->addWidget(widget1);

                    treeView->setIndexWidget(index1, container);

                    break;

                } case 8: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(childItem->rowCount()-1, 1, childItem->index());

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                    "Output Stage Gain Control (0-15)...",
                    "Output Stage Gain Control must be 0-15",
                    "1");
                    layout->addWidget(widget1);

                    for (int i = 0; i < 4; i++) {
                        if (i == 1) {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                            "Reserved...",
                            "Reserved",
                            "3");
                            layout->addWidget(widget1);
                        } if (i == 3) {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                            "Reserved...",
                            "Reserved",
                            "0");
                            layout->addWidget(widget1);
                        } else {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                            "Reserved...",
                            "Reserved",
                            "1");
                            layout->addWidget(widget1);
                        }
                    }

                    treeView->setIndexWidget(index1, container);

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

    QWidget *buttons = new QWidget();
    QHBoxLayout *layout_buttons = new QHBoxLayout(buttons);

    saveButton = new QPushButton("Save", buttons);
    layout_buttons->addWidget(saveButton);

    loadButton = new QPushButton("Download", buttons);
    layout_buttons->addWidget(loadButton);

    buttons->setLayout(layout_buttons);
    layout->addWidget(buttons);

    connect(toggleButton, &QPushButton::clicked, this, &HCM1035Widget::on_toggle_button_clicked);
    connect(saveButton, &QPushButton::clicked, this, &HCM1035Widget::on_save_button_clicked);
    connect(loadButton, &QPushButton::clicked, this, &HCM1035Widget::on_load_button_clicked);

    setLayout(layout);
//    QWidget *centralWidget = new QWidget(this);
//    centralWidget->setLayout(layout);
//    setCentralWidget(centralWidget);





}



















