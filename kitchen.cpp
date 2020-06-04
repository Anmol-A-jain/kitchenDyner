#include "kitchen.h"
#include "ui_kitchen.h"
#include "widget/serverConnection/serverconnection.h"
#include "widget/orderWindow/orderwindow.h"
#include <QMessageBox>
#include <data/allaction.h>
#include <data/databasecon.h>

serverSocket* Kitchen::s;

Kitchen::Kitchen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kitchen)
{
    ui->setupUi(this);
    logWindow = newWindow(widgetWindow::serverConnectionWindow);
    childFrame = logWindow;
    ui->windowContainer->addWidget(childFrame);

    databaseCon::initDB();
}

Kitchen::~Kitchen()
{
    delete ui;
}

QWidget *Kitchen::newWindow(int option)
{
    switch (option)
    {
        case serverConnectionWindow :
        {
            logWindow = new serverConnection(this);
            return logWindow;
            break;
        }
        case orderListWindow :
        {
            orderInfoWindow = new orderWindow(this);
            return orderInfoWindow;
            break;
        }
    }
    return childFrame;
}

void Kitchen::orderList()
{
    //childFrame->deleteLater();
    QWidget* temp = childFrame;
    childFrame = newWindow(orderListWindow);;
    ui->windowContainer->addWidget(childFrame);
    delete temp;
}

void Kitchen::closeWindow()
{
    QMessageBox::StandardButton reply = QMessageBox::critical(this,"Diconnected","Server has been disconnected,\n App will exit",QMessageBox::Ok);
    if(reply == QMessageBox::Ok)
        qApp->exit(0);
}

void Kitchen::addOrderItem(int orderNo)
{
    if(childFrame == orderInfoWindow)
    {
        static_cast<orderWindow*>(orderInfoWindow)->addItemWidget(orderNo);
    }
}
