#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btnLogin_clicked();

    void on_txtName_returnPressed();

    void on_txtPass_returnPressed();

private:
    Ui::Login *ui;
    QWidget* myParent;
};

#endif // LOGIN_H
