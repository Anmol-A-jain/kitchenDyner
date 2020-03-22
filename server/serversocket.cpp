#include "serversocket.h"
#include <QDebug>
#include <QMessageBox>
#include "widget/serverConnection/serverconnection.h"
#include "kitchen.h"

QTcpSocket* serverSocket::serverClient = new QTcpSocket();

serverSocket::serverSocket(QWidget* parent)
{
    myParent = parent;
}

void serverSocket::connectToSerever(QString ip)
{
    connect(serverClient,&QTcpSocket::readyRead,this,&serverSocket::myReadReady);
    connect(serverClient,&QTcpSocket::connected,this,&serverSocket::myConnected,Qt::DirectConnection);
    connect(serverClient,&QTcpSocket::disconnected,this,&serverSocket::myDisconnect);
    serverClient->connectToHost(ip,1812);
}

void serverSocket::myReadReady()
{
    // get the information
    //serverClient->waitForReadyRead(1000);
    int bytes = serverClient->bytesAvailable();
    QByteArray dataIn ;//= serverClient->readAll();
    qDebug() << "serverConnection (myReadReady) : Data available count: " << bytes;

    while(bytes != 0)
    {
        if(bytes < 1000 )
        {
            dataIn.append(serverClient->readAll());
            bytes = 0;
        }
        else
        {
            dataIn.append(serverClient->read(1000));
            bytes -= 1000;
        }
        qDebug() << "serverConnection (myReadReady) : Data in: " << dataIn;
        qDebug() << "serverConnection (myReadReady) : Data count: " << bytes;
    }

    qDebug() << "serverConnection (myReadReady) : Data in: " << dataIn;
    qDebug() << "serverConnection (myReadReady) : Data count: " << bytes;

    QMessageBox m;
    m.setText(dataIn);
    m.exec();

    QDataStream in(&dataIn,QIODevice::ReadWrite);

    qint16 action;
    in >> action;

    qDebug() << "serverConnection (myReadReady) : action : " << action;
}

void serverSocket::myConnected()
{

    QByteArray data ;
    QDataStream out(&data,QIODevice::ReadWrite);
    qint16 i = ALLAction::kitchenInfo;
    QString name = "kitchen";

    out << i << name ;

    serverClient->write(data);

    serverConnection::deleteAllThread();
    static_cast<Kitchen*>(myParent)->orderList();


}

void serverSocket::myDisconnect()
{
    static_cast<Kitchen*>(myParent)->closeWindow();
    qDebug() << "serverConnection (myDiconnected) : state : " << serverSocket::serverClient->state() ;
}
