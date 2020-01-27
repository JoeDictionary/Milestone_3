#ifndef MAXPOOL3D_H
#define MAXPOOL3D_H

#include "object3d.h"

class MaxPool3D
{
public:
    MaxPool3D();
    MaxPool3D(int);
    QVector<object3D*> forward(QVector<object3D*>);
    QVector<object3D*> backward(QVector<object3D*>);
    QVector<object3D*> cache;
    int stride=1;

    int dimX;
    int dimY;
    int dimZ;
};

#endif // MAXPOOL3D_H
