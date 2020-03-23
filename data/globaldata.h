#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

// creating a structure to store menu data in it

struct orderData
{
    QString name;
    double qty = 0;
    QString note = "";
};

class GlobalData
{
public:
    GlobalData();

    QString getTagName(int tagname);
    QString getattribute(int tagname);

    //shadow effect function
    static void setShadow(QWidget* widget, QColor color = QColor(0,0,0),qreal real = 0.0, qreal radius = 5.0);

    //menu data Functions
    static void setItemQty(QString name,double qty,QString note);

    //delete vector
    static void deleteCartVectordata();

    //vector to store menu in dynamic array
    static QVector<orderData*> CartItem;

    enum data{clientName};

private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;
};

#endif // GLOBALDATA_H
