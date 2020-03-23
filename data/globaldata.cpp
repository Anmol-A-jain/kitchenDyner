#include "globaldata.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>

QVector<orderData*> GlobalData::CartItem;

GlobalData::GlobalData()
{
    this->tagname.insert(data::clientName,"waiterName");
    this->attribute.insert(data::clientName,"Name");
}

QString GlobalData::getTagName(int tagname)
{
    return this->tagname[tagname];
}

QString GlobalData::getattribute(int tagname)
{
    return this->attribute[tagname];
}

void GlobalData::setShadow(QWidget *widget,QColor color,qreal real,qreal radius  )
{
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(real);
    effect->setBlurRadius(radius);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}

void GlobalData::setItemQty(QString name, double qty, QString note)
{
    orderData* order = new orderData;

    order->name = name;
    order->note = note;
    order->qty = qty;

    CartItem.push_back(order);
}

void GlobalData::deleteCartVectordata()
{
    for (int i = 0; i < CartItem.count(); ++i)
    {
        delete CartItem.at(i);
    }
    CartItem.clear();
    qDebug() << "GlobalData (deleteCartVectordata) : cart data has been deleted";
}
