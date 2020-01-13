#ifndef KERNEL_H
#define KERNEL_H

#include <QVector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

class Kernel
{
public:
    /* Initializes 'filter_amount' filters with the specified dimensions (zDim, yDim and xDim)
     * and sets their weights randomly. */
    Kernel(int filter_amount, int zDim=3, int yDim=3, int xDim=3);

    /* Sets weights of filters to random values. */
    void reset();

    /* Prints every filter of in content to the console. */
    void printContent();

    /* Contains content of the kernel object. */
    QVector< QVector<QVector<QVector<double>>> > content;

    /*  */
    int filterShape [3];

    /*  */
    int kernelSize;

    int nBins;


private:
    double doubleRand();


};

#endif // KERNEL_H
