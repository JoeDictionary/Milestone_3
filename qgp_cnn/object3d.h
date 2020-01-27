#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QVector>

class object3D
{
public:
    object3D();

    QVector<QVector<QVector<double>>> data;
    QVector<QVector<QVector<QVector<int>>>> coordinates;
};

#endif // OBJECT3D_H
