#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gthe3Widget = new GTHE3(this);
    setCentralWidget(gthe3Widget);
}

MainWindow::~MainWindow()
{
}

