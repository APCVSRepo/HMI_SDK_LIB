#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QLibrary>
#include <QWidget>
#include "ui_interface.h"
#include "app_list_interface.h"
#include "Template/TemplateManager.h"
#include "SDLApps/UI/SDLAppsView.h"

using namespace hmisdk;

class UIManager : public QWidget, public UIInterface {
    Q_OBJECT

public:
    explicit UIManager(QWidget *parent = NULL);
    ~UIManager();

    void SetAppListInterface(AppListInterface *pList);
    bool FindTemplate(std::string name);

    void onAppActive();
    void onAppStop();
    //hmi
    void onAppShow(int type);
    void onAppRegister(int appId);
    void onAppUnregister(int appId);

    void onVideoStreamStart();
    void onVideoStreamStop();

    void tsSpeak(int VRID, std::string strText);

    void OnEndAudioPassThru();

    // add by fanqiang
    void ShowDeviceList();
    void SetSDLStatus(bool bConnect);   //TODO: this func is not found anywhere to be called
    void initAppHMI();

    //AppListInterface Proxy
    void OnAppActivated(int appID);
//    void StopVideoStream();
    void ExitApp();

    int GetCurViewId();

signals:
    void onAppShowSignal(int type);
    void onAppActivatedSignal(AppDataInterface *pInterface);
    void OnAppUnregisterSignal(int appId);

    void onVideoStartSignal();
    void onVideoStopSignal();
    void finishLoadSDK();

    void appListUpdateSignal();

public slots:
    void AppShowSlot(int type);
    void OnAppUnregisterSlot(int appId);

    void onVideoStartSlots();
    void onVideoStopSlots();
    void loadsdk();

public:
    SDLAppsView *getSDLAppsView();

private:
    int m_iCurUI;
    std::string m_sCurTpln;
    AppListInterface *m_pList;
    QLibrary m_sdk;
    TemplateManager m_TplManager;
};

#endif // UIMANAGER_H
