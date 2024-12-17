#include "LMK1000-widget.h"

void LMK1000Widget::setupWidgets(QStandardItem *itm, int rowIndex, QModelIndex lineEditIndex) {

    if (rowIndex == 2) {
        QWidget *widget = createLineEditWithSaveButton(rowIndex, 510, 2,
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
        QWidget *widget = createLineEditWithSaveButton(rowIndex, 2250, 150,
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

QWidget* LMK1000Widget::createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText, int bitNumber, int bitWidth) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholderText);
    lineEdit->setProperty("lineEditName", placeholderText);
    lineEdit->setProperty("bitNumber", bitNumber);
    lineEdit->setProperty("bitWidth", bitWidth);
    lineEdit->setProperty("default", defaultText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *saveButton = new QPushButton("Сохранить");

    connect(saveButton, &QPushButton::clicked, [this, lineEdit, valueLimit, modulo, errorMsg, defaultText]() {
        QString inputValue = lineEdit->text();
        bool ok;
        int doubleValue = inputValue.toInt(&ok);

        if (ok && doubleValue >= 0 && doubleValue <= valueLimit) {
            if (modulo != 0) {
                if (fmod(doubleValue, modulo) == 0) {
                    QString processedValue = QString::number(doubleValue);
                    lineEdit->setText(processedValue);
                    lineEdit->setStyleSheet("color: green;");
                } else {
                    QMessageBox::warning(this, "Ошибка", "Введенное значение должно быть в пределах 0-" + QString::number(valueLimit) + "." + " и делиться на " + QString::number(modulo));
                    lineEdit->setText(defaultText);
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Недопустимый модуль: деление на ноль.");
                lineEdit->setText(defaultText);
            }
        } else {
                QMessageBox::warning(this, "Ошибка", "Введенное значение должно быть в пределах 0-" + QString::number(valueLimit) + ".");
                lineEdit->setText(defaultText);
        }
    });

    hLayout->addWidget(lineEdit);
    hLayout->addWidget(saveButton);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
}

void LMK1000Widget::setEditableFlags(QStandardItem *item, bool editable) {
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

void LMK1000Widget::blockEditing(QStandardItemModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *rootItem = model->item(row);
        setEditableFlags(rootItem, false);
    }
}



















