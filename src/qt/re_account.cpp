#include "re_account.h"
#include "ui_re_account.h"

Re_account::Re_account(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Re_account)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/library.png"));
    setWindowTitle("修改账户");
    ui->comboBox->addItem("男");
    ui->comboBox->addItem("女");
}

Re_account::~Re_account()
{
    delete ui;
}
void Re_account::get(QString a,QString b,QString c,int sex,QString d)
{
    old = b;
    ui->lineEdit_1->setText(a);
    ui->lineEdit_2->setText(b);
    ui->lineEdit_3->setText(c);
    ui->comboBox->setCurrentIndex(sex);
    ui->lineEdit_4->setText(d);

}

void Re_account::on_btn_save_clicked()
{
  for (Passenger &p : mainbs.passengers)
    {
      if (p.idNumber == old.toStdString())
        {
          qDebug() << old;
          p.name = ui->lineEdit_1->text().toStdString();
          p.idNumber = ui->lineEdit_2->text().toStdString();
          p.idType = ui->lineEdit_3->text().toStdString();
          p.password = ui->lineEdit_4->text().toStdString();
          if (ui->comboBox->currentIndex() == 0)
            {
              p.gender = "Male";
            }
          else
            {
              p.gender = "Famale";
            }
          QMessageBox *msgbox = new QMessageBox(this);
          msgbox->information(this,"提示","修改成功，请点击显示全表以查看！");
          save();
          this->close();
          break;
        }
    }
}


