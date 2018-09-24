#include "SUB.h"
IfmModule g_pMod;  /* Global handle related to this plugin */

#pragma region IFM_Definitions
/* --- IFMREG_BEGIN --- */
/*  -- Do not edit! --  */

static void ExceptionHandler (IfmHandle, IfmExceptionContext*);
static IfmResult OnInitModule (IfmHandle);
static void OnExitModule (IfmHandle);
static IfmResult OnBeginDocument (IfmDocument);
static void OnEndDocument (IfmDocument);
static void Serialize (IfmDocument, IfmArchive);
static void OnActivate (IfmDocument, Widget);
static void OnEditDocument (IfmDocument, Widget);
static void OnEnterProblemEditor (IfmDocument);
static void OnLeaveProblemEditor (IfmDocument);
static void PreEnterSimulator (IfmDocument);
static void PostEnterSimulator (IfmDocument);
static void OnLeaveSimulator (IfmDocument);
static void PreSimulation (IfmDocument);
static void PostSimulation (IfmDocument);
static void PreTimeStep (IfmDocument);
static void PostTimeStep (IfmDocument);
static void PreFlowSimulation (IfmDocument);
static void PostFlowSimulation (IfmDocument);
static void PreMassSimulation (IfmDocument, int);
static void PostMassSimulation (IfmDocument, int);
static void PreHeatSimulation (IfmDocument);
static void PostHeatSimulation (IfmDocument);
static IfmBool OnTimeStepConstraint (IfmDocument, double, double*);
static void OnUpdateMaterial (IfmDocument, IfmParamID, int, double);
static void PostLoadDocument (IfmDocument pDoc);
static void PreSaveDocument (IfmDocument pDoc);
static void PostSaveDocument (IfmDocument pDoc);
static IfmResult OnChangeProblemClass (IfmDocument);
static void OnChangeTopology (IfmDocument);
static IfmBool OnLockPowerID (IfmDocument, int);
static IfmResult PreRefineProblem (IfmDocument, int, int);
static void PostRefineProblem (IfmDocument, IfmBool);
static void OnMarkElementsForAMR (IfmDocument);
static void OnRefineElementAttributes (IfmDocument, int, int*, int, int*);
static void OnRefineNodeAttributes (IfmDocument, int, int, int);
static void OnStateChanged (IfmDocument, IfmDOC_STATE);
static IfmBool OnStateChanging (IfmDocument, IfmDOC_STATE);

/*
 * Enter a short description between the quotation marks in the following lines:
 */
static const char szDesc[] =
        "Please, insert a plug-in description here!";

#ifdef __cplusplus
extern "C"
#endif /* __cplusplus */

IfmResult RegisterModule(IfmModule pMod)
{
    if (IfmGetFeflowVersion (pMod) < IFM_REQUIRED_VERSION)
        return False;
    g_pMod = pMod;
    IfmRegisterModule (pMod, "SIMULATION", "SUB+", "SUB+", 0x1000);
    IfmSetDescriptionString (pMod, szDesc);
    IfmSetCopyrightPath (pMod, "SUB.txt");
    IfmSetHtmlPage (pMod, "SUB.htm");
    IfmSetPrimarySource (pMod, "SUB.cpp");
    IfmRegisterProc (pMod, "ExceptionHandler", 1, (IfmProc)ExceptionHandler);
    IfmRegisterProc (pMod, "OnInitModule", 1, (IfmProc)OnInitModule);
    IfmRegisterProc (pMod, "OnExitModule", 1, (IfmProc)OnExitModule);
    IfmRegisterProc (pMod, "OnBeginDocument", 1, (IfmProc)OnBeginDocument);
    IfmRegisterProc (pMod, "OnEndDocument", 1, (IfmProc)OnEndDocument);
    IfmRegisterProc (pMod, "Serialize", 1, (IfmProc)Serialize);
    IfmRegisterProc (pMod, "OnActivate", 1, (IfmProc)OnActivate);
    IfmRegisterProc (pMod, "OnEditDocument", 1, (IfmProc)OnEditDocument);
    IfmRegisterProc (pMod, "OnEnterProblemEditor", 1, (IfmProc)OnEnterProblemEditor);
    IfmRegisterProc (pMod, "OnLeaveProblemEditor", 1, (IfmProc)OnLeaveProblemEditor);
    IfmRegisterProc (pMod, "PreEnterSimulator", 1, (IfmProc)PreEnterSimulator);
    IfmRegisterProc (pMod, "PostEnterSimulator", 1, (IfmProc)PostEnterSimulator);
    IfmRegisterProc (pMod, "OnLeaveSimulator", 1, (IfmProc)OnLeaveSimulator);
    IfmRegisterProc (pMod, "PreSimulation", 1, (IfmProc)PreSimulation);
    IfmRegisterProc (pMod, "PostSimulation", 1, (IfmProc)PostSimulation);
    IfmRegisterProc (pMod, "PreTimeStep", 1, (IfmProc)PreTimeStep);
    IfmRegisterProc (pMod, "PostTimeStep", 1, (IfmProc)PostTimeStep);
    IfmRegisterProc (pMod, "OnTimeStepConstraint", 1, (IfmProc)OnTimeStepConstraint);
    IfmRegisterProc (pMod, "OnUpdateMaterial", 1, (IfmProc)OnUpdateMaterial);
    IfmRegisterProc (pMod, "PreFlowSimulation", 1, (IfmProc)PreFlowSimulation);
    IfmRegisterProc (pMod, "PostFlowSimulation", 1, (IfmProc)PostFlowSimulation);
    IfmRegisterProc (pMod, "PreMassSimulation", 1, (IfmProc)PreMassSimulation);
    IfmRegisterProc (pMod, "PostMassSimulation", 1, (IfmProc)PostMassSimulation);
    IfmRegisterProc (pMod, "PreHeatSimulation", 1, (IfmProc)PreHeatSimulation);
    IfmRegisterProc (pMod, "PostHeatSimulation", 1, (IfmProc)PostHeatSimulation);
    IfmRegisterProc (pMod, "PreSaveDocument", 1, (IfmProc)PreSaveDocument);
    IfmRegisterProc (pMod, "PostSaveDocument", 1, (IfmProc)PostSaveDocument);
    IfmRegisterProc (pMod, "PostLoadDocument", 1, (IfmProc)PostLoadDocument);
    IfmRegisterProc (pMod, "OnChangeProblemClass", 1, (IfmProc)OnChangeProblemClass);
    IfmRegisterProc (pMod, "OnChangeTopology", 1, (IfmProc)OnChangeTopology);
    IfmRegisterProc (pMod, "OnLockPowerID", 1, (IfmProc)OnLockPowerID);
    IfmRegisterProc (pMod, "OnMarkElementsForAMR", 1, (IfmProc)OnMarkElementsForAMR);
    IfmRegisterProc (pMod, "OnRefineElementAttributes", 1, (IfmProc)OnRefineElementAttributes);
    IfmRegisterProc (pMod, "OnRefineNodeAttributes", 1, (IfmProc)OnRefineNodeAttributes);
    IfmRegisterProc (pMod, "OnStateChanged", 1, (IfmProc)OnStateChanged);
    IfmRegisterProc (pMod, "OnStateChanging", 1, (IfmProc)OnStateChanging);
    IfmRegisterProc (pMod, "PostRefineProblem", 1, (IfmProc)PostRefineProblem);
    IfmRegisterProc (pMod, "PreRefineProblem", 1, (IfmProc)PreRefineProblem);
    return True;
}

static void Serialize (IfmDocument pDoc, IfmArchive pArc)
{
    CSub::FromHandle(pDoc)->Serialize (pDoc, pArc);
}
static void PostLoadDocument (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PostLoadDocument (pDoc);
}
static void PreSaveDocument (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PreSaveDocument (pDoc);
}
static void PostSaveDocument (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PostSaveDocument (pDoc);
}
static void OnActivate (IfmDocument pDoc, Widget button)
{
    CSub::FromHandle(pDoc)->OnActivate (pDoc, button);
}
static void OnEditDocument (IfmDocument pDoc, Widget wParent)
{
    CSub::FromHandle(pDoc)->OnEditDocument (pDoc, wParent);
}
static void OnEnterProblemEditor (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->OnEnterProblemEditor (pDoc);
}
static void OnLeaveProblemEditor (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->OnLeaveProblemEditor (pDoc);
}
static void PreEnterSimulator (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PreEnterSimulator (pDoc);
}
static void PostEnterSimulator (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PostEnterSimulator (pDoc);
}
static void OnLeaveSimulator (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->OnLeaveSimulator (pDoc);
}
static void PreSimulation (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PreSimulation (pDoc);
}
static void PostSimulation (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PostSimulation (pDoc);
}
static void PreTimeStep (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PreTimeStep (pDoc);
}
static void PostTimeStep (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PostTimeStep (pDoc);
}
static IfmBool OnTimeStepConstraint (IfmDocument pDoc, double tNow, double* dtProposed)
{
    return CSub::FromHandle(pDoc)->OnTimeStepConstraint (pDoc, tNow, dtProposed);
}
static void OnUpdateMaterial (IfmDocument pDoc, IfmParamID nParam, int nSpecies, double tTime)
{
    CSub::FromHandle(pDoc)->OnUpdateMaterial (pDoc, nParam, nSpecies, tTime);
}
static void PreFlowSimulation (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PreFlowSimulation (pDoc);
}
static void PostFlowSimulation (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PostFlowSimulation (pDoc);
}
static void PreMassSimulation (IfmDocument pDoc, int iSpecies)
{
    CSub::FromHandle(pDoc)->PreMassSimulation (pDoc, iSpecies);
}
static void PostMassSimulation (IfmDocument pDoc, int iSpecies)
{
    CSub::FromHandle(pDoc)->PostMassSimulation (pDoc, iSpecies);
}
static void PreHeatSimulation (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PreHeatSimulation (pDoc);
}
static void PostHeatSimulation (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->PostHeatSimulation (pDoc);
}
static IfmResult OnChangeProblemClass (IfmDocument pDoc)
{
    return CSub::FromHandle(pDoc)->OnChangeProblemClass (pDoc);
}
static void OnChangeTopology (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->OnChangeTopology (pDoc);
}
static IfmBool OnLockPowerID (IfmDocument pDoc, int nPowerID)
{
    return CSub::FromHandle(pDoc)->OnLockPowerID (pDoc, nPowerID);
}
static void OnMarkElementsForAMR (IfmDocument pDoc)
{
    CSub::FromHandle(pDoc)->OnMarkElementsForAMR (pDoc);
}
static IfmResult PreRefineProblem (IfmDocument pDoc, int nNodeCount2D, int nElemCount2D)
{
    return CSub::FromHandle(pDoc)->PreRefineProblem (pDoc, nNodeCount2D, nElemCount2D);
}
static void PostRefineProblem (IfmDocument pDoc, IfmBool bDiscard)
{
    CSub::FromHandle(pDoc)->PostRefineProblem (pDoc, bDiscard);
}
static void OnRefineElementAttributes (IfmDocument pDoc, int nNewCount, int* pNewElem,
                                       int nOldCount, int* pOldElem)
{
    CSub::FromHandle(pDoc)->OnRefineElementAttributes (pDoc, nNewCount, pNewElem, nOldCount, pOldElem);
}
static void OnRefineNodeAttributes (IfmDocument pDoc,
                                    int nNewNode, int nNodeFrom, int nNodeTo)
{
    CSub::FromHandle(pDoc)->OnRefineNodeAttributes (pDoc, nNewNode, nNodeFrom, nNodeTo);
}
static IfmBool OnStateChanging (IfmDocument pDoc, IfmDOC_STATE newState)
{
    return CSub::FromHandle(pDoc)->OnStateChanging (pDoc, newState);
}
static void OnStateChanged (IfmDocument pDoc, IfmDOC_STATE newState)
{
    CSub::FromHandle(pDoc)->OnStateChanged (pDoc, newState);
}

/* --- IFMREG_END --- */
#pragma endregion


static void ExceptionHandler (IfmHandle pHdl, IfmExceptionContext* pEx)
{
    /*
   * TODO: If you want to suppress the warning message in FEFLOW's LOG window
   *	   the next two lines must be commented out!
   */
    IfmWarning (pHdl, "%s: %s! Skipped...\n", pEx->proc, pEx->reason);

    /*
   * TODO:
   *  If you want to abort the simulation step you can use the action:
   *
      pEx->action = IfmEX_ABORT;
   */

    /*
   * TODO:
   *  If you want to ignore the exception condition
   *  you can use the following construction:
   *  (Which member of argUnion takes affect depends on argType)
   *
      pEx->argUnion.aDouble = 0.;
      pEx->action = IfmEX_CONTINUE;
   *
   */
}

static IfmResult OnInitModule (IfmHandle pHdl)
{
    /*
   * TODO: Add your own initialization code here ...
   */
    return True;
}

static void OnExitModule (IfmHandle pHdl)
{
    /*
   * TODO: Add your own code here ...
   */
}

static IfmResult OnBeginDocument (IfmDocument pDoc)
{
    if (IfmDocumentVersion (pDoc) < IFM_CURRENT_DOCUMENT_VERSION)
        return false;

    try {
        IfmDocumentSetUserData(pDoc, new CSub(pDoc));
    }
    catch (...) {
        return false;
    }

    return true;
}

static void OnEndDocument (IfmDocument pDoc)
{
    delete CSub::FromHandle(pDoc);
}

///////////////////////////////////////////////////////////////////////////
// Implementation of CSub

// Constructor
CSub::CSub (IfmDocument pDoc)
    : m_pDoc(pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

// Destructor
CSub::~CSub ()
{
    /*
   * TODO: Add your own code here ...
   */
}

// Obtaining class instance from document handle
CSub* CSub::FromHandle (IfmDocument pDoc)
{
    return reinterpret_cast<CSub*>(IfmDocumentGetUserData(pDoc));
}

// Callbacks
void CSub::Serialize (IfmDocument pDoc, IfmArchive pArc)
{
    /*
   * TODO: Add your own code here ...
   */

}

void CSub::PostLoadDocument (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::PreSaveDocument (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::PostSaveDocument (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::OnActivate (IfmDocument pDoc, Widget button)
{
    /*
   * TODO: Add your own code here ...
   */
    //Set up debugging tool
    checkAndCreateUserData();
    createWorkingFolder();
    writeExtraSettingInformation();
}

void CSub::OnEditDocument (IfmDocument pDoc, Widget wParent)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::OnEnterProblemEditor (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::OnLeaveProblemEditor (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::PreEnterSimulator (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::PostEnterSimulator (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::OnLeaveSimulator (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::PreSimulation (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
    createWorkingFolder();               //create SUB_Inputs and SUB_Outputs folder
    readExtraSetingInformation();        //get Extra Setting, if not, use default values
    getCoordinates();                    //result is coordinate matrix
    getElements();                       //result is element matrix
    getDirichletBoundaryConditionFromUserData(); //results are fixX, fixY, fixZ
    getMechanicalParametersFromUserData(); //results are mechanical input parameters
    getMaterialFlowProperties();         //result is elementMaterial matrix
    getBoundaryCondition();              //result is fixH
    getInitialHead();                    //result is initialHead matrix
    getTimeInformation();

    //createBoundaryCondition();
    initilizeData();
    createBoundaryCondition();
    undrainedAnalysis();
    drainedAnalysis();
    exportResults();
    releaseMemory();

    //Abort Feflow operation
    IfmInfo(m_pDoc,"Finished, check the output folder for results");
    IfmInfo(m_pDoc,saveFolder.toLatin1().data());
}

void CSub::PostSimulation (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::PreTimeStep (IfmDocument pDoc)
{
    skipTimeStep();
    FreeConsole();
}

void CSub::PostTimeStep (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */

    //    IfmSetSimulationControlFlag(m_pDoc,IfmCTL_SKIP);
}

IfmBool CSub::OnTimeStepConstraint (IfmDocument pDoc, double tNow, double* dtProposed)
{
    /*
   * TODO: Add your own code here ...
   */
    return true;
}

void CSub::OnUpdateMaterial (IfmDocument pDoc, IfmParamID nParam, int nSpecies, double tTime)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::PreFlowSimulation (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
    //IfmSetSimulationControlFlag(m_pDoc,IfmCTL_SKIP);
}

void CSub::PostFlowSimulation (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
    //IfmSetSimulationControlFlag(m_pDoc,IfmCTL_SKIP);

}

void CSub::PreMassSimulation (IfmDocument pDoc, int iSpecies)
{
    /*
   * TODO: Add your own code here ...
   */
    //IfmSetSimulationControlFlag(m_pDoc,IfmCTL_SKIP);
}

void CSub::PostMassSimulation (IfmDocument pDoc, int iSpecies)
{
    /*
   * TODO: Add your own code here ...
   */
    //IfmSetSimulationControlFlag(m_pDoc,IfmCTL_SKIP);
}

void CSub::PreHeatSimulation (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
    //IfmSetSimulationControlFlag(m_pDoc,IfmCTL_SKIP);
}

void CSub::PostHeatSimulation (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
    //IfmSetSimulationControlFlag(m_pDoc,IfmCTL_SKIP);
}

IfmResult CSub::OnChangeProblemClass (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
    return true;
}

void CSub::OnChangeTopology (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   */
}

IfmBool CSub::OnLockPowerID (IfmDocument pDoc, int nPowerID)
{
    /*
   * TODO: Add your own code here ...
   */
    return false;
}

void CSub::OnMarkElementsForAMR (IfmDocument pDoc)
{
    /*
   * TODO: Add your own code here ...
   *    Call IfmSetAmrElementRefinement(pAmr, nIndex, IfmAMR_REFINE)
   *    to mark the nIndex'th element for refining.
   *	Similarly, you can use the flags IfmAMR_DEREFINE for derefining
   *	and IfmAMR_KEEP for unmarking.
   */
}

IfmResult CSub::PreRefineProblem (IfmDocument pDoc, int nNodeCount2D, int nElemCount2D)
{
    /*
   * TODO: Add your own code here ...
   */
    return true;
}

void CSub::PostRefineProblem (IfmDocument pDoc, IfmBool bDiscard)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::OnRefineElementAttributes (IfmDocument pDoc, int nNewCount, int* pNewElem, int nOldCount, int* pOldElem)
{
    /*
   * TODO: Add your own code here ...
   */
}

void CSub::OnRefineNodeAttributes (IfmDocument pDoc, int nNewNode, int nNodeFrom, int nNodeTo)
{
    /*
   * TODO: Add your own code here ...
   */
}

IfmBool CSub::OnStateChanging (IfmDocument pDoc, IfmDOC_STATE newState)
{
    /*
   * TODO: Add your own code here ...
   */
    return true;
}

void CSub::pauseSystem()
{
    do {
        qDebug() << "PRESS ENTER TO CONTINUE"<<endl;;
    } while (cin.get() != '\n');
}

void CSub::convertPairVectorToMatrix(vector<pair<int, double> > pairVector, MatrixXd &matrix)
{
    matrix.resize(pairVector.size(),2);
    for (int i=0;i<matrix.rows();i++)
    {
        matrix(i,0)=pairVector[i].first;
        matrix(i,1)=pairVector[i].second;
    }
}

void CSub::checkAndCreateUserData()
{
    //Nodal references
    QString xDisplacement="X_Displacement";
    QString yDisplacement="Y_Displacement";
    QString zDisplacement="Z_Displacement";

    long referenceIDX=IfmGetRefDistrIdByName(m_pDoc,xDisplacement.toLatin1().data());
    long referenceIDY=IfmGetRefDistrIdByName(m_pDoc,yDisplacement.toLatin1().data());
    long referenceIDZ=IfmGetRefDistrIdByName(m_pDoc,zDisplacement.toLatin1().data());

    if(referenceIDX==-1)
    {
        IfmCreateRefDistr(m_pDoc,"X_Displacement");
    }

    if(referenceIDY==-1)
    {
        IfmCreateRefDistr(m_pDoc,"Y_Displacement");
    }

    if(referenceIDZ==-1)
    {
        IfmCreateRefDistr(m_pDoc,"Z_Displacement");
    }

    //-----------------------
    //Elementeral
    QString Bulk_Modulus="Bulk_Modulus";
    QString Poisson_Ratio="Poisson_Ratio";
    QString Porosity="Porosity";
    QString Grain_Compressibility="Grain_Compressibility";

    long referID1=IfmGetElementalRefDistrIdByName(m_pDoc,Bulk_Modulus.toLatin1().data());
    long referID2=IfmGetElementalRefDistrIdByName(m_pDoc,Poisson_Ratio.toLatin1().data());
    long referID3=IfmGetElementalRefDistrIdByName(m_pDoc,Porosity.toLatin1().data());
    long referID4=IfmGetElementalRefDistrIdByName(m_pDoc,Grain_Compressibility.toLatin1().data());

    if(referID1==-1)
    {
        IfmCreateElementalRefDistr(m_pDoc,"Bulk_Modulus");
    }

    if(referID2==-1)
    {
        IfmCreateElementalRefDistr(m_pDoc,"Poisson_Ratio");
    }

    if(referID3==-1)
    {
        IfmCreateElementalRefDistr(m_pDoc,"Porosity");
    }

    if(referID4==-1)
    {
        IfmCreateElementalRefDistr(m_pDoc,"Grain_Compressibility");
    }
    IfmInfo(m_pDoc,"User data is created");
}

void CSub::releaseMemory()
{
    XX.resize(0,0);
    U.resize(0,0);
    V.resize(0,0);
    W.resize(0,0);
    H.resize(0,0);

    U0.resize(0,0);
    V0.resize(0,0);
    W0.resize(0,0);
    H0.resize(0,0);
    Sxx.resize(0,0);
    Syy.resize(0,0);
    Szz.resize(0,0);
    Sxz.resize(0,0);
    Syz.resize(0,0);
    Sxy.resize(0,0);
    KK.resize(0,0);
    trip_total.clear();
    trip_total.resize(0);
    IfmInfo(m_pDoc,"Memory is release");
}

void CSub::initilizeData()
{
    //Input parameters
    gf=9.8064;
    Cfe=1e-10; //water compressibility
    numberOfNode=coordinates.rows();
    numberOfElement=elements.rows();
    totalDegreeOfFreedom=4*numberOfNode;
    numberOfNodePerElement=6;
    numberOfResultStep=numberOfStep/intervalResult;

    if(numberOfStep%intervalResult!=0)
    {
        numberOfResultStep=numberOfResultStep+1; //Include last step
    }

    numberOfResultStep=numberOfResultStep+1;        //Include Initial step
    numberOfStep=numberOfStep+1;                    //We save initial step also

    //Solution vector
    XX=MatrixXd::Zero(totalDegreeOfFreedom,1);
    U=MatrixXd::Zero(numberOfNode,numberOfResultStep);
    V=MatrixXd::Zero(numberOfNode,numberOfResultStep);
    W=MatrixXd::Zero(numberOfNode,numberOfResultStep);
    H=MatrixXd::Zero(numberOfNode,numberOfResultStep);
    U0=MatrixXd::Zero(numberOfNode,1);
    V0=MatrixXd::Zero(numberOfNode,1);
    W0=MatrixXd::Zero(numberOfNode,1);
    H0=MatrixXd::Zero(numberOfNode,1);

    //Force vector
    Fx=MatrixXd::Zero(numberOfNode,1);
    Fy=MatrixXd::Zero(numberOfNode,1);
    Fz=MatrixXd::Zero(numberOfNode,1);
    QQ=MatrixXd::Zero(numberOfNode,1);
    F=MatrixXd::Zero(totalDegreeOfFreedom,1);

    //Stress Vector
    if(writeStressFlag==true)
    {
        Sxx=MatrixXd::Zero(numberOfElement,numberOfResultStep);
        Syy=MatrixXd::Zero(numberOfElement,numberOfResultStep);
        Szz=MatrixXd::Zero(numberOfElement,numberOfResultStep);
        Sxy=MatrixXd::Zero(numberOfElement,numberOfResultStep);
        Sxz=MatrixXd::Zero(numberOfElement,numberOfResultStep);
        Syz=MatrixXd::Zero(numberOfElement,numberOfResultStep);
    }

    //Gaussian points
    gauss=gaussPoint.gauss9;
    IfmInfo(m_pDoc,"Finish initilizeData for coupled hydro-mechanical");
}

void CSub::createBoundaryCondition()
{
    MatrixXd fixx_new,fixy_new,fixz_new,fixh_new;
    fixx_new=fixx;
    fixy_new=fixy;
    fixz_new=fixz;
    fixh_new=fixh;

    for (auto j=0;j<fixx_new.rows();j++)
    {
        int index=fixx_new(j,0);
        fixx_new(j,0)=index-1;
    }

    for (auto j=0;j<fixy_new.rows();j++)
    {
        int index=fixy_new(j,0);
        fixy_new(j,0)=numberOfNode+index-1;
    }

    for (auto j=0;j<fixz_new.rows();j++)
    {
        int index=fixz_new(j,0);
        fixz_new(j,0)=2*numberOfNode+index-1;
    }

    for (auto j=0;j<fixh_new.rows();j++)
    {
        int index=fixh_new(j,0);
        fixh_new(j,0)=3*numberOfNode+index-1;
    }

    DirichletU=MatrixXd::Zero(fixx_new.rows()+fixy_new.rows()+fixz_new.rows(),fixx_new.cols());
    DirichletU<<fixx_new,fixy_new,fixz_new;

    DirichletD=MatrixXd::Zero(fixx_new.rows()+fixy_new.rows()+fixz_new.rows()+fixh_new.rows(),fixx_new.cols());
    DirichletD<<fixx_new,fixy_new,fixz_new,fixh_new;

    DirichletAll=MatrixXd::Zero(totalDegreeOfFreedom,3);
    DirichletAllD=MatrixXd::Zero(totalDegreeOfFreedom,3);
    DirichletAllU=MatrixXd::Zero(totalDegreeOfFreedom,3);

    for (auto j=0;j<DirichletU.rows();j++)
    {
        int equaNum=DirichletU(j,0);
        DirichletAllU(equaNum,0)=equaNum;
        DirichletAllU(equaNum,1)=1;
        DirichletAllU(equaNum,2)=DirichletU(j,1);
    }

    for (auto j=0;j<DirichletD.rows();j++)
    {
        int equaNum=DirichletD(j,0);
        DirichletAllD(equaNum,0)=equaNum;
        DirichletAllD(equaNum,1)=1;
        DirichletAllD(equaNum,2)=DirichletD(j,1);
    }
    IfmInfo(m_pDoc,"Finish create boundary condition");
}

void CSub::assemblyGlobalMatrixMultiThread()
{
    //Reset global matrix
    KK.setZero();
    KK.resize(totalDegreeOfFreedom,totalDegreeOfFreedom);
    trip_total.clear();
    trip_total.resize(0);
    trip_total.reserve(30*30*numberOfElement);

    //Start MultiThread codes
    int NumberOfCore=QThread::idealThreadCount();
    std::vector<elementMatrix*> eleMatrix;

    for (int jj=0;jj<NumberOfCore;jj++)
    {
        eleMatrix.push_back(new elementMatrix);
    }
    int subnoe=int(numberOfElement/(NumberOfCore));

    for (int jj=0;jj<NumberOfCore;jj++)
    {
        eleMatrix[jj]->startElement=jj*subnoe;
        eleMatrix[jj]->endElement=(jj+1)*subnoe;
        if(jj==(NumberOfCore)-1)
        {
            eleMatrix[jj]->startElement=jj*subnoe;
        }
        eleMatrix[jj]->coordinates=coordinates;
        eleMatrix[jj]->elements=elements;
        eleMatrix[jj]->hydroParameters=hydroParameters;
        eleMatrix[jj]->mechanicalParameters=mechanicalParameters;
        eleMatrix[jj]->DirichletAll=DirichletAll;
        eleMatrix[jj]->U0=U0;
        eleMatrix[jj]->V0=V0;
        eleMatrix[jj]->W0=W0;
        eleMatrix[jj]->H0=H0;
        eleMatrix[jj]->initialH=initialH;
        eleMatrix[jj]->timeIncrement=timeIncrement;
    }

    vector <std::thread> myThread;

    for (int jj=0;jj<NumberOfCore;jj++)
    {
        myThread.push_back(std::thread(&elementMatrix::assemblyMatrix,eleMatrix[jj]));
    }
    for( auto& t : myThread) t.join() ;

    bool checkThread=true;
    for (int jj=0;jj<NumberOfCore;jj++)
    {
        checkThread=checkThread && eleMatrix[jj]->checkFinish;
    }

    while(checkThread==false)
    {
        checkThread=true;
        for (int jj=0;jj<NumberOfCore;jj++)
        {
            checkThread=checkThread && eleMatrix[jj]->checkFinish;
            if(checkThread==false){break;}
        }
    }


    for (int jj=0;jj<NumberOfCore;jj++)
    {
        trip_total.insert(trip_total.end(),eleMatrix[jj]->trip_total.begin(),eleMatrix[jj]->trip_total.end());
        F=F+ eleMatrix[jj]->F;
    }

    //End MultiThread codes

    //Create global sparse matrix
    KK.setFromTriplets(trip_total.begin(),trip_total.end());

    //Apply boundary condition, global level
    for (int j=0;j<Dirichlet.rows();j++)
    {
        int jj=Dirichlet(j,0);
        F(jj,0)=Dirichlet(j,1);
        KK.coeffRef(jj,jj)=1;
    }
    KK.prune(0.0);
    KK.makeCompressed();
    trip_total.clear(); //Release memory

    //delete pointer
    for (elementMatrix* obj : eleMatrix)
        delete obj;
    eleMatrix.clear();
}

void CSub::undrainedAnalysis()
{
    timer.start();
    currentStep=0;
    currentResultStep=0;
    U0.setZero();
    V0.setZero();
    W0.setZero();

    Fx.setZero();
    Fy.setZero();
    Fz.setZero();
    QQ.setZero();
    F.setZero();

    timeIncrement=0;
    H0=initialH.col(1);
    Dirichlet=DirichletU;
    DirichletAll=DirichletAllU;
    F<<Fx,Fx,Fz,QQ;

    assemblyGlobalMatrixMultiThread();
    solveDirect();
    assignToVectorSolutions();
    calculateStress();
}

void CSub::drainedAnalysis()
{
    for (int step=1;step<numberOfStep;step++)
    {
        currentStep=step;
        if(currentStep%intervalResult==0 || currentStep==(numberOfStep-1))
        {
            currentResultStep++;
        }
        Fx.setZero();
        Fy.setZero();
        Fz.setZero();
        QQ.setZero();
        F.setZero();

        //Convert from days to seconds
        timeIncrement=initialTimeIncrement*86400.0f;
        for (int i=0;i<wellRate.rows();i++)
        {
            QQ(wellRate(i,0)-1,0)=-wellRate(i,1)*timeIncrement;
        }
        Dirichlet=DirichletD;
        DirichletAll=DirichletAllD;
        F<<Fx,Fx,Fz,QQ;

        timerAssembly.start();
        assemblyGlobalMatrixMultiThread();
        QString timeNotification="Assembly global matrix takes: "+QString::number(timerAssembly.elapsed())+" mili-seconds";
        IfmInfo(m_pDoc,timeNotification.toLatin1().data());

        solveDirect();
        if(currentStep%intervalResult==0 || currentStep==(numberOfStep-1))
        {            
            assignToVectorSolutions();
            calculateStress();
        }

        QString notification="Step-"+QString::number(step)+" Total running time : "+QString::number(timer.elapsed()/1000)+" seconds";
        IfmInfo(m_pDoc,notification.toLatin1().data());
    }
}

void CSub::solveDirect()
{
    QElapsedTimer solverTimer;
    solverTimer.start();
    PardisoLU<SparseMatrix<double,RowMajor> > solver;
    solver.compute(KK);
    XX.setZero();
    XX=solver.solve(F);

    for (auto j=0;j<numberOfNode;j++)
    {
        U0(j,0)=XX(j,0);
        V0(j,0)=XX(j+numberOfNode,0);
        W0(j,0)=XX(j+2*numberOfNode,0);
        H0(j,0)=XX(j+3*numberOfNode,0);
    }

    QString notification="Direct Solver, solving Time: "+QString::number(solverTimer.elapsed()/1000)+" seconds";
    IfmInfo(m_pDoc,notification.toLatin1().data());
}

void CSub::exportResults()
{
    WriteToFile exportFile;
    QStringList header;
    QString stepIndex;
    for (int i=0;i<numberOfResultStep;i++)
    {
        if(i<(numberOfResultStep-1))
        {
            stepIndex="Step-"+QString::number(i*intervalResult);
        }
        else
        {
            stepIndex="Step-"+QString::number(numberOfStep-1);
        }
        header.push_back(stepIndex);
    }

    folderName=saveFolder;
    folderName=folderName+"/Nodal_Solutions";
    QDir mDir;
    mDir.setPath(folderName);
    if(!mDir.exists())
    {
        mDir.mkdir(folderName);
    }

    IfmInfo(m_pDoc,"Save to folder:");
    IfmInfo(m_pDoc,folderName.toLatin1().data());

    fileName=folderName+"/X-displacement.txt";
    exportFile.fileName=fileName.toStdString();
    exportFile.ToFile(U,header);

    fileName=folderName+"/Y-displacement.txt";
    exportFile.fileName=fileName.toStdString();
    exportFile.ToFile(V,header);

    fileName=folderName+"/Z-displacement.txt";
    exportFile.fileName=fileName.toStdString();
    exportFile.ToFile(W,header);

    fileName=folderName+"/Head.txt";
    exportFile.fileName=fileName.toStdString();
    exportFile.ToFile(H,header);
    IfmInfo(m_pDoc,"Exported nodal results to /Subsidence_Outputs/Nodal_Solutions folder");

    if(writeStressFlag==true)
    {
        folderName=saveFolder+"/Element_Stress";
        mDir.setPath(folderName);
        if(!mDir.exists())
        {
            mDir.mkdir(folderName);
        }

        fileName=folderName+"/Sxx.txt";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(Sxx,header);

        fileName=folderName+"/Syy.txt";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(Syy,header);

        fileName=folderName+"/Szz.txt";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(Szz,header);

        fileName=folderName+"/Sxy.txt";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(Sxy,header);

        fileName=folderName+"/Sxz.txt";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(Sxz,header);

        fileName=folderName+"/Syz.txt";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(Syz,header);
        IfmInfo(m_pDoc,"Exported stress results to /Subsidence_Outputs/Element_Stress folder");
    }
}

void CSub::assignToVectorSolutions()
{
    for (auto j=0;j<numberOfNode;j++)
    {
        U(j,currentResultStep)=XX(j,0);
        V(j,currentResultStep)=XX(j+numberOfNode,0);
        W(j,currentResultStep)=XX(j+2*numberOfNode,0);
        H(j,currentResultStep)=XX(j+3*numberOfNode,0);
    }
}

void CSub::calculateStress()
{
    if(writeStressFlag==true)
    {
        for (int i=0;i<numberOfElement;i++)
        {
            calculateStressPrism6(i);
        }
    }
}

void CSub::calculateStressPrism6(int &eleNum)
{
    int ii=eleNum;
    kxe=hydroParameters(ii,1);
    kye=hydroParameters(ii,2);
    kze=hydroParameters(ii,3);
    Ke=mechanicalParameters(ii,0);
    ve=mechanicalParameters(ii,1);
    Ge=3*Ke*(1-2*ve)/2.0f/(1+ve);
    ne=mechanicalParameters(ii,2);
    Cse=mechanicalParameters(ii,3);
    Cme=1/Ke;
    BiotCoeff=1-Cse/Cme;
    Se=ne*Cfe+(BiotCoeff-ne)*Cse;

    //Initial vector
    MatrixXd u0=MatrixXd::Zero(6,1);
    MatrixXd v0=MatrixXd::Zero(6,1);
    MatrixXd w0=MatrixXd::Zero(6,1);
    MatrixXd h0=MatrixXd::Zero(6,1);
    MatrixXd hinitial=MatrixXd::Zero(6,1);

    MatrixXd nodeIndex=MatrixXd::Zero(6,1);
    MatrixXd index_total=MatrixXd::Zero(24,1);
    MatrixXd X_coor=MatrixXd::Zero(6,1);
    MatrixXd Y_coor=MatrixXd::Zero(6,1);
    MatrixXd Z_coor=MatrixXd::Zero(6,1);

    //Shape function
    double g1,g2,g3,g4,wi;
    MatrixXd N=MatrixXd::Zero(1,6);
    MatrixXd dNL1=MatrixXd::Zero(1,6);
    MatrixXd dNL2=MatrixXd::Zero(1,6);
    MatrixXd dNL3=MatrixXd::Zero(1,6);

    MatrixXd jacobi=MatrixXd::Zero(3,3);
    MatrixXd jacobiLeft=MatrixXd::Zero(3,6);
    MatrixXd jacobiRight=MatrixXd::Zero(6,3);

    MatrixXd dN=MatrixXd::Zero(3,6);
    MatrixXd dNx=MatrixXd::Zero(1,6);
    MatrixXd dNy=MatrixXd::Zero(1,6);
    MatrixXd dNz=MatrixXd::Zero(1,6);

    //Get coordinates and index
    for (auto j=0;j<6;j++)
    {
        int index=elements(ii,j+1)-1;
        nodeIndex(j,0)=index;
        u0(j,0)=U0(index,0);
        v0(j,0)=V0(index,0);
        w0(j,0)=W0(index,0);
        h0(j,0)=H0(index,0);
        hinitial(j,0)=initialH(index,1);

        X_coor(j,0)=coordinates(index,1);
        Y_coor(j,0)=coordinates(index,2);
        Z_coor(j,0)=coordinates(index,3);

        index_total(j,0)=index;
        index_total(6+j,0)=numberOfNode+index;
        index_total(12+j,0)=2*numberOfNode+index;
        index_total(18+j,0)=3*numberOfNode+index;
    }

    //Loop over gaussian points
    //Loop over gauss point
    Sxx(eleNum,currentResultStep)=0;
    Syy(eleNum,currentResultStep)=0;
    Szz(eleNum,currentResultStep)=0;
    Sxy(eleNum,currentResultStep)=0;
    Sxz(eleNum,currentResultStep)=0;
    Syz(eleNum,currentResultStep)=0;

    for (auto jj=0;jj<gauss.rows();jj++)
    {
        g1=gauss(jj,0); g2=gauss(jj,1); g3=gauss(jj,2); wi=gauss(jj,3);
        g4=1.0-g1-g2;

        //6 Nodes shape function
        N(0,0)=0.5*g1*(1.0-g3);
        N(0,1)=0.5*g2*(1.0-g3);
        N(0,2)=0.5*g4*(1.0-g3);
        N(0,3)=0.5*g1*(1.0+g3);
        N(0,4)=0.5*g2*(1.0+g3);
        N(0,5)=0.5*g4*(1.0+g3);

        dNL1(0,0)=0.5*(1.0-g3);
        dNL1(0,1)=0.0;
        dNL1(0,2)=-0.5*(1.0-g3);
        dNL1(0,3)=0.5*(1.0+g3);
        dNL1(0,4)=0.0;
        dNL1(0,5)=-0.5*(1.0+g3);

        dNL2(0,0)=0;
        dNL2(0,1)=0.5*(1.0-g3);
        dNL2(0,2)=-0.5*(1.0-g3);
        dNL2(0,3)=0.0;
        dNL2(0,4)=0.5*(1.0+g3);
        dNL2(0,5)=-0.5*(1.0+g3);

        dNL3(0,0)=-0.5*g1;
        dNL3(0,1)=-0.5*g2;
        dNL3(0,2)=-0.5*g4;
        dNL3(0,3)=0.5*g1;
        dNL3(0,4)=0.5*g2;
        dNL3(0,5)=0.5*g4;

        jacobiLeft<<dNL1,dNL2,dNL3;
        jacobiRight<<X_coor,Y_coor,Z_coor;
        jacobi=jacobiLeft*jacobiRight;
        double detj;
        detj=abs(jacobi.determinant());

        dN=jacobi.inverse()*jacobiLeft;
        dNx=dN.row(0);
        dNy=dN.row(1);
        dNz=dN.row(2);

        MatrixXd Sxx_e=MatrixXd::Zero(1,1);
        MatrixXd Syy_e=MatrixXd::Zero(1,1);
        MatrixXd Szz_e=MatrixXd::Zero(1,1);
        MatrixXd Sxy_e=MatrixXd::Zero(1,1);
        MatrixXd Sxz_e=MatrixXd::Zero(1,1);
        MatrixXd Syz_e=MatrixXd::Zero(1,1);

        Sxx_e=-(Ke+4*Ge/3)*dNx*u0-(Ke-2*Ge/3)*dNy*v0-(Ke-2*Ge/3)*dNz*w0;
        Syy_e=-(Ke+4*Ge/3)*dNy*v0-(Ke-2*Ge/3)*dNx*u0-(Ke-2*Ge/3)*dNz*w0;
        Szz_e=-(Ke+4*Ge/3)*dNz*w0-(Ke-2*Ge/3)*dNx*u0-(Ke-2*Ge/3)*dNy*v0;
        Sxy_e=-Ge*dNy*u0-Ge*dNx*v0;
        Sxz_e=-Ge*dNz*u0-Ge*dNx*w0;
        Syz_e=-Ge*dNz*v0-Ge*dNy*w0;

        Sxx(eleNum,currentResultStep)=Sxx(eleNum,currentResultStep)+Sxx_e(0,0);
        Syy(eleNum,currentResultStep)=Syy(eleNum,currentResultStep)+Syy_e(0,0);
        Szz(eleNum,currentResultStep)=Szz(eleNum,currentResultStep)+Szz_e(0,0);
        Sxy(eleNum,currentResultStep)=Sxy(eleNum,currentResultStep)+Sxy_e(0,0);
        Sxz(eleNum,currentResultStep)=Sxz(eleNum,currentResultStep)+Sxz_e(0,0);
        Syz(eleNum,currentResultStep)=Syz(eleNum,currentResultStep)+Syz_e(0,0);

    } //End loop over gaussian points

    Sxx(eleNum,currentResultStep)=Sxx(eleNum,currentResultStep)/gauss.rows();
    Syy(eleNum,currentResultStep)=Syy(eleNum,currentResultStep)/gauss.rows();
    Szz(eleNum,currentResultStep)=Szz(eleNum,currentResultStep)/gauss.rows();
    Sxy(eleNum,currentResultStep)=Sxy(eleNum,currentResultStep)/gauss.rows();
    Sxz(eleNum,currentResultStep)=Sxz(eleNum,currentResultStep)/gauss.rows();
    Syz(eleNum,currentResultStep)=Syz(eleNum,currentResultStep)/gauss.rows();
}

void CSub::writeExtraSettingInformation()
{
    QString fullName=extraSettingFolder+"/"+"PlugIn_Options.dat";
    QFile mFile;
    mFile.setFileName(fullName);

    if(mFile.exists()==true)
    {
        return;
    }
    else  //start writting extra database
    {
        if(mFile.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&mFile);
            stream<<"This file is used to have extra settings for Plugin"<<endl;
            stream<<"This file now mostly is used to reserve for future features"<<endl;
            stream<<"If this file is deleted, all setting are set to default values"<<endl;
            //save
            stream<<"#WRITE_RESULTS_AFTER_Nth_STEP"<<" "<<"1"<<endl;
            stream<<"#WRITE_STRESS_RESULTS_YES/NO"<<" "<<"YES"<<endl;
            stream<<"#WRITE_MATERIAL_INFORMATION_YES/NO"<<" "<<"NO"<<endl;;
            stream<<"#WRITE_MESH_INFORMATION_YES/NO"<<" "<<"YES"<<endl;
        }
    }
    mFile.close();
    mFile.flush();
}

void CSub::readExtraSetingInformation()
{
    QString fullName=extraSettingFolder+"/"+"PlugIn_Options.dat";
    QFile mFile;
    mFile.setFileName(fullName);

    if(mFile.exists()==false)
    {
        return;
        intervalResult=1;
        writeMeshFlag=true;
        writeMaterialFlag=false;
        writeStressFlag=true;
        IfmInfo(m_pDoc,"Extra setting is not exists, all settings are set to default values");
    }
    else  //start writting extra database
    {
        if(mFile.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&mFile);
            QString Line,inputSetting, valueSetting;
            QStringList list;
            while(!stream.atEnd())
            {
                Line=stream.readLine();
                list=Line.split(QRegExp("\\s+"),QString::SkipEmptyParts); //Extract list of string from readLine
                inputSetting=list[0];
                if(inputSetting=="#WRITE_RESULTS_AFTER_Nth_STEP")
                {
                    valueSetting=list[1];
                    intervalResult=valueSetting.toInt();
                }

                if(inputSetting=="#WRITE_STRESS_RESULTS_YES/NO")
                {
                    valueSetting=list[1];
                    if(valueSetting=="YES")
                    {
                        writeStressFlag=true;
                    }
                    else
                    {
                        writeStressFlag=false;
                    }
                }

                if(inputSetting=="#WRITE_MATERIAL_INFORMATION_YES/NO")
                {
                    valueSetting=list[1];
                    if(valueSetting=="YES")
                    {
                        writeMaterialFlag=true;
                    }
                    else
                    {
                        writeMaterialFlag=false;
                    }
                }

                if(inputSetting=="#WRITE_MESH_INFORMATION_YES/NO")
                {
                    valueSetting=list[1];
                    if(valueSetting=="YES")
                    {
                        writeMeshFlag=true;
                    }
                    else
                    {
                        writeMeshFlag=false;
                    }
                }
            }
        }
        IfmInfo(m_pDoc,"Extra Setting is imported successfully");
    }
    mFile.close();
    mFile.flush();
}

void CSub::createWorkingFolder()
{
    QString problemPath=IfmGetProblemPath(m_pDoc);
    QFileInfo mFile(problemPath);
    folderName=mFile.path();

    saveFolder=folderName+"/"+"Subsidence_Outputs";
    QDir mDir;
    mDir.setPath(saveFolder);
    if(!mDir.exists())
    {
        mDir.mkdir(saveFolder);
        IfmInfo(m_pDoc,"Save folder is created");
        IfmInfo(m_pDoc,saveFolder.toLatin1().data());
    }
    else
    {
        IfmInfo(m_pDoc,"Save folder folder is already exists");
    }

    extraSettingFolder=folderName+"/"+"Subsidence_Settings";
    mDir.setPath(extraSettingFolder);
    if(!mDir.exists())
    {
        mDir.mkdir(extraSettingFolder);
        IfmInfo(m_pDoc,"Extra Setting folder is created");
        IfmInfo(m_pDoc,extraSettingFolder.toLatin1().data());
    }
    else
    {
        IfmInfo(m_pDoc,"Extra Setting folder is already exists");
    }

}

void CSub::getMaterialFlowProperties()
{
    //Unit is m/d, convert to m/s
    numberOfElement=IfmGetNumberOfElements(m_pDoc);
    hydroParameters=MatrixXd::Zero(numberOfElement,5);

    for (int j=0;j<numberOfElement;j++)
    {
        hydroParameters(j,0)=IfmGetMatXConductivityValue3D(m_pDoc,j)/86400.0f;
        hydroParameters(j,1)=IfmGetMatYConductivityValue3D(m_pDoc,j)/86400.0f;
        hydroParameters(j,2)=IfmGetMatZConductivityValue3D(m_pDoc,j)/86400.0f;
        hydroParameters(j,3)=IfmGetMatFlowCompressibility(m_pDoc,j);
        hydroParameters(j,4)=IfmGetMatFlowSinkSource(m_pDoc,j);
    }

    if(writeMaterialFlag==true)
    {
        WriteToFile exportFile;
        QStringList header;
        QString list="Kxx,Kyy,Kzz,Ss,So/Sink,K,Poisson,Porosity,Cf,UnitWeight";
        header=list.split(',');
        MatrixXd materialAll=MatrixXd::Zero(numberOfElement,10);
        materialAll<<hydroParameters,mechanicalParameters;

        fileName=saveFolder+"/properties.dat";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(materialAll,header);
        IfmInfo(m_pDoc,"Element properties is written to properties.dat");
    }
}

void CSub::getBoundaryCondition()
{
    QStringList header;
    QString list="#Node,H_value";
    header=list.split(',');
    vector<pair<int,double> >vector_wellRate;
    vector<pair<int,double> >vector_fixH;

    numberOfNode=IfmGetNumberOfNodes(m_pDoc);
    for (int j=0;j<numberOfNode;j++)
    {
        int typeBC=IfmGetBcFlowType(m_pDoc,j);
        double valueBC=IfmGetBcFlowValue(m_pDoc,j);
        if(typeBC==1)
        {
            vector_fixH.push_back(make_pair(j+1,valueBC));
        }
        if(typeBC==4)
        {
            vector_wellRate.push_back(make_pair(j+1,valueBC/86400.0f)); //convert from m3/d to m3/s
        }
    }
    convertPairVectorToMatrix(vector_fixH,fixh);
    convertPairVectorToMatrix(vector_wellRate,wellRate);
}

void CSub::getInitialHead()
{
    QStringList header;
    QString list="#Node,initial_H";
    header=list.split(',');
    numberOfNode=IfmGetNumberOfNodes(m_pDoc);
    initialH=MatrixXd::Zero(numberOfNode,2);
    for (int j=0;j<numberOfNode;j++)
    {
        initialH(j,0)=j+1;
        initialH(j,1)=IfmGetResultsFlowHeadValue(m_pDoc,j);
    }
}

void CSub::skipTimeStep()
{
    IfmSetSimulationControlFlag(m_pDoc,IfmCTL_ABORT);
}


void CSub::getTimeInformation()
{
    //Time is day, convert to seconds
    initialTimeIncrement=IfmGetCurrentTimeIncrement(m_pDoc);
    finalSimulationTime=IfmGetFinalSimulationTime(m_pDoc);
    numberOfStep=finalSimulationTime/initialTimeIncrement;
}

void CSub::getDirichletBoundaryConditionFromUserData()
{
    vector <pair<int,double> > vectorFixX;
    vector <pair<int,double> > vectorFixY;
    vector <pair<int,double> > vectorFixZ;

    //Nodal references
    QString xDisplacement="X_Displacement";
    QString yDisplacement="Y_Displacement";
    QString zDisplacement="Z_Displacement";

    double flagError=-99999;
    double TOLERANCE=1e-3;

    long referenceIDX=IfmGetRefDistrIdByName(m_pDoc,xDisplacement.toLatin1().data());
    long referenceIDY=IfmGetRefDistrIdByName(m_pDoc,yDisplacement.toLatin1().data());
    long referenceIDZ=IfmGetRefDistrIdByName(m_pDoc,zDisplacement.toLatin1().data());

    if(referenceIDX==-1 || referenceIDY==-1 || referenceIDZ==-1)
    {
        IfmWarning(m_pDoc,"Nodal Distribution X_Displacement, Y_Displacement, Z_Displacement must be defined first");
    }
    else
    {
        for (int i=0;i<numberOfNode;i++)
        {
            double valueX=IfmGetRefDistrValue(m_pDoc,referenceIDX,i);
            double valueY=IfmGetRefDistrValue(m_pDoc,referenceIDY,i);
            double valueZ=IfmGetRefDistrValue(m_pDoc,referenceIDZ,i);

            if(abs(valueX-flagError)>TOLERANCE)
            {
                vectorFixX.push_back(make_pair(i+1,valueX));
            }

            if(abs(valueY-flagError)>TOLERANCE)
            {
                vectorFixY.push_back(make_pair(i+1,valueY));
            }

            if(abs(valueZ-flagError)>TOLERANCE)
            {
                vectorFixZ.push_back(make_pair(i+1,valueZ));
            }
        }
    }

    //conver to fixX, fixY, fixZ matrix
    convertPairVectorToMatrix(vectorFixX,fixx);
    convertPairVectorToMatrix(vectorFixY,fixy);
    convertPairVectorToMatrix(vectorFixZ,fixz);
    IfmInfo(m_pDoc,"Get User Data sucesfully: X-Displacement, Y-Displacemetn, Z-Displacement");
}

void CSub::getMechanicalParametersFromUserData()
{
    mechanicalParameters=MatrixXd::Zero(numberOfElement,5);
    //Elemental Reference Distribution
    //Nodal references
    QString Bulk_Modulus="Bulk_Modulus";
    QString Poisson_Ratio="Poisson_Ratio";
    QString Porosity="Porosity";
    QString Grain_Compressibility="Grain_Compressibility";

    long referID1=IfmGetElementalRefDistrIdByName(m_pDoc,Bulk_Modulus.toLatin1().data());
    long referID2=IfmGetElementalRefDistrIdByName(m_pDoc,Poisson_Ratio.toLatin1().data());
    long referID3=IfmGetElementalRefDistrIdByName(m_pDoc,Porosity.toLatin1().data());
    long referID4=IfmGetElementalRefDistrIdByName(m_pDoc,Grain_Compressibility.toLatin1().data());

    if(referID1==-1 || referID2==-1 || referID3==-1 || referID4==-1)
    {
        IfmWarning(m_pDoc,"Elemental Distribution Bulk_Modulus, Poisson_Ratio, Porosity, Grain_Compressibility, Unit_Weight mus be defined first");
    }
    else
    {
        for (int i=0;i<numberOfElement;i++)
        {
            mechanicalParameters(i,0)=IfmGetElementalRefDistrValue(m_pDoc,referID1,i);
            mechanicalParameters(i,1)=IfmGetElementalRefDistrValue(m_pDoc,referID2,i);
            mechanicalParameters(i,2)=IfmGetElementalRefDistrValue(m_pDoc,referID3,i);
            mechanicalParameters(i,3)=IfmGetElementalRefDistrValue(m_pDoc,referID4,i);
        }
    }
    IfmInfo(m_pDoc,"Get User Data sucesfully: Bulk_Modulus, Poisson_Ratio, Porosity, Grain_Compressibility,Unit_Weight");
}

void CSub::getCoordinates()
{
    WriteToFile exportFile;
    numberOfNodePerSlice=IfmGetNumberOfNodesPerSlice(m_pDoc);
    numberOfElementPerLayer=IfmGetNumberOfElementsPerLayer(m_pDoc);
    numberOfNode=IfmGetNumberOfNodes(m_pDoc);
    int numberOfSlice=IfmGetNumberOfSlices(m_pDoc);
    coordinates.resize(numberOfNode,5);

    for (int i=0;i<numberOfNode;i++)
    {
        int slice;
        slice=int(i/numberOfNodePerSlice)+1;
        coordinates(i,0)=i+1;
        coordinates(i,1)=IfmGetX(m_pDoc,i);
        coordinates(i,2)=IfmGetY(m_pDoc,i);
        coordinates(i,3)=IfmGetZ(m_pDoc,i);
        coordinates(i,4)=slice;
    }

    if(writeMeshFlag==true)
    {
        QStringList header;
        header.push_back("Node Index");
        header.push_back("X-Coord");
        header.push_back("Y-Coord");
        header.push_back("Z-Coord");
        header.push_back("#Slice");

        fileName=saveFolder+"/coordinates.dat";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(coordinates,header);
        IfmInfo(m_pDoc,"Nodal coordinates information is written to coordinate.dat");
    }
}

void CSub::getElements()
{
    WriteToFile exportFile;
    numberOfElement=IfmGetNumberOfElements(m_pDoc);
    degreeOfFreedom=IfmGetNumberOfNodesPerElement(m_pDoc);
    elements.resize(numberOfElement,8);
    //should change 8 to dof+2
    numberOfElementPerLayer=IfmGetNumberOfElementsPerLayer(m_pDoc);
    int layer;

    for (int i=0;i<numberOfElement;i++)
    {
        layer=int(i/numberOfElementPerLayer)+1;
        elements(i,0)=i+1;
        for (int j=0;j<degreeOfFreedom;j++)
        {
            elements(i,j+1)=IfmGetNode(m_pDoc,i,j)+1;
        }
        elements(i,7)=layer;
    }

    if(writeMeshFlag==true)
    {
        QStringList header;
        QString string="Index,Node1,Node2,Node3,Node4,Node5,Node6,Layer";
        header=string.split(',');
        fileName=saveFolder+"/elements.dat";
        exportFile.fileName=fileName.toStdString();
        exportFile.ToFile(elements,header);
        IfmInfo(m_pDoc,"Element information is written to elements.dat");
    }
}

void CSub::OnStateChanged (IfmDocument pDoc, IfmDOC_STATE newState)
{
    /*
   * TODO: Add your own code here ...
   */
}
