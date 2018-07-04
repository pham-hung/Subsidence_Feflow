#ifndef BASESTEPRESULT_H
#define BASESTEPRESULT_H
#include <Eigen/Dense>
#include <QString>
using namespace Eigen;

class BaseStepResult
{
public:
    BaseStepResult();
    int fieldIndex=0;
    int stepIndex=1;
    QString resultComboName="Total Head";
    double minValue=0;
    double maxValue=100;
    bool autoMaxMin=true;    
    int startStep=1;
    int endStep=1;
    double delay=200;
    bool lockView=false;
    bool autoChangeMaxMin=true;
    bool animationFlag=false;
    bool validInformation=false;
};

#endif // BASESTEPRESULT_H
