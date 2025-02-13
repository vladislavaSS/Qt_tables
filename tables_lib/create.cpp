#include "functions.h"


Tables::Tables(QWidget* parent) : QWidget(parent), treeView(new QTreeView(this)), model(new QStandardItemModel(this)) {
  layout = new QVBoxLayout();
}

void Tables::setEditableFlags(QStandardItem *item, bool editable) {
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

void Tables::blockEditing(QStandardItemModel *model) {
  for (int row = 0; row < model->rowCount(); ++row) {
    QStandardItem *rootItem = model->item(row);
    setEditableFlags(rootItem, false);
  }
}



















