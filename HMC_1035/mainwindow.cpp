#include "mainwindow.h"
#include "HCM1035-widget.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HCM1035Widget *hcmwidget = new HCM1035Widget(this);
    setCentralWidget(hcmwidget);
}
