#include "itemwidget.h"
#include "ui_itemwidget.h"

itemWidget::itemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemWidget)
{
    ui->setupUi(this);
}

itemWidget::~itemWidget()
{
    delete ui;
}
