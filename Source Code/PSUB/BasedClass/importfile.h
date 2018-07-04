#ifndef IMPORTFILE_H
#define IMPORTFILE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include <QThread>
#include <iostream>
#include <Eigen/Dense>
#include <QDir>
#include <QFileInfo>
#include <QElapsedTimer>
#include <QFileDialog>

using namespace Eigen;
using namespace std;

class importFile : public QObject
{
    Q_OBJECT

public:    
    explicit importFile(QObject *parent = nullptr);
    //Get numbe of Row and Col

    int numberOfRow(); //Done
    int numberOfCol(); //Done

    void setFolderName(QString folderName); //set folderName
    void setFileName(QString fileName); //set fileName, fullName=fileName+folderName
    void setFileName(QString fileName,bool fullFileFlag); //if fullFileFlag=true, fullNalme=fileName;

    void getDimension(); //get number of rows and columns of an ASCII file, using fullName + skipHeading

    void doGetFile(QString fileName, int skipHeading); //Get file with fileName + folderName + skipHeading
    void doGetFile(QString fileName);//getFIle with fileName only, skipHeading=0 or predefined
    void doGetFile(QString fileName,bool fullFileFlag); //Get file with full file Name, skipheading is kept unchanged
    void getFile(); //main get File function, using full file name, and skipHeading.

    void setSkipHeading(int skipHeading); //set Skipheading, default=0;
    bool checkFinishThread(); //for multi thread
    void pauseSystem();     

    void setFileIndexID(int fileIndexID);
    void setThreadID (int threadID);

    MatrixXd dataFile=MatrixXd::Zero(1,1); //Make this public to easier access

signals:
    void startedGetFile();   //started to get file
    void failedGetFile();    //Failed to get file
    void finishSigleThread();
    void finishAllThread();

public slots:
    void doGetFile();

private:
    QString fileName;
    QString folderName;
    QString fullName;
    int row=0;
    int col=0;
    int fileIndexID=0;
    int threadID=0;
    int skipHeading=0;
    bool checkFinish=false;
    bool successCheck=false;
    bool fullFileFlag=false;
    QElapsedTimer timer;    
};

#endif // IMPORTFILE_H
