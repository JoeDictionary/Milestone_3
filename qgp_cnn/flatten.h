#ifndef FLATTEN_H
#define FLATTEN_H

#include "object3d.h"
#include <QVector>

class Flatten
{
public:
    Flatten();
    QVector<double> forward(QVector<object3D*>);
    QVector<object3D*> backward(QVector<double>);

    int dimX;
    int dimY;
    int dimZ;

    int channel_count;
};

#endif // FLATTEN_H
