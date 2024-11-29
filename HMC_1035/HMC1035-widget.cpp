#include "HMC1035-widget.h"

#include <QVBoxLayout>

HMC1035Widget::HMC1035Widget(QWidget *parent)
    : QWidget{parent}, treeView(new QTreeView(this)), model(new QStandardItemModel(this)), treeExpanded(false)
{
    viewTree();
    treeView -> setColumnWidth(0, 250);
}


void HMC1035Widget::viewTree() {
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
            regIndex1++;

        switch (regIndex1) {
            case 1: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = LineEdit("chip_ID [23:0] (RO register)", "A71A5");

                layout->addWidget(widget1);
                treeView->setIndexWidget(index1, container);

                break;
            } case 2: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 262143, 1,
                    "Not Defined [23:6]...",
                    "Not Defined must be 0-262143",
                    "?", 23, 18);
                layout->addWidget(widget3);

                QCheckBox *checkBox2 = createCheckBoxWidget("Soft Reset", Undefined, 5, 1);
                layout->addWidget(checkBox2);

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 31, 1,
                "Read Address [4:0]...",
                "Read Address must be 0-31",
                "?", 4, 5);

                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 3: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                for (int k = 10; k > 0; k--) {
                    if (k == 2){
                        QCheckBox *checkBox1 = createCheckBoxWidget("Reserved", Checked, 1, 1);
                        layout->addWidget(checkBox1);
                    } else {
                        QModelIndex index1 = model->index(parentItem->rowCount()-2, 1, parentItem->index());
                        QCheckBox *checkBox1 = createCheckBoxWidget("Reserved", Unchecked, k-1, 1);
                        layout->addWidget(checkBox1);
                    }
                }

                treeView->setIndexWidget(index1, container);

                break;
            } case 4: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16383, 1,
                "rdiv [13:0] (0-16383)...",
                "rdiv [13:0] must be 0-16383",
                "1", 13, 14);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 5: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 524287, 1,
                "intg [18:0] (0-524287)...",
                "intg [18:0] must be 0-524287",
                "25", 18, 19);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 6: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 16777215, 1,
                "frac [23:0] (0-16777215)...",
                "frac [23:0] must be 0-16777215",
                "0", 23, 24);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 7: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 511, 0,
                "VCO Subsystem data [15:7] (0-511)...",
                "VCO Subsystem data [15:7] must be 0-511",
                "0", 15, 9);
                layout->addWidget(widget3);

                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 0,
                "VCO Subsystem register address [6:3] (0-15)...",
                "VCO Subsystem register address [6:3] must be 0-15",
                "0", 6, 4);
                layout->addWidget(widget2);

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 0,
                "VCO Subsystem_ID [2:0] (0-7)...",
                "VCO Subsystem_ID [2:0] must be 0-7",
                "0", 2, 3);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 8: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox8 = createCheckBoxWidget("Reserved", Unchecked, 22, 1);
                layout->addWidget(checkBox8);

                QCheckBox *checkBox7 = createCheckBoxWidget("Reserved", Checked, 21, 1);
                layout->addWidget(checkBox7);

                QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0", 20, 2);
                layout->addWidget(widget6);

                QCheckBox *checkBox6 = createCheckBoxWidget("Reserved", Unchecked, 18, 1);
                layout->addWidget(checkBox6);

                QWidget *widget4 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0", 17, 2);
                layout->addWidget(widget4);

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0", 15, 2);
                layout->addWidget(widget3);

                QCheckBox *checkBox5 = createCheckBoxWidget("Reserved", Unchecked, 13, 1);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox4 = createCheckBoxWidget("Reserved", Unchecked, 12, 1);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox3 = createCheckBoxWidget("SD Enable", Checked, 11, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox2 = createCheckBoxWidget("Reserved", Unchecked, 10, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox1 = createCheckBoxWidget("Reserved", Checked, 9, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox0 = createCheckBoxWidget("Reserved", Checked, 8, 1);
                layout->addWidget(checkBox0);

                QCheckBox *checkBox = createCheckBoxWidget("frac_bypass", Unchecked, 7, 1);
                layout->addWidget(checkBox);

                QWidget *widget12 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "4", 6, 3);
                layout->addWidget(widget12);

                QWidget *widget11 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "2", 3, 2);
                layout->addWidget(widget11);

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("seed [1:0]", {"10 - B29D08h seed",
                                                                                    "00 - 0 seed",
                                                                                    "01 - lsb seed",
                                                                                    "11 - 50F1CDh seed"}, 1, 2);
                layout->addWidget(comboBoxWidget1);

                treeView->setIndexWidget(index1, container);


                break;
            } case 9: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox5 = createCheckBoxWidget("Reserved", Unchecked, 13, 1);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox4 = createCheckBoxWidget("Reserved", Unchecked, 12, 1);
                layout->addWidget(checkBox4);

                QWidget *comboBoxWidget5 = createComboBoxWidgetLable("LD Digital Timer Frequency Control [11:10]", {"00 - fastest",
                                                                                                                    "01",
                                                                                                                    "10",
                                                                                                                    "11 - slowest"}, 11, 2);
                layout->addWidget(comboBoxWidget5);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("LD Digital Window duration [9:7]", {"2 - 2 cycles",
                                                                                                          "0 - 1/2 cycle",
                                                                                                          "1 - 1 cycle",
                                                                                                          "3 - 4 cycles",
                                                                                                          "4 - 8 cycles",
                                                                                                          "5 - 16 cycles",
                                                                                                          "6 - 32 cycles",
                                                                                                          "7 - 64 cycles"}, 9, 3);
                layout->addWidget(comboBoxWidget4);

                QCheckBox *checkBox3 = createCheckBoxWidget("Lock Detect Window type", Checked, 6, 1);
                layout->addWidget(checkBox3);

                QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 0,
                "Reserved",
                "Reserved",
                "0", 5, 2);
                layout->addWidget(widget6);

                QCheckBox *checkBox2 = createCheckBoxWidget("Enable Internal Lock Detect", Checked, 3, 1);
                layout->addWidget(checkBox2);

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("lkd_wincnt_max [2:0]", {"5 - 2048",
                                                                                              "0 - 5",
                                                                                              "1 - 32",
                                                                                              "2 - 96",
                                                                                              "3 - 256",
                                                                                              "4 - 512",
                                                                                              "6 - 8192",
                                                                                              "7 - 65535"}, 2, 3);
                layout->addWidget(comboBoxWidget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 10: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                for (int k = 1; k < 3; k++) {
                    QCheckBox *checkBox1 = createCheckBoxWidget("Reserved", Checked, 24-k, 1);
                    layout->addWidget(checkBox1);
                }

                QCheckBox *checkBox = createCheckBoxWidget("High Frequency Reference", Unchecked, 21, 1);
                layout->addWidget(checkBox);

                for (int k = 1; k < 4; k++) {
                    QCheckBox *checkBox1 = createCheckBoxWidget("Reserved", Unchecked, 21-k, 1);
                    layout->addWidget(checkBox1);
                }

                QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 0,
                "Reserved",
                "Reserved",
                "3", 17, 3);
                layout->addWidget(widget6);

                QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 7, 0,
                "Reserved",
                "Reserved",
                "3", 14, 3);
                layout->addWidget(widget5);

                QCheckBox *checkBox1 = createCheckBoxWidget("Reserved", Checked, 11, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox4 = createCheckBoxWidget("VCO Buffer and Prescaler Bias Enable", Checked, 10, 1);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox3 = createCheckBoxWidget("Prescaler Clock enable", Checked, 9, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox5 = createCheckBoxWidget("Reserved", Unchecked, 8, 1);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox6 = createCheckBoxWidget("Reserved", Checked, 7, 1);
                layout->addWidget(checkBox6);

                QCheckBox *checkBox7 = createCheckBoxWidget("Reserved", Checked, 6, 1);
                layout->addWidget(checkBox7);

                QCheckBox *checkBox2 = createCheckBoxWidget("gpo_pad_en", Checked, 5, 1);
                layout->addWidget(checkBox2);

                for (int k = 5; k > 0; k--) {
                    QCheckBox *checkBox1 = createCheckBoxWidget("Reserved", Checked, k, 1);
                    layout->addWidget(checkBox1);
                }

                treeView->setIndexWidget(index1, container);

                break;
            } case 11: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());


                QCheckBox *checkBox6 = createCheckBoxWidget("Reserved", Unchecked, 23, 1);
                layout->addWidget(checkBox6);

                QCheckBox *checkBox5 = createCheckBoxWidget("Offset DN enable", Checked, 22, 1);
                layout->addWidget(checkBox5);

                QCheckBox *checkBox4 = createCheckBoxWidget("Offset UP enable", Unchecked, 21, 1);
                layout->addWidget(checkBox4);

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 127, 1,
                "Offset Magnitude (0-127)...",
                "Offset Magnitude must be 0-127",
                "0", 20, 7);
                layout->addWidget(widget3);

                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 100, 1,
                "CP UP Gain (0-127)...",
                "CP UP Gain must be 0-127",
                "100", 13, 7);
                layout->addWidget(widget2);

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 100, 1,
                "CP DN Gain (0-127)...",
                "CP DN Gain must be 0-127",
                "100", 6, 7);
                layout->addWidget(widget1);
                treeView->setIndexWidget(index1, container);

                break;
            } case 12: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0", 16, 1);
                layout->addWidget(widget1);

                QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0", 15, 1);
                layout->addWidget(widget2);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("FSM/VSPI Clock Select", {"01 - Input Crystal Reference/4",
                                                                                               "00 - Input Crystal Reference",
                                                                                               "10 - Input Crystal Reference/16",
                                                                                               "11 - Input Crystal Reference/32"}, 14, 2);
                layout->addWidget(comboBoxWidget4);

                QCheckBox *checkBox3 = createCheckBoxWidget("No VSPI Trigger", Unchecked, 12, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox1 = createCheckBoxWidget("Bypass VCO Tuning", Unchecked, 11, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox = createCheckBoxWidget("Force Curve", Unchecked, 10, 1);
                layout->addWidget(checkBox);

                QWidget *widget4 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "2", 9, 2);
                layout->addWidget(widget4);

                QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0", 7, 2);
                layout->addWidget(widget3);

                QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reserved",
                "Reserved",
                "0", 5, 3);
                layout->addWidget(widget5);

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("Vtune Resolution", {"5 - 64",
                                                                                          "0 - 1",
                                                                                          "1 - 2",
                                                                                          "2 - 4",
                                                                                          "3 - 8",
                                                                                          "4 - 32",
                                                                                          "6 - 128 Program this value",
                                                                                          "7 - 256"}, 2, 3);
                layout->addWidget(comboBoxWidget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 13: {
                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget13 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                "Reserved",
                "Reserved",
                "0", 23, 2);
                layout->addWidget(widget13);

                QWidget *widget12 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                "Reserved",
                "Reserved",
                "0", 21, 2);
                layout->addWidget(widget12);

                QWidget *widget11 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                "Reserved",
                "Reserved",
                "1", 19, 1);
                layout->addWidget(widget11);

                QWidget *widget10 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                "Reserved",
                "Reserved",
                "3", 18, 2);
                layout->addWidget(widget10);

                QWidget *widget9 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                "Reserved",
                "Reserved",
                "3", 16, 2);
                layout->addWidget(widget9);

                QWidget *widget7 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                "Reservedl",
                "Reserved",
                "0", 14, 3);
                layout->addWidget(widget7);

                QCheckBox *checkBox7 = createCheckBoxWidget("Reservedl", Unchecked, 11, 1);
                layout->addWidget(checkBox7);

                QCheckBox *checkBox6 = createCheckBoxWidget("Force CP DN", Unchecked, 10, 1);
                layout->addWidget(checkBox6);

                QCheckBox *checkBox5 = createCheckBoxWidget("Force CP UP", Unchecked, 9, 1);
                layout->addWidget(checkBox5);

                QWidget *comboBoxWidget4 = createComboBoxWidgetLable("CSP Mode", {"00 - Disabled",
                                                                                  "01 - 5.4ns",
                                                                                  "10 - 14.4ns",
                                                                                  "11 - 24.1ns"}, 8, 2);
                layout->addWidget(comboBoxWidget4);

                QCheckBox *checkBox2 = createCheckBoxWidget("PD_dn_en", Checked, 6, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox1 = createCheckBoxWidget("PD_up_en", Checked, 5, 1);
                layout->addWidget(checkBox1);

                for (int k = 3; k < 1; k++) {
                    QCheckBox *checkBox6 = createCheckBoxWidget("Reserved", Unchecked, k+2, 1);
                    layout->addWidget(checkBox6);
                }

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 273, 1,
                "PD_del_sel (0-273)...",
                "PD_del_sel must be 0-273",
                "1", 2, 3);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 14: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("CSP Mode", {"00 - Disabled",
                                                                                  "01 - Disabled",
                                                                                  "10 - 16383"}, 13, 14);

                layout->addWidget(comboBoxWidget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 15: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox4 = createCheckBoxWidget("Disable NFET", Unchecked, 9, 1);
                layout->addWidget(checkBox4);

                QCheckBox *checkBox3 = createCheckBoxWidget("Disable PFET", Unchecked, 8, 1);
                layout->addWidget(checkBox3);

                QCheckBox *checkBox2 = createCheckBoxWidget("LDO Driver Always On", Unchecked, 7, 1);
                layout->addWidget(checkBox2);

                QCheckBox *checkBox1 = createCheckBoxWidget("Prevent Automux SDO", Unchecked, 6, 1);
                layout->addWidget(checkBox1);

                QCheckBox *checkBox = createCheckBoxWidget("GPO Test Data", Unchecked, 5, 1);
                layout->addWidget(checkBox);

                QWidget *comboBoxWidget1 = createComboBoxWidgetLable("gpo_select", {"1 - Lock Detect Output",
                                                                                    "0 - Data from Reg0F[5]",
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
                                                                                    "26 - Not Used",
                                                                                    "27 - Not Used",
                                                                                    "28 - Not Used",
                                                                                    "29 - Not Used",
                                                                                    "30 - SPI Output Buffer En",
                                                                                    "31 - Soft RSTB"}, 4, 5);
                layout->addWidget(comboBoxWidget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 16: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QCheckBox *checkBox1 = createCheckBoxWidget("AutoCal Busy (RO register)", Unchecked, 8, 1);
                layout->addWidget(checkBox1);

                QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                "VCO Switch Setting",
                "VCO Switch Setting",
                "32", 7, 8);
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 17: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget2 = LineEdit("SAR Error Sign (RO register)", "0");
                layout->addWidget(widget2);

                QWidget *widget1 = LineEdit("SAR Error Mag Counts (RO register)", "7FFFF");
                layout->addWidget(widget1);

                treeView->setIndexWidget(index1, container);

                break;
            } case 18: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget1 = LineEdit("Lock Detect", "0");
                layout->addWidget(widget1);

                QWidget *widget2 = LineEdit("GPO", "0");
                layout->addWidget(widget2);

                treeView->setIndexWidget(index1, container);

                break;
            } case 19: {

                QWidget *container = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(container);
                QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                QWidget *widget2 = LineEdit("Reserved", "0");
                layout->addWidget(widget2);

                QWidget *widget1 = LineEdit("Reserved", "1259");
                layout->addWidget(widget1);

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
            regIndex2++;

            switch (regIndex2) {
                case 1: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 255, 1,
                    "CAPS [8:1] (0 - max frequency, 22 - min frequency.)",
                    "CAPS [8:1] ",
                    "16", 8, 8);
                    layout->addWidget(widget2);

                    QCheckBox *checkBox1 = createCheckBoxWidget("Cal", Unchecked, 0, 1);
                    layout->addWidget(checkBox1);

                    treeView->setIndexWidget(index1, container);

                    break;
                } case 2: {
                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                    QCheckBox *checkBox7 = createCheckBoxWidget("don’t care", Checked, 8, 1);
                    layout->addWidget(checkBox7);

                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 0,
                    "Reserved [7:6] ...",
                    "Reserved",
                    "3", 7, 2);
                    layout->addWidget(widget2);

                    QCheckBox *checkBox6 = createCheckBoxWidget("Output Stage Enable", Checked, 5, 1);
                    layout->addWidget(checkBox6);

                    QCheckBox *checkBox5 = createCheckBoxWidget("Spare", Checked, 4, 1);
                    layout->addWidget(checkBox5);

                    QCheckBox *checkBox4 = createCheckBoxWidget("IO Master Enable", Checked, 3, 1);
                    layout->addWidget(checkBox4);

                    QCheckBox *checkBox3 = createCheckBoxWidget("PLL Buffer Enable", Checked, 2, 1);
                    layout->addWidget(checkBox3);

                    QCheckBox *checkBox2 = createCheckBoxWidget("VCO Enable", Checked, 1, 1);
                    layout->addWidget(checkBox2);

                    QCheckBox *checkBox1 = createCheckBoxWidget("Master Enable VCO Subsystem", Checked, 0, 1);
                    layout->addWidget(checkBox1);

                    treeView->setIndexWidget(index1, container);

                    break;
                } case 3: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                    QCheckBox *checkBox7 = createCheckBoxWidget("don’t care", Checked, 8, 1);
                    layout->addWidget(checkBox7);

                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [7:6] ...",
                    "Reserved",
                    "0", 7, 2);
                    layout->addWidget(widget2);

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 62, 1,
                    "RF Divide ratio [5:0] ...",
                    "RF Divide ratio [5:0] must be <62",
                    "1", 5, 6);
                    layout->addWidget(widget1);

                    treeView->setIndexWidget(index1, container);

                    break;
                } case 4: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());


                    QWidget *comboBoxWidget7 = createComboBoxWidgetLable("Mute Mode [8:7]", {"01 - During VCO Calibration",
                                                                                             "00 - Mute enabled when divide ratio",
                                                                                             "10 - During VCO Calibration or when Lock Detect/GPO output is off",
                                                                                             "11 - Mute always On"}, 8, 2);
                    layout->addWidget(comboBoxWidget7);

                    QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 0,
                    "Reserved...",
                    "Reserved",
                    "0", 6, 1);
                    layout->addWidget(widget6);

                    QCheckBox *checkBox5 = createCheckBoxWidget("Increase Internal Output Resistance [5]", Unchecked, 5, 1);
                    layout->addWidget(checkBox5);

                    QCheckBox *checkBox4 = createCheckBoxWidget("Internal Termination Enable [4]", Checked, 4, 1);
                    layout->addWidget(checkBox4);

                    QCheckBox *checkBox3 = createCheckBoxWidget("RF_N output enable [3]", Unchecked, 3, 1);
                    layout->addWidget(checkBox3);

                    QCheckBox *checkBox2 = createCheckBoxWidget("RF_P output enable [2]", Unchecked, 2, 1);
                    layout->addWidget(checkBox2);

                    QWidget *comboBoxWidget1 = createComboBoxWidgetLable("Power- Performance Priroirty", {"10 - Power Priority",
                                                                                                          "00 - Not supported",
                                                                                                          "01 - Not supported",
                                                                                                          "11 - Performance Priority"}, 1, 2);
                    layout->addWidget(comboBoxWidget1);

                    treeView->setIndexWidget(index1, container);

                    break;

                } case 5: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                    QWidget *widget6 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [8:7] ...",
                    "Reserved",
                    "1", 8, 2);
                    layout->addWidget(widget6);

                    QWidget *widget5 = createLineEditWithSaveButton(parentItem->rowCount()-1, 2, 2,
                    "Reserved [6:5] ...",
                    "Reserved",
                    "2", 6, 2);
                    layout->addWidget(widget5);

                    QWidget *widget4 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [4:3] ...",
                    "Reserved",
                    "1", 4, 2);
                    layout->addWidget(widget4);

                    QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [2] ...",
                    "Reserved",
                    "0", 2, 1);
                    layout->addWidget(widget3);

                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 0, 0,
                    "Reserved [1] ...",
                    "Reserved",
                    "0", 1, 1);
                    layout->addWidget(widget2);

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 1,
                    "Reserved [0] ...",
                    "Reserved",
                    "1", 0, 1);
                    layout->addWidget(widget1);

                    treeView->setIndexWidget(index1, container);

                    break;

                } case 6: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 0,
                    "Reserved...",
                    "Reserved",
                    "0", 8, 1);
                    layout->addWidget(widget1);

                    for (int k = 8; k > 0; k--) {
                        if (k%2 != 0) {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 0,
                            "Reserved...",
                            "Reserved",
                            "2", k, 2);
                            layout->addWidget(widget1);
                        }
                    }

                    treeView->setIndexWidget(index1, container);

                    break;

                } case 7: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 0,
                    "Reserved...",
                    "Reserved",
                    "0", 8, 1);
                    layout->addWidget(widget1);

                    for (int k = 8; k > 0; k--) {
                        if (k%2 != 0) {
                            QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 0,
                            "Reserved...",
                            "Reserved",
                            "3", k, 2);
                            layout->addWidget(widget1);
                        }
                    }

                    treeView->setIndexWidget(index1, container);

                    break;

                } case 8: {

                    QWidget *container = new QWidget();
                    QVBoxLayout *layout = new QVBoxLayout(container);
                    QModelIndex index1 = model->index(parentItem->rowCount()-1, 1, parentItem->index());

                    QWidget *widget4 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 0,
                    "Reserved...",
                    "Reserved",
                    "0", 8, 1);
                    layout->addWidget(widget4);

                    QWidget *widget3 = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 0,
                    "Reserved...",
                    "Reserved",
                    "1", 7, 1);
                    layout->addWidget(widget3);

                    QWidget *widget2 = createLineEditWithSaveButton(parentItem->rowCount()-1, 3, 3,
                    "Reserved...",
                    "Reserved",
                    "3", 6, 2);
                    layout->addWidget(widget2);

                    QWidget *widget = createLineEditWithSaveButton(parentItem->rowCount()-1, 1, 0,
                    "Reserved...",
                    "Reserved",
                    "1", 4, 1);
                    layout->addWidget(widget);

                    QWidget *widget1 = createLineEditWithSaveButton(parentItem->rowCount()-1, 15, 1,
                    "Output Stage Gain Control (0-15)...",
                    "Output Stage Gain Control must be 0-15",
                    "1", 3, 4);
                    layout->addWidget(widget1);

                    treeView->setIndexWidget(index1, container);

                    break;
                }
            }


        }
    }
}


    if (model) blockEditing(model);

    HMCflag = 1;

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
    QHBoxLayout *layout_buttons2 = new QHBoxLayout(buttons);

    save_elem = new QPushButton("Save element", buttons);
    layout_buttons2->addWidget(save_elem);

    load_elem = new QPushButton("Download element", buttons);
    layout_buttons2->addWidget(load_elem);

    buttons2->setLayout(layout_buttons2);
    layout->addWidget(buttons2);

    connect(toggleButton, &QPushButton::clicked, this, &HMC1035Widget::on_toggle_button_clicked);
    connect(saveButton, &QPushButton::clicked, this, &HMC1035Widget::on_save_button_clicked);
    connect(treeView, &QTreeView::clicked, this, &HMC1035Widget::onParentItemClicked);
    connect(loadButton, &QPushButton::clicked, this, &HMC1035Widget::load_all);
    connect(load_elem, &QPushButton::clicked, this, &HMC1035Widget::load_element);

    setLayout(layout);

    HMCflag = 1;

}



















