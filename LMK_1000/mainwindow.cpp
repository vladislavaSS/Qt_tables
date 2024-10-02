#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "LMK1000-widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LMK1000Widget *lmkwidget = new LMK1000Widget(this);
    setCentralWidget(lmkwidget);

}


























