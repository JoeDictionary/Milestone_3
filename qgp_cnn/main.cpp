#include <QCoreApplication>
#include <channel.h>
#include <kernel.h>
#include <dataloader.h>
#include <filter.h>
#include <conv3d.h>

#include <random>
#include <time.h>
#include <QDebug>
#include <QtDebug>

// Home: "C:/Users/filip/Desktop/PROGRAMMING/dataset_half/qgp"
// Laptop: "C:/Users/Filip/Desktop/dataset_half/qgp"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int filterAmount = 28;
    int kernelAmount = 32;
    mt19937 gen(1834989023784); // mersenne_twister_engine seeded with rd()

    /*
    uniform_real_distribution<double> disOne(-1.0, 1.0);
    // QVector<Kernel> kernelArray = QVector<Kernel>(kernelAmount, Kernel(filterAmount, kernelAmount, gen));
    Kernel kernelArray(filterAmount, kernelAmount, gen, 3);
    kernelArray.printContent();
    Kernel myKernel(28, 32, gen);
    */

    DataLoader myLoader("C:/Users/filip/Desktop/PROGRAMMING/dataset_half/qgp", "C:/Users/filip/Desktop/PROGRAMMING/dataset_half/nqgp");
    // myLoader.loadBatch();

    Channel myChan(5, 5, 5);
    Channel otherChan(3, 3, 3);
    // myChan.printContent();
    // (myChan + otherChan).printContent();

    // Conv3D myConv(28, 1, myLoader, gen);
    // myConv.kernelArray[0].printContent();
    Kernel myKernel(28, 2, gen);
    myKernel.printContent();

    return a.exec();
}
