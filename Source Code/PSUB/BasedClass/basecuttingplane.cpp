#include "basecuttingplane.h"

BaseCuttingPlane::BaseCuttingPlane()
{
    setToVector();
}

void BaseCuttingPlane::setToVector()
{
    normVector.setX(normX);
    normVector.setY(normY);
    normVector.setZ(normZ);

    if(clipFlag==true)
    {
        normVector.setW(1);
    }
    else
    {
        normVector.setW(-1);
    }

    pointVector.setX(pointX);
    pointVector.setY(pointY);
    pointVector.setZ(pointZ);
}
