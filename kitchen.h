#ifndef KITCHEN_H
#define KITCHEN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Kitchen; }
QT_END_NAMESPACE

class Kitchen : public QMainWindow
{
    Q_OBJECT

public:
    Kitchen(QWidget *parent = nullptr);
    ~Kitchen();
    QWidget* newWindow(int option);
    void orderList();
    void closeWindow();

    void addOrderItem(int orderNo);

private:
    Ui::Kitchen *ui;
    QWidget* childFrame;
    QWidget* logWindow;
    QWidget* orderInfoWindow;

    enum widgetWindow{serverConnectionWindow,orderListWindow};
};
#endif // KITCHEN_H
