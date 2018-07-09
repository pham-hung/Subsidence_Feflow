#ifndef IFM_MODULEP_H
#define IFM_MODULEP_H

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

#include "module.h"
#include "graphicp.h"

#include <stdarg.h>

/* This ID must be unique across all IFM subsystems 
   (use regex 'IFM_.*_ID[	 ]*[0-9]' to verify) */
#define IFM_MODULE_ID		0

  /* Module methods */
struct IfmModuleMethods
{
  /* Version 0x0001 */
  void (*setUserData) (IfmHandle, IfmPointer);
  IfmPointer (*getUserData) (IfmHandle);

  IfmResult (*registerModule) (IfmHandle, const char*, const char*, 
			       const char*, unsigned int);
  void (*setDescriptionString) (IfmHandle, const char*);
  void (*setCopyrightString) (IfmHandle, const char*);
  void (*setCopyrightPath) (IfmHandle, const char*);
  void (*setHtmlPage) (IfmHandle, const char*);
  IfmProc (*registerProc) (IfmHandle, const char*, unsigned int, IfmProc);

  			/* Exception handling  */
  void (*tryProc) (IfmHandle, IfmTryProc, void*);
  void (*throwException) (IfmHandle, const char*, const char*);
  void (*resume) (IfmHandle);

			/* Global path settings */
  const char* (*getModulePath) (IfmHandle);
  const char* (*getInstallPath) (IfmHandle);
  const char* (*getHelpPath) (IfmHandle);
  const char* (*getLastProjectPath) (IfmHandle);
  char* (*getComponentPath) (IfmHandle, char*, int, const char*);

			/* Memory allocation */
  void (*enableMemoryExceptions) (IfmHandle, IfmBool);
  IfmResult (*allocMem) (IfmHandle, void*, unsigned int, unsigned int, int);
  IfmResult (*reallocMem) (IfmHandle, void*, unsigned int, unsigned int);
  void (*freeMem) (IfmHandle, void*);
  IfmResult (*newString) (IfmHandle, char**, const char*);
  IfmResult (*allocMem2D) (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, IfmBool);
  IfmResult (*allocMem2Dvar) (IfmHandle, void*, unsigned int, unsigned int*,
			   unsigned int, IfmBool);
  IfmResult (*reallocMem2D) (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, IfmBool);
  IfmResult (*allocMem3D) (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, unsigned int, IfmBool);
  IfmResult (*allocMem4D) (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, unsigned int, unsigned int, IfmBool);

  void (*freeMem2D) (IfmHandle, void*);
  void (*freeMem3D) (IfmHandle, void*);
  void (*freeMem4D) (IfmHandle, void*);

			  /* Profile handling */
  char* (*pfGetString) (IfmHandle, const char*, const char*,
		const char*);
  void (*pfSetString) (IfmHandle, const char*, const char*,
		const char*);
  void (*pfFreeString) (IfmHandle, char*);
  long (*pfGetLong) (IfmHandle, const char*, const char*,
		long);
  void (*pfSetLong) (IfmHandle, const char*, const char*,
		long);
  IfmBool (*pfGetBool) (IfmHandle, const char*, const char*,
		IfmBool);
  void (*pfSetBool) (IfmHandle, const char*, const char*,
		IfmBool);
  double (*pfGetDouble) (IfmHandle, const char*, const char*,
		double);
  void (*pfSetDouble) (IfmHandle, const char*, const char*,
		double);
  IfmResult (*setOption) (IfmHandle, IfmOptionType, IfmPointer);
  IfmResult (*getOption) (IfmHandle, IfmOptionType, IfmPointer);

  /* Since FEFLOW v 4.712 99/09/13 */
  void      (*freePath) (IfmHandle, IfmPath path);
  IfmPath   (*newPath) (IfmHandle, const char* srcPath1, va_list vargs);
  IfmPath   (*getDir) (IfmHandle, const char* path);
  IfmPath   (*getName) (IfmHandle, const char* path);
  IfmPath   (*getTitle) (IfmHandle, const char* path);
  IfmPath   (*getExt) (IfmHandle, const char* path);
  IfmResult (*defaultExt) (IfmHandle, IfmPath* path, const char* ext);
  IfmPath   (*forceExt) (IfmHandle, const char* path, const char* ext);
  IfmPath   (*getAbsPath) (IfmHandle, const char* relPath, const char* baseDir);
  IfmPath   (*getRelPath) (IfmHandle, const char* absPath, const char* baseDir);

  IfmPath   (*getCurDir) (IfmHandle);
  IfmResult (*makeDir) (IfmHandle, const char* path, IfmBool recursive);
  IfmResult (*rmDir) (IfmHandle, const char* path, IfmBool recursive);

  /* Since FEFLOW v 5.050 2002/12/12 */
  IfmResult (*allocMemDbg) (IfmHandle, void*, unsigned int, unsigned int, int, 
			   const char*, int);
  IfmResult (*reallocMemDbg) (IfmHandle, void*, unsigned int, unsigned int, const char*, int);
  IfmResult (*newStringDbg) (IfmHandle, char**, const char*, const char*, int);
  IfmResult (*allocMem2DDbg) (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, IfmBool, const char*, int);
  IfmResult (*allocMem2DvarDbg) (IfmHandle, void*, unsigned int, unsigned int*,
			   unsigned int, IfmBool, const char*, int);
  IfmResult (*reallocMem2DDbg) (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, IfmBool, const char*, int);
  IfmResult (*allocMem3DDbg) (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, unsigned int, IfmBool, const char*, int);
  IfmResult (*allocMem4DDbg) (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, unsigned int, unsigned int, IfmBool, 
			   const char*, int);
  void	    (*freeMemDbg) (IfmHandle, void*);
  void	    (*freeMem2DDbg) (IfmHandle, void*);
  void	    (*freeMem3DDbg) (IfmHandle, void*);
  void	    (*freeMem4DDbg) (IfmHandle, void*);

  /* FEFLOW v 5.061 2003/07/25 */
  void	    (*setPrimarySource) (IfmHandle pMod, const char* pszSrcPath);

  /* FEFLOW v 6.000 2010/04/12 */
  int	    (*getFeflowKernelVersion) (IfmModule);

  /* FEFLOW v 6.007 2011/06/09 */
  IfmResult (*setCurDir) (IfmHandle, const char*);

  /* FEFLOW v 6.071 2012/06/25 */
  HRESULT   (*createInstance)(IfmHandle, REFCLSID rclsid, struct IUnknown* pUnkOuter, REFIID riid, void** ppv);
};

/*
** Each part starts with the following structure
*/
struct IfmAnyPart
{
  int				nId;   		/* Class identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
};

/*
** Module specific part
*/
struct IfmModulePart
{
  int				nId;   		/* Class identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmModuleMethods*	pfn;	   	/* Implementation of the interface */
  IfmPointer			privData;  	/* Pointer to FEFLOW's module data */
};

struct IfmModuleStruct
{
  int				numParts;   	/* Number of available parts */
  IfmPointer			hdlData;	/* Handle-specific data */
  void*				pReserve[2];	/* Reserve for future releases */
  struct IfmModulePart		mod;		/* Module interface */
  struct IfmGraphicPart		gph;		/* Graphics interface */
};

typedef  struct _IfmAnyList {
  char	*elem;		/* pointer to an array of elements	*/
  int	num_el;		/* current number of elements in array	*/
  int	max_el;		/* allocated size in the array		*/
} IfmAnyList;

/* Macros for easier access */

#define IFM_PROC_NUM(s_type, proc) \
    ((int)(((char*)(&(((s_type*)NULL)->proc)))-((char*)NULL))/sizeof(void(*)()))

#define MOD_STRUCT(pHdl) ((struct IfmModuleStruct*)pHdl)
#define MOD_PART(pHdl) (&MOD_STRUCT(pHdl)->mod)
#define MOD_CALL(pHdl, proc, args) MOD_PART(pHdl)->pfn->proc args
#define IS_MOD_STRUCT(pHdl) ((pHdl)->numParts >= 1 && MOD_PART(pHdl)->nId == IFM_MODULE_ID)

#define MOD_ASSERT_VALID(pHdl) \
  IFM_ASSERT_VALID(pHdl, IFM_MODULE_ID, IFM_CURRENT_MODULE_VERSION)

#define MOD_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, MOD_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmModuleMethods, proc) < MOD_PART(pHdl)->nProcs)

#define MOD_CALL_PROC(pHdl, proc, args) \
  MOD_ASSERT_VALID(pHdl);		\
  MOD_ASSERT_PROC(pHdl, proc);		\
  MOD_CALL(pHdl, proc, args)

#define MOD_CALL_FUNC(pHdl, proc, args) \
  MOD_ASSERT_VALID(pHdl);		\
  MOD_ASSERT_PROC(pHdl, proc);		\
  return MOD_CALL(pHdl, proc, args)


#define GPH_PART(pHdl) (&MOD_STRUCT(pHdl)->gph)
#define GPH_CALL(pHdl, proc, args) GPH_PART(pHdl)->pfn->proc args
#define IS_GPH_STRUCT(pHdl) ((pHdl)->numParts >= 2 && GPH_PART(pHdl)->nId == IFM_GRAPHIC_ID)

#define GPH_ASSERT_VALID(pHdl) \
  MOD_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_GRAPHIC_ID, IFM_CURRENT_GRAPHIC_VERSION)

#define GPH_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, GPH_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmGraphicMethods, proc) < GPH_PART(pHdl)->nProcs)

#define GPH_CALL_PROC(pHdl, proc, args) \
  GPH_ASSERT_VALID(pHdl);		\
  GPH_ASSERT_PROC(pHdl, proc);		\
  GPH_CALL(pHdl, proc, args)

#define GPH_CALL_FUNC(pHdl, proc, args) \
  GPH_ASSERT_VALID(pHdl);		\
  GPH_ASSERT_PROC(pHdl, proc);		\
  return GPH_CALL(pHdl, proc, args)

#endif /* IFM_MODULEP_H */
 
