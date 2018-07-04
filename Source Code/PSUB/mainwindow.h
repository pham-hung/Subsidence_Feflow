#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <windows.h>
#include "BasedClass/importfile.h"
#include "BasedClass/importmultifiles.h"
#include <iostream>
#include <QDebug>
#include <QFileInfoList>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QFormLayout>
#include <QTextEdit>
#include <QFile>
#include <QFileDialog>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QComboBox>
#include <QRgb>
#include <QMouseEvent>
#include <QFrame>
#include <QThread>
#include <QProcess>
#include <QRadioButton>
#include <QSpacerItem>

//Widgetclass
#include "importfeflowmesh.h"
#include "importresultsdata.h"
#include "scalesetting.h"
#include "contoursetting.h"
#include "cuttingplane.h"
#include "stepresult.h"

//Base class
#include "BasedClass/basescaleclass.h"
#include "BasedClass/basecontoursetting.h"
#include "BasedClass/basecuttingplane.h"
#include "BasedClass/basestepresult.h"
#include "BasedClass/base3dviewport.h"
#include "OpenGLCLass/glwidget.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUpLayout();
    void closeEvent(QCloseEvent *event);
    void updateDeformationCoordinates();
    void updateScaleCoordinates();
    void updateResultsData();
    void systemPause();
    void runAnimation();

private slots:
    void replot();    
    void replotResetViewport();
    void on_actionMesh_File_triggered(); //Import Feflow Mesh
    void on_actionResults_File_triggered(); //Import Feflow results
    void on_actionScale_Setting_triggered(); //scale setting
    void on_actionContour_Color_Setting_triggered(); //color setting
    void on_actionSlice_Setting_triggered(); //Cutting plane
    void on_actionPick_Time_Step_Results_triggered(); //Pick time step

    //slot from widget class
    void getMeshData(Ref<MatrixXd> coordinates,Ref<MatrixXd> elements);
    void getResultsData(Ref<MatrixXd> H,Ref<MatrixXd> U,Ref<MatrixXd> V,Ref<MatrixXd> W);
    void getScaleInformation(BaseScaleClass scaleObject);
    void getColorInformation(BaseContourSetting contourSettingObject);
    void getCuttingPlaneInformation(BaseCuttingPlane cuttingPlaneSettingObject);
    void newPickedField(int fieldIndex);
    void newPickedStep(int fieldIndex,int stepIndex);
    void getStepResultInformation(BaseStepResult stepResultObject);

    //slot from OpenGL Widgets
    void getSignalFromOpenGLWidget();
    void getValueAtMousePosition(double mouseValue);
    void getViewportInformation(Base3DViewport viewPortSettingObject);

signals:
    void sendBackInformationNewPickedStep(int,bool);      //send step
    void sendBackInformationNewPickedStep(double,double); //send max min values

    //signals to OpenGL Widget
    void sendShownData(Ref<MatrixXd> coordinatesScale, Ref<MatrixXd> coordinatesDeform, Ref<MatrixXd> elements, Ref<MatrixXd> results);
    void sendViewportInformation(Base3DViewport viewPortSettingObject);
    void sendContourSettingInformation(BaseContourSetting contourSettingObject);
    void sendCuttingPlaneInformation(BaseCuttingPlane cuttingPlaneSettingObject);
    void sendStepResultInformation(BaseStepResult stepResultObject);

private:
    void setUpConnection(); //set up signal and slot connectio between objects
    Ui::MainWindow *ui;

    //initialization
    MatrixXd coordinates=MatrixXd::Zero(1,1);
    MatrixXd coordinatesScale=MatrixXd::Zero(1,1);
    MatrixXd coordinatesDeform=MatrixXd::Zero(1,1); //after deformon
    MatrixXd elements=MatrixXd::Zero(1,1);
    MatrixXd H=MatrixXd::Zero(1,1);
    MatrixXd P=MatrixXd::Zero(1,1);
    MatrixXd U=MatrixXd::Zero(1,1);
    MatrixXd V=MatrixXd::Zero(1,1);
    MatrixXd W=MatrixXd::Zero(1,1);
    MatrixXd totalDisp=MatrixXd::Zero(1,1);
    MatrixXd results=MatrixXd::Zero(1,1);     //result View

    int non=0;
    int noe=0;
    int nos=0; //number of Step
    double gf=9.8064;
    int fieldIndex;

    //External Widget data
    BaseScaleClass scaleObject;     //setting scale view
    ScaleSetting *scaleView=new ScaleSetting;

    BaseContourSetting contourSettingObject; //colorBand setting
    ContourSetting *colorSetting=new ContourSetting;

    BaseCuttingPlane cuttingPlaneSettingObject; //Cutting Plane
    CuttingPlane *cuttingPlaneSetting=new CuttingPlane;

    BaseStepResult stepResultObject; //Step Result
    StepResult *stepResultSetting = new StepResult;

    Base3DViewport viewPortSettingObject;
    //Data for OpenGL class


    //Data for main window GUI
    QPushButton *replotButton=new QPushButton;
    QPushButton *topButton=new QPushButton;
    QPushButton *botButton=new QPushButton;
    QPushButton *leftButton=new QPushButton;
    QPushButton *rightButton=new QPushButton;
    QPushButton *behindButton=new QPushButton;
    QPushButton *frontButton=new QPushButton;

    //Layout
    QGridLayout *mainLayout=new QGridLayout;
    QVBoxLayout *glLayout = new QVBoxLayout;
    QBoxLayout *buttonLayout= new QBoxLayout(QBoxLayout::LeftToRight);
    QSpacerItem *spacer1 = new QSpacerItem(20,10,QSizePolicy::Expanding,QSizePolicy::Minimum);

    //OpenGL
    GLWidget *widget;
};

#endif // MAINWINDOW_H
