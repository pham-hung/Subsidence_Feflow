#include "stepresult.h"
#include "ui_stepresult.h"

StepResult::StepResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StepResult)
{
    ui->setupUi(this);
    ui->resultCombo->setCurrentIndex(-1);
}

StepResult::~StepResult()
{
    delete ui;
}

void StepResult::doneAnimation()
{
    StepResultObject.animationFlag=false;
}

void StepResult::on_animationStart_clicked()
{
    getUserData();
    StepResultObject.animationFlag=true;
    emit sendStepResultsInformation(StepResultObject);
    this->close();
}


void StepResult::on_resultCombo_currentIndexChanged(int index)
{
    emit pickedNewField(index);
}

void StepResult::getInformationFromMainWindow(int nos, bool validPick)
{    
    qDebug()<<"Get information from Main Window"<<endl;
    this->nos=nos;
    this->validPick=validPick;
    if(validPick==false)
    {
        QMessageBox::warning(Q_NULLPTR,"ERROR","This selection has no data, import data first");
        qDebug()<<"Step index: "<<ui->stepCombo->currentIndex();
        ui->stepCombo->clear();
        qDebug()<<"Step index: "<<ui->stepCombo->currentIndex();
        ui->startCombo->clear();
        ui->endCombo->clear();
    }
    else
    {
        ui->stepCombo->clear();
        qDebug()<<"Step index: "<<ui->stepCombo->currentIndex();
        for (int i=0;i<nos;i++)
        {
            QString newStep=QString::number(i+1,10);
            ui->stepCombo->addItem(newStep);
            ui->startCombo->addItem(newStep);
            ui->endCombo->addItem(newStep);
        }
    }
}

void StepResult::getInformationFromMainWindow(double minVal, double maxVal)
{
    maxValAuto=maxVal;
    minValAuto=minVal;
    if(ui->maxCombo->currentIndex()==0) //Auto
    {
        ui->minLine->setText(QString::number(minValAuto,'g',6));
        ui->maxLine->setText(QString::number(maxValAuto,'g',6));
        ui->maxLine->setEnabled(false);
        ui->minLine->setEnabled(false);
    }
    on_okButton_clicked();
}

void StepResult::on_closeButton_clicked()
{
    this->close();
}

void StepResult::on_stepCombo_currentIndexChanged(int index)
{    
    int fieldIndex=ui->resultCombo->currentIndex();
    int stepIndex=ui->stepCombo->currentText().toInt();
    if(index>=0)
    {
        emit pickedNewStep(fieldIndex,stepIndex);
    }
}

void StepResult::on_maxCombo_currentIndexChanged(int index)
{
    if(ui->maxCombo->currentIndex()==1) //manualy
    {
        ui->maxLine->setEnabled(true);
        ui->maxLine->setText("100");
        ui->minLine->setEnabled(true);
        ui->minLine->setText("-100");
    }
    else
    {
        ui->maxLine->setEnabled(false);
        ui->minLine->setEnabled(false);
        ui->minLine->setText(QString::number(minValAuto,'g',6));
        ui->maxLine->setText(QString::number(maxValAuto,'g',6));
    }
}

void StepResult::on_okButton_clicked()
{    
    getUserData();
    StepResultObject.animationFlag=false;
    emit sendStepResultsInformation(StepResultObject);
}

void StepResult::getUserData()
{
    StepResultObject.fieldIndex=ui->resultCombo->currentIndex();
    StepResultObject.stepIndex=ui->stepCombo->currentText().toInt();
    if(ui->maxCombo->currentIndex()==0)
    {
        StepResultObject.autoMaxMin=true;
        ui->maxLine->setEnabled(false);
        ui->minLine->setEnabled(false);
        ui->minLine->setText(QString::number(minValAuto,'g',6));
        ui->maxLine->setText(QString::number(maxValAuto,'g',6));
    }
    else
    {
        StepResultObject.autoMaxMin=false;
    }
    StepResultObject.maxValue=ui->maxLine->text().toDouble();
    StepResultObject.minValue=ui->minLine->text().toDouble();
    StepResultObject.startStep=ui->startCombo->currentText().toInt();
    StepResultObject.endStep=ui->endCombo->currentText().toInt();
    StepResultObject.delay=ui->delayLine->text().toInt();

    if(ui->autoChangeValueCheckBox->isChecked())
    {
        StepResultObject.autoChangeMaxMin=true;
    }
    else
    {
        StepResultObject.autoChangeMaxMin=false;
    }
}
