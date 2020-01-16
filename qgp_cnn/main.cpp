#include <QCoreApplication>
#include <channel.h>
#include <kernel.h>
#include <dataloader.h>
#include <filter.h>

#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <QtDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
    Channel myChan(20, 20, 20);
    // myChan.cell(0,0,0) = -1;
    myChan.pad();
    myChan.printContent();
    */

    /*
    Kernel myKern(2);
    myKern.printContent();
    myKern.reset();
    myKern.printContent();
    */


    DataLoader myLoader;
    myLoader.loadBatch();


    /*
    Filter myFilter(1);
    myFilter.printContent();
    */

    return a.exec();
}
