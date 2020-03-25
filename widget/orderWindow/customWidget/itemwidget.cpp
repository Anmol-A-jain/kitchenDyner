#include "itemwidget.h"
#include "ui_itemwidget.h"

itemWidget::itemWidget( QString name, QString note, double qty, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemWidget)
{
    ui->setupUi(this);

    this->myParent = parent;

    ui->lblQty->setText(QString::number(qty));
    ui->lblName->setText(name);
    ui->txtNote->setText("Note: " + note);

    if(note.isEmpty())
    {
        ui->txtNote->hide();
    }
}

itemWidget::~itemWidget()
{
    delete ui;
}
