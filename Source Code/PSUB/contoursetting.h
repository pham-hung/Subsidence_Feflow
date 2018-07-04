#ifndef CONTOURSETTING_H
#define CONTOURSETTING_H

#include <QDialog>
#include "BasedClass/basecontoursetting.h"

namespace Ui {
class ContourSetting;
}

class ContourSetting : public QDialog
{
    Q_OBJECT

public:
    explicit ContourSetting(QWidget *parent = 0);
    ~ContourSetting();

private slots:
    void on_okButton_clicked();
    void on_closeButton_clicked();

signals:
    void sendColorInformation(BaseContourSetting colorObject);

private:
    Ui::ContourSetting *ui;
    BaseContourSetting colorObject;
};

#endif // CONTOURSETTING_H
