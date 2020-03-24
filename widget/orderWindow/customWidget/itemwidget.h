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
    explicit itemWidget(QWidget *parent = nullptr);
    ~itemWidget();

private:
    Ui::itemWidget *ui;
};

#endif // ITEMWIDGET_H
