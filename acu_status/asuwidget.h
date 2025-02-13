#ifndef ASUWIDGET_H
#define ASUWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QStandardItem>
#include <QTabWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QFileSystemWatcher>


#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>


class asuWidget : public QWidget {
    Q_OBJECT

public:
    explicit asuWidget(QWidget *parent = nullptr);

    void tableK();

    void tableZ();

    void deserialized(QString path);

    QTabWidget *tabWidget;

    QVBoxLayout *layout;

//    QTabWidget *tabWidgetK;

    QVBoxLayout *layoutK;

//    QTabWidget *tabWidgetZ;

    QVBoxLayout *layoutZ;

    QString path = "Proto_AcuStatus.json";


    QTabWidget *tabWidgetK = new QTabWidget(this);
    QTabWidget *tabWidgetZ = new QTabWidget(this);


private:

    QFileSystemWatcher *fileWatcher;

    QStandardItemModel *model1;

    QStandardItemModel *model2;

};

#endif // ASUWIDGET_H
