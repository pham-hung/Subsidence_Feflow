#include "writetofile.h"
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<QString>

void WriteToFile::ToFile(const Ref<const MatrixXd> matrixA)
{
    int row=matrixA.rows();
    int col=matrixA.cols();
    double val=0;
    ofstream file_;
    file_.open(fileName);

    for (int i=0;i<row;i=i+1)
    {
        for (int j=0;j<col;j=j+1)
        {
          val=matrixA(i,j);
          file_<<std::setw(13)<<std::setprecision(5)<<std::scientific<<val<<' ';
        }
        file_<<'\n';
    }
    file_.close();
    qDebug()<<"Exported successfully "<<QString::fromStdString(fileName)<<endl;
}

void WriteToFile::ToFile(const Ref<const MatrixXi> matrixA)
{
    int row=matrixA.rows();
    int col=matrixA.cols();
    double val=0;
    ofstream file_;
    file_.open(fileName);

    for (int i=0;i<row;i=i+1)
    {
        for (int j=0;j<col;j=j+1)
        {
          val=matrixA(i,j);
          file_<<std::setw(13)<<std::setprecision(0)<<std::defaultfloat<<val<<' ';
        }
        file_<<'\n';
    }
    file_.close();
    qDebug()<<"Exported successfully "<<QString::fromStdString(fileName)<<endl;
}

void WriteToFile::ToFile(const Ref<const MatrixXd> matrixA, QStringList headerList)
{
    int row=matrixA.rows();
    int col=matrixA.cols();
    double val=0;
    ofstream streamFile_;
    streamFile_.open(fileName);
    QString headerString;

    for (auto i=0;i<headerList.size();i++)
    {
        headerString=headerList[i];
        streamFile_<<std::setw(13)<<std::internal<<headerString.toStdString()<<' ';
    }
    streamFile_<<'\n';

    for (int i=0;i<row;i=i+1)
    {
        for (int j=0;j<col;j=j+1)
        {
          val=matrixA(i,j);
          streamFile_<<std::setw(13)<<std::right<<std::setprecision(5)<<std::scientific<<val<<' ';
        }
        streamFile_<<'\n';
    }
    streamFile_.close();
    qDebug()<<"Exported successfully "<<QString::fromStdString(fileName)<<endl;
}

WriteToFile::WriteToFile()
{

}
