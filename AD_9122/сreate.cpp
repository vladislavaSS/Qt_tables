#include "AD9122-widget.h"

void AD9122Widget::onItemChanged(QStandardItem* changedItem) {

    if (!changedItem) return;
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(treeView->model());
    if (!model) return;
}

QWidget* AD9122Widget::LineOfPower(int rowIndex, int valueLimit, const QString& placeholderText, const QString& errorMsg, const QString& defaultText) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholderText);
    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *saveButton = new QPushButton("Сохранить");

    connect(saveButton, &QPushButton::clicked, [this, lineEdit, valueLimit, errorMsg, defaultText]() {
        QString inputValue = lineEdit->text();
        int in_val = inputValue.toInt();
        if (inputValue.toInt()) {
            if (!((in_val >= 0) && ((in_val & (in_val - 1)) == 0)) || (in_val > valueLimit)) {
                QMessageBox::warning(this, "Ошибка", errorMsg);
                lineEdit->setText(defaultText);
            } else {
                QString processedValue = QString::number(inputValue.toInt());
                lineEdit->setText(processedValue);
                lineEdit->setStyleSheet("color: green;");
            }
        } else {
            lineEdit->setText(defaultText);
        }
    });

    hLayout->addWidget(lineEdit);
    hLayout->addWidget(saveButton);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);
    return widget;
}

QWidget* AD9122Widget::LineEdit(const QString& labelText, const QString& placeholderText){

    QLabel *label = new QLabel(labelText);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(label);

    QLabel *text = new QLabel(placeholderText);
    hLayout->addWidget(text);

    QWidget *widget = new QWidget();
    widget->setLayout(hLayout);

    return widget;
}

QWidget* AD9122Widget::createLineEditWithSaveButton(int rowIndex, double valueLimit, double modulo, const QString& placeholderText, const QString& errorMsg, const QString& defaultText, int bitNumber, int bitWidth) {
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

QWidget* AD9122Widget::createComboBoxWidgetLable(const QString &labelText, const QStringList &options, int bitNumber, int bitWidth) {

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

QCheckBox* AD9122Widget::createCheckBoxWidget(const QString &labelText, CheckBoxState state, int bitNumber, int bitWidth) {
    QCheckBox *checkBox = new QCheckBox(labelText);
    checkBox->setProperty("checkBoxName", labelText);
    checkBox->setProperty("bitNumber", bitNumber);
    checkBox->setProperty("bitWidth", bitWidth);
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

void AD9122Widget::setEditableFlags(QStandardItem *item, bool editable) {
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

void AD9122Widget::blockEditing(QStandardItemModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *rootItem = model->item(row);
        setEditableFlags(rootItem, false);
    }
}



















