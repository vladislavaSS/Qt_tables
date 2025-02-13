#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tables.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AD9122Widget *adwidget = new AD9122Widget(this);
    setCentralWidget(adwidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}



