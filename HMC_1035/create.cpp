#include "HMC1035-widget.h"

QWidget* HMC1035Widget::createComboBoxWidgetLable(const QString &labelText, const QStringList &options, int bitNumber, int bitWidth) {

    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *label = new QLabel(labelText);
    layout->addWidget(label);

    QComboBox *comboBox = new QComboBox();
    comboBox->setProperty("ComboBoxName", labelText);
    comboBox->setProperty("bitNumber", bitNumber);
    comboBox->setProperty("bitWidth", bitWidth);
    comboBox->setProperty("default", options);
    comboBox->addItems(options);
    layout->addWidget(comboBox);

    widget->setLayout(layout);

    return widget;
}

QCheckBox* HMC1035Widget::createCheckBoxWidget(const QString &labelText, CheckBoxState state, int bitNumber, int bitWidth) {
    QCheckBox *checkBox = new QCheckBox(labelText);
    checkBox->setProperty("checkBoxName", labelText);
    checkBox->setProperty("bitNumber", bitNumber);
    checkBox->setProperty("default", state);

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

QWidget* HMC1035Widget::LineEdit(const QString& labelText, const QString& placeholderText){

    QLabel *label = new QLabel(labelText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(label);

    QLabel *text = new QLabel(placeholderText);
    hLayout->addWidget(text);
    text->setProperty("QLabelName", placeholderText);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;

}

QWidget* HMC1035Widget::createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText, int bitNumber, int bitWidth) {
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

void HMC1035Widget::setEditableFlags(QStandardItem *item, bool editable) {
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

void HMC1035Widget::blockEditing(QStandardItemModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *rootItem = model->item(row);
        setEditableFlags(rootItem, false);
    }
}

void HMC1035Widget::on_toggle_button_clicked()
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

QString HMC1035Widget::bin2hex(const QString& binaryStr) {

    for (QChar c : binaryStr) if (c != '0' && c != '1') return QString();

    bool ok;
    quint64 decimalValue = binaryStr.toULongLong(&ok, 2);
    if (!ok) return QString();

    QString hexStr = QString::number(decimalValue, 16).toUpper();
    return hexStr;
}

QString HMC1035Widget::hex2Json(QString& Result, QString& text, int bitNumber, int bitCount) {

    int contrl_summ = bitNumber + Result.size();
    if (bitNumber > bitCount - 1) Result = "";
    else if (bitNumber < bitCount - 1) {
        if (Result.isEmpty()) Result += QString(bitCount - 1 - bitNumber, '0') + text;
        else if (!Result.isEmpty() && contrl_summ < bitCount) Result += QString(bitCount - 1 - contrl_summ, '0') + text;
        else Result += text;
    } else Result += text;

    return Result;


}

QString HMC1035Widget::dec2bin(const QString& decimalStr, int bitWidth) {

    bool ok;
    int decimalValue = decimalStr.toInt(&ok);

    if (!ok) return QString();

    QString binaryStr;
    if (decimalValue == 0) binaryStr = "0";
    else {
        while (decimalValue > 0) {
            binaryStr.prepend(QString::number(decimalValue % 2));
            decimalValue /= 2;
        }
    }

    if (binaryStr.size() < bitWidth) binaryStr = QString(bitWidth - binaryStr.size(), '0') + binaryStr;
    return binaryStr;
}

QString HMC1035Widget::hex2bin(QString &hexString) {

    bool ok;

    hexString = hexString.remove("0x").toUpper();
    int value = hexString.toInt(&ok, 16);

    if (!ok) return QString();

    QString binaryString = QString::number(value, 2);

    return binaryString.rightJustified(bitCount, '0');

}

QString HMC1035Widget::bin2dec(const QString& binaryString) {
    bool ok;
    int decimalValue = binaryString.toLongLong(&ok, 2);

    if (!ok) {
        return "";
    }

    return QString::number(decimalValue);
}

bool HMC1035Widget::isBinary(const QString &numericPart) {
    QString filtered = numericPart;
    filtered.remove('0');
    filtered.remove('1');
    return filtered.isEmpty();
}

