#ifndef KERNEL_H
#define KERNEL_H

#include <filter.h>

#include <QVector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

class Kernel
{
public:
    /* Initializes 'filter_amount' 3D-filters with the specified size 'filtSize'
     * inside the kernel and sets their weights randomly. */
    Kernel(int filter_amount, int filtSize=3);

    /* Sets weights of filters to random values. */
    void reset();

    /* Prints every filter of in content to the console. */
    void printContent();

    /* Contains content of the kernel object. */
    QVector< QVector<QVector<QVector<double>>> > content;

    /*  */
    int filterSize;

    /*  */
    int kernelSize;

    int nBins;


private:
    double doubleRand();


};

#endif // KERNEL_H
