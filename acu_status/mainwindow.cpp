#include "mainwindow.h"
#include "asuwidget.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    asuWidget *widget = new asuWidget(this);
    setCentralWidget(widget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

