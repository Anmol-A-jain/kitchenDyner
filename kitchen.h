#ifndef KITCHEN_H
#define KITCHEN_H

#include <QMainWindow>
#include "server/serversocket.h"

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
    void loginWidget();
    void closeWindow();
    void addOrderItem(int orderNo);

    static serverSocket* s;

private slots:
    void on_btnLogout_clicked();

private:
    Ui::Kitchen *ui;
    QWidget* childFrame;
    QWidget* logWindow;
    QWidget* orderInfoWindow;
    QWidget* login;

    enum widgetWindow{serverConnectionWindow,orderListWindow,loginWindow};
};
#endif // KITCHEN_H
