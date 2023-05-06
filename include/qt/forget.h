#ifndef FORGET_H
#define FORGET_H

#include <QWidget>
#include "library.h"
namespace Ui {
class forget;
}

class forget : public QWidget
{
    Q_OBJECT

public:
    explicit forget(QWidget *parent = nullptr);
    ~forget();

private slots:

    void on_btn_register_2_clicked();

private:
    Ui::forget *ui;
};

#endif // FORGET_H
