#include <QCoreApplication>
#include <channel.h>
#include <kernel.h>
#include <dataloader.h>
#include <filter.h>

#include <random>
#include <time.h>
#include <QDebug>
#include <QtDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    uniform_real_distribution<double> disOne(-1.0, 1.0);
    mt19937 gen(123412446686); // mersenne_twister_engine seeded with rd()

    // QVector<Kernel> kernelArray = QVector<Kernel>(kernelAmount, Kernel(filterAmount, kernelAmount, gen));
    // kernelArray[0].printContent();
    // Kernel myKernel(28, 32, gen);

    QVector<int> testInput = QVector<int>(27, 1.0);
    Filter myFilter(28);
    myFilter.reset(1, gen);
    myFilter.printContent();

    Channel myChannel(3, 3, 3);
    myChannel.fill(testInput);
    myChannel.pad();
    myChannel.applyFilter(myFilter).printContent();

    /*
    DataLoader myLoader;
    myLoader.loadBatch();
    QVector<int> data = myLoader.convertStringData();

    Filter myFilter(28);

    Channel myChan;
    myChan.fill(data);
    myChan.pad();
    (myChan.applyFilter(myFilter)).printContent();
    */

    return a.exec();
}
