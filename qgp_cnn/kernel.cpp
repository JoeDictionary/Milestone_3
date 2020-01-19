#include "kernel.h"


Kernel::Kernel(int filterAmount,int channels,mt19937 seed, int filtSize)
{
    // Shape of the filters in the kernel.
    filterSize = filtSize;
    // Kernel size is the amount of filters in that kernel.
    kernelSize = filterAmount;
    nBins = filterSize * filterSize * filterSize;
    nChannels = channels;
    randSeed = seed;

    srand(static_cast<unsigned int>(clock()));

    // Sets content to an array of 'filterAmount' filters.
    content = QVector<Filter>(filterAmount, Filter(nChannels,filtSize));
    reset();
}

void Kernel::reset()
{
    for (Filter& filter : content) {
        filter.reset(nChannels, randSeed);
    }
}

void Kernel::printContent()
{
    int counter = 0;

    for (Filter filter : content) {
        cout << "Filter " << ++counter << "\n";
        filter.printContent();
        cout << "\n";
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
