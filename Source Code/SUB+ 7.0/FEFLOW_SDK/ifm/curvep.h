#ifndef IFM_CURVEP_H
#define IFM_CURVEP_H

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
*  permission of DHI-WASY GmbH
*
*-----------------------------------------------------------------------------*/

#include "diagram.h"
#include "modulep.h"
#include "graphicp.h"
#include "stdarg.h"

/* This ID must be unique across all IFM subsystems 
   (use regex 'IFM_.*_ID[	 ]*[0-9]' to verify) */
#define IFM_CURVE_ID		8

struct IfmCurveMethods
{
  int  (*curveAddRef) (IfmCurve curve);
  int  (*curveRelease) (IfmCurve curve);
  void (*curveSetValues) (IfmCurve curve, const char* res_name, va_list vargs);
  void (*curveGetValues) (IfmCurve curve, const char* res_name, va_list vargs);
  int  (*curveAddPoint) (IfmCurve curve, double x, double y);
  int  (*curveAddPoints) (IfmCurve curve, double* x, double* y, int npoints);
  int  (*curveAddPointVector) (IfmCurve curve, IfmPoint* xy, int npoints);
  int  (*curveSetPoint) (IfmCurve curve, int index, double x, double y);
  int  (*curveGetNumberOfPoints) (IfmCurve curve);
  int  (*curveGetPoint) (IfmCurve curve, int index, double* x, double* y);
  int  (*curveQueryPoints) (IfmCurve curve, double* x, double* y, int start, int count);
  int  (*curveQueryPointVector) (IfmCurve curve, IfmPoint* xy, int start, int count);
  int  (*curveRemovePoints) (IfmCurve curve, int start, int count);
  void (*curveClear) (IfmCurve curve);
};

struct IfmCurvePart
{
  int				nId;   		/* Subsystem identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmCurveMethods*	pfn;	   	/* Implementation of the interface */
  void*				privData;  	/* Pointer to implementation data */
};

struct IfmCurveStruct
{
  int				numParts;   	/* Number of available parts */
  IfmPointer			hdlData;	/* Handle-specific data */
  IfmPointer			pReserve[2];	/* Reserve for future releases */
  struct IfmModulePart		mod;		/* Module interface */
  struct IfmGraphicPart		gph;		/* Graphics interface */
  struct IfmCurvePart		dgc;		/* Diagram interface */
};

/* Macros for easier access */
#define DGC_STRUCT(pHdl) ((struct IfmCurveStruct*)pHdl)
#define DGC_PART(pHdl) (&DGC_STRUCT(pHdl)->dgc)
#define DGC_CALL(pHdl, func, args) DGC_PART(pHdl)->pfn->func args
#define IS_DGC_STRUCT(pHdl) ((pHdl)->numParts >= 3 && DGC_PART(pHdl)->nId == IFM_CURVE_ID)

#define DGC_ASSERT_VALID(pHdl) \
  GPH_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_CURVE_ID, IFM_CURRENT_CURVE_VERSION)

#define DGC_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, DGC_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmCurveMethods, proc) < DGC_PART(pHdl)->nProcs)
#endif /* IFM_CURVEP_H */
