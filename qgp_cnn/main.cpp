#include <QCoreApplication>
#include <channel.h>
#include <kernel.h>
#include <dataloader.h>

#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <QtDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Channel myChan(5, 5, 5);
    // myChan.cell(0,0,0) = -1;
    /*
    myChan.pad();
    myChan.printContent();
    */
    Kernel myKern(4);
    myKern.printContent();
    qDebug() << myKern.content.size();
    // qDebug() << myKern.kernelSize;
    // myChan.printContent();

    DataLoader myLoader;
    myLoader.loadBatch();


    return a.exec();
}
