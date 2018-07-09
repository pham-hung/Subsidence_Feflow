#ifndef IFM_XDKP_H
#define IFM_XDKP_H

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

#include "xdk.h"
#include "modulep.h"

#include <Xm/Xm.h>
#include <Xm/ArrowB.h>
#include <Xm/ArrowBG.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <Xm/CascadeBG.h>
#include <Xm/Command.h>
#include <Xm/DialogS.h>
#include <Xm/DragC.h>
#include <Xm/DragIcon.h>
#include <Xm/DragOverS.h>
#include <Xm/DrawingA.h>
#include <Xm/DrawnB.h>
#include <Xm/DropSMgr.h>
#include <Xm/DropTrans.h>
#include <Xm/FileSB.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/List.h>
#include <Xm/MainW.h>
#include <Xm/MenuShell.h>
#include <Xm/MessageB.h>
#include <Xm/PanedW.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/Scale.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrolledW.h>
#include <Xm/SelectioB.h>
#include <Xm/SeparatoG.h>
#include <Xm/Separator.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <Xm/VendorS.h>
#include <Xm/CutPaste.h>
#include <Xm/AtomMgr.h>
#include <Xm/Protocols.h>
#include <Xm/DropSMgr.h>
#include <Xm/Screen.h>

#if XmVersion >= 2000
#include <Xm/Notebook.h>
#include <Xm/Print.h>
#include <Xm/SSpinB.h>
#include <Xm/ComboBox.h>
#include <Xm/Gadget.h>
#include <Xm/GrabShell.h>
#include <Xm/Manager.h>
#include <Xm/Primitive.h>
#include <Xm/SpinB.h>
#endif

#include <X11/Intrinsic.h>
#include <X11/Composite.h>
#include <X11/Constraint.h>
#include <X11/Core.h>
#include <X11/Object.h>
#include <X11/RectObj.h>
#include <X11/Shell.h>
#include <X11/Vendor.h>

#include <Dtx/ComboBox.h>
#include <Xbae/Matrix.h>
#include <Xbae/Clip.h>

/* This ID must be unique across all IFM subsystems 
   (use regex 'IFM_.*_ID[	 ]*[0-9]' to verify) */
#define IFM_X11_ID		9
#define IFM_XT_ID		10
#define IFM_XM_ID		11

#if NeedWidePrototypes
#define _IfmBoolean int
#define _IfmPosition int
#define _IfmDimension unsigned int
#define _IfmEnum unsigned int
#define _IfmStringDirection int
#else
#define _IfmBoolean Boolean
#define _IfmPosition short
#define _IfmDimension unsigned short
#define _IfmEnum unsigned char
#define _IfmStringDirection unsigned char
#endif

typedef Bool (*XrmEnumerateCallback)(XrmDatabase* db, XrmBindingList bindings, XrmQuarkList quarks, XrmRepresentation* type, XrmValue* value, XPointer closure);

typedef struct {
    String	name;	/* resource name */
    String	type;	/* representation type name */
    XtArgVal	value;	/* representation */
    int		size;	/* size of representation */
} IfmTypedArg;


  /* X11 lib methods */
struct IfmX11Methods
{
  /* Version 0x5050 */
  XFontStruct *(*xLoadQueryFont)(Display* display,_Xconst char* name);
  XFontStruct *(*xQueryFont)(Display* display,XID font_ID);
  XTimeCoord *(*xGetMotionEvents)(Display* display,Window w,Time start,Time stop,int* nevents_return);
  XModifierKeymap *(*xDeleteModifiermapEntry)(XModifierKeymap* modmap, _XtKeyCode keycode_entry,int modifier);
  XModifierKeymap *(*xGetModifierMapping)(Display* display);
  XModifierKeymap *(*xInsertModifiermapEntry)(XModifierKeymap* modmap, _XtKeyCode keycode_entry,int modifier);
  XModifierKeymap *(*xNewModifiermap)(int max_keys_per_mod);
  XImage *(*xCreateImage)(Display* display,Visual* visual,unsigned int depth,int format,int offset,char* data,unsigned int width,unsigned int height,int bitmap_pad,int bytes_per_line);
  Status (*xInitImage)(XImage* image);
  XImage *(*xGetImage)(Display* display,Drawable d,int x,int y,unsigned int width,unsigned int height,unsigned long plane_mask,int format);
  XImage *(*xGetSubImage)(Display* display,Drawable d,int x,int y,unsigned int width,unsigned int height,unsigned long plane_mask,int format,XImage* dest_image,int dest_x,int dest_y);
  char *(*xFetchBytes)(Display* display,int* nbytes_return);
  char *(*xFetchBuffer)(Display* display,int* nbytes_return,int buffer);
  char *(*xGetAtomName)(Display* display,Atom atom);
  Status (*xGetAtomNames)(Display* dpy,Atom* atoms,int count,char** names_return);
  char *(*xGetDefault)(Display* display,_Xconst char* program,_Xconst char* option);
  char *(*xDisplayName)(_Xconst char* string);
  char *(*xKeysymToString)(KeySym keysym);
  Atom (*xInternAtom)(Display* display,_Xconst char* atom_name,Bool only_if_exists);
  Status (*xInternAtoms)(Display* dpy,char** names,int count,Bool onlyIfExists,Atom* atoms_return);
  Colormap (*xCopyColormapAndFree)(Display* display,Colormap colormap);
  Colormap (*xCreateColormap)(Display* display,Window w,Visual* visual,int alloc);
  Cursor (*xCreatePixmapCursor)(Display* display,Pixmap source,Pixmap mask,XColor* foreground_color,XColor* background_color,unsigned int x,unsigned int y);
  Cursor (*xCreateGlyphCursor)(Display* display,Font source_font,Font mask_font,unsigned int source_char,unsigned int mask_char,XColor* foreground_color,XColor* background_color);
  Cursor (*xCreateFontCursor)(Display* display,unsigned int shape);
  Font (*xLoadFont)(Display* display,_Xconst char* name);
  GC (*xCreateGC)(Display* display,Drawable d,unsigned long valuemask,XGCValues* values);
  GContext (*xGContextFromGC)(GC gc);
  void (*xFlushGC)(Display* display,GC gc);
  Pixmap (*xCreatePixmap)(Display* display,Drawable d,unsigned int width,unsigned int height,unsigned int depth);
  Pixmap (*xCreateBitmapFromData)(Display* display,Drawable d,_Xconst char* data,unsigned int width,unsigned int height);
  Pixmap (*xCreatePixmapFromBitmapData)(Display* display,Drawable d,char* data,unsigned int width,unsigned int height,unsigned long fg,unsigned long bg,unsigned int depth);
  Window (*xCreateSimpleWindow)(Display* display,Window parent,int x,int y,unsigned int width,unsigned int height,unsigned int border_width,unsigned long border,unsigned long background);
  Window (*xGetSelectionOwner)(Display* display,Atom selection);
  Window (*xCreateWindow)(Display* display,Window parent,int x,int y,unsigned int width,unsigned int height,unsigned int border_width,int depth,unsigned int vclass,Visual* visual,unsigned long valuemask,XSetWindowAttributes* attributes);
  Colormap *(*xListInstalledColormaps)(Display* display,Window w,int* num_return);
  char **(*xListFonts)(Display* display,_Xconst char* pattern,int maxnames,int* actual_count_return);
  char **(*xListFontsWithInfo)(Display* display,_Xconst char* pattern,int maxnames,int* count_return,XFontStruct** info_return);
  char **(*xGetFontPath)(Display* display,int* npaths_return);
  char **(*xListExtensions)(Display* display,int* nextensions_return);
  Atom *(*xListProperties)(Display* display,Window w,int* num_prop_return);
  XHostAddress *(*xListHosts)(Display* display,int* nhosts_return,Bool* state_return);
  KeySym (*xKeycodeToKeysym)(Display* display, _XtKeyCode keycode,int index);
  KeySym (*xLookupKeysym)(XKeyEvent* key_event,int index);
  KeySym *(*xGetKeyboardMapping)(Display* display,_XtKeyCode first_keycode,int keycode_count,int* keysyms_per_keycode_return);
  KeySym (*xStringToKeysym)(_Xconst char* string);
  long (*xMaxRequestSize)(Display* display);
  long (*xExtendedMaxRequestSize)(Display* display);
  char *(*xResourceManagerString)(Display* display);
  char *(*xScreenResourceString)(Screen* screen);
  unsigned long (*xDisplayMotionBufferSize)(Display* display);
  VisualID (*xVisualIDFromVisual)(Visual* visual);
  Status (*xInitThreads)(void);
  void (*xLockDisplay)(Display* display);
  void (*xUnlockDisplay)(Display* display);
  XExtCodes *(*xInitExtension)(Display* display,_Xconst char* name);
  XExtCodes *(*xAddExtension)(Display* display);
  XExtData *(*xFindOnExtensionList)(XExtData** structure,int number);
  XExtData **(*xEHeadOfExtensionList)(XEDataObject object);
  Window (*xRootWindow)(Display* display,int screen_number);
  Window (*xDefaultRootWindow)(Display* display);
  Window (*xRootWindowOfScreen)(Screen* screen);
  Visual *(*xDefaultVisual)(Display* display,int screen_number);
  Visual *(*xDefaultVisualOfScreen)(Screen* screen);
  GC (*xDefaultGC)(Display* display,int screen_number);
  GC (*xDefaultGCOfScreen)(Screen* screen);
  unsigned long (*xBlackPixel)(Display* display,int screen_number);
  unsigned long (*xWhitePixel)(Display* display,int screen_number);
  unsigned long (*xAllPlanes)(void);
  unsigned long (*xBlackPixelOfScreen)(Screen* screen);
  unsigned long (*xWhitePixelOfScreen)(Screen* screen);
  unsigned long (*xNextRequest)(Display* display);
  unsigned long (*xLastKnownRequestProcessed)(Display* display);
  char *(*xServerVendor)(Display* display);
  char *(*xDisplayString)(Display* display);
  Colormap (*xDefaultColormap)(Display* display,int screen_number);
  Colormap (*xDefaultColormapOfScreen)(Screen* screen);
  Display *(*xDisplayOfScreen)(Screen* screen);
  Screen *(*xScreenOfDisplay)(Display* display,int screen_number);
  Screen *(*xDefaultScreenOfDisplay)(Display* display);
  long (*xEventMaskOfScreen)(Screen* screen);
  int (*xScreenNumberOfScreen)(Screen* screen);
  XPixmapFormatValues *(*xListPixmapFormats)(Display* display,int* count_return);
  int *(*xListDepths)(Display* display,int screen_number,int* count_return);
  Status (*xReconfigureWMWindow)(Display* display,Window w,int screen_number,unsigned int mask,XWindowChanges* changes);
  Status (*xGetWMProtocols)(Display* display,Window w,Atom** protocols_return,int* count_return);
  Status (*xSetWMProtocols)(Display* display,Window w,Atom* protocols,int count);
  Status (*xIconifyWindow)(Display* display,Window w,int screen_number);
  Status (*xWithdrawWindow)(Display* display,Window w,int screen_number);
  Status (*xGetCommand)(Display* display,Window w,char*** argv_return,int* argc_return);
  Status (*xGetWMColormapWindows)(Display* display,Window w,Window** windows_return,int* count_return);
  Status (*xSetWMColormapWindows)(Display* display,Window w,Window* colormap_windows,int count);
  void (*xFreeStringList)(char** list);
  int (*xSetTransientForHint)(Display* display,Window w,Window prop_window);
  int (*xActivateScreenSaver)(Display* display);
  int (*xAddHost)(Display* display,XHostAddress* host);
  int (*xAddHosts)(Display* display,XHostAddress* hosts,int num_hosts);
  int (*xAddToExtensionList)(struct _XExtData** structure,XExtData* ext_data);
  int (*xAddToSaveSet)(Display* display,Window w);
  Status (*xAllocColor)(Display* display,Colormap colormap,XColor* screen_in_out);
  Status (*xAllocColorCells)(Display* display,Colormap colormap,Bool contig,unsigned long* plane_masks_return,unsigned int nplanes,unsigned long* pixels_return,unsigned int npixels);
  Status (*xAllocColorPlanes)(Display* display,Colormap colormap,Bool contig,unsigned long* pixels_return,int ncolors,int nreds,int ngreens,int nblues,unsigned long* rmask_return,unsigned long* gmask_return,unsigned long* bmask_return);
  Status (*xAllocNamedColor)(Display* display,Colormap colormap,_Xconst char* color_name,XColor* screen_def_return,XColor* exact_def_return);
  int (*xAllowEvents)(Display* display,int event_mode,Time time);
  int (*xAutoRepeatOff)(Display* display);
  int (*xAutoRepeatOn)(Display* display);
  int (*xBell)(Display* display,int percent);
  int (*xBitmapBitOrder)(Display* display);
  int (*xBitmapPad)(Display* display);
  int (*xBitmapUnit)(Display* display);
  int (*xCellsOfScreen)(Screen* screen);
  int (*xChangeActivePointerGrab)(Display* display,unsigned int event_mask,Cursor cursor,Time time);
  int (*xChangeGC)(Display* display,GC gc,unsigned long valuemask,XGCValues* values);
  int (*xChangeKeyboardControl)(Display* display,unsigned long value_mask,XKeyboardControl* values);
  int (*xChangeKeyboardMapping)(Display* display,int first_keycode,int keysyms_per_keycode,KeySym* keysyms,int num_codes);
  int (*xChangePointerControl)(Display* display,Bool do_accel,Bool do_threshold,int accel_numerator,int accel_denominator,int threshold);
  int (*xChangeProperty)(Display* display,Window w,Atom property,Atom type,int format,int mode,_Xconst unsigned char* data,int nelements);
  int (*xChangeSaveSet)(Display* display,Window w,int change_mode);
  int (*xChangeWindowAttributes)(Display* display,Window w,unsigned long valuemask,XSetWindowAttributes* attributes);
  Bool (*xCheckMaskEvent)(Display* display,long event_mask,XEvent* event_return);
  Bool (*xCheckTypedEvent)(Display* display,int event_type,XEvent* event_return);
  Bool (*xCheckTypedWindowEvent)(Display* display,Window w,int event_type,XEvent* event_return);
  Bool (*xCheckWindowEvent)(Display* display,Window w,long event_mask,XEvent* event_return);
  int (*xCirculateSubwindows)(Display* display,Window w,int direction);
  int (*xCirculateSubwindowsDown)(Display* display,Window w);
  int (*xCirculateSubwindowsUp)(Display* display,Window w);
  int (*xClearArea)(Display* display,Window w,int x,int y,unsigned int width,unsigned int height,Bool exposures);
  int (*xClearWindow)(Display* display,Window w);
  int (*xCloseDisplay)(Display* display);
  int (*xConfigureWindow)(Display* display,Window w,unsigned int value_mask,XWindowChanges* values);
  int (*xConnectionNumber)(Display* display);
  int (*xConvertSelection)(Display* display,Atom selection,Atom target,Atom property,Window requestor,Time time);
  int (*xCopyArea)(Display* display,Drawable src,Drawable dest,GC gc,int src_x,int src_y,unsigned int width,unsigned int height,int dest_x,int dest_y);
  int (*xCopyGC)(Display* display,GC src,unsigned long valuemask,GC dest);
  int (*xCopyPlane)(Display* display,Drawable src,Drawable dest,GC gc,int src_x,int src_y,unsigned int width,unsigned int height,int dest_x,int dest_y,unsigned long plane);
  int (*xDefaultDepth)(Display* display,int screen_number);
  int (*xDefaultDepthOfScreen)(Screen* screen);
  int (*xDefaultScreen)(Display* display);
  int (*xDefineCursor)(Display* display,Window w,Cursor cursor);
  int (*xDeleteProperty)(Display* display,Window w,Atom property);
  int (*xDestroyWindow)(Display* display,Window w);
  int (*xDestroySubwindows)(Display* display,Window w);
  int (*xDoesBackingStore)(Screen* screen);
  Bool (*xDoesSaveUnders)(Screen* screen);
  int (*xDisableAccessControl)(Display* display);
  int (*xDisplayCells)(Display* display,int screen_number);
  int (*xDisplayHeight)(Display* display,int screen_number);
  int (*xDisplayHeightMM)(Display* display,int screen_number);
  int (*xDisplayKeycodes)(Display* display,int* min_keycodes_return,int* max_keycodes_return);
  int (*xDisplayPlanes)(Display* display,int screen_number);
  int (*xDisplayWidth)(Display* display,int screen_number);
  int (*xDisplayWidthMM)(Display* display,int screen_number);
  int (*xDrawArc)(Display* display,Drawable d,GC gc,int x,int y,unsigned int width,unsigned int height,int angle1,int angle2);
  int (*xDrawArcs)(Display* display,Drawable d,GC gc,XArc* arcs,int narcs);
  int (*xDrawImageString)(Display* display,Drawable d,GC gc,int x,int y,_Xconst char* string,int length);
  int (*xDrawImageString16)(Display* display,Drawable d,GC gc,int x,int y,_Xconst XChar2b* string,int length);
  int (*xDrawLine)(Display* display,Drawable d,GC gc,int x1,int x2,int y1,int y2);
  int (*xDrawLines)(Display* display,Drawable d,GC gc,XPoint* points,int npoints,int mode);
  int (*xDrawPoint)(Display* display,Drawable d,GC gc,int x,int y);
  int (*xDrawPoints)(Display* display,Drawable d,GC gc,XPoint* points,int npoints,int mode);
  int (*xDrawRectangle)(Display* display,Drawable d,GC gc,int x,int y,unsigned int width,unsigned int height);
  int (*xDrawRectangles)(Display* display,Drawable d,GC gc,XRectangle* rectangles,int nrectangles);
  int (*xDrawSegments)(Display* display,Drawable d,GC gc,XSegment* segments,int nsegments);
  int (*xDrawString)(Display* display,Drawable d,GC gc,int x,int y,_Xconst char* string,int length);
  int (*xDrawString16)(Display* display,Drawable d,GC gc,int x,int y,_Xconst XChar2b* string,int length);
  int (*xDrawText)(Display* display,Drawable d,GC gc,int x,int y,XTextItem* items,int nitems);
  int (*xDrawText16)(Display* display,Drawable d,GC gc,int x,int y,XTextItem16* items,int nitems);
  int (*xEnableAccessControl)(Display* display);
  int (*xEventsQueued)(Display* display,int mode);
  Status (*xFetchName)(Display* display,Window w,char** window_name_return);
  int (*xFillArc)(Display* display,Drawable d,GC gc,int x,int y,unsigned int width,unsigned int height,int angle1,int angle2);
  int (*xFillArcs)(Display* display,Drawable d,GC gc,XArc* arcs,int narcs);
  int (*xFillPolygon)(Display* display,Drawable d,GC gc,XPoint* points,int npoints,int shape,int mode);
  int (*xFillRectangle)(Display* display,Drawable d,GC gc,int x,int y,unsigned int width,unsigned int height);
  int (*xFillRectangles)(Display* display,Drawable d,GC gc,XRectangle* rectangles,int nrectangles);
  int (*xFlush)(Display* display);
  int (*xForceScreenSaver)(Display* display,int mode);
  int (*xFree)(void* data);
  int (*xFreeColormap)(Display* display,Colormap colormap);
  int (*xFreeColors)(Display* display,Colormap colormap,unsigned long* pixels,int npixels,unsigned long planes);
  int (*xFreeCursor)(Display* display,Cursor cursor);
  int (*xFreeExtensionList)(char** list);
  int (*xFreeFont)(Display* display,XFontStruct* font_struct);
  int (*xFreeFontInfo)(char** names,XFontStruct* free_info,int actual_count);
  int (*xFreeFontNames)(char** list);
  int (*xFreeFontPath)(char** list);
  int (*xFreeGC)(Display* display,GC gc);
  int (*xFreeModifiermap)(XModifierKeymap* modmap);
  int (*xFreePixmap)(Display* display,Pixmap pixmap);
  int (*xGeometry)(Display* display,int screen,_Xconst char* position,_Xconst char* default_position,unsigned int bwidth,unsigned int fwidth,unsigned int fheight,int xadder,int yadder,int* x_return,int* y_return,int* width_return,int* height_return);
  int (*xGetErrorDatabaseText)(Display* display,_Xconst char* name,_Xconst char* message,_Xconst char* default_string,char* buffer_return,int length);
  int (*xGetErrorText)(Display* display,int code,char* buffer_return,int length);
  Bool (*xGetFontProperty)(XFontStruct* font_struct,Atom atom,unsigned long* value_return);
  Status (*xGetGCValues)(Display* display,GC gc,unsigned long valuemask,XGCValues* values_return);
  Status (*xGetGeometry)(Display* display,Drawable d,Window* root_return,int* x_return,int* y_return,unsigned int* width_return,unsigned int* height_return,unsigned int* border_width_return,unsigned int* depth_return);
  Status (*xGetIconName)(Display* display,Window w,char** icon_name_return);
  int (*xGetInputFocus)(Display* display,Window* focus_return,int* revert_to_return);
  int (*xGetKeyboardControl)(Display* display,XKeyboardState* values_return);
  int (*xGetPointerControl)(Display* display,int* accel_numerator_return,int* accel_denominator_return,int* threshold_return);
  int (*xGetPointerMapping)(Display* display,unsigned char* map_return,int nmap);
  int (*xGetScreenSaver)(Display* display,int* timeout_return,int* interval_return,int* prefer_blanking_return,int* allow_exposures_return);
  Status (*xGetTransientForHint)(Display* display,Window w,Window* prop_window_return);
  int (*xGetWindowProperty)(Display* display,Window w,Atom property,long long_offset,long long_length,Bool _delete,Atom req_type,Atom* actual_type_return,int* actual_format_return,unsigned long* nitems_return,unsigned long* bytes_after_return,unsigned char** prop_return);
  Status (*xGetWindowAttributes)(Display* display,Window w,XWindowAttributes* window_attributes_return);
  int (*xGrabButton)(Display* display,unsigned int button,unsigned int modifiers,Window grab_window,Bool owner_events,unsigned int event_mask,int pointer_mode,int keyboard_mode,Window confine_to,Cursor cursor);
  int (*xGrabKey)(Display* display,int keycode,unsigned int modifiers,Window grab_window,Bool owner_events,int pointer_mode,int keyboard_mode);
  int (*xGrabKeyboard)(Display* display,Window grab_window,Bool owner_events,int pointer_mode,int keyboard_mode,Time time);
  int (*xGrabPointer)(Display* display,Window grab_window,Bool owner_events,unsigned int event_mask,int pointer_mode,int keyboard_mode,Window confine_to,Cursor cursor,Time time);
  int (*xGrabServer)(Display* display);
  int (*xHeightMMOfScreen)(Screen* screen);
  int (*xHeightOfScreen)(Screen* screen);
  int (*xImageByteOrder)(Display* display);
  int (*xInstallColormap)(Display* display,Colormap colormap);
  KeyCode (*xKeysymToKeycode)(Display* display,KeySym keysym);
  int (*xKillClient)(Display* display,XID resource);
  Status (*xLookupColor)(Display* display,Colormap colormap,_Xconst char* color_name,XColor* exact_def_return,XColor* screen_def_return);
  int (*xLowerWindow)(Display* display,Window w);
  int (*xMapRaised)(Display* display,Window w);
  int (*xMapSubwindows)(Display* display,Window w);
  int (*xMapWindow)(Display* display,Window w);
  int (*xMaskEvent)(Display* display,long event_mask,XEvent* event_return);
  int (*xMaxCmapsOfScreen)(Screen* screen);
  int (*xMinCmapsOfScreen)(Screen* screen);
  int (*xMoveResizeWindow)(Display* display,Window w,int x,int y,unsigned int width,unsigned int height);
  int (*xMoveWindow)(Display* display,Window w,int x,int y);
  int (*xNextEvent)(Display* display,XEvent* event_return);
  int (*xNoOp)(Display* display);
  Status (*xParseColor)(Display* display,Colormap colormap,_Xconst char* spec,XColor* exact_def_return);
  int (*xParseGeometry)(_Xconst char* parsestring,int* x_return,int* y_return,unsigned int* width_return,unsigned int* height_return);
  int (*xPeekEvent)(Display* display,XEvent* event_return);
  int (*xPending)(Display* display);
  int (*xPlanesOfScreen)(Screen* screen);
  int (*xProtocolRevision)(Display* display);
  int (*xProtocolVersion)(Display* display);
  int (*xPutBackEvent)(Display* display,XEvent* event);
  int (*xPutImage)(Display* display,Drawable d,GC gc,XImage* image,int src_x,int src_y,int dest_x,int dest_y,unsigned int width,unsigned int height);
  int (*xQLength)(Display* display);
  Status (*xQueryBestCursor)(Display* display,Drawable d,unsigned int width,unsigned int height,unsigned int* width_return,unsigned int* height_return);
  Status (*xQueryBestSize)(Display* display,int vclass,Drawable which_screen,unsigned int width,unsigned int height,unsigned int* width_return,unsigned int* height_return);
  Status (*xQueryBestStipple)(Display* display,Drawable which_screen,unsigned int width,unsigned int height,unsigned int* width_return,unsigned int* height_return);
  Status (*xQueryBestTile)(Display* display,Drawable which_screen,unsigned int width,unsigned int height,unsigned int* width_return,unsigned int* height_return);
  int (*xQueryColor)(Display* display,Colormap colormap,XColor* def_in_out);
  int (*xQueryColors)(Display* display,Colormap colormap,XColor* defs_in_out,int ncolors);
  Bool (*xQueryExtension)(Display* display,_Xconst char* name,int* major_opcode_return,int* first_event_return,int* first_error_return);
  int (*xQueryKeymap)(Display* display,char keys_return[32]);
  Bool (*xQueryPointer)(Display* display,Window w,Window* root_return,Window* child_return,int* root_x_return,int* root_y_return,int* win_x_return,int* win_y_return,unsigned int* mask_return);
  int (*xQueryTextExtents)(Display* display,XID font_ID,_Xconst char* string,int nchars,int* direction_return,int* font_ascent_return,int* font_descent_return,XCharStruct* overall_return);
  int (*xQueryTextExtents16)(Display* display,XID font_ID,_Xconst XChar2b* string,int nchars,int* direction_return,int* font_ascent_return,int* font_descent_return,XCharStruct* overall_return);
  Status (*xQueryTree)(Display* display,Window w,Window* root_return,Window* parent_return,Window** children_return,unsigned int* nchildren_return);
  int (*xRaiseWindow)(Display* display,Window w);
  int (*xReadBitmapFile)(Display* display,Drawable d,_Xconst char* filename,unsigned int* width_return,unsigned int* height_return,Pixmap* bitmap_return,int* x_hot_return,int* y_hot_return);
  int (*xReadBitmapFileData)(_Xconst char* filename,unsigned int* width_return,unsigned int* height_return,unsigned char** data_return,int* x_hot_return,int* y_hot_return);
  int (*xRebindKeysym)(Display* display,KeySym keysym,KeySym* list,int mod_count,_Xconst unsigned char* string,int bytes_string);
  int (*xRecolorCursor)(Display* display,Cursor cursor,XColor* foreground_color,XColor* background_color);
  int (*xRefreshKeyboardMapping)(XMappingEvent* event_map);
  int (*xRemoveFromSaveSet)(Display* display,Window w);
  int (*xRemoveHost)(Display* display,XHostAddress* host);
  int (*xRemoveHosts)(Display* display,XHostAddress* hosts,int num_hosts);
  int (*xReparentWindow)(Display* display,Window w,Window parent,int x,int y);
  int (*xResetScreenSaver)(Display* display);
  int (*xResizeWindow)(Display* display,Window w,unsigned int width,unsigned int height);
  int (*xRestackWindows)(Display* display,Window* windows,int nwindows);
  int (*xRotateBuffers)(Display* display,int rotate);
  int (*xRotateWindowProperties)(Display* display,Window w,Atom* properties,int num_prop,int npositions);
  int (*xScreenCount)(Display* display);
  int (*xSelectInput)(Display* display,Window w,long event_mask);
  Status (*xSendEvent)(Display* display,Window w,Bool propagate,long event_mask,XEvent* event_send);
  int (*xSetAccessControl)(Display* display,int mode);
  int (*xSetArcMode)(Display* display,GC gc,int arc_mode);
  int (*xSetBackground)(Display* display,GC gc,unsigned long background);
  int (*xSetClipMask)(Display* display,GC gc,Pixmap pixmap);
  int (*xSetClipOrigin)(Display* display,GC gc,int clip_x_origin,int clip_y_origin);
  int (*xSetClipRectangles)(Display* display,GC gc,int clip_x_origin,int clip_y_origin,XRectangle* rectangles,int n,int ordering);
  int (*xSetCloseDownMode)(Display* display,int close_mode);
  int (*xSetCommand)(Display* display,Window w,char** argv,int argc);
  int (*xSetDashes)(Display* display,GC gc,int dash_offset,_Xconst char* dash_list,int n);
  int (*xSetFillRule)(Display* display,GC gc,int fill_rule);
  int (*xSetFillStyle)(Display* display,GC gc,int fill_style);
  int (*xSetFont)(Display* display,GC gc,Font font);
  int (*xSetFontPath)(Display* display,char** directories,int ndirs);
  int (*xSetForeground)(Display* display,GC gc,unsigned long foreground);
  int (*xSetFunction)(Display* display,GC gc,int function);
  int (*xSetGraphicsExposures)(Display* display,GC gc,Bool graphics_exposures);
  int (*xSetIconName)(Display* display,Window w,_Xconst char* icon_name);
  int (*xSetInputFocus)(Display* display,Window focus,int revert_to,Time time);
  int (*xSetLineAttributes)(Display* display,GC gc,unsigned int line_width,int line_style,int cap_style,int join_style);
  int (*xSetModifierMapping)(Display* display,XModifierKeymap* modmap);
  int (*xSetPlaneMask)(Display* display,GC gc,unsigned long plane_mask);
  int (*xSetPointerMapping)(Display* display,_Xconst unsigned char* map,int nmap);
  int (*xSetScreenSaver)(Display* display,int timeout,int interval,int prefer_blanking,int allow_exposures);
  int (*xSetSelectionOwner)(Display* display,Atom selection,Window owner,Time time);
  int (*xSetState)(Display* display,GC gc,unsigned long foreground,unsigned long background,int function,unsigned long plane_mask);
  int (*xSetStipple)(Display* display,GC gc,Pixmap stipple);
  int (*xSetSubwindowMode)(Display* display,GC gc,int subwindow_mode);
  int (*xSetTSOrigin)(Display* display,GC gc,int ts_x_origin,int ts_y_origin);
  int (*xSetTile)(Display* display,GC gc,Pixmap tile);
  int (*xSetWindowBackground)(Display* display,Window w,unsigned long background_pixel);
  int (*xSetWindowBackgroundPixmap)(Display* display,Window w,Pixmap background_pixmap);
  int (*xSetWindowBorder)(Display* display,Window w,unsigned long border_pixel);
  int (*xSetWindowBorderPixmap)(Display* display,Window w,Pixmap border_pixmap);
  int (*xSetWindowBorderWidth)(Display* display,Window w,unsigned int width);
  int (*xSetWindowColormap)(Display* display,Window w,Colormap colormap);
  int (*xStoreBuffer)(Display* display,_Xconst char* bytes,int nbytes,int buffer);
  int (*xStoreBytes)(Display* display,_Xconst char* bytes,int nbytes);
  int (*xStoreColor)(Display* display,Colormap colormap,XColor* color);
  int (*xStoreColors)(Display* display,Colormap colormap,XColor* color,int ncolors);
  int (*xStoreName)(Display* display,Window w,_Xconst char* window_name);
  int (*xStoreNamedColor)(Display* display,Colormap colormap,_Xconst char* color,unsigned long pixel,int flags);
  int (*xSync)(Display* display,Bool discard);
  int (*xTextExtents)(XFontStruct* font_struct,_Xconst char* string,int nchars,int* direction_return,int* font_ascent_return,int* font_descent_return,XCharStruct* overall_return);
  int (*xTextExtents16)(XFontStruct* font_struct,_Xconst XChar2b* string,int nchars,int* direction_return,int* font_ascent_return,int* font_descent_return,XCharStruct* overall_return);
  int (*xTextWidth)(XFontStruct* font_struct,_Xconst char* string,int count);
  int (*xTextWidth16)(XFontStruct* font_struct,_Xconst XChar2b* string,int count);
  Bool (*xTranslateCoordinates)(Display* display,Window src_w,Window dest_w,int src_x,int src_y,int* dest_x_return,int* dest_y_return,Window* child_return);
  int (*xUndefineCursor)(Display* display,Window w);
  int (*xUngrabButton)(Display* display,unsigned int button,unsigned int modifiers,Window grab_window);
  int (*xUngrabKey)(Display* display,int keycode,unsigned int modifiers,Window grab_window);
  int (*xUngrabKeyboard)(Display* display,Time time);
  int (*xUngrabPointer)(Display* display,Time time);
  int (*xUngrabServer)(Display* display);
  int (*xUninstallColormap)(Display* display,Colormap colormap);
  int (*xUnloadFont)(Display* display,Font font);
  int (*xUnmapSubwindows)(Display* display,Window w);
  int (*xUnmapWindow)(Display* display,Window w);
  int (*xVendorRelease)(Display* display);
  int (*xWarpPointer)(Display* display,Window src_w,Window dest_w,int src_x,int src_y,unsigned int src_width,unsigned int src_height,int dest_x,int dest_y);
  int (*xWidthMMOfScreen)(Screen* screen);
  int (*xWidthOfScreen)(Screen* screen);
  int (*xWindowEvent)(Display* display,Window w,long event_mask,XEvent* event_return);
  int (*xWriteBitmapFile)(Display* display,_Xconst char* filename,Pixmap bitmap,unsigned int width,unsigned int height,int x_hot,int y_hot);
  Bool (*xSupportsLocale)(void);
  char *(*xSetLocaleModifiers)(_Xconst char* modifier_list);
  XFontSet (*xCreateFontSet)(Display* display,_Xconst char* base_font_name_list,char*** missing_charset_list,int* missing_charset_count,char** def_string);
  void (*xFreeFontSet)(Display* display,XFontSet font_set);
  int (*xFontsOfFontSet)(XFontSet font_set,XFontStruct*** font_struct_list,char*** font_name_list);
  char *(*xBaseFontNameListOfFontSet)(XFontSet font_set);
  char *(*xLocaleOfFontSet)(XFontSet font_set);
  Bool (*xContextDependentDrawing)(XFontSet font_set);
  Bool (*xDirectionalDependentDrawing)(XFontSet font_set);
  Bool (*xContextualDrawing)(XFontSet font_set);
  XFontSetExtents *(*xExtentsOfFontSet)(XFontSet font_set);
  int (*xmbTextEscapement)(XFontSet font_set,_Xconst char* text,int bytes_text);
  int (*xwcTextEscapement)(XFontSet font_set,_Xconst wchar_t* text,int num_wchars);
  int (*xmbTextExtents)(XFontSet font_set,_Xconst char* text,int bytes_text,XRectangle* overall_ink_return,XRectangle* overall_logical_return);
  int (*xwcTextExtents)(XFontSet font_set,_Xconst wchar_t* text,int num_wchars,XRectangle* overall_ink_return,XRectangle* overall_logical_return);
  Status (*xmbTextPerCharExtents)(XFontSet font_set,_Xconst char* text,int bytes_text,XRectangle* ink_extents_buffer,XRectangle* logical_extents_buffer,int buffer_size,int* num_chars,XRectangle* overall_ink_return,XRectangle* overall_logical_return);
  Status (*xwcTextPerCharExtents)(XFontSet font_set,_Xconst wchar_t* text,int num_wchars,XRectangle* ink_extents_buffer,XRectangle* logical_extents_buffer,int buffer_size,int* num_chars,XRectangle* overall_ink_return,XRectangle* overall_logical_return);
  void (*xmbDrawText)(Display* display,Drawable d,GC gc,int x,int y,XmbTextItem* text_items,int nitems);
  void (*xwcDrawText)(Display* display,Drawable d,GC gc,int x,int y,XwcTextItem* text_items,int nitems);
  void (*xmbDrawString)(Display* display,Drawable d,XFontSet font_set,GC gc,int x,int y,_Xconst char* text,int bytes_text);
  void (*xwcDrawString)(Display* display,Drawable d,XFontSet font_set,GC gc,int x,int y,_Xconst wchar_t* text,int num_wchars);
  void (*xmbDrawImageString)(Display* display,Drawable d,XFontSet font_set,GC gc,int x,int y,_Xconst char* text,int bytes_text);
  void (*xwcDrawImageString)(Display* display,Drawable d,XFontSet font_set,GC gc,int x,int y,_Xconst wchar_t* text,int num_wchars);

  XClassHint *(*xAllocClassHint)(void);
  XIconSize *(*xAllocIconSize)(void);
  XSizeHints *(*xAllocSizeHints)(void);
  XStandardColormap *(*xAllocStandardColormap)(void);
  XWMHints *(*xAllocWMHints)(void);
  int (*xClipBox)(Region r,XRectangle* rect_return);
  Region (*xCreateRegion)(void);
  char *(*xDefaultString)(void);
  int (*xDeleteContext)(Display* display,XID rid,XContext context);
  int (*xDestroyRegion)(Region r);
  int (*xEmptyRegion)(Region r);
  int (*xEqualRegion)(Region r1,Region r2);
  int (*xFindContext)(Display* display,XID rid,XContext context,XPointer* data_return);
  Status (*xGetClassHint)(Display* display,Window w,XClassHint* class_hints_return);
  Status (*xGetIconSizes)(Display* display,Window w,XIconSize** size_list_return,int* count_return);
  Status (*xGetNormalHints)(Display* display,Window w,XSizeHints* hints_return);
  Status (*xGetRGBColormaps)(Display* display,Window w,XStandardColormap** stdcmap_return,int* count_return,Atom property);
  Status (*xGetSizeHints)(Display* display,Window w,XSizeHints* hints_return,Atom property);
  Status (*xGetStandardColormap)(Display* display,Window w,XStandardColormap* colormap_return,Atom property);
  Status (*xGetTextProperty)(Display* display,Window window,XTextProperty* text_prop_return,Atom property);
  XVisualInfo *(*xGetVisualInfo)(Display* display,long vinfo_mask,XVisualInfo* vinfo_template,int* nitems_return);
  Status (*xGetWMClientMachine)(Display* display,Window w,XTextProperty* text_prop_return);
  XWMHints *(*xGetWMHints)(Display* display,Window w);
  Status (*xGetWMIconName)(Display* display,Window w,XTextProperty* text_prop_return);
  Status (*xGetWMName)(Display* display,Window w,XTextProperty* text_prop_return);
  Status (*xGetWMNormalHints)(Display* display,Window w,XSizeHints* hints_return,long* supplied_return);
  Status (*xGetWMSizeHints)(Display* display,Window w,XSizeHints* hints_return,long* supplied_return,Atom property);
  Status (*xGetZoomHints)(Display* display,Window w,XSizeHints* zhints_return);
  int (*xIntersectRegion)(Region sra,Region srb,Region dr_return);
  void (*xConvertCase)(KeySym sym,KeySym* lower,KeySym* upper);
  int (*xLookupString)(XKeyEvent* event_struct,char* buffer_return,int bytes_buffer,KeySym* keysym_return,XComposeStatus* status_in_out);
  Status (*xMatchVisualInfo)(Display* display,int screen,int depth,int vclass,XVisualInfo* vinfo_return);
  int (*xOffsetRegion)(Region r,int dx,int dy);
  Bool (*xPointInRegion)(Region r,int x,int y);
  Region (*xPolygonRegion)(XPoint* points,int n,int fill_rule);
  int (*xRectInRegion)(Region r,int x,int y,unsigned int width,unsigned int height);
  int (*xSaveContext)(Display* display,XID rid,XContext context,_Xconst char* data);
  int (*xSetClassHint)(Display* display,Window w,XClassHint* class_hints);
  int (*xSetIconSizes)(Display* display,Window w,XIconSize* size_list,int count);
  int (*xSetNormalHints)(Display* display,Window w,XSizeHints* hints);
  void (*xSetRGBColormaps)(Display* display,Window w,XStandardColormap* stdcmaps,int count,Atom property);
  int (*xSetSizeHints)(Display* display,Window w,XSizeHints* hints,Atom property);
  int (*xSetStandardProperties)(Display* display,Window w,_Xconst char* window_name,_Xconst char* icon_name,Pixmap icon_pixmap,char** argv,int argc,XSizeHints* hints);
  void (*xSetTextProperty)(Display* display,Window w,XTextProperty* text_prop,Atom property);
  void (*xSetWMClientMachine)(Display* display,Window w,XTextProperty* text_prop);
  int (*xSetWMHints)(Display* display,Window w,XWMHints* wm_hints);
  void (*xSetWMIconName)(Display* display,Window w,XTextProperty* text_prop);
  void (*xSetWMName)(Display* display,Window w,XTextProperty* text_prop);
  void (*xSetWMNormalHints)(Display* display,Window w,XSizeHints* hints);
  void (*xSetWMProperties)(Display* display,Window w,XTextProperty* window_name,XTextProperty* icon_name,char** argv,int argc,XSizeHints* normal_hints,XWMHints* wm_hints,XClassHint* class_hints);
  void (*xmbSetWMProperties)(Display* display,Window w,_Xconst char* window_name,_Xconst char* icon_name,char** argv,int argc,XSizeHints* normal_hints,XWMHints* wm_hints,XClassHint* class_hints);
  void (*xSetWMSizeHints)(Display* display,Window w,XSizeHints* hints,Atom property);
  int (*xSetRegion)(Display* display,GC gc,Region r);
  void (*xSetStandardColormap)(Display* display,Window w,XStandardColormap* colormap,Atom property);
  int (*xSetZoomHints)(Display* display,Window w,XSizeHints* zhints);
  int (*xShrinkRegion)(Region r,int dx,int dy);
  Status (*xStringListToTextProperty)(char** list,int count,XTextProperty* text_prop_return);
  int (*xSubtractRegion)(Region sra,Region srb,Region dr_return);
  int (*xmbTextListToTextProperty)(Display* display,char** list,int count,XICCEncodingStyle style,XTextProperty* text_prop_return);
  int (*xwcTextListToTextProperty)(Display* display,wchar_t** list,int count,XICCEncodingStyle style,XTextProperty* text_prop_return);
  void (*xwcFreeStringList)(wchar_t** list);
  Status (*xTextPropertyToStringList)(XTextProperty* text_prop,char*** list_return,int* count_return);
  int (*xmbTextPropertyToTextList)(Display* display,XTextProperty* text_prop,char*** list_return,int* count_return);
  int (*xwcTextPropertyToTextList)(Display* display,XTextProperty* text_prop,wchar_t*** list_return,int* count_return);
  int (*xUnionRectWithRegion)(XRectangle* rectangle,Region src_region,Region dest_region_return);
  int (*xUnionRegion)(Region sra,Region srb,Region dr_return);
  int (*xWMGeometry)(Display* display,int screen_number,_Xconst char* user_geometry,_Xconst char* default_geometry,unsigned int border_width,XSizeHints* hints,int* x_return,int* y_return,int* width_return,int* height_return,int* gravity_return);
  int (*xXorRegion)(Region sra,Region srb,Region dr_return);
};

  /* X Toolkit (Xt) methods */
struct IfmXtMethods
{
  /* Version 0x5050 */
  WidgetClass (*xtGetWidgetClass) (const char* widget_class);
  char*	  (*xtRealloc)(char* ptr, Cardinal num, Cardinal size, IfmBool bInit);
  int	  (*xtCreateArgList)(Widget widget, WidgetClass widget_class, va_list vargs, ArgList* args, Cardinal* nargs);

  void	  (*xtManageChildren)(WidgetList children, Cardinal num_children);
  void	  (*xtUnmanageChildren)(WidgetList children, Cardinal num_children);
  Boolean (*xtConvertAndStore)(Widget widget,_Xconst _XtString from_type,XrmValue* from,_Xconst _XtString to_type,XrmValue* to_in_out);
  Boolean (*xtCallConverter)(Display* dpy,XtTypeConverter converter,XrmValuePtr args,Cardinal num_args,XrmValuePtr from,XrmValue* to_in_out,XtCacheRef* cache_ref_return);
  Boolean (*xtDispatchEvent)(XEvent* event);
  Boolean (*xtCallAcceptFocus)(Widget widget,Time* time);
  Boolean (*xtAppPeekEvent)(XtAppContext app_context,XEvent* event_return);
  Boolean (*xtIsSubclass)(Widget widget,WidgetClass _widgetClass);
  Boolean (*xtCheckSubclassFlag)(Widget object, _XtXtEnum type_flag);
  Boolean (*xtIsSubclassOf)(Widget object,WidgetClass widget_class,WidgetClass flag_class,_XtXtEnum type_flag);
  Boolean (*xtIsObject)(Widget object);
  Boolean (*xtIsManaged)(Widget rectobj);
  Boolean (*xtIsRealized)(Widget widget);
  Boolean (*xtIsSensitive)(Widget widget);
  Boolean (*xtOwnSelection)(Widget widget,Atom selection,Time time,XtConvertSelectionProc convert,XtLoseSelectionProc lose,XtSelectionDoneProc done);
  Boolean (*xtOwnSelectionIncremental)(Widget widget,Atom selection,Time time,XtConvertSelectionIncrProc convert_callback,XtLoseSelectionIncrProc lose_callback,XtSelectionDoneIncrProc done_callback,XtCancelConvertSelectionProc cancel_callback,XtPointer client_data);
  XtGeometryResult (*xtMakeResizeRequest)(Widget widget,_XtDimension width,_XtDimension height,Dimension* width_return,Dimension* height_return);
  void (*xtTranslateCoords)(Widget widget,_XtPosition x,_XtPosition y,Position* rootx_return,Position* rooty_return);
  KeySym* (*xtGetKeysymTable)(Display* dpy,KeyCode* min_keycode_return,int* keysyms_per_keycode_return);
  void (*xtKeysymToKeycodeList)(Display* dpy,KeySym keysym,KeyCode** keycodes_return,Cardinal* keycount_return);
  void (*xtDisplayStringConversionWarning)(Display* dpy,_Xconst _XtString from_value,_Xconst _XtString to_type);
  void (*xtSetTypeConverter)(_Xconst _XtString from_type,_Xconst _XtString to_type,XtTypeConverter converter,XtConvertArgList convert_args,Cardinal num_args,XtCacheType cache_type,XtDestructor destructor);
  void (*xtAppSetTypeConverter)(XtAppContext app_context,_Xconst _XtString from_type,_Xconst _XtString to_type,XtTypeConverter converter,XtConvertArgList convert_args,Cardinal num_args,XtCacheType cache_type,XtDestructor destructor);
  void (*xtConvert)(Widget widget,_Xconst _XtString from_type,XrmValue* from,_Xconst _XtString to_type,XrmValue* to_return);
  void (*xtDirectConvert)(XtConverter converter,XrmValuePtr args,Cardinal num_args,XrmValuePtr from,XrmValue* to_return);
  XtTranslations (*xtParseTranslationTable)(_Xconst _XtString table);
  XtAccelerators (*xtParseAcceleratorTable)(_Xconst _XtString source);
  void (*xtOverrideTranslations)(Widget widget,XtTranslations translations);
  void (*xtAugmentTranslations)(Widget widget,XtTranslations translations);
  void (*xtInstallAccelerators)(Widget destination,Widget source);
  void (*xtInstallAllAccelerators)(Widget destination,Widget source);
  void (*xtUninstallTranslations)(Widget widget);
  void (*xtAppAddActions)(XtAppContext app_context,XtActionList actions,Cardinal num_actions);
  XtActionHookId (*xtAppAddActionHook)(XtAppContext app_context,XtActionHookProc proc,XtPointer client_data);
  void (*xtRemoveActionHook)(XtActionHookId id);
  void (*xtGetActionList)(WidgetClass widget_class,XtActionList* actions_return,Cardinal* num_actions_return);
  void (*xtCallActionProc)(Widget widget,_Xconst _XtString action,XEvent* event,String* params,Cardinal num_params);
  void (*xtRegisterGrabAction)(XtActionProc action_proc,_XtBoolean owner_events,unsigned int event_mask,int pointer_mode,int keyboard_mode);
  void (*xtSetMultiClickTime)(Display* dpy,int milliseconds);
  int (*xtGetMultiClickTime)(Display* dpy);
  KeySym (*xtGetActionKeysym)(XEvent* event,Modifiers* modifiers_return);
  void (*xtTranslateKeycode)(Display* dpy,_XtKeyCode keycode,Modifiers modifiers,Modifiers* modifiers_return,KeySym* keysym_return);
  void (*xtTranslateKey)(Display* dpy,_XtKeyCode keycode,Modifiers modifiers,Modifiers* modifiers_return,KeySym* keysym_return);
  void (*xtSetKeyTranslator)(Display* dpy,XtKeyProc proc);
  void (*xtRegisterCaseConverter)(Display* dpy,XtCaseProc proc,KeySym start,KeySym stop);
  void (*xtConvertCase)(Display* dpy,KeySym keysym,KeySym* lower_return,KeySym* upper_return);
  void (*xtAddEventHandler)(Widget widget,EventMask event_mask,_XtBoolean nonmaskable,XtEventHandler proc,XtPointer closure);
  void (*xtRemoveEventHandler)(Widget widget,EventMask event_mask,_XtBoolean nonmaskable,XtEventHandler proc,XtPointer closure);
  void (*xtAddRawEventHandler)(Widget widget,EventMask event_mask,_XtBoolean nonmaskable,XtEventHandler proc,XtPointer closure);
  void (*xtRemoveRawEventHandler)(Widget widget,EventMask event_mask,_XtBoolean nonmaskable,XtEventHandler proc,XtPointer closure);
  void (*xtInsertEventHandler)(Widget widget,EventMask event_mask,_XtBoolean nonmaskable,XtEventHandler proc,XtPointer closure,XtListPosition position);
  void (*xtInsertRawEventHandler)(Widget widget,EventMask event_mask,_XtBoolean nonmaskable,XtEventHandler proc,XtPointer closure,XtListPosition position);
  XtEventDispatchProc (*xtSetEventDispatcher)(Display* dpy,int event_type,XtEventDispatchProc proc);
  Boolean (*xtDispatchEventToWidget)(Widget widget,XEvent* event);
  void (*xtInsertEventTypeHandler)(Widget widget,int type,XtPointer select_data,XtEventHandler proc,XtPointer closure,XtListPosition position);
  void (*xtRemoveEventTypeHandler)(Widget widget,int type,XtPointer select_data,XtEventHandler proc,XtPointer closure);
  EventMask (*xtBuildEventMask)(Widget widget);
  void (*xtRegisterExtensionSelector)(Display* dpy,int min_event_type,int max_event_type,XtExtensionSelectProc proc,XtPointer client_data);
  void (*xtAddGrab)(Widget widget,_XtBoolean exclusive,_XtBoolean spring_loaded);
  void (*xtRemoveGrab)(Widget widget);
  void (*xtAppProcessEvent)(XtAppContext app_context,XtInputMask mask);
  void (*xtAddExposureToRegion)(XEvent* event,Region region);
  void (*xtSetKeyboardFocus)(Widget subtree,Widget descendent);
  Widget (*xtGetKeyboardFocusWidget)(Widget widget);
  XEvent* (*xtLastEventProcessed)(Display* dpy);
  Time (*xtLastTimestampProcessed)(Display* dpy);
  XtIntervalId (*xtAppAddTimeOut)(XtAppContext app_context,unsigned long interval,XtTimerCallbackProc proc,XtPointer closure);
  void (*xtRemoveTimeOut)(XtIntervalId timer);
  XtInputId (*xtAppAddInput)(XtAppContext app_context,int source,XtPointer condition,XtInputCallbackProc proc,XtPointer closure);
  void (*xtRemoveInput)(XtInputId id);
  XtSignalId (*xtAppAddSignal)(XtAppContext app_context,XtSignalCallbackProc proc,XtPointer closure);
  void (*xtRemoveSignal)(XtSignalId id);
  void (*xtNoticeSignal)(XtSignalId id);
  void (*xtAppNextEvent)(XtAppContext app_context,XEvent* event_return);
  XtInputMask (*xtAppPending)(XtAppContext app_context);
  XtBlockHookId (*xtAppAddBlockHook)(XtAppContext app_context,XtBlockHookProc proc,XtPointer client_data);
  void (*xtRemoveBlockHook)(XtBlockHookId id);
  void (*xtRealizeWidget)(Widget widget);
  void (*xtUnrealizeWidget)(Widget widget);
  void (*xtDestroyWidget)(Widget widget);
  void (*xtSetSensitive)(Widget widget,_XtBoolean sensitive);
  void (*xtSetMappedWhenManaged)(Widget widget,_XtBoolean mapped_when_managed);
  Widget (*xtNameToWidget)(Widget reference,_Xconst _XtString names);
  Widget (*xtWindowToWidget)(Display* display,Window window);
  XtPointer (*xtGetClassExtension)(WidgetClass object_class,Cardinal byte_offset,XrmQuark type,long version,Cardinal record_size);
  ArgList (*xtMergeArgLists)(ArgList args1,Cardinal num_args1,ArgList args2,Cardinal num_args2);
  Display *(*xtDisplayOfObject)(Widget object);
  Screen *(*xtScreenOfObject)(Widget object);
  Window (*xtWindowOfObject)(Widget object);
  String (*xtName)(Widget object);
  WidgetClass (*xtSuperclass)(Widget object);
  WidgetClass (*xtClass)(Widget object);
  Widget (*xtParent)(Widget widget);
  void (*xtAddCallback)(Widget widget,_Xconst _XtString callback_name,XtCallbackProc callback,XtPointer closure);
  void (*xtRemoveCallback)(Widget widget,_Xconst _XtString callback_name,XtCallbackProc callback,XtPointer closure);
  void (*xtAddCallbacks)(Widget widget,_Xconst _XtString callback_name,XtCallbackList callbacks);
  void (*xtRemoveCallbacks)(Widget widget,_Xconst _XtString callback_name,XtCallbackList callbacks);
  void (*xtRemoveAllCallbacks)(Widget widget,_Xconst _XtString callback_name);
  void (*xtCallCallbacks)(Widget widget,_Xconst _XtString callback_name,XtPointer call_data);
  void (*xtCallCallbackList)(Widget widget,XtCallbackList callbacks,XtPointer call_data);
  XtCallbackStatus (*xtHasCallbacks)(Widget widget,_Xconst _XtString callback_name);
  XtGeometryResult (*xtMakeGeometryRequest)(Widget widget,XtWidgetGeometry* request,XtWidgetGeometry* reply_return);
  XtGeometryResult (*xtQueryGeometry)(Widget widget,XtWidgetGeometry* intended,XtWidgetGeometry* preferred_return);
  Widget (*xtCreatePopupShell)(_Xconst _XtString name,WidgetClass _widgetClass,Widget parent,ArgList args,Cardinal num_args);
  void (*xtPopup)(Widget popup_shell,XtGrabKind grab_kind);
  void (*xtPopupSpringLoaded)(Widget popup_shell);
  void (*xtCallbackNone)(Widget widget,XtPointer closure,XtPointer call_data);
  void (*xtCallbackNonexclusive)(Widget widget,XtPointer closure,XtPointer call_data);
  void (*xtCallbackExclusive)(Widget widget,XtPointer closure,XtPointer call_data);
  void (*xtPopdown)(Widget popup_shell);
  void (*xtCallbackPopdown)(Widget widget,XtPointer closure,XtPointer call_data);
  void (*xtMenuPopupAction)(Widget widget,XEvent* event,String* params,Cardinal* num_params);
  Widget (*xtCreateWidget)(_Xconst _XtString name,WidgetClass widget_class,Widget parent,ArgList args,Cardinal num_args);
  Widget (*xtAppCreateShell)(_Xconst _XtString application_name,_Xconst _XtString application_class,WidgetClass widget_class,Display* display,ArgList args,Cardinal num_args);
  XtAppContext (*xtWidgetToApplicationContext)(Widget widget);
  XtAppContext (*xtDisplayToApplicationContext)(Display* dpy);
  XrmDatabase (*xtDatabase)(Display* dpy);
  XrmDatabase (*xtScreenDatabase)(Screen* screen);
  void (*xtGetApplicationResources)(Widget widget,XtPointer base,XtResourceList resources,Cardinal num_resources,ArgList args,Cardinal num_args);
  void (*xtGetSubresources)(Widget widget,XtPointer base,_Xconst _XtString name,_Xconst _XtString _class,XtResourceList resources,Cardinal num_resources,ArgList args,Cardinal num_args);
  void (*xtSetValues)(Widget widget,ArgList args,Cardinal num_args);
  void (*xtGetValues)(Widget widget,ArgList args,Cardinal num_args);
  void (*xtSetSubvalues)(XtPointer base,XtResourceList resources,Cardinal num_resources,ArgList args,Cardinal num_args);
  void (*xtGetSubvalues)(XtPointer base,XtResourceList resources,Cardinal num_resources,ArgList args,Cardinal num_args);
  void (*xtGetResourceList)(WidgetClass widget_class,XtResourceList* resources_return,Cardinal* num_resources_return);
  void (*xtGetConstraintResourceList)(WidgetClass widget_class,XtResourceList* resources_return,Cardinal* num_resources_return);
  void (*xtAppErrorMsg)(XtAppContext app_context,_Xconst _XtString name,_Xconst _XtString type,_Xconst _XtString _class,_Xconst _XtString _default,String* params,Cardinal* num_params);
  void (*xtAppWarningMsg)(XtAppContext app_context,_Xconst _XtString name,_Xconst _XtString type,_Xconst _XtString _class,_Xconst _XtString _default,String* params,Cardinal* num_params);
  void (*xtAppError)(XtAppContext app_context,_Xconst _XtString message);
  void (*xtAppWarning)(XtAppContext app_context,_Xconst _XtString message);
  XrmDatabase *(*xtAppGetErrorDatabase)(XtAppContext app_context);
  void (*xtAppGetErrorDatabaseText)(XtAppContext app_context,_Xconst _XtString name,_Xconst _XtString type,_Xconst _XtString _class,_Xconst _XtString _default,String buffer_return,int nbytes,XrmDatabase database);
  XtWorkProcId (*xtAppAddWorkProc)(XtAppContext app_context,XtWorkProc proc,XtPointer closure);
  void  (*xtRemoveWorkProc)(XtWorkProcId id);
  GC (*xtGetGC)(Widget widget,XtGCMask valueMask,XGCValues* values);
  GC (*xtAllocateGC)(Widget widget,Cardinal depth,XtGCMask valueMask,XGCValues* values,XtGCMask dynamicMask,XtGCMask unusedMask);
  void (*xtDestroyGC)(GC gc);
  void (*xtReleaseGC)(Widget object,GC gc);
  void (*xtSetWMColormapWindows)(Widget widget,Widget* list,Cardinal count);
  String (*xtFindFile)(_Xconst _XtString path,Substitution substitutions,Cardinal num_substitutions,XtFilePredicate predicate);
  String (*xtResolvePathname)(Display* dpy,_Xconst _XtString type,_Xconst _XtString filename,_Xconst _XtString suffix,_Xconst _XtString path,Substitution substitutions,Cardinal num_substitutions,XtFilePredicate predicate);
  void (*xtDisownSelection)(Widget widget,Atom selection,Time time);
  void (*xtGetSelectionValue)(Widget widget,Atom selection,Atom target,XtSelectionCallbackProc callback,XtPointer closure,Time time);
  void (*xtGetSelectionValues)(Widget widget,Atom selection,Atom* targets,int count,XtSelectionCallbackProc callback,XtPointer* closures,Time time);
  void (*xtAppSetSelectionTimeout)(XtAppContext app_context,unsigned long timeout);
  unsigned long (*xtAppGetSelectionTimeout)(XtAppContext app_context);
  XSelectionRequestEvent *(*xtGetSelectionRequest)(Widget widget,Atom selection,XtRequestId request_id);
  void (*xtGetSelectionValueIncremental)(Widget widget,Atom selection,Atom target,XtSelectionCallbackProc selection_callback,XtPointer client_data,Time time);
  void (*xtGetSelectionValuesIncremental)(Widget widget,Atom selection,Atom* targets,int count,XtSelectionCallbackProc callback,XtPointer* client_data,Time time);
  void (*xtSetSelectionParameters)(Widget requestor,Atom selection,Atom type,XtPointer value,unsigned long length,int format);
  void (*xtGetSelectionParameters)(Widget owner,Atom selection,XtRequestId request_id,Atom* type_return,XtPointer* value_return,unsigned long* length_return,int* format_return);
  void (*xtCreateSelectionRequest)(Widget requestor,Atom selection);
  void (*xtSendSelectionRequest)(Widget requestor,Atom selection,Time time);
  void (*xtCancelSelectionRequest)(Widget requestor,Atom selection);
  Atom (*xtReservePropertyAtom)(Widget widget);
  void (*xtReleasePropertyAtom)(Widget widget,Atom selection);
  void (*xtGrabKey)(Widget widget,_XtKeyCode keycode,Modifiers modifiers,_XtBoolean owner_events,int pointer_mode,int keyboard_mode);
  void (*xtUngrabKey)(Widget widget,_XtKeyCode keycode,Modifiers modifiers);
  int (*xtGrabKeyboard)(Widget widget,_XtBoolean owner_events,int pointer_mode,int keyboard_mode,Time time);
  void (*xtUngrabKeyboard)(Widget widget,Time time);
  void (*xtGrabButton)(Widget widget,int button,Modifiers modifiers,_XtBoolean owner_events,unsigned int event_mask,int pointer_mode,int keyboard_mode,Window confine_to,Cursor cursor);
  void (*xtUngrabButton)(Widget widget,unsigned int button,Modifiers modifiers);
  int (*xtGrabPointer)(Widget widget,_XtBoolean owner_events,unsigned int event_mask,int pointer_mode,int keyboard_mode,Window confine_to,Cursor cursor,Time time);
  void (*xtUngrabPointer)(Widget widget,Time time);
  void (*xtGetApplicationNameAndClass)(Display* dpy,String* name_return,String* class_return);
  void (*xtRegisterDrawable)(Display* dpy,Drawable drawable,Widget widget);
  void (*xtUnregisterDrawable)(Display* dpy,Drawable drawable);
  Widget (*xtHooksOfDisplay)(Display* dpy);
  void (*xtGetDisplays)(XtAppContext app_context,Display*** dpy_return,Cardinal* num_dpy_return);
  void (*xtAppLock)(XtAppContext app_context);
  void (*xtAppUnlock)(XtAppContext app_context);
  Boolean (*xtCvtStringToAcceleratorTable)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToAtom)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToBool)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToBoolean)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToCommandArgArray)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToCursor)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToDimension)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToDirectoryString)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToDisplay)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToFile)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToFloat)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToFont)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToFontSet)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToFontStruct)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToGravity)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToInitialState)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToInt)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToPixel)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToRestartStyle)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToShort)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToTranslationTable)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToUnsignedChar)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtStringToVisual)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToBool)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToBoolean)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToColor)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToFloat)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToFont)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToPixel)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToPixmap)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToShort)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtIntToUnsignedChar)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);
  Boolean (*xtCvtColorToPixel)(Display* dpy,XrmValuePtr args,Cardinal* num_args,XrmValuePtr fromVal,XrmValuePtr toVal,XtPointer* closure_ret);

  XrmQuark (*xrmStringToQuark)(_Xconst char* string);
  XrmQuark (*xrmPermStringToQuark)(_Xconst char* string);
  XrmString (*xrmQuarkToString)(XrmQuark quark);
  XrmQuark (*xrmUniqueQuark)(void);
  void (*xrmStringToQuarkList)(_Xconst char* string,XrmQuarkList quarks_return);
  void (*xrmStringToBindingQuarkList)(_Xconst char* string,XrmBindingList bindings_return,XrmQuarkList quarks_return);
  void (*xrmDestroyDatabase)(XrmDatabase database);
  void (*xrmQPutResource)(XrmDatabase* database,XrmBindingList bindings,XrmQuarkList quarks,XrmRepresentation type,XrmValue* value);
  void (*xrmPutResource)(XrmDatabase* database,_Xconst char* specifier,_Xconst char* type,XrmValue* value);
  void (*xrmQPutStringResource)(XrmDatabase* database,XrmBindingList bindings,XrmQuarkList quarks,_Xconst char* value);
  void (*xrmPutStringResource)(XrmDatabase* database,_Xconst char* specifier,_Xconst char* value);
  void (*xrmPutLineResource)(XrmDatabase* database,_Xconst char* line);
  Bool (*xrmQGetResource)(XrmDatabase database,XrmNameList quark_name,XrmClassList quark_class,XrmRepresentation* quark_type_return,XrmValue* value_return);
  Bool (*xrmGetResource)(XrmDatabase database,_Xconst char* str_name,_Xconst char* str_class,char** str_type_return,XrmValue* value_return);
  Bool (*xrmQGetSearchList)(XrmDatabase database,XrmNameList names,XrmClassList classes,XrmSearchList list_return,int list_length);
  void (*xrmSetDatabase)(Display* display,XrmDatabase database);
  XrmDatabase (*xrmGetDatabase)(Display* display);
  XrmDatabase (*xrmGetFileDatabase)(_Xconst char* filename);
  Status (*xrmCombineFileDatabase)(_Xconst char* filename,XrmDatabase* target,Bool override);
  XrmDatabase (*xrmGetStringDatabase)(_Xconst char* data);
  void (*xrmPutFileDatabase)(XrmDatabase database,_Xconst char* filename);
  void (*xrmMergeDatabases)(XrmDatabase source_db,XrmDatabase* target_db);
  void (*xrmCombineDatabase)(XrmDatabase source_db,XrmDatabase* target_db,Bool override);
  Bool (*xrmEnumerateDatabase)(XrmDatabase db,XrmNameList name_prefix,XrmClassList class_prefix,int mode,XrmEnumerateCallback proc,XPointer closure);
  char *(*xrmLocaleOfDatabase)(XrmDatabase database);
  void (*xrmParseCommand)(XrmDatabase* database,XrmOptionDescList table,int table_count,_Xconst char* name,int* argc_in_out,char** argv_in_out);
};

  /* Motif (Xm) methods */
struct IfmXmMethods
{
  /* Version 0x5050 */
  Widget  (*xmCreateFormDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateFileSelectionDialog)(Widget parent,char *name,Arg *argList,Cardinal argcount);
  Widget  (*xmCreateDialogShell)(Widget widget,String name,ArgList arglist,Cardinal argcount);
  Widget  (*xmCreateCommandDialog)(Widget widget,String name,ArgList arglist,Cardinal argcount);
  Widget  (*xmCreateBulletinBoardDialog)(Widget widget,String name,ArgList arglist,Cardinal argcount);
  Widget  (*xmCreateSimpleCheckBox)(Widget parent,char *name,Arg *arglist,Cardinal argcount);
  Widget  (*xmCreateSimpleMenuBar)(Widget parent,char *name,Arg *arglist,Cardinal argcount);
  Widget  (*xmCreateSimpleOptionMenu)(Widget parent,char *name,Arg *arglist,Cardinal argcount);
  Widget  (*xmCreateSimplePopupMenu)(Widget parent,char *name,Arg *arglist,Cardinal argcount);
  Widget  (*xmCreateSimplePulldownMenu)(Widget parent,char *name,Arg *arglist,Cardinal argcount);
  Widget  (*xmCreateSimpleRadioBox)(Widget parent,char *name,Arg *arglist,Cardinal argcount);
  Widget  (*xmCreateScrolledList)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateScrolledText)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateSelectionDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreatePromptDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateMenuBar)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateOptionMenu)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreatePopupMenu)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreatePulldownMenu)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateRadioBox)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateWorkArea)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateErrorDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateInformationDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateMessageDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateQuestionDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateTemplateDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateWarningDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateWorkingDialog)(Widget parent,char *name,Arg *arglist,Cardinal argCount);
  Widget  (*xmCreateMenuShell)(Widget parent,char *name,Arg *arglist,Cardinal argCount);

  Widget  (*xmFileSelectionBoxGetChild)(Widget parent,_IfmEnum child);
  void  (*xmFileSelectionDoSearch)(Widget widget,XmString dirmask);
  Widget  (*xmDropTransferStart)(Widget refWidget,ArgList args,Cardinal argCount);
  void  (*xmDropTransferAdd)(Widget widget,XmDropTransferEntry transfers,Cardinal num_transfers);
  void  (*xmDropSiteRegister)(Widget widget,ArgList args,Cardinal argCount);
  void  (*xmDropSiteUnregister)(Widget widget);
  void  (*xmDropSiteStartUpdate)(Widget refWidget);
  void  (*xmDropSiteUpdate)(Widget enclosingWidget,ArgList args,Cardinal argCount);
  void  (*xmDropSiteEndUpdate)(Widget refWidget);
  void  (*xmDropSiteRetrieve)(Widget enclosingWidget,ArgList args,Cardinal argCount);
  int   (*xmDropSiteQueryStackingOrder)(Widget widget,Widget *parent_rtn,Widget **children_rtn,Cardinal *num_children_rtn);
  void  (*xmDropSiteConfigureStackingOrder)(Widget widget,Widget sibling,Cardinal stack_mode);
  XmDropSiteVisuals  (*xmDropSiteGetActiveVisuals)(Widget widget);
  Widget  (*xmDragStart)(Widget w,XEvent *event,ArgList args,Cardinal numArgs);
  void  (*xmDragCancel)(Widget dragContext);
  Boolean  (*xmTargetsAreCompatible)(Display *dpy,Atom *exportTargets,Cardinal numExportTargets,Atom *importTargets,Cardinal numImportTargets);
  Widget  (*xmGetXmDisplay)(Display *Dsp);
  Widget  (*xmGetDragContext)(Widget w,Time time);
  int  (*xmClipboardBeginCopy)(Display *display,Window window,XmString clip_label,Widget widget,VoidProc callback,long *item_id);
  int  (*xmClipboardCancelCopy)(Display *display,Window window,long item_id);
  int  (*xmClipboardCopy)(Display *display,Window window,long item_id,char *format_name,XtPointer buffer,unsigned long length,long private_id,long *data_id);
  int  (*xmClipboardCopyByName)(Display *display,Window window,long data_id,XtPointer buffer,unsigned long length,long private_id);
  int  (*xmClipboardEndCopy)(Display *display,Window window,long item_id);
  int  (*xmClipboardEndRetrieve)(Display *display,Window window);
  int  (*xmClipboardInquireCount)(Display *display,Window window,int *count,unsigned long *max_length);
  int  (*xmClipboardInquireFormat)(Display *display,Window window,int index,XtPointer format_name_buf,unsigned long buffer_len,unsigned long *copied_len);
  int  (*xmClipboardInquireLength)(Display *display,Window window,char *format_name,unsigned long *length);
  int  (*xmClipboardInquirePendingItems)(Display *display,Window window,char *format_name,XmClipboardPendingList *item_list,unsigned long *count);
  int  (*xmClipboardLock)(Display *display,Window window);
  int  (*xmClipboardRegisterFormat)(Display *display,char *format_name,int format_length);
  int  (*xmClipboardRetrieve)(Display *display,Window window,char *format_name,XtPointer buffer,unsigned long length,unsigned long *num_bytes,long *private_id);
  int  (*xmClipboardStartCopy)(Display *display,Window window,XmString clip_label,Time timestamp,Widget widget,XmCutPasteProc callback,long *item_id);
  int  (*xmClipboardStartRetrieve)(Display *display,Window window,Time timestamp);
  int  (*xmClipboardUndoCopy)(Display *display,Window window);
  int  (*xmClipboardUnlock)(Display *display,Window window,_IfmBoolean remove_all_locks);
  int  (*xmClipboardWithdrawFormat)(Display *display,Window window,long data_id);
  void  (*xmCommandSetValue)(Widget widget,XmString command);
  void  (*xmCommandAppendValue)(Widget widget,XmString command);
  void  (*xmCommandError)(Widget widget,XmString error);
  Widget  (*xmCommandGetChild)(Widget widget,_IfmEnum child);
  void  (*xmCascadeButtonGadgetHighlight)(Widget wid,_IfmBoolean highlight);
  Atom  (*xmInternAtom)(Display *display,String name,_IfmBoolean only_if_exists);
  String  (*xmGetAtomName)(Display *display,Atom atom);
  Cardinal  (*xmGetSecondaryResourceData)(WidgetClass wc,XmSecondaryResourceData **resData);
  Pixmap  (*xmGetPixmap)(Screen *screen,char *image_name,Pixel foreground,Pixel background);
  Pixmap  (*xmGetPixmapByDepth)(Screen *screen,char *image_name,Pixel foreground,Pixel background,int depth);
  Boolean  (*xmDestroyPixmap)(Screen *screen,Pixmap pixmap);
  Boolean  (*xmInstallImage)(XImage *image,char *image_name);
  Boolean  (*xmUninstallImage)(XImage *image);
  void  (*xmUpdateDisplay)(Widget w);
  void  (*xmResolvePartOffsets)(WidgetClass w_class,XmOffsetPtr *offset);
  void  (*xmResolveAllPartOffsets)(WidgetClass w_class,XmOffsetPtr *offset,XmOffsetPtr *constraint_offset);
  Boolean  (*xmWidgetGetBaselines)(Widget wid,Dimension **baselines,int *line_count);
  Boolean  (*xmWidgetGetDisplayRect)(Widget wid,XRectangle *displayrect);
  void  (*xmCvtStringToUnitType)(XrmValuePtr args,Cardinal *num_args,XrmValue *from_val,XrmValue *to_val);
  char  *(*xmRegisterSegmentEncoding)(char *fontlist_tag,char *ct_encoding);
  char  *(*xmMapSegmentEncoding)(char *fontlist_tag);
  XmString  (*xmCvtCTToXmString)(char *text);
  Boolean  (*xmCvtTextToXmString)(Display *display,XrmValuePtr args,Cardinal *num_args,XrmValue *from_val,XrmValue *to_val,XtPointer *converter_data);
  char  *(*xmCvtXmStringToCT)(XmString string);
  Boolean  (*xmCvtXmStringToText)(Display *display,XrmValuePtr args,Cardinal *num_args,XrmValue *from_val,XrmValue *to_val,XtPointer *converter_data);
  int  (*xmConvertUnits)(Widget widget,int orientation,int from_unit_type,int from_value,int to_unit_type);
  int  (*xmCvtToHorizontalPixels)(Screen *screen,int from_val,int from_type);
  int  (*xmCvtToVerticalPixels)(Screen *screen,int from_val,int from_type);
  int  (*xmCvtFromHorizontalPixels)(Screen *screen,int from_val,int to_type);
  int  (*xmCvtFromVerticalPixels)(Screen *screen,int from_val,int to_type);
  void  (*xmSetFontUnits)(Display *display,int h_value,int v_value);
  void  (*xmSetFontUnit)(Display *display,int value);
  void  (*xmSetMenuCursor)(Display *display,Cursor cursorId);
  Cursor  (*xmGetMenuCursor)(Display *display);
  Widget  (*xmTrackingEvent)(Widget widget,Cursor cursor,_IfmBoolean confine_to,XEvent *event_return);
  Widget  (*xmTrackingLocate)(Widget widget,Cursor cursor,_IfmBoolean confine_to);
  XmColorProc  (*xmSetColorCalculation)(XmColorProc proc);
  XmColorProc  (*xmGetColorCalculation)(void);
  void  (*xmGetColors)(Screen *screen,Colormap color_map,Pixel background,Pixel *foreground_ret,Pixel *top_shadow_ret,Pixel *bottom_shadow_ret,Pixel *select_ret);
  void  (*xmChangeColor)(Widget widget,Pixel background);
  Dimension  (*xmStringBaseline)(XmFontList fontlist,XmString string);
  Boolean  (*xmStringByteCompare)(XmString s1,XmString s2);
  Boolean  (*xmStringCompare)(XmString s1,XmString s2);
  XmString  (*xmStringConcat)(XmString s1,XmString s2);
  XmString  (*xmStringCreate)(char *text,char *tag);
  XmString  (*xmStringCreateLtoR)(char *text,char *tag);
  XmString  (*xmStringLtoRCreate)(char *text,char *tag);
  XmString  (*xmStringCreateLocalized)(char *text);
  XmString  (*xmStringCreateSimple)(char *text);
  XmString  (*xmStringDirectionCreate)(_IfmStringDirection direction);
  void  (*xmStringDraw)(Display *d,Window w,XmFontList fontlist,XmString string,GC gc,_IfmPosition x,_IfmPosition y,_IfmDimension width,_IfmEnum alignment,_IfmEnum layout_direction,XRectangle *clip);
  void  (*xmStringDrawImage)(Display *d,Window w,XmFontList fontlist,XmString string,GC gc,_IfmPosition x,_IfmPosition y,_IfmDimension width,_IfmEnum alignment,_IfmEnum layout_direction,XRectangle *clip);
  void  (*xmStringDrawUnderline)(Display *d,Window w,XmFontList fontlist,XmString string,GC gc,_IfmPosition x,_IfmPosition y,_IfmDimension width,_IfmEnum alignment,_IfmEnum layout_direction,XRectangle *clip,XmString underline);
  Boolean  (*xmStringEmpty)(XmString s1);
  void  (*xmStringExtent)(XmFontList fontlist,XmString string,Dimension *width,Dimension *height);
  void  (*xmStringFree)(XmString string);
  void  (*xmStringFreeContext)(XmStringContext context);
  Boolean  (*xmStringGetLtoR)(XmString string,XmStringCharSet tag,char **text);
  XmStringComponentType  (*xmStringGetNextComponent)(XmStringContext context,char **text,XmStringCharSet *tag,XmStringDirection *direction,XmStringComponentType *unknown_tag,unsigned short *unknown_length,unsigned char **unknown_value);
  Boolean  (*xmStringGetNextSegment)(XmStringContext context,char **text,XmStringCharSet *tag,XmStringDirection *direction,Boolean *separator);
  Boolean  (*xmStringHasSubstring)(XmString string,XmString substring);
  Dimension  (*xmStringHeight)(XmFontList fontlist,XmString string);
  Boolean  (*xmStringInitContext)(XmStringContext *context,XmString string);
  int  (*xmStringLength)(XmString s1);
  int  (*xmStringLineCount)(XmString string);
  XmString  (*xmStringNConcat)(XmString s1,XmString s2,int num_bytes);
  XmString  (*xmStringCopy)(XmString s);
  XmString  (*xmStringNCopy)(XmString s1,int num_bytes);
  XmStringComponentType  (*xmStringPeekNextComponent)(XmStringContext context);
  XmString  (*xmStringSegmentCreate)(char *text,char *tag,_IfmStringDirection direction,_IfmBoolean separator);
  XmString  (*xmStringSeparatorCreate)(void);
  Dimension  (*xmStringWidth)(XmFontList fontList,XmString string);
  XmFontList  (*xmStringCreateFontList)(XFontStruct *font,XmStringCharSet charset);
  XmFontList  (*xmFontListAppendEntry)(XmFontList oldlist,XmFontListEntry entry);
  XmFontList  (*xmFontListCreate)(XFontStruct *font,XmStringCharSet charset);
  XmFontList  (*xmFontListAdd)(XmFontList old,XFontStruct *font,XmStringCharSet charset);
  XmFontList  (*xmFontListCopy)(XmFontList fontlist);
  XmFontListEntry  (*xmFontListEntryCreate)(char *tag,XmFontType type,XtPointer font);
  void  (*xmFontListEntryFree)(XmFontListEntry *entry);
  XtPointer  (*xmFontListEntryGetFont)(XmFontListEntry entry,XmFontType *type_return);
  char  *(*xmFontListEntryGetTag)(XmFontListEntry entry);
  XmFontListEntry  (*xmFontListEntryLoad)(Display *display,char *font_name,XmFontType type,char *tag);
  void  (*xmFontListFree)(XmFontList list);
  void  (*xmFontListFreeFontContext)(XmFontContext context);
  Boolean  (*xmFontListInitFontContext)(XmFontContext *context,XmFontList fontlist);
  XmFontListEntry  (*xmFontListNextEntry)(XmFontContext context);
  Boolean  (*xmFontListGetNextFont)(XmFontContext context,XmStringCharSet *charset,XFontStruct **font);
  XmFontList  (*xmFontListRemoveEntry)(XmFontList oldlist,XmFontListEntry entry);
  Widget  (*xmGetDestination)(Display *display);
  Boolean  (*xmIsTraversable)(Widget widget);
  XmVisibility  (*xmGetVisibility)(Widget widget);
  void  (*xmAddTabGroup)(Widget widget);
  void  (*xmRemoveTabGroup)(Widget widget);
  Widget  (*xmGetTabGroup)(Widget widget);
  Boolean  (*xmProcessTraversal)(Widget widget,XmTraversalDirection direction);
  Widget  (*xmGetFocusWidget)(Widget widget);
  void  (*xmListAddItem)(Widget widget,XmString item,int position);
  void  (*xmListAddItems)(Widget widget,XmString *items,int item_count,int position);
  void  (*xmListAddItemUnselected)(Widget widget,XmString item,int position);
  void  (*xmListAddItemsUnselected)(Widget widget,XmString *items,int item_count,int position);
  void  (*xmListDeleteAllItems)(Widget widget);
  void  (*xmListDeleteItem)(Widget widget,XmString item);
  void  (*xmListDeleteItems)(Widget widget,XmString *items,int item_count);
  void  (*xmListDeleteItemsPos)(Widget widget,int item_count,int position);
  void  (*xmListDeletePos)(Widget widget,int position);
  void  (*xmListDeletePositions)(Widget widget,int *position_list,int position_count);
  void  (*xmListDeselectAllItems)(Widget widget);
  void  (*xmListDeselectItem)(Widget widget,XmString item);
  void  (*xmListDeselectPos)(Widget widget,int position);
  int  (*xmListGetKbdItemPos)(Widget widget);
  Boolean  (*xmListGetMatchPos)(Widget widget,XmString item,int **position_list,int *position_count);
  Boolean  (*xmListGetSelectedPos)(Widget widget,int **position_list,int *position_count);
  Boolean  (*xmListItemExists)(Widget widget,XmString item);
  int  (*xmListItemPos)(Widget widget,XmString item);
  Boolean  (*xmListPosSelected)(Widget widget,int position);
  Boolean  (*xmListPosToBounds)(Widget widget,int position,Position *x,Position *y,Dimension *width,Dimension *height);
  void  (*xmListReplaceItems)(Widget widget,XmString *old_items,int item_count,XmString *new_items);
  void  (*xmListReplaceItemsPos)(Widget widget,XmString *new_items,int item_count,int position);
  void  (*xmListReplaceItemsPosUnselected)(Widget widget,XmString *new_items,int item_count,int position);
  void  (*xmListReplaceItemsUnselected)(Widget widget,XmString *old_items,int item_count,XmString *new_items);
  void  (*xmListReplacePositions)(Widget widget,int *position_list,XmString *item_list,int item_count);
  void  (*xmListSelectItem)(Widget widget,XmString item,_IfmBoolean notify);
  void  (*xmListSelectPos)(Widget widget,int position,_IfmBoolean notify);
  void  (*xmListSetAddMode)(Widget widget,_IfmBoolean mode);
  void  (*xmListSetBottomItem)(Widget widget,XmString item);
  void  (*xmListSetBottomPos)(Widget widget,int position);
  void  (*xmListSetHorizPos)(Widget widget,int position);
  void  (*xmListSetItem)(Widget widget,XmString item);
  Boolean  (*xmListSetKbdItemPos)(Widget widget,int position);
  void  (*xmListSetPos)(Widget widget,int position);
  void  (*xmListUpdateSelectedList)(Widget widget);
  int  (*xmListYToPos)(Widget widget,_IfmPosition y);
  void  (*xmTextClearSelection)(Widget widget,Time time);
  Boolean  (*xmTextCopy)(Widget widget,Time time);
  Boolean  (*xmTextCut)(Widget widget,Time time);
  void  (*xmTextDisableRedisplay)(Widget widget);
  void  (*xmTextEnableRedisplay)(Widget widget);
  Boolean  (*xmTextFindString)(Widget widget,XmTextPosition start,char *string,XmTextDirection direction,XmTextPosition *position);
  Boolean  (*xmTextFindStringWcs)(Widget widget,XmTextPosition start,wchar_t *wcstring,XmTextDirection direction,XmTextPosition *position);
  int  (*xmTextGetBaseline)(Widget widget);
  XmTextPosition  (*xmTextGetCursorPosition)(Widget widget);
  Boolean  (*xmTextGetEditable)(Widget widget);
  XmTextPosition  (*xmTextGetInsertionPosition)(Widget widget);
  XmTextPosition  (*xmTextGetLastPosition)(Widget widget);
  int  (*xmTextGetMaxLength)(Widget widget);
  char  *(*xmTextGetSelection)(Widget widget);
  Boolean  (*xmTextGetSelectionPosition)(Widget widget,XmTextPosition *left,XmTextPosition *right);
  wchar_t  *(*xmTextGetSelectionWcs)(Widget widget);
  XmTextSource  (*xmTextGetSource)(Widget widget);
  char  *(*xmTextGetString)(Widget widget);
  wchar_t  *(*xmTextGetStringWcs)(Widget widget);
  int  (*xmTextGetSubstring)(Widget widget,XmTextPosition start,int num_chars,int buffer_size,char *buffer);
  int  (*xmTextGetSubstringWcs)(Widget widget,XmTextPosition start,int num_chars,int buffer_size,wchar_t *buffer);
  XmTextPosition  (*xmTextGetTopCharacter)(Widget widget);
  void  (*xmTextInsert)(Widget widget,XmTextPosition position,char *string);
  void  (*xmTextInsertWcs)(Widget widget,XmTextPosition position,wchar_t *wcstring);
  Boolean  (*xmTextPaste)(Widget widget);
  Boolean  (*xmTextPosToXY)(Widget widget,XmTextPosition position,Position *x,Position *y);
  Boolean  (*xmTextRemove)(Widget widget);
  void  (*xmTextReplace)(Widget widget,XmTextPosition from_pos,XmTextPosition to_pos,char *value);
  void  (*xmTextReplaceWcs)(Widget widget,XmTextPosition from_pos,XmTextPosition to_pos,wchar_t *wcstring);
  void  (*xmTextScroll)(Widget widget,int lines);
  void  (*xmTextSetAddMode)(Widget widget,_IfmBoolean state);
  void  (*xmTextSetCursorPosition)(Widget widget,XmTextPosition position);
  void  (*xmTextSetEditable)(Widget widget,_IfmBoolean editable);
  void  (*xmTextSetHighlight)(Widget widget,XmTextPosition left,XmTextPosition right,XmHighlightMode mode);
  void  (*xmTextSetInsertionPosition)(Widget widget,XmTextPosition position);
  void  (*xmTextSetMaxLength)(Widget widget,int max_length);
  void  (*xmTextSetSelection)(Widget widget,XmTextPosition first,XmTextPosition last,Time time);
  void  (*xmTextSetSource)(Widget widget,XmTextSource source,XmTextPosition top_character,XmTextPosition cursor_position);
  void  (*xmTextSetString)(Widget widget,char *value);
  void  (*xmTextSetStringWcs)(Widget widget,wchar_t *wcstring);
  void  (*xmTextSetTopCharacter)(Widget widget,XmTextPosition top_character);
  void  (*xmTextShowPosition)(Widget widget,XmTextPosition position);
  XmTextPosition  (*xmTextXYToPos)(Widget widget,_IfmPosition x,_IfmPosition y);
  Widget  (*xmSelectionBoxGetChild)(Widget parent,_IfmEnum child);
  void  (*xmScrollVisible)(Widget scrollw_widget,Widget widget,Dimension left_right_margin,Dimension top_bottom_margin);
  void  (*xmScrolledWindowSetAreas)(Widget widget,Widget h_scrollbar,Widget v_scrollbar,Widget work_region);
  void  (*xmScrollBarGetValues)(Widget w,int *value_return,int *slider_size_return,int *increment_return,int *page_increment_return);
  void  (*xmScrollBarSetValues)(Widget w,int value,int slider_size,int increment,int page_increment,_IfmBoolean notify);
  Widget  (*xmGetXmScreen)(Screen *screen);
  void  (*xmScaleGetValue)(Widget widget,int *value_return);
  void  (*xmScaleSetValue)(Widget widget,int value);
  Widget  (*xmOptionButtonGadget)(Widget option_menu);
  Widget  (*xmOptionLabelGadget)(Widget option_menu);
  void  (*xmMenuPosition)(Widget menu,XButtonPressedEvent *event);
  Widget  (*xmGetTearOffControl)(Widget menu);
  void  (*xmAddToPostFromList)(Widget menu_wid,Widget widget);
  void  (*xmRemoveFromPostFromList)(Widget menu_wid,Widget widget);
  Widget  (*xmGetPostedFromWidget)(Widget menu);
  void  (*xmActivateProtocol)(Widget shell,Atom property,Atom protocol);
  void  (*xmAddProtocolCallback)(Widget shell,Atom property,Atom protocol,XtCallbackProc callback,XtPointer closure);
  void  (*xmAddProtocols)(Widget shell,Atom property,Atom *protocol,Cardinal num_protocols);
  void  (*xmRemoveProtocolCallback)(Widget shell,Atom property,Atom protocol,XtCallbackProc callback,XtPointer closure);
  void  (*xmRemoveProtocols)(Widget shell,Atom property,Atom *protocols,Cardinal num_protocols);
  void  (*xmDeactivateProtocol)(Widget shell,Atom property,Atom proto_atom);
  void  (*xmSetProtocolHooks)(Widget shell,Atom property,Atom proto_atom,XtCallbackProc pre_hook,XtPointer pre_closure,XtCallbackProc post_hook,XtPointer post_closure);
  Widget  (*xmMessageBoxGetChild)(Widget parent,_IfmEnum child);
  Widget  (*xmMainWindowSep1)(Widget widget);
  Widget  (*xmMainWindowSep2)(Widget widget);
  Widget  (*xmMainWindowSep3)(Widget widget);
  void  (*xmMainWindowSetAreas)(Widget widget,Widget menu_bar,Widget command_window,Widget horizontal_scrollbar,Widget vertical_scrollbar,Widget work_region);
  Boolean (*xmToggleButtonGetState)(Widget widget);
  void (*xmToggleButtonSetState)(Widget widget,_IfmBoolean state,_IfmBoolean notify);
  Boolean  (*xmToggleButtonGadgetGetState)(Widget gadget);
  void  (*xmToggleButtonGadgetSetState)(Widget gadget,_IfmBoolean state,_IfmBoolean notify);
  void (*xmTextFieldClearSelection)(Widget widget,Time time);
  Boolean (*xmTextFieldCopy)(Widget widget,Time time);
  Boolean (*xmTextFieldCut)(Widget widget,Time time);
  int (*xmTextFieldGetBaseline)(Widget widget);
  XmTextPosition (*xmTextFieldGetCursorPosition)(Widget widget);
  Boolean (*xmTextFieldGetEditable)(Widget widget);
  XmTextPosition (*xmTextFieldGetInsertionPosition)(Widget widget);
  XmTextPosition (*xmTextFieldGetLastPosition)(Widget widget);
  int (*xmTextFieldGetMaxLength)(Widget widget);
  char *(*xmTextFieldGetSelection)(Widget widget);
  Boolean (*xmTextFieldGetSelectionPosition)(Widget widget,XmTextPosition *left,XmTextPosition *right);
  wchar_t *(*xmTextFieldGetSelectionWcs)(Widget widget);
  char *(*xmTextFieldGetString)(Widget widget);
  wchar_t *(*xmTextFieldGetStringWcs)(Widget widget);
  int (*xmTextFieldGetSubstring)(Widget widget,XmTextPosition start,int num_chars,int buffer_size,char *buffer);
  int (*xmTextFieldGetSubstringWcs)(Widget widget,XmTextPosition start,int num_chars,int buffer_size,wchar_t *buffer);
  void (*xmTextFieldInsert)(Widget widget,XmTextPosition position,char *string);
  void (*xmTextFieldInsertWcs)(Widget widget,XmTextPosition position,wchar_t *wcstring);
  Boolean (*xmTextFieldPaste)(Widget widget);
  Boolean (*xmTextFieldPosToXY)(Widget widget,XmTextPosition position,Position *x,Position *y);
  Boolean (*xmTextFieldRemove)(Widget widget);
  void (*xmTextFieldReplace)(Widget widget,XmTextPosition from_pos,XmTextPosition to_pos,char *value);
  void (*xmTextFieldReplaceWcs)(Widget widget,XmTextPosition from_pos,XmTextPosition to_pos,wchar_t *wcstring);
  void (*xmTextFieldSetAddMode)(Widget widget,_IfmBoolean state);
  void (*xmTextFieldSetCursorPosition)(Widget widget,XmTextPosition position);
  void (*xmTextFieldSetEditable)(Widget widget,_IfmBoolean editable);
  void (*xmTextFieldSetHighlight)(Widget widget,XmTextPosition left,XmTextPosition right,XmHighlightMode mode);
  void (*xmTextFieldSetInsertionPosition)(Widget widget,XmTextPosition position);
  void (*xmTextFieldSetMaxLength)(Widget widget,int max_length);
  void (*xmTextFieldSetSelection)(Widget widget,XmTextPosition first,XmTextPosition last,Time time);
  void (*xmTextFieldSetString)(Widget widget,char *value);
  void (*xmTextFieldSetStringWcs)(Widget widget,wchar_t *wcstring);
  void (*xmTextFieldShowPosition)(Widget widget,XmTextPosition position);
  XmTextPosition (*xmTextFieldXYToPos)(Widget widget,_IfmPosition x,_IfmPosition y);

  String (*dtxComboBoxGetString)(Widget w);
  void (*dtxComboBoxSetString)(Widget w,String text);
  int (*dtxComboBoxAddItem)(Widget combo,XmString item,int pos,int unique);
  void (*dtxComboBoxAddItems)(Widget combo,XmString* items,int n,int pos);
  void (*dtxComboBoxDeletePos)(Widget combo,int pos);
  void (*dtxComboBoxDeleteAllItems)(Widget combo);
  void (*dtxComboBoxSetItem)(Widget combo,XmString item);
  void (*dtxComboBoxSelectItem)(Widget combo,XmString item);
  void (*dtxComboBoxSelectPos)(Widget combo,int pos);
  void (*dtxComboBoxSelectPosEx)(Widget combo,int pos,int notify);
  void (*dtxComboBoxReplaceItems)(Widget combo,XmString* old_items,int count,XmString* new_items);
  void (*dtxComboBoxReplaceItemsPosUnselected)(Widget combo,XmString* items,int count,int pos);
  void (*dtxComboBoxReplaceItemsPos)(Widget combo,XmString* items,int count,int pos);
  void (*dtxComboBoxReplaceItemsUnselected)(Widget combo,XmString* old_items,int count,XmString* new_items);
  void (*dtxComboBoxReplacePositions)(Widget combo,int* positions,XmString* items,int count);
  int (*dtxComboBoxGetSelectedPos)(Widget combo);
  XtPointer (*dtxComboBoxSetItemData)(Widget combo,int pos,XtPointer data);
  XtPointer (*dtxComboBoxGetItemData)(Widget combo,int pos);
  void (*xbaeMatrixSetCell)(Widget w,int row,int column,_Xconst String value);
  void (*xbaeMatrixEditCell)(Widget w,int row,int column);
  void (*xbaeMatrixSelectCell)(Widget w,int row,int column);
  void (*xbaeMatrixSelectRow)(Widget w,int row);
  void (*xbaeMatrixSelectColumn)(Widget w,int column);
  void (*xbaeMatrixDeselectAll)(Widget w);
  void (*xbaeMatrixDeselectCell)(Widget w,int row,int column);
  void (*xbaeMatrixDeselectRow)(Widget w,int row);
  void (*xbaeMatrixDeselectColumn)(Widget w,int column);
  String (*xbaeMatrixGetCell)(Widget w,int row,int column);
  Boolean (*xbaeMatrixCommitEdit)(Widget w,Boolean unmap);
  void (*xbaeMatrixCancelEdit)(Widget w,Boolean unmap);
  void (*xbaeMatrixAddRows)(Widget w,int position,String* rows,String* labels,Pixel* colors,int num_colors);
  void (*xbaeMatrixDeleteRows)(Widget w,int position,int num_rows);
  void (*xbaeMatrixAddColumns)(Widget w,int position,String* columns,String* labels,short* widths,int* max_lengths,unsigned char* alignments,unsigned char* label_alignments,Pixel* colors,int num_columns);
  void (*xbaeMatrixDeleteColumns)(Widget w,int position,int num_columns);
  void (*xbaeMatrixSetRowColors)(Widget w,int position,Pixel* colors,int num_colors);
  void (*xbaeMatrixSetColumnColors)(Widget w,int position,Pixel* colors,int num_colors);
  void (*xbaeMatrixSetCellColor)(Widget w,int row,int column,Pixel color);
  int (*xbaeMatrixGetEventRowColumn)(Widget w,XEvent* event,int* row,int* column);
  void (*xbaeMatrixGetCurrentCell)(Widget w,int* row,int* column);
  void (*xbaeMatrixRefresh)(Widget w);
  Widget (*xbaeMatrixGetChild)(Widget w,XbaeMatrixChildType child);
  void (*xbaeMatrixSetChoice)(Widget w,XmString* items,Cardinal item_count);
  void (*xbaeClipRedraw)(Widget w);
};

struct IfmX11Part
{
  int				nId;   		/* Class identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmX11Methods*		pfn;	   	/* Implementation of the interface */
  void*				privData; 	/* Pointer to private (FEFLOW's) data */
};

struct IfmXtPart
{
  int				nId;   		/* Class identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmXtMethods*		pfn;	   	/* Implementation of the interface */
  void*				privData; 	/* Pointer to private (FEFLOW's) data */
};

struct IfmXmPart
{
  int				nId;   		/* Class identification code */
  int				nVersion;   	/* FEFLOW's interface version */
  int				nSize;		/* Size of part */
  int				nProcs;		/* Number of methods */
  struct IfmXmMethods*		pfn;	   	/* Implementation of the interface */
  void*				privData; 	/* Pointer to private (FEFLOW's) data */
};

struct IfmMotifStruct
{
  int				numParts;   	/* Number of available parts */
  IfmPointer			hdlData;	/* Handle-specific data */
  IfmPointer			pReserve[2];	/* Reserve for future releases */
  struct IfmModulePart		mod;		/* Module interface */
  struct IfmGraphicPart		gph;		/* Graphics interface */
  struct IfmX11Part		x11;		/* Xlib interface */
  struct IfmXtPart		xt;		/* Xt interface */
  struct IfmXmPart		xm;		/* Motif interface */
};

#define X11_STRUCT(pHdl) ((struct IfmMotifStruct*)pHdl)
#define X11_PART(pHdl) (&X11_STRUCT(pHdl)->x11)
#define X11_CALL(pHdl, func, args) X11_PART(pHdl)->pfn->func args
#define IS_X11_STRUCT(pHdl) ((pHdl)->numParts >= 3 && X11_PART(pHdl)->nId == IFM_X11_ID)

#define X11_ASSERT_VALID(pHdl) \
  GPH_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_X11_ID, IFM_CURRENT_X11_VERSION)

#define X11_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, X11_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmX11Methods, proc) < X11_PART(pHdl)->nProcs)

#define XT_STRUCT(pHdl) ((struct IfmMotifStruct*)pHdl)
#define XT_PART(pHdl) (&XT_STRUCT(pHdl)->xt)
#define XT_CALL(pHdl, func, args) XT_PART(pHdl)->pfn->func args
#define IS_XT_STRUCT(pHdl) ((pHdl)->numParts >= 4 && XT_PART(pHdl)->nId == IFM_XT_ID)

#define XT_ASSERT_VALID(pHdl) \
  X11_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_XT_ID, IFM_CURRENT_XT_VERSION)

#define XT_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, XT_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmXtMethods, proc) < XT_PART(pHdl)->nProcs)

#define XM_STRUCT(pHdl) ((struct IfmMotifStruct*)pHdl)
#define XM_PART(pHdl) (&XM_STRUCT(pHdl)->xm)
#define XM_CALL(pHdl, func, args) XM_PART(pHdl)->pfn->func args
#define IS_XM_STRUCT(pHdl) ((pHdl)->numParts >= 5 && XM_PART(pHdl)->nId == IFM_XM_ID)

#define XM_ASSERT_VALID(pHdl) \
  XT_ASSERT_VALID(pHdl); \
  IFM_ASSERT_VALID(pHdl, IFM_XM_ID, IFM_CURRENT_XM_VERSION)

#define XM_ASSERT_PROC(pHdl, proc) \
  IFM_ASSERT(pHdl, XM_PART(pHdl)->pfn->proc != NULL); \
  IFM_ASSERT(pHdl, IFM_PROC_NUM(struct IfmXmMethods, proc) < XM_PART(pHdl)->nProcs)

#include "graphicp.h"

#endif /* IFM_XDKP_H */
