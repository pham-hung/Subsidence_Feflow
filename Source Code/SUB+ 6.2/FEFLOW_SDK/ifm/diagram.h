#ifndef IFM_DIAGRAM_H
#define IFM_DIAGRAM_H

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
#include "archive.h"

#ifndef IFM_CURRENT_DIAGRAM_VERSION
#define IFM_CURRENT_DIAGRAM_VERSION 0x5413
#endif
#ifndef IFM_CURRENT_CURVE_VERSION
#define IFM_CURRENT_CURVE_VERSION   0x5050
#endif

#if defined IFM_TARGET_VERSION && IFM_TARGET_VERSION < IFM_CURRENT_DIAGRAM_VERSION
#undef  IFM_CURRENT_DIAGRAM_VERSION
#define IFM_CURRENT_DIAGRAM_VERSION IFM_TARGET_VERSION
#endif

#if defined IFM_TARGET_VERSION && IFM_TARGET_VERSION < IFM_CURRENT_CURVE_VERSION
#undef  IFM_CURRENT_CURVE_VERSION
#define IFM_CURRENT_CURVE_VERSION IFM_TARGET_VERSION
#endif

#if IFM_REQUIRED_VERSION < IFM_CURRENT_DIAGRAM_VERSION
#undef  IFM_REQUIRED_VERSION
#define IFM_REQUIRED_VERSION IFM_CURRENT_DIAGRAM_VERSION
#endif
#if IFM_REQUIRED_VERSION < IFM_CURRENT_CURVE_VERSION
#undef  IFM_REQUIRED_VERSION
#define IFM_REQUIRED_VERSION IFM_CURRENT_CURVE_VERSION
#endif


/*****************************************************************
** Custom diagram windows
*/

#define IfmNO_DATA	1.1e38	/* Values > 1.e38 are handled as NO_DATA */

#define IfmDSC_LINEAR	0	/* Diagram scaling */
#define IfmDSC_LOGX	1
#define IfmDSC_LOGY	2
#define IfmDSC_LOGXY	3

#define IfmDLS_NONE	0	/* Diagram line types */
#define IfmDLS_SOLID	1
#define IfmDLS_DASH	2
#define IfmDLS_DOT	3
#define IfmDLS_DASH_DOT	4
#define IfmDLS_DASH2	5

#define IfmDMT_NONE	-1	/* Diagram marker types */
#define IfmDMT_PLUS	1
#define IfmDMT_CROSS	0
#define IfmDMT_QUAD	2
#define IfmDMT_DIAMOND	6
#define IfmDMT_TRIUP	7
#define IfmDMT_TRIDOWN	8

	/* Diagram resources */
#define IfmNdiagramKind		IfmDiagramStrings[0]	/* int:	    DSC_LINEAR	*/
#define IfmNabscissaLabel	IfmDiagramStrings[1]	/* string:  ""		*/
#define IfmNordinateLabel	IfmDiagramStrings[2]	/* string:  ""		*/
#define IfmNabscissaUnit	IfmDiagramStrings[3]	/* string:  ""		*/
#define IfmNordinateUnit	IfmDiagramStrings[4]	/* string:  ""		*/
#define IfmNautoScale		IfmDiagramStrings[5]	/* bool:    true (ignored) */
#define IfmNautoLayout		IfmDiagramStrings[6]	/* bool:    true (ignored) */
#define IfmNextentMinX		IfmDiagramStrings[7]	/* double:  1.		*/
#define IfmNextentMinY		IfmDiagramStrings[8]	/* double:  1.		*/
#define IfmNextentMaxX		IfmDiagramStrings[9]	/* double:  1.		*/
#define IfmNextentMaxY		IfmDiagramStrings[10]	/* double:  1.		*/
#define IfmNmarginLeft		IfmDiagramStrings[11]	/* int:	    50 pixel	*/
#define IfmNmarginRight		IfmDiagramStrings[12]	/* int:	    5 pixel	*/
#define IfmNmarginTop		IfmDiagramStrings[13]	/* int:	    5 pixel	*/
#define IfmNmarginBottom	IfmDiagramStrings[14]	/* int:	    30 pixel	*/
#define IfmNadjustExtent	IfmDiagramStrings[15]	/* bool:    true	*/
#define IfmNabscissaLabelFormat	IfmDiagramStrings[16]	/* string:  "%g"	*/
#define IfmNordinateLabelFormat	IfmDiagramStrings[17]	/* string:  "%g"	*/
#define IfmNmajorTicLength	IfmDiagramStrings[18]	/* int:	    5 pixel	*/
#define IfmNminorTicLength	IfmDiagramStrings[19]	/* int:	    3 pixel	*/
#define IfmNdiagramTitle	IfmDiagramStrings[20]	/* string:  ""		*/
#define IfmNshowTooltips	IfmDiagramStrings[21]	/* bool:    true	*/
#define IfmNhorizontalGridLines	IfmDiagramStrings[22]	/* bool:    true	*/
#define IfmNverticalGridLines	IfmDiagramStrings[23]	/* bool:    true	*/
#define IfmNdisableContextMenu	IfmDiagramStrings[24]	/* bool:    false	*/
#define IfmNverticalSpacing	IfmDiagramStrings[25]	/* int:     5 pixel	*/
#define IfmNhorizontalSpacing	IfmDiagramStrings[26]	/* int:     5 pixel	*/
#define IfmNdiagramX		IfmDiagramStrings[27]	/* int:     unspecified	*/
#define IfmNdiagramY		IfmDiagramStrings[28]	/* int:     unspecified	*/
#define IfmNdiagramWidth	IfmDiagramStrings[29]	/* int:     100 pixel	*/
#define IfmNdiagramHeight	IfmDiagramStrings[30]	/* int:     100 pixel	*/

	/* CURVE resources */
#define IfmNcurveTitle		IfmCurveStrings[0]	/* string:  ""		*/
#define IfmNcurveLabel		IfmCurveStrings[1]	/* string:  ""		*/
#define IfmNlineColor		IfmCurveStrings[2]	/* Pixel:   black	*/
#define IfmNlineStyle		IfmCurveStrings[3]	/* int:	    solid	*/
#define IfmNlineWidth		IfmCurveStrings[4]	/* int:	    1		*/
#define IfmNmarkerColor		IfmCurveStrings[5]	/* Pixel:   black	*/
#define IfmNmarkerType		IfmCurveStrings[6]	/* int:	    cross	*/
#define IfmNmarkerSize		IfmCurveStrings[7]	/* int:	    3 pixel	*/
#define IfmNvisible		IfmCurveStrings[8]	/* bool:    true	*/
#define IfmNpermanent		IfmCurveStrings[9]	/* bool:    false	*/
#define IfmNexpression		IfmCurveStrings[10]	/* string:  ""		*/
#define IfmNstartTime		IfmCurveStrings[11]	/* double:  0.		*/
#define IfmNendTime		IfmCurveStrings[12]	/* double:  100.	*/

typedef void (*IfmDiagramFormatProc) (char buf[256], int maxchars, double value, int do_x, void* ptr);

IFM_FUNCPROTOBEGIN

/* Diagrams (v 5.050) */

	/* Diagram specific resources */
extern const char* const IfmDiagramStrings[];
extern const char* const IfmCurveStrings[];

	/* Create a new diagram window */
extern IfmDiagram IfmDiagramCreate (IfmHandle handle, Widget parent, const char* title);
	/* Destroy a diagram */
extern void IfmDiagramDestroy (IfmDiagram handle);
	/* Serialize a diagram */
extern void IfmDiagramSerialize (IfmDiagram pDiagram, IfmArchive pArchive);
	/* Get the diagram's XmForm widget */
extern Widget IfmDiagramGetWidget (IfmDiagram handle);
	/* Show or hide the diagram */
extern void IfmDiagramShow (IfmDiagram handle, IfmBool show_window);
	/* Set diagram properties */
extern void IfmDiagramVaGetValues (IfmDiagram handle, const char* res_name, ...);
	/* Query diagram properties */
extern void IfmDiagramVaSetValues (IfmDiagram handle, const char* res_name, ...);
	/* Add a curve to the diagram */
extern int IfmDiagramAddCurve (IfmDiagram handle, IfmCurve curve);
	/* Remove a curve to the diagram */
extern int IfmDiagramRemoveCurve (IfmDiagram handle, IfmCurve curve);
  	/* Remove all curves from the diagram */
extern int IfmDiagramRemoveAllCurves (IfmDiagram handle, IfmBool perm_only);
	/* Find a curve in the diagram by name */
extern IfmCurve IfmDiagramFindCurve (IfmDiagram handle, const char* name);
	/* Set label formatting function */
extern IfmDiagramFormatProc IfmDiagramSetFormatter (IfmDiagram handle, IfmDiagramFormatProc proc, void* client_data);
	/* Redraw the diagram with current settings */
extern void IfmDiagramRedraw (IfmDiagram handle, IfmBool draw_immediate);
	/* Serializing a diagram (no curves) */
extern void IfmioDiagram(IfmArchive pArc, IfmDiagram pDiagram);

	/* Create a new diagram curve, unique name, optional number of points
	   to avoid reallocation if known */
extern IfmCurve IfmCurveCreate (IfmHandle handle, const char* name, int points);
	/* Add a further reference to the curve - the curve will not be freed
	   even if no diagram holds the curve (hidden curves) */
extern int IfmCurveAddRef (IfmCurve curve);
	/* Release reference to the curve - as long as other references
	   exist, the curve will not be freed! returns the number of 
	   remaining references */
extern int IfmCurveRelease (IfmCurve curve);
	/* Set curve properties */
extern void IfmCurveVaSetValues (IfmCurve curve, const char* res_name, ...);
	/* Query curve properties */
extern void IfmCurveVaGetValues (IfmCurve curve, const char* res_name, ...);
	/* Add a single point to the curve */
extern int IfmCurveAddPoint (IfmCurve curve, double x, double y);
	/* Add a multiple points to the curve */
extern int IfmCurveAddPoints (IfmCurve curve, double* x, double* y, int npoints);
	/* Add a multiple coordinate pairs to the curve */
extern int IfmCurveAddPointVector (IfmCurve curve, IfmPoint* xy, int npoints);
	/* Overwrite a single point of the curve */
extern int IfmCurveSetPoint (IfmCurve curve, int index, double x, double y);
	/* Get the number of curve points (n) */
extern int IfmCurveGetNumberOfPoints (IfmCurve curve);
	/* Retrieve a single point of the curve */
extern int IfmCurveGetPoint (IfmCurve curve, int index, double* x, double* y);
	/* Retrieve all points of a curve (x[n], y[n]) */
extern int IfmCurveQueryPoints (IfmCurve curve, double* x, double* y, int start, int count);
	/* Retrieve all points of a curve (xy[n]) */
extern int IfmCurveQueryPointVector (IfmCurve curve, IfmPoint* xy, int start, int count);
	/* Removes a number of points */
extern int IfmCurveRemovePoints (IfmCurve curve, int start, int count);
	/* Removes all points */
extern void IfmCurveClear (IfmCurve curve);
	/* Serializing a curve */
extern void IfmioCurve(IfmArchive pArc, IfmCurve pCurve);

IFM_FUNCPROTOEND

#ifdef __cplusplus

namespace ifm
{
  // Wrapper class for IFM diagram curves (Note: curves have to be handled with reference counting!)
  class diagram_curve
  {
    IfmCurve    curve;
  public:
    diagram_curve() : curve(0) {}
    diagram_curve(IfmHandle doc, const char* name) : curve(IfmCurveCreate(doc, name, 0)) {}
    diagram_curve(const diagram_curve& rhs) : curve(0) { operator=(rhs); }
    ~diagram_curve() { if (curve) IfmCurveRelease(curve); }
    operator IfmCurve() const { return curve; }
    void operator=(const diagram_curve& rhs)
    {
      if (curve)
	IfmCurveRelease(curve);
      curve = rhs.curve;
      if (curve)
	IfmCurveAddRef(curve);
    }
  };

} // namespace ifm

#endif // C++

#endif /* IFM_DIAGRAM_H */

