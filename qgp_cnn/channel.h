#ifndef CHANNEL_H
#define CHANNEL_H

#include <QVector>
#include <iostream>

using namespace std;

class Channel
{
public:
    Channel(int zDim, int yDim, int xDim);
    double& cell(int z, int y, int x);
    void clear();
    void activate();
    void pad();
    void printContent();

    int shape [3];
    QVector<QVector<QVector<double>>> content;

private:
    double lRelu(double x);
};

#endif // CHANNEL_H
