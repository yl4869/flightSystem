#ifndef CPP_RE_H
#define CPP_RE_H

#include <QWidget>
#include <string>
#include "bookingsystem.hpp"
#include "file.hpp"
#include <string>
#include <ctime>
#include <iostream>
using namespace std;
extern BookingSystem mainbs;
extern Passenger mainpassenger;
extern File mainf;
class Cpp_re : public QWidget
{
  Q_OBJECT
public:
  explicit Cpp_re(QWidget *parent = nullptr);

signals:

};
void save();
#endif // CPP_RE_H
