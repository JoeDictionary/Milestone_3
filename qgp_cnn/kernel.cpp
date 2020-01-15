#include "kernel.h"


Kernel::Kernel(int filterAmount, int filtSize)
{
    // Shape of every filter in the kernel.
    filterSize = filtSize;
    // Kernel size is the amount of filters in that kernel.
    kernelSize = filterAmount;

    nBins = filterSize * filterSize * filterSize;

    // Sets content to an array of 'filterAmount' filters.
    content =  QVector< QVector<QVector<QVector<double>>> >( filterAmount, QVector<QVector<QVector<double>>>(filterSize, QVector<QVector<double>>(filterSize, QVector<double>(filterSize, 0.0))) );

    srand(static_cast<unsigned int>(clock()));
    reset();
}

void Kernel::reset()
{
    for (QVector<QVector<QVector<double>>>& filter : content) {
        for (QVector<QVector<double>>& z : filter) {
            for (QVector<double>& y : z) {
                for (double& x : y){
                    x = doubleRand() * (1/sqrt(kernelSize*nBins));
                }
            }
        }
    }
}

void Kernel::printContent()
{
    int counter = 0;

    for (QVector<QVector<QVector<double>>> filter : content) {
        cout << "\n\nFilter" << ++counter;
        for (QVector<QVector<double>> z : filter) {
            cout << "\n";
            for (QVector<double> y : z) {
                cout << "\n";
                for (double x : y){
                    // cout << x << " ";

                    if (x < 0) {
                        printf("%.2f ", x);
                    } else {
                        printf(" %.2f ", x);
                    }
                }
            }
        }
    }
}

double Kernel::doubleRand()
{
    float plusMinus = double(rand()) / (double(RAND_MAX) + 1.0);
    if (plusMinus < 0.5){
      return double(rand()) / (double(RAND_MAX) + 1.0);
    } else {
      return -(double(rand()) / (double(RAND_MAX) + 1.0));
    }
}
