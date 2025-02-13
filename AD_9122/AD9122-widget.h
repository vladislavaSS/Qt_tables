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

    explicit AD9122Widget(/*Tables* tablesInstance, */QWidget *parent = nullptr);

private:

    Tables tables;

    Tables *tablesInstance;

    bool treeExpanded = 0;

//    bool ADflag = 1;

//    bool LMKflag = 0;

//    int bitCount = 8;

    QTreeView *treeView;

    QStandardItemModel *model;

    QVBoxLayout *layout;

    void viewTree();

    void loadJsonData(const QString &fileName);

    void createWidgets(QJsonObject bitObject, QWidget *container, QVBoxLayout *layout, QStandardItem *registerItem);

};

#endif // AD9122WIDGET_H
