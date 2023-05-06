#include "re_book.h"
#include "ui_re_book.h"
#include "manage.h"
Re_book::Re_book(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Re_book)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/library.png"));
    setWindowTitle("修改航班信息");

}

Re_book::~Re_book()
{
    delete ui;
}

void Re_book::get(QString a,QString b,QString c,QString d,QString f,int tal,int money)
{
    old = a;
    ui->lineEdit_1->setFocus();
    ui->lineEdit_1->setText(a);
    ui->lineEdit_2->setText(b);
    ui->lineEdit_3->setText(c);
    ui->lineEdit_4->setText(d);
    ui->lineEdit_5->setText(f);
    ui->lineEdit_6->setText(QString::number(tal));
    ui->lineEdit_7->setText(QString::number(money));
    qDebug() << old;
}

void Re_book::on_btn_re_clicked()
{
  for (Flight &f : mainbs.flights)
    {
      if (f.getFlightNumber() == old.toStdString())
        {
          qDebug() << old;
          f.flightNumber = ui->lineEdit_1->text().toStdString();
          f.departureAirport = ui->lineEdit_2->text().toStdString();
          f.arrivalAirport = ui->lineEdit_3->text().toStdString();
          f.departureTime = ui->lineEdit_4->text().toStdString();
          f.arrivalTime = ui->lineEdit_5->text().toStdString();
          f.totalSeats = ui->lineEdit_6->text().toInt();
          f.price = ui->lineEdit_7->text().toInt();
          QMessageBox *msgbox = new QMessageBox(this);
          msgbox->information(this,"提示","修改成功，请点击显示全表以查看！");
          save();
          this->close();
          break;
        }
    }
  /*
    if(ui->lineEdit_6->text().toInt() >= ui->lineEdit_1->text().toInt())
      {
        old->SetLeftnum(ui->lineEdit_1->text().toInt());
        old->SetBookName(ui->lineEdit_2->text().toStdString());
        old->SetBookWriter(ui->lineEdit_3->text().toStdString());
        old->SetBookPublisher(ui->lineEdit_4->text().toStdString());
        old->SetBookField(ui->lineEdit_5->text().toStdString());
        old->SetBookTotalnum(ui->lineEdit_6->text().toInt());
        QMessageBox *msgbox = new QMessageBox(this);
        msgbox->information(this,"提示","修改成功，请点击显示全表以查看！");
        save();
        this->close();
      }
    else{
        QMessageBox *msgbox = new QMessageBox(this);
        msgbox->information(this,"提示","总数量小于借出总数，请重新修改！");
        ui->lineEdit_6->clear();
        ui->lineEdit_1->clear();
        ui->lineEdit_1->setFocus();
      }
      */
}

void Re_book::on_btn_rent_clicked()
{
    Rent* ren = new Rent;
    ren->setWindowModality(Qt::ApplicationModal);
    ren->show();
}

