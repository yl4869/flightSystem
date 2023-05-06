#include "library.h" 
#include <QApplication>
#include "QFile"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    library w;
    mainf.Init();
    mainf.LoadSystem(mainbs);
    qDebug() << mainbs.passengers.size() << QString::fromStdString(mainbs.passengers[0].idNumber);
    //qDebug() << mainbs.tickets.size();
    w.show();
    return a.exec();
}
