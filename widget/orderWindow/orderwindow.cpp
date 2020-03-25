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

    if(row == 0)
    {
        row = 1;
    }
    else
    {
        row = 0;
        column++;
    }

//    if(column==3)
//    {
//        row++;
//        column = 0;
//    }
//    else
//    {
//        column++;
//    }
}

void orderWindow::deleteFromOrderContainer(orderDataWidget *orderData)
{
    for (int i = 0; i < list.count(); ++i)
    {
        if(list.at(i) == orderData)
        {
            list.at(i)->deleteLater();
            list.remove(i);
        }
    }
    this->refreshData();
}

void orderWindow::refreshData()
{

    for (int i = 0; i < list.count(); ++i)
    {
        ui->orderContainer->removeWidget(list.at(i));
    }
    row = 0;
    column = 0;

    for (int i = 0; i < list.count(); ++i)
    {
        addToOrderContainer(list.at(i));
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
            int tblNo = q->at(i)->getTblNo();
            QString custName = q->at(i)->getCustName();
            orderDataWidget* window = new orderDataWidget(orderNo,tblNo,custName,this);
            this->addToOrderContainer(window);
            list.push_back(window);
        }
    }

}
