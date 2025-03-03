#ifndef CUSTOMBOX_H
#define CUSTOMBOX_H

#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QStringList>
#include <QDebug>
#include <QPainter>

class ComboBoxDelegate : public QStyledItemDelegate {
public:
//    ComboBoxDelegate(const QStringList &items, QObject *parent = nullptr)
    ComboBoxDelegate(const QStringList &items, int row, QObject *parent = nullptr)
        : QStyledItemDelegate(parent), items(items) {}


    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (index.column() == 2 && index.row() == targetRow) {
            QComboBox *comboBox = new QComboBox(parent);
            comboBox->addItems(items);
            return comboBox;
        } return nullptr;
    }

    //    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    //        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();

    //        painter->save();
    //        painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, currentText);
    //        painter->restore();
    //    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox) {
            QString currentText = index.model()->data(index, Qt::EditRole).toString();
            int idx = comboBox->findText(currentText);
            if (idx >= 0) {
                comboBox->setCurrentIndex(idx);
            }
        }
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox) {
            model->setData(index, comboBox->currentText(), Qt::EditRole);
        }
    }

private:
    int targetRow;
    QStringList items;
};



#endif // CUSTOMBOX_H
