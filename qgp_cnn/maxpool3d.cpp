#include "maxpool3d.h"

MaxPool3D::MaxPool3D()
{

}

MaxPool3D::MaxPool3D(int stride)
{
    this->stride=stride;
}

//accepts an object and stride value
//strides through the input object, advancing by the stride value, progressively through all dimensions
//saves the maximum of each 3d-sub-vector in a new 3D vector, along with its coordinates
QVector<object3D*> MaxPool3D::forward(QVector<object3D*> inputs3D){

    QVector<object3D*> res = QVector<object3D*>();
    int stride=this->stride;

    //process all channels in the array
    for(object3D *input3D : inputs3D){
        //set dimensions from the source input object
        //input3D
        int dimX=input3D->data.length();
        int dimY=input3D->data[0].length();
        int dimZ=input3D->data[0][0].length();

        // add padding to prevend array overflow
        while(dimX % stride != 0)dimX++;
        while(dimY % stride != 0)dimY++;
        while(dimZ % stride != 0)dimZ++;

        this->dimX=dimX;
        this->dimY=dimY;
        this->dimZ=dimZ;

        //vector<vector<vector<int>>> matrix(4, vector<vector<int>>(4));

        // create a new output layer with dimensions compatible with the stride value
        object3D *output3D = new object3D();
        output3D->data = QVector<QVector<QVector<double>>>(dimX/stride, QVector<QVector<double>>(dimY/stride, QVector<double>(dimZ/stride, 0.0) ));
        output3D->coordinates = QVector<QVector<QVector<QVector<int>>>>(dimX/stride, QVector<QVector<QVector<int>>>(dimY/stride, QVector<QVector<int>>(dimZ/stride, QVector<int>(3, 0)) ));

        //create padded window with the contents of the input
        QVector<QVector<QVector<double>>> paddedInput3D = QVector<QVector<QVector<double>>>(dimX, QVector<QVector<double>>(dimY, QVector<double>(dimZ, 0.0) ));
        for(int x=0; x<input3D->data.length(); x++){
            for(int y=0; y<input3D->data[0].length(); y++){
                for(int z=0; z<input3D->data[0][0].length(); z++){
                    paddedInput3D[x][y][z]=input3D->data[x][y][z];
                }
            }
        }

        //go through paddedInput3D striding the stride value provided
        for(int x=0; x<dimX; x+=stride){
            for(int y=0; y<dimX; y+=stride){
                for(int z=0; z<dimZ; z+=stride){

                    //finde den Max-Wert heraus
                    double max = -1;
                    QVector<int> coordinates = {0,0,0};

                    for(int x2=x; x2<x+stride; x2++){
                        for(int y2=y; y2<y+stride; y2++){
                            for(int z2=z; z2<z+stride; z2++){
                                if(paddedInput3D[x2][y2][z2]>max){
                                    max=paddedInput3D[x2][y2][z2];
                                    coordinates[0]=x2-x;
                                    coordinates[1]=y2-y;
                                    coordinates[2]=z2-z;
                                }
                            }
                        }
                    }

                    output3D->coordinates[x/stride][y/stride][z/stride][0]=coordinates[0];
                    output3D->coordinates[x/stride][y/stride][z/stride][1]=coordinates[1];
                    output3D->coordinates[x/stride][y/stride][z/stride][2]=coordinates[2];
                }
            }
        }
        //std::cout << dimX << " " << dimY << " " << dimZ << " ";

        //push the currectly convoluted channel to the output layer
        res.push_back(output3D);
    }

    //save the data for BP
    this->cache=res;

    //return the now halved output
    return res;
}

QVector<object3D*> MaxPool3D::backward(QVector<object3D*> inputs3D){

    QVector<object3D*> res = QVector<object3D*>();

    //process all channels in the array
    for(int i=0; i<inputs3D.length(); i++){
        object3D *input3D = inputs3D.at(i);
        object3D *tmpCache = cache.at(i);

        //create layer of the "original" size, as when the data were input to forward propagation
        object3D *output3D = new object3D();
        output3D->data = QVector<QVector<QVector<double>>>(this->dimX, QVector<QVector<double>>(this->dimY, QVector<double>(this->dimZ, 0.0)));

        //now with the layer of the original size on hand, we navigate to each "source" sub-cube and multiply it by the value from our BP input
        for(int x=0; x<this->dimX; x+=stride){
            for(int y=0; y<this->dimY; y+=stride){
                for(int z=0; z<this->dimZ; z+=stride){
                    //now, this accesses each topleft pixel of each sub-cube
                    //we get the coordinates from cache and add set the respective coordinates so sigma
                    //there is no point back-propagating through non-maximum neurons
                    int padding_x = tmpCache->coordinates[x][y][z][0];
                    int padding_y = tmpCache->coordinates[x][y][z][1];
                    int padding_z = tmpCache->coordinates[x][y][z][2];

                    //we construct say 10x10x10 with stride 2, so the source thereof must be 10/2x10/2x10/2
                    double sigma = input3D->data[x/stride][y/stride][z/stride];
                    output3D->data[x+padding_x][y+padding_y][z+padding_z] = sigma*1;
                }
            }
        }
        res.push_back(output3D);
    }

    return res;
}
