#ifndef STEPRESULT_H
#define STEPRESULT_H

#include <QDialog>
#include <QMessageBox>
#include "BasedClass/basestepresult.h"
#include <QDebug>

namespace Ui {
class StepResult;
}

class StepResult : public QDialog
{
    Q_OBJECT

public:
    explicit StepResult(QWidget *parent = 0);
    ~StepResult();
    void doneAnimation();
private slots:
    void on_animationStart_clicked();
    void on_resultCombo_currentIndexChanged(int index); //change combo pick
    void getInformationFromMainWindow(int nos,bool validPick);
    void getInformationFromMainWindow(double minVal, double maxVal);
    void on_closeButton_clicked();
    void on_stepCombo_currentIndexChanged(int index); //change step combo
    void on_maxCombo_currentIndexChanged(int index);
    void on_okButton_clicked();

signals:
    void sendStepResultsInformation(BaseStepResult StepResultObject);
    void pickedNewField(int index);
    void pickedNewStep(int fieldIndex,int stepIndex);

private:
    void getUserData();
    Ui::StepResult *ui;
    BaseStepResult StepResultObject;
    int nos;
    bool validPick=true;
    double minValAuto, maxValAuto;
};

#endif // STEPRESULT_H
