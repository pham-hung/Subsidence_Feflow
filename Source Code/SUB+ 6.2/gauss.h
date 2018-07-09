#ifndef GAUSS_H
#define GAUSS_H
#include <Eigen/Dense>
#include <QObject>
using namespace Eigen;

class Gauss: public QObject
{
    Q_OBJECT

public:
    Gauss();
    MatrixXd gauss4, gauss8, gauss27, gauss13, gauss9;
    void createGauss4();
    void createGauss8();
    void createGauss9(); //For prism
    void createGauss27();
    void createGauss13();
};

#endif // GAUSS_H
