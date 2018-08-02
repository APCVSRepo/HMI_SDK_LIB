/**
* @file			app_list
* @brief		AppListInterface接口实现类，实现手机端App数据控制，保存所有手机端App数据列表（参见AppDataInterface说明），作为UI部分控制指定App的总入口，对于公用部分的RPC请求也会在此处理，指定App的处理将会继续传递到下一层AppDataInterface中进行
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef APPLIST_H_
#define APPLIST_H_

#include "app_list_interface.h"
#include "app_data.h"
#include "ui_interface.h"

namespace hmisdk {

class AppData;
class AppList : public IMessageInterface, public AppListInterface {
 public:
  AppList();
  ~AppList();

  //AppListInterface
  void setUIManager(UIInterface *pUI);
  AppDataInterface *getActiveApp();
  void getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames);
  void getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath);
  void getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath, std::vector<std::string> &vAppTypes);

  void getDeviceList(std::vector<DeviceData> &vDevice);
  void appUnregistered(int appId);

  // add by fanqiang
  void OnStartDeviceDiscovery();
  void OnAppActivated(int appID);
  void OnAppExit();
  void OnShowDeviceList();
  void ShowPreviousUI();
  void OnDeviceChosen(const std::string name, const std::string id);
  void OnFindApplications(std::string name, std::string id);
  void OnDeviceSelect(const std::string id);

 public: //IMessageInterface
  Result onRequest(Json::Value);
  void onNotification(Json::Value);
  void onResult(Json::Value);
  void onRawData(void *p, int iLength);
  void onError(std::string error);

 private:
  // add by fanqiang
  void updateDeiveList(Json::Value jsonObj);
  Result recvFromServer(Json::Value);
  void newAppRegistered(Json::Value jsonObj);
  void appUnregistered(Json::Value jsonObj);
  void updateAppList(Json::Value jsonObj);

 private:
  UIInterface *m_pUIManager;
  std::vector <AppData *> m_AppDatas;
  AppData *m_pCurApp;
  std::vector <DeviceData> m_DeviceList;
};

}

#endif // APPLIST_H_
