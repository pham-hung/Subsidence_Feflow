#ifndef CUTTINGPLANE_H
#define CUTTINGPLANE_H

#include <QDialog>
#include "BasedClass/basecuttingplane.h"

namespace Ui {
class CuttingPlane;
}

class CuttingPlane : public QDialog
{
    Q_OBJECT

public:
    explicit CuttingPlane(QWidget *parent = 0);
    ~CuttingPlane();

signals:
    void sendClipInformation(BaseCuttingPlane clipViewObject);

private slots:
    void on_closeButton_clicked();
    void on_okButton_clicked();

private:
    Ui::CuttingPlane *ui;
    BaseCuttingPlane clipViewObject;
};

#endif // CUTTINGPLANE_H
