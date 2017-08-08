/**
* @file			sdk_export.h  
* @brief		HMI SDK动态库导出函数
* @author		fanqiang
* @date			2017-6-21 
* @version		A001 
* @copyright	ford                                                              
*/

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


#include "app_list_interface.h"
#include "ui_interface.h"

/** 
 * HMI SDK初始化
 * @param[in]	pUI		UIInterface接口
 * @return		返回值AppListInterface可用于判断SDK初始化是否成功，失败返回NULL
 * @ref			
 * @see			ui_interface.h app_list_interface.h
 * @note		初始化SDK及HMI资源，并连接SDL
 */ 
extern "C" HMISDK_EXPORT AppListInterface* InitHmiSdk(UIInterface* pUI);

/** 
 * HMI SDK释放
 * @return		无
 * @ref			
 * @see			
 * @note		释放App数据管理等资源
 */ 
extern "C" HMISDK_EXPORT void UnInitHmiSdk();

#endif // HMISDKLIB_H
