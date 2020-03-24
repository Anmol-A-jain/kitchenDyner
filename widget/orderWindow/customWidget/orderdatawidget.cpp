#include "orderdatawidget.h"
#include "ui_orderdatawidget.h"
#include <QTimer>
#include "data/globaldata.h"

orderDataWidget::orderDataWidget(int orderNo, int tblNo, QString custName, int status, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderDataWidget)
{
    ui->setupUi(this);

    this->myParent = parent;

    this->orderNo = orderNo;
    this->tblNo = tblNo;
    this->custName = custName;
    this->status = status;

    ui->lblName->setText(ui->lblName->text().append(custName));
    ui->lblTbl->setText(ui->lblTbl->text() + QString::number(tblNo));
    ui->lblOrderNo->setText(ui->lblOrderNo->text() + QString::number(orderNo));

    QString orderType = (tblNo != 0) ? "Booked Table" : "Parcel" ;

    ui->lblOrderType->setText(orderType);

    GlobalData::setShadow(this,QColor(0,0,0),0,10);
}

orderDataWidget::~orderDataWidget()
{
    delete ui;
}
