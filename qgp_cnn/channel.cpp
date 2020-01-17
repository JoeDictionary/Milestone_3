#include "channel.h"

Channel::Channel(int zDim, int yDim, int xDim)
{
    shape[0] = zDim; shape[1] = yDim; shape[2] = xDim;

    // Creates a 3d QVector withe the dimensions zDim, yDim, xDim filled with zeros and assigns that QVector to 'content'.
    content = QVector<QVector<QVector<double>>>(zDim, QVector<QVector<double>>(yDim, QVector<double>(xDim, 0)));
}

double &Channel::cell(int z, int y, int x)
{
    return content[z][y][x];
}

void Channel::clear()
{
    for (QVector<QVector<double>>& z : content) {
        for (QVector<double>& y : z) {
            for (double& x : y){
                x = 0;
            }
        }
    }
}

void Channel::activate()
{
    for (QVector<QVector<double>>& z : content){
        for (QVector<double>& y : z){
            for (double& x : y){
                x = lRelu(x);
            }
        }
    }
}

Channel Channel::applyFilter(Filter filter)
{
    if (!padded) {
        qDebug() << "(applyFilter) Channel not padded";
        return NULL;
    }
    Channel output;

    //  Channel dimensions without counting padding.
    int zDim = shape[0]-2; int yDim = shape[1]-2; int xDim = shape[2]-2;

    qDebug() << "(applyFilter) zDim: " << zDim;
    qDebug() << "(applyFilter) yDim: " << yDim;
    qDebug() << "(applyFilter) xDim: " << xDim;

    // The next 3 for-loops iterate through every possible filter-position in the channel.
    // zPos, yPos, xPos are the coordinates of the current position of the filter.
    for (int zPos=1; zPos < zDim; zPos++) {
        for (int yPos=1; yPos < yDim; yPos++) {
            for (int xPos=1; xPos < xDim; xPos++) {
                int zMin = zPos-1; int yMin = yPos-1; int xMin = xPos-1;
                int zFilter = 0; int yFilter = 0; int xFilter = 0;

                /*
                qDebug() << "(applyFilter) zMin: " << zMin;
                qDebug() << "(applyFilter) yMin: " << yMin;
                qDebug() << "(applyFilter) xMin: " << xMin;
                */

                // Sum of of one filter iteration.
                double filterSum = 0;

                // The next 3 for-loops iterate through every cell of channel currently covered by the filter at the coordinates zPos, yPos, xPos (Position).
                // z, y, x are the coordinates of one of the cells covered by the filter.
                // zFilter, yFilter, xFilter are coordinates of the 'filter' cells and oterate through every cel in 'filter'
                for (int z = zMin; z < zMin+2; z++){
                    yFilter = 0;
                    for (int y = yMin; y < yMin+2; y++){
                        xFilter = 0;
                        for (int x = xMin; x < xMin+2; x++){
                            /*
                            qDebug() << "(applyFilter) z: " << z;
                            qDebug() << "(applyFilter) y: " << y;
                            qDebug() << "(applyFilter) x: " << x;
                            */

                            filterSum += content[z][y][x] * filter.content[zFilter][yFilter][xFilter];
                            ++xFilter;
                        }
                        ++yFilter;
                    }
                    ++zFilter;
                }
                // 'filterSum' has the same position in 'output' as the filter-position at the time of that iteration.
                output.content[zPos][yPos][xPos] = filterSum;
            }
        }
    }
    return output;
}

void Channel::pad()
{
    if (padded){
        cout << "\nAlready padded!";
        return;
    }

    for (QVector<QVector<double>>& plane : content){
        plane.insert(0, 1, QVector<double>(shape[2], 0));
        plane.push_back(QVector<double>(shape[2], 0));
        for (QVector<double>& row : plane){
            row.insert(0, 1, 0);
            row.push_back(0);
        }
    }

    content.insert(0, 1,
                   QVector<QVector<double>>(shape[1]+2, QVector<double>(shape[2]+2, 0) ) );
    content.push_back(QVector<QVector<double>>(shape[1]+2, QVector<double>(shape[2]+2, 0) ) );

    padded = true;
    shape[0] += 2; shape[1] += 2; shape[2] += 2;
}



/* Prints every cell of 'content' to the console. */
void Channel::printContent()
{
    for (QVector<QVector<double>> z : content) {
        cout << "\n";
        for (QVector<double> y : z) {
            cout << "\n";
            for (double x : y){
                cout << x << " ";
            }
        }
    }
}

void Channel::fill(QVector<int> &data)
{
    for (int z = 0; z < shape[0]; z++){
        for (int y = 0; y < shape[1]; y++){
            for (int x = 0; x < shape[2]; x++){
                content[z][y][x] = data[0];
                data.removeFirst();
            }
        }
    }
}

QVector<QVector<QVector<double> > > &Channel::contentRef()
{
    return content;
}

double Channel::lRelu(double x)
{
    return max(x*0.01, x);
}


