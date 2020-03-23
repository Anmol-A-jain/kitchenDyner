#ifndef ORDERITEMWIDGET_H
#define ORDERITEMWIDGET_H

#include <QWidget>

namespace Ui {
class orderItemWidget;
}

class orderItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit orderItemWidget(QWidget *parent = nullptr);
    ~orderItemWidget();

private:
    Ui::orderItemWidget *ui;
};

#endif // ORDERITEMWIDGET_H
