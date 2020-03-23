#include "orderwindow.h"
#include "ui_orderwindow.h"

orderWindow::orderWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderWindow)
{
    ui->setupUi(this);
    myParent = parent;
}

orderWindow::~orderWindow()
{
    delete ui;
}
