#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>

namespace Ui {
class itemWidget;
}

class itemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit itemWidget(QString name,QString note,double qty, QWidget *parent = nullptr);
    ~itemWidget();

private:
    Ui::itemWidget *ui;
    QWidget* myParent;
};

#endif // ITEMWIDGET_H
