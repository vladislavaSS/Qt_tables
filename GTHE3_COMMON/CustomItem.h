#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include "gthe3.h"

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QColor>
#include <QDebug>
#include <cmath>

class CustomItem : public QStandardItem {
public:
    CustomItem() : QStandardItem() {}
    CustomItem(const QString &text) : QStandardItem(text) {}

    QVariant getProperty(const QString &key) {
        return properties.value(key, QVariant());
    }

    void setProperty(const QString &key, const QVariant &value) {
        properties[key] = value;
    }

    void setPropertyList(const QString &key, const QVariantList &value) {
        properties.insert(key, QVariant::fromValue(value));
    }

    QVariantList getPropertyList(const QString &key) {
        QVariant value = properties.value(key, QVariant());
        if (value.canConvert<QVariantList>()) {
            return value.value<QVariantList>();
        }
        return QVariantList();
    }

    QStringList getPropertyKeys() const {
        return properties.keys();
    }

    QPair<int, int>split(QString str, QString sign) {

        int num1;
        int num2;
        QStringList parts = str.split(sign);
        if (parts.size() == 2) {
            bool ok1, ok2;
            num1 = parts[0].toInt(&ok1);
            num2 = parts[1].toInt(&ok2);
        }
        return qMakePair(num1, num2);
    }

    void validate(QStandardItem *item) {

        static bool isColorChange = false;
        if (isColorChange) return;
        CustomItem *customItem = dynamic_cast<CustomItem*>(item);

        if (!(customItem->getPropertyList("data").isEmpty())){
            QStringList stringList;
            QVariantList dataVar = customItem->getPropertyList("data");
            for (const QVariant &value : dataVar) {
                if (value.canConvert<QString>()) stringList << value.toString();
            }

            for (int i = 0; i < stringList.size(); ++i) {
                const QVariant &item = stringList[i];
                if (item.canConvert<QString>() && i % 2 == 0) {
                    if (item.toString() == customItem->text()) {
                        isColorChange = true;
                        setData(QBrush(QColor("Black")), Qt::ForegroundRole);
                        break;
                    } else {
                        isColorChange = true;
                        setData(QBrush(QColor("Red")), Qt::ForegroundRole);
                    }
                }
            }
        } else if (customItem->getProperty("range").isValid()) {

            QVariant condition = customItem->getProperty("range");
            QString cond = condition.toString();

            if (cond.contains(" - ")) {
                QPair<int, int> pair(split(cond, " - "));
                int num1 = pair.first;
                int num2 = pair.second;
                if (customItem->text().toInt() >= num1 && customItem->text().toInt() <= num2) {
                    isColorChange = true;
                    setData(QBrush(QColor("Black")), Qt::ForegroundRole);
                } else {
                    isColorChange = true;
                    setData(QBrush(QColor("Red")), Qt::ForegroundRole);
                }
            }

        } else {
            for (const QChar &ch : item->text()) {
                if (!ch.isDigit()) {
                    isColorChange = true;
                    setData(QBrush(QColor("Red")), Qt::ForegroundRole);
                    break;
                } else {
                    QString attrbits = customItem->getProperty("attrbits").toString();
                    int size = 0;

                    if (attrbits.contains(':')) {
                        QPair<int, int> pair(split(attrbits, ":"));
                        int num1 = pair.first;
                        int num2 = pair.second;
                        size = num1 - num2 + 1;
                    } else if (!attrbits.isEmpty()) size = 1;
                      else size = 0;


                    qint64 limit = pow(2, size) - 1;
                    if (!((item->text()).toLongLong() >= 0 && (item->text()).toLongLong() <= limit)) {
                        isColorChange = true;
                        setData(QBrush(QColor("Red")), Qt::ForegroundRole);
                    } else {
                        isColorChange = true;
                        setData(QBrush(QColor("Black")), Qt::ForegroundRole);
                    }
                }
            }
        }

        isColorChange = false;
    }

    QString tbl2js(QStandardItem *value) {

        CustomItem *item = dynamic_cast<CustomItem*>(value);

        if (item->getPropertyList("data").isEmpty() && !item->getProperty("diff").isValid())
            return value->text();
        else if (!(item->getPropertyList("data").isEmpty())) {

            QStringList stringList;
            QVariantList dataVar = item->getPropertyList("data");
            for (const QVariant &value : dataVar) {
                if (value.canConvert<QString>()) stringList << value.toString();
            }

            for (int i = 0; i < stringList.size(); ++i) {
                const QVariant &item = stringList[i];
                if (item.canConvert<QString>() && i % 2 == 0) {
                    if(value->text() == stringList[i]) return stringList[i+1];
                }
            }
        } else if (item->getProperty("diff").isValid()) {

            QVariant str = item->getProperty("diff");
            int diff = str.toInt() + item->text().toInt();

            if (diff >= 0) return QString::number(diff);

        }


    return 0;
    }

    QString getData(QStandardItem *item, QString data) {

        CustomItem *customItem = dynamic_cast<CustomItem*>(item);
        if (customItem->getPropertyList("data").isEmpty() && !customItem->getProperty("diff").isValid())
            return data;
        else if (!(customItem->getPropertyList("data").isEmpty())) {
            QStringList stringList;
            QVariantList dataVar = customItem->getPropertyList("data");
            for (const QVariant &value : dataVar) {
                if (value.canConvert<QString>()) stringList << value.toString();
            }
            for (int i = 0; i < stringList.size(); ++i) {
                const QVariant &item = stringList[i];
                if (item.canConvert<QString>() && i % 2 != 0) {
                    if(data == stringList[i]) return stringList[i-1];
                }
            }
        } else if (customItem->getProperty("diff").isValid()) {
            QVariant str = customItem->getProperty("diff");
            int diff = str.toInt() - item->text().toInt();
            if (diff >= 0) return QString::number(diff);
        }
        return QString();


    }




private:
    QTableView* tableView;
    QMap<QString, QVariant> properties;

};


#endif // CUSTOMITEM_H



