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


    // Also amount of output channels.
    int kernelAmount = 32;

    int filterAmount = 28;
    QVector<Kernel> kernelArray = QVector<Kernel>(kernelAmount, Kernel(filterAmount, kernelAmount));
    // qDebug() << kernelArray.size();
    for (Kernel i : kernelArray) {
        for (Filter j : i.content) {
            j.reset(32);
        }
    }

    kernelArray[0].printContent();

    /*
    Kernel myKern(2);
    myKern.printContent();
    // myKern.reset();
    // myKern.printContent();
    */

    /*
    Filter myFilter(28);

    DataLoader myLoader;
    myLoader.loadBatch();
    QVector<int> data = myLoader.convertStringData();

    myChan.fill(data);
    myChan.pad();
    // myChan.printContent();
    (myChan.applyFilter(myFilter)).printContent();
    */

    return a.exec();
}
