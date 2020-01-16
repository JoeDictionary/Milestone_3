#include "dataloader.h"

DataLoader::DataLoader()
{

}

void DataLoader::loadBatch()
{
    // Clears 'trainingData' list from already used data.
    QStringList stringData;
    // trainingBatch.clear();

    for(int i=0;i < batchSize; i++){
        // Steps fileIterator to next file
        QFile file(qFileIterator->next());

        qDebug() << qFileIterator->fileName();
        file.open(QIODevice::ReadOnly);
        stringData.append(file.readAll());
    }

    qDebug() << "(loadBatch) Next Batch Loaded!";
    qDebug() << "(loadBatch) stringData-size: " << stringData.size();
}

QVector<int> DataLoader::convertStringData()
{
    QVector<int> processedData;

    /*
    if (trainingBatch.size() <= 0) {
        qDebug() << "(DataLoader) Batch processed, loading next batch...";
        loadBatch();
    }
    */

    for (QString i : trainingBatch[0].split(QRegExp("\\s+"), QString::SkipEmptyParts )) {
        // processedData.push_back(i.toInt());
    }

    return processedData;
}



/*
void NeuralNet::feedInput()
{
    QList<int> processedData;

    // Splits first entry in string in 'trainingData' into strings of single digits, converts these to integers and appends them to 'processed' data.
    for(QString i : trainingData[0].split(QRegExp("\\s+"), QString::SkipEmptyParts)) {
        processedData.append(i.toInt());
    }

    // Sets every neuron's 'currentVal' in the input layer to the corresponding datapoint in 'processedData'.
    for(int i = 0; net[0].size(); i++) {
        net[0][i].currentVal = processedData[i];
    }
}
*/
