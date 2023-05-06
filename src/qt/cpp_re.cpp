#include "cpp_re.h"

BookingSystem mainbs;
Passenger mainpassenger;
File mainf;
Cpp_re::Cpp_re(QWidget *parent) : QWidget(parent)
{

}


void save()
{

  mainf.FlushSystem(mainbs);

}


