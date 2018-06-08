#ifndef VR_H
#define VR_H

#include <QObject>
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"

struct VRAppInfo{
    int appId;
    std::string appName;
    std::string appIcon;
};

class VR : public QObject, public App
{
    Q_OBJECT

private:
    explicit VR();

public:
    enum eViewId{
        eViewId_Main,
        eViewId_Interaction
    };

    static VR* Inst();

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);
    void onReply(string appId, map<string, string> parameter);

    const std::vector<VRAppInfo> &GetAppList()const;

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
    std::vector<VRAppInfo> m_vVRAppList;

    static VR *m_pInst;
};

#endif // VR_H
