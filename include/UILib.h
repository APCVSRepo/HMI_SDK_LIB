#ifndef UILIB_H
#define UILIB_H



#if defined(WIN32) || defined(WINCE)
#ifdef HMIUI_LIBRARY
#define UISHARED_EXPORT __declspec(dllexport)
#else
#define UISHARED_EXPORT __declspec(dllimport)
#endif

#else
#define UISHARED_EXPORT
#endif


/*
#include <QtCore/qglobal.h>

#if defined(TESTLIB_LIBRARY)
#  define UISHARED_EXPORT Q_DECL_EXPORT
#else
#  define UISHARED_EXPORT Q_DECL_IMPORT
#endif
*/

#include "AppListInterface.h"
#include "UIInterface.h"


extern "C" UISHARED_EXPORT UIInterface *UILib_Init(AppListInterface *pList);

extern "C" UISHARED_EXPORT void UILib_Close();


#endif // UILIB_H
