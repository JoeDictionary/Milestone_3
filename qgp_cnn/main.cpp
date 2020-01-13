#include <QCoreApplication>
#include <channel.h>
#include <kernel.h>
#include <QDebug>

#include <cstdlib>
#include <ctime>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Channel myChan(5, 5, 5);
    // myChan.cell(0,0,0) = -1;
    /*
    myChan.pad();
    myChan.printContent();
    */
    Kernel myKern(3, 3, 3);
    myKern.printContent();
    // myChan.printContent();

    return a.exec();
}
