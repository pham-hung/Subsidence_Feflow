#include "importresultsdata.h"
#include "ui_importresultsdata.h"

importResultsData::importResultsData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::importResultsData)
{
    ui->setupUi(this);
}

importResultsData::~importResultsData()
{
    delete ui;
}

void importResultsData::on_browse1_clicked()
{
    //Total head
    hFileName=QFileDialog::getOpenFileName();
    ui->totalHeadLine->setText(hFileName);
}

void importResultsData::on_browse2_clicked()
{
    //X displacement
    uFileName=QFileDialog::getOpenFileName();
    ui->xDispLine->setText(uFileName);
}

void importResultsData::on_browse3_clicked()
{
    //Y displacement
    vFileName=QFileDialog::getOpenFileName();
    ui->yDispLine->setText(vFileName);
}

void importResultsData::on_browse4_clicked()
{
    //Z displacement
    wFileName=QFileDialog::getOpenFileName();
    ui->zDispLine->setText(wFileName);
}

void importResultsData::on_importButton_clicked()
{
    skipHeadingH=ui->skipHeading1->text().toInt();
    skipHeadingU=ui->skipHeading2->text().toInt();
    skipHeadingV=ui->skipHeading3->text().toInt();
    skipHeadingW=ui->skipHeading4->text().toInt();

    importFile *resultImport =new importFile;

    //total Head
    resultImport->setSkipHeading(skipHeadingH);
    resultImport->setFileName(hFileName,true);
    resultImport->getFile();
    H=resultImport->dataFile;

    //X displacement
    resultImport->setSkipHeading(skipHeadingU);
    resultImport->setFileName(uFileName,true);
    resultImport->getFile();
    U=resultImport->dataFile;

    //Y displacement
    resultImport->setSkipHeading(skipHeadingV);
    resultImport->setFileName(vFileName,true);
    resultImport->getFile();
    V=resultImport->dataFile;

    //Z displacement
    resultImport->setSkipHeading(skipHeadingW);
    resultImport->setFileName(wFileName,true);
    resultImport->getFile();
    W=resultImport->dataFile;
    emit sendResultsData(H,U,V,W);
    QMessageBox::information(Q_NULLPTR,"DONE","Files are imported successfully");
    this->close();
}

void importResultsData::on_closeButton_clicked()
{
    this->close();
}
