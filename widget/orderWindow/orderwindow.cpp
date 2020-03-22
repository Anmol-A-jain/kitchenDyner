#include "orderwindow.h"
#include "ui_orderwindow.h"

orderWindow::orderWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderWindow)
{
    ui->setupUi(this);
}

orderWindow::~orderWindow()
{
    delete ui;
}
