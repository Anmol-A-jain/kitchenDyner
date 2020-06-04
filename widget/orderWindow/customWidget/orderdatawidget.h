#ifndef ORDERDATAWIDGET_H
#define ORDERDATAWIDGET_H

#include <QWidget>
#include "widget/orderWindow/customWidget/itemwidget.h"

namespace Ui {
class orderDataWidget;
}

class orderDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit orderDataWidget(int orderNo, int tblNo, QString custName, QString status, QWidget *parent = nullptr);
    ~orderDataWidget();
    void loadData();
    void deleteVectorData();

    int getOrderNo() const;

private slots:
    void on_btnComplete_clicked();

    void on_btnAccepted_clicked();

private:
    QWidget* myParent;
    Ui::orderDataWidget *ui;
    int orderNo;
    int tblNo;
    QString custName,status;

    QVector<itemWidget*> list;

};

#endif // ORDERDATAWIDGET_H
