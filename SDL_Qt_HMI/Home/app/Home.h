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
        eViewId_Main
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

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);

public slots:
    void OnAppShow(string appId,string viewId);
    void OnAppHide();
    void OnNotify(string appId, map<string, string> parameter);

public:signals:
    void SigAppShow(string appId,string viewId);
    void SigAppHide();
    void SigNotify(string appId, map<string, string> parameter);
private:
    static Home *m_pInst;
};

#endif // HOME_H
