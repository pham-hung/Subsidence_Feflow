#include "scalesetting.h"
#include "ui_scalesetting.h"

ScaleSetting::ScaleSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScaleSetting)
{
    ui->setupUi(this);
}

ScaleSetting::~ScaleSetting()
{
    delete ui;
}

void ScaleSetting::on_closeButton_clicked()
{
    this->close();
}

void ScaleSetting::on_applyButton_clicked()
{
    scaleObject.xScale=ui->xScaleLine->text().toDouble();
    if(scaleObject.xScale<0)
    {
        scaleObject.xScale=1;
        ui->xScaleLine->setText("1");
    }

    scaleObject.yScale=ui->yScaleLine->text().toDouble();
    if(scaleObject.yScale<0)
    {
        scaleObject.yScale=1;
        ui->yScaleLine->setText("1");
    }

    scaleObject.zScale=ui->zScaleLine->text().toDouble();
    if(scaleObject.zScale<0)
    {
        scaleObject.zScale=1;
        ui->zScaleLine->setText("1");
    }

    scaleObject.deformScale=ui->deformScaleLine->text().toDouble();
    if(scaleObject.deformScale<0)
    {
        scaleObject.deformScale=1;
        ui->deformScaleLine->setText("1");
    }
    emit sendScaleInformation(scaleObject);
    this->close();
}
