#include "register_qt.h"
#include "ui_register_qt.h"


register_qt::register_qt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::register_qt)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/register.png"));
    setWindowTitle("立即注册");
}

register_qt::~register_qt()
{
    delete ui;
}


void register_qt::on_btn_register_clicked()
{
  string idnum = ui->re_num->text().toStdString();
  string name = ui->re_name->text().toStdString();
  string idt = ui->re_idt->text().toStdString();
  string gender;
  if (ui->re_sex->currentIndex() == 0)
    {
      gender = "Male";
    }
  else
    {
      gender = "Famale";
    }
  string password = ui->re_password1->text().toStdString();
  Passenger p1(name, gender, 30, idt, idnum,
                         "+1-234-567-890",password);

   if (ui->re_password1->text()!=ui->re_password2->text())
     {
       QMessageBox *msgbox = new QMessageBox(this);
      msgbox->information(this,"提示","两次密码不同，请重新输入！");
      ui->re_password1->setFocus();
      ui->re_password1->clear();
      ui->re_password2->clear();
     }
    else
     {
        mainbs.addPassenger(p1);
       QMessageBox *msgbox = new QMessageBox(this);
        msgbox->information(this,"提示","注册成功！");
       save();
       this->close();
     }
//  try {
//    if(ui->re_password1->text()!=ui->re_password2->text())
//    {
//       throw -1;
//  }
//       else if(Manager::AddReader(,,,))
//      {

//       QMessageBox *msgbox = new QMessageBox(this);
//       msgbox->information(this,"提示","注册成功！");
//       save();
//       this->close();
//  }
//    else
//      {
//        throw 'a';
//      }
//  }
//       catch (int a) {
//       QMessageBox *msgbox = new QMessageBox(this);
//       msgbox->information(this,"提示","两次密码不同，请重新输入！");

//       ui->re_password1->setFocus();
//       ui->re_password1->clear();
//       ui->re_password2->clear();

//  }
//      catch(char a)
//  {
//    QMessageBox *msgbox = new QMessageBox(this);
//    msgbox->information(this,"提示","此学号以被注册，请重新输入！");
//    ui->re_num->clear();
//    ui->re_num->setFocus();
//  }


}






//  if(ui->re_password1->text()!=ui->re_password2->text())
//    {
//      QMessageBox *msgbox = new QMessageBox(this);
//      msgbox->information(this,"提示","两次密码不同，请重新输入！");
//      ui->re_num->clear();
//      ui->re_name->clear();
//      ui->re_password1->clear();
//      ui->re_password2->clear();
//      ui->re_num->setFocus();
//    }
//  else
//    {
//      Manager::AddReader(ui->re_num->text().toStdString(),ui->re_name->text().toStdString(),ui->re_password1->text().toStdString(),ui->re_sex->currentIndex());
//      QMessageBox *msgbox = new QMessageBox(this);
//      msgbox->information(this,"提示","注册成功！");
//      save();
//      this->close();

//    }
