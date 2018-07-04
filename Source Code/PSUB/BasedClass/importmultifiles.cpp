#include "importmultifiles.h"

importMultiFiles::importMultiFiles(QObject *parent) : QObject(parent)
{

}

void importMultiFiles::getFileSize()
{
    //Arrange file by size
    //Read from bottom to top (largest size to smallest size)
    numberOfFile= listFileName.size();
    QString fileName;
    for (int i=0;i<numberOfFile;i++)
    {
        fileName=listFileName[i];
        QFile mFile(fileName);
        double size=mFile.size();        
        pair<double,QString> newPair;
        newPair.first=size;
        newPair.second=fileName;
        vectorFileName.push_back(newPair);
    }
    sort(vectorFileName.begin(),vectorFileName.end());
    reverse(vectorFileName.begin(),vectorFileName.end());
}

void importMultiFiles::setListFiles(QStringList listFileName)
{
    this->listFileName=listFileName;
}

void importMultiFiles::getFileMultiThread()
{

}
