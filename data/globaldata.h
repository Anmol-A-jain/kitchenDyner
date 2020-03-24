#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

class OrderData;

struct OrderItemData
{
    double qty;
    int status = 0 ;
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

    QVector<OrderItemData*>* itemList;

public:

    enum orderStatus{sendning,preparing,accepted,finished};

    OrderData(qint16 orderNo,qint16 tblNo)
    {
        this->orderNo = orderNo;
        this->tblNo = tblNo;
        itemList = new QVector<OrderItemData*>;
    }

    void setData(QString name,double qty,int status,QString ID,QString note)
    {
        OrderItemData* item = new OrderItemData;

        item->name = name;
        item->qty = qty;
        item->status = status;
        item->ID = ID;
        item->note = note;

        itemList->push_back(item);
    }


    void updateStatus(QString ID,int status)
    {
        for (int i = 0; i < itemList->count(); ++i)
        {
            if(itemList->at(i)->ID == ID)
            {
                itemList->at(i)->status = status;
            }
        }
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

};

#endif // GLOBALDATA_H
