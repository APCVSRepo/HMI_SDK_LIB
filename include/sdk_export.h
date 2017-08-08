/**
* @file			sdk_export.h  
* @brief		HMI SDK��̬�⵼������
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
 * HMI SDK��ʼ��
 * @param[in]	pUI		UIInterface�ӿ�
 * @return		����ֵAppListInterface�������ж�SDK��ʼ���Ƿ�ɹ���ʧ�ܷ���NULL
 * @ref			
 * @see			ui_interface.h app_list_interface.h
 * @note		��ʼ��SDK��HMI��Դ��������SDL
 */ 
extern "C" HMISDK_EXPORT AppListInterface* InitHmiSdk(UIInterface* pUI);

/** 
 * HMI SDK�ͷ�
 * @return		��
 * @ref			
 * @see			
 * @note		�ͷ�App���ݹ������Դ
 */ 
extern "C" HMISDK_EXPORT void UnInitHmiSdk();

#endif // HMISDKLIB_H
