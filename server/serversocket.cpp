#include "serversocket.h"
#include <QDebug>
#include <QMessageBox>
#include "widget/serverConnection/serverconnection.h"
#include "kitchen.h"
#include "data/allaction.h"
#include "data/globaldata.h"
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

            QVector<OrderData*>* q = &GlobalData::orderList;

            OrderData* order = new OrderData(orderNo,tblNo,custName);
            q->push_back(order);

            for (int i = 0; i < count; ++i)
            {
                QString itemName,note;
                double qty;

                in  >> itemName >> qty >> note;

                order->setData(itemName,qty,note);

                qDebug() << "serverConnection (myReadReady) : data : " ;
                qDebug() << "serverConnection (myReadReady) : name : " << itemName;
                qDebug() << "serverConnection (myReadReady) : note : " << note;
                qDebug() << "serverConnection (myReadReady) : qty : " << qty << "\n";
            }

            QVector<OrderItemData*>* itemData = order->getItemList();

            for (int i = 0; i < itemData->count(); ++i)
            {
                qDebug() << "\nserverConnection (myReadReady) : data from GlobalData : " ;
                qDebug() << "serverConnection (myReadReady) : name : " << itemData->at(i)->name ;
                qDebug() << "serverConnection (myReadReady) : note : " << itemData->at(i)->note ;
                qDebug() << "serverConnection (myReadReady) : qty : " << itemData->at(i)->qty ;
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

            QVector<OrderData*>* q = &GlobalData::orderList;

            qDebug() << "serverConnection (myReadReady) : deleteOrder : count of List (before) : " <<q->count();

            for (int i = 0; i < q->count(); ++i)
            {
                if(q->at(i)->getOrderNo() == orderNo)
                {
                    q->at(i)->deleteThis();
                    delete q->at(i);
                    q->remove(i);
                }
                break;
            }
            qDebug() << "serverConnection (myReadReady) : deleteOrder : count of List (after): " <<q->count();
            emit refreshOrders(orderNo);
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
    static_cast<Kitchen*>(myParent)->orderList();

}

void serverSocket::myDisconnect()
{
    static_cast<Kitchen*>(myParent)->closeWindow();
    qDebug() << "serverConnection (myDiconnected) : state : " << serverSocket::serverClient->state() ;
}
