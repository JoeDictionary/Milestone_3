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

    int filterAmount = 28;
    int kernelAmount = 32;

    uniform_real_distribution<double> disOne(-1.0, 1.0);
    mt19937 gen(time(NULL)); // mersenne_twister_engine seeded with rd()

    // QVector<Kernel> kernelArray = QVector<Kernel>(kernelAmount, Kernel(filterAmount, kernelAmount, gen));
    Kernel kernelArray(filterAmount, kernelAmount, gen, 3);
    kernelArray.printContent();
    Kernel myKernel(28, 32, gen);

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
