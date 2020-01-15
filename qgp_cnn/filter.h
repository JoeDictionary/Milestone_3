#ifndef FILTER_H
#define FILTER_H

#include <cstdlib>
#include <ctime>
#include <random>
#include <QVector>
#include <iostream>

using namespace std;

class Filter
{
public:
    Filter(int nChannels, int size=3, int nBins=27);

    /* Contains the weights of the filter. */
    QVector<QVector<QVector<double>>> content;

    /* Genrates a random weight for the filter. */
    double doubleRand();

    /* Returns reference to a cell in 'content' selected by z, y and x coordinates. */
    double& cell(int z, int y, int x);

    /* Returns reference to the content property. */
    QVector<QVector<QVector<double>>>& contentRef();

    void reset(int nChannels, int nBins=27);

    void printContent();

};

#endif // FILTER_H