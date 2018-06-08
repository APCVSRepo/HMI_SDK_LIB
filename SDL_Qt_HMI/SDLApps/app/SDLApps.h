#ifndef SDLAPPS_H
#define SDLAPPS_H

#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "SDLApps/Factory/SDLVFactory.h"
#include "SDLApps/UI/SDLAppsWindow.h"
#include "SDLApps/Templates/UIManager.h"

class SDLApps:public QObject,public App
{
    Q_OBJECT
private:
    SDLApps();

public:
    enum eViewId{
        eViewId_SDL_Main,
    };

    static SDLApps* Inst();
    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId,map<string,string> parameter);
    void onReply(string appId, map<string, string> parameter);
    UIManager *GetUIManager();

//    void UpdateAppList();
    bool FromNavi();
    void SetFromNavi(bool bFromNavi);

    bool FromMedia();
    void SetFromMedia(bool bFromMedia);

public slots:
    void OnAppShow(string appId,string viewId);
    void OnAppHide();
    void OnNotify(string appId, map<string, string> parameter);
    void OnReply(string appId, map<string, string> parameter);

    void OnAppListUpdate();

signals:
    void SigAppShow(string appId,string viewId);
    void SigAppHide();
    void SigNotify(string appId, map<string, string> parameter);
    void SigReply(string appId, map<string, string> parameter);

private:
    void StartSDL();

private:
    UIManager *m_pUIManager;
    bool m_bFromNavi;
    bool m_bFromMedia;

    static SDLApps *m_pInst;
};

#endif // SDLAPPS_H
