#ifndef HOME_H
#define HOME_H

#include "HMIFrameWork/App.h"
#include "Home/UI/HomeView.h"
#include <QWidget>
#include "HMIFrameWork/AppConfig.h"
#include "Home/Factory/HomeVFactory.h"
#include <QObject>
class Home:public QObject,public App
{
    Q_OBJECT
private:
        Home();
public:
    enum eViewId{
        eViewId_Main,
        eViewId_BootAnimation,
        eViewId_Settings_Main,
        eViewId_Settings_Sound,
        eViewId_Settings_DataTime,

        eViewId_Settings_BT,
        eViewId_Settings_Wifi,
        eViewId_Settings_WifiAddHotSpots,
        eViewId_Settings_WifiPassword,

        eViewId_Settings_Display,
        eViewId_Settings_Emergency,
        eViewId_Settings_MobileApplications,
        eViewId_Settings_RoutineSetting,
        eViewId_Settings_SpeechRecogniton
    };

    static Home* Inst();
    void HomeClicked();
    void SDLAppsClicked();
    void HVACClicked();
    void MediaClicked();
    void MessageClicked();
    void NavClicked();
    void PhoneClicked();
    void SettingsClicked();
    void WeatherClicked();
    bool SetNotifyBTShowStatus(bool isShow);
    bool GetNotifyBTShowStatus();
    string GetNotifyBTShowId();

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);
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

    void SigQuickMove(QString type);
private:
    static Home *m_pInst;
    bool m_bNotifyBTShow;
    string m_NotifyBTShowId;
};

#endif // HOME_H
