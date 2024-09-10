#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <cmath>
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>


extern QStringList itemNames;
extern QStringList regNames;

QWidget* MainWindow::createComboBoxWidgetLable(const QString &labelText, const QStringList &options) {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *label = new QLabel(labelText);
    layout->addWidget(label);

    QComboBox *comboBox = new QComboBox();
    comboBox->addItems(options);
    layout->addWidget(comboBox);

    widget->setLayout(layout);

    return widget;
}

QCheckBox* MainWindow::createCheckBoxWidget(const QString &labelText, CheckBoxState state) {
    QCheckBox *checkBox = new QCheckBox(labelText);

    switch (state) {
        case Unchecked:
            checkBox->setChecked(false);
            checkBox->setTristate(false);
            break;
        case Checked:
            checkBox->setChecked(true);
            checkBox->setTristate(false);
            break;
        case Undefined:
            checkBox->setCheckState(Qt::PartiallyChecked);
            checkBox->setTristate(true);
            break;
    }

    return checkBox;
}

QWidget* MainWindow::LineEdit(const QString& labelText, const QString& placeholderText){

    QLabel *label = new QLabel(labelText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(label);

    QLabel *text = new QLabel(placeholderText);
    hLayout->addWidget(text);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
}

QWidget* MainWindow::createLineEditWithSaveButton(int rowIndex, double valueLimit, double minLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholderText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *saveButton = new QPushButton("Сохранить");

    connect(saveButton, &QPushButton::clicked, [this, lineEdit, valueLimit, minLimit, errorMsg, defaultText]() {
        QString inputValue = lineEdit->text();
        bool ok;
        double doubleValue = inputValue.toDouble(&ok);

        if (ok && doubleValue >= 0.0 && doubleValue <= valueLimit && minLimit <= doubleValue) {
                if (doubleValue) {
                    QString processedValue = QString::number(doubleValue, 'f', 2);
                    lineEdit->setText(processedValue);
                    lineEdit->setStyleSheet("color: green;");
                }
        } else {
            QMessageBox::warning(this, "Ошибка", "Введенное значение должно быть десятичным в пределах " + QString::number(minLimit) + "-" + QString::number(valueLimit));
            lineEdit->setText(defaultText);
        }
    });

    hLayout->addWidget(lineEdit);
    hLayout->addWidget(saveButton);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
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

QStringList itemNames = {"PLL", "VCO Subsystem"};

QStringList childName1 = {
    "00h ID Register", "00h Open Mode Read Address/RST Strobe Register", "01h RST Register", "02h REFDIV Register", "03h Frequency Register - Integer Part",
    "04h Frequency Register - Fractional Part", "05h VCO SPI Register", "06h SD CFG Register", "07h Lock Detect Register", "08h Analog EN Register",
    "09h Charge Pump Register", "0Ah VCO AutoCal Configuration Register", "0Bh PD Register", "0Ch Exact Frequency Mode Register", "0Fh GPO_LD/SDO Register",
    "10h VCO Tune Register", "11h SAR Register", "12h GPO2 Register", "13h BIST Register"
};

QStringList childName2 = {
    "00h Tuning", "01h Enables", "02h Biases", "03h Config", "04h Cal/Bias",
    "05h CF_Cal", "06h MSB Cal", "07h MSB Cal"
};










