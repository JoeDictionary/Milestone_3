#include "flatten.h"

Flatten::Flatten()
{

}

QVector<double> Flatten::forward(QVector<object3D*> inputs3D){

    //save the channel count
    this->channel_count=inputs3D.length();

    QVector<double> flattened;

    //process all channels in the array
    for(object3D *input3D : inputs3D){
        //set dimensions from the source input object
        //input3D
        this->dimX=input3D->data.length();
        this->dimY=input3D->data[0].length();
        this->dimZ=input3D->data[0][0].length();

        for(int x=0; x<this->dimX; x++){
            for(int y=0; y<this->dimY; y++){
                for(int z=0; z<this->dimZ; z++){
                    flattened.push_back(input3D->data[x][y][z]);
                }
            }
        }
    }

    return flattened;
}

QVector<object3D*> Flatten::backward(QVector<double> flattened){

    QVector<object3D*> res = QVector<object3D*>();

    for(int i=0; i<this->channel_count; i++){
        object3D *output3D = new object3D();
        output3D->data = QVector<QVector<QVector<double>>>(this->dimX, QVector<QVector<double>>(this->dimY, QVector<double>(this->dimZ, 0.0)));

        for(int x=0; x<this->dimX; x++){
            for(int y=0; y<this->dimY; y++){
                for(int z=0; z<this->dimZ; z++){
                    output3D->data[x][y][z] = flattened.last();
                    flattened.pop_back();
                }
            }
        }
        res.push_back(output3D);
    }

    return res;
}
