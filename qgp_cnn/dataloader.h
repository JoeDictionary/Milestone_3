#ifndef DATALOADER_H
#define DATALOADER_H

#include <QtDebug>
#include <QDirIterator>


class DataLoader
{
public:
    DataLoader();
    void loadBatch();

    int batchSize = 10;

private:
    /* Contains current batch of training data. */
    QStringList trainingBatch;

    /* Directory iterator for iterating over training files in specified directory. */
    QDirIterator* dirIterator = new QDirIterator("C:/Users/Filip/Desktop/dataset_half/nqgp", QDir::Files);
};

#endif // DATALOADER_H