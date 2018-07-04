#include "cuttingplane.h"
#include "ui_cuttingplane.h"

CuttingPlane::CuttingPlane(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CuttingPlane)
{
    ui->setupUi(this);
}

CuttingPlane::~CuttingPlane()
{
    delete ui;
}

void CuttingPlane::on_closeButton_clicked()
{
    this->close();
}

void CuttingPlane::on_okButton_clicked()
{
    clipViewObject.normX=ui->xNormLine->text().toDouble();
    clipViewObject.normY=ui->yNormLine->text().toDouble();
    clipViewObject.normZ=ui->zNormLine->text().toDouble();
    clipViewObject.pointX=ui->xCoordLine->text().toDouble();
    clipViewObject.pointY=ui->yCoordLine->text().toDouble();
    clipViewObject.pointZ=ui->zCoordLine->text().toDouble();

    if(ui->clipFlagCheckBox->isChecked())
    {
        clipViewObject.clipFlag=true;
    }
    else
    {
        clipViewObject.clipFlag=false;
    }

    clipViewObject.setToVector();
    emit sendClipInformation(clipViewObject);
    this->close();
}
