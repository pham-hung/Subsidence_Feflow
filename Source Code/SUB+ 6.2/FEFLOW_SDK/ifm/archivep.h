#ifndef IFM_ARCHIVEP_H
#define IFM_ARCHIVEP_H

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

#include "modulep.h"
#include "documentp.h"
#include "archive.h"

/* This ID must be unique across all IFM subsystems 
   (use regex 'IFM_.*_ID[	 ]*[0-9]' to verify) */
#define IFM_ARCHIVE_ID		6

struct IfmArchiveMethods
{
  int (*getVersion)(IfmHandle);			/* Get archive version */
  IfmioMode (*getMode)(IfmHandle);		/* Get I/O mode - LOAD, STORE or FREE */
  void (*setMode)(IfmHandle, IfmioMode);	/* Set I/O mode - LOAD, STORE or FREE */
  void (*ioChar)(IfmHandle, char*);		/* Load, store or free a character */
  void (*ioShort)(IfmHandle, short*);		/* Load, store or free a short integer */
  void (*ioInt)(IfmHandle, int*);		/* Load, store or free an integer */
  void (*ioLong)(IfmHandle, long*);		/* Load, store or free a long integer */
  void (*ioUChar)(IfmHandle, unsigned char*);	/* dto. but unsigned */
  void (*ioUShort)(IfmHandle, unsigned short*);
  void (*ioUInt)(IfmHandle, unsigned int*);	
  void (*ioULong)(IfmHandle, unsigned long*);
  void (*ioFloat)(IfmHandle, float*);		/* Floating point (4 Bytes) */
  void (*ioDouble)(IfmHandle, double*);		/* Double prec float (8 Bytes) */
  void (*ioString)(IfmHandle, char**, unsigned int); /* string */
  void (*ioBinary)(IfmHandle, void*, unsigned int); /* any binary data */
  const char* (*getPath)(IfmHandle);		/* Get archive path (either fem or dac) */
  void (*ioInt64)(IfmHandle, IfmInt64*);	/* Load, store or free a signed 64-bit integer */
  void (*ioUInt64)(IfmHandle, IfmUInt64*);	/* Load, store or free an unsigned 64-bit integer */
};
 
struct IfmArchivePart
{
  int				nId;   		/* Part identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmArchiveMethods*	pfn;	   	/* Implementation of the interface */
  IfmPointer			privData;  	/* Pointer to private data */
};

struct IfmArchiveStruct
{
  int				numParts;   	/* Number of available parts */
  IfmPointer			hdlData;	/* Handle-specific data */
  IfmPointer			pReserve[2];	/* Reserve for future releases */
  struct IfmModulePart		mod;		/* Module interface */
  struct IfmGraphicPart		gph;		/* Graphics interface */
  struct IfmArchivePart		arc;		/* Archive interface */
};

/* Macros for easier access */

#define ARC_STRUCT(pHdl) ((struct IfmArchiveStruct*)pHdl)
#define ARC_PART(pHdl) (&ARC_STRUCT(pHdl)->arc)
#define ARC_CALL(pHdl, func, args) ARC_PART(pHdl)->pfn->func args
#define IS_ARC_STRUCT(pHdl) ((pHdl)->numParts >= 3 && ARC_PART(pHdl)->nId == IFM_ARCHIVE_ID)

#define ARC_ASSERT_VALID(pHdl) \
  GPH_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_ARCHIVE_ID, IFM_CURRENT_ARCHIVE_VERSION)

#define ARC_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, ARC_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmArchiveMethods, proc) < ARC_PART(pHdl)->nProcs)

#endif /* IFM_ARCHIVEP_H */
