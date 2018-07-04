#ifndef BASECUTTINGPLANE_H
#define BASECUTTINGPLANE_H
#include <QVector4D>
#include <QVector3D>

class BaseCuttingPlane
{
public:
    BaseCuttingPlane();
    //Setting a cutting plane
    bool clipFlag=false;
    double normX=0;
    double normY=0;
    double normZ=1;
    double pointX=0;
    double pointY=0;
    double pointZ=0;
    QVector4D normVector;
    QVector3D pointVector;
    void setToVector();
};

#endif // BASECUTTINGPLANE_H
