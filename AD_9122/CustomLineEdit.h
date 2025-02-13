#ifndef CUSTOM_LINE_EDIT_H
#define CUSTOM_LINE_EDIT_H

#include <QLineEdit>
#include <QDebug>


class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:

    QStringList m_validValues;

    explicit CustomLineEdit(QWidget *parent = nullptr) : QLineEdit(parent)
    {
        setPlaceholderText("Введите текст...");
//        setStyleSheet("QLineEdit { border: 2px solid gray; }");
    }

    void clearAndFocus()
    {
        clear();
        setFocus();
    }

    void setBorderColor(const QString &color)
    {
        setStyleSheet(QString("QLineEdit { border: 2px solid %1; }").arg(color));
    }

    void validateText(const QString &text) {

        qDebug() << "text" << text;

        if (!m_validValues.contains(text, Qt::CaseInsensitive)) {
            setBorderColor("red");
        } else {
            setBorderColor("gray");
        }
    }

private:


signals:

};

#endif // CUSTOM_LINE_EDIT_H





