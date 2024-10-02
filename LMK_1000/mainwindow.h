#define MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LMK1000-widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private:
    Ui::MainWindow *ui;
};
