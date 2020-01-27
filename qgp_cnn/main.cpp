#include <QCoreApplication>
#include <channel.h>
#include <kernel.h>
#include <dataloader.h>
#include <filter.h>

#include <random>
#include <time.h>
#include <QDebug>
#include <QtDebug>

#include "object3d.h"
#include "conv3d.h"
#include "maxpool3d.h"
#include "flatten.h"

// Home: "C:/Users/filip/Desktop/PROGRAMMING/dataset_half/qgp"
// Laptop: "C:/Users/Filip/Desktop/dataset_half/qgp"


QVector<double> ann(QVector<double> input1D){
    return input1D;
}

Conv3D * c1, * c2;
MaxPool3D * m1, * m2;
Flatten * f;

//2a
void initCNN(){
    c1 = new Conv3D(32,28);
    m1 = new MaxPool3D(2);
    c2 = new Conv3D(64,32);
    m2 = new MaxPool3D(2);
    f = new Flatten();
}

QVector<object3D*> cnnChannels;

//2b
void fillCNN(QVector<object3D*> channels){
    cnnChannels=channels;
}

//2c
void clearCNN(){
    cnnChannels.clear();

    delete c1;
    delete c2;
    delete m1;
    delete m2;
    delete f;

    initCNN();
}

void runCNN(){

    QVector<object3D*> tmpData=cnnChannels;
    //1  Conv3D (2D)
    tmpData = c1->forward(tmpData);
    //2  MaxPool3D (2E)
    tmpData = m1->forward(tmpData);
    //3  Conv3D (2F)
    tmpData = c2->forward(tmpData);
    //4  MaxPool3D (2G)
    tmpData = m2->forward(tmpData);
    //5  Flatten
    QVector<double> flattenedImage = f->forward(tmpData);
    //6  ANN
    QVector<double> m2result=ann(flattenedImage);
    //7  BP Flatten
    tmpData = f->backward(m2result);
    //8  BP MaxPool3D (2J)
    tmpData = m2->backward(tmpData);
    //9  BP Conv3D (2H)
    tmpData = c2->backward(tmpData);
    //10 BP MaxPool3D (2K)
    tmpData = m1->backward(tmpData);
    //11 BP Conv3D (2I)
    tmpData = c1->backward(tmpData);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int filterAmount = 28;
    int kernelAmount = 32;

    // 2a
    initCNN();

    QVector<object3D*> channels = QVector<object3D*>();
    //for(Channel ch in DataloaderOutput){channels.push(ch.content);}

    object3D *testObj = new object3D();
    testObj->data = QVector<QVector<QVector<double>>>(9, QVector<QVector<double>>(11, QVector<double>(20, 0.0)));
    channels.push_back(testObj);

    object3D *testObj2 = new object3D();
    testObj2->data = QVector<QVector<QVector<double>>>(9, QVector<QVector<double>>(11, QVector<double>(20, 0.0)));
    channels.push_back(testObj2);

    //2b
    //DataLoader myLoader("C:/Users/filip/Desktop/PROGRAMMING/dataset_half/qgp", "C:/Users/filip/Desktop/PROGRAMMING/dataset_half/nqgp");
    //data=myLoader.loadBatch();
    fillCNN(channels);


    runCNN();


    delete testObj;
    delete testObj2;

    /*
    uniform_real_distribution<double> disOne(-1.0, 1.0);
    mt19937 gen(time(NULL)); // mersenne_twister_engine seeded with rd()
    // QVector<Kernel> kernelArray = QVector<Kernel>(kernelAmount, Kernel(filterAmount, kernelAmount, gen));
    Kernel kernelArray(filterAmount, kernelAmount, gen, 3);
    kernelArray.printContent();
    Kernel myKernel(28, 32, gen);
    */


    /*
    Channel myChan(3, 3, 3);
    Channel otherChan(3, 3, 3);
    (myChan + otherChan).printContent();
    */

    return a.exec();
}
