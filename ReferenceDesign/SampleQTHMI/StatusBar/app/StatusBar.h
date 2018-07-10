#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QObject>
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"

enum eIconType
{
    ICON_WIFI,
    ICON_BT,
    ICON_USB,
    ICON_MSG
};

class StatusBar : public QObject, public App
{
    Q_OBJECT

private:
    explicit StatusBar();

public:
    enum eViewId{
        eViewId_Main
    };

    static StatusBar* Inst();

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);
    void onReply(string appId, map<string, string> parameter);

public slots:
    void OnAppShow(string appId,string viewId);
    void OnAppHide();
    void OnNotify(string appId, map<string, string> parameter);
    void OnReply(string appId, map<string, string> parameter);

signals:
    void SigAppShow(string appId,string viewId);
    void SigAppHide();
    void SigNotify(string appId, map<string, string> parameter);
    void SigReply(string appId, map<string, string> parameter);

    void SigLoadingStatusChanged(bool status);
    void SigTemperatureChanged(int temperature);
    void SigTemperatureUnitChanged(bool isCelsius);
    void SigIconStatusChanged(int type, bool active, int count = 0);

private:
    static StatusBar *m_pInst;
};

#endif // STATUSBAR_H
