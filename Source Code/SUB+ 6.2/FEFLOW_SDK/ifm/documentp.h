#ifndef IFM_DOCUMENTP_H
#define IFM_DOCUMENTP_H

/********************** Copyright (C) DHI-WASY GmbH 2013 **********************
*
*	FEFLOW * interactive graphics-based Finite Element simulation
*		 system for subsurface FLOW and transport processes
*
*		-->	FEFLOW interface manager
*
*------------------------------------------------------------------------------
*
*
*  Copyright 1996-2013, DHI-WASY GmbH
*  All Rights Reserved.
*
*  This is UNPUBLISHED PROPRIETARY SOURCE CODE of DHI-WASY GmbH;
*  the contents of this file may not be disclosed to third parties, copied or
*  duplicated in any form, in whole or in part, without the prior written
*  permission of DHI-WASY GmbH.
*
*-----------------------------------------------------------------------------*/

#include "document.h"
#include "modulep.h"

/* This ID must be unique across all IFM subsystems 
   (use regex 'IFM_.*_ID[	 ]*[0-9]' to verify) */
#define IFM_DOCUMENT_ID		2

/* NOTE!!!
 *
 * The order of the functions MUST NOT be changed!
 * New functions have to be added always at the end. 
 */
struct IfmDocumentMethods
{
  /* User data methods */
  void	     (*setUserData) (IfmHandle, IfmPointer);
  IfmPointer (*getUserData) (IfmHandle);

  /* Serializing methods */

  int	(*getLoadVersion) (IfmHandle);
  int 	(*getSaveVersion) (IfmHandle);
  void 	(*setSaveVersion) (IfmHandle, int);

  /* Control methods */

  int	 (*getNumberOfDimensions) (IfmHandle);			/* returns ndm */
  int	 (*getNumberOfNodes) (IfmHandle);			/* returns np */
  int    (*getNumberOfNodesPerSlice) (IfmHandle);		/* returns np_2d */
  int	 (*getNumberOfElements) (IfmHandle);			/* returns ne */
  int	 (*getNumberOfElementsPerLayer) (IfmHandle);		/* returns ne_nd */
  int	 (*getNumberOfNodesPerElement) (IfmHandle);		/* returns nbn */
  int	 (*getNumberOfNodesPerElement2D) (IfmHandle);		/* returns nbn */
  int	 (*getNumberOfSlices) (IfmHandle);			/* returns n_slices */
  int	 (*getNumberOfLayers) (IfmHandle);			/* returns n_layers */

  /* Topology methods */

  int	 (*getNode) (IfmHandle, int, int);			/* returns nop[e][nbn] */
  double (*getOriginX) (IfmHandle);				/* returns xlGK */
  double (*getOriginY) (IfmHandle);				/* returns ylGK */
  double (*getOriginZ) (IfmHandle);				/* returns 0. */

  /* Obsolete since v 4.921 */
  float	 (*getExtentX_f) (IfmHandle);				/* returns scale_x */
  float	 (*getExtentY_f) (IfmHandle);				/* returns scale_y */
  float	 (*getExtentZ_f) (IfmHandle);				/* returns 1. ??? */
  float	 (*getX_f) (IfmHandle, int);				/* returns x[DIMX][n] */
  float	 (*getY_f) (IfmHandle, int);				/* returns x[DIMY][n] */
  float	 (*getZ_f) (IfmHandle, int);				/* returns elev[n][...] */

  /* Time-related values */

  double (*getAbsoluteSimulationTime) (IfmHandle);		/* returns t */
  double (*getCurrentTimeIncrement) (IfmHandle);		/* returns dt */

  /* Group-related data to be get */

  int	 (*getNumberOfValidGroups) (IfmHandle);			/* returns group */
  int	 (*getMaximumNumberOfGroups) (IfmHandle);		/* returns maxgroups */
  int	 (*isNodeInGroup) (IfmHandle, int, int);		/* returns flag */
  double (*getFlowValueOfGroupIdAtCurrentTime) (IfmHandle, int);/* returns fluid flux */
  double (*getMassValueOfGroupIdAtCurrentTime) (IfmHandle, int);/* returns mass flux */
  double (*getHeatValueOfGroupIdAtCurrentTime) (IfmHandle, int);/* returns heat flux */

  /* BC data to be get */

  int	 (*getBcFlowType) (IfmHandle, int);			/* returns ncod_f */
  int	 (*getBcFlowTimeDependency) (IfmHandle, int);		/* returns ncod_f */
  double (*getBcFlowValue) (IfmHandle, int);			/* returns bc_f.v */
  int	 (*getBcMassType) (IfmHandle, int);			/* returns ncod_t */
  int	 (*getBcMassTimeDependency) (IfmHandle, int);		/* returns ncod_t */
  double (*getBcMassValue) (IfmHandle, int);			/* returns bc_t.v */
  int	 (*getBcHeatType) (IfmHandle, int);			/* returns ncod_h */
  int	 (*getBcHeatTimeDependency) (IfmHandle, int);		/* returns ncod_h */
  double (*getBcHeatValue) (IfmHandle, int);			/* returns bc_h.v */

  /* Material data to be get */

  double (*getMatConductivityValue2D) (IfmHandle, int);		/* get_mat call */
  double (*getMatXConductivityValue3D) (IfmHandle, int);	/* get_mat call */
  double (*getMatYConductivityValue3D) (IfmHandle, int);	/* get_mat call */
  double (*getMatZConductivityValue3D) (IfmHandle, int);	/* get_mat call */
  double (*getMatFlowRechargeValue) (IfmHandle, int);		/* get_mat call */

  double (*getMatAnisotropyFactor2D) (IfmHandle, int);		/* get_mat call */
  double (*getMatAnisotropyAngle2D) (IfmHandle, int);		/* get_mat call */
  double (*getMatBottom2D) (IfmHandle, int);			/* get_mat call */
  double (*getMatTops2D) (IfmHandle, int);			/* get_mat call */
  double (*getMatFlowStorativity) (IfmHandle, int);		/* get_mat call */
  double (*getMatFlowDensityRatio) (IfmHandle, int);		/* get_mat call */
  double (*getMatFlowExpansionCoeff) (IfmHandle, int);		/* get_mat call */
  double (*getMatFlowCompressibility) (IfmHandle, int);		/* get_mat call */
  double (*getMatFlowSinkSource) (IfmHandle, int);		/* get_mat call */
  double (*getMatFlowTransferIn) (IfmHandle, int);		/* get_mat call */
  double (*getMatFlowTransferOut) (IfmHandle, int);		/* get_mat call */

  double (*getMatMassAquiferThickness) (IfmHandle, int);	/* get_mat call */
  double (*getMatMassPorosity) (IfmHandle, int);		/* get_mat call */
  double (*getMatMassSorptionCoeff1) (IfmHandle, int);		/* get_mat call */
  double (*getMatMassSorptionCoeff2) (IfmHandle, int);		/* get_mat call */
  double (*getMatMassDiffusion) (IfmHandle, int);		/* get_mat call */
  double (*getMatMassLongDispersivity) (IfmHandle, int);	/* get_mat call */
  double (*getMatMassTransDispersivity) (IfmHandle, int);	/* get_mat call */
  double (*getMatMassDecayRate) (IfmHandle, int);		/* get_mat call */
  double (*getMatMassSinkSource) (IfmHandle, int);		/* get_mat call */
  double (*getMatMassTransferIn) (IfmHandle, int);		/* get_mat call */
  double (*getMatMassTransferOut) (IfmHandle, int);		/* get_mat call */

  double (*getMatHeatAquiferThickness) (IfmHandle, int);	/* get_mat call */
  double (*getMatHeatPorosity) (IfmHandle, int);		/* get_mat call */
  double (*getMatHeatSolidCapacity) (IfmHandle, int);		/* get_mat call */
  double (*getMatHeatSolidConductivity) (IfmHandle, int);	/* get_mat call */
  double (*getMatHeatLongDispersivity) (IfmHandle, int);	/* get_mat call */
  double (*getMatHeatTransDispersivity) (IfmHandle, int);	/* get_mat call */
  double (*getMatHeatFluidSinkSource) (IfmHandle, int);		/* get_mat call */
  double (*getMatHeatSolidSinkSource) (IfmHandle, int);		/* get_mat call */
  double (*getMatHeatTransferIn) (IfmHandle, int);		/* get_mat call */
  double (*getMatHeatTransferOut) (IfmHandle, int);		/* get_mat call */

  /* Resulting data to be get */

  double (*getResultsFlowHeadValue) (IfmHandle, int);		/* returns r2 */
  double (*getResultsTransportMassValue) (IfmHandle, int);	/* returns r3 */
  double (*getResultsTransportHeatValue) (IfmHandle, int);	/* returns rh */

  /* BC data to be set */

  void (*setBcFlowValueAtCurrentTime) (IfmHandle, int, double);	/* bc param call */
  void (*setBcMassValueAtCurrentTime) (IfmHandle, int, double);	/* bc param call */
  void (*setBcHeatValueAtCurrentTime) (IfmHandle, int, double);	/* bc param call */

  /* BC group-related data to be set */

  void (*setBcFlowValueOfGroupIdAtCurrentTime) (IfmHandle, int, double);	/* bc param call */
  void (*setBcMassValueOfGroupIdAtCurrentTime) (IfmHandle, int, double);	/* bc param call */
  void (*setBcHeatValueOfGroupIdAtCurrentTime) (IfmHandle, int, double);	/* bc param call */

  /* Material data to be set */

  void (*setMatConductivityValue2D) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatXConductivityValue3D) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatYConductivityValue3D) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatZConductivityValue3D) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatFlowRechargeValue) (IfmHandle, int, double);	/* set_mat call */

  void (*setMatAnisotropyFactor2D) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatAnisotropyAngle2D) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatBottom2D) (IfmHandle, int, double);		/* set_mat call */
  void (*setMatTops2D) (IfmHandle, int, double);		/* set_mat call */
  void (*setMatFlowStorativity) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatFlowDensityRatio) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatFlowExpansionCoeff) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatFlowCompressibility) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatFlowSinkSource) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatFlowTransferIn) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatFlowTransferOut) (IfmHandle, int, double);	/* set_mat call */

  void (*setMatMassAquiferThickness) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatMassPorosity) (IfmHandle, int, double);		/* set_mat call */
  void (*setMatMassSorptionCoeff1) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatMassSorptionCoeff2) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatMassDiffusion) (IfmHandle, int, double);		/* set_mat call */
  void (*setMatMassLongDispersivity) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatMassTransDispersivity) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatMassDecayRate) (IfmHandle, int, double);		/* set_mat call */
  void (*setMatMassSinkSource) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatMassTransferIn) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatMassTransferOut) (IfmHandle, int, double);	/* set_mat call */

  void (*setMatHeatAquiferThickness) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatHeatPorosity) (IfmHandle, int, double);		/* set_mat call */
  void (*setMatHeatSolidCapacity) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatHeatSolidConductivity) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatHeatLongDispersivity) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatHeatTransDispersivity) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatHeatFluidSinkSource) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatHeatSolidSinkSource) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatHeatTransferIn) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatHeatTransferOut) (IfmHandle, int, double);	/* set_mat call */

  /* Resulting data to be set */

  void (*setResultsFlowHeadValue) (IfmHandle, int, double);		/* set r2 */
  void (*setResultsTransportMassValue) (IfmHandle, int, double);	/* set r3 */
  void (*setResultsTransportHeatValue) (IfmHandle, int, double);	/* set rh */

  /* Available since v. 0x0003 (01/19/99, hjd) */

  int  (*enableProcessing) (IfmHandle, IfmBool);		/* enable/disable processing */
  int  (*simulationControl) (IfmHandle, int);			/* set/get processing state */
  int  (*getProblemType) (IfmHandle);				/* returns ic0 */
  int  (*getProblemClass) (IfmHandle);				/* returns ic1 */
  int  (*getTimeClass) (IfmHandle);				/* returns ic2 */
  int  (*getProblemProjection) (IfmHandle);			/* returns proj */
  int  (*getAMRType) (IfmHandle);				/* returns amr_use */
  int  (*getCurrentSliceNumber) (IfmHandle);			/* returns current_slice */
  int  (*getCurrentLayerNumber) (IfmHandle);			/* returns current_layer */
  int  (*getNumberOfValidObsPoints) (IfmHandle);		/* returns obs_pnt.pnts */

  /* Observation data to be set */

  int    (*getTypeOfObsId) (IfmHandle, int);			/* returns obs type */
  float  (*getXOfObsId_f) (IfmHandle, int);			/* returns obs x */ 
  float  (*getYOfObsId_f) (IfmHandle, int);			/* returns obs y */ 
  float  (*getZOfObsId_f) (IfmHandle, int);			/* returns obs z */ 
  double (*getFlowValueOfObsIdAtCurrentTime) (IfmHandle, int);	/* returns obs H */
  double (*getMassValueOfObsIdAtCurrentTime) (IfmHandle, int);	/* returns obs C */
  double (*getHeatValueOfObsIdAtCurrentTime) (IfmHandle, int);	/* returns obs T */
  double (*getPressureValueOfObsIdAtCurrentTime) (IfmHandle, int);	 /* returns obs P */
  double (*getSaturationValueOfObsIdAtCurrentTime) (IfmHandle, int);	 /* returns obs S */
  double (*getMoistureContentValueOfObsIdAtCurrentTime) (IfmHandle, int);/* returns obs Theta */
  double (*getResultsFlowHeadValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);
  double (*getResultsTransportMassValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);
  double (*getResultsTransportHeatValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);
  double (*getResultsFlowPressureValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);
  double (*getResultsFlowSaturationValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);
  double (*getResultsFlowMoistureContentValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);

  /* Saving and restoring internal B.C. representation (4.709) */

  void   (*initBc) (IfmHandle, IfmBcData* bcOut);
  void	 (*freeBc) (IfmHandle, IfmBcData* bcInOut);
  void   (*copyBc) (IfmHandle, IfmBcData* bcOut, const IfmBcData* bcIn);
  void   (*interpolateBc) (IfmHandle, IfmBcData* bcOut, 
		    const IfmBcData* bcLeft, const IfmBcData* bcRight);
  void   (*getBcFlowData) (IfmHandle, int, IfmBcData*);
  void   (*setBcFlowData) (IfmHandle, int, const IfmBcData*);
  void   (*getBcMassData) (IfmHandle, int, IfmBcData*);
  void   (*setBcMassData) (IfmHandle, int, const IfmBcData*);
  void   (*getBcHeatData) (IfmHandle, int, IfmBcData*);
  void   (*setBcHeatData) (IfmHandle, int, const IfmBcData*);

  int (*setBcFlowTypeAndValueAtCurrentTime) (IfmHandle, int, int, int, double);/* bc param call */
  int (*setBcMassTypeAndValueAtCurrentTime) (IfmHandle, int, int, int, double);/* bc param call */
  int (*setBcHeatTypeAndValueAtCurrentTime) (IfmHandle, int, int, int, double);/* bc param call */

  double (*getResultsFlowHeadValueAtXYSlice) (IfmHandle, double, double, int, IfmBool*);
  double (*getResultsTransportMassValueAtXYSlice) (IfmHandle, double, double, int, IfmBool*);
  double (*getResultsTransportHeatValueAtXYSlice) (IfmHandle, double, double, int, IfmBool*);
  double (*getResultsFlowPressureValueAtXYSlice) (IfmHandle, double, double, int, IfmBool*);
  double (*getResultsFlowSaturationValueAtXYSlice) (IfmHandle, double, double, int, IfmBool*);
  double (*getResultsFlowMoistureContentValueAtXYSlice) (IfmHandle, double, double, int, IfmBool*);

  /* Reference distribution data access */
  long    (*getNumberOfNodalRefDistr) (IfmHandle);	
  void    (*getNodalRefDistrName) (IfmHandle, long, char*);
  long    (*getNodalRefDistrIdByName) (IfmHandle, const char*);
  double  (*getNodalRefDistrValue) (IfmHandle, long, long);
  void    (*setNodalRefDistrValue) (IfmHandle, long, long, double);
  long    (*createNodalRefDistr) (IfmHandle, const char*);
  void    (*deleteNodalRefDistr) (IfmHandle, long);

  /* FEM problem border (v 4.717) */
  int	  (*getNumberOfBorders) (IfmHandle pHdl);
  int	  (*getNumberOfBorderNodes) (IfmHandle pHdl, int nBorder);
  int	  (*getBorderNode) (IfmHandle pHdl, int nBorder, int nIndex);
  IfmBool (*isExteriorBorder) (IfmHandle pHdl, int nBorder);

  /* FEM unsaturated & heat fluid data extended (v 4.802) */
  double  (*getResultsFlowPressureValue) (IfmHandle, int);
  double  (*getResultsFlowSaturationValue) (IfmHandle, int);
  double  (*getResultsFlowMoistureContentValue) (IfmHandle, int);
  void    (*setResultsFlowPressureValue) (IfmHandle, int, double);
  void    (*setResultsFlowSaturationValue) (IfmHandle, int, double);
  void    (*setResultsFlowMoistureContentValue) (IfmHandle, int, double);
  double  (*getMatHeatFluidCapacity) (IfmHandle, int);
  double  (*getMatHeatFluidConductivity) (IfmHandle, int);
  void    (*setMatHeatFluidCapacity) (IfmHandle, int, double);
  void    (*setMatHeatFluidConductivity) (IfmHandle, int, double);
  int     (*getMatUnsatModelType) (IfmHandle, int);
  double  (*getMatUnsatPorosity) (IfmHandle, int);
  double  (*getMatUnsatMaximumSaturation) (IfmHandle, int);
  double  (*getMatUnsatResidualSaturation) (IfmHandle, int);
  double  (*getMatUnsatFittingCoefficient) (IfmHandle, int);
  double  (*getMatUnsatFittingExponent) (IfmHandle, int);
  double  (*getMatUnsatFittingExponent2) (IfmHandle, int);
  double  (*getMatUnsatFittingExponent3) (IfmHandle, int);
  double  (*getMatUnsatAirEntryPressureHead) (IfmHandle, int);
  void    (*setMatUnsatModelType) (IfmHandle, int, double);
  void    (*setMatUnsatPorosity) (IfmHandle, int, double);
  void    (*setMatUnsatMaximumSaturation) (IfmHandle, int, double);
  void    (*setMatUnsatResidualSaturation) (IfmHandle, int, double);
  void    (*setMatUnsatFittingCoefficient) (IfmHandle, int, double);
  void    (*setMatUnsatFittingExponent) (IfmHandle, int, double);
  void    (*setMatUnsatFittingExponent2) (IfmHandle, int, double);
  void    (*setMatUnsatFittingExponent3) (IfmHandle, int, double);
  void    (*setMatUnsatAirEntryPressureHead) (IfmHandle, int, double);
  double  (*getMatMassDecayRate2) (IfmHandle, int);
  void    (*setMatMassDecayRate2) (IfmHandle, int, double);
  double  (*getResultsXVelocityValue) (IfmHandle, int);
  double  (*getResultsYVelocityValue) (IfmHandle, int);
  double  (*getResultsZVelocityValue) (IfmHandle, int);
  double  (*getResultsXVelocityValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);
  double  (*getResultsYVelocityValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);
  double  (*getResultsZVelocityValueAtXYZ) (IfmHandle, double, double, double, IfmBool*);
  double  (*getResultsVelocityNormValue) (IfmHandle, int);
  void    (*setResultsTransportMassIntermediateValue) (IfmHandle, int, double);	/* set r3_ini */
  double  (*getResultsFlowHeadPreviousTimeValue) (IfmHandle, int);
  double  (*getResultsTransportMassPreviousTimeValue) (IfmHandle, int);
  double  (*getResultsTransportHeatPreviousTimeValue) (IfmHandle, int);
  double  (*getAMRErrorTolerance) (IfmHandle);				/* get eps_amr */
  void    (*setAMRErrorTolerance) (IfmHandle, double);			/* set eps_amr */

  /* Power function handing (v 4.823) */
  int	  (*powerGetCurve) (IfmHandle, int);
  int	  (*powerCreateCurve) (IfmHandle, int);
  IfmBool (*powerDeleteCurve) (IfmHandle, int);
  IfmBool (*powerIsCyclic) (IfmHandle, int nID);
  void	  (*powerSetCyclic) (IfmHandle, int nID, IfmBool bCyclic);
  IfmInterpolationKind (*powerGetInterpolationKind) (IfmHandle pDoc, int nID);
  void	  (*powerSetInterpolationKind) (IfmHandle pDoc, int nID, IfmInterpolationKind kind);
  const char* (*powerGetComment) (IfmHandle, int nID);
  void	  (*powerSetComment) (IfmHandle, int nID, const char* pszComment);
  int	  (*powerGetNumberOfPoints) (IfmHandle, int nID);
  void	  (*powerGetPoint) (IfmHandle, int nID, int nIndex, double* time, double* value);
  int	  (*powerSetPoint) (IfmHandle, int nID, double time, double value);
  int	  (*powerDeletePoint) (IfmHandle, int nID, int nIndex);
  double  (*powerInterpolateValue) (IfmHandle, int nID, double time);

  /* Document state (v 4.823) */
  IfmBool (*setModified)(IfmHandle, int bModified);

  /* Boundary condition constraints (v 4.825) */
  int	  (*getBccFlowType) (IfmHandle, int);			/* returns ncod_f */
  int	  (*getBccFlowTimeDependency) (IfmHandle, int, int);	/* returns ncod_f */
  double  (*getBccFlowValue) (IfmHandle, int, int);		/* returns bc_f.v */
  int	  (*getBccMassType) (IfmHandle, int);			/* returns ncod_t */
  int	  (*getBccMassTimeDependency) (IfmHandle, int, int);	/* returns ncod_t */
  double  (*getBccMassValue) (IfmHandle, int, int);		/* returns bc_t.v */
  int	  (*getBccHeatType) (IfmHandle, int);			/* returns ncod_h */
  int	  (*getBccHeatTimeDependency) (IfmHandle, int, int);	/* returns ncod_h */
  double  (*getBccHeatValue) (IfmHandle, int, int);		/* returns bc_h.v */
  void	  (*setBccFlowValueAtCurrentTime) (IfmHandle, int, double, int);
  int	  (*setBccFlowTypeAndValueAtCurrentTime) (IfmHandle, int, int, int, double, int);
  void	  (*setBccMassValueAtCurrentTime) (IfmHandle, int, double, int);
  int	  (*setBccMassTypeAndValueAtCurrentTime) (IfmHandle, int, int, int, double, int);
  void	  (*setBccHeatValueAtCurrentTime) (IfmHandle, int, double, int);
  int	  (*setBccHeatTypeAndValueAtCurrentTime) (IfmHandle, int, int, int, double, int);
  void	  (*setBccFlowValueOfGroupIdAtCurrentTime) (IfmHandle, int, double, int);
  void	  (*setBccMassValueOfGroupIdAtCurrentTime) (IfmHandle, int, double, int);
  void	  (*setBccHeatValueOfGroupIdAtCurrentTime) (IfmHandle, int, double, int);

  /* Budget evaluation (v 4.919) */
  IfmBudget* (*budgetFlowCreate) (IfmDocument pDoc);
  IfmBudget* (*budgetMassCreate) (IfmDocument pDoc);
  IfmBudget* (*budgetHeatCreate) (IfmDocument pDoc);
  double     (*budgetQueryFlowAtNode) (IfmDocument pDoc, IfmBudget* pBudget, int nNode);
  double     (*budgetQueryMassAtNode) (IfmDocument pDoc, IfmBudget* pBudget, int nNode);
  double     (*budgetQueryHeatAtNode) (IfmDocument pDoc, IfmBudget* pBudget, int nNode);
  void       (*budgetClose) (IfmDocument pDoc, IfmBudget* pBudget);

  /* Inverse incidence matrix & double precision topology (v 4.921) */
  int	 (*getNumberOfNodeElements) (IfmHandle, int nNode);
  int	 (*getElement) (IfmHandle, int, int);
  double (*getExtentX_d) (IfmHandle);		/* returns scale_x */
  double (*getExtentY_d) (IfmHandle);		/* returns scale_y */
  double (*getExtentZ_d) (IfmHandle);		/* returns 1. ??? */
  double (*getX_d) (IfmHandle, int);		/* returns x[DIMX][n] */
  double (*getY_d) (IfmHandle, int);		/* returns x[DIMY][n] */
  double (*getZ_d) (IfmHandle, int);		/* returns elev[n][...] */
  double (*getXOfObsId_d) (IfmHandle, int);	/* returns obs x */ 
  double (*getYOfObsId_d) (IfmHandle, int);	/* returns obs y */ 
  double (*getZOfObsId_d) (IfmHandle, int);	/* returns obs z */ 

  /* Interpolated slice elevation (v. 5050) */
  double (*getZValueAtXYSlice) (IfmHandle hdl, double x, double y, int slc, IfmBool *ine);

  /* Extended budget evaluation (v. 5050) */
  IfmBool (*budgetComponentsQueryFlowAtNode) (IfmDocument pDoc, IfmBudget* pBudget,
					      int nNode, IfmBudgetComponents* pBudgetComp);
  IfmBool (*budgetComponentsQueryMassAtNode) (IfmDocument pDoc, IfmBudget* pBudget,
					      int nNode, IfmBudgetComponents* pBudgetComp);
  IfmBool (*budgetComponentsQueryHeatAtNode) (IfmDocument pDoc, IfmBudget* pBudget,
					      int nNode, IfmBudgetComponents* pBudgetComp);
  /* Setting of velocity vector components (v. 5057) */
  void   (*setXVelocityValue) (IfmHandle, int, double);
  void   (*setYVelocityValue) (IfmHandle, int, double);
  void   (*setZVelocityValue) (IfmHandle, int, double);
  double (*getFinalSimulationTime) (IfmHandle);

  /* Setting of x-, y- and z-coordinates (v. 5059) */
  void	 (*setX) (IfmHandle, int, double);	/* sets x[DIMX][n] */
  void	 (*setY) (IfmHandle, int, double);	/* sets x[DIMY][n] */
  void	 (*setZ) (IfmHandle, int, double);	/* sets elev[n][...] */
  void   (*getExtents) (IfmHandle, double* xmin, double* xmax, double* ymin, 
			double* ymax, double* zmin, double* zmax);
  const char* (*getProblemPath) (IfmHandle);
  const char* (*getProblemTitle) (IfmHandle);

  void   (*updateElementExtents) (IfmHandle hdl);

  /* Control of time stepping and mesh moving (v. 5062) */
  IfmBool (*timeStepIsRejected) (IfmHandle);
  IfmBool (*allowNodeMovement) (IfmHandle, int, double, double);

  /* Content computation (v. 5063) */
  double (*getTotalContent) (IfmHandle, IfmContentType);

  /* Mesh smooting (v. 5063) */
  IfmBool (*meshSmoothing) (IfmHandle, IfmSmoothVectorType);

  /* Gravity direction (v. 5.063) */
  IfmGravityDirection (*getGravityDirection) (IfmHandle, double*);

  /* Predictor values (v. 5.069) */
  double (*getPredictorHeadTimeValue) (IfmHandle, int);
  double (*getPredictorMassTimeValue) (IfmHandle, int);
  double (*getPredictorHeatTimeValue) (IfmHandle, int);

  /* Extended functions for unsaturated problems (v. 5.069) */
  double (*getMatUnsatFittingCoefficientDryingCurve) (IfmHandle, int);
  void (*setMatUnsatFittingCoefficientDryingCurve) (IfmHandle, int, double);
  int  (*getUnsatHysteresisIndicatorValue) (IfmHandle, int);
  double (*getUnsatHysteresisStarValue) (IfmHandle, int);
  double (*getFlowSaturationValueAtGivenHead) (IfmHandle, int, double);

  /* Added exchange measure function (v. 5.069) */
  double (*getExchangeThicknessAtNode3D) (IfmHandle, int, int);

  /* Extended functions for control of predictor-corrector solutions (v. 5.070) */
  void (*setResultsFlowHeadPreviousTimeValue) (IfmHandle, int, double);
  void (*setResultsTransportMassPreviousTimeValue) (IfmHandle, int, double);
  void (*setResultsTransportHeatPreviousTimeValue) (IfmHandle, int, double);
  double (*getAccelerationHeadTimeValue) (IfmHandle, int);
  double (*getAccelerationMassTimeValue) (IfmHandle, int);
  double (*getAccelerationHeatTimeValue) (IfmHandle, int);

  /* AMR control methods (v 5.071) */
  void	  (*setAmrElementRefinement) (IfmHandle, int nIndex, IfmRefinement flag);
  IfmRefinement (*getAmrElementRefinement) (IfmHandle, int nIndex);

  /* Search routines (v 5.155) */
  int	  (*findElementAtXY) (IfmHandle, double x, double y, double relax);
  int	  (*findNodeAtXY) (IfmHandle, double x, double y, double* dist);
  int	  (*getNextElement2D) (IfmHandle, int nElement, const IfmRect* rcBounds);
  int	  (*getNextNode2D) (IfmHandle, int nNode, const IfmRect* rcBounds);

  /* Anisotropic material functions in 3D (v.5.158) */
  double (*getMatAnisotropyAnglePhi) (IfmHandle, int);		/* get_mat call */
  double (*getMatAnisotropyAnglePsi) (IfmHandle, int);		/* get_mat call */
  double (*getMatAnisotropyAngleTheta) (IfmHandle, int);	/* get_mat call */
  void (*setMatAnisotropyAnglePhi) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatAnisotropyAnglePsi) (IfmHandle, int, double);	/* set_mat call */
  void (*setMatAnisotropyAngleTheta) (IfmHandle, int, double);	/* set_mat call */

  /* Multipsecies Id (v. 5.161) */
  int (*getNumberOfSpecies) (IfmHandle);
  int (*getSpeciesPhaseType) (IfmHandle, int);
  const char* (*getSpeciesName) (IfmHandle, int);
  int (*getSpeciesKineticsType) (IfmHandle, int);
  int (*getMultiSpeciesId) (IfmHandle);
  void (*setMultiSpeciesId) (IfmHandle, int);

  /* Fracture elements (5.253) */
  int (*getNumberOfTotalFractureElements) (IfmHandle);
  int (*getNumberOf1DFractureElements) (IfmHandle);
  int (*getNumberOf2DTriangularFractureElements) (IfmHandle);
  int (*getNumberOf2DQuadrilateralFractureElements) (IfmHandle);
  void (*getNodalArrayOfFractureElement) (IfmHandle, int, IfmFracNodes*);
  double (*getFracArea) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracFlowConductivity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracFlowStorativity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracFlowCompressibility) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracFlowSinkSource) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracFlowDensityRatio) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracFlowExpansionCoeff) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracFlowTransferIn) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracFlowTransferOut) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassPorosity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassSorptionCoeff) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassDiffusion) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassLongDispersivity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassTransDispersivity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassDecayRate) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassSinkSource) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassTransferIn) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracMassTransferOut) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatPorosity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatFluidCapacity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatSolidCapacity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatFluidConductivity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatSolidConductivity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatLongDispersivity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatTransDispersivity) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatFluidSinkSource) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatSolidSinkSource) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatTransferIn) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  double (*getFracHeatTransferOut) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracArea) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracFlowConductivity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracFlowStorativity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracFlowCompressibility) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracFlowSinkSource) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracFlowDensityRatio) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracFlowExpansionCoeff) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracFlowTransferIn) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracFlowTransferOut) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassPorosity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassSorptionCoeff) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassDiffusion) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassLongDispersivity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassTransDispersivity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassDecayRate) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassSinkSource) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassTransferIn) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracMassTransferOut) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatPorosity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatFluidCapacity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatSolidCapacity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatFluidConductivity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatSolidConductivity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatLongDispersivity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatTransDispersivity) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatFluidSinkSource) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatSolidSinkSource) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatTransferIn) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*setFracHeatTransferOut) (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);

  /* Flow 1st kind B.C. with special options (5.253) */
  int (*setBcPressureValueAtCurrentTime) (IfmHandle, int, double);
  int (*setBcSeepageFaceAtCurrentTime) (IfmHandle, int);
  int (*setBcSaturationValueAtCurrentTime) (IfmHandle, int, double);
  int (*setBcMoistureContentValueAtCurrentTime) (IfmHandle, int, double);
  double (*getElementalContent) (IfmHandle, IfmContentType, int);

  /* Extension for hysteretic unsaturated problems (5.254) */
  int (*getUnsatHysteresisCondition) (IfmHandle);
  void (*setUnsatHysteresisCondition) (IfmHandle);
  double (*getMatUnsatFittingExponentDryingCurve) (IfmHandle, int);
  double (*getMatUnsatFittingExponent2DryingCurve) (IfmHandle, int);
  double (*getMatUnsatFittingExponent3DryingCurve) (IfmHandle, int);
  void (*setMatUnsatFittingExponentDryingCurve) (IfmHandle, int, double);
  void (*setMatUnsatFittingExponent2DryingCurve) (IfmHandle, int, double);
  void (*setMatUnsatFittingExponent3DryingCurve) (IfmHandle, int, double);
  int (*getAMREstimatorType) (IfmHandle);
  void (*setAMREstimatorType) (IfmHandle, int);
  int (*getMassMatricesFlag) (IfmHandle);
  void (*setMassMatricesFlag) (IfmHandle, int);
  void (*setAMRType) (IfmHandle, int);

  int (*setBcFlowTypeAndValueAtCurrentTime2) (IfmHandle, int, int, int, int, double);
  int (*setBcMassTypeAndValueAtCurrentTime2) (IfmHandle, int, int, int, int, double);
  int (*setBcHeatTypeAndValueAtCurrentTime2) (IfmHandle, int, int, int, int, double);

  /* Predictor values (v. 5.257 */
  void (*setPredictorHeadTimeValue) (IfmHandle, int, double);
  void (*setPredictorMassTimeValue) (IfmHandle, int, double);
  void (*setPredictorHeatTimeValue) (IfmHandle, int, double);

  /* Additional Bcc types and elemental distributions (v. 5.258) */
  IfmBool (*isBccFlowSet) (IfmHandle, int, int);
  IfmBool (*isBccMassSet) (IfmHandle, int, int);
  IfmBool (*isBccHeatSet) (IfmHandle, int, int);
  long    (*getNumberOfElementalRefDistr) (IfmHandle);	
  void    (*getElementalRefDistrName) (IfmHandle, long, char*);
  long    (*getElementalRefDistrIdByName) (IfmHandle, const char*);
  double  (*getElementalRefDistrValue) (IfmHandle, long, long);
  void    (*setElementalRefDistrValue) (IfmHandle, long, long, double);
  long    (*createElementalRefDistr) (IfmHandle, const char*);
  void    (*deleteElementalRefDistr) (IfmHandle, long);

  /* Additional numerical settings (v. 5.268) */
  int  (*getMeshType) (IfmHandle);
  void (*setMeshType) (IfmHandle, int);
  int  (*getEquationSolvingType) (IfmHandle);
  void (*setEquationSolvingType) (IfmHandle, int);
  int  (*getIterativeSymEquationSolverType) (IfmHandle);
  void (*setIterativeSymEquationSolverType) (IfmHandle, int);
  int  (*getIterativeNonSymEquationSolverType) (IfmHandle);
  void (*setIterativeNonSymEquationSolverType) (IfmHandle, int);
  int  (*getRichardsEquationFormType) (IfmHandle);
  void (*setRichardsEquationFormType) (IfmHandle, int);
  int  (*getUnsatDerivativeCapaType) (IfmHandle);
  void (*setUnsatDerivativeCapaType) (IfmHandle, int);
  int  (*getUnsatWeightingType) (IfmHandle);
  void (*setUnsatWeightingType) (IfmHandle, int);
  int  (*getUnsatErrorCheckOption) (IfmHandle);
  void (*setUnsatErrorCheckOption) (IfmHandle, int);
  int  (*getUnsatIterationMethod) (IfmHandle);
  void (*setUnsatIterationMethod) (IfmHandle, int);
  double (*getInitialTimeIncrement) (IfmHandle);
  void (*setInitialTimeIncrement) (IfmHandle, double);
  void (*setFinalSimulationTime) (IfmHandle, double);
  double (*getTimeSteppingErrorTolerance) (IfmHandle);
  void (*setTimeSteppingErrorTolerance) (IfmHandle, double);
  int  (*getTimeSteppingKind) (IfmHandle);
  void (*setTimeSteppingKind) (IfmHandle, int);
  int  (*getPredictorCorrectorMethod) (IfmHandle);
  void (*setPredictorCorrectorMethod) (IfmHandle, int);
  double  (*getPredictorCorrectorTimeStepIncreasingRate) (IfmHandle);
  void (*setPredictorCorrectorTimeStepIncreasingRate) (IfmHandle, double);
  double  (*getPredictorCorrectorTimeStepMaximumSize) (IfmHandle);
  void (*setPredictorCorrectorTimeStepMaximumSize) (IfmHandle, double);
  IfmBool (*deleteFiniteElements) (IfmHandle pHdl, int* elist, int le);

  /*  Additional hysteresis function (v. 5302) */
  void (*setUnsatHysteresisIndicatorGeneral) (IfmHandle, IfmHysteresisIndicatorType);

  /* River boundary condition (v. 5308) */
  int (*setCoupledRiverBndNodes) (IfmHandle, int, int*, double*, double*);
  /* Elemental velocities (v. 5308) */
  IfmBool (*getResultsElementalVelocityValuesAtXYZ) (IfmHandle, double, double, double, IfmVTriplet*);
  /* Mass transfer boundary condition (v. 5308) */
  int (*setCoupledMassTransBndNodes) (IfmHandle, int, int*, double*, double*);
  /* Heat transfer boundary condition (v. 5308) */
  int (*setCoupledHeatTransBndNodes) (IfmHandle, int, int*, double*, double*);

  /* Enable/disable spatial index (v. 5357) */
  IfmBool (*enableSpatialIndex) (IfmHandle hdl, IfmBool bEnableIndex);

  /* Spline function dataset (v. 5357) */
  IfmBool (*getSplineSaturationFunction) (IfmHandle, int, IfmSpline*);
  IfmBool (*getSplineConductivityFunction) (IfmHandle, int, IfmSpline*);
  IfmBool (*setSplineSaturationFunction) (IfmHandle, int, const IfmSpline*);
  IfmBool (*setSplineConductivityFunction) (IfmHandle, int, const IfmSpline*);

  /* Spline function Ids (v. 5.404) */
  int (*getSplineSaturationId) (IfmHandle, int, int);
  int (*getSplineConductivityId) (IfmHandle, int, int);
  void (*setSplineSaturationId) (IfmHandle, int, int, int);
  void (*setSplineConductivityId) (IfmHandle, int, int, int);

  /* BHE functions (v. 5.404) */
  int (*getBHENumber) (IfmHandle);
  int (*getBHEReferenceNode) (IfmHandle, int);
  double (*getBHEHeatInputRate) (IfmHandle, int);
  double (*getBHEInletTemperature) (IfmHandle, int);
  double (*getBHEOutletTemperature) (IfmHandle, int);
  int (*getBHEType) (IfmHandle, int);
  double (*getBHEFlowDischarge) (IfmHandle, int);
  double (*getReferenceTemperature) (IfmHandle);
  void (*setBHEHeatInputRate) (IfmHandle, int, double);
  void (*setBHEInletTemperature) (IfmHandle, int, double);
  void (*setBHEFlowDischarge) (IfmHandle, int, double);

  /* Auxiliary function for identifying type formulation of transport equation(s) (v. 5.413) */
  IfmBool (*isDivergenceFormTransport) (IfmHandle);		/* returns flag.fte */

  /* New fracture (create and delete) functions (v. 6.001) */
  int (*createFracElement) (IfmHandle, int, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
  void (*deleteFracElement) (IfmHandle, int);

  /* BHE extension (v. 5.415) */
  void (*resetBHE) (IfmHandle);

  /* Modified hysteresis functions (v. 5.416, 6.002) */
  int  (*getUnsatHysteresisIndicatorValueAtNode) (IfmHandle, int);
  double (*getUnsatHysteresisStarValueAtNode) (IfmHandle, int, int);

  /* Spline function dataset (v. 6009) */
  IfmBool (*getSplineSaturationFunction2) (IfmHandle, int, IfmSpline2*);
  IfmBool (*getSplineConductivityFunction2) (IfmHandle, int, IfmSpline2*);
  int (*setSplineSaturationFunction2) (IfmHandle, int, const IfmSpline2*);
  int (*setSplineConductivityFunction2) (IfmHandle, int, const IfmSpline2*);

  /* Kernel interface access (v. 6071) */
  struct IUnknown* (*getDocumentInterface) (IfmHandle);
  IfmResult (*budgetCompute) (IfmHandle, IfmProblemClass, int*, int, double*, IfmBudgetComponentsEx*);

  /* BHE functions (v. 6.103) */
  int (*getBHEArrayNumber) (IfmHandle);
  const char* (*getBHEArrayName) (IfmHandle, int);
  void (*setBHEArrayFlowDischarge) (IfmHandle, int, double);
  void (*setBHEArrayInTemperature) (IfmHandle, int, double);
  double (*getBHEArrayFlowDischarge) (IfmHandle, int);
  double (*getBHEArrayOutTemperature) (IfmHandle, int);
  double (*getBHEArrayInTemperature) (IfmHandle, int);

  /* Residual functions (v. 6.104) */
  double (*getSolutionResidualNorm2) (IfmHandle, IfmProblemClass);
  double (*getSolutionResidualNormMax) (IfmHandle, IfmProblemClass);

  /* Species handling (v. 6.107) */
  int (*addSpecies) (IfmHandle hdl, const char* species_name, int inherit_from);

  /* Enable recording of reference distributions (v. 6.158) */
  IfmBool (*enableNodalRefDistrRecording) (IfmHandle hdl, long rID, IfmBool nEnable);
  IfmBool (*enableElementalRefDistrRecording) (IfmHandle hdl, long rID, IfmBool bEnable);

  /* Integration of a nodal property over a mesh element (v. 6.158) */
  double (*integrateNodalQuantitiesOfElement) (IfmHandle, int, const double*);

  /* Element diameter calculations (v. 6.158) */
  double (*getElementDiameter) (IfmHandle, int);
  double (*getFracElementDiameter) (IfmHandle, int);

  /* Inactive elements (v. 6.191) */
  int	 (*getMatElementActive) (IfmHandle, int);
  void	 (*setMatElementActive) (IfmHandle, int, int);

  /* Multi-layer wells (v. 6.202) */
  IfmBool (*queryMultiLayerWellInfo) (IfmHandle, int, IfmMLWInfo*);

  /* Multi-layer wells (v. 6.206) */
  int     (*getNumberOfMultiLayerWells) (IfmDocument pDoc);
  IfmBool (*isMultiLayerWellAttrValid) (IfmDocument pDoc, int, IfmMLW_ATTR);
  IfmBool (*isMultiLayerWellAttrTransient) (IfmDocument pDoc, int, IfmMLW_ATTR);
  double  (*getMultiLayerWellAttrValue) (IfmDocument pDoc, int, IfmMLW_ATTR);
  int	  (*getMultiLayerWellAttrTSID) (IfmDocument pDoc, int, IfmMLW_ATTR);
  void    (*setMultiLayerWellAttrValue) (IfmHandle, int, IfmMLW_ATTR, double);
  void    (*setMultiLayerWellAttrTSID) (IfmHandle, int, IfmMLW_ATTR, int);

  /* Access to flow law in fracture elements (v. 6.206) */
  IfmFractureLaw (*getFracLaw) (IfmHandle, int, IfmFractureType, IfmFractureMode);
  void	  (*setFracLaw) (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);

  /* Access to selection item sets (v. 6.206) */
  int	      (*getNumberOfSelections)(IfmDocument pDoc, IfmSEL_TYPE nSelType);
  int	      (*getSelectionCapacity) (IfmDocument pDoc, IfmSEL_TYPE nSelType);
  int	      (*findSelection) (IfmDocument pDoc, IfmSEL_TYPE nSelType, const char* pszSelName);
  int	      (*createSelection) (IfmDocument pDoc, IfmSEL_TYPE nSelType, const char* pszSelName);
  IfmResult   (*deleteSelection) (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex);
  const char* (*getSelectionName) (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex);
  int	      (*enumSelectionItems) (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex, int nStartPos);
  IfmBool     (*selectionItemIsSet) (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex, int nItem);
  void	      (*setSelectionItem) (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex, int nItem);
  void	      (*clearSelectionItem) (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex, int nItem);

  /* Expression based distributions (v. 6.206) */
  int	      (*getNumberOfNodalExprDistr) (IfmDocument pDoc);
  int	      (*getNumberOfElementalExprDistr) (IfmDocument pDoc);
  const char* (*getNodalExprDistrName) (IfmDocument pDoc, int nID);
  const char* (*getElementalExprDistrName) (IfmDocument pDoc, int nID);
  int	      (*getNodalExprDistrIdByName) (IfmDocument pDoc, const char* pszName);
  int	      (*getElementalExprDistrIdByName) (IfmDocument pDoc, const char* pszName);
  double      (*getNodalExprDistrValue) (IfmDocument pDoc, int nID, int nIndex);
  double      (*getElementalExprDistrValue) (IfmDocument pDoc, int nID, int nIndex);

  /* Access to element number of nodes (v. 6.206) */
  int	      (*getNumberOfElementNodes) (IfmHandle hdl, int nElement);
  int	      (*getNumberOfElementNodes2D) (IfmHandle hdl, int nElement);

  /* Velocity field (v. 6.206) */
  IfmBool     (*isVelocityFieldPresent)(IfmDocument pDoc);

  /* History values (v. 6.209) */
  IfmResult   (*getHistoryDimensions)(IfmDocument pDoc, IfmHistoryID nID, int nKind, int* nTimes, int* nCurves);
  IfmResult   (*getHistoryValues)(IfmDocument pDoc, IfmHistoryID nID, int nKind, int nTimes, int nCurves, double* pTimes, double** pValues);

  /* Nodal velocity, interpolation on refdist, 3d search (v. 6.212) */
  IfmBool     (*getResultsNodalVelocityValuesAtXYZ) (IfmDocument, double x, double y, double z, IfmVTriplet* v);
  IfmBool     (*getNodalRefDistrValueAtXYSlice) (IfmHandle, long refid, double x, double y, int slice, double* pVal);
  IfmBool     (*getNodalRefDistrValueAtXYZ) (IfmHandle, long refid, double x, double y, double z, double* pVal);
  int	      (*findElementAtXYZ) (IfmHandle, double x, double y, double z);
  int	      (*findNodeAtXYZ) (IfmHandle, double x, double y, double z, double* dist);
};

struct IfmDocumentPart
{
  int				nId;   		/* Class identification code */
  int				nVersion;   	/* FEFLOW's document version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmDocumentMethods*	pfn;	   	/* Implementation of the interface */
  IfmPointer			privData; 	/* Pointer to private (FEFLOW's) data */
};

struct IfmDocumentStruct
{
  int				numParts;   	/* Number of available parts */
  IfmPointer			hdlData;	/* Handle-specific data */
  IfmPointer			pReserve[2];	/* Reserve for future releases */
  struct IfmModulePart		mod;		/* Module interface */
  struct IfmGraphicPart		gph;		/* Graphics interface */
  struct IfmDocumentPart	doc;		/* Document interface */
};

/* Macros for easier access */
#define DOC_STRUCT(pHdl) ((struct IfmDocumentStruct*)pHdl)
#define DOC_PART(pHdl) (&DOC_STRUCT(pHdl)->doc)
#define DOC_CALL(pHdl, func, args) DOC_PART(pHdl)->pfn->func args
#define IS_DOC_STRUCT(pHdl) ((pHdl)->numParts >= 3 && DOC_PART(pHdl)->nId == IFM_DOCUMENT_ID)

#define DOC_ASSERT_VALID(pHdl) \
  GPH_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_DOCUMENT_ID, IFM_CURRENT_DOCUMENT_VERSION)

#define DOC_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, DOC_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmDocumentMethods, proc) < DOC_PART(pHdl)->nProcs)

#endif /* IFM_DOCUMENTP_H */
