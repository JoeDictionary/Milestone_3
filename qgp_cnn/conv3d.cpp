#include "conv3d.h"
#include "filter.h"

Conv3D::Conv3D(int filterAmount, int outputChannelAmount, DataLoader loader, mt19937 seed)
{
    kernelArray = QVector<Kernel>(outputChannelAmount, Kernel(filterAmount, outputChannelAmount, seed));

    for (Kernel i : kernelArray) {
        i.reset();
    }
}

Conv3D::Conv3D(int nChannels, int nKernels){

    //create an array or arrays of filters
    this->filterSets = QVector<QVector<Filter*>>(nKernels, QVector<Filter*>());
    for(QVector<Filter*> & bit : this->filterSets){
        for(int i=0; i<nChannels; i++){
            //appends a 3x3x3 Filter with random values in each point
            bit.push_back(new Filter(3,3,3));
        }
    }

    this->nChannels = nChannels;
    this->nKernels = nKernels;
}

QVector<object3D*> Conv3D::forward(QVector<object3D*> channelCollection){

    //backup the input for use in BP
    this->cachedChannelCollection = channelCollection;

    int dimX=channelCollection[0]->data.length();
    int dimY=channelCollection[0]->data[0].length();
    int dimZ=channelCollection[0]->data[0][0].length();

    QVector<object3D*> res = QVector<object3D*>();

    //loop through the array with arrays of Filters
    for(QVector<Filter*> filterCollection : this->filterSets){

        //now we have one filterCollection and one channelCollection
        //these we now process into one Ergebnisfenster

        object3D *ergebnisFenster = new object3D();
        ergebnisFenster->data = QVector<QVector<QVector<double>>>(dimX-1, QVector<QVector<double>>(dimY-1, QVector<double>(dimZ-1, 0.0)));

        //now we take the first element or every channel, multiply it with the first element of its corresp. filter, add all results together and call lRelu on it
        //navigate to a specific location - starting with 0,0,0 through n,n,n
        for(int x=0; x<dimX-1-2; x++){
            for(int y=0; y<dimY-1-2; y++){
                for(int z=0; z<dimZ-1-2; z++){

                    double sum = 0.0;

                    //add padding to the current coordinates to assess a subportion of the same size as the Filter
                    for(int padd_x=0; padd_x<3; padd_x++){
                        for(int padd_y=0; padd_y<3; padd_y++){
                            for(int padd_z=0; padd_z<3; padd_z++){

                                //at the very beginning, (x,y,z) corresponds to (0,0,0)
                                //go through all channels and their respective filters


                                for(int channel_ind=0; channel_ind<filterCollection.length(); channel_ind++){
                                    object3D *channel = channelCollection.at(channel_ind);
                                    Filter *filter = filterCollection.at(channel_ind);
                                    //at this point we have point (0,0,0) and two sources, namely channel and filter

                                    //now we take the first (or nth) element of channel
                                    double a = channel->data[x+padd_x][y+padd_y][z+padd_z];

                                    //now we take the first (or nth) element of the filter
                                    double w = filter->content[padd_x][padd_y][padd_z];

                                    //we multiply them together and add to the sum
                                    sum += a * w;
                                }
                            }
                        }
                    }

                    //we call lRelu on sum and add it to the appropriate coordinates of the ergebnisFenster
                    ergebnisFenster->data[x][y][z] = lRelu(sum);
                }
            }
        }

        //at this point the ergebnisFenster is fully populated, so we add it to the bulk
        res.push_back(ergebnisFenster);

        //now the iteration is complete and if there are any more filterSets, the process repeats and the result is appended by yet another ergebnisFenster
        //there are as many elements in the output array as there are filterSets
    }

    //return the Array with ergebnisFenstern
    return res;
}

QVector<object3D*> Conv3D::backward(QVector<object3D*> bp_input){

    QVector<object3D*> channelCollection = this->cachedChannelCollection;

    int dimX=channelCollection[0]->data.length();
    int dimY=channelCollection[0]->data[0].length();
    int dimZ=channelCollection[0]->data[0][0].length();

    QVector<object3D*> res = QVector<object3D*>();
/*
    //loop through the array with arrays of Filters
    for(QVector<Filter*> &filterCollection : this->filterSets){
    //for(QVector<Filter*> filterCollection : bp_input){

        //now we have one filterCollection and one channelCollection
        //these we now process into one Ergebnisfenster

        object3D *ergebnisFenster = new object3D();
        ergebnisFenster->data = QVector<QVector<QVector<double>>>(dimX-1, QVector<QVector<double>>(dimY-1, QVector<double>(dimZ-1, 0.0)));

        //now we take the first element or every channel, multiply it with the first element of its corresp. filter, add all results together and call lRelu on it
        //navigate to a specific location - starting with 0,0,0 through n,n,n
        for(int x=0; x<dimX-1-2; x++){
            for(int y=0; y<dimY-1-2; y++){
                for(int z=0; z<dimZ-1-2; z++){

                    double sum = 0.0;

                    //add padding to the current coordinates to assess a subportion of the same size as the Filter
                    for(int padd_x=0; padd_x<3; padd_x++){
                        for(int padd_y=0; padd_y<3; padd_y++){
                            for(int padd_z=0; padd_z<3; padd_z++){

                                //at the very beginning, (x,y,z) corresponds to (0,0,0)
                                //go through all channels and their respective filters


                                for(int channel_ind=0; channel_ind<filterCollection.length(); channel_ind++){
                                    object3D *channel = channelCollection.at(channel_ind);
                                    Filter *filter = filterCollection.at(channel_ind);
                                    //at this point we have point (0,0,0) and two sources, namely channel and filter

                                    //now we take the first (or nth) element of channel
                                    double a = channel->data[x+padd_x][y+padd_y][z+padd_z];

                                    //now we take the first (or nth) element of the filter
                                    //double w = filter->content[padd_x][padd_y][padd_z];
                                    double dh = lReluDeriv(bp_input[bp_ind]);

                                    //we multiply them together and add to the sum
                                    //sum += a * w;
                                    filter[x][y][z]=a*dh;
                                }
                            }
                        }
                    }
                }
            }
        }
    }*/

    //return the Array with ergebnisFenstern
    return res;
}
/*
void Conv3D(Kernel kernel, int dimX, int dimY, int dimZ){

    int offsetX = kernel.dimX-1;
    int offsetY = kernel.dimY-1;
    int offsetZ = kernel.dimZ-1;

    for(int x=0; x<dimX-offsetX; x++){
        for(int y=0; y<dimX-offsetY; y++){
            for(int z=0; z<dimZ-offsetZ; z++){
                //startpunkt im 3D Raum von Berechnung anhand des Kernels

            }
        }
    }
}*/

double Conv3D::lRelu(double x)
{
    return max(x*0.01, x);
}

double Conv3D::lReluDeriv(double x){
        if(x >= 0){
            return 1;
        } else {
            return 0.01;
        }
}
