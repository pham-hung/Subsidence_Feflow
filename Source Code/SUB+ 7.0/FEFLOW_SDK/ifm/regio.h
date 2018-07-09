#ifndef IFM_REGIO_H
#define IFM_REGIO_H

/********************** Copyright (C) DHI-WASY GmbH 2015 **********************
*
*	FEFLOW * interactive graphics-based Finite Element simulation
*		 system for subsurface FLOW and transport processes
*
*		-->	FEFLOW interface manager
*
*------------------------------------------------------------------------------
*
*
*  Copyright 1996-2015, DHI-WASY GmbH
*  All Rights Reserved.
*
*  This is UNPUBLISHED PROPRIETARY SOURCE CODE of DHI-WASY GmbH;
*  the contents of this file may not be disclosed to third parties, copied or
*  duplicated in any form, in whole or in part, without the prior written
*  permission of DHI-WASY GmbH
*
*-----------------------------------------------------------------------------*/

#include "module.h"
#include "document.h"

#ifndef IFM_CURRENT_REGIO_VERSION
#define IFM_CURRENT_REGIO_VERSION 0x4700
#endif

#if defined IFM_TARGET_VERSION && IFM_TARGET_VERSION < IFM_CURRENT_REGIO_VERSION
#undef  IFM_CURRENT_REGIO_VERSION
#define IFM_CURRENT_REGIO_VERSION IFM_TARGET_VERSION
#endif

#if IFM_REQUIRED_VERSION < IFM_CURRENT_REGIO_VERSION
#undef  IFM_REQUIRED_VERSION
#define IFM_REQUIRED_VERSION IFM_CURRENT_REGIO_VERSION
#endif

typedef IfmHandle IfmRegio;

typedef enum {
  IfmRegioSpecial,
  IfmRegioNodal,
  IfmRegioElemental
} IfmRegioType;

IFM_FUNCPROTOBEGIN

extern int IfmRegioGetVersion (IfmRegio);

extern IfmRegioType IfmRegioGetType (IfmRegio);
extern int IfmRegioGetCurrentSlice (IfmRegio);
extern int IfmRegioGetCurrentLayer (IfmRegio);

extern int IfmRegioGetDimensionOfMeasurePoints (IfmRegio);
extern int IfmRegioGetNumberOfMeasurePoints (IfmRegio);
extern float IfmRegioGetMeasureX (IfmRegio, int);
extern float IfmRegioGetMeasureY (IfmRegio, int);
extern float IfmRegioGetMeasureZ (IfmRegio, int);
extern double IfmRegioGetMeasureValue (IfmRegio, int);

extern int IfmRegioGetDimensionOfSamplePoints (IfmRegio);
extern int IfmRegioGetNumberOfSamplePoints (IfmRegio);
extern float IfmRegioGetSampleX (IfmRegio, int);
extern float IfmRegioGetSampleY (IfmRegio, int);
extern float IfmRegioGetSampleZ (IfmRegio, int);
extern double IfmRegioGetSampleValue (IfmRegio, int);
extern void IfmRegioSetSampleValue (IfmRegio, int, double);

IFM_FUNCPROTOEND

#define IfmRegioGetOriginX IfmGetOriginX
#define IfmRegioGetOriginY IfmGetOriginY
#define IfmRegioGetOriginZ IfmGetOriginZ

#endif /* IFM_REGIO_H */
 
