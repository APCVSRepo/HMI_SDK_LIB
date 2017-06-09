#ifndef HMISDKLIB_H
#define HMISDKLIB_H



#if defined(WIN32) || defined(WINCE)
#ifdef HMISDK_LIB
#define HMISDK_EXPORT __declspec(dllexport)
#else
#define HMISDK_EXPORT __declspec(dllimport)
#endif
#else
#define HMISDK_EXPORT
#endif


#include "AppListInterface.h"
#include "UIInterface.h"

extern "C" HMISDK_EXPORT AppListInterface* HMISDK_Init(UIInterface* pUI);

extern "C" HMISDK_EXPORT void HMISDK_UnInit();

#endif // HMISDKLIB_H
