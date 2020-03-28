#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QHash>
#include <QVector>
#include <QWidget>

class GlobalData
{
public:
    GlobalData();

    QString getTagName(int tagname);
    QString getattribute(int tagname);

    //shadow effect function
    static void setShadow(QWidget* widget, QColor color = QColor(0,0,0),qreal real = 0.0, qreal radius = 5.0);

    enum data{clientName};

    static QString sending ;
    static QString sent ;
    static QString accepted ;
    static QString finished ;

private:
    QHash<int,QString> tagname;
    QHash<int,QString> attribute;
};

#endif // GLOBALDATA_H
