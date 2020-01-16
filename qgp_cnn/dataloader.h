#ifndef DATALOADER_H
#define DATALOADER_H

#include <filter.h>

#include <QtDebug>
#include <QDirIterator>
#include <QRegExp>


class DataLoader
{
public:
    DataLoader();
    void loadBatch();

    int batchSize = 10;

    QVector<int> convertStringData();

private:
    /* Contains current batch of training data as strings. Each file is one string. */
    QStringList trainingBatch;

    /* Directory iterator for iterating over qgp training files in specified directory. */
    QDirIterator* qFileIterator = new QDirIterator("C:/Users/filip/Desktop/PROGRAMMING/dataset_half/qgp", QDir::Files);

    /* Directory iterator for iterating over nqgp training files in specified directory. */
    QDirIterator* nqFileIterator = new QDirIterator("C:/Users/filip/Desktop/PROGRAMMING/dataset_half/nqgp", QDir::Files);
};

#endif // DATALOADER_H
