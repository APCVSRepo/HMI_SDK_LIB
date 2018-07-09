#ifndef VOICERECOGNITION_H
#define VOICERECOGNITION_H

#include <QObject>
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"

struct VRAppInfo{
    int appId;
    std::string appName;
    std::string appIcon;
};

class VoiceRecognition : public QObject, public App
{
    Q_OBJECT

private:
    explicit VoiceRecognition();

public:
    enum eViewId{
        eViewId_Main,
        eViewId_Interaction
    };

    static VoiceRecognition* Inst();

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

    static VoiceRecognition *m_pInst;
};

#endif // VOICERECOGNITION_H
