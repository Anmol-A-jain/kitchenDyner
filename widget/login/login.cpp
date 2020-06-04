#include <QMessageBox>

#include "login.h"
#include "ui_login.h"
#include "kitchen.h"
#include "server/serversocket.h"
#include "data/globaldata.h"
#include "data/databasecon.h"
#include "data/xmlmanipulation.h"
#include "data/allaction.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    myParent = parent;
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    QString name = ui->txtName->text();
    QString pass = ui->txtPass->text();

    if(pass.isEmpty() || name.isEmpty())
    {
        QMessageBox::warning(this,"Empty","Please filled all fields");
        return;
    }

    QByteArray dataOut;
    QDataStream out(&dataOut,QIODevice::ReadWrite);

    qint16 sendAction = ALLAction::loginKitchen;

    out << sendAction << name << pass;

    serverSocket::serverClient->write(dataOut);
    serverSocket::serverClient->flush();
}

void Login::on_txtName_returnPressed()
{
    on_btnLogin_clicked();
}

void Login::on_txtPass_returnPressed()
{
    on_btnLogin_clicked();
}
