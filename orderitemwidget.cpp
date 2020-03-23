#include "orderitemwidget.h"
#include "ui_orderitemwidget.h"

orderItemWidget::orderItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderItemWidget)
{
    ui->setupUi(this);
}

orderItemWidget::~orderItemWidget()
{
    delete ui;
}
