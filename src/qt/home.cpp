#include "home.h"
#include "ui_home.h"
#include <QMessageBox>

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    int i = 0;
    ui->setupUi(this);
    setWindowIcon(QIcon(":/library.png"));
    setWindowTitle("用户界面");
    ui->tableView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_1->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableView_1->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableView_2->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//自动调节
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    model1 = new QStandardItemModel( ui-> tableView_1);
    model2 = new QStandardItemModel( ui-> tableView_2);
    ui -> tableView_1 -> setModel ( model1 );
    ui -> tableView_2 -> setModel ( model2 );
    model1->setHorizontalHeaderLabels(QStringList()<<"航班号"<<"始飞地"<<"目的地"<<"起飞时间"<<"到达时间"<<"票价"<<"剩余票数");
    model2->setHorizontalHeaderLabels(QStringList()<<"航班号"<<"始飞地"<<"目的地"<<"起飞时间"<<"到达时间"<<"票价");

    for(Flight b : mainbs.getFlights()) {
          showbookline1(b,i++);
        }
    i = 0;
    for(Ticket t : mainbs.findPassengerTickets(mainpassenger.idNumber)) {
          Flight b = mainbs.getFlightInfo(t.flightNumber);
          showbookline2(b,i++);
        }
    /*
    for(auto i = mainreader->GetRecord().begin();i!=mainreader->GetRecord().end(); i++) { i->CheckRecord(); }
    mainreader->CheckRecord();
    if(mainreader->GetNumber() == 0)
      {
        ui->lineEdit_2->setStyleSheet("color:red");//文本颜色
        ui->lineEdit_2->setText("无借书份额，请先还书！");
        ui->pushButton->hide();
      }
    else if(!mainreader->GetState())
      {
        ui->lineEdit_2->setStyleSheet("color:red");//文本颜色
        ui->lineEdit_2->setText("请先交罚款！");
        ui->pushButton->show();
      }
    else
      {
        ui->lineEdit_2->setStyleSheet("color:green");//文本颜色
        ui->lineEdit_2->setText("可以借书");
        ui->pushButton->hide();
      }
      */
}

Home::~Home()
{
    delete ui;
}


void Home::on_btn_ok_clicked()
{
    int row = ui-> tableView_1 ->currentIndex().row();//获得当前行索引
    if(row!= -1)
      {
        QModelIndex index = model1->index(row,0);
        QString id = model1->data(index).toString();
        qDebug() << id;
        Reservation r1 = mainbs.bookFlight(id.toStdString(), mainpassenger);
        Ticket t1 = mainbs.generateTicket(r1);
        QMessageBox *msgbox = new QMessageBox(this);
        msgbox->information(this,"提示","订票成功！");
        int i = 0;
        model1->removeRows(0,model1->rowCount());//清除
        model2->removeRows(0,model2->rowCount());//清除
        for(Flight b : mainbs.getFlights()) {
              showbookline1(b,i++);
            }
        i = 0;
        for(Ticket t : mainbs.findPassengerTickets(mainpassenger.idNumber)) {
              qDebug() << "test" <<QString::fromStdString(t.flightNumber);
              Flight b = mainbs.getFlightInfo(t.flightNumber);
              showbookline2(b,i++);
            }
        /*
        if(book0->GetBookLeftnum() == 0)
          {
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","无剩余书籍！");
          }
        else if(mainreader->GetNumber() == 0)
        {
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","无借书份额，请先还书！");
        }else if(!mainreader->GetState())
          {//qDebug()<<mainreader->GetState();
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","请先交罚款！");
          }
        else
          {
            mainreader->BorrowBook(id.toStdString());
            mainreader->CheckRecord();
            QMessageBox *msgbox = new QMessageBox(this);
            msgbox->information(this,"提示","订票成功！");
            int i = 0;
            model1->removeRows(0,model1->rowCount());//清除
            model2->removeRows(0,model2->rowCount());//清除
            for(Flight b : mainbs.getFlights()) {
                  showbookline1(b,i++);
                }
            i = 0;
            for(Ticket t : mainbs.findPassengerTickets(mainpassenger.idNumber)) {
                  Flight b = mainbs.getFlightInfo(t.flightNumber);
                  showbookline2(b,i++);
                }
            save();
          }
          */

      }
}



void Home::on_btn_back_clicked()
{
    int row = ui-> tableView_2 ->currentIndex().row();//获得当前行索引
    if(row != -1)
      {
        QModelIndex index = model2->index(row,0);
        QString id = model2->data(index).toString();
        for(Ticket t : mainbs.findPassengerTickets(mainpassenger.idNumber)) {
              if (t.flightNumber == id.toStdString())
                {
                  if (mainbs.cancelTicket(t.ticketNumber))
                    {
                      qDebug() << "yes";
                        break;
                    }

                }
            }
        QMessageBox *msgbox = new QMessageBox(this);
        msgbox->information(this,"提示","退票成功！");
        int i = 0;
        model1->removeRows(0,model1->rowCount());//清除
        model2->removeRows(0,model2->rowCount());//清除
        for(Flight b : mainbs.getFlights()) {
              showbookline1(b,i++);
            }
        i = 0;
        for(Ticket t : mainbs.findPassengerTickets(mainpassenger.idNumber)) {
              Flight b = mainbs.getFlightInfo(t.flightNumber);
              showbookline2(b,i++);
            }
        save();
        }
}

void Home::on_btn_all_clicked()
{
  int i = 0;
    model1->removeRows(0,model1->rowCount());//清除
    for(Flight b : mainbs.getFlights()) {
          showbookline1(b,i++);
        }
}

void Home::on_btn_search_clicked()
{
    model1->removeRows(0,model1->rowCount());//清除
    int index=0, i = 0;
    if(index == 0)
      {
        qDebug() << ui->lineEdit->text() << ui->lineEdit_3->text();
          string start = ui->lineEdit_3->text().toStdString();
          string end = ui->lineEdit->text().toStdString();
          for(Flight b : mainbs.findFlights(start, end)) {
                showbookline1(b,i++);
              }
            }
}


void Home::showbookline1(Flight b, int i)
{
  model1->setItem(i,0,new QStandardItem(QString::fromStdString(b.getFlightNumber())));
  model1->setItem(i,1,new QStandardItem(QString::fromStdString(b.getDepartureAirport())));
  model1->setItem(i,2,new QStandardItem(QString::fromStdString(b.getArrivalAirport())));
  model1->setItem(i,3,new QStandardItem(QString::fromStdString(b.getDepartureTime())));
  model1->setItem(i,4,new QStandardItem(QString::fromStdString(b.getArrivalTime())));
  model1->setItem(i,5,new QStandardItem(QString::number(b.price)));
  model1->setItem(i,6,new QStandardItem(QString::number(b.getAvailableSeats())));
  //model1->setItem(i,7,new QStandardItem(QString::number(b->GetBookTotalnum())));
  //qDebug()<<QString::fromStdString(b.GetBookID())<<QString::fromStdString(b.GetBookName())<<QString::fromStdString(b.GetBookWriter())<<QString::fromStdString(b.GetBookPublisher())<<QString::fromStdString(b.GetBookField());
}

void Home::showbookline2(Flight b, int i)
{
  model2->setItem(i,0,new QStandardItem(QString::fromStdString(b.getFlightNumber())));
  model2->setItem(i,1,new QStandardItem(QString::fromStdString(b.getDepartureAirport())));
  model2->setItem(i,2,new QStandardItem(QString::fromStdString(b.getArrivalAirport())));
  model2->setItem(i,3,new QStandardItem(QString::fromStdString(b.getDepartureTime())));
  model2->setItem(i,4,new QStandardItem(QString::fromStdString(b.getArrivalTime())));
  model2->setItem(i,5,new QStandardItem(QString::number(b.price)));
  //model2->setItem(i,6,new QStandardItem(rdata));
  //model2->setItem(i,7,new QStandardItem(QString::number(b->GetNo())));
  ui->tableView_2->setColumnHidden(7,true);

}

void Home::on_btn_exit_clicked()
{
    this->close();
    library* lab = new library;
    lab->show();
}

void Home::on_lineEdit_returnPressed()
{
    on_btn_search_clicked();
}


void Home::on_pushButton_clicked()
{
  /*
    mainreader->pay();
    for(auto i = mainreader->GetRecord().begin();i!=mainreader->GetRecord().end(); i++) { i->CheckRecord(); }
    mainreader->CheckRecord();
    save();
    ui->pushButton->hide();
    for(auto i = mainreader->GetRecord().begin();i!=mainreader->GetRecord().end(); i++) { i->CheckRecord(); }
    mainreader->CheckRecord();
    if(mainreader->GetNumber() == 0)
      {
        ui->lineEdit_2->setStyleSheet("color:red");//文本颜色
        ui->lineEdit_2->setText("无借书份额，请先还书！");
        ui->pushButton->hide();
      }
    else if(!mainreader->GetState())
      {
        ui->lineEdit_2->setStyleSheet("color:red");//文本颜色
        ui->lineEdit_2->setText("请先交罚款！");
        ui->pushButton->show();
      }
    else
      {
        ui->lineEdit_2->setStyleSheet("color:green");//文本颜色
        ui->lineEdit_2->setText("可以借书");
        ui->pushButton->hide();
      }
    model1->removeRows(0,model1->rowCount());//清除
    model2->removeRows(0,model2->rowCount());//清除
    int line = 0;
    for(Book &b : Manager::booklist) {
          showbookline1(&b,line++);
        }
    line = 0;
    for(Bookrecord &b : mainreader->GetRecord()) {
          showbookline2(&b,line++);
        }
    QMessageBox *msgbox = new QMessageBox(this);
    msgbox->information(this,"提示","还款成功！");
*/
}
