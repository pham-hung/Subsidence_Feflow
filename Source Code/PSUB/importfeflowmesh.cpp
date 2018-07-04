#include "importfeflowmesh.h"
#include "ui_importfeflowmesh.h"

importFeflowMesh::importFeflowMesh(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::importFeflowMesh)
{
    ui->setupUi(this);
}

importFeflowMesh::~importFeflowMesh()
{
    delete ui;
}

void importFeflowMesh::on_browseButton1_clicked()
{
    coordinatesFileName=QFileDialog::getOpenFileName();
    ui->coordinatesLine->setText(coordinatesFileName);
}

void importFeflowMesh::on_closeButton_clicked()
{
    this->close();
}

void importFeflowMesh::on_browseButton2_clicked()
{
    elementsFileName=QFileDialog::getOpenFileName();
    ui->elementLine->setText(elementsFileName);
}

void importFeflowMesh::on_importButton_clicked()
{
    skipHeadingCoord=ui->skipHeadingLineCoord->text().toInt();
    skipHeadingElement=ui->skipHeadingElementLine->text().toInt();;
    //Coordinates
    importFile *feflowImport= new importFile;
    feflowImport->setSkipHeading(skipHeadingCoord);
    feflowImport->setFileName(coordinatesFileName,true);
    feflowImport->getFile();
    coordinates=feflowImport->dataFile;

    //element
    feflowImport->setSkipHeading(skipHeadingElement);
    feflowImport->setFileName(elementsFileName,true);
    feflowImport->getFile();
    elements=feflowImport->dataFile;

    //done
    emit sendMeshData(coordinates,elements);
    QMessageBox::information(Q_NULLPTR,"DONE","Files are imported successfully");
    this->close();
}
