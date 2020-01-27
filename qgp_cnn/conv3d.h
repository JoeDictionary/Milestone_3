#ifndef CONV3D_H
#define CONV3D_H

#include <dataloader.h>
#include <kernel.h>
#include <channel.h>

#include <random>


class Conv3D
{
public:
    Conv3D(int filterAmount, int outputChannelAmount, DataLoader loader, mt19937 seed);

    QVector<Kernel> kernelArray;

    QVector<Channel> inputChannels;

    QVector<Channel> outputChannels;


};

#endif // CONV3D_H
