#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

class OrderData;

struct OrderItemData
{
    double qty;
    QString name,ID,note;
};

class GlobalData
{
public:
    GlobalData();

    QString getTagName(int tagname);
    QString getattribute(int tagname);

    //shadow effect function
    static void setShadow(QWidget* widget, QColor color = QColor(0,0,0),qreal real = 0.0, qreal radius = 5.0);

    enum data{clientName};

    static QVector<OrderData*> orderList;

private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;
};

class OrderData
{
private:
    qint16 orderNo;
    qint16 tblNo;
    QString custName;
    int status;

    QVector<OrderItemData*>* itemList;

public:

    enum orderStatus{sendning,sent,accepted,finished};

    OrderData(qint16 orderNo,qint16 tblNo,QString orderType)
    {
        this->orderNo = orderNo;
        this->tblNo = tblNo;
        this->custName = orderType;
        this->status = sent;
        itemList = new QVector<OrderItemData*>;
    }

    void setData(QString name,double qty,QString ID,QString note)
    {
        OrderItemData* item = new OrderItemData;

        item->name = name;
        item->qty = qty;
        item->ID = ID;
        item->note = note;

        itemList->push_back(item);
    }


    void updateStatus(int status)
    {
        this->status = status;
    }

    QVector<OrderItemData *>* getItemList()
    {
        return itemList;
    }
    qint16 getOrderNo()
    {
        return orderNo;
    }

    qint16 getTblNo()
    {
        return tblNo;
    }
    QString getCustName()
    {
        return custName;
    }
    int getStatus()
    {
        return status;
    }

};

#endif // GLOBALDATA_H
