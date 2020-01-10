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
    /*  */
    Kernel(int zDim=3, int yDim=3, int xDim=3);
    void reset();
    void printContent();

    QVector<QVector<QVector<double>>> content;
    int shape [3];
    int nChannels = 28;
    int nBins;


private:
    double doubleRand();


};

#endif // KERNEL_H
