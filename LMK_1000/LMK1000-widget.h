#ifndef LMK1000WIDGET_H
#define LMK1000WIDGET_H

#include <QMainWindow>
#include "../tables_lib/functions.h"

class LMK1000Widget : public QWidget
{
    Q_OBJECT
public:
    explicit LMK1000Widget(Tables* tablesInstance, QWidget *parent = nullptr);

private slots:

    void setupWidgets(QStandardItem *itm, int rowIndex, QModelIndex lineEditIndex);

private:

    Tables tables;

    Tables *tablesInstance = new Tables;

    bool treeExpanded;

    bool LMKflag;

    int bitCount;

    QTreeView *treeView;

    QStandardItemModel *model;

    QVBoxLayout *layout;

    void viewTree();

};

#endif // LMK1000WIDGET_H
