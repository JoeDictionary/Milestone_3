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
    Filter(int,int,int);
    Filter(int nChannels, int size=3);

    /* Contains the weights of the filter. */
    QVector<QVector<QVector<double>>> content;

    /* Returns reference to a cell in 'content' selected by z, y and x coordinates. */
    double& cell(int z, int y, int x);

    /* Returns reference to the content property. */
    QVector<QVector<QVector<double>>>& contentRef();

    void reset(int nChannels, mt19937 seed);

    void printContent();

private:
    int nBins;

    mt19937* randSeed;
};

#endif // FILTER_H
