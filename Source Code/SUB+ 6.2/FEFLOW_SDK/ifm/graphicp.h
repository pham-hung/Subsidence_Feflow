#ifndef IFM_GRAPHICP_H
#define IFM_GRAPHICP_H

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

#include "graphic.h"

/* This ID must be unique across all IFM subsystems 
   (use regex 'IFM_.*_ID[	 ]*[0-9]' to verify) */
#define IFM_GRAPHIC_ID		1

  /* Window methods */
struct IfmGraphicMethods
{
  /* Version 0x0001 */
  					/* Call assertion dialog */
  void	 (*printAssert) (IfmHandle, const char*, const char*, unsigned int);
  					/* Call alert box */
  int	 (*alert) (IfmHandle, Widget, const char*, const char*);
					/* Display warning in log window*/
  void	 (*warning) (IfmHandle, const char*);
					/* Display message */
  void	 (*message) (IfmHandle, const char*);
  void	 (*progress) (IfmHandle, int);	/* Display progress */
  					/* Display Help */
  void	 (*help) (IfmHandle, Widget, const char*);
					 /* Add local fallback resources */  
  void	 (*addFallbackResources) (IfmHandle, Widget, const char*, const char* const*);
  Widget (*getTopLevelWindow) (IfmHandle);	 /* returns topLevel */
  Widget (*getMainWindow) (IfmHandle);	 /* returns allSW */
  Widget (*getPanelWindow) (IfmHandle);	 /* returns subMenu */
  Widget (*getActiveViewWindow) (IfmHandle); /* returns graphics */
  Pixmap (*getBackgroundPixmap) (IfmHandle); /* returns backg_pixmap */

  /* Version 0x0002 */

					/* Display debug message in log window*/
  void	(*debug) (IfmHandle, int, const char*);
  void	(*info) (IfmHandle, const char*);
  void	(*updateDisplay) (IfmHandle);
  void	(*bell) (IfmHandle);
  void	(*addCallback) (IfmHandle, Widget, const char*, 
		IfmCallbackProc, XtPointer);
  void	(*removeCallback) (IfmHandle, Widget, const char*,
		IfmCallbackProc, XtPointer);
  void	(*addEventHandler) (IfmHandle, Widget, EventMask,
		int, IfmEventHandler, XtPointer);
  void	(*removeEventHandler) (IfmHandle, Widget, EventMask,
		int, IfmEventHandler, XtPointer);
  IfmWorkProcId (*addWorkProc) (IfmHandle, XtAppContext,
		IfmWorkProc, XtPointer);
  void  (*removeWorkProc) (IfmHandle, IfmWorkProcId);
  IfmIntervalId (*addTimeOut) (IfmHandle, XtAppContext,
		unsigned long, IfmTimerCallbackProc, XtPointer);
  void	(*removeTimeOut) (IfmHandle, IfmIntervalId);
  IfmInputId (*addInput) (IfmHandle, XtAppContext, int,
		XtPointer, IfmInputCallbackProc, XtPointer);
  void	(*removeInput) (IfmHandle, IfmInputId);
  IfmSignalId (*addSignal) (IfmHandle, XtAppContext,
		IfmSignalCallbackProc, XtPointer);
  void	(*removeSignal) (IfmHandle, IfmSignalId);
  void	(*noticeSignal) (IfmHandle, IfmSignalId);

  /* Version 0x0003  01/19/1999 */

  Colormap (*getColormap) (IfmHandle);
  Pixel* (*getRainbowPalette) (IfmHandle, int*);
  Visual* (*getVisual) (IfmHandle);
  unsigned int (*getVisualDepth) (IfmHandle);

  /* Version 0x4710  05/31/1999 */
  WidgetClass (*getXbaeMatrixWidgetClass)(IfmHandle);
  WidgetClass (*getDtxComboBoxWidgetClass)(IfmHandle);
  void (*redrawDisplay) (IfmHandle);
  void (*beginWaitCursor) (IfmHandle, Widget shell);
  void (*endWaitCursor) (IfmHandle, Widget shell);

  /* Version 0x4712  10/13/1999 */
  IfmResult (*locatePath) (IfmHandle, IfmPath* path, IfmBool keepName, Widget parent);
  IfmResult (*fileSelection) (IfmHandle, IfmPath* pszPath, IfmBool bOpenDialog, 
			      IfmFileSelectionInfo* info, Widget parent);

  /* Version 0x4823  01/18/2001 */
  Cursor (*createXpmCursor) (IfmHandle, char** xpm);
  Pixmap (*createXpmPixmap) (IfmHandle, Widget w, char** xpm);
  void	 (*setXpmPixmap) (IfmHandle, Widget w, const char* res, char** xpm);
  Widget (*createEditor) (IfmHandle, Widget w, const char* name, Arg args[], int n);

  /* Version 0x5050  11/29/2002 */
  void (*drawFemMesh)(IfmHandle, Widget w, Pixmap pix, IfmRect* rectExtent, 
		      const IfmRect* rectVpt, double ratio, int nFlags);
  IfmDiagram (*diagramCreate) (IfmHandle handle, Widget parent, const char* title);
  IfmCurve (*curveCreate) (IfmHandle handle, const char* name, int points);
  XtAppContext (*getAppContext) (IfmHandle);
  IfmHandle (*initMotif) (IfmHandle handle);

  /* Version 0x5059  07/09/2003 */
  void	  (*getViewExtent) (IfmHandle pMod, double* xmin, double* ymin, double* xmax, double* ymax);
  IfmBool (*setViewExtent) (IfmHandle pMod, double xmin, double ymin, double xmax, double ymax);
  int	  (*transformPoints) (IfmHandle pMod, IfmPoint* points, int nPoints, 
				      IfmCoorSystem nSourceCS, IfmCoorSystem nTargetCS);
  int	  (*transformCoords) (IfmHandle pMod, double* x, double* y, int nPoints, 
				      IfmCoorSystem nSourceCS, IfmCoorSystem nTargetCS);
  void	  (*invalidateViewRect) (IfmHandle pMod, int xmin, int ymin, 
				 int xmax, int ymax);
  void	  (*redrawView) (IfmHandle pMod);

  /* Version 0x5106  06/11/2004 */
  void*	  (*getMainHwnd) (IfmHandle pMod);
  void*	  (*getAppInstance) (IfmHandle pMod);
  
  /* Version 0x5991  03/04/2010 */
  Pixel	  (*allocRGBColor) (IfmHandle pMod, int red, int green, int blue);
  Pixel	  (*allocNamedColor) (IfmHandle pMod, const char* colorname);
  void	  (*freeColor) (IfmHandle pMod, Pixel pixel);
  void	  (*queryColor) (IfmHandle pMod, Pixel pixel, int* red, int* green, int* blue);

#if IFM_CURRENT_GRAPHIC_VERSION >= 0x6154
  IfmBool (*editProperties) (IfmHandle pMod, const char* caption, const char* header, 
			     IfmProperty* prop_list, int num_prop);
#endif
};

struct IfmGraphicPart
{
  int				nId;   		/* Class identification code */
  int				nVersion;   	/* FEFLOW's graphics version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmGraphicMethods*	pfn;	   	/* Implementation of the interface */
  void*				privData; 	/* Pointer to private (FEFLOW's) data */
};

#include "modulep.h"

#endif /* IFM_GRAPHICP_H */
