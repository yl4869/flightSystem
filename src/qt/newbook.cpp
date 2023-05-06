#include "newbook.h"
#include "ui_newbook.h"
#include <QMessageBox>
#include <QRegExpValidator>
NewBook::NewBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewBook)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/library.png"));
    setWindowTitle("添加航班");
    ui->lineEdit_6->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
}

NewBook::~NewBook()
{
    delete ui;
}

void NewBook::on_btn_addbook_clicked()
{
  string flightNumber = ui->lineEdit_1->text().toStdString();
  string departureAirport = ui->lineEdit_2->text().toStdString();
  string arrivalAirport = ui->lineEdit_3->text().toStdString();
  string departureTime = ui->lineEdit_4->text().toStdString();
  string arrivalTime = ui->lineEdit_5->text().toStdString();
  int totalSeats = ui->lineEdit_6->text().toInt();
  int money = ui->lineEdit_7->text().toInt();
  Flight flight1(flightNumber, departureTime, arrivalTime, departureAirport,
                 arrivalAirport, "United", "United", totalSeats);
  mainbs.addFlight(flight1);
  QMessageBox *msgbox = new QMessageBox(this);
  msgbox->information(this,"提示","添加航班成功，请点击显示全表以查看！");
  save();
  this->close();
}
