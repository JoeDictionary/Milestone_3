#include "channel.h"

Channel::Channel(int zDim, int yDim, int xDim)
{
    shape[0] = zDim; shape[1] = yDim; shape[2] = xDim;

    // Creates a 3d QVector withe the dimensions zDim, yDim, xDim filled woth zeros and assigns it to 'content'.
    content = QVector<QVector<QVector<double>>>(zDim, QVector<QVector<double>>(yDim, QVector<double>(xDim, 0)));

}

/* Returns reference to a cell in 'content' selected by z, y and x coordinates. */
double &Channel::cell(int z, int y, int x)
{
    return content[z][y][x];
}

/* Sets every cell of 'content' to 0 */
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

void Channel::pad()
{
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

double Channel::lRelu(double x)
{
    return max(x*0.01, x);
}


