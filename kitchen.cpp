#include "kitchen.h"
#include "ui_kitchen.h"
#include "widget/serverConnection/serverconnection.h"
#include "widget/orderWindow/orderwindow.h"
#include "widget/login/login.h"
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

    ui->btnLogout->hide();
    databaseCon::initDB();
}

Kitchen::~Kitchen()
{
    delete ui;
}

QWidget *Kitchen::newWindow(int option)
{
    ui->btnLogout->hide();
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
            ui->btnLogout->show();
            orderInfoWindow = new orderWindow(this);
            return orderInfoWindow;
            break;
        }
        case loginWindow:
        {
            login = new Login(this);
            return login;
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

void Kitchen::loginWidget()
{
    //childFrame->deleteLater();
    QWidget* temp = childFrame;
    childFrame = newWindow(loginWindow);;
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

void Kitchen::on_btnLogout_clicked()
{
    QMessageBox::StandardButton yes = QMessageBox::StandardButton::Yes;
    QMessageBox::StandardButton no = QMessageBox::StandardButton::No;

    QMessageBox::StandardButton reply = QMessageBox::information(this,"Logout?","Do you want to logout from kitchen",no|yes,no);

    if(reply == yes)
    {
        loginWidget();
    }
}
