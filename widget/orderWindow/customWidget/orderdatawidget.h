#ifndef ORDERDATAWIDGET_H
#define ORDERDATAWIDGET_H

#include <QWidget>

namespace Ui {
class orderDataWidget;
}

class orderDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit orderDataWidget(int orderNo,int tblNo,QString custName,int status,QWidget *parent = nullptr);
    ~orderDataWidget();


private:
    QWidget* myParent;
    Ui::orderDataWidget *ui;
    int orderNo;
    int tblNo;
    QString custName;
    int status;

};

#endif // ORDERDATAWIDGET_H
