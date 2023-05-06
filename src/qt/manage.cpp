#include "manage.h"
#include "ui_manage.h"
#include "newmanage.h"
#include <iostream>
#include <QMessageBox>
Manage::Manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manage)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/library.png"));
    setWindowTitle("管理员界面");
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    ui->tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_5->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView_4->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView_3->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView_5->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);


    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//自动调节
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    model3 = new QStandardItemModel( ui-> tableView_3);
    model4 = new QStandardItemModel( ui-> tableView_4);
    model5 = new QStandardItemModel( ui-> tableView_5);
    ui -> tableView_3 -> setModel ( model3 );
    ui -> tableView_4 -> setModel ( model4 );
    ui -> tableView_5 -> setModel ( model5 );
    model3->setHorizontalHeaderLabels(QStringList()<<"航班号"<<"始飞地"<<"目的地"<<"起飞时间"<<"到达时间"<<"票价"<<"剩余票数"<<"总票数");
    model4->setHorizontalHeaderLabels(QStringList()<<"邮箱"<<"姓名"<<"卡号"<<"性别"<<"密码");
    model5->setHorizontalHeaderLabels(QStringList()<<"邮箱"<<"姓名"<<"性别"<<"密码");
    int i = 0;
    for(Flight b : mainbs.getFlights()) {
          showbookline3(b,i++);
        }
   i=0;
   for(Passenger b : mainbs.getPassengers()) {
        Manage::showreaderline4(b,i++);
       }

}

Manage::~Manage()
{
    delete ui;
}

void Manage::on_btn_add_clicked()
{
    NewBook* book0 = new NewBook;
    book0->setWindowModality(Qt::ApplicationModal);
    book0->show();
}


void Manage::on_btn_add_2_clicked()
{
    register_qt* rg = new register_qt;
    rg->setWindowModality(Qt::ApplicationModal);
    rg->show();

}


void Manage::on_btn_re_book_clicked()
{
    int row = ui-> tableView_3 ->currentIndex().row();//获得当前行索引
    QModelIndex index;
    QString name[5];
    if(row!=-1)
      {
        for(int i = 0;i < 5;i++)
          {
            index = model3->index(row,i);
            name[i] = model3->data(index).toString();
          }
        index = model3->index(row,6);
        int tal = model3->data(index).toInt();
        index = model3->index(row,5);
        int money = model3->data(index).toInt();
        Re_book* reb = new Re_book;
        reb->get(name[0],name[1],name[2],name[3],name[4],tal,money);
        reb->setWindowModality(Qt::ApplicationModal);
        reb->show();

      }
}

void Manage::on_btn_deletebook_clicked()
{
    int row = ui-> tableView_3 ->currentIndex().row();//获得当前行索引
    QModelIndex index;
    index = model3->index(row,0);
    if(row != -1)
      {
        string id = model3->data(index).toString().toStdString();
        mainbs.cancelFlight(id);
        QMessageBox *msgbox = new QMessageBox(this);
        msgbox->information(this,"提示","删除成功！");
        save();
      }
      on_btn_all_2_clicked();
}

void Manage::on_btn_search_2_clicked()
{
  model3->removeRows(0,model3->rowCount());//清除
  int index=0, i = 0;
  if(index == 0)
    {
      qDebug() << ui->lineEdit->text() << ui->lineEdit_3->text();
        string start = ui->lineEdit_2->text().toStdString();
        string end = ui->lineEdit_3->text().toStdString();
        for(Flight b : mainbs.findFlights(start, end)) {
              showbookline3(b,i++);
            }
          }
}

void Manage::on_btn_all_2_clicked()
{
    model3->removeRows(0,model3->rowCount());//清除
    int i = 0;
    for(Flight b : mainbs.getFlights()) {
          showbookline3(b,i++);
        }
}

void Manage::on_btn_re_account_clicked()
{
    int row = ui-> tableView_4 ->currentIndex().row();//获得当前行索引
    QModelIndex index;
    int sex = 1;
    QString name[4];
    index = model4->index(row,1);
    name[0] = model4->data(index).toString();
    index = model4->index(row,0);
    name[1] = model4->data(index).toString();
    index = model4->index(row,2);
    name[2] = model4->data(index).toString();
    index = model4->index(row,4);
    name[3] = model4->data(index).toString();
    if(model4->data(index).toString() == "男")
      sex = 0;
    else sex = 1;
    Re_account* rea = new Re_account;
    rea->get(name[0],name[1],name[2],sex, name[3]);
    rea->setWindowModality(Qt::ApplicationModal);
    rea->show();
}

void Manage::on_btn_all_3_clicked()
{
    model4->removeRows(0,model4->rowCount());//清除
    int i = 0;
    for(Passenger b : mainbs.getPassengers()) {
         Manage::showreaderline4(b,i++);
        }
}

void Manage::on_btn_search_3_clicked()
{
  Passenger p = mainbs.getPassengerInfo(ui->lineEdit_4->text().toStdString());
    if(p.name != "")
          {
            model4->removeRows(0,model4->rowCount());//清除
            Manage::showreaderline4(p,0);
          }
        else
          {
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","无此用户信息！");
          }

}

void Manage::on_btn_deleteaccount_clicked()
{
  int row = ui-> tableView_4 ->currentIndex().row();//获得当前行索引
  QModelIndex index;
  index = model4->index(row,0);
  if(row != -1)
    {
      string id = model4->data(index).toString().toStdString();
      mainbs.cancelPassenger(id);
      QMessageBox *msgbox = new QMessageBox(this);
      msgbox->information(this,"提示","删除成功！");
      save();
      on_btn_all_3_clicked();
    }
}

void Manage::on_btn_addman_clicked()
{
    Newmanage* man = new Newmanage;
    man->setWindowModality(Qt::ApplicationModal);
    man->show();
}

void Manage::on_btn_reman_clicked()
{

}

void Manage::on_btn_deleteman_clicked()
{

}

void Manage::on_btn_search_clicked()
{

}

void Manage::showbookline3(Flight b,int i)
{
  model3->setItem(i,0,new QStandardItem(QString::fromStdString(b.getFlightNumber())));
  model3->setItem(i,1,new QStandardItem(QString::fromStdString(b.getDepartureAirport())));
  model3->setItem(i,2,new QStandardItem(QString::fromStdString(b.getArrivalAirport())));
  model3->setItem(i,3,new QStandardItem(QString::fromStdString(b.getDepartureTime())));
  model3->setItem(i,4,new QStandardItem(QString::fromStdString(b.getArrivalTime())));
  model3->setItem(i,5,new QStandardItem(QString::number(b.price)));
  model3->setItem(i,6,new QStandardItem(QString::number(b.getAvailableSeats())));
  model3->setItem(i,7,new QStandardItem(QString::number(b.getTotalSeats())));
}


void Manage::showreaderline4(Passenger b,int i)
{
  model4->setItem(i,0,new QStandardItem(QString::fromStdString(b.idNumber)));
  model4->setItem(i,1,new QStandardItem(QString::fromStdString(b.name)));
  model4->setItem(i,2,new QStandardItem(QString::fromStdString(b.idType)));
  model4->setItem(i,4,new QStandardItem(QString::fromStdString(b.password)));
  if(b.gender == "Male")
    {
       model4->setItem(i,3,new QStandardItem("男"));
    }
  else
    {
      model4->setItem(i,3,new QStandardItem("女"));
    }

}


void Manage::on_btn_all_clicked()
{

}


void Manage::on_btn_exit_clicked()
{
    library* rab = new library;
    rab->show();
    this->close();
}

void Manage::on_lineEdit_2_returnPressed()
{
    on_btn_search_2_clicked();
}

void Manage::on_lineEdit_4_returnPressed()
{
    on_btn_search_3_clicked();
}

void Manage::on_lineEdit_returnPressed()
{
    on_btn_search_clicked();
}

