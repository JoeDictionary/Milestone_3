#include "dataloader.h"

DataLoader::DataLoader(QString qgpPath, QString nqgpPath)
{
    qFileIterator = new QDirIterator(qgpPath, QDir::Files);
    nqFileIterator = new QDirIterator(nqgpPath, QDir::Files);
}

DataLoader::~DataLoader()
{
    delete qFileIterator;
    delete nqFileIterator;
}

void DataLoader::loadBatch()
{
    trainingBatch.clear();

    for(int i=0;i < batchSize; i++){
        // Steps fileIterator to next file
        QFile file(qFileIterator->next());

        qDebug() << qFileIterator->fileName();
        file.open(QIODevice::ReadOnly);
        trainingBatch.append(file.readAll());
    }

    qDebug() << "(loadBatch) Next Batch Loaded!";
}

QVector<int> DataLoader::convertStringData()
{
    QVector<int> processedData;

    if (trainingBatch.size() <= 0) {
        qDebug() << "(DataLoader) Batch processed, loading next batch...";
        loadBatch();
    }    

    // Splits the first string in 'trainingBatch' into numbers and adds them to 'processedData'.
    for (QString i : trainingBatch[0].split(QRegExp("\\s+"), QString::SkipEmptyParts )) {
        processedData.push_back(i.toInt());
    }
    // Removes used up data.
    trainingBatch.removeFirst();

    return processedData;
}
