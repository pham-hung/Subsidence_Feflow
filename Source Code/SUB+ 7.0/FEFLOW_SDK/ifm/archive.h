#ifndef IFM_ARCHIVE_H
#define IFM_ARCHIVE_H

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
#ifdef IFM_USE_X11
/*#include "xdk.h"*/
#endif

#ifndef IFM_CURRENT_ARCHIVE_VERSION
#define IFM_CURRENT_ARCHIVE_VERSION 0x5308
#endif

#if defined IFM_TARGET_VERSION && IFM_TARGET_VERSION < IFM_CURRENT_ARCHIVE_VERSION
#undef  IFM_CURRENT_ARCHIVE_VERSION
#define IFM_CURRENT_ARCHIVE_VERSION IFM_TARGET_VERSION
#endif

#if IFM_REQUIRED_VERSION < IFM_CURRENT_ARCHIVE_VERSION
#undef  IFM_REQUIRED_VERSION
#define IFM_REQUIRED_VERSION IFM_CURRENT_ARCHIVE_VERSION
#endif

		/* Special handle type */
typedef IfmHandle IfmArchive;

typedef enum {IfmIO_LOAD, IfmIO_STORE, IfmIO_FREE, IfmIO_INIT} IfmioMode;
typedef void (*IfmioProc) (IfmHandle pHdl, void* pData);

IFM_FUNCPROTOBEGIN

extern int IfmArchiveVersion (IfmHandle);

extern const char* IfmioGetPath(IfmHandle);
extern int IfmioGetVersion (IfmHandle);
extern IfmioMode IfmioGetMode (IfmHandle pHdl);
extern void IfmioSetMode (IfmHandle pHdl, IfmioMode newMode);
extern void IfmioFree (IfmHandle pHdl, IfmioProc pfnProc, void* pData);
extern void IfmioBool (IfmArchive pArc, IfmBool* pData);
extern void IfmioChar (IfmHandle pHdl, char* pData);
extern void IfmioShort (IfmHandle pHdl, short* pData);
extern void IfmioInt (IfmHandle pHdl, int* pData);
extern void IfmioLong (IfmHandle pHdl, long* pData);
extern void IfmioInt64 (IfmHandle pHdl, IfmInt64* pData);
extern void IfmioUChar (IfmHandle pHdl, unsigned char* pData);
extern void IfmioUShort (IfmHandle pHdl, unsigned short* pData);
extern void IfmioUInt (IfmHandle pHdl, unsigned int* pData);
extern void IfmioULong (IfmHandle pHdl, unsigned long* pData);
extern void IfmioUInt64 (IfmHandle pHdl, IfmUInt64* pData);
extern void IfmioFloat (IfmHandle pHdl, float* pData);
extern void IfmioDouble (IfmHandle pHdl, double* pData);
extern void IfmioString (IfmHandle pHdl, char** pData, unsigned int len);
extern void IfmioRelativePath (IfmHandle pHdl, IfmPath* pPath);
extern void IfmioBinary (IfmHandle pHdl, void* pData, unsigned int len);
extern void _IfmioArray (IfmArchive pArc, void* pArray,
			unsigned int* pnCount, unsigned int nElemSize,
		 	IfmioProc pfnElemProc);
extern void IfmioVector (IfmArchive pArc, void* pArray, unsigned int nCount,
			unsigned int nElemSize, IfmioProc pfnElemProc);
extern void _IfmioArray2D (IfmArchive pArc, void* pArray, unsigned int* pnRows,
			unsigned int* pnColumns, unsigned int nElemSize,
			IfmioProc pfnElemProc);
extern void IfmioMatrix2D (IfmArchive pArc, void* pArray, unsigned int nRows,
			unsigned int nColumns, unsigned int nElemSize,
			IfmioProc pfnElemProc);
void IfmioPixel(IfmArchive pArc, Pixel* pPixel);

#ifdef _DEBUG
extern void _IfmioArrayDbg (IfmArchive pArc, void* pArray,
			unsigned int* pnCount, unsigned int nElemSize,
		 	IfmioProc pfnElemProc, const char* pszFile, int nLineNo);
extern void _IfmioArray2DDbg (IfmArchive pArc, void* pArray, unsigned int* pnRows,
			unsigned int* pnColumns, unsigned int nElemSize,
			IfmioProc pfnElemProc, const char* pszFile, int nLineNo);
#endif /* _DEBUG */

#if IFM_CURRENT_ARCHIVE_VERSION >= 0x6156
void IfmioInt64 (IfmArchive pArc, IfmInt64* pData);
void IfmioUInt64 (IfmArchive pArc, IfmUInt64* pData);
#endif

IFM_FUNCPROTOEND

/* For convenience */
#define IfmioStringFree(a,b) IfmioFree(a,(IfmioProc)IfmioString,b)

#ifdef _DEBUG
#define IfmioArray(a,b,c,d,e) _IfmioArrayDbg(a,b,c,d,e,__FILE__,__LINE__)
#define IfmioArray2D(a,b,c,d,e,f) _IfmioArray2DDbg(a,b,c,d,e,f,__FILE__,__LINE__)
#else /* !_DEBUG */
#define IfmioArray _IfmioArray
#define IfmioArray2D _IfmioArray2D
#endif /* _DEBUG */

#if defined __cplusplus && !defined IFM_NO_STL

#include <vector>
#include <list>
#include <map>
#include <string>

// Prototypes
inline void IfmioTypedItem(IfmArchive pArc, char& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioChar(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, short& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioShort(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, int& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioInt(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, long& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioLong(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, IfmInt64& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioInt64(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, unsigned char& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioUChar(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, unsigned short& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioUShort(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, unsigned int& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioUInt(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, unsigned long& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioULong(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, IfmUInt64& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioUInt64(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, float& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioFloat(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, double& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioDouble(pArc, &x);
}
inline void IfmioTypedItem(IfmArchive pArc, char*& x)
{
  if (IfmioGetMode(pArc) != IfmIO_INIT) IfmioString(pArc, &x, ~0);
}

// Serialize a string
inline void IfmioTypedItem(IfmArchive pArc, std::string& x)
{
  char* s;
  switch (IfmioGetMode(pArc)) {
    case IfmIO_STORE:
      s = const_cast<char*>(x.c_str());
      IfmioString(pArc, &s, ~0);
      break;
    case IfmIO_LOAD:
      s = NULL;
      IfmioString(pArc, &s, ~0);
      x.assign(s);
      IfmFreeMem(pArc, &s);
      break;
  }
}

// Serialize a std::vector of any TypedItem
template <typename T>
void IfmioTypedItem(IfmArchive pArc, std::vector<T>& v)
{
  unsigned int nSize;
  switch (IfmioGetMode(pArc)) {
    case IfmIO_STORE:
      nSize = (unsigned int)v.size();
      IfmioTypedItem(pArc, nSize);
      for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
	IfmioTypedItem(pArc, *i);
      break;
    case IfmIO_LOAD:
      nSize = 0;
      IfmioTypedItem(pArc, nSize);
      v.resize(nSize);
      for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
	IfmioTypedItem(pArc, *i);
      break;
  }
}

// Serialize a std::list of any TypedItem
template <typename T>
void IfmioTypedItem(IfmArchive pArc, std::list<T>& v)
{
  unsigned int nSize;
  switch (IfmioGetMode(pArc)) {
    case IfmIO_STORE:
      nSize = (unsigned int)v.size();
      IfmioTypedItem(pArc, nSize);
      for (typename std::list<T>::iterator i = v.begin(); i != v.end(); ++i)
	IfmioTypedItem(pArc, *i);
      break;
    case IfmIO_LOAD:
      nSize = 0;
      IfmioTypedItem(pArc, nSize);
      for (unsigned int i = 0; i < nSize; i++) {
	T x;
	IfmioTypedItem(pArc, x);
	v.push_back(x);
      }
      break;
  }
}

// Serialize a std::map of any TypedItem
template <typename ID, typename T>
void IfmioTypedItem(IfmArchive pArc, std::map<ID,T>& v)
{
  unsigned int nSize;
  switch (IfmioGetMode(pArc)) {
    case IfmIO_STORE:
      nSize = (unsigned int)v.size();
      IfmioTypedItem(pArc, nSize);
      for (typename std::map<ID,T>::iterator i = v.begin(); i != v.end(); ++i) {
	IfmioTypedItem(pArc, const_cast<ID&>(i->first));
	IfmioTypedItem(pArc, i->second);
      }
      break;
    case IfmIO_LOAD:
      nSize = 0;
      IfmioTypedItem(pArc, nSize);
      for (unsigned int i = 0; i < nSize; i++) {
	ID id; T x;
	IfmioTypedItem(pArc, id);
	IfmioTypedItem(pArc, x);
	v[id] = x;
      }
      break;
  }
}

#endif /* C++ */

#endif /* IFM_ARCHIVE_H */
