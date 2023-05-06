#include "library.h"
#include "ui_library.h"

library::library(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::library)
{
    ui->setupUi(this);
    setFixedSize(600,300);
    setWindowIcon(QIcon(":/library.png"));
    setWindowTitle("飞机购票系统");
    ui->comboBox->addItem("用户登录");
    ui->comboBox->addItem("管理员登录");
    ui->line_account->setFocus();
}
library::~library()
{
    delete ui;
}


void library::on_btn_login_clicked()
{
    //Ladmin* mainladmin;
    int index = ui->comboBox->currentIndex();
    if(index == 0)
      {
        Passenger p = mainbs.getPassengerInfo(ui->line_account->text().toStdString());
        if(p.password != ui->line_password->text().toStdString())
          {

            ui->line_account->clear();
            ui->line_password->clear();
            ui->line_account->setFocus();
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","密码或用户名错误，请重新输入！");
            qDebug() << QString::fromStdString(p.idNumber);
            qDebug() << QString::fromStdString(p.password);
          }
        else{
            QMessageBox *msgbox = new QMessageBox(this);
            mainpassenger = p;
            msgbox->information(this,"提示","用户登录成功！");
            //File::LoadRecord(*mainreader,mainreader->GetRecord());
            Home* home = new Home;
            this->close();
            home->show();
          }
      }
    else{
        if(ui->line_password->text().toStdString() == "admin" && ui->line_account->text().toStdString() == "admin")
          {
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","管理员登录成功！");
            Manage* man = new Manage;
            this->close();
            man->show();
          }
        else
          {
            ui->line_account->clear();
            ui->line_password->clear();
            ui->line_account->setFocus();
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","密码或用户名错误，请重新输入！");
          }
      }
}

void library::on_btn_register_clicked()
{
    ui->line_account->clear();
    ui->line_password->clear();
    ui->line_account->setFocus();
    register_qt* re0 = new register_qt;
    re0->setWindowModality(Qt::ApplicationModal);
    re0->show();
}

void library::on_btn_retrieve_clicked()
{
    ui->line_account->clear();
    ui->line_password->clear();
    ui->line_account->setFocus();
    forget* fg = new forget;
    fg->setWindowModality(Qt::ApplicationModal);
    fg->show();
}

void library::on_comboBox_activated(int index)
{
    if(index == 1)
      {
        ui->line_account->clear();
        ui->line_password->clear();
        ui->btn_register->hide();
        ui->btn_retrieve->hide();
        ui->line_account->setFocus();
      }
    else
      {
        ui->line_account->clear();
        ui->line_password->clear();
        ui->btn_register->show();
        ui->btn_retrieve->show();
        ui->line_account->setFocus();
      }
}

void library::on_line_account_returnPressed()
{
    ui->line_password->setFocus();
}

void library::on_line_password_returnPressed()
{
    library::on_btn_login_clicked();
}
