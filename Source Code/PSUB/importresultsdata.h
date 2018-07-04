#ifndef IMPORTRESULTSDATA_H
#define IMPORTRESULTSDATA_H

#include <QDialog>
#include "BasedClass/importfile.h"
#include <QMessageBox>

using namespace std;
using namespace Eigen;

namespace Ui {
class importResultsData;
}

class importResultsData : public QDialog
{
    Q_OBJECT

public:
    explicit importResultsData(QWidget *parent = 0);
    ~importResultsData();

signals:
    void sendResultsData(Ref<MatrixXd> H, Ref<MatrixXd> U, Ref<MatrixXd> V, Ref<MatrixXd> W);

private slots:
    void on_browse1_clicked(); //Head
    void on_browse2_clicked(); //U
    void on_browse3_clicked(); //V
    void on_browse4_clicked(); //W
    void on_importButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::importResultsData *ui;    
    MatrixXd H,U,V,W;
    QString hFileName;
    QString uFileName;
    QString vFileName;
    QString wFileName;

    int skipHeadingH=0;
    int skipHeadingU=0;
    int skipHeadingV=0;
    int skipHeadingW=0;
};

#endif // IMPORTRESULTSDATA_H
