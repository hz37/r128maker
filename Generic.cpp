//---------------------------------------------------------------------------

#include "Generic.h"
#pragma hdrstop

//---------------------------------------------------------------------------

// Constants (also see Generic.h).

extern const int CDefaultRefLevel = -23; // LUFS
extern const double CDefaultAllowedDeviation = 0.4; // LU
extern const int CDefaultTruePeakLevel = -1; // dBTP
extern const int CDefaultBufferSize = 1; // Second
extern const int CDefaultOversample = 1; // .TRUE.
extern const int CDefaultOversampleMethod = 1; // Medium sinc
extern const int CDefaultSkipOversampling = 1; // .TRUE.
extern const int CDefaultSkipOversamplingPeak = -6; // dBFS
extern const int CDefaultDoNotCheckAgain = 1; // .TRUE.
extern const int COversampleRatio = 4; // 4x oversampling, as recommended by R128.
extern const int CDefaultPriority = 4; // Normal priority

extern const AnsiString CDefaultRefLevelKey = "CDefaultRefLevelKey";
extern const AnsiString CDefaultAllowedDeviationKey = "CDefaultAllowedDeviationKey";
extern const AnsiString CDefaultTruePeakLevelKey = "CDefaultTruePeakLevelKey";
extern const AnsiString CDefaultBufferSizeKey = "CDefaultBufferSizeKey";
extern const AnsiString CDefaultOversampleKey = "CDefaultOversampleKey";
extern const AnsiString CDefaultOversampleMethodKey = "CDefaultOversampleMethodKey";
extern const AnsiString CDefaultSkipOversamplingKey = "CDefaultSkipOversamplingKey";
extern const AnsiString CDefaultSkipOversamplingPeakKey = "CDefaultSkipOversamplingPeakKey";
extern const AnsiString CDefaultDoNotCheckAgainKey = "CDefaultDoNotCheckAgainKey";
extern const AnsiString CDefaultPriorityKey = "CDefaultPriorityKey";

//---------------------------------------------------------------------------

