#ifndef IFM_XDK_H
#define IFM_XDK_H

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

#ifndef NeedFunctionPrototypes
#define NeedFunctionPrototypes 1
#endif
#ifndef NeedWidePrototypes
#define NeedWidePrototypes 1
#endif
#ifndef NeedNestedPrototypes
#define NeedNestedPrototypes 1
#endif

#include "graphic.h"

#ifndef IFM_CURRENT_X11_VERSION
#define IFM_CURRENT_X11_VERSION 0x5050
#define IFM_CURRENT_XT_VERSION  0x5050
#define IFM_CURRENT_XM_VERSION  0x5050
#endif

#if defined IFM_TARGET_VERSION && IFM_TARGET_VERSION < IFM_CURRENT_X11_VERSION
#define IFM_TARGET_X11_VERSION IFM_TARGET_VERSION
#else
#define IFM_TARGET_X11_VERSION IFM_CURRENT_X11_VERSION
#endif

IFM_FUNCPROTOBEGIN

extern IfmResult IfmInitXDK(IfmHandle pMod);

IFM_FUNCPROTOEND

#endif /* IFM_XDK_H */
