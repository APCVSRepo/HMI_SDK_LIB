#ifndef MEDIA_H
#define MEDIA_H

#include <QObject>
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"

struct MediaAppInfo{
    int appId;
    std::string appName;
    std::string appIcon;
};

class Media : public QObject, public App
{
    Q_OBJECT

private:
    explicit Media();

public:
    enum eViewId{
        eViewId_Main
    };

    static Media* Inst();

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);
    void onReply(string appId, map<string, string> parameter);

    const std::vector<MediaAppInfo> &GetAppList()const;

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
    std::vector<MediaAppInfo> m_vMediaAppList;

    static Media *m_pInst;
};

#endif // MEDIA_H
