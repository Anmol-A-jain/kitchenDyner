#include "orderwindow.h"
#include "ui_orderwindow.h"
#include <data/globaldata.h>
#include "widget/orderWindow/customWidget/orderdatawidget.h"
#include <QDebug>
#include <QScrollBar>

orderWindow::orderWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderWindow)
{
    ui->setupUi(this);
    myParent = parent;
    row = 0;
    column = 0;
}

orderWindow::~orderWindow()
{
    delete ui;
}

void orderWindow::addToOrderContainer(QWidget *window)
{
    ui->orderContainer->addWidget(window,row,column);

    if(column==3)
    {
        row++;
        column = 0;
    }
    else
    {
        column++;
    }
}

void orderWindow::addItemWidget(int orderNo)
{
    QVector<OrderData*>* q = &GlobalData::orderList;

    for (int i = 0; i < q->count(); ++i)
    {
        qDebug() << "orderWindow (addItemWidget) : Order No : " << q->at(i)->getOrderNo();
        if(q->at(i)->getOrderNo() == orderNo)
        {
            int tblNo = q->at(i)->getTblNo(),status = q->at(i)->getStatus();
            QString custName = q->at(i)->getCustName();
            orderDataWidget* window = new orderDataWidget(orderNo,tblNo,custName,status,this);
            this->addToOrderContainer(window);
            list.push_back(window);
        }
    }

}
