#ifndef IMPORTFEFLOWMESH_H
#define IMPORTFEFLOWMESH_H

#include <QDialog>
#include <BasedClass/importfile.h>
#include <QFileDialog>
#include <QMessageBox>
using namespace std;
using namespace Eigen;

namespace Ui {
class importFeflowMesh;
}

class importFeflowMesh : public QDialog
{
    Q_OBJECT

public:
    explicit importFeflowMesh(QWidget *parent = 0);
    ~importFeflowMesh();

private slots:
    void on_browseButton1_clicked();//coordinate browse
    void on_browseButton2_clicked();//element browse
    void on_closeButton_clicked(); //close button
    void on_importButton_clicked(); //start import file

signals:
    void sendMeshData(Ref<MatrixXd> cooordinates,Ref<MatrixXd> elements);

private:
    Ui::importFeflowMesh *ui;
    MatrixXd coordinates;
    MatrixXd elements;
    int non, noe;
    int row,col;
    int skipHeadingCoord=0;
    int skipHeadingElement=0;
    QString coordinatesFileName;
    QString elementsFileName;
};

#endif // IMPORTFEFLOWMESH_H
