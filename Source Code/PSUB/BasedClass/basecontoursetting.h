#ifndef BASECONTOURSETTING_H
#define BASECONTOURSETTING_H
#include <QString>

class BaseContourSetting
{
public:
    BaseContourSetting();
    int noc=10; //number of contour
    int contourPosition=0; //contourPosition, 0 is left, 1 is right, 2 is bottom
    int fontSize=10;
    int numericType=0; //1 is float (3 decimal), 1 is interger, 2 is scientific
    bool nodeVisible=false;
    bool meshVisible=false;
    bool resultVisible=true;
    bool axeVisible=true;
    bool dateVisible=true;
    bool titleVisible=true;
    bool maxVisible=true;
    bool deformedMeshVisible=true;
    QString title="Coupled Plugin";
};

#endif // BASECONTOURSETTING_H
