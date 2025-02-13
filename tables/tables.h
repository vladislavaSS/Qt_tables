#ifndef AD9122WIDGET_H
#define AD9122WIDGET_H

#include "../tables_lib/functions.h"
#include "../tables_lib/functions.h"

#include "QJsonArray"
#include "QJsonObject"
#include "QJsonDocument"

extern QStringList itemNames;
extern QStringList regNames;

class AD9122Widget : public QWidget
{
    Q_OBJECT
public:

    explicit AD9122Widget(QWidget *parent = nullptr);

private:

    Tables tables;

    Tables *tablesInstance;

    bool treeExpanded = 0;

    QTreeView *treeView;

    QStandardItemModel *model;

    QVBoxLayout *layout;

    void loadJsonData(const QString &fileName);

    void createWidgets(QJsonObject bitObject, QWidget *container, QVBoxLayout *layout, QStandardItem *registerItem);

    void appendRows(QJsonObject registerObject, QStandardItem *rootItem);
};

#endif // AD9122WIDGET_H
