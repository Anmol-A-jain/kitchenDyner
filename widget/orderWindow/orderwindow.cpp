#include "orderwindow.h"
#include "ui_orderwindow.h"
#include <data/globaldata.h>
#include <data/databasecon.h>
#include <server/serversocket.h>
#include "widget/orderWindow/customWidget/orderdatawidget.h"
#include <QDebug>
#include <QScrollBar>
#include <kitchen.h>

orderWindow::orderWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderWindow)
{
    ui->setupUi(this);
    myParent = parent;
    row = 0;
    column = 0;

    connect(Kitchen::s,SIGNAL(refreshOrders(qint16)),this,SLOT(deleteOrder(qint16)));

    databaseCon d;
    QString cmd = "SELECT * FROM tblOrderData ";
    QSqlQuery* q =  d.execute(cmd);

    while(q->next())
    {
//        qDebug() << "orderWindow (addItemWidget) : Order No : " << q->value("orderNo").toInt();
//        if(q->value("orderNo").toInt() == orderNo)
//        {

        int orderNo = q->value("orderNo").toInt() ;//q->at(i)->getTblNo();
        int tblNo = q->value("tblNo").toInt() ;//q->at(i)->getTblNo();
        QString custName = q->value("custName").toString();//q->at(i)->getCustName();
        QString status = q->value("status").toString();//q->at(i)->getCustName();


        orderDataWidget* window = new orderDataWidget(orderNo,tblNo,custName,status,this);
        this->addToOrderContainer(window);
        list.push_back(window);
//        }
    }

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
    //QVector<OrderData*>* q = &GlobalData::orderList;

    databaseCon d;
    QString cmd = "SELECT * FROM tblOrderData WHERE orderNo = "+QString::number(orderNo)+" ;";
    QSqlQuery* q =  d.execute(cmd);

    while(q->next())
    {
//        qDebug() << "orderWindow (addItemWidget) : Order No : " << q->value("orderNo").toInt();
//        if(q->value("orderNo").toInt() == orderNo)
//        {
        int tblNo = q->value("orderNo").toInt() ;//q->at(i)->getTblNo();
        QString custName = q->value("custName").toString();//q->at(i)->getCustName();
        QString status = q->value("status").toString();//q->at(i)->getCustName();


        orderDataWidget* window = new orderDataWidget(orderNo,tblNo,custName,status,this);
        this->addToOrderContainer(window);
        list.push_back(window);
//        }
    }

}

void orderWindow::deleteOrder(qint16 orderNo)
{
    qDebug() << "orderWindow (deleteOrder) : orderNo : " << orderNo;

    for (int i = 0; i < list.count(); ++i)
    {
        if(orderNo == list.at(i)->getOrderNo())
        {
            deleteFromOrderContainer(list.at(i));
        }
    }
}
