#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QWidget>
#include "widget/orderWindow/customWidget/orderdatawidget.h"

namespace Ui {
class orderWindow;
}

class orderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit orderWindow(QWidget *parent = nullptr);
    ~orderWindow();
    void addToOrderContainer(QWidget* window);
    void deleteFromOrderContainer(orderDataWidget* orderData);
    void refreshData();

public slots:
    void addItemWidget(int orderNo);

private:
    Ui::orderWindow *ui;
    QWidget* myParent;

    QVector<orderDataWidget*> list;
    int row,column;
};

#endif // ORDERWINDOW_H
