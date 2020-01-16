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

    Channel myChan(20, 20, 20);

    /*
    // myChan.cell(0,0,0) = -1;
    myChan.pad();
    myChan.printContent();
    */

    /*
    Kernel myKern(2);
    myKern.printContent();
    // myKern.reset();
    // myKern.printContent();
    */

    Filter myFilter(28);

    DataLoader myLoader;
    myLoader.loadBatch();
    QVector<int> data = myLoader.convertStringData();

    myChan.fill(data);
    myChan.pad();

    myChan.applyFilter(myFilter);

    return a.exec();
}
