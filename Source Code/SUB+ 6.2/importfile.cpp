#include "importfile.h"

importFile::importFile(QObject *parent) : QObject(parent)
{
    qDebug()<<"Import classed is created"<<endl;
}

int importFile::numberOfRow()
{
    return row;
}

int importFile::numberOfCol()
{
    return col;
}

void importFile::setFolderName(QString folderName)
{
    this->folderName=folderName;
    fullName=folderName+'/'+fileName;
}

void importFile::setFileName(QString fileName)
{
    this->fileName=fileName;
    fullName=folderName+'/'+fileName;
}

void importFile::setFileName(QString fileName, bool fullFileFlag)
{
    if(fullFileFlag=false)
    {
        fullName=folderName+'/'+fileName;
    }
    else
    {
        this->fullName=fileName;
        this->fullFileFlag=true;
    }
}

void importFile::getDimension()
{
    row=0;
    col=0;
    QFile mFile(fullName);
    QString mLine, Temp;
    QTextStream mStream(&mFile);

    //Reading file
    if(!mFile.open(QFile::ReadOnly|QFile::Text))
    {
        qDebug()<<"Cannot open the file"<<endl;
        successCheck=false;
        emit failedGetFile();
        return;
    }
    else
    {
        for (auto i=0;i<skipHeading;i++)
        {
            mLine=mStream.readLine(); //Skip n lines
        }

        while(!mStream.atEnd())
        {

            mLine=mStream.readLine();
            row=row+1;
            if(row==1)
            {
                QStringList mList=mLine.split(QRegExp("\\s+"),QString::SkipEmptyParts);
                col=mList.count();
            }
        }
        successCheck=true;
    }
    mFile.close();
    qDebug()<<"Number of Row and Col" <<row<<col<<endl;
}

void importFile::doGetFile(QString fileName, int skipHeadding)
{
    this->fullName=folderName+'/'+fileName;
    this->skipHeading=skipHeadding;
    getFile();
}

void importFile::doGetFile(QString fileName)
{
    fullName=folderName+'/'+fileName;
    getFile();
}

void importFile::doGetFile(QString fileName, bool fullFileFlag)
{
    if (fullFileFlag=false)
    {
        fullName=folderName+'/'+fileName;
    }
    else
    {
        fullName=fileName;
    }
    getFile();
}

void importFile::getFile()
{
    checkFinish=false;
    timer.start();
    getDimension();
    if(successCheck==true)
    {
        dataFile.resize(row,col);
        QFile mFile(fullName);
        QString mLine,Temp;
        QTextStream mStream(&mFile);
        mFile.open(QFile::ReadOnly|QFile::Text);

        int i=0, percent;
        percent=int(row/10);
        for (auto i=0;i<skipHeading;i++)
        {
            mLine=mStream.readLine(); //Skip n lines
        }

        while(!mStream.atEnd())
        {
            mLine=mStream.readLine();
            QStringList mList=mLine.split(QRegExp("\\s+"),QString::SkipEmptyParts);
            for (int j=0;j<col;j++)
            {
                Temp=mList[j];
                double value=Temp.toDouble();
                dataFile(i,j)=value;;
            }
            i++;
        }
        qDebug()<<endl;
        mFile.close();
    }
    else
    {
        emit failedGetFile();
        qDebug()<<"Failed to get file: "<<fullName<<endl;
    }
    qDebug()<<"Finish importing file: "<<fullName<<" in:"<<timer.elapsed()/1000<<" seconds"<<endl;
    emit finishSigleThread();
    successCheck=false;
}

void importFile::setSkipHeading(int skipHeadding)
{
    this->skipHeading=skipHeadding;
}

bool importFile::checkFinishThread()
{
    return checkFinish;
}

void importFile::pauseSystem()
{
    do
    {
        qDebug()<<"Press Enter Key to continue"<<endl;
    } while(cin.get()!='\n');
}

void importFile::setFileIndexID(int fileIndexID)
{
    this->fileIndexID=fileIndexID;
}

void importFile::setThreadID(int threadID)
{
    this->threadID=threadID;
}

void importFile::doGetFile()
{
    getFile();
}
