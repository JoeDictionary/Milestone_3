#ifndef CONV3D_H
#define CONV3D_H

#include "object3d.h"
#include "filter.h"

class Conv3D
{
public:
    Conv3D();
    Conv3D(int,int);
    QVector<object3D*> forward(QVector<object3D*>);
    QVector<object3D*> backward(QVector<object3D*>);

    QVector<QVector<Filter*>> filterSets;

    double lRelu(double);
    double lReluDeriv(double);

    int nChannels;
    int nKernels;
    QVector<object3D*> cachedChannelCollection;
};

#endif // CONV3D_H
