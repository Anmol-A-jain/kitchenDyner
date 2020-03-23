#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QWidget>

namespace Ui {
class orderWindow;
}

class orderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit orderWindow(QWidget *parent = nullptr);
    ~orderWindow();

private:
    Ui::orderWindow *ui;
    QWidget* myParent;
};

#endif // ORDERWINDOW_H
