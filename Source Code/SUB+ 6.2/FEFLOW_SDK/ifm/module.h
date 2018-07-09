#ifndef IFM_MODULE_H
#define IFM_MODULE_H

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
//#include <wintypes.h>
//#include <winguiddef.h>

#ifndef False
#define False 0
#endif
#ifndef True
#define True 1
#endif
#ifndef NULL
#define NULL 0
#endif

#ifndef IFM_CURRENT_MODULE_VERSION
#define IFM_CURRENT_MODULE_VERSION 0x6071
#endif

#if defined IFM_TARGET_VERSION && IFM_TARGET_VERSION < IFM_CURRENT_MODULE_VERSION
#undef  IFM_CURRENT_MODULE_VERSION
#define IFM_CURRENT_MODULE_VERSION IFM_TARGET_VERSION
#endif

#if IFM_REQUIRED_VERSION < IFM_CURRENT_MODULE_VERSION
#undef  IFM_REQUIRED_VERSION
#define IFM_REQUIRED_VERSION IFM_CURRENT_MODULE_VERSION
#endif

/* Control flags for the process flow */
enum {
  IfmCTL_CONTINUE = 0,		/* Continue the current process flow */
  IfmCTL_ABORT,			/* Immediate aborting, no further modules will be called */
  IfmCTL_BREAK,			/* Save termination of the current process loop */
  IfmCTL_REPEAT,		/* Repeat the last operation (iterating) (useful in post...) */
  IfmCTL_SKIP			/* Skip the next built-in operation (useful in pre...) */
};
		/* Opaque handle of an IFM subsystem */
typedef struct IfmModuleStruct* IfmHandle;

		/* Special handle type */
typedef IfmHandle IfmModule;

		/* Result of conditional operations */
typedef int IfmResult;

		/* Logical value */
typedef int IfmBool;
 
		/* Opaque pointer type */
typedef void* IfmPointer;

		/* File name pointer */
typedef char* IfmPath;

#ifdef WIN32			    /* 64-bit integer value */
typedef __int64 IfmInt64;
typedef unsigned __int64 IfmUInt64;
#else
typedef long long IfmInt64;
typedef unsigned long long IfmUInt64;
#endif

		/* In IFM context executed callback */
typedef void (*IfmTryProc)(IfmHandle, void*);

typedef struct {
  const char*       proc;	/* Name of the interface function */
  const char*       reason;	/* Reason of exceptional condition */
  enum {
    IfmEX_SKIP,			/* Skip execution of the calling function */
    IfmEX_CONTINUE,		/* Ignore exception (uFallback must be set!) */
    IfmEX_ABORT			/* Abort the current execution */
  }                 action;	
  enum {
    IfmEX_VOID,
    IfmEX_LONG,
    IfmEX_ULONG,
    IfmEX_FLOAT,
    IfmEX_DOUBLE,
    IfmEX_STRING,
    IfmEX_CHAR_ARRAY,
    IfmEX_POINTER
  }		    argType;	/* Argument type */
  union {
    long            aLong;	/* Value for all signed integers */
    unsigned long   aULong;	/* Value for all unsigned integers */
    float           aFloat;	/* Value for floats */
    double          aDouble;	/* Value for doubles */
    char*	    aString;	/* Value for strings (allocated) */
    char*	    aCharArray;	/* Value for strings (static) */
    void*	    aPointer;	/* Value for anonymous pointer */
  }                 argUnion;
} IfmExceptionContext;

typedef enum _IfmOptionType {
  IfmOPT_PERMANENT 	= 1,	/* Keep module permanent in memory */
  IfmOPT_DEBUG		= 2,	/* Enable argument validation (range check etc.) */
  IfmOPT_DOCEX		= 3,	/* Enable document extension */
  IfmOPT_DETACH 	= 4,	/* Enable/disable detaching shared library 
				   (disable for searching memory leaks) (v.5.05+) */
  /* for backward compatibility */
  IfmPERMANENT	= IfmOPT_PERMANENT,
  IfmDEBUG	= IfmOPT_DEBUG,
  IfmDOC_EX	= IfmOPT_DOCEX
} IfmOptionType;

		/* COM data types*/
#ifndef DEFINE_GUID
#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID {
  unsigned long  Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char  Data4[8];
} GUID;
#endif
typedef GUID IID;
typedef GUID CLSID;
#ifdef __cplusplus
typedef const IID& REFIID;
typedef const CLSID& REFCLSID;
#else
typedef const IID* REFIID;
typedef const CLSID* REFCLSID;
#endif
#endif
#ifndef HRESULT
typedef long HRESULT;
#endif
#ifndef IUnknown
struct IUnknown;
#endif
  
#ifdef __cplusplus
#define IFM_FUNCPROTOBEGIN extern "C" {
#define IFM_FUNCPROTOEND }
typedef IfmResult (*IfmProc) (IfmHandle, ...);
#else
#define IFM_FUNCPROTOBEGIN 
#define IFM_FUNCPROTOEND
typedef IfmResult (*IfmProc) ();
#endif

#ifndef NDEBUG
#define IFM_ASSERT(pHdl, exp) (void)((exp)||(IfmPrintAssert((pHdl), #exp, __FILE__, __LINE__), 0))
#define IFM_ASSERT_VALID(pHdl, id, nver) IfmAssertValid((pHdl), (id), (nver))
#define IFM_VERIFY(pHdl, exp) (void)((exp)||(IfmPrintAssert((pHdl), #exp, __FILE__, __LINE__), 0))
#else
#define IFM_ASSERT(pHdl, exp)
#define IFM_ASSERT_VALID(pHdl, id, nver) 
#define IFM_VERIFY(pHdl, exp) exp
#endif

/* End of variable argument lists */
#define IfmVaEnd ((char*)0)

IFM_FUNCPROTOBEGIN

#ifndef NDEBUG
extern void IfmPrintAssert (IfmHandle, const char*, const char*, unsigned int);
extern void IfmAssertValid (IfmHandle, int, int);
#endif
IfmBool IfmCheckHandle (IfmHandle, int);

extern int IfmModuleVersion (IfmHandle);
extern int IfmGetFeflowVersion (IfmModule);
#ifdef WIN32
extern int IfmFeflowResourceVersion();
#endif

/* Decimal/hexadecimal conversion */
extern int IfmHexToDec(int nHex);
extern int IfmDecToHex(int nDec);

extern void IfmModuleSetUserData (IfmHandle pHandle, IfmPointer pGlobalData); 
extern IfmPointer IfmModuleGetUserData (IfmHandle pHandle); 

extern IfmResult IfmRegisterModule (IfmHandle pHandle,
				    const char* ifcName,
				    const char* modName, 
				    const char* dpyName, 
				    unsigned int modVersion);
extern void IfmSetDescriptionString (IfmHandle pMod, const char* descString);
extern void IfmSetCopyrightString (IfmHandle pMod, const char* copyrightString);
extern void IfmSetCopyrightPath (IfmHandle pMod,
				 const char* copyrightPath);
extern void IfmSetHtmlPage (IfmHandle pMod, const char* htmlPage);
extern IfmProc IfmRegisterProc (IfmHandle pHandle, const char* procName, 
			          unsigned int procVersion, IfmProc procAddr);
extern void IfmEnableMemoryExceptions (IfmHandle, IfmBool);
extern IfmResult _IfmAllocMem (IfmHandle pHandle, void* pAddr, unsigned int nItemCount, 
			          unsigned int nItemSize, int bInitByZero);
extern IfmResult _IfmReallocMem (IfmHandle pHandle, void* pAddr, unsigned int nItemCount, 
			          unsigned int nItemSize);
extern IfmResult _IfmAllocMem2D (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, IfmBool);
extern IfmResult _IfmAllocMem2Dvar (IfmHandle, void*, unsigned int, unsigned int*,
			   unsigned int, IfmBool);
extern IfmResult _IfmReallocMem2D (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, IfmBool);
extern IfmResult _IfmAllocMem3D (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, unsigned int, IfmBool);
extern IfmResult _IfmAllocMem4D (IfmHandle, void*, unsigned int, unsigned int,
			   unsigned int, unsigned int, unsigned int, IfmBool);
extern IfmResult _IfmNewString (IfmHandle pHandle, char** pStringDest, const char* pStringSrc); 

extern void _IfmFreeMem (IfmHandle pHandle, void* ptrAddr);
extern void _IfmFreeMem2D (IfmHandle pHandle, void* ptrAddr);
extern void _IfmFreeMem3D (IfmHandle pHandle, void* ptrAddr);
extern void _IfmFreeMem4D (IfmHandle pHandle, void* ptrAddr);
extern int  _IfmGrowList   (IfmHandle, void*, int, int, int);
extern int  _IfmAdjustList (IfmHandle, void*, int);
extern void _IfmFreeList   (IfmHandle, void*);

#if IFM_CURRENT_MODULE_VERSION >= 0x5050 /* Debug version with leak check (MS-VC) */
extern IfmResult _IfmAllocMemDbg (IfmHandle pHandle, void* pAddr, unsigned int nItemCount, 
			unsigned int nItemSize, int bInitByZero, 
			const char* pszFileName, int nLineNo);
extern IfmResult _IfmReallocMemDbg (IfmHandle pHandle, void* pAddr, unsigned int nItemCount, 
			unsigned int nItemSize, const char* pszFileName, int nLineNo);
extern IfmResult _IfmAllocMem2DDbg (IfmHandle, void*, unsigned int, unsigned int,
			unsigned int, IfmBool, const char* pszFileName, int nLineNo);
extern IfmResult _IfmAllocMem2DvarDbg (IfmHandle, void*, unsigned int, unsigned int*,
			unsigned int, IfmBool, const char* pszFileName, int nLineNo);
extern IfmResult _IfmReallocMem2DDbg (IfmHandle, void*, unsigned int, unsigned int,
			unsigned int, IfmBool, const char* pszFileName, int nLineNo);
extern IfmResult _IfmAllocMem3DDbg (IfmHandle, void*, unsigned int, unsigned int,
			unsigned int, unsigned int, IfmBool, 
			const char* pszFileName, int nLineNo);
extern IfmResult _IfmAllocMem4DDbg (IfmHandle, void*, unsigned int, unsigned int,
			unsigned int, unsigned int, unsigned int, IfmBool, 
			const char* pszFileName, int nLineNo);
extern IfmResult _IfmNewStringDbg (IfmHandle pHandle, char** pStringDest, const char* pStringSrc, 
			const char* pszFileName, int nLineNo);

extern void _IfmFreeMemDbg (IfmHandle pHandle, void* ptrAddr);
extern void _IfmFreeMem2DDbg (IfmHandle pHandle, void* ptrAddr);
extern void _IfmFreeMem3DDbg (IfmHandle pHandle, void* ptrAddr);
extern void _IfmFreeMem4DDbg (IfmHandle pHandle, void* ptrAddr);
extern int  _IfmGrowListDbg  (IfmHandle, void*, int, int, int, const char*, int);
extern int  _IfmAdjustListDbg (IfmHandle, void*, int, const char*, int);
extern void _IfmFreeListDbg  (IfmHandle, void*);
#endif /* >= 5.050 */


extern void IfmTry (IfmHandle, IfmTryProc, void*);
extern void IfmThrowException (IfmHandle, const char*, const char*);

extern const char* IfmGetModulePath (IfmHandle);
extern const char* IfmGetInstallPath (IfmHandle);
extern const char* IfmGetHelpPath (IfmHandle);
extern const char* IfmGetLastProjectPath (IfmHandle);
extern char* IfmGetComponentPath (IfmHandle, char*, int, const char*);

extern char* IfmProfileGetString (IfmHandle, const char*, const char*,
		const char*);
extern void IfmProfileSetString (IfmHandle, const char*, const char*,
		const char*);
extern void IfmProfileFreeString (IfmHandle, char*);
extern long IfmProfileGetLong (IfmHandle, const char*, const char*,
		long);
extern void IfmProfileSetLong (IfmHandle, const char*, const char*,
		long);
extern IfmBool IfmProfileGetBool (IfmHandle, const char*, const char*,
		IfmBool);
extern void IfmProfileSetBool (IfmHandle, const char*, const char*,
		IfmBool);
extern double IfmProfileGetDouble (IfmHandle, const char*, const char*,
		double);
extern void IfmProfileSetDouble (IfmHandle, const char*, const char*,
		double);
extern IfmResult IfmModuleSetOption (IfmHandle, IfmOptionType, IfmPointer);
extern IfmResult IfmModuleGetOption (IfmHandle, IfmOptionType, IfmPointer);

#if IFM_CURRENT_MODULE_VERSION >= 0x4712
extern void      IfmFreePath (IfmHandle, IfmPath srcPath);
extern IfmPath   IfmNewPath (IfmHandle, const char* srcPath);
extern IfmPath   IfmVaNewPath (IfmHandle, const char* srcPath1, ...);
extern IfmPath   IfmGetFileDirectory (IfmHandle, const char* path);
extern IfmPath   IfmGetFileName (IfmHandle, const char* path);
extern IfmPath	 IfmGetFileTitle (IfmHandle, const char* path);
extern IfmPath   IfmGetFileExtension (IfmHandle, const char* path);
extern IfmResult IfmDefaultExtension (IfmHandle, IfmPath* path, const char* extension);
extern IfmPath   IfmForceExtension (IfmHandle, const char* path, const char* extension);
extern IfmPath   IfmGetAbsolutePath (IfmHandle, const char* relPath, const char* baseDir);
extern IfmPath   IfmGetRelativePath (IfmHandle, const char* absPath, const char* baseDir);
extern IfmPath   IfmGetCurrentDirectory (IfmHandle);
extern IfmResult IfmMakeDirectory (IfmHandle, const char* path, IfmBool recursive);
extern IfmResult IfmRemoveDirectory (IfmHandle, const char* path, IfmBool recursive);
#endif

#if IFM_CURRENT_MODULE_VERSION >= 0x5061
extern void IfmSetPrimarySource (IfmHandle pMod, const char* pszSrcPath);
#endif

#if (IFM_CURRENT_MODULE_VERSION >= 0x5416 && IFM_CURRENT_MODULE_VERSION < 0x5450) || IFM_CURRENT_MODULE_VERSION >= 0x6000
extern int IfmGetFeflowKernelVersion (IfmModule);
#endif

#if (IFM_CURRENT_MODULE_VERSION >= 0x5416 && IFM_CURRENT_MODULE_VERSION < 0x5450) || IFM_CURRENT_MODULE_VERSION >= 0x6007
extern IfmResult IfmSetCurrentDirectory (IfmHandle, const char* path);
#endif

#if IFM_CURRENT_MODULE_VERSION >= 0x6071
extern HRESULT  IfmCreateInstance (IfmHandle, REFCLSID rclsid, struct IUnknown* pUnkOuter, REFIID riid, void** ppv);
#endif

  /* FEFLOW v 6.007 2011/06/09 */

IFM_FUNCPROTOEND

/* For compatibility */
#define IfmGraphic IfmHandle
#define IfmModuleGetGraphic(hdl) hdl

#ifndef _DEBUG
#define IfmAllocMem	_IfmAllocMem
#define IfmReallocMem	_IfmReallocMem
#define IfmAllocMem2D	_IfmAllocMem2D
#define IfmAllocMem2Dvar _IfmAllocMem2Dvar
#define IfmReallocMem2D	_IfmReallocMem2D
#define IfmAllocMem3D	_IfmAllocMem3D
#define IfmAllocMem4D	_IfmAllocMem4D
#define IfmNewString	_IfmNewString
#define IfmFreeMem	_IfmFreeMem
#define IfmFreeMem2D	_IfmFreeMem2D
#define IfmFreeMem3D	_IfmFreeMem3D
#define IfmFreeMem4D	_IfmFreeMem4D
#define IfmGrowList	_IfmGrowList
#define IfmAdjustList	_IfmAdjustList
#define IfmFreeList	_IfmFreeList
#else	/* _DEBUG */
#define IfmAllocMem(h,p,n,s,i)		    _IfmAllocMemDbg(h,p,n,s,i,__FILE__,__LINE__)
#define IfmReallocMem(h,p,n,s)		    _IfmReallocMemDbg(h,p,n,s,__FILE__,__LINE__)
#define IfmAllocMem2D(h,p,n1,n2,s,i)	    _IfmAllocMem2DDbg(h,p,n1,n2,s,i,__FILE__,__LINE__)
#define IfmAllocMem2Dvar(h,p,n1,n2,s,i)	    _IfmAllocMem2DvarDbg(h,p,n1,n2,s,i,__FILE__,__LINE__)
#define IfmReallocMem2D(h,p,n1,n2,s,i)	    _IfmReallocMem2DDbg(h,p,n1,n2,s,i,__FILE__,__LINE__)
#define IfmAllocMem3D(h,p,n1,n2,n3,s,i)	    _IfmAllocMem3DDbg(h,p,n1,n2,n3,s,i,__FILE__,__LINE__)
#define IfmAllocMem4D(h,p,n1,n2,n3,n4,s,i)  _IfmAllocMem4DDbg(h,p,n1,n2,n3,n4,s,i,__FILE__,__LINE__)
#define IfmNewString(h,d,s)		    _IfmNewStringDbg(h,d,s,__FILE__,__LINE__)
#define IfmFreeMem	_IfmFreeMemDbg
#define IfmFreeMem2D	_IfmFreeMem2DDbg
#define IfmFreeMem3D	_IfmFreeMem3DDbg
#define IfmFreeMem4D	_IfmFreeMem4DDbg
#define IfmGrowList(h,a,s,c,g) _IfmGrowListDbg(h,a,s,c,g,__FILE__,__LINE__)
#define IfmAdjustList(h,a,s)_IfmAdjustListDbg(h,a,s,__FILE__,__LINE__)
#define IfmFreeList	_IfmFreeListDbg
#endif	/* _DEBUG */

#endif	/* IFM_MODULE_H */
