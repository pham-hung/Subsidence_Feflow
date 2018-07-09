#ifndef IFM_GRAPHIC_H
#define IFM_GRAPHIC_H

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

#if !defined IFM_NO_X11 && (defined IFM_USE_X11 || defined X_PROTOCOL || !defined WIN32)
#ifndef IFM_USE_X11
#define IFM_USE_X11
#endif
#undef  IFM_NO_X11
#endif
#ifdef IFM_NO_X11
#undef IFM_USE_X11
#endif
#if !defined IFM_USE_X11 && !defined IFM_NO_X11
#define IFM_NO_X11
#endif

#ifdef IFM_USE_X11
#include <X11/Intrinsic.h>
#else
typedef void *XtPointer;
typedef unsigned char Boolean;
typedef unsigned long Pixmap;
typedef unsigned long EventMask;
typedef unsigned long Colormap;
typedef unsigned long Pixel;
typedef unsigned long Cursor;
typedef unsigned long Drawable;
typedef short Position;
typedef unsigned short Dimension;
typedef struct _XEvent XEvent;
typedef struct _XtAppContext* XtAppContext;
typedef struct _Visual Visual;
typedef struct _WidgetRec* Widget;
typedef struct _WidgetClassRec* WidgetClass;
typedef struct _Arg Arg;
typedef struct {
  unsigned long pixel;
  unsigned short red, green, blue;
  char flags;  /* do_red, do_green, do_blue */
  char pad;
} XColor;
#endif

#include "module.h"
#include <time.h>

#ifndef IFM_CURRENT_GRAPHIC_VERSION
#define IFM_CURRENT_GRAPHIC_VERSION 0x6154
#endif

#if defined IFM_TARGET_VERSION && IFM_TARGET_VERSION < IFM_CURRENT_GRAPHIC_VERSION
#undef  IFM_CURRENT_GRAPHIC_VERSION
#define IFM_CURRENT_GRAPHIC_VERSION IFM_TARGET_VERSION
#endif

#if IFM_REQUIRED_VERSION < IFM_CURRENT_GRAPHIC_VERSION
#undef  IFM_REQUIRED_VERSION
#define IFM_REQUIRED_VERSION IFM_CURRENT_GRAPHIC_VERSION
#endif

typedef void* IfmIntervalId;
typedef void* IfmInputId;
typedef void* IfmWorkProcId;
typedef void* IfmSignalId;

typedef void (*IfmEventHandler)(
    IfmHandle		/* IFM handle */,
    Widget              /* widget */,
    XtPointer           /* closure */,
    XEvent*             /* event */,
    Boolean*            /* continue_to_dispatch */
);

typedef void (*IfmCallbackProc)(
    IfmHandle		/* IFM handle */,
    Widget              /* widget */,
    XtPointer           /* closure */, 
    XtPointer           /* call_data */
);

typedef void (*IfmTimerCallbackProc)(
    IfmHandle		/* IFM handle */,
    XtPointer           /* closure */,
    IfmIntervalId*      /* id */
);

typedef void (*IfmInputCallbackProc)(
    IfmHandle		/* IFM handle */,
    XtPointer           /* closure */,
    int*                /* source */,
    IfmInputId*          /* id */
);

typedef Boolean (*IfmWorkProc)(
    IfmHandle		/* IFM handle */,
    XtPointer           /* closure */
);

typedef void (*IfmSignalCallbackProc)(
    IfmHandle		/* IFM handle */,
    XtPointer           /* closure */,
    IfmSignalId*        /* id */
);

typedef struct _IfmFileSelectionInfo
{
  char*	      title;		  /* Title of the file selection box */
  char*	      initialDirectory;	  /* Initial directory */
  char*	      defaultExtension;	  /* Extensions of files to be listed */
  char*       filter;		  /* Example: "Text files (*.txt)|*.txt|All files (*.*)|*.*"  */
  int	      currentFilter;	  /* Index of current filter (0=first) */
  char*	      helpURL;		  /* HTML help file */
} IfmFileSelectionInfo;

typedef struct _IfmPoint	  /* 2D Point */
{
  double  x, y;			  /* Point coordinates */
} IfmPoint;

typedef struct _IfmRect		  /* 2D Rectangle */
{
  double  xmin, ymin, xmax, ymax; /* Bounding coordinates */
} IfmRect;

typedef IfmHandle  IfmDiagram;
typedef IfmHandle  IfmCurve;

typedef struct _IfmRGBA	      /* Color with alpha */
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
} IfmRGBA;


typedef enum _IfmPROP_TYPE     /* Note! String variables must be initialized by 0 or allocated with an IFM allocation routine! */
{
		      /* Variable passed as:  */
  IfmPROP_BOOL,	      /*   IfmBool*	      */
  IfmPROP_INT,	      /*   int*		      */
  IfmPROP_DOUBLE,     /*   double*	      */
  IfmPROP_STRING,     /*   char**	      */
  IfmPROP_PATH,	      /*   char**	      */
  IfmPROP_COLOR,      /*   IfmRGBA*	      */
  IfmPROP_ENUM,	      /*   enum...*	      */
  IfmPROP_TIME,	      /*   time_t...*	      */
  IfmPROP_ID,	      /*   char**	      */
} IfmPROP_TYPE;

typedef struct _IfmPropExtInt /* Extension for integer properties */
{
  int minval;
  int maxval;
} IfmPropExtInt;

typedef struct _IfmPropExtDbl /* Extension for float properties */
{
  double minval;
  double maxval;
} IfmPropExtDbl;

typedef struct _IfmPropExtStr /* Extension for string properties */
{
  int maxlen;
} IfmPropExtStr;

typedef struct _IfmPropExtEnum /* Extension for enum properties */
{
  const char* name;
  int	      value;
} IfmPropExtEnum;

typedef struct _IfmPropExtTime /* Extension for time properties */
{
  time_t  tmin;
  time_t  tmax;
} IfmPropExtTime;

typedef struct _IfmPropExtPath
{
  IfmBool     fileOpenDlg;	  /* If true it is a file open, otherwise a file save as dialog */
  char*	      initialDirectory;	  /* Initial directory */
  char*	      defaultExtension;	  /* Extensions of files to be listed */
  char*       filter;		  /* Example: "Text files (*.txt)|*.txt|All files (*.*)|*.*"  */
  int	      currentFilter;	  /* Index of current filter (0=first) */
} IfmPropExtPath;


typedef struct _IfmProperty
{
  const char*	name;	    /* Name of the property (utf-8 encoded) */
  IfmPROP_TYPE	type;	    /* Type of the variable */
  void*		addr;	    /* Address of the variable to edit */
  const void*	def;	    /* Address of the default value for the variable or NULL to disable reset to default */
  const char*	desc;	    /* Description of the property (utf-8 encoded) */
  union {
    const void*	    ext;    /* Any extension */
    IfmPropExtInt*  ext_i;  /* Extension for integer property or NULL */
    IfmPropExtDbl*  ext_d;  /* Extension for double property or NULL */
    IfmPropExtStr*  ext_s;  /* Extension for string properties or NULL */
    IfmPropExtPath* ext_p;  /* Extension for path property or NULL */
    IfmPropExtTime* ext_t;  /* Extension for time property or NULL */
    IfmPropExtEnum* ext_e;  /* Enum values (last entry with name = NULL) */
    const char*     ext_id; /* Extension for values from id lists 
				[*]powid    -> time series (power function) id
				[*]ref_n    -> nodal reference distribution id
				[*]ref_e    -> elemental reference distribution id
				'*' as first character allows to select empty (no) ids, too.
			     */
  };
} IfmProperty;

				/* Flags controlling IfmDrawFemMesh() */
#define IfmMESH_NORMAL	0	/* Normal mesh */
#define IfmMESH_WHITE	(1<<0)	/* Draw mesh lines (bg_white) */
#define IfmMESH_BLACK	(1<<1)	/* Draw mesh lines (BLACK) */
#define IfmMESH_NOFILL	(1<<2)	/* Don't fill mesh interior (grey95) */
#define IfmMESH_NOLINES	(1<<3)	/* Don't draw mesh lines (bg_black) */
#define IfmMESH_NOCLS	(1<<4)	/* Don't clear drawable before drawing */
#define IfmMESH_NOORG	(1<<5)	/* Don't show origin */
#define IfmMESH_NOMARK	(1<<6)	/* Don't show markers */
#define IfmMESH_NOOPT	(1<<7)	/* Don't optimize line drawing */
#define IfmMESH_INVERT	(1<<8)	/* Force xor'd fill and border colors */
#define IfmMESH_QUERY	(1<<9)	/* Return realized world extent */

				/* Flags controlling IfmTransformPoints() */
typedef enum _IfmCoorSystem
{
  IfmCOOR_SCREEN,		/* Screen coordinates depending on main window position */
  IfmCOOR_CLIENT,		/* Client coordinates (local main window coordinates) */
  IfmCOOR_LOCAL,		/* Local real world coordinates (relative to mesh origin) */
  IfmCOOR_GLOBAL,		/* Global real world coordinates (e.g. GK, UTM) */
  IfmCOOR_POLAR			/* Local polar coordinates (relative to mesh origin) */
} IfmCoorSystem;

IFM_FUNCPROTOBEGIN

extern int IfmAlert (IfmHandle, Widget, const char*, const char*, ...);
extern void IfmWarning (IfmHandle, const char*, ...);
extern void IfmMessage (IfmHandle, const char*, ...);
extern void IfmShowProgress (IfmHandle, int);
extern void IfmGetHelp (IfmHandle, Widget, const char*);
extern void IfmAddFallbackResources (IfmHandle, Widget, const char*, const char* const*);
extern XtAppContext IfmGetAppContext (IfmHandle);
extern Widget IfmGetTopLevelWindow (IfmHandle);
extern Widget IfmGetMainWindow (IfmHandle);
extern Widget IfmGetActiveViewWindow (IfmHandle);
extern Pixmap IfmGetBackgroundPixmap (IfmHandle);
extern void*  IfmGetMainHwnd (IfmHandle pMod);	    /* Applicable under WIN32 only! */
extern void*  IfmGetAppInstance (IfmHandle pMod);   /* Applicable under WIN32 only! */

extern void IfmDebug (IfmHandle, int, const char*, ...);
extern void IfmInfo (IfmHandle, const char*, ...);
extern void IfmBell (IfmHandle);
extern void IfmUpdateDisplay (IfmHandle);

extern void IfmAddCallback(
    IfmHandle		/* IFM handle */,
    Widget              /* widget */,
    const char*   	/* callback_name */,
    IfmCallbackProc     /* callback */,
    XtPointer           /* closure */
);

extern void IfmRemoveCallback(
    IfmHandle		/* IFM handle */,
    Widget              /* widget */,
    const char*   	/* callback_name */,
    IfmCallbackProc     /* callback */,
    XtPointer           /* closure */
);

extern void IfmAddEventHandler(
    IfmHandle		/* IFM handle */,
    Widget              /* widget */,
    EventMask           /* event_mask */,
    int          	/* nonmaskable */,
    IfmEventHandler     /* proc */,
    XtPointer           /* closure */
);

extern void IfmRemoveEventHandler(
    IfmHandle		/* IFM handle */,
    Widget              /* widget */,
    EventMask           /* event_mask */,
    int          	/* nonmaskable */,
    IfmEventHandler     /* proc */,
    XtPointer           /* closure */
);

extern IfmWorkProcId IfmAppAddWorkProc(
    IfmHandle		 /* IFM handle */,
    XtAppContext         /* app_context */,
    IfmWorkProc          /* proc */,
    XtPointer            /* closure */
);

extern void  IfmRemoveWorkProc(
    IfmHandle		 /* IFM handle */,
    IfmWorkProcId        /* id */
);

extern IfmIntervalId IfmAppAddTimeOut(
    IfmHandle		 /* IFM handle */,
    XtAppContext         /* app_context */,
    unsigned long        /* interval */,
    IfmTimerCallbackProc /* proc */,
    XtPointer            /* closure */
);

extern void IfmRemoveTimeOut(
    IfmHandle		 /* IFM handle */,
    IfmIntervalId        /* timer */
);

extern IfmInputId IfmAppAddInput(
    IfmHandle		 /* IFM handle */,
    XtAppContext         /* app_context */,
    int                  /* source */,
    XtPointer            /* condition */,
    IfmInputCallbackProc /* proc */,
    XtPointer            /* closure */
);

extern void IfmRemoveInput(
    IfmHandle		 /* IFM handle */,
    IfmInputId           /* id */
);


extern IfmSignalId IfmAppAddSignal(
    IfmHandle		  /* IFM handle */,
    XtAppContext          /* app_context */,
    IfmSignalCallbackProc /* proc */,
    XtPointer             /* closure */
);

extern void IfmRemoveSignal(
    IfmHandle		 /* IFM handle */,
    IfmSignalId          /* id */
);

extern void IfmNoticeSignal(
    IfmHandle		 /* IFM handle */,
    IfmSignalId          /* id */
);

/* X11 Colormap handling */
extern Colormap IfmGetColormap (IfmHandle);
extern Pixel*   IfmGetRainbowPalette (IfmHandle, int*);
extern Visual*  IfmGetVisual (IfmHandle);
unsigned int    IfmGetVisualDepth (IfmHandle);

#if IFM_CURRENT_GRAPHIC_VERSION >= 0x4710
/* Workarounds for not supported private widget classes (WIN32) */
extern WidgetClass IfmGetXbaeMatrixWidgetClass (IfmHandle);
extern WidgetClass IfmGetDtxComboBoxWidgetClass (IfmHandle);
			/* Redraws the current graphics with actual fem problem data */
extern void IfmRedrawDisplay (IfmHandle);
			/* Start the wait cursor */
extern void IfmBeginWaitCursor (IfmHandle, Widget shell);
			/* Return to default cursor */
extern void IfmEndWaitCursor (IfmHandle, Widget shell);
#endif


#if IFM_CURRENT_GRAPHIC_VERSION >= 0x4712
/* File handling */
extern IfmResult IfmLocatePath (IfmHandle, IfmPath* locatePath, IfmBool keepName, Widget parent);
extern IfmResult IfmFileSelection (IfmHandle, IfmPath* path, IfmBool bOpenDialog,
				   IfmFileSelectionInfo* info, Widget parent);
#endif

#if IFM_CURRENT_GRAPHIC_VERSION >= 0x4823
/* XPM Pixmaps */
extern Cursor IfmCreateXpmCursor (IfmHandle, char** xpm);
extern Pixmap IfmCreateXpmPixmap (IfmHandle, Widget w, char** xpm);
extern void   IfmSetXpmPixmap (IfmHandle, Widget w, const char* res, char** xpm);
/* Editor */
extern Widget IfmCreateEditor (IfmHandle, Widget w, const char* name, Arg* args, int n);
#endif

#if IFM_CURRENT_GRAPHIC_VERSION >= 0x5050
/* Mesh drawing  */
extern void IfmDrawFemMesh(IfmHandle, Widget w, Pixmap pix, IfmRect* rectExt, 
			   const IfmRect* rectVpt, double ratio, int nFlags);

/* Diagrams (v 5.050) (see diagram.h) */
/*
extern IfmDiagram IfmDiagramCreate (IfmHandle handle, Widget parent, const char* title);
extern IfmCurve   IfmCurveCreate (IfmHandle handle, const char* name, int points);
*/
/* Motif Development Kit */
extern IfmResult IfmInitMotif(IfmHandle pMod);
#endif

#if IFM_CURRENT_GRAPHIC_VERSION >= 0x5059
/* Work view access */
extern void	IfmGetViewExtent (IfmHandle pMod, double* xmin, double* ymin, double* xmax, double* ymax);
extern IfmBool	IfmSetViewExtent (IfmHandle pMod, double xmin, double ymin, double xmax, double ymax);
extern int	IfmTransformPoints (IfmHandle pMod, IfmPoint* points, int nPoints, 
				    IfmCoorSystem nSourceCS, IfmCoorSystem nTargetCS);
extern int	IfmTransformCoords (IfmHandle pMod, double* x, double* y, int nPoints, 
				    IfmCoorSystem nSourceCS, IfmCoorSystem nTargetCS);
extern void	IfmInvalidateViewRect (IfmHandle pMod, int xmin, int ymin, 
				       int xmax, int ymax);
extern void	IfmRedrawView (IfmHandle pMod);
#endif

/* Color allocation */
extern Pixel	IfmAllocRGBColor (IfmHandle pMod, int red, int green, int blue);
extern Pixel	IfmAllocNamedColor (IfmHandle pMod, const char* colorname);
extern void	IfmFreeColor (IfmHandle pMod, Pixel pixel);
extern void	IfmQueryColor (IfmHandle pMod, Pixel pixel, int* red, int* green, int* blue);

#if IFM_CURRENT_GRAPHIC_VERSION >= 0x6154
extern IfmBool	IfmEditProperties (IfmHandle pMod, const char* caption, const char* header, IfmProperty* prop_list, int num_prop);
#endif

IFM_FUNCPROTOEND

/* For compatibility */
#define IfmGraphicAlert		IfmAlert
#define IfmGraphicWarning	IfmWarning
#define IfmGraphicMessage	IfmMessage
#define IfmGraphicHelp		IfmGetHelp
#define IfmGraphicProgress	IfmShowProgress

#endif /* IFM_GRAPHIC_H */

