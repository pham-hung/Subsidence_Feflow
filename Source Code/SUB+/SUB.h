#ifndef SUB_H
#define SUB_H
#include <ifm/module.h>
#include <ifm/graphic.h>
#include <ifm/document.h>
#include <ifm/archive.h>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/PardisoSupport>

#include <iostream>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <vector>
#include <thread>
#include <QFile>
#include <QString>
#include <QElapsedTimer>

#include "writetofile.h"
#include "sub_global.h"
#include "windows.h"
#include "elementmatrix.h"

#define EIGEN_USE_MKL_ALL

using namespace std;
using namespace Eigen;

class SUBSHARED_EXPORT CSub:public QObject
{
Q_OBJECT
public:
    CSub(IfmDocument pDoc);
    ~CSub();

#pragma region IFM_Definitions
public:
    static CSub* FromHandle(IfmDocument pDoc);
    void Serialize (IfmDocument pDoc, IfmArchive pArc);
    void OnActivate (IfmDocument pDoc, Widget wParent);
    void OnEditDocument (IfmDocument pDoc, Widget wParent);
    void PreEnterSimulator (IfmDocument pDoc);
    void PostEnterSimulator (IfmDocument pDoc);
    void OnLeaveSimulator (IfmDocument pDoc);
    void OnEnterProblemEditor (IfmDocument pDoc);
    void OnLeaveProblemEditor (IfmDocument pDoc);
    void PreSimulation (IfmDocument pDoc);
    void PostSimulation (IfmDocument pDoc);
    void PreTimeStep (IfmDocument pDoc);
    void PostTimeStep (IfmDocument pDoc);
    void PreFlowSimulation (IfmDocument pDoc);
    void PostFlowSimulation (IfmDocument pDoc);
    void PreMassSimulation (IfmDocument pDoc, int iSpecies);
    void PostMassSimulation (IfmDocument pDoc, int iSpecies);
    void PreHeatSimulation (IfmDocument pDoc);
    void PostHeatSimulation (IfmDocument pDoc);
    IfmBool OnTimeStepConstraint (IfmDocument pDoc, double tNow, double* dtProposed);
    void OnUpdateMaterial (IfmDocument pDoc, IfmParamID nParam, int nSpecies, double tTime);
    void PostLoadDocument (IfmDocument pDoc);
    void PreSaveDocument (IfmDocument pDoc);
    void PostSaveDocument (IfmDocument pDoc);
    IfmResult OnChangeProblemClass (IfmDocument pDoc);
    void OnChangeTopology (IfmDocument pDoc);
    IfmBool OnLockPowerID (IfmDocument pDoc, int nID);
    IfmResult PreRefineProblem (IfmDocument pDoc, int, int);
    void PostRefineProblem (IfmDocument pDoc, IfmBool);
    void OnMarkElementsForAMR (IfmDocument pDoc);
    void OnRefineElementAttributes (IfmDocument pDoc, int, int*, int, int*);
    void OnRefineNodeAttributes (IfmDocument pDoc, int, int, int);
    void OnStateChanged (IfmDocument pDoc, IfmDOC_STATE);
    IfmBool OnStateChanging (IfmDocument pDoc, IfmDOC_STATE);

    //Plug-in function    
    void createWorkingFolder();                   //Create two folders (Subsidence_Ouputs, Subsidence_Inputs)
    void getCoordinates();                        //get coordinates of all nodes
    void getElements();                           //get elements list
    void getMaterialFlowProperties();             //get material properties of all elements
    void getBoundaryCondition();                  //get 1st Flow Boundary condition (fixH)
    void getInitialHead();                        //get Initial head of all nodes    
    void getTimeInformation();                    //get Time Information from Feflow, constant
    void getDirichletBoundaryConditionFromUserData();  //Get Diriclet boundary condition from Feflow user data base
    void getMechanicalParametersFromUserData();    //get mechanical input parameters from user data

    //control Feflow sequential process
    void skipTimeStep();
    void repeatTimeStep();

    //Support function. Since Feflow control the main thread, all support functions are saved in Plug-in main class
    void pauseSystem(); //For debugging, doesn't depend on the Operate System
    void convertPairVectorToMatrix(vector<pair<int,double> > pairVector, MatrixXd &matrix);
    void checkAndCreateUserData();
    void releaseMemory();

    //coupled hydro-mechanical functions
    void initilizeData();
    void createBoundaryCondition();
    void assemblyGlobalMatrixMultiThread();
    void undrainedAnalysis();
    void drainedAnalysis();
    void solveDirect();
    void exportResults();
    void assignToVectorSolutions();
    void calculateStress();

    //Calculate Stress
    void calculateStressPrism6(int &eleNum);

    //extraSetting Information
    void writeExtraSettingInformation();
    void readExtraSetingInformation();

signals:
    void sendSignal(Ref<MatrixXd> coordinates,Ref<MatrixXd> elements,Ref<MatrixXd> hydroParameters, Ref<MatrixXd> mechanicalParameters,
                    Ref<MatrixXd> fixx, Ref<MatrixXd> fixy, Ref<MatrixXd> fixz, Ref<MatrixXd> fixh, Ref<MatrixXd> initialH,QString saveFolder,double timeIncrement,int numberOfStep);

public slots:


#pragma endregion

private:    
    IfmDocument m_pDoc;
    //common variables
    QElapsedTimer timer, timerAssembly; //to calculate time
    MatrixXd coordinates, elements;
    int numberOfNode, numberOfElement, degreeOfFreedom,NumberOfGroup,totalDegreeOfFreedom,numberOfNodePerElement;
    QString fileName, folderName, saveFolder, extraSettingFolder;
    MatrixXd hydroParameters, mechanicalParameters;    
    double gf;
    int numberOfNodePerSlice; //number of node per slice
    int numberOfElementPerLayer; //number of element per layer

    //Boundary conditions
    MatrixXd fixx, fixy, fixz, fixh,initialH;
    MatrixXd wellRate;
    MatrixXd DirichletAll, Dirichlet;
    MatrixXd DirichletU,DirichletAllU;
    MatrixXd DirichletD,DirichletAllD;

    //Load vector
    MatrixXd Fx,Fy,Fz,QQ,F, Fgravity;

    //Time step parameters
    double timeIncrement, initialTimeIncrement;
    double finalSimulationTime;
    int numberOfStep;
    int currentStep;
    int numberOfResultStep;
    int currentResultStep;

    //Solution matrices
    MatrixXd U,V,W,H,XX; //nodal solutions
    MatrixXd U0,V0,W0,H0,XX0; //Initial solutions (previous step)
    MatrixXd Sxx,Syy,Szz,Sxy,Syz,Sxz; //stress solutions         

    //Gauss-point
    MatrixXd gauss;
    Gauss gaussPoint;

    //Global matrix
    typedef Eigen::Triplet<double> Trip;
    std::vector<Trip> trip_total;
    SparseMatrix<double,RowMajor> KK; //Global matrix system

    //Element parameters
    double kxe, kye, kze, Ke, Ge, ve, Se, ne, Cfe, Cse, BiotCoeff, Cme;

    //For extra setting
    bool writeMeshFlag=true;
    bool writeMaterialFlag=false;
    bool writeStressFlag=true;
    int intervalResult=1;
};

#endif // SUB_H
