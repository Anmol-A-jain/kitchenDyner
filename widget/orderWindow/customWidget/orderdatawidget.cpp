#include "orderdatawidget.h"
#include "ui_orderdatawidget.h"
#include "data/globaldata.h"
#include "data/allaction.h"
#include "widget/orderWindow/orderwindow.h"
#include "server/serversocket.h"
#include "data/databasecon.h"
#include <QDebug>


orderDataWidget::orderDataWidget(int orderNo, int tblNo, QString custName, QString status, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderDataWidget)
{
    ui->setupUi(this);

    this->myParent = parent;

    this->orderNo = orderNo;
    this->tblNo = tblNo;
    this->custName = custName;
    this->status = status;

    ui->lblName->setText(ui->lblName->text().append(custName));
    ui->lblOrderNo->setText(ui->lblOrderNo->text() + QString::number(orderNo));

    QString orderType = (tblNo != 0) ? ("Table : " + QString::number(tblNo)) : "Parcel" ;

    ui->lblOrderType->setText(orderType);

    GlobalData::setShadow(this,QColor(0,0,0),0,10);
    ui->btnComplete->hide();

    GlobalData::setShadow(ui->btnComplete,QColor(255,0,0),0,10);
    GlobalData::setShadow(ui->btnAccepted,QColor(52, 149, 254),0,10);

//    QVector<OrderData*>* orderList = &GlobalData::orderList;
//    for (int i = 0; i < orderList->count(); ++i)
//    {
//        if(orderNo == orderList->at(i)->getOrderNo() && orderList->at(i)->getStatus() == OrderData::accepted)
//        {
//            ui->btnAccepted->hide();
//            ui->btnComplete->show();
//        }
//    }

    if(status == GlobalData::accepted)
    {
        ui->btnAccepted->hide();
        ui->btnComplete->show();
    }

    loadData();
}

orderDataWidget::~orderDataWidget()
{
    deleteVectorData();
    delete ui;
}

void orderDataWidget::loadData()
{

    qDebug() << "orderDataWidget (loadData) : order No : " << orderNo ;
    //QVector<OrderData*>* orderList = &GlobalData::orderList;

    databaseCon d;
    QString cmd = "SELECT *   FROM tblOrderItemData WHERE orderID = "+QString::number(orderNo)+" ;";
    QSqlQuery* q =  d.execute(cmd);

    while(q->next())
    {

        //qDebug() << "orderDataWidget (loadData) : index no of orderList : " << i ;
        //QVector<OrderItemData*>* itemList = orderList->at(i)->getItemList();

        //qDebug() << "orderDataWidget (loadData) : count of item : " << itemList->count() ;

//        for (int j = 0; j < itemList->count(); ++j)
//        {


        QString name = q->value("name").toString() ;//itemList->at(j)->name;
        QString note = q->value("note").toString() ;//itemList->at(j)->note;
        double qty = q->value("qty").toDouble() ;//itemList->at(j)->qty;

        qDebug() << "orderDataWidget (loadData) : name : " << name  ;
        qDebug() << "orderDataWidget (loadData) : note : " << note ;
        qDebug() << "orderDataWidget (loadData) : qty : " << qty ;

        itemWidget *item = new itemWidget(name,note,qty,this);
        ui->itemContainer->addWidget(item);
        list.push_back(item);


//        }
    }
}

void orderDataWidget::deleteVectorData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        list[i]->deleteLater();
    }
}

void orderDataWidget::on_btnComplete_clicked()
{
    QByteArray dataOut;
    QDataStream out(&dataOut,QIODevice::ReadWrite);

    qint16 sendAction = ALLAction::individual;
    QString status = GlobalData::finished;
    qint16 orderNumber = this->orderNo;

    out << sendAction ;

    out << orderNumber << status;

    serverSocket::serverClient->write(dataOut);
    serverSocket::serverClient->flush();


    qDebug() << "orderDataWidget (on_btnComplete_clicked) : order No : " << orderNo ;

    databaseCon d;
    QString cmd = "DELETE FROM tblOrderData WHERE orderNo = "+QString::number(orderNo)+" ;";
    delete  d.execute(cmd);

//    QVector<OrderData*>* orderList = &GlobalData::orderList;

//    for (int i = 0; i < orderList->count(); ++i)
//    {
//        if(orderList->at(i)->getOrderNo() == this->orderNo)
//        {
//            qDebug() << "orderDataWidget (loadData) : index no of orderList : " << i ;

//            QVector<OrderItemData*>* itemList = orderList->at(i)->getItemList();
//            qDebug() << "orderDataWidget (loadData) : count of item : " << itemList->count() ;
//            for (int j = 0; j < itemList->count(); ++j)
//            {
//                delete itemList->at(j);
//            }
//            itemList->clear();
//            delete orderList->at(i);
//            orderList->remove(i);
//        }
//    }

    static_cast<orderWindow*>(myParent)->deleteFromOrderContainer(this);

}

void orderDataWidget::on_btnAccepted_clicked()
{
    QByteArray dataOut;
    QDataStream out(&dataOut,QIODevice::ReadWrite);

    qint16 sendAction = ALLAction::individual;
    QString status = GlobalData::accepted;

    qint16 orderNumber = this->orderNo;

    out << sendAction;

    out << orderNumber << status;

    serverSocket::serverClient->write(dataOut);
    serverSocket::serverClient->flush();
    ui->btnAccepted->hide();
    ui->btnComplete->show();
}

int orderDataWidget::getOrderNo() const
{
    return orderNo;
}
