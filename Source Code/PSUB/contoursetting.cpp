#include "contoursetting.h"
#include "ui_contoursetting.h"


ContourSetting::ContourSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContourSetting)
{
    ui->setupUi(this);
}

ContourSetting::~ContourSetting()
{
    delete ui;
}

void ContourSetting::on_okButton_clicked()
{
    colorObject.noc=ui->nocLine->text().toInt();
    if(colorObject.noc<1)
    {
        colorObject.noc=10;
        ui->nocLine->setText("10");
    }

    colorObject.contourPosition=ui->positionCombo->currentIndex();
    colorObject.fontSize=ui->fontSizeLine->text().toInt();
    if(colorObject.fontSize<0)
    {
        colorObject.fontSize=10;
        ui->fontSizeLine->setText("10");
    }
    colorObject.numericType=ui->numericCombo->currentIndex();

    if(ui->nodeCheckBox->isChecked())
    {
        colorObject.nodeVisible=true;
    }
    else
    {
        colorObject.nodeVisible=false;
    }

    if(ui->meshCheckBox->isChecked())
    {
        colorObject.meshVisible=true;
    }
    else
    {
        colorObject.meshVisible=false;
    }

    if(ui->resultCheckBox->isChecked())
    {
        colorObject.resultVisible=true;
    }
    else
    {
        colorObject.resultVisible=false;
    }

    if(ui->axeCheckBox->isChecked())
    {
        colorObject.axeVisible=true;
    }
    else
    {
        colorObject.axeVisible=false;
    }

    if(ui->dateCheckBox->isChecked())
    {
        colorObject.dateVisible=true;
    }
    else
    {
        colorObject.dateVisible=false;
    }


    if(ui->titleCheckBox->isChecked())
    {
        colorObject.titleVisible=true;
    }
    else
    {
        colorObject.titleVisible=false;
    }

    colorObject.title=ui->titleLine->text();

    if(ui->maxCheckBox->isChecked())
    {
        colorObject.maxVisible=true;
    }
    else
    {
        colorObject.maxVisible=false;
    }
    if(ui->deformMeshCheckBox->isChecked())
    {
        colorObject.deformedMeshVisible=true;
    }
    else
    {
        colorObject.deformedMeshVisible=false;
    }
    emit sendColorInformation(colorObject);
    this->close();
}

void ContourSetting::on_closeButton_clicked()
{
    this->close();
}
