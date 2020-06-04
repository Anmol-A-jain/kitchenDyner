#include "serverconnection.h"
#include "ui_serverconnection.h"
#include <QDebug>
#include <QMessageBox>
#include <kitchen.h>

QVector<FindByIp*> serverConnection::threadList;

serverConnection::serverConnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverConnection)
{
    ui->setupUi(this);
    myParent = parent;

    QString title = "Log In";

    connect(serverSocket::serverClient,&QTcpSocket::stateChanged,this,&serverConnection::stateChanged);

    const QHostAddress &localhost = QHostAddress::LocalHost;
    QString ipaddress;
    for(const QHostAddress &address : QNetworkInterface::allAddresses() )
    {
        if(address != localhost && address.protocol() == QAbstractSocket::IPv4Protocol )
        {
            baseIp = address.toString();

            while(baseIp.right(1) != "." )
            {
                baseIp = baseIp.left(baseIp.length()-1);
            }
            ui->txtIp->setText(baseIp);
        }
    }
}

serverConnection::~serverConnection()
{
    delete ui;
}

void serverConnection::connectToServer(QString ip)
{
    Kitchen::s = new serverSocket(myParent);
    Kitchen::s->connectToSerever(ip);
}

void serverConnection::deleteAllThread()
{
    for(int i = 0; i < threadList.size(); ++i)
    {
        threadList[i]->exit();
    }
    qDebug() << "serverConnection (deleteAllThread) : deleted thread all thread ";
}

void serverConnection::on_btnConnect_clicked()
{
    if(ui->txtIp->text() == "")
        return;
    if(serverSocket::serverClient->state() == QTcpSocket::ConnectedState)
    {
        ui->lblStatus->setText("Connected");
        return;
    }
    this->connectToServer(ui->txtIp->text());

    if(serverSocket::serverClient->state() != QTcpSocket::ConnectingState || serverSocket::serverClient->state() != QTcpSocket::ConnectedState)
    {
        ui->lblStatus->setText("not Connected");
    }
}

void serverConnection::stateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << "serverConnection (stateChanged) : state : " << serverSocket::serverClient->state() ;
    if(state == QTcpSocket::UnconnectedState)
    {
        ui->lblStatus->setText("Try again");
    }
    if(state == QTcpSocket::ConnectingState)
    {
        ui->lblStatus->setText("Connecting...");
    }
}

void serverConnection::on_btnauto_clicked()
{
    const QHostAddress &localhost = QHostAddress::LocalHost;
    QString ipaddress;
    for(const QHostAddress &address : QNetworkInterface::allAddresses() )
    {
        if(address != localhost && address.protocol() == QAbstractSocket::IPv4Protocol )
        {
            baseIp = address.toString();

            while(baseIp.right(1) != "." )
            {
                baseIp = baseIp.left(baseIp.length()-1);
            }
            ui->txtIp->setText(baseIp);
        }
    }

    QString baseNetowrk = baseIp;

    for(int i = 0; i <= 255; i++)
    {
        QString currIp = (baseNetowrk + "%1").arg(i);

        FindByIp* f = new FindByIp(currIp,this);
        f->start();
        serverConnection::threadList.push_back(f);
        connect(f,SIGNAL(connectToServer(QString)),this,SLOT(connectToServer(QString)));
    }

    ui->btnauto->hide();
    ui->label_2->hide();
}
