#include "forget.h"
#include "ui_forget.h"
#include "library.h"

forget::forget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/forget.png"));
    setWindowTitle("找回密码");
}

forget::~forget()
{
    delete ui;
}


void forget::on_btn_register_2_clicked()
{
    Passenger p = mainbs.getPassengerInfo(ui->re_num_3->text().toStdString());
        if(ui->re_name_3->text().toStdString() != p.idType)
          {
            qDebug() << QString::fromStdString(p.idType);
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","邮箱与卡号不一致！");
            ui->re_num_3->clear();
            ui->re_name_3->clear();
            ui->re_num_3->setFocus();
          }
        else if(ui->re_password1_2->text() != ui->re_password2_2->text())
          {
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","两次密码输入不一致！");
            ui->re_password1_2->clear();
            ui->re_password2_2->clear();
            ui->re_password1_2->setFocus();
          }
        else
          {
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","重置密码成功！");
            for (Passenger &i : mainbs.passengers)
              {
                if (i.idNumber == p.idNumber)
                  {
                      i.password = ui->re_password1_2->text().toStdString();
                      break;
                  }
              }
            qDebug() << QString::fromStdString(p.idNumber);
            qDebug() << QString::fromStdString(p.password);
            save();
            this->close();
          }
      }

