#include "globaldata.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>

QVector<OrderData*> GlobalData::orderList;


QString OrderData::sending = "sending";
QString OrderData::sent = "sent";
QString OrderData::accepted = "accepted";
QString OrderData::finished = "finished";

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
    auto deleteItLater = widget->graphicsEffect() ;
    auto effect = new QGraphicsDropShadowEffect();
    effect->setOffset(real);
    effect->setBlurRadius(radius);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
    delete deleteItLater;
}
