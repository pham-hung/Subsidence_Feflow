#ifndef ELEMENTMATRIX_H
#define ELEMENTMATRIX_H

#include <QObject>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/PardisoSupport>

#include <QFile>
#include <QString>
#include <QDebug>
#include <QElapsedTimer>
#include <iostream>
#include <vector>
#include <QThread>
#include <thread>
#include <QDir>
#include "gauss.h"

using namespace std;
using namespace Eigen;

//This class is used for assembly global matrix using multiThread
class elementMatrix : public QObject
{
    Q_OBJECT
public:
    explicit elementMatrix(QObject *parent = nullptr);
    int startElement, endElement, eleNum;

    //common input
    MatrixXd coordinates, elements;
    MatrixXd hydroParameters, mechanicalParameters;
    MatrixXd U0,V0,W0,H0,initialH;
    MatrixXd DirichletAll;
    double timeIncrement;

    //output
    typedef Eigen::Triplet<double> Trip;
    vector <Trip> trip_total;
    MatrixXd F;
    bool checkFinish=false;

    void assemblyMatrix();
    void prism6pMatrix(int &eleNum);

signals:

public slots:

private:
    double kxe, kye, kze, Ke, Ge, ve, Se, ne, Cfe, Cse, BiotCoeff, Cme,gf;
    int numberOfNode, numberOfElement,totalDegreeOfFreedom;

    MatrixXd gauss;
    Gauss gaussPoint;
};

#endif // ELEMENTMATRIX_H
