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

QVector<QVector<QVector<double> > > &Channel::contentRef()
{
    return content;
}

double Channel::lRelu(double x)
{
    return max(x*0.01, x);
}


