#include "kernel.h"

/* Creates a 3D kernel with the dimensions zDim, yDim, xDim which is stored in 'content'. Initiates the weights randomly.
 * Sets every position of 'shape' to one of the three passed dimensions of the kernel. */
Kernel::Kernel(int filterAmount, int zDim, int yDim, int xDim)
{
    // Shape of every filter in the kernel.
    filterShape[0] = zDim; filterShape[1] = yDim; filterShape[2] = xDim;
    // Kernel size is the amount of filters in that kernel.
    kernelSize = filterAmount;

    nBins = zDim * yDim * xDim;

    // Sets content to an array of 'filterAmount' 'zDim'*'yDim'*'xDim'-filters.
    content =  QVector< QVector<QVector<QVector<double>>> >(filterAmount, QVector<QVector<QVector<double>>>(zDim, QVector<QVector<double>>(yDim, QVector<double>(xDim, 0.0))) );

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
        for (QVector<QVector<double>> z : filter) {
            cout << "\n\n";
            cout << "Filter" << ++counter;
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
