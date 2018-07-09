#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QObject>
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"

struct NaviAppInfo{
//    NaviAppInfo(int id, std::string name, std::string icon, std::string type)
//        :appId(id)
//        ,appName(name)
//        ,appIcon(icon)
//        ,appType(type)
//    {

//    }

    int appId;
    std::string appName;
    std::string appIcon;
//    std::string appType;
};

class Navi : public QObject, public App
{
    Q_OBJECT

private:
    explicit Navi();

public:
    enum eViewId{
        eViewId_Main
    };

    static Navi* Inst();

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);
    void onReply(string appId, map<string, string> parameter);

    const std::vector<NaviAppInfo> &GetAppList()const;

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

    void SigUpdateAppList();

private:
    std::vector<NaviAppInfo> m_vNaviAppList;

    static Navi *m_pInst;
};

#endif // NAVIGATION_H
