#ifndef CHANNEL_H
#define CHANNEL_H

#include <filter.h>

#include <QVector>
#include <iostream>
#include <QtDebug>

using namespace std;

class Channel
{
public:
    /* Creates a channel with the dimensions 'zDim' 'yDim' 'xDim' represented as a 3d QVector. Initially filled with zeros.
    * Sets every position of 'shape' to one of the three passed dimensions of the channel ('zDim', 'yDim' and 'xDim'). */
    Channel(int zDim=20, int yDim=20, int xDim=20);

    Channel operator + (Channel const &obj);

    /* Runs every value in content through the lRelu activation function. */
    void activate();

    /* Applies filter to the channel and returns the resulting channel. */
    Channel applyFilter(Filter filter);

    /* Returns reference to the 'content' property. */
    QVector<QVector<QVector<double> > >& contentRef();

    /* Returns reference to a cell in 'content' selected by z, y and x coordinates. */
    double& cell(int z, int y, int x);

    /* Sets every cell of 'content' to 0 */
    void clear();

    /* Fills the channel with data. Deletes the first zDim*yDim*xDim elements of the input list.
     * Sets 'filled' to true. */
    void fill(QVector<int> &data);

    /* Pads the channel with one layer of zeros. Increasing its width, height, and depth by 2.
     * Adds 2 to every position of 'shape' and sets 'padded' to true. Does not pad if 'padded' is true.
     * Does not pad if Channel is not yet filled with data. */
    void pad();

    /* Prints 'content' to the console in a structured manner. */
    void printContent();

    /* Indicates whether or not this channel has been padded. */
    bool padded = false;

    /* Indicates whether or not this channel has been filled with data. */
    bool filled = false;

    /* Contains dimensions passed in the constructor.
     * shape[0]=zDim; shape[1]=yDim; shape[2]=xDim */
    int shape [3];

private:

    /* Contains the channel's cells in a 3-dimensional array. */
    QVector<QVector<QVector<double> > > content;

    /* Leaky ReLU activation function. */
    double lRelu(double x);
};

#endif // CHANNEL_H
