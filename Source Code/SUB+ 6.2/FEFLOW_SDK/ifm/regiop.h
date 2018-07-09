#ifndef IFM_REGIOP_H
#define IFM_REGIOP_H

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

#include "regio.h"
#include "documentp.h"

/* This ID must be unique across all IFM subsystems 
   (use regex 'IFM_.*_ID[	 ]*[0-9]' to verify) */
#define IFM_REGIO_ID		3

struct IfmRegioMethods
{
  /* Control methods */

  IfmRegioType (*getType) (IfmHandle);		/* depending on context */
  int	 (*getCurrentSlice) (IfmHandle);
  int	 (*getCurrentLayer) (IfmHandle);

  /* Measure points methods */

  int	 (*getDimensionOfMeasurePoints) (IfmHandle);
  int	 (*getNumberOfMeasurePoints) (IfmHandle);
  float	 (*getMeasureX) (IfmHandle, int);
  float	 (*getMeasureY) (IfmHandle, int);
  float	 (*getMeasureZ) (IfmHandle, int);
  double (*getMeasureValue) (IfmHandle, int);

  /* Sample points methods */

  int	 (*getDimensionOfSamplePoints) (IfmHandle);
  int	 (*getNumberOfSamplePoints) (IfmHandle);
  float	 (*getSampleX) (IfmHandle, int);
  float	 (*getSampleY) (IfmHandle, int);
  float	 (*getSampleZ) (IfmHandle, int);
  double (*getSampleValue) (IfmHandle, int);
  void	 (*setSampleValue) (IfmHandle, int, double);

};

struct IfmRegioPart
{
  int				nId;   		/* Subsystem identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmRegioMethods*	pfn;	   	/* Implementation of the interface */
  void*				privData;  	/* Pointer to implementation data */
};

struct IfmRegioStruct
{
  int				numParts;   	/* Number of available parts */
  IfmPointer			hdlData;	/* Handle-specific data */
  IfmPointer			pReserve[2];	/* Reserve for future releases */
  struct IfmModulePart		mod;		/* Module interface */
  struct IfmGraphicPart		gph;		/* Graphics interface */
  struct IfmDocumentPart	doc;		/* Document interface */
  struct IfmRegioPart		reg;		/* Regionalization interface */
};

/* Macros for easier access */
#define REG_STRUCT(pHdl) ((struct IfmRegioStruct*)pHdl)
#define REG_PART(pHdl) (&REG_STRUCT(pHdl)->reg)
#define REG_CALL(pHdl, func, args) REG_PART(pHdl)->pfn->func args
#define IS_REG_STRUCT(pHdl) ((pHdl)->numParts >= 4 && REG_PART(pHdl)->nId == IFM_REGIO_ID)

#define REG_ASSERT_VALID(pHdl) \
  DOC_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_REGIO_ID, IFM_CURRENT_REGIO_VERSION)

#define REG_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, REG_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmRegioMethods, proc) < REG_PART(pHdl)->nProcs)

#endif /* IFM_REGIOP_H */
