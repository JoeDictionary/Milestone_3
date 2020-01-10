#ifndef CHANNEL_H
#define CHANNEL_H

#include <QVector>
#include <iostream>

using namespace std;

class Channel
{
public:
    /* Creates a channel with the dimensions 'zDim' 'yDim' 'xDim' represented as a 3d QVector. Initially filled with zeros.
    * Sets every position of 'shape' to one of the three passed dimensions of the channel ('zDim', 'yDim' and 'xDim'). */
    Channel(int zDim, int yDim, int xDim);

    /* Returns reference to a cell in 'content' selected by z, y and x coordinates. */
    double& cell(int z, int y, int x);

    /* Sets every cell of 'content' to 0 */
    void clear();

    /* Runs every value in content through the lRelu activation function. */
    void activate();

    /* Pads the channel with one layer of zeros. Increasing its width, height, and depth by 2.
     * Adds 2 to every position of 'shape' and sets 'padded' to true. Does not pad if 'padded' is true. */
    void pad();

    /* Prints 'content' to the console in a structured manner. */
    void printContent();

    /* Contains dimensions passed in the constructor.
     * shape[0]=zDim; shape[1]=yDim; shape[2]=xDim */
    int shape [3];

    /* Returns reference to the 'content' property. */
    QVector<QVector<QVector<double>>>& contentRef();

    /* Indicates whether or not this channel has been padded. */
    bool padded = false;

private:

    /* Contains the channel's cells in a 3-dimensional array. */
    QVector<QVector<QVector<double>>> content;

    /* Leaky ReLU activation function. */
    double lRelu(double x);
};

#endif // CHANNEL_H
