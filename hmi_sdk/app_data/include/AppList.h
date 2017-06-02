#ifndef APPLIST_H
#define APPLIST_H

#include "AppListInterface.h"
#include "AppData.h"
#include "UIInterface.h"


class AppData;
class AppList : public IMessageInterface, public AppListInterface
{
public:
    AppList();
    ~AppList();

    //AppListInterface
    void setUIManager(UIInterface *pUI);
    AppDataInterface* getActiveApp();
    void getAppList(std::vector<int>& vAppIDs, std::vector<std::string>& vAppNames);
    void getAppList(std::vector<int>& vAppIDs, std::vector<std::string>& vAppNames,std::vector<std::string> &vIconPath);
    void OnAppActivated(int appID);
    void OnAppExit();
    void OnShowDeviceList();
    void ShowPreviousUI();
    // add by fanqiang
    void OnStartDeviceDiscovery();
    void OnDeviceChosen(const std::string name, const std::string id);
    void OnFindApplications(std::string name, std::string id);
    void getDeviceList(std::vector<DeviceData>& vDevice);
    void OnDeviceSelect(const std::string id);

    void appUnregistered(int appId);

    void IconnectToVS(IMessageInterface * pMsgHandler, std::string sIP, int iPort);
    void IdelConnectToVS();

public: //IMessageInterface
    Result onRequest(Json::Value);
    void onNotification(Json::Value);
    void onResult(Json::Value);
    void onRawData(void * p, int iLength);
    void onError(std::string error);

private:
    Result recvFromServer(Json::Value);
    void newAppRegistered(Json::Value jsonObj);
    void appUnregistered(Json::Value jsonObj);

    // add by fanqiang
    void updateDeiveList(Json::Value jsonObj);
private:
    UIInterface *m_pUIManager;
    std::vector <AppData *> m_AppDatas;
    AppData * m_pCurApp;
    std::vector <DeviceData> m_devicelist;
};

#endif // APPLIST_H
