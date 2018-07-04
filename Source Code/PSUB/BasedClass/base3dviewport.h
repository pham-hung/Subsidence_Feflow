#ifndef BASE3DVIEWPORT_H
#define BASE3DVIEWPORT_H
#include <QMatrix4x4>

class Base3DViewport
{
public:
    Base3DViewport();
    //Initial parameter
    double xLeft0, xRight0, yBot0, yTop0;
    //Actual para;meter
    double xLeft, xRight, yBot, yTop;
    //Max min variable
    double xMax, xMin, yMax, yMin, zMax, zMin;
    //center variable
    double xCenter, yCenter, zCenter;
    //lock view
    bool lockView=false;
    bool keepViewport=false;
    QMatrix4x4 cameraMatrix;
};

#endif // BASE3DVIEWPORT_H
