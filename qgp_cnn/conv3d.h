#ifndef CONV3D_H
#define CONV3D_H

#include <dataloader.h>


class Conv3D
{
public:
    Conv3D(int FilterAmount, int outputChannelAmount, DataLoader loader);
};

#endif // CONV3D_H
