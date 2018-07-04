#ifndef IMPORTMULTIFILES_H
#define IMPORTMULTIFILES_H

#include <QObject>
#include "importfile.h"
#include <QStringList>
#include <vector>
#include <QThread>
#include <QMutex>
using namespace Eigen;
using namespace std;

class importMultiFiles : public QObject
{
    Q_OBJECT
public:
    explicit importMultiFiles(QObject *parent = nullptr);
    void getFileSize();
    void setListFiles(QStringList listFileName);
    void getFileMultiThread();
    void pauseSystem();
    vector<MatrixXd> listMatrix;
signals:    

public slots:

private:
    QStringList listFileName;
    int numberOfFile;
    vector<pair<double,QString> >vectorFileName;    
    int count=0;
    int threadIndex=0;
    QMutex mutex;
    vector<QThread*> thread;
    vector<importFile*> mImport;
};

#endif // IMPORTMULTIFILES_H
