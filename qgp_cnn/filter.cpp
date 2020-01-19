#include "filter.h"


Filter::Filter(int nChannels, int size)
{
    nBins = size * size * size;
    content = QVector< QVector<QVector<double>> >(size, QVector<QVector<double>>(size, QVector<double>(size, 0.0)) );
    // mt19937 tempSeed(time(NULL));
    // reset(nChannels, tempSeed);
}

void Filter::reset(int nChannels, mt19937 seed)
{
    mt19937 gen(time(NULL)); // mersenne_twister_engine seeded with rd()
    uniform_real_distribution<double> dist(-1.0, 1.0);

    for (QVector<QVector<double>>& z : content) {
        for (QVector<double>& y : z){
            for (double& x : y){
                x = dist(gen) * (1/sqrt(nChannels*nBins));
            }
        }
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
                cout << x << " ";
                /*
                if (x < 0) {
                    printf("%.2f ", x);
                } else {
                    printf(" %.2f ", x);
                }
                */
            }
            cout << "\n";
        }
        cout << "\n";
    }
}
