#include "newmanage.h"
#include "ui_newmanage.h"
Newmanage::Newmanage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Newmanage)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/library.png"));
}

Newmanage::~Newmanage()
{
    delete ui;
}

void Newmanage::on_pushButton_clicked()
{

}
