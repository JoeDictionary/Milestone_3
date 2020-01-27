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
    Kernel(int filter_amount, int channels, mt19937 seed,int filtSize=3);

    /* Sets weights of filters to random values. */
    void reset();

    /* Prints every filter of in content to the console. */
    void printContent();

    /* Contains filters of the kernel. */
    QVector<Filter> content;

    /* Dimension of the depth, width and height of the filters. */
    int filterSize;

    /* Amount of filters in the kernel. */
    int kernelSize;

    /* 'filterSize' to the power of 3. */
    int nBins;

    /* Amount of total kernels in the "kernel-group" this kernel is in. */
    int nChannels;

    double bias = 1;

private:

    mt19937 randSeed;
};

#endif // KERNEL_H
