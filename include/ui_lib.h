/**
* @file			ui_lib
* @brief		hmi_sdk动态库导出函数定义
* @author		fanqiang
* @date			2017-6-21 
* @version		A001 
* @copyright	ford                                                              
*/

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

#include "app_list_interface.h"
#include "UIInterface.h"

extern "C" UISHARED_EXPORT UIInterface *UILib_Init(AppListInterface *pList);

extern "C" UISHARED_EXPORT void UILib_Close();

#endif // UILIB_H
