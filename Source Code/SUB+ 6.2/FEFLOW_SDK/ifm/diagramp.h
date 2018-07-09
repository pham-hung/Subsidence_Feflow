#ifndef IFM_DIAGRAMP_H
#define IFM_DIAGRAMP_H

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
#define IFM_DIAGRAM_ID		7

struct IfmDiagramMethods
{
  void (*diagramDestroy) (IfmDiagram handle);
  void (*diagramSerialize) (IfmDiagram pDiagram, IfmArchive pArchive);
  void (*diagramShow) (IfmDiagram handle, IfmBool show_window);
  Widget (*diagramGetWidget) (IfmDiagram handle);
  void (*diagramGetValues) (IfmDiagram handle, const char* res_name, va_list vargs);
  void (*diagramSetValues) (IfmDiagram handle, const char* res_name, va_list vargs);
  int  (*diagramAddCurve) (IfmDiagram handle, IfmCurve curve);
  int  (*diagramRemoveCurve) (IfmDiagram handle, IfmCurve curve);
  int  (*diagramRemoveAllCurves) (IfmDiagram handle, IfmBool perm_only);
  IfmCurve (*diagramFindCurve) (IfmDiagram handle, const char* name);
  IfmDiagramFormatProc (*diagramSetFormatter) (IfmDiagram handle, IfmDiagramFormatProc proc, void* client_data);
  void (*diagramRedraw) (IfmDiagram handle, IfmBool draw_immediate);
};

struct IfmDiagramPart
{
  int				nId;   		/* Subsystem identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmDiagramMethods*	pfn;	   	/* Implementation of the interface */
  void*				privData;  	/* Pointer to implementation data */
};

struct IfmDiagramStruct
{
  int				numParts;   	/* Number of available parts */
  IfmPointer			hdlData;	/* Handle-specific data */
  IfmPointer			pReserve[2];	/* Reserve for future releases */
  struct IfmModulePart		mod;		/* Module interface */
  struct IfmGraphicPart		gph;		/* Graphics interface */
  struct IfmDiagramPart		dgr;		/* Diagram interface */
};

/* Macros for easier access */
#define DGR_STRUCT(pHdl) ((struct IfmDiagramStruct*)pHdl)
#define DGR_PART(pHdl) (&DGR_STRUCT(pHdl)->dgr)
#define DGR_CALL(pHdl, func, args) DGR_PART(pHdl)->pfn->func args
#define IS_DGR_STRUCT(pHdl) ((pHdl)->numParts >= 3 && DGR_PART(pHdl)->nId == IFM_DIAGRAM_ID)

#define DGR_ASSERT_VALID(pHdl) \
  GPH_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_DIAGRAM_ID, IFM_CURRENT_DIAGRAM_VERSION)

#define DGR_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, DGR_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmDiagramMethods, proc) < DGR_PART(pHdl)->nProcs)

#endif /* IFM_DIAGRAMP_H */
