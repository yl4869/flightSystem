#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDebug>
#include "library.h"
#include "manage.h"
#include "bookingsystem.hpp"
namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:

    explicit Home(QWidget *parent = nullptr);
    ~Home();
    void showbookline1(Flight b, int i);
    void showbookline2(Flight b, int i);

private slots:

    void on_btn_ok_clicked();


    void on_btn_back_clicked();

    void on_btn_all_clicked();

    void on_btn_search_clicked();

    void on_btn_exit_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();


private:
    Ui::Home *ui;
    QStandardItemModel* model1;
    QStandardItemModel* model2;

};

#endif // HOME_H
