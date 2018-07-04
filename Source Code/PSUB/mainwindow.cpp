#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpConnection();
    setUpLayout();
    replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpLayout()
{
    this->setGeometry(200,200,1366,768);
    ui->centralWidget->setLayout(mainLayout);
    mainLayout->addLayout(glLayout,0,0,18,10);
    mainLayout->addLayout(buttonLayout,19,0,1,10);

    buttonLayout->addWidget(replotButton);
    buttonLayout->addWidget(topButton);
    buttonLayout->addWidget(botButton);
    buttonLayout->addWidget(rightButton);
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(behindButton);
    buttonLayout->addWidget(frontButton);
    buttonLayout->addItem(spacer1);

    replotButton->setText("REPLOT");
    replotButton->setFixedWidth(100);

    topButton->setText("TOP VIEW");
    topButton->setFixedWidth(100);

    botButton->setText("BOTTOM VIEW");
    botButton->setFixedWidth(100);

    rightButton->setText("RIGHT VIEW");
    rightButton->setFixedWidth(100);

    leftButton->setText("LEFT VIEW");
    leftButton->setFixedWidth(100);

    frontButton->setText("FRONT VIEW");
    frontButton->setFixedWidth(100);

    behindButton->setText("BEHIND VIEW");
    behindButton->setFixedWidth(100);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,"EXIT PROGRAM",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::updateDeformationCoordinates()
{
    coordinatesDeform=coordinatesScale;
    int fieldIndex=stepResultObject.fieldIndex;
    int stepIndex=stepResultObject.stepIndex-1;
    vector<int> fieldValid={0,1,2,3,4,5};
    auto validCheck=std::find(fieldValid.begin(),fieldValid.end(),fieldIndex);

    if(validCheck != fieldValid.end()) //if results is H, deformation...
    {
        if((U.rows()==V.rows() && V.rows()==W.rows())&&(U.rows()>1))
        {
            coordinatesDeform.col(1)=coordinatesDeform.col(1)+U.col(stepIndex)*scaleObject.deformScale;
            coordinatesDeform.col(2)=coordinatesDeform.col(2)+V.col(stepIndex)*scaleObject.deformScale;
            coordinatesDeform.col(3)=coordinatesDeform.col(3)+W.col(stepIndex)*scaleObject.deformScale;
        }
    }
}

void MainWindow::updateScaleCoordinates()
{
    coordinatesScale=coordinates;
    if(coordinates.rows()>1)
    {
        coordinatesScale.col(0)=coordinates.col(0);
        coordinatesScale.col(1)=coordinates.col(1)*scaleObject.xScale;
        coordinatesScale.col(2)=coordinates.col(2)*scaleObject.yScale;
        coordinatesScale.col(3)=coordinates.col(3)*scaleObject.zScale;
    }
}

void MainWindow::updateResultsData()
{
    int fieldIndex=stepResultObject.fieldIndex;
    int stepIndex=stepResultObject.stepIndex-1;
    vector<int> fieldValid={0,1,2,3,4,5};
    auto validCheck=std::find(fieldValid.begin(),fieldValid.end(),fieldIndex);

    bool firstCondition=bool(validCheck != fieldValid.end());
    bool secondCondition=bool((U.rows()==V.rows() && V.rows()==W.rows())&&(U.rows()>1));


    if(firstCondition) //if results is H, deformation...
    {
        if(secondCondition)
        {
            if(fieldIndex==0)
            {
                results=H.col(stepIndex);
            }
            else if(fieldIndex==1)
            {
                results=P.col(stepIndex);
            }
            else if(fieldIndex==2)
            {
                results=U.col(stepIndex);
            }
            else if(fieldIndex==3)
            {
                results=V.col(stepIndex);
            }
            else if(fieldIndex==4)
            {
                results=W.col(stepIndex);
            }
            else if(fieldIndex==5)
            {
                results=totalDisp.col(stepIndex);
            }
            else
            {
                QMessageBox::warning(Q_NULLPTR,"ERROR","This is under developed");
            }
        }
    }
    else
    {
        QMessageBox::warning(Q_NULLPTR,"ERROR","This is under developed");
    }

}

void MainWindow::systemPause()
{
    do {
        cout << '\n' << "Press the Enter key to continue.";
    } while (cin.get() != '\n');
}

void MainWindow::runAnimation()
{
    stepResultSetting->close();
    int firstStep=stepResultObject.startStep;
    int lastStep=stepResultObject.endStep;
    if(lastStep<=firstStep)
    {
        QMessageBox::warning(Q_NULLPTR,"ERROR","Chose again start and end step for animation");
    }
    else
    {
        for(int ii=firstStep;ii<lastStep+1;ii++)
        {
            qDebug()<<"Step :"<<ii<<"Delay (ms): "<<endl;
            stepResultObject.stepIndex=ii;
            updateResultsData();
            updateDeformationCoordinates();
            replot();
            QCoreApplication::processEvents();
            QThread::msleep(stepResultObject.delay);
        }
    }
}

void MainWindow::replot()
{
    //Add widget to layout and setting
    if (glLayout->count()!=0)
    {
        glLayout->removeWidget(widget);
        widget->setParent(NULL);
        delete widget;
        widget=NULL;
    }
    widget =new GLWidget;
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
    format.setVersion(3,3);
    widget->setFormat(format);

    //Signal-slots connection
    connect(widget,SIGNAL(sendSignalToMainWindow()),this,SLOT(getSignalFromOpenGLWidget()));
    connect(widget,SIGNAL(sendValueAtMousePosition(double)),this,SLOT(getValueAtMousePosition(double)));
    connect(widget,SIGNAL(sendViewportInformation(Base3DViewport)),this,SLOT(getViewportInformation(Base3DViewport)));

    connect(this,SIGNAL(sendShownData(Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>)),widget,SLOT(getShownData(Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>)));
    connect(this,SIGNAL(sendViewportInformation(Base3DViewport)),widget,SLOT(getViewportInformation(Base3DViewport)));
    connect(this,SIGNAL(sendContourSettingInformation(BaseContourSetting)),widget,SLOT(getContourSettingInformation(BaseContourSetting)));
    connect(this,SIGNAL(sendCuttingPlaneInformation(BaseCuttingPlane)),widget,SLOT(getCuttingPlaneInformation(BaseCuttingPlane)));
    connect(this,SIGNAL(sendStepResultInformation(BaseStepResult)),widget,SLOT(getStepResultInformation(BaseStepResult)));

    connect(topButton,SIGNAL(clicked(bool)),widget,SLOT(ZpositiveToXY()));
    connect(botButton,SIGNAL(clicked(bool)),widget,SLOT(ZnegativeToXY()));
    connect(rightButton,SIGNAL(clicked(bool)),widget,SLOT(XpositiveToYZ()));
    connect(leftButton,SIGNAL(clicked(bool)),widget,SLOT(XnegativeToYZ()));
    connect(behindButton,SIGNAL(clicked(bool)),widget,SLOT(YnegativeToXZ()));
    connect(frontButton,SIGNAL(clicked(bool)),widget,SLOT(YpositiveToXZ()));

    glLayout->addWidget(widget);
    widget->forceToUpdateWiget();
}

void MainWindow::replotResetViewport()
{
    viewPortSettingObject.lockView=false;
    replot();
}

void MainWindow::on_actionMesh_File_triggered()
{
    importFeflowMesh *feflowMesh=new importFeflowMesh;
    feflowMesh->show();
    connect(feflowMesh,SIGNAL(sendMeshData(Ref<MatrixXd>,Ref<MatrixXd>)),this,SLOT(getMeshData(Ref<MatrixXd>,Ref<MatrixXd>)));
}

void MainWindow::getMeshData(Ref<MatrixXd> coordinates, Ref<MatrixXd> elements)
{
    this->coordinates=coordinates;
    this->elements=elements;
    results.resize(coordinates.rows(),1);
    results.setOnes();
    non=coordinates.rows();
    noe=elements.rows();
    updateScaleCoordinates();
    updateDeformationCoordinates();
    replotResetViewport();
}

void MainWindow::getResultsData(Ref<MatrixXd> H, Ref<MatrixXd> U, Ref<MatrixXd> V, Ref<MatrixXd> W)
{
    this->H=H;
    this->U=U;
    this->V=V;
    this->W=W;

    //Calculate total deformation and
    if (coordinates.rows()>1)
    {
        P.resize(H.rows(),H.cols());
        for (auto i=0;i<H.rows();i++)
        {
            double elevation=coordinates(i,3); //z-coordinates
            for (auto j=0;j<H.cols();j++)
            {
                P(i,j)=gf*(H(i,j)-elevation);
            }
        }
    }

    //total deformation
    if(U.rows()==V.rows() && V.rows()==W.rows())
    {
        totalDisp.resize(U.rows(),U.cols());
        for (auto i=0;i<U.rows();i++)
        {
            for (auto j=0;j<U.cols();j++)
            {
                double xDeform=U(i,j);
                double yDeform=V(i,j);
                double zDeform=W(i,j);
                double total=sqrt(xDeform*xDeform+yDeform*yDeform+zDeform*zDeform);;
                totalDisp(i,j)=total;;
            }
        }
    }
    updateDeformationCoordinates();
    replotResetViewport();
}

void MainWindow::getScaleInformation(BaseScaleClass baseObject)
{
    this->scaleObject=baseObject;
    updateScaleCoordinates();
    updateDeformationCoordinates();
    replotResetViewport();
}

void MainWindow::getColorInformation(BaseContourSetting colorObject)
{
    this->contourSettingObject=colorObject;
    viewPortSettingObject.lockView=true;
    replot();
}

void MainWindow::getCuttingPlaneInformation(BaseCuttingPlane clipViewObject)
{
    this->cuttingPlaneSettingObject=clipViewObject;
    viewPortSettingObject.lockView=true;
    replot();
}

void MainWindow::newPickedField(int fieldIndex)
{
    bool validPick=true;
    if(fieldIndex==0) //total Head
    {
        nos=H.cols();
        if(H.rows()==1)
        {
            validPick=false;
        }
    }
    else if (fieldIndex==1) //Pore pressure
    {
        nos=P.cols();
        if(P.rows()==1)
        {
            validPick=false;
        }
    }
    else if (fieldIndex==2) //X-Displacement
    {
        nos=U.cols();
        if(U.rows()==1)
        {
            validPick=false;
        }
    }
    else if (fieldIndex==3) //Y-Displacement
    {
        nos=V.cols();
        if(V.rows()==1)
        {
            validPick=false;
        }
    }
    else if (fieldIndex==4) //Z-Displacement
    {
        nos=W.cols();
        if(W.rows()==1)
        {
            validPick=false;
        }
    }
    else if (fieldIndex==5) //Total-Displacement
    {
        nos=totalDisp.cols();
        if(totalDisp.rows()==1)
        {
            validPick=false;
        }
    }    
    emit sendBackInformationNewPickedStep(nos,validPick);
    qDebug()<<"Pass newPickedField"<<endl;
    //    emit sendBackInformationNewPickedStep();
}

void MainWindow::newPickedStep(int fieldIndex, int stepIndex)
{
    double minVal, maxVal;
    if(fieldIndex==0) //total Head
    {
        minVal=H.col(stepIndex-1).minCoeff();
        maxVal=H.col(stepIndex-1).maxCoeff();
    }
    else if (fieldIndex==1) //Pore pressure
    {
        minVal=P.col(stepIndex-1).minCoeff();
        maxVal=P.col(stepIndex-1).maxCoeff();
    }
    else if (fieldIndex==2) //X-Displacement
    {
        minVal=U.col(stepIndex-1).minCoeff();
        maxVal=U.col(stepIndex-1).maxCoeff();
    }
    else if (fieldIndex==3) //Y-Displacement
    {
        minVal=V.col(stepIndex-1).minCoeff();
        maxVal=V.col(stepIndex-1).maxCoeff();
    }
    else if (fieldIndex==4) //Z-Displacement
    {
        minVal=W.col(stepIndex-1).minCoeff();
        maxVal=W.col(stepIndex-1).maxCoeff();
    }
    else if (fieldIndex==5) //Total-Displacement
    {
        minVal=totalDisp.col(stepIndex-1).minCoeff();
        maxVal=totalDisp.col(stepIndex-1).maxCoeff();
    }    
    updateResultsData();
    emit sendBackInformationNewPickedStep(minVal,maxVal);
}

void MainWindow::getStepResultInformation(BaseStepResult stepResultObject)
{
    this->stepResultObject=stepResultObject;
    updateDeformationCoordinates();
    updateResultsData();

    if(stepResultObject.animationFlag==false)
    {
        viewPortSettingObject.lockView=true;
        replot();
    }
    else
    {
        viewPortSettingObject.lockView=true;
        runAnimation();
        stepResultSetting->doneAnimation();
    }
}

void MainWindow::getSignalFromOpenGLWidget()
{
    emit sendShownData(coordinatesScale, coordinatesDeform, elements, results);
    emit sendViewportInformation(viewPortSettingObject);
    emit sendContourSettingInformation(contourSettingObject);
    emit sendCuttingPlaneInformation(cuttingPlaneSettingObject);
    emit sendStepResultInformation(stepResultObject);

    disconnect(widget,SIGNAL(sendSignalToMainWindow()),this,SLOT(getSignalFromOpenGLWidget()));
    disconnect(this,SIGNAL(sendShownData(Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>)),widget,SLOT(getShownData(Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>)));
    disconnect(this,SIGNAL(sendViewportInformation(Base3DViewport)),widget,SLOT(getViewportInformation(Base3DViewport)));
    disconnect(this,SIGNAL(sendContourSettingInformation(BaseContourSetting)),widget,SLOT(getContourSettingInformation(BaseContourSetting)));
    disconnect(this,SIGNAL(sendCuttingPlaneInformation(BaseCuttingPlane)),widget,SLOT(getCuttingPlaneInformation(BaseCuttingPlane)));
    disconnect(this,SIGNAL(sendStepResultInformation(BaseStepResult)),widget,SLOT(getStepResultInformation(BaseStepResult)));
}

void MainWindow::getValueAtMousePosition(double mouseValue)
{

}

void MainWindow::getViewportInformation(Base3DViewport viewPortSettingObject)
{
    this->viewPortSettingObject=viewPortSettingObject;
}

void MainWindow::setUpConnection()
{
    connect(scaleView,SIGNAL(sendScaleInformation(BaseScaleClass)),this,SLOT(getScaleInformation(BaseScaleClass)));
    connect(colorSetting,SIGNAL(sendColorInformation(BaseContourSetting)),this,SLOT(getColorInformation(BaseContourSetting)));
    connect(cuttingPlaneSetting,SIGNAL(sendClipInformation(BaseCuttingPlane)),this,SLOT(getCuttingPlaneInformation(BaseCuttingPlane)));
    connect(stepResultSetting,SIGNAL(pickedNewField(int)),this,SLOT(newPickedField(int)));
    connect(this,SIGNAL(sendBackInformationNewPickedStep(int,bool)),stepResultSetting,SLOT(getInformationFromMainWindow(int,bool)));
    connect(stepResultSetting,SIGNAL(pickedNewStep(int,int)),this,SLOT(newPickedStep(int,int)));
    connect(this,SIGNAL(sendBackInformationNewPickedStep(double,double)),stepResultSetting,SLOT(getInformationFromMainWindow(double,double)));
    connect(stepResultSetting,SIGNAL(sendStepResultsInformation(BaseStepResult)),this,SLOT(getStepResultInformation(BaseStepResult)));

    //connect GUI button
    connect(replotButton,SIGNAL(clicked(bool)),this,SLOT(replotResetViewport()));

}

void MainWindow::on_actionResults_File_triggered()
{
    importResultsData *feflowResults=new importResultsData;
    feflowResults->show();
    connect(feflowResults,SIGNAL(sendResultsData(Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>)),this,SLOT(getResultsData(Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>,Ref<MatrixXd>)));
}

void MainWindow::on_actionScale_Setting_triggered()
{
    scaleView->show();
}

void MainWindow::on_actionContour_Color_Setting_triggered()
{
    colorSetting->show();
}

void MainWindow::on_actionSlice_Setting_triggered()
{
    cuttingPlaneSetting->show();
}

void MainWindow::on_actionPick_Time_Step_Results_triggered()
{
    stepResultSetting->show();
}
