/**
* @file			app_list_interface.h
* @brief		手机端App数据控制接口，保存所有手机端App数据列表（参见AppDataInterface说明），作为UI部分控制指定App的总入口，对于公用部分的RPC请求也会在此处理，指定App的处理将会继续传递到下一层AppDataInterface中进行
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef APPLISTINTERFACE_H
#define APPLISTINTERFACE_H

#include <iostream>
#include <string.h>
#include <vector>
#include "app_data_interface.h"

class UIInterface;

/**  设备信息*/
struct DeviceData {
  std::string name;	///<  设备名
  std::string id;	///<  设备id
};

class AppListInterface {
 public:
  /**
   * 通知用户画面中选中某个App
   * @param[in]	appID		App标识
   * @return		无
   * @ref
   * @see
   * @note		通知SDK用户在App列表中点击某个App
   */
  virtual void OnAppActivated(int appID) = 0;

  /**
   * 通知退出当前App
   * @return		无
   * @ref
   * @see
   * @note		通知SDK用户在画面点击退出App菜单等操作
   */
  virtual void OnAppExit() = 0;

  /**
   * 通知切换到前一画面
   * @return		无
   * @ref
   * @see
   * @note		通知SDK需要切换到前一画面或App列表画面
   */
  virtual void ShowPreviousUI() = 0;

  /**
   * 通知需要获取设备列表
   * @return		无
   * @ref
   * @see
   * @note		用户点击画面获取设备列表触发该事件，通知SDK获取设备列表
   */
  virtual void OnShowDeviceList() = 0;

  /**
   * 获取当前AppDataInterface数据接口
   * @return		AppDataInterface*	当前AppDataInterface数据接口
   * @ref
   * @see
   * @note		在展示某个画面时，需要获取当前活动App，然后取得画面的数据
   */
  virtual AppDataInterface *getActiveApp() = 0;

  /**
   * 设置UIInterface接口
   * @param[in]	pUI		UIInterface接口
   * @return		无
   * @ref
   * @see
   * @note		该函数会在SDK初始化时调用进行设置，保证后续AppListInterface对该接口使用有效
   */
  virtual void setUIManager(UIInterface *pUI) = 0;

  /**
   * 获取所有App信息
   * @param[out]	vAppIDs		App标识列表
   * @param[out]	vAppNames		App显示名称列表
   * @return		无
   * @ref
   * @see
   * @note		获取所有App标识和名称
   */
  virtual void getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames) = 0;

  /**
   * 获取所有App信息
   * @param[out]	vAppIDs		App标识列表
   * @param[out]	vAppNames		App显示名称列表
   * @param[out]	vIconPath		App显示图标列表
   * @return		无
   * @ref
   * @see
   * @note		获取所有App标识、名称及图标
   */
  virtual void getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath) = 0;


  /**
   * 获取所有App信息
   * @param[out]	vAppIDs		App标识列表
   * @param[out]	vAppNames		App显示名称列表
   * @param[out]	vIconPath		App显示图标列表
   * @param[out]	vAppTypes		App类型列表
   * @return		无
   * @ref
   * @see
   * @note		获取所有App标识、名称及图标
   */
  virtual void getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath, std::vector<std::string> &vAppTypes) = 0;

  /**
   * 通知选择了设备并要求获取设备支持的App信息
   * @param[in]	id		设备ID
   * @return		无
   * @ref
   * @see
   * @note		用户点击画面选择某个设备触发该事件，通知选择了设备并要求获取设备支持的App信息
   */
  virtual void OnDeviceSelect(const std::string id) = 0;

  /**
   * 获取当前连接所有设备信息
   * @param[out]	vDevice		当前连接所有设备信息
   * @return		无
   * @ref
   * @see			DeviceData结构定义
   * @note
   */
  virtual void getDeviceList(std::vector<DeviceData> &vDevice) = 0;

  /**
   * 请求SDK扫描设备信息
   * @return		无
   * @ref
   * @see
   * @note		通知SDK扫描获取有效的设备
   */
  virtual void OnStartDeviceDiscovery() = 0;

  /**
   * 通知取消App注册
   * @param[in]	appId		app对应的id
   * @return		无
   * @ref
   * @see
   * @note		App取消注册时会触发该事件，SDK会将该App数据销毁，并将画面切换到App列表
   */
  virtual void appUnregistered(int appId) = 0;
};

#endif // APPLISTINTERFACE_H
