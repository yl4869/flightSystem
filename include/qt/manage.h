#ifndef MANAGE_H
#define MANAGE_H

#include <QWidget>
#include "newbook.h"
#include "register_qt.h"
#include <QStandardItemModel>
#include <QDebug>
#include "re_book.h"
#include "re_account.h"
#include "re_admin.h"
#include "library.h"
#include "bookingsystem.hpp"
namespace Ui {
class Manage;
}

class Manage : public QWidget
{
    Q_OBJECT

public:
    explicit Manage(QWidget *parent = nullptr);
    ~Manage();
    void showbookline3(Flight b,int i);
    void showreaderline4(Passenger b,int i);
    //void showadminline5(Ladmin* b,int i);
    QStandardItemModel* model3;
    QStandardItemModel* model4;
    QStandardItemModel* model5;

private slots:
    void on_btn_add_clicked();

    void on_btn_add_2_clicked();

    void on_btn_re_book_clicked();

    void on_btn_deletebook_clicked();

    void on_btn_search_2_clicked();

    void on_btn_all_2_clicked();

    void on_btn_re_account_clicked();

    void on_btn_all_3_clicked();

    void on_btn_search_3_clicked();

    void on_btn_deleteaccount_clicked();

    void on_btn_addman_clicked();

    void on_btn_reman_clicked();

    void on_btn_deleteman_clicked();

    void on_btn_search_clicked();

    void on_btn_all_clicked();


    void on_btn_exit_clicked();

    void on_lineEdit_2_returnPressed();

    void on_lineEdit_4_returnPressed();

    void on_lineEdit_returnPressed();

private:
    Ui::Manage *ui;

};

#endif // MANAGE_H
