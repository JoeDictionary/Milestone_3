#include "conv3d.h"

Conv3D::Conv3D(int filterAmount, int outputChannelAmount, DataLoader loader, mt19937 seed)
{
    kernelArray = QVector<Kernel>(outputChannelAmount, Kernel(filterAmount, outputChannelAmount, seed));

    for (Kernel i : kernelArray) {
        i.reset();
    }
}
