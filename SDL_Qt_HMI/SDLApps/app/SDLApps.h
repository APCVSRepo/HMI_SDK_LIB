#ifndef SDLAPPS_H
#define SDLAPPS_H
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"
#include "SDLApps/Factory/SDLVFactory.h"
#include "SDLApps/UI/SDLAppsWindow.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
class SDLApps:public QObject,public App
{
    Q_OBJECT
private:
    SDLApps();
public:
    enum eViewId{
        eViewId_SDL_Main
    };

    static SDLApps* Inst();
    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId,map<string,string> parameter);
    void onReply(string appId, map<string, string> parameter);

public slots:
    void OnAppShow(string appId,string viewId);
    void OnAppHide();
    void OnNotify(string appId, map<string, string> parameter);
    void OnReply(string appId, map<string, string> parameter);

public:signals:
    void SigAppShow(string appId,string viewId);
    void SigAppHide();
    void SigNotify(string appId, map<string, string> parameter);
    void SigReply(string appId, map<string, string> parameter);

private:
    static SDLApps *m_pInst;
};

#endif // SDLAPPS_H
