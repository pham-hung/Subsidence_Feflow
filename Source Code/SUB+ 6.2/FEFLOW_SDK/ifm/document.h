#ifndef IFM_DOCUMENT_H
#define IFM_DOCUMENT_H

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
*  permission of DHI-WASY GmbH.
*
*-----------------------------------------------------------------------------*/

#include "module.h"
#include "graphic.h"

#ifndef IFM_CURRENT_DOCUMENT_VERSION
#define IFM_CURRENT_DOCUMENT_VERSION 0x6212
#endif

#if defined IFM_TARGET_VERSION && IFM_TARGET_VERSION < IFM_CURRENT_DOCUMENT_VERSION
#undef  IFM_CURRENT_DOCUMENT_VERSION
#define IFM_CURRENT_DOCUMENT_VERSION IFM_TARGET_VERSION
#endif

#if IFM_REQUIRED_VERSION < IFM_CURRENT_DOCUMENT_VERSION
#undef  IFM_REQUIRED_VERSION
#define IFM_REQUIRED_VERSION IFM_CURRENT_DOCUMENT_VERSION
#endif

		/* Constants */

typedef enum IfmProblemType {		/* Problem type ... */
  IfmTYPE_SATURATED	= 0,		/* Saturated media (groundwater) */
  IfmTYPE_UNSATURATED	= 1		/* Unsaturated media */
} IfmProblemType;

typedef enum IfmHysteresisIndicatorType {/* Hysteresis indicator type ... */
  IfmDRYING_DIRECTION	= -1,		/* Drying direction */
  IfmNEUTRAL_DIRECTION	= 0,		/* No preferred hysteretic direction */
  IfmWETTING_DIRECTION	= 1		/* Wetting direction */
} IfmHysteresisIndicatorType;

typedef enum IfmHysteresisCurveType {	/* Hysteresis curve type ... */
  IfmWETTING_CURVE	= 0,		/* Wetting curve */
  IfmDRYING_CURVE	= 1		/* Drying curve */
} IfmHysteresisCurveType;

typedef enum IfmProblemClass {		/* Problem class ... */
  IfmPCLS_NO_CLASS       = -1,		/* Illegal problem class */
  IfmPCLS_FLOW           = 0,		/* Separate flow simulation */
  IfmPCLS_MASS_TRANSPORT = 1,		/* Combined flow and mass transport */
  IfmPCLS_HEAT_TRANSPORT = 2,		/* Combined flow and heat transport */
  IfmPCLS_THERMOHALINE	 = 3		/* Combined flow, mass and heat transport */
} IfmProblemClass;

typedef enum IfmParamID
{
    IfmP_INVALID	= -1,	/* Invalid ID */
    IfmP_NONE		= 0,	/* Unused (aligned for start index 1) */

    /* Flow-related material properties (elemental distributions): */
    IfmP_COND		= 100,	/* Transmissivity or conductivity */
    IfmP_CONDX		= 101,	/* Conductivity in x-direction for 3D */
    IfmP_ANIS		= 102,	/* Anisotropy factor */
    IfmP_CONDY		= 103,	/* Conductivity in y-direction for 3D */
    IfmP_ANGL		= 104,	/* Anisotropy angle */
    IfmP_CONDZ		= 105,	/* Conductivity in z-direction for 3D */
    IfmP_BOTT		= 106,	/* Aquifer bottom elevation */
    IfmP_IOFLOW		= 107,	/* In/outflow on top or bottom for 3D */
    IfmP_TOPS		= 108,	/* Aquifer top elevation */
    IfmP_DENS		= 109,	/* Density ratio for 3D and/or thermohaline transport */
    IfmP_STOR		= 110,	/* Storativity (drain- or fillable) or density ratio */
    IfmP_EXPAN		= 111,	/* Volumetric expansion coefficient for heat transport */
    IfmP_COMP		= 112,	/* Storage compressibility */
    IfmP_SOUF		= 113,	/* Source/sink for flow */
    IfmP_TRAF_IN	= 114,	/* Transfer rate for inflow */
    IfmP_TRAF_OUT	= 115,	/* Transfer rate for outflow */
    IfmP_PM_TYPE	= 116,	/* Coded parametric unsaturated model type */
    IfmP_UPORO		= 117,	/* Porosity (used for unsaturated storativity) */
    IfmP_MAX_SAT	= 118,	/* Maximum saturation (Ss) */
    IfmP_RES_SAT	= 119,	/* Residual saturation (Sr) */
    IfmP_FIT_COEFF	= 120,	/* Fitting coefficient in capillary head (A) or (Alpha) */
    IfmP_FIT_EXPO	= 121,	/* Fitting exponent in capillary head curve (n), (B) or (Beta) */
    IfmP_FIT_EXPO2	= 122,	/* Fitting exponent or coefficient in relative conductivity curve (delta) or (A) */
    IfmP_FIT_EXPO3	= 123,	/* Fitting exponent in relative conductivity curve (B) */
    IfmP_AEPH		= 124,	/* Air-entry pressure head */
    IfmP_TRANS_OLD	= 125,	/* Formerly defined transmissivity (do not use!!!) */
    IfmP_TRANS		= 126,	/* Transmissivity */
    IfmP_MAX_SAT_D	= 127,	/* (Ss) - drying curve */
    IfmP_RES_SAT_D	= 128,	/* (Sr) - drying curve */
    IfmP_FIT_COEFF_D	= 129,	/* (A) or (Alpha) - drying curve */
    IfmP_FIT_EXPO_D	= 130,	/* (n), (B) or (Beta) - drying curve */
    IfmP_FIT_EXPO2_D	= 131,	/* (delta) or (A) - drying curve */
    IfmP_FIT_EXPO3_D	= 132,	/* (B) - drying curve */
    IfmP_AEPH_D		= 133,	/* Air-entry pressure head - drying curve */
    IfmP_ANGLE_PHI	= 134,	/* Euler phi-angle for general 3D anisotropy of conductivity */
    IfmP_ANGLE_PSI	= 135,	/* Euler psi-angle for general 3D anisotropy of conductivity */
    IfmP_ANGLE_THETA	= 136,	/* Euler theta-angle for general 3D anisotropy of conductivity */
    IfmP_INACTIVE_ELE	= 137,	/* Inactive elements (pseudo material) */

    /* Mass-related material properties (elemental distributions): */
    IfmP_ATHI		= 200,	/* Aquifer thickness */
    IfmP_PORO		= 201,	/* Porosity */
    IfmP_SORP		= 202,	/* Sorption coefficient */
    IfmP_DIFF		= 203,	/* Molecular diffusion */
    IfmP_LDIS		= 204,	/* Longitudinal dispersivity */
    IfmP_TDIS		= 205,	/* Transverse dispersivity */
    IfmP_DECA		= 206,	/* Decay rate */
    IfmP_SOUT		= 207,	/* Source/sink for transport */
    IfmP_TRAT_IN	= 208,	/* Transfer rate for influxing transport */
    IfmP_TRAT_OUT	= 209,	/* Transfer rate for outfluxing transport */
    IfmP_SORP2		= 210,	/* Additional sorption coefficient for the Freundlich or Langmuir isotherm */
    IfmP_DECA2		= 211,	/* Additional reaction coefficient for Michaelis-Menten mechanism */
    IfmP_DISIfmP_BETA	= 212,	/* Additional dispersion coefficient for nonlinear dispersion */
    IfmP_MULT_DENS	= 213,	/* Multiple (species-dependent) density ratio */
    IfmP_SOLFRAC	= 214,	/* Solid-volume fraction (used instead of porosity for solid-phase species) */

    /* Heat-related material properties (elemental distributions): */
    IfmP_ATHIH		= 300,	/* Aquifer thickness (heat) */
    IfmP_POROH		= 301,	/* Porosity (heat) */
    IfmP_CAPACS		= 302,	/* Volumetric heat capacity of solid */
    IfmP_CONDUCS	= 303,	/* Heat conductivity of solid */
    IfmP_LDISH		= 304,	/* Longitudinal thermo-dispersivity */
    IfmP_TDISH		= 305,	/* Transverse thermo-dispersivity */
    IfmP_SOURCF		= 306,	/* Heat source/sink of fluid */
    IfmP_SOURCS		= 307,	/* Heat source/sink of solid */
    IfmP_TRAH_IN	= 308,	/* Thermo-transfer rate for influxing transport */
    IfmP_TRAH_OUT	= 309,	/* Thermo-transfer rate for outfluxing transport */
    IfmP_CAPACF		= 310,	/* Volumetric heat capacity of fluid */
    IfmP_CONDUCF	= 311,	/* Heat conductivity of fluid */
    IfmP_ANISH		= 312	/* Anisotropy factor of solid heat conductivity */
} IfmParamID;

typedef enum IfmHistoryID {
    IfmHIST_HEAD	= 1,	/* The 'head distribution' window */
    IfmHIST_AVER_M	= 2,	/* The 'average mass distribution' window */
    IfmHIST_LOCA_M	= 3,	/* The 'local mass distribution' window */
    IfmHIST_AVER_H	= 4,	/* The 'average heat distribution' window */
    IfmHIST_LOCA_H	= 5,	/* The 'local heat distribution' window */
    IfmHIST_FFLUX	= 6,	/* The 'fluid flux' window */
    IfmHIST_MFLUX	= 7,	/* The 'mass flux' window */
    IfmHIST_HFLUX	= 8,	/* The 'heat flux' window */
    IfmHIST_ITERA	= 10,	/* Iteration window index */
    IfmHIST_TIMES	= 12,	/* Time step history index */
    IfmHIST_RESIDUAL	= 13,	/* Residual window index */
    IfmHIST_VARIO	= 15,	/* Kriging variogram index */
    IfmHIST_ANA		= 16,	/* Analytical function index */
    IfmHIST_MULTW_FLUX	= 17,	/* Muli-layer well flux window index */
    IfmHIST_BHE		= 18,	/* Borehole heat exchanger window index */
    IfmHIST_IFM		= 19,	/* IFM based diagram window index */
    IfmHIST_FFLUX_I	= 20,	/* The 'integral fluid flux' window */
    IfmHIST_MFLUX_I	= 21,	/* The 'integral mass flux' window */
    IfmHIST_HFLUX_I	= 22,	/* The 'integral heat flux' window */
    IfmHIST_BHE_IO	= 23	/* The Inlet/outlet bhe diagram */
} IfmHistoryID;

typedef enum IfmTimeClass {		/* Time class ... */
  IfmTCLS_STEADY   = 0,			/* Steady flow / steady transport */
  IfmTCLS_UNSTEADY = 1,			/* Fully unsteady flow / unsteady transport */
  IfmTCLS_ST_UNST  = 2			/* Steady flow / unsteady transport */
} IfmTimeClass;

typedef enum IfmProjectionClass {	/* Projection class ... */
  IfmPROJ_UNDEF_PROJ  = -1,		/* Undefined projection */
  IfmPROJ_CONFINED_2D = 0,		/* Horizontal confined 2D aquifer */
  IfmPROJ_PHREATIC_2D = 1,		/* Horizontal phreatic 2D aquifer */
  IfmPROJ_VERTICAL_2D = 2,		/* Vertical confined 2D aquifer */
  IfmPROJ_AXISYM_2D   = 3,		/* Vertical confined axisymmetric */
  IfmPROJ_CONFINED_3D = 4,		/* 3D confined aquifer */
  IfmPROJ_PHREATIC_3D = 5,		/* 3D phreatic aquifer (fixed mesh) */
  IfmPROJ_MOVE_FS_3D  = 6		/* 3D aquifer with movable free surface */
} IfmProjectionClass;

typedef enum IfmAMR {			/* Adaptive Mesh Refinement (AMR) technique ... */
  IfmAMR_NO = 0,			/* Do not use AMR technique */
  IfmAMR_DO = 1				/* Perform AMR technique */
} IfmAMR;

typedef enum IfmMESH {			/* Meshing type ... */
  IfmMSH_TRIA = 0,			/* Triangular element mesh */
  IfmMSH_QUAD = 1			/* Quadrilateral element mesh */
} IfmMESH;

typedef enum IfmMM {			/* Mass matrix properties ... */
  IfmCONSISTENT_MM = 0,			/* consistent mass matrix */
  IfmLUMPED_MM     = 1			/* lumped mass matrix */
} IfmMM;

typedef enum IfmBHEType {		/* BHE type ... */
  IfmTYPE_2U  = 0,			/* Double U-shape BHE type */
  IfmTYPE_1U  = 1,			/* Single U-shape BHE type */
  IfmTYPE_CXA = 2,			/* Coaxial BHE type (annular inlet) */
  IfmTYPE_CXC = 3			/* Coaxial BHE type (centred inlet) */
} IfmBHEType;

typedef enum IfmAMRESTIMATOR {		/* A posteriori error estimators by */
  IfmAMR_ONATE_AND_BUGEDA = 0,		/* ... Onate and Bugeda (1994) */
  IfmAMR_ZIENKIEWICZ_AND_ZHU = 1,	/* ... Zienkiewicz and Zhu (1987-1990) */
  IfmAMR_UNSPECIFIED = 2		/* ... unspecified AMR method (used by IFM calls) */
} IfmAMRESTIMATOR;

typedef enum IfmEQSOLV_TYPE {		/* Equation solving type ... */
  IfmEQSOLV_ITERAT  = 0,		/* Iterative equation solving */
  IfmEQSOLV_DIRECT  = 1			/* Direct equation solving */
} IfmEQSOLV_TYPE;

typedef enum IfmITERSYMEQS {		/* Iterative symmetric equation solver type ... */
  IfmITERSYMEQS_PCG = 0,		/* Conjugate gradient method */
  IfmITERSYMEQS_AMG = 1			/* Algebraic multigrid method */
} IfmITERSYMEQS;

typedef enum IfmITERNONSYMEQS {		/* Iterative nonsymmetric equation solver type ... */
  IfmITERNONSYMEQS_ORTHO = 0,		/* ORTHOMIN method */
  IfmITERNONSYMEQS_GMRES = 1,		/* GMRES method */
  IfmITERNONSYMEQS_CGS = 2,		/* CGS method */
  IfmITERNONSYMEQS_BICGSTAB = 3,	/* BICGSTAB method */
  IfmITERNONSYMEQS_BICGSTABP = 4,	/* BICGSTABP method */
  IfmITERNONSYMEQS_AMG = 5		/* AMG method */
} IfmITERNONSYMEQS;

typedef enum IfmUFORM {			/* Forms of the Richards equation ... */
  IfmUFORM_H = 0,			/* Standard h-based form */
  IfmUFORM_MIXED = 1,			/* Mixed s-h form */
  IfmUFORM_VARSUB = 2			/* Variable substitution form */
} IfmUFORM;

typedef enum IfmCAPA {			/* Type of derivation of the capacity term ... */
  IfmCAPA_CSS = 0,			/* Chord-slope scheme */
  IfmCAPA_ANA = 1,			/* Analytical scheme */
  IfmCAPA_ANA_TCE = 2			/* Time-centred analytic scheme */
} IfmCAPA;

typedef enum IfmICM {			/* Type of weighting for unsaturated problems ... */
  IfmICM_CW = 0,			/* Central weighting */
  IfmICM_UPW = 1			/* Upstream weighting */
} IfmICM;

typedef enum IfmCPS {			/* Error-checking options for unsaturated problems ... */
  IfmCPS_DONT = 0,			/* Don't check capillary head and saturation error; if applicable, check residual */
  IfmCPS_DO = 1,			/* Check capillary head and saturation error; if applicable, check residual */
  IfmCPS_OMITRES = 2,			/* Don't check capillary head and saturation error; don't check residual */
  IfmCPS_OMITRES_DO = 3			/* Check capillary head and saturation error; don't check residual (introduced in 6.1) */
} IfmCPS;

typedef enum IfmUS {			/* Iteration method used for unsaturated problems ... */
  IfmUS_PICARD = 0,			/* Picard iteration scheme */
  IfmUS_NEWTON = 1			/* Newton iteration scheme */
} IfmUS;

typedef enum IfmKTS {			/* Time stepping kind */
  IfmKTS_PCS = 0,			/* Predictor-corrector scheme */
  IfmKTS_CTS = 1			/* Constant time stepping scheme */
} IfmKTS;

typedef enum IfmPCS {			/* Method of predictor-corrector time stepping */
  IfmPCS_FEBE = 0,			/* Forward Euler/Backward Euler (FE/BE) */
  IfmPCS_ABTR = 1			/* Adams-Bashforth/Trapezoid Rule (AB/TR) */
} IfmPCS;

typedef enum IfmDMN {			/* Dimension of problem ... */
  IfmNDM_2D = 2,			/* Two-dimensional problem to solve */
  IfmNDM_3D = 3				/* Three-dimensional problem to solve */
} IfmDMN;

typedef enum IfmBC {			/* Boundary conditions (BC) ... */
  IfmBC_NONE           = 0,		/* No boundary conditions */
  IfmBC_DIRICHLET      = 1,		/* 1st kind (Dirichlet) boundary conditions */
  IfmBC_NEUMANN        = 2,		/* 2nd kind (Neumann) boundary conditions */
  IfmBC_CAUCHY         = 3,		/* 3rd kind (Cauchy) boundary conditions */
  IfmBC_SINGLE_WELL    = 4,		/* 4th kind (Single well) boundary conditions */
  IfmBC_GRADIENT_FTYPE = 5,		/* Gradient-type 2nd kind (Neumann) B.C. for
					   unsaturated flow */
  IfmBC_NO             = IfmBC_NONE	/* for backward compatibility */
} IfmBC;

typedef enum IfmBC_SPEC {		/* BC specifications ... */
  IfmNONINTEGRAL_BC	= 0,		/* Non-integrated B.C. flux option */
  IfmINTEGRAL_BC	= 1		/* Integrated B.C. flux option */
} IfmBC_SPEC;

typedef enum IfmBCC {			/* Boundary constraints (BCC) ... */
  IfmBCC_NONE           = 0,		/* No boundary constraints */
  IfmBCC_DIRICHLET      = 1,		/* 1st kind (Dirichlet) constraint conditions */
  IfmBCC_NEUMANN        = 2,		/* 2nd kind (Neumann) constraint conditions */
  IfmBCC_CAUCHY         = 3,		/* 3rd kind (Cauchy) constraint conditions */
  IfmBCC_SINGLE_WELL    = 4,		/* 4th kind (Single well) constraint conditions */
  IfmBCC_GRADIENT_FTYPE = 5,		/* Gradient-type 2nd kind constraint B.C. */
  IfmBCC_SPECIAL_3RD_BCC= 6,		/* Special 3rd kind flow head B.C.'s constraint */
  IfmBCC_NO             = IfmBCC_NONE	/* for backward compatibility */
} IfmBCC;

typedef enum IfmBCC_TYPE {		/* Boundary constraint types ... */
  IfmMIN_BCC_TYPE	= 0,		/* Minimum constraint */
  IfmMAX_BCC_TYPE	= 1,		/* Maximum constraint */
  IfmHMIN_BCC_TYPE	= 2,		/* Head minimum constraint (for transport) */
  IfmHMAX_BCC_TYPE	= 3		/* Head maximum constraint (for transport) */
} IfmBCC_TYPE;

typedef enum IfmMLW_ATTR {		/* Multi-layer well attributes ... */
  IfmMLW_RATE		= 0,		/* Well rate value [m^3/d] */
  IfmMLW_BCC_HMIN	= 1,		/* Minimum hydraulic head constraint value [m^3/d] or NaN if n/a */
  IfmMLW_BCC_HMAX	= 2,		/* Maximum hydraulic head constraint value [m^3/d] or NaN if n/a */
} IfmMLW_ATTR;

typedef enum IfmPM {			/* Parametric model types for unsaturated problems ... */
   IfmPM_VAN_GENUCHTEN	= 0,		/* Van Genuchten-Mualem model */
   IfmPM_BROOKS_COREY	= 1,		/* Brooks-Corey model */
   IfmPM_HAVERKAMP	= 2,		/* Haverkamp et al. model */
   IfmPM_EXPONENTIAL	= 3,		/* Exponential model */
   IfmPM_LINEAR         = 4,		/* Linear model */
   IfmPM_VG_MODIFIED	= 5,		/* Van Genuchten modified parameter model */
   IfmPM_SPLINES	= 6		/* Splines parameter model */
} IfmPM;

typedef enum IfmDOC_STATE {		/* Document related states */
  IfmSTATE_ENABLED	= 0,		/* The module is or becomes enabled */
  IfmSTATE_DISABLED	= 1		/* The module is or becomes disabled */
} IfmDOC_STATE;

typedef enum IfmSEL_TYPE {		/* Selection types ... */
  IfmSEL_NODAL = 0,			/* Nodal selection */
  IfmSEL_ELEMENTAL = 1,			/* Elemental selection */
  IfmSEL_INVALID = -1			/* Invalid selection type */
} IfmSEL_TYPE;

typedef struct IfmBcData {		/* Definition of boundary conditions (B.C.) */
  long	code;				/* B.C. type, stationarity, contraint flags, ... */
  int	count;				/* Number of values */
  double* values;			/* Values */ 
} IfmBcData;

typedef enum IfmSPLINE_CURVETYPE {	/* Definition of spline curve type */
  IfmSPL_SAT_FUNC	= 0,		/* Saturation spline function */
  IfmSPL_COND_FUNC	= 1		/* Conductivity spline function */
} IfmSPLINE_CURVETYPE;

typedef enum IfmSPLINE_METHODTYPE {	/* Definition of spline method type */
  IfmCUBIC_INT_SPL	= 0,		/* Cubic interpolating spline */
  IfmCUBIC_MONO_SPL	= 1,		/* Cubic monotone spline */
  IfmCUBIC_SMOOTH_SPL	= 2		/* Cubic smoothing monotonic spline */
} IfmSPLINE_METHODTYPE;

typedef struct IfmSpline {		/* Definition of basic spline dataset */
  char   name[128];			/* Name of spline function */
  int    curve_type;			/* Spline curve type:  IfmSPL_SAT_FUNC  | IfmSPL_COND_FUNC  */
  int    spl_type;			/* Spline method type: IfmCUBIC_INT_SPL | IfmCUBIC_MONO_SPL */
  int    nknt;				/* Number of knots applied to the spline interpolation */
  double *x;				/* x-coordinates of knots [nknt] */
  double *y;				/* y-coordinates of knots [nknt] */
} IfmSpline;

typedef struct IfmSpline2 {		/* Definition of basic spline dataset */
  int	 sid;				/* Unique ID of a spline curve */
  char   name[128];			/* Name of spline function */
  int    curve_type;			/* Spline curve type:  IfmSPL_SAT_FUNC  | IfmSPL_COND_FUNC  */
  int    spl_type;			/* Spline method type: IfmCUBIC_INT_SPL | IfmCUBIC_MONO_SPL */
  int    nknt;				/* Number of knots applied to the spline interpolation */
  double *x;				/* x-coordinates of knots [nknt] */
  double *y;				/* y-coordinates of knots [nknt] */
  double *stdev;			/* Standard deviation at knots [nknt] if available (is used for smoothing spline only) */
} IfmSpline2;

typedef enum IfmInterpolationKind {	/* Kind of interpolation */
  IfmINTERPOL_DEFAULT,			/* User-defined interpolation (through problem editor) */
  IfmINTERPOL_CONST,			/* No interpolation - constant from point to point */
  IfmINTERPOL_LINEAR,			/* Linear interpolation between points */
  IfmINTERPOL_AKIMA,			/* AKIMA interpolation */
  IfmINTERPOL_AKIMA2			/* AKIMA interpolation (smoother) */
} IfmInterpolationKind;

typedef enum IfmContentType {		/* Type of content */
  IfmTOTAL_VOLUME,			/* Total volume */
  IfmVOID_VOLUME,			/* Void volume */
  IfmFLUID_CONTENT,			/* Fluid content */
  IfmDILUTED_MASS,			/* Diluted mass (fluid phase) */
  IfmSORBED_MASS,			/* Sorbed mass (solid phase) */
  IfmENERGY_FLUID,			/* Energy of fluid phase */
  IfmENERGY_SOLID,			/* Energy of solid phase */
  IfmENERGY_TOTAL			/* Total energy content */
} IfmContentType;

typedef enum IfmGravityDirection {	/* Gravity direction */
  IfmGRAVITY_DIM_X,			/* acting along x-axis */
  IfmGRAVITY_DIM_Y,			/* acting along y-axis */
  IfmGRAVITY_DIM_Z			/* acting along z-axis */
} IfmGravityDirection;

typedef enum IfmSmoothVectorType {	/* Smoothing vector types */
  IfmSMOOTH_DEFAULT,			/* Smooth by null vector */
  IfmSMOOTH_BY_HEAD,			/* Smooth by head vector */
  IfmSMOOTH_BY_MASS,			/* Smooth by mass vector */
  IfmSMOOTH_BY_HEAT			/* Smooth by heat vector */
} IfmSmoothVectorType;

typedef struct _IfmBudget IfmBudget;	/* Budget evaluation structure */

typedef struct IfmBudgetComponents {	/* Budget components evaluation structure */
  double total_flux;			/* Total budget flux component */
  double boundary_flux;			/* Boundary budget flux component */
  double area_flux;			/* Area budget flux component */
} IfmBudgetComponents;

typedef struct IfmBudgetComponentsEx {	/* Budget components evaluation structure */
  double border_in;		/* Border budget component */
  double border_out;
  double bulk_in;		/* Distributed source/sink budget component */
  double bulk_out;
  double dirichlet_in;		/* BC Dirichlet budget component (1st kind) */
  double dirichlet_out;
  double neumann_in;		/* BC Neumann budget component (2nd kind) */
  double neumann_out;
  double cauchy_in;		/* BC Cauchy budget component (3rd kind) */
  double cauchy_out;
  double well_in;		/* Well budget component (4th kind) */
  double well_out;
  double conv_in;		/* Convective budget component */
  double conv_out;		
} IfmBudgetComponentsEx;

typedef enum _IfmRefinement {
  IfmAMR_KEEP,				/* Neither refinement nor derefinement */
  IfmAMR_REFINE,			/* Mark element for refinement */
  IfmAMR_DEREFINE,			/* Mark element for derefinement */
  IfmAMR_NOREFINE = IfmAMR_KEEP		/* Alias for IfmAMR_KEEP */
} IfmRefinement;

typedef enum _IfmSpeciesPhaseType {	/* Phase types for multispecies transport */
  IfmFLUID_PHASE,			/* Fluid phase type */
  IfmSOLID_PHASE			/* Solid phase type */
} IfmSpeciesPhaseType;

typedef enum _IfmSpeciesKineticsType {	/* Kinetics types for multispecies transport */
  IfmKM_DEGRADATION,			/* Degardation-type reaction kinetics type */
  IfmKM_ARRHENIUS,			/* Arrhenius-type reaction kinetics type */
  IfmKM_MONOD,				/* Monod-type reaction kinetics type */
  IfmKM_USER_SPECIFIED			/* User-specified reaction kinetics type */
} IfmSpeciesKineticsType;

#define IfmALL_ELEMENTS	-1		/* Used as index for indicating all elements */
#define IfmALL_NODES	-1		/* Used as index for indicating all nodes */

typedef enum _IfmFractureType {		/* Fracture element type */
  IfmALL_FRAC_TYPES = -1,		/* All fracture types */
  IfmFRAC_1D        = 0,		/* One-dimensional (bar) fracture element type */
  IfmFRAC_2D_TRI    = 1,		/* Two-dimensional triangular fracture element type */
  IfmFRAC_2D_QUA    = 2			/* Two-dimensional quadrilateral fracture element type */
} IfmFractureType;

typedef enum _IfmFractureMode {		/* Fracture element selection mode */
  IfmALL_FRAC_MODES = -1,		/* All fracture selection modes */
  IfmFRAC_H         = 0,		/* Horizontal fracture selection mode */
  IfmFRAC_V         = 1,		/* Vertical fracture selection mode */
  IfmFRAC_A         = 2			/* Arbitrary fracture selection mode */
} IfmFractureMode;

typedef enum _IfmFractureLaw {		/* Fracture element flow law */
  IfmALL_FRAC_LAWS = -1,		/* All fracture flow laws */
  IfmDARCY_LAW     = 0,			/* Darcy flow equation */
  IfmHP_LAW        = 1,			/* Hagen-Poiseuille flow equation */
  IfmMANNING_LAW   = 2			/* Manning-Strickler flow equation */
} IfmFractureLaw;

typedef struct _IfmFracNodes {		/* Node array for a fracture element */
  int   nbn;				/* Number of nodes per fracture element (max 4) */
  int	nop[4];				/* Nodal incidence */
} IfmFracNodes;

typedef struct _IfmVTriplet {		/* Velocity triplet */
  double vx;				/* Velocity x-component */
  double vy;				/* Velocity y-component */
  double vz;				/* Velocity z-component (applicable in 3D) */
} IfmVTriplet;

typedef struct _IfmMLWInfo {		/* Multi-layer well information */
  int	      size;			/* Size of this structure */
  int	      id;			/* Identifier (index) for multilayer well */

  double      radius;			/* Radius of multilayer well */
  double      top_elev;			/* Top-z of multilayer well */
  double      bottom_elev;		/* Bottom-z of multilayer well */
  const char* name;			/* Optional well name */

  /* Derived information */
  int	      top_node;			/* Top node of multilayer well */
  int	      bottom_node;		/* Bottom node of multilayer well */
} IfmMLWInfo;

		/* Special handle type */
typedef IfmHandle IfmDocument;

IFM_FUNCPROTOBEGIN

extern int IfmDocumentVersion (IfmHandle);

extern void IfmDocumentSetUserData (IfmHandle, IfmPointer);
extern IfmPointer IfmDocumentGetUserData (IfmHandle);

extern IfmBool IfmDocumentSetEnabled (IfmHandle, IfmBool bEnable);
extern IfmBool IfmDocumentIsEnabled (IfmHandle);

extern void    IfmDocumentSetModified (IfmHandle, IfmBool bModified);
extern IfmBool IfmDocumentIsModified (IfmHandle);

extern void IfmSetSimulationControlFlag (IfmHandle, int nMode);
extern int IfmGetSimulationControlFlag (IfmHandle);

extern int IfmGetLoadVersion (IfmHandle);
extern int IfmGetSaveVersion (IfmHandle);
extern void IfmSetSaveVersion (IfmHandle, int);

extern const char* IfmGetProblemPath (IfmHandle);
extern const char* IfmGetProblemTitle (IfmHandle);

extern int IfmGetProblemType (IfmHandle);
extern int IfmGetProblemClass (IfmHandle);
extern int IfmGetTimeClass (IfmHandle);
extern int IfmGetProblemProjection (IfmHandle);
extern int IfmGetAMRType (IfmHandle);
extern void IfmSetAMRType (IfmHandle, int);
extern int IfmGetMeshType (IfmHandle);
extern void IfmSetMeshType (IfmHandle, int);
extern int IfmGetNumberOfDimensions (IfmHandle);
extern int IfmGetNumberOfNodes (IfmHandle);
extern int IfmGetNumberOfNodesPerSlice (IfmHandle);
extern int IfmGetNumberOfElements (IfmHandle);
extern int IfmGetNumberOfElementsPerLayer (IfmHandle);
extern int IfmGetNumberOfNodesPerElement (IfmHandle);
extern int IfmGetNumberOfNodesPerElement2D (IfmHandle);
extern int IfmGetNumberOfSlices (IfmHandle);
extern int IfmGetCurrentSliceNumber (IfmHandle);
extern int IfmGetNumberOfLayers (IfmHandle);
extern int IfmGetCurrentLayerNumber (IfmHandle);
extern int IfmGetNode (IfmHandle, int, int);

extern int IfmGetEquationSolvingType (IfmHandle);
extern void IfmSetEquationSolvingType (IfmHandle, int);
extern int IfmGetIterativeSymEquationSolverType (IfmHandle);
extern void IfmSetIterativeSymEquationSolverType (IfmHandle, int);
extern int IfmGetIterativeNonSymEquationSolverType (IfmHandle);
extern void IfmSetIterativeNonSymEquationSolverType (IfmHandle, int);
extern int IfmGetRichardsEquationFormType (IfmHandle);
extern void IfmSetRichardsEquationFormType (IfmHandle, int);
extern int IfmGetUnsatDerivativeCapaType (IfmHandle);
extern void IfmSetUnsatDerivativeCapaType (IfmHandle, int);
extern int IfmGetUnsatWeightingType (IfmHandle);
extern void IfmSetUnsatWeightingType (IfmHandle, int);
extern int IfmGetUnsatErrorCheckOption (IfmHandle);
extern void IfmSetUnsatErrorCheckOption (IfmHandle, int);
extern int IfmGetUnsatIterationMethod (IfmHandle);
extern void IfmSetUnsatIterationMethod (IfmHandle, int);

extern double IfmGetOriginX (IfmHandle);
extern double IfmGetOriginY (IfmHandle);
extern double IfmGetOriginZ (IfmHandle);
extern double IfmGetExtentX (IfmHandle);
extern double IfmGetExtentY (IfmHandle);
extern double IfmGetExtentZ (IfmHandle);
extern void   IfmGetExtents (IfmHandle, double* xmin, double* xmax, double* ymin, 
			     double* ymax, double* zmin, double* zmax);
extern double IfmGetX (IfmHandle, int);
extern double IfmGetY (IfmHandle, int);
extern double IfmGetZ (IfmHandle, int);
extern void   IfmSetX (IfmHandle, int, double);
extern void   IfmSetY (IfmHandle, int, double);
extern void   IfmSetZ (IfmHandle, int, double);
extern double IfmGetZValueAtXYSlice (IfmHandle hdl, double x, double y, int slc, IfmBool *ine);
extern void   IfmUpdateElementExtents (IfmHandle hdl);
extern IfmBool IfmAllowNodeMovement (IfmDocument pDoc, int nNode, double x, double y);

extern double IfmGetAbsoluteSimulationTime (IfmHandle);
extern double IfmGetInitialTimeIncrement (IfmHandle);
extern void IfmSetInitialTimeIncrement (IfmHandle, double);
extern double IfmGetFinalSimulationTime (IfmHandle);
extern void IfmSetFinalSimulationTime (IfmHandle, double);
extern double IfmGetCurrentTimeIncrement (IfmHandle);
extern IfmBool IfmIsTimeStepRejected (IfmDocument pDoc);
extern double IfmGetTimeSteppingErrorTolerance (IfmHandle);
extern void IfmSetTimeSteppingErrorTolerance (IfmHandle, double);
extern int IfmGetTimeSteppingKind (IfmHandle);
extern void IfmSetTimeSteppingKind (IfmHandle, int);
extern int IfmGetPredictorCorrectorMethod (IfmHandle);
extern void IfmSetPredictorCorrectorMethod (IfmHandle, int);
extern double IfmGetPredictorCorrectorTimeStepIncreasingRate (IfmHandle);
extern void IfmSetPredictorCorrectorTimeStepIncreasingRate (IfmHandle, double);
extern double IfmGetPredictorCorrectorTimeStepMaximumSize (IfmHandle);
extern void IfmSetPredictorCorrectorTimeStepMaximumSize (IfmHandle, double);

extern int IfmGetNumberOfValidGroups (IfmHandle);
extern int IfmGetMaximumNumberOfGroups (IfmHandle);
extern int IfmIsNodeInGroup (IfmHandle, int, int);
extern double IfmGetFlowValueOfGroupIdAtCurrentTime (IfmHandle, int);
extern double IfmGetMassValueOfGroupIdAtCurrentTime (IfmHandle, int);
extern double IfmGetHeatValueOfGroupIdAtCurrentTime (IfmHandle, int);

extern int IfmGetBcFlowType (IfmHandle, int);
extern int IfmGetBcFlowTimeDependency (IfmHandle, int);
extern double IfmGetBcFlowValue (IfmHandle, int);
extern int IfmGetBcMassType (IfmHandle, int);
extern int IfmGetBcMassTimeDependency (IfmHandle, int);
extern double IfmGetBcMassValue (IfmHandle, int);
extern int IfmGetBcHeatType (IfmHandle, int);
extern int IfmGetBcHeatTimeDependency (IfmHandle, int);
extern double IfmGetBcHeatValue (IfmHandle, int);

extern int IfmGetBccFlowType (IfmHandle, int);
extern IfmBool IfmIsBccFlowSet (IfmHandle, int, int);
extern int IfmGetBccFlowTimeDependency (IfmHandle, int, int);
extern double IfmGetBccFlowValue (IfmHandle, int, int);
extern int IfmGetBccMassType (IfmHandle, int);
extern IfmBool IfmIsBccMassSet (IfmHandle, int, int);
extern int IfmGetBccMassTimeDependency (IfmHandle, int, int);
extern double IfmGetBccMassValue (IfmHandle, int, int);
extern int IfmGetBccHeatType (IfmHandle, int);
extern IfmBool IfmIsBccHeatSet (IfmHandle, int, int);
extern int IfmGetBccHeatTimeDependency (IfmHandle, int, int);
extern double IfmGetBccHeatValue (IfmHandle, int, int);

extern double IfmGetMatConductivityValue2D (IfmHandle, int);
extern double IfmGetMatXConductivityValue3D (IfmHandle, int);
extern double IfmGetMatYConductivityValue3D (IfmHandle, int);
extern double IfmGetMatZConductivityValue3D (IfmHandle, int);
extern double IfmGetMatFlowRechargeValue (IfmHandle, int);
extern double IfmGetResultsFlowHeadValue (IfmHandle, int);
extern double IfmGetResultsFlowHeadPreviousTimeValue (IfmHandle, int);
extern double IfmGetResultsFlowPressureValue (IfmHandle, int);
extern double IfmGetResultsFlowSaturationValue (IfmHandle, int);
extern double IfmGetResultsFlowMoistureContentValue (IfmHandle, int);
extern double IfmGetResultsTransportMassValue (IfmHandle, int);
extern double IfmGetResultsTransportMassPreviousTimeValue (IfmHandle, int);
extern double IfmGetResultsTransportHeatValue (IfmHandle, int);
extern double IfmGetResultsTransportHeatPreviousTimeValue (IfmHandle, int);

extern int IfmGetMatUnsatModelType (IfmHandle, int);
extern double IfmGetMatUnsatPorosity (IfmHandle, int);
extern double IfmGetMatUnsatMaximumSaturation (IfmHandle, int);
extern double IfmGetMatUnsatResidualSaturation (IfmHandle, int);
extern double IfmGetMatUnsatFittingCoefficient (IfmHandle, int);
extern double IfmGetMatUnsatFittingExponent (IfmHandle, int);
extern double IfmGetMatUnsatFittingExponent2 (IfmHandle, int);
extern double IfmGetMatUnsatFittingExponent3 (IfmHandle, int);
extern double IfmGetMatUnsatAirEntryPressureHead (IfmHandle, int);

extern double IfmGetMatAnisotropyFactor2D (IfmHandle, int);
extern double IfmGetMatAnisotropyAngle2D (IfmHandle, int);
extern double IfmGetMatBottom2D (IfmHandle, int);
extern double IfmGetMatTops2D (IfmHandle, int);
extern double IfmGetMatFlowStorativity (IfmHandle, int);
extern double IfmGetMatFlowDensityRatio (IfmHandle, int);
extern double IfmGetMatFlowExpansionCoeff (IfmHandle, int);
extern double IfmGetMatFlowCompressibility (IfmHandle, int);
extern double IfmGetMatFlowSinkSource (IfmHandle, int);
extern double IfmGetMatFlowTransferIn (IfmHandle, int);
extern double IfmGetMatFlowTransferOut (IfmHandle, int);

extern double IfmGetMatMassAquiferThickness (IfmHandle, int);
extern double IfmGetMatMassPorosity (IfmHandle, int);
extern double IfmGetMatMassSorptionCoeff1 (IfmHandle, int);
extern double IfmGetMatMassSorptionCoeff2 (IfmHandle, int);
extern double IfmGetMatMassDiffusion (IfmHandle, int);
extern double IfmGetMatMassLongDispersivity (IfmHandle, int);
extern double IfmGetMatMassTransDispersivity (IfmHandle, int);
extern double IfmGetMatMassDecayRate (IfmHandle, int);
extern double IfmGetMatMassDecayRate2 (IfmHandle, int);
extern double IfmGetMatMassSinkSource (IfmHandle, int);
extern double IfmGetMatMassTransferIn (IfmHandle, int);
extern double IfmGetMatMassTransferOut (IfmHandle, int);

extern double IfmGetMatHeatAquiferThickness (IfmHandle, int);
extern double IfmGetMatHeatPorosity (IfmHandle, int);
extern double IfmGetMatHeatSolidCapacity (IfmHandle, int);
extern double IfmGetMatHeatFluidCapacity (IfmHandle, int);
extern double IfmGetMatHeatSolidConductivity (IfmHandle, int);
extern double IfmGetMatHeatFluidConductivity (IfmHandle, int);
extern double IfmGetMatHeatLongDispersivity (IfmHandle, int);
extern double IfmGetMatHeatTransDispersivity (IfmHandle, int);
extern double IfmGetMatHeatFluidSinkSource (IfmHandle, int);
extern double IfmGetMatHeatSolidSinkSource (IfmHandle, int);
extern double IfmGetMatHeatTransferIn (IfmHandle, int);
extern double IfmGetMatHeatTransferOut (IfmHandle, int);

extern void IfmSetBcFlowValueAtCurrentTime (IfmHandle, int, double);
extern int  IfmSetBcFlowTypeAndValueAtCurrentTime (IfmHandle, int, int, int, double);
extern int  IfmSetBcFlowTypeAndValueAtCurrentTime2 (IfmHandle, int, int, int, int, double);
extern int  IfmSetBcPressureValueAtCurrentTime (IfmHandle, int, double);
extern int  IfmSetBcSeepageFaceAtCurrentTime (IfmHandle, int);
extern int  IfmSetBcSaturationValueAtCurrentTime (IfmHandle, int, double);
extern int  IfmSetBcMoistureContentValueAtCurrentTime (IfmHandle, int, double);
extern void IfmSetBcMassValueAtCurrentTime (IfmHandle, int, double);
extern int  IfmSetBcMassTypeAndValueAtCurrentTime (IfmHandle, int, int, int, double);
extern int  IfmSetBcMassTypeAndValueAtCurrentTime2 (IfmHandle, int, int, int, int, double);
extern void IfmSetBcHeatValueAtCurrentTime (IfmHandle, int, double);
extern int  IfmSetBcHeatTypeAndValueAtCurrentTime (IfmHandle, int, int, int, double);
extern int  IfmSetBcHeatTypeAndValueAtCurrentTime2 (IfmHandle, int, int, int, int, double);

extern void IfmSetBccFlowValueAtCurrentTime (IfmHandle, int, double, int);
extern int IfmSetBccFlowTypeAndValueAtCurrentTime (IfmHandle, int, int, int, double, int);
extern void IfmSetBccMassValueAtCurrentTime (IfmHandle, int, double, int);
extern int IfmSetBccMassTypeAndValueAtCurrentTime (IfmHandle, int, int, int, double, int);
extern void IfmSetBccHeatValueAtCurrentTime (IfmHandle, int, double, int);
extern int IfmSetBccHeatTypeAndValueAtCurrentTime (IfmHandle, int, int, int, double, int);
extern void IfmSetBccFlowValueOfGroupIdAtCurrentTime (IfmHandle, int, double, int);
extern void IfmSetBccMassValueOfGroupIdAtCurrentTime (IfmHandle, int, double, int);
extern void IfmSetBccHeatValueOfGroupIdAtCurrentTime (IfmHandle, int, double, int);

extern void IfmSetBcFlowValueOfGroupIdAtCurrentTime (IfmHandle, int, double);
extern void IfmSetBcMassValueOfGroupIdAtCurrentTime (IfmHandle, int, double);
extern void IfmSetBcHeatValueOfGroupIdAtCurrentTime (IfmHandle, int, double);

extern int    IfmGetNumberOfValidObsPoints (IfmHandle);
extern int    IfmGetTypeOfObsId (IfmHandle, int);
extern double IfmGetXOfObsId (IfmHandle, int);
extern double IfmGetYOfObsId (IfmHandle, int);
extern double IfmGetZOfObsId (IfmHandle, int);
extern double IfmGetFlowValueOfObsIdAtCurrentTime (IfmHandle, int);
extern double IfmGetMassValueOfObsIdAtCurrentTime (IfmHandle, int);
extern double IfmGetHeatValueOfObsIdAtCurrentTime (IfmHandle, int);
extern double IfmGetPressureValueOfObsIdAtCurrentTime (IfmHandle, int);
extern double IfmGetSaturationValueOfObsIdAtCurrentTime (IfmHandle, int);
extern double IfmGetMoistureContentValueOfObsIdAtCurrentTime (IfmHandle, int);

extern double IfmGetResultsFlowHeadValueAtXYZ (IfmHandle, double, double, double, IfmBool*);
extern double IfmGetResultsTransportMassValueAtXYZ (IfmHandle, double, double, double, IfmBool*);
extern double IfmGetResultsTransportHeatValueAtXYZ (IfmHandle, double, double, double, IfmBool*);
extern double IfmGetResultsFlowPressureValueAtXYZ (IfmHandle, double, double, double, IfmBool*);
extern double IfmGetResultsFlowSaturationValueAtXYZ (IfmHandle, double, double, double, IfmBool*);
extern double IfmGetResultsFlowMoistureContentValueAtXYZ (IfmHandle, double, double, double, IfmBool*);

extern double IfmGetResultsFlowHeadValueAtXYSlice (IfmHandle, double, double, int, IfmBool*);
extern double IfmGetResultsTransportMassValueAtXYSlice (IfmHandle, double, double, int, IfmBool*);
extern double IfmGetResultsTransportHeatValueAtXYSlice (IfmHandle, double, double, int, IfmBool*);
extern double IfmGetResultsFlowPressureValueAtXYSlice (IfmHandle, double, double, int, IfmBool*);
extern double IfmGetResultsFlowSaturationValueAtXYSlice (IfmHandle, double, double, int, IfmBool*);
extern double IfmGetResultsFlowMoistureContentValueAtXYSlice (IfmHandle, double, double, int, IfmBool*);

extern IfmBool	IfmIsVelocityFieldPresent (IfmDocument pDoc);
extern double	IfmGetResultsXVelocityValue (IfmDocument pDoc, int node);
extern void	IfmSetXVelocityValue (IfmDocument pDoc, int node, double);
extern double	IfmGetResultsYVelocityValue (IfmDocument pDoc, int node);
extern void	IfmSetYVelocityValue (IfmDocument pDoc, int node, double);
extern double	IfmGetResultsZVelocityValue (IfmDocument pDoc, int node);
extern void	IfmSetZVelocityValue (IfmDocument pDoc, int node, double);
extern double	IfmGetResultsVelocityNormValue (IfmDocument pDoc, int node);
extern double	IfmGetResultsXVelocityValueAtXYZ (IfmDocument pDoc, double x, double y, double z, IfmBool* inside);
extern double	IfmGetResultsYVelocityValueAtXYZ (IfmDocument pDoc, double x, double y, double z, IfmBool* inside);
extern double	IfmGetResultsZVelocityValueAtXYZ (IfmDocument pDoc, double x, double y, double z, IfmBool* inside);

extern void IfmSetMatConductivityValue2D (IfmHandle, int, double);
extern void IfmSetMatXConductivityValue3D (IfmHandle, int, double);
extern void IfmSetMatYConductivityValue3D (IfmHandle, int, double);
extern void IfmSetMatZConductivityValue3D (IfmHandle, int, double);
extern void IfmSetMatFlowRechargeValue (IfmHandle, int, double);
extern void IfmSetResultsFlowHeadValue (IfmHandle, int, double);
extern void IfmSetResultsFlowPressureValue (IfmHandle, int, double);
extern void IfmSetResultsFlowSaturationValue (IfmHandle, int, double);
extern void IfmSetResultsFlowMoistureContentValue (IfmHandle, int, double);
extern void IfmSetResultsTransportMassValue (IfmHandle, int, double);
extern void IfmSetResultsTransportMassIntermediateValue (IfmHandle, int, double);
extern void IfmSetResultsTransportHeatValue (IfmHandle, int, double);

extern void IfmSetMatAnisotropyFactor2D (IfmHandle, int, double);
extern void IfmSetMatAnisotropyAngle2D (IfmHandle, int, double);
extern void IfmSetMatBottom2D (IfmHandle, int, double);
extern void IfmSetMatTops2D (IfmHandle, int, double);
extern void IfmSetMatFlowStorativity (IfmHandle, int, double);
extern void IfmSetMatFlowDensityRatio (IfmHandle, int, double);
extern void IfmSetMatFlowExpansionCoeff (IfmHandle, int, double);
extern void IfmSetMatFlowCompressibility (IfmHandle, int, double);
extern void IfmSetMatFlowSinkSource (IfmHandle, int, double);
extern void IfmSetMatFlowTransferIn (IfmHandle, int, double);
extern void IfmSetMatFlowTransferOut (IfmHandle, int, double);

extern void IfmSetMatUnsatModelType (IfmHandle, int, double);
extern void IfmSetMatUnsatPorosity (IfmHandle, int, double);
extern void IfmSetMatUnsatMaximumSaturation (IfmHandle, int, double);
extern void IfmSetMatUnsatResidualSaturation (IfmHandle, int, double);
extern void IfmSetMatUnsatFittingCoefficient (IfmHandle, int, double);
extern void IfmSetMatUnsatFittingExponent (IfmHandle, int, double);
extern void IfmSetMatUnsatFittingExponent2 (IfmHandle, int, double);
extern void IfmSetMatUnsatFittingExponent3 (IfmHandle, int, double);
extern void IfmSetMatUnsatAirEntryPressureHead (IfmHandle, int, double);

extern void IfmSetMatMassAquiferThickness (IfmHandle, int, double);
extern void IfmSetMatMassPorosity (IfmHandle, int, double);
extern void IfmSetMatMassSorptionCoeff1 (IfmHandle, int, double);
extern void IfmSetMatMassSorptionCoeff2 (IfmHandle, int, double);
extern void IfmSetMatMassDiffusion (IfmHandle, int, double);
extern void IfmSetMatMassLongDispersivity (IfmHandle, int, double);
extern void IfmSetMatMassTransDispersivity (IfmHandle, int, double);
extern void IfmSetMatMassDecayRate (IfmHandle, int, double);
extern void IfmSetMatMassDecayRate2 (IfmHandle, int, double);
extern void IfmSetMatMassSinkSource (IfmHandle, int, double);
extern void IfmSetMatMassTransferIn (IfmHandle, int, double);
extern void IfmSetMatMassTransferOut (IfmHandle, int, double);

extern void IfmSetMatHeatAquiferThickness (IfmHandle, int, double);
extern void IfmSetMatHeatPorosity (IfmHandle, int, double);
extern void IfmSetMatHeatSolidCapacity (IfmHandle, int, double);
extern void IfmSetMatHeatFluidCapacity (IfmHandle, int, double);
extern void IfmSetMatHeatSolidConductivity (IfmHandle, int, double);
extern void IfmSetMatHeatFluidConductivity (IfmHandle, int, double);
extern void IfmSetMatHeatLongDispersivity (IfmHandle, int, double);
extern void IfmSetMatHeatTransDispersivity (IfmHandle, int, double);
extern void IfmSetMatHeatFluidSinkSource (IfmHandle, int, double);
extern void IfmSetMatHeatSolidSinkSource (IfmHandle, int, double);
extern void IfmSetMatHeatTransferIn (IfmHandle, int, double);
extern void IfmSetMatHeatTransferOut (IfmHandle, int, double);

/* For compatibility */
#define IfmDocumentGetModule(pDoc) pDoc
#define IfmDocumentGetGraphic(pDoc) pDoc

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x4709
/* Saving and restoring internal B.C. representation (see two-phase sample) */
extern void IfmGetBcFlowData (IfmHandle, int, IfmBcData*);
extern void IfmSetBcFlowData (IfmHandle, int, const IfmBcData*);
extern void IfmGetBcMassData (IfmHandle, int, IfmBcData*);
extern void IfmSetBcMassData (IfmHandle, int, const IfmBcData*);
extern void IfmGetBcHeatData (IfmHandle, int, IfmBcData*);
extern void IfmSetBcHeatData (IfmHandle, int, const IfmBcData*);
extern void IfmInitBc (IfmHandle, IfmBcData* bcOut);
extern void IfmFreeBc (IfmHandle, IfmBcData* bcInOut);
extern void IfmCopyBc (IfmHandle, IfmBcData* bcOut, const IfmBcData* bcIn);
extern void IfmInterpolateBc (IfmHandle, IfmBcData* bcOut, 
		  const IfmBcData* bcLeft, const IfmBcData* bcRight);

/* Reference distribution access */
extern long   IfmGetNumberOfNodalRefDistr (IfmHandle);
extern long   IfmGetNumberOfElementalRefDistr (IfmHandle);
extern void   IfmGetNodalRefDistrName (IfmHandle, long, char*);
extern void   IfmGetElementalRefDistrName (IfmHandle, long, char*);
extern long   IfmGetNodalRefDistrIdByName (IfmHandle, const char *);
extern long   IfmGetElementalRefDistrIdByName (IfmHandle, const char *);
extern double IfmGetNodalRefDistrValue (IfmHandle, long, long);
extern double IfmGetElementalRefDistrValue (IfmHandle, long, long);
extern void   IfmSetNodalRefDistrValue (IfmHandle, long, long, double);
extern void   IfmSetElementalRefDistrValue (IfmHandle, long, long, double);
extern long   IfmCreateNodalRefDistr (IfmHandle, const char *);
extern long   IfmCreateElementalRefDistr (IfmHandle, const char *);
extern void   IfmDeleteNodalRefDistr (IfmHandle, long);
extern void   IfmDeleteElementalRefDistr (IfmHandle, long);

/* Backward compatibility */
#define IfmGetNumberOfRefDistr	IfmGetNumberOfNodalRefDistr
#define IfmGetRefDistrName	IfmGetNodalRefDistrName
#define IfmGetRefDistrIdByName	IfmGetNodalRefDistrIdByName
#define IfmGetRefDistrValue	IfmGetNodalRefDistrValue
#define IfmSetRefDistrValue	IfmSetNodalRefDistrValue
#define IfmCreateRefDistr	IfmCreateNodalRefDistr
#define IfmDeleteRefDistr	IfmDeleteNodalRefDistr

/* FEM problem border */
extern int	IfmGetNumberOfBorders (IfmHandle pHdl);
extern int	IfmGetNumberOfBorderNodes (IfmHandle pHdl, int nBorder);
extern int	IfmGetBorderNode (IfmHandle pHdl, int nBorder, int nIndex);
extern IfmBool	IfmIsExteriorBorder (IfmHandle pHdl, int nBorder);

extern IfmBool	IfmDeleteFiniteElements (IfmHandle pHdl, int* elist, int le);

/* More AMR functions */
extern double IfmGetAmrErrorTolerance (IfmHandle);
extern void   IfmSetAmrErrorTolerance (IfmHandle, double);

#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x4823
/* Handling of power functions */
extern int	IfmGetPowerCurve (IfmDocument pDoc, int nStartID);
extern int	IfmCreatePowerCurve (IfmDocument pDoc, int nID);
extern IfmBool	IfmDeletePowerCurve (IfmDocument pDoc, int nID);
extern IfmBool  IfmIsPowerCyclic (IfmDocument pDoc, int nID);
extern void	IfmSetPowerCyclic (IfmDocument pDoc, int nID, IfmBool bCyclic);
extern IfmInterpolationKind IfmGetPowerInterpolationKind (IfmDocument pDoc, int nID);
extern void	IfmSetPowerInterpolationKind (IfmDocument pDoc, int nID, IfmInterpolationKind kind);
extern const char* IfmGetPowerComment (IfmDocument pDoc, int nID);
extern void	IfmSetPowerComment (IfmDocument pDoc, int nID, const char* pszComment);
extern int	IfmFindPowerCurve (IfmDocument pDoc, const char* pszComment);
extern int	IfmGetNumberOfPowerPoints (IfmDocument pDoc, int nID);
extern void	IfmGetPowerPoint (IfmDocument pDoc, int nID, int nIndex, double* time, double* value);
extern int	IfmSetPowerPoint (IfmDocument pDoc, int nID, double time, double value);
extern int	IfmDeletePowerPoint (IfmDocument pDoc, int nID, int nIndex);
extern double	IfmInterpolatePowerValue (IfmDocument pDoc, int nID, double time);
#endif 

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x4919
/* Handling of budget evaluation (v 4.919/5.050) */
extern IfmBudget* IfmBudgetFlowCreate (IfmDocument pDoc);
extern IfmBudget* IfmBudgetMassCreate (IfmDocument pDoc);
extern IfmBudget* IfmBudgetHeatCreate (IfmDocument pDoc);
extern double 	  IfmBudgetQueryFlowAtNode (IfmDocument pDoc, IfmBudget* pBudget, int nNode);
extern double 	  IfmBudgetQueryMassAtNode (IfmDocument pDoc, IfmBudget* pBudget, int nNode);
extern double 	  IfmBudgetQueryHeatAtNode (IfmDocument pDoc, IfmBudget* pBudget, int nNode);
extern IfmBool 	  IfmBudgetComponentsQueryFlowAtNode (IfmDocument pDoc, IfmBudget* pBudget,
			int nNode, IfmBudgetComponents* pBudgetComp);
extern IfmBool 	  IfmBudgetComponentsQueryMassAtNode (IfmDocument pDoc, IfmBudget* pBudget,
			int nNode, IfmBudgetComponents* pBudgetComp);
extern IfmBool 	  IfmBudgetComponentsQueryHeatAtNode (IfmDocument pDoc, IfmBudget* pBudget,
			int nNode, IfmBudgetComponents* pBudgetComp);
extern void 	  IfmBudgetClose (IfmDocument pDoc, IfmBudget* pBudget);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x4921
/* Inverse incidence matrix */
extern int	IfmGetNumberOfNodeElements (IfmDocument pDoc, int nNode);
extern int	IfmGetElement (IfmDocument pDoc, int nNode, int nIndex);

/* Backward compatiblity */
extern float	IfmGetExtentX_f (IfmHandle);
extern float	IfmGetExtentY_f (IfmHandle);
extern float	IfmGetExtentZ_f (IfmHandle);
extern float	IfmGetX_f (IfmDocument pDoc, int nNode);
extern float	IfmGetY_f (IfmDocument pDoc, int nNode);
extern float	IfmGetZ_f (IfmDocument pDoc, int nNode);
extern float	IfmGetXOfObsId_f (IfmDocument pDoc, int nObsId);
extern float	IfmGetYOfObsId_f (IfmDocument pDoc, int nObsId);
extern float	IfmGetZOfObsId_f (IfmDocument pDoc, int nObsId);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5063
/* Content computation */
extern double	IfmGetTotalContent (IfmHandle, IfmContentType);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5253
/* Content computation */
extern double   IfmGetElementalContent (IfmHandle, IfmContentType, int);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5063
/* Mesh smoothing */
extern IfmBool	IfmMeshSmoothing (IfmHandle, IfmSmoothVectorType);

/* Gravity direction */
extern IfmGravityDirection IfmGetGravityDirection (IfmHandle, double*);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5069
/* Predictor values */
extern double IfmGetPredictorHeadTimeValue (IfmHandle, int);
extern double IfmGetPredictorMassTimeValue (IfmHandle, int);
extern double IfmGetPredictorHeatTimeValue (IfmHandle, int);

/* Extended functions for unsaturated problems */
extern double IfmGetMatUnsatFittingCoefficientDryingCurve (IfmHandle, int);
extern void IfmSetMatUnsatFittingCoefficientDryingCurve (IfmHandle, int, double);
extern int  IfmGetUnsatHysteresisIndicatorValue (IfmHandle, int);
extern double IfmGetUnsatHysteresisStarValue (IfmHandle, int);
extern double IfmGetFlowSaturationValueAtGivenHead (IfmHandle, int, double);

/* Added exchange measure function */
extern double IfmGetExchangeThicknessAtNode3D (IfmHandle, int, int);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5070
/* Extended functions for control of predictor-corrector solutions */
extern void IfmSetResultsFlowHeadPreviousTimeValue (IfmHandle, int, double);
extern void IfmSetResultsTransportMassPreviousTimeValue (IfmHandle, int, double);
extern void IfmSetResultsTransportHeatPreviousTimeValue (IfmHandle, int, double);
extern double IfmGetAccelerationHeadTimeValue (IfmHandle, int);
extern double IfmGetAccelerationMassTimeValue (IfmHandle, int);
extern double IfmGetAccelerationHeatTimeValue (IfmHandle, int);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5071
/* AMR functions */
extern void          IfmSetAmrElementRefinement (IfmHandle, int nIndex, IfmRefinement flag);
extern IfmRefinement IfmGetAmrElementRefinement (IfmHandle, int nIndex);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5155
/* Search routines */
extern int  IfmFindElementAtXY (IfmHandle, double x, double y, double relax);
extern int  IfmFindNodeAtXY (IfmHandle, double x, double y, double* dist);
extern int  IfmGetNextElement2D (IfmHandle, int nElement, const IfmRect* rcBounds);
extern int  IfmGetNextNode2D (IfmHandle, int nNode, const IfmRect* rcBounds);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5158
/* Anisotropic material functions in 3D */
extern double IfmGetMatAnisotropyAnglePhi (IfmHandle, int);
extern double IfmGetMatAnisotropyAnglePsi (IfmHandle, int);
extern double IfmGetMatAnisotropyAngleTheta (IfmHandle, int);
extern void IfmSetMatAnisotropyAnglePhi (IfmHandle, int, double);
extern void IfmSetMatAnisotropyAnglePsi (IfmHandle, int, double);
extern void IfmSetMatAnisotropyAngleTheta (IfmHandle, int, double);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5161
/* Multipsecies Id */
extern int IfmGetNumberOfSpecies (IfmHandle);
extern int IfmGetSpeciesPhaseType (IfmHandle, int);
extern const char* IfmGetSpeciesName (IfmHandle, int);
extern int IfmGetSpeciesKineticsType (IfmHandle, int);
extern int IfmGetMultiSpeciesId (IfmHandle);
extern void IfmSetMultiSpeciesId (IfmHandle, int);
#endif


#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5253
/* Fracture elements */
extern int IfmGetNumberOfTotalFractureElements (IfmHandle);
extern int IfmGetNumberOf1DFractureElements (IfmHandle);
extern int IfmGetNumberOf2DTriangularFractureElements (IfmHandle);
extern int IfmGetNumberOf2DQuadrilateralFractureElements (IfmHandle);
extern void IfmGetNodalArrayOfFractureElement (IfmHandle, int, IfmFracNodes*);
extern double IfmGetFracArea (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracFlowConductivity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracFlowStorativity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracFlowCompressibility (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracFlowSinkSource (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracFlowDensityRatio (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracFlowExpansionCoeff (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracFlowTransferIn (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracFlowTransferOut (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassPorosity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassSorptionCoeff (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassDiffusion (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassLongDispersivity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassTransDispersivity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassDecayRate (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassSinkSource (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassTransferIn (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracMassTransferOut (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatPorosity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatFluidCapacity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatSolidCapacity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatFluidConductivity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatSolidConductivity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatLongDispersivity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatTransDispersivity (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatFluidSinkSource (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatSolidSinkSource (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatTransferIn (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern double IfmGetFracHeatTransferOut (IfmHandle, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracArea (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracFlowConductivity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracFlowStorativity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracFlowCompressibility (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracFlowSinkSource (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracFlowDensityRatio (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracFlowExpansionCoeff (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracFlowTransferIn (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracFlowTransferOut (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassPorosity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassSorptionCoeff (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassDiffusion (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassLongDispersivity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassTransDispersivity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassDecayRate (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassSinkSource (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassTransferIn (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracMassTransferOut (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatPorosity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatFluidCapacity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatSolidCapacity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatFluidConductivity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatSolidConductivity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatLongDispersivity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatTransDispersivity (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatFluidSinkSource (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatSolidSinkSource (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatTransferIn (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void IfmSetFracHeatTransferOut (IfmHandle, int, double, IfmFractureType, IfmFractureMode, IfmFractureLaw);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5254
/* Extended functions for hysteretic unsaturated problems */
extern int IfmGetUnsatHysteresisCondition (IfmHandle);
extern void IfmSetUnsatHysteresisCondition (IfmHandle);
extern double IfmGetMatUnsatFittingExponentDryingCurve (IfmHandle, int);
extern double IfmGetMatUnsatFittingExponent2DryingCurve (IfmHandle, int);
extern double IfmGetMatUnsatFittingExponent3DryingCurve (IfmHandle, int);
extern void IfmSetMatUnsatFittingExponentDryingCurve (IfmHandle, int, double);
extern void IfmSetMatUnsatFittingExponent2DryingCurve (IfmHandle, int, double);
extern void IfmSetMatUnsatFittingExponent3DryingCurve (IfmHandle, int, double);

/* AMR functions */
extern int IfmGetAMREstimatorType (IfmHandle);
extern void IfmSetAMREstimatorType (IfmHandle, int EstimatorType);

/* Mass matrix functions */
extern int IfmGetMassMatricesFlag (IfmHandle);
extern void IfmSetMassMatricesFlag (IfmHandle, int MMType);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5257
/* Predictor values */
extern void IfmSetPredictorHeadTimeValue (IfmHandle, int, double);
extern void IfmSetPredictorMassTimeValue (IfmHandle, int, double);
extern void IfmSetPredictorHeatTimeValue (IfmHandle, int, double);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5302
extern void IfmSetUnsatHysteresisIndicatorGeneral (IfmHandle, IfmHysteresisIndicatorType);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5308
/* Transfer boundary conditions */
extern int IfmSetCoupledRiverBndNodes (IfmHandle, int, int*, double*, double*);
extern int IfmSetCoupledMassTransBndNodes (IfmHandle, int, int*, double*, double*);
extern int IfmSetCoupledHeatTransBndNodes (IfmHandle, int, int*, double*, double*);
extern IfmBool IfmGetResultsElementalVelocityValuesAtXYZ (IfmHandle, double, double, double, IfmVTriplet*);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5357
/* Enable/Disable spatial index */
extern IfmBool IfmEnableSpatialIndex (IfmHandle hdl, IfmBool bEnableIndex);

/* Spline function dataset */
extern IfmBool IfmGetSplineSaturationFunction (IfmHandle, int, IfmSpline*);
extern IfmBool IfmGetSplineConductivityFunction (IfmHandle, int, IfmSpline*);
extern IfmBool IfmSetSplineSaturationFunction (IfmHandle, int, const IfmSpline*);
extern IfmBool IfmSetSplineConductivityFunction (IfmHandle, int, const IfmSpline*);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5404
/* Spline function Ids */
extern int IfmGetSplineSaturationId (IfmHandle, int, int);
extern int IfmGetSplineConductivityId (IfmHandle, int, int);
extern void IfmSetSplineSaturationId (IfmHandle, int, int, int);
extern void IfmSetSplineConductivityId (IfmHandle, int, int, int);

/* BHE functions */
extern int IfmGetBHENumber (IfmHandle);
extern int IfmGetBHEReferenceNode (IfmHandle, int);
extern double IfmGetBHEHeatInputRate (IfmHandle, int);
extern double IfmGetBHEInletTemperature (IfmHandle, int);
extern double IfmGetBHEOutletTemperature (IfmHandle, int);
extern int IfmGetBHEType (IfmHandle, int);
extern double IfmGetBHEFlowDischarge (IfmHandle, int);
extern double IfmGetReferenceTemperature (IfmHandle);
extern void IfmSetBHEHeatInputRate (IfmHandle, int, double);
extern void IfmSetBHEInletTemperature (IfmHandle, int, double);
extern void IfmSetBHEFlowDischarge (IfmHandle, int, double);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5413
extern IfmBool IfmIsDivergenceFormTransport (IfmHandle);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x5415
extern void IfmResetBHE (IfmHandle);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6001
extern int    IfmCreateFracElement (IfmHandle, int, int, IfmFractureType, IfmFractureMode, IfmFractureLaw);
extern void   IfmDeleteFracElement (IfmHandle, int);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6008 || (IFM_CURRENT_DOCUMENT_VERSION >= 0x5416 && IFM_CURRENT_DOCUMENT_VERSION < 0x5450)
extern int  IfmGetUnsatHysteresisIndicatorValueAtNode (IfmHandle, int);
extern double IfmGetUnsatHysteresisStarValueAtNode (IfmHandle, int, int);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6009
/* New spline function dataset */
extern IfmBool IfmGetSplineSaturationFunction2 (IfmHandle, int, IfmSpline2*);
extern IfmBool IfmGetSplineConductivityFunction2 (IfmHandle, int, IfmSpline2*);
extern int IfmSetSplineSaturationFunction2 (IfmHandle, int, const IfmSpline2*);
extern int IfmSetSplineConductivityFunction2 (IfmHandle, int, const IfmSpline2*);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6071
/* Kernel interface access  */
extern struct IUnknown* IfmDocumentGetInterface (IfmHandle);
/* Efficient budget computation */
extern IfmResult IfmBudgetCompute (IfmHandle, IfmProblemClass nKind, int* pNodes, int nNodes, 
				   double* pNodalBudget, IfmBudgetComponentsEx* pCumulativeBudget);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6103

/* BHE array functions */
extern int IfmGetBHEArrayNumber (IfmHandle);
extern const char* IfmGetBHEArrayName (IfmHandle, int);
extern void IfmSetBHEArrayFlowDischarge (IfmHandle, int, double);
extern void IfmSetBHEArrayInTemperature (IfmHandle, int, double);
extern double IfmGetBHEArrayFlowDischarge (IfmHandle, int);
extern double IfmGetBHEArrayOutTemperature (IfmHandle, int);
extern double IfmGetBHEArrayInTemperature (IfmHandle, int);

#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6104

/* Residual computation */
extern double IfmGetSolutionResidualNorm2 (IfmHandle, IfmProblemClass);
extern double IfmGetSolutionResidualNormMax (IfmHandle, IfmProblemClass);

#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6107

/* Species handling */
extern int IfmAddSpecies (IfmHandle hdl, const char* pszSpeciesName, int nInheritFrom);

#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6158

/* Enable recording of reference distributions */
IfmBool IfmEnableNodalRefDistrRecording (IfmHandle hdl, long rID, IfmBool bEnable);
IfmBool IfmEnableElementalRefDistrRecording (IfmHandle hdl, long rID, IfmBool bEnable);

double IfmIntegrateNodalQuantitiesOfElement (IfmHandle hdl, int nElem, const double* p);

/* Element diameter calculations */
double IfmGetElementDiameter (IfmHandle hdl, int nElem);
double IfmGetFracElementDiameter (IfmHandle hdl, int nElem);

#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6191

  /* Inactive elements */
  int  IfmGetMatElementActive (IfmDocument pDoc, int nElem);
  void IfmSetMatElementActive (IfmDocument pDoc, int nEleb, int nActive);

#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6202

  /* Multi-layer wells */
  IfmBool IfmQueryMultiLayerWellInfo (IfmDocument pDoc, int nNode, IfmMLWInfo* pMLW);

#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6206

  int     IfmGetNumberOfMultiLayerWells (IfmDocument pDoc);
  IfmBool IfmIsMultiLayerWellAttrValid (IfmDocument pDoc, int nId, IfmMLW_ATTR nAttr);
  IfmBool IfmIsMultiLayerWellAttrTransient (IfmDocument pDoc, int nId, IfmMLW_ATTR nAttr);
  double  IfmGetMultiLayerWellAttrValue (IfmDocument pDoc, int nId, IfmMLW_ATTR nAttr);
  int	  IfmGetMultiLayerWellAttrTSID (IfmDocument pDoc, int nId, IfmMLW_ATTR nAttr);
  void	  IfmSetMultiLayerWellAttrValue (IfmDocument pDoc, int nId, IfmMLW_ATTR nAttr, double dRate);
  void	  IfmSetMultiLayerWellAttrTSID (IfmDocument pDoc, int nId, IfmMLW_ATTR nAttr, int nTSID);
  IfmFractureLaw IfmGetFracLaw(IfmHandle hdl, int nFracElement, IfmFractureType nFracType, IfmFractureMode nFracMode);
  void	  IfmSetFracLaw (IfmHandle hdl, int nFracElement, IfmFractureType nFracType, IfmFractureMode nFracMode, IfmFractureLaw nFracLaw);

  /* Selection handling */
  int	      IfmGetNumberOfSelections(IfmDocument pDoc, IfmSEL_TYPE nSelType);
  int	      IfmGetSelectionCapacity (IfmDocument pDoc, IfmSEL_TYPE nSelType);
  int	      IfmFindSelection (IfmDocument pDoc, IfmSEL_TYPE nSelType, const char* pszSelName);
  int	      IfmCreateSelection (IfmDocument pDoc, IfmSEL_TYPE nSelType, const char* pszSelName);
  IfmResult   IfmDeleteSelection (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex);
  const char* IfmGetSelectionName (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex);
  int	      IfmEnumSelectionItems (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex, int nStartPos);
  IfmBool     IfmSelectionItemIsSet (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex, int nItem);
  void	      IfmSetSelectionItem (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex, int nItem);
  void	      IfmClearSelectionItem (IfmDocument pDoc, IfmSEL_TYPE nSelType, int nSelIndex, int nItem);

  /* Expression based distributions */
  int	      IfmGetNumberOfNodalExprDistr (IfmDocument pDoc);
  int	      IfmGetNumberOfElementalExprDistr (IfmDocument pDoc);
  const char* IfmGetNodalExprDistrName (IfmDocument pDoc, int nID);
  const char* IfmGetElementalExprDistrName (IfmDocument pDoc, int nID);
  int	      IfmGetNodalExprDistrIdByName (IfmDocument pDoc, const char* pszName);
  int	      IfmGetElementalExprDistrIdByName (IfmDocument pDoc, const char* pszName);
  double      IfmGetNodalExprDistrValue (IfmDocument pDoc, int nID, int nIndex);
  double      IfmGetElementalExprDistrValue (IfmDocument pDoc, int nID, int nIndex);

  /* Access to number of element nodes */
  int         IfmGetNumberOfElementNodes (IfmDocument pDoc, int nElem);
  int         IfmGetNumberOfElementNodes2D (IfmDocument pDoc, int nElem);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6209
  /* Get history values (currently from diagrams) */
  IfmResult   IfmGetHistoryDimensions (IfmDocument pDoc, IfmHistoryID nID, int nKind, int* nTimes, int* nHist);
  IfmResult   IfmGetHistoryValues (IfmDocument pDoc, IfmHistoryID nID, int nKind, int nTimes, int nHist, double* pTimes, double** pValues);
#endif

#if IFM_CURRENT_DOCUMENT_VERSION >= 0x6212
  /* Nodal velocity components */
  extern IfmBool IfmGetResultsNodalVelocityValuesAtXYZ (IfmHandle, double x, double y, double z, IfmVTriplet* v);

  /* Interpolated reference distribution values */
  extern IfmBool IfmGetNodalRefDistrValueAtXYSlice (IfmHandle, long refid, double x, double y, int slice, double* pVal);
  extern IfmBool IfmGetNodalRefDistrValueAtXYZ (IfmHandle, long refid, double x, double y, double z, double* pVal);

  /* 3D search routines */
  extern int  IfmFindElementAtXYZ (IfmHandle, double x, double y, double z);
  extern int  IfmFindNodeAtXYZ (IfmHandle, double x, double y, double z, double* dist);
#endif

IFM_FUNCPROTOEND

#endif /* IFM_DOCUMENT_H */
 
