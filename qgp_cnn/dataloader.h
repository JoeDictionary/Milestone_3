#ifndef DATALOADER_H
#define DATALOADER_H

#include <filter.h>

#include <QtDebug>
#include <QDirIterator>


class DataLoader
{
public:
    DataLoader(QString qgpPath, QString nqgpPath);

    ~DataLoader();

    void loadBatch();

    QVector<int> convertStringData();

    int batchSize = 10;

    /* Contains current batch of training data as strings. Each file is one string. */
    QStringList trainingBatch;

private:

    // Home: C:/Users/filip/Desktop/PROGRAMMING/dataset_half/qgp
    // Laptop: C:/Users/Filip/Desktop/dataset_half/qgp

    bool qFilePathSet = false;

    /* Directory iterator for iterating over qgp training files in specified directory. */
    QDirIterator* qFileIterator;
    bool nqFilePathSet = false;

    /* Directory iterator for iterating over nqgp training files in specified directory. */
    QDirIterator* nqFileIterator;
};

#endif // DATALOADER_H
