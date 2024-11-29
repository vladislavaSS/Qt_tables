#include "mainwindow.h"
#include "HMC1035-widget.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HMC1035Widget *HMCwidget = new HMC1035Widget(this);
    setCentralWidget(HMCwidget);
}
