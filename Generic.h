//---------------------------------------------------------------------------

// Generic header for all classes.
// Based on the Harold Howe article, speeds up precompiled headers.

/*

Every source file only includes (case sensitive):

#include "Generic.h"
#pragma hdrstop

(any STL headers below #pragma hdrstop)

*/

//---------------------------------------------------------------------------

#ifndef GenericH
#define GenericH

//---------------------------------------------------------------------------

// VCL.

#include <vcl.h>
#include <registry.hpp>

// STL.
            
#include <algorithm>
#include <memory>

// C RTL.

#include <fastmath.h>
#include <stdio.h>

// Custom.

#include "ebur128.h"
#include "R128MakerUnit.h"
#include "SettingsUnit.h"
#include "Storage.h"

//---------------------------------------------------------------------------

// Constants (also see Generic.cpp).

extern const int CDefaultRefLevel;
extern const double CDefaultAllowedDeviation;
extern const int CDefaultTruePeakLevel;
extern const int CDefaultBufferSize;
extern const int CDefaultOversample;
extern const int CDefaultOversampleMethod;
extern const int COversampleRatio;
extern const int CDefaultSkipOversampling;
extern const int CDefaultSkipOversamplingPeak;
extern const int CDefaultDoNotCheckAgain;
extern const int CDefaultPriority;

extern const AnsiString CDefaultRefLevelKey;
extern const AnsiString CDefaultAllowedDeviationKey;
extern const AnsiString CDefaultTruePeakLevelKey;
extern const AnsiString CDefaultBufferSizeKey;
extern const AnsiString CDefaultOversampleKey;
extern const AnsiString CDefaultOversampleMethodKey;
extern const AnsiString CDefaultSkipOversamplingKey;
extern const AnsiString CDefaultSkipOversamplingPeakKey;
extern const AnsiString CDefaultDoNotCheckAgainKey;
extern const AnsiString CDefaultPriorityKey;

//---------------------------------------------------------------------------

#endif

//---------------------------------------------------------------------------



