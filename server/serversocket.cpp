#include "serversocket.h"
#include <QDebug>
#include <QMessageBox>
#include "widget/serverConnection/serverconnection.h"
#include "kitchen.h"
#include "data/allaction.h"
#include "data/globaldata.h"
#include "data/databasecon.h"
#include "kitchen.h"
#include <QSqlQuery>

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
    qDebug() << "serverConnection (myReadReady) : Data count (Should be 0) : " << bytes;

    QDataStream in(&dataIn,QIODevice::ReadWrite);

    qint16 action;
    in >> action;

    qDebug() << "serverConnection (myReadReady) : action : " << action;


    switch (action)
    {
        case ALLAction::kitchenInfo:
        {


            break;
        }
        case ALLAction::individual:
        {
            qint16 orderNo,tblNo,count;
            QString custName;

            in >> orderNo >> custName >> tblNo >> count;
            qDebug() << "serverConnection (myReadReady) : cart Data : "  << orderNo << ":" << custName << ":" << tblNo << ":" << count ;

            databaseCon d;
            QString cmd = "INSERT INTO tblOrderData VALUES ("+QString::number(orderNo)+","+QString::number(tblNo)+",'"+custName+"','"+GlobalData::sent+"');";
            delete d.execute(cmd);

            for (int i = 0; i < count; ++i)
            {
                QString itemName,note;
                double qty;

                in  >> itemName >> qty >> note;

                cmd = "INSERT INTO tblOrderItemData VALUES ("+QString::number(orderNo)+","+QString::number(qty)+",'"+itemName+"','"+note+"');";
                delete d.execute(cmd);

                qDebug() << "serverConnection (myReadReady) : data : " ;
                qDebug() << "serverConnection (myReadReady) : name : " << itemName;
                qDebug() << "serverConnection (myReadReady) : note : " << note;
                qDebug() << "serverConnection (myReadReady) : qty : " << qty << "\n";
            }

            QByteArray dataOut;
            QDataStream out(&dataOut,QIODevice::ReadWrite);

            qint16 sendAction = ALLAction::individual;
            QString status = "sent";
            out << sendAction ;

            out << orderNo  << status;

            serverClient->write(dataOut);
            serverClient->flush();

            static_cast<Kitchen*>(myParent)->addOrderItem(orderNo);

            break;
        }
        case ALLAction::deleteOrder:
        {
            qint16 orderNo;
            in >> orderNo;

            databaseCon d;
            QString cmd = "DELETE FROM tblOrderData WHERE orderNo = "+QString::number(orderNo)+" ;";
            delete d.execute(cmd);

            emit refreshOrders(orderNo);
            break;
        }
        case ALLAction::loginKitchen:
        {
            static_cast<Kitchen*>(myParent)->orderList();
            break;
        }
        case ALLAction::notification:
        {
            enum msgType{warning,informative,critical};
            QString errMsg;
            qint16 type;
            in >> type >> errMsg;

            switch (type)
            {
                case msgType::informative:
                {
                    QMessageBox::information(myParent,"Message",errMsg);
                    break;
                }
                case msgType::warning:
                {
                    QMessageBox::warning(myParent,"Message",errMsg);
                    break;
                }
                case msgType::critical:
                {
                    QMessageBox::critical(myParent,"Message",errMsg);
                    break;
                }

            }


            break;
        }
        default:
        {
            break;
        }
    }

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
    static_cast<Kitchen*>(myParent)->loginWidget();

}

void serverSocket::myDisconnect()
{
    static_cast<Kitchen*>(myParent)->closeWindow();
    qDebug() << "serverConnection (myDiconnected) : state : " << serverSocket::serverClient->state() ;
}
