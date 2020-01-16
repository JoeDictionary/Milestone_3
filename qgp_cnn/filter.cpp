#include "filter.h"


Filter::Filter(int nChannels, int nBins, int size)
{
    content = QVector< QVector<QVector<double>> >(size, QVector<QVector<double>>(size, QVector<double>(size, 0.0)) );
    reset(nChannels, nBins);
}

void Filter::reset(int nChannels, int nBins)
{
    srand(static_cast<unsigned int>(clock()));

    for (QVector<QVector<double>>& z : content) {
        for (QVector<double>& y : z){
            for (double& x : y){
                x = doubleRand() * (1/sqrt(nChannels*nBins));
            }
        }
    }
}

double Filter::doubleRand()
{
    // If 'plusMinus' < 0.5 the random value is positive otherwise it is negative.
    float plusMinus = double(rand()) / (double(RAND_MAX) + 1.0);

    if (plusMinus < 0.5){
      return double(rand()) / (double(RAND_MAX) + 1.0);
    } else {
      return -(double(rand()) / (double(RAND_MAX) + 1.0));
    }
}

double &Filter::cell(int z, int y, int x)
{
    return content[z][x][y];
}

QVector<QVector<QVector<double> > > &Filter::contentRef()
{
    return content;
}

void Filter::printContent()
{
    for (QVector<QVector<double>> z : content) {
        for (QVector<double> y : z) {
            for (double x : y){
                // cout << x << " ";
                if (x < 0) {
                    printf("%.2f ", x);
                } else {
                    printf(" %.2f ", x);
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
}
