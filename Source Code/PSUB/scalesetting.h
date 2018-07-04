#ifndef SCALESETTING_H
#define SCALESETTING_H

#include <QDialog>
#include "BasedClass/basescaleclass.h"

namespace Ui {
class ScaleSetting;
}

class ScaleSetting : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleSetting(QWidget *parent = 0);
    ~ScaleSetting();

signals:
    void sendScaleInformation(BaseScaleClass scaleObject);
    void chooseNewField(int fieldPosition);
    void chooseNewStep(int step);

private slots:
    void on_closeButton_clicked();
    void on_applyButton_clicked();

private:
    Ui::ScaleSetting *ui;
    BaseScaleClass scaleObject;
};

#endif // SCALESETTING_H
