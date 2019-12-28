#include "kernel.h"

Kernel::Kernel(int zDim, int yDim, int xDim)
{
    nBins = zDim * yDim * xDim;

    shape[0] = zDim; shape[1] = yDim; shape[2] = xDim;
    content = QVector<QVector<QVector<double>>>(zDim, QVector<QVector<double>>(yDim, QVector<double>(xDim, 0.0) ));
    srand(static_cast<unsigned int>(clock()));
    reset();

}

void Kernel::reset()
{
    for (QVector<QVector<double>>& z : content) {
        for (QVector<double>& y : z) {
            for (double& x : y){
                x = doubleRand() * (1/sqrt(nChannels*nBins));
            }
        }
    }
}

void Kernel::printContent()
{
    for (QVector<QVector<double>> z : content) {
        cout << "\n";
        for (QVector<double> y : z) {
            cout << "\n";
            for (double x : y){
                cout << x << " ";
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
