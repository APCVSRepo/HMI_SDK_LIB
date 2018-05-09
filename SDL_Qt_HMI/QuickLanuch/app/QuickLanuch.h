#ifndef QUICKLANUCH_H
#define QUICKLANUCH_H

#include "HMIFrameWork/App.h"
#include "QuickLanuch/UI/QuickLanuchView.h"
#include "HMIFrameWork/AppConfig.h"
class QuickLanuch:public QObject,public App
{
    Q_OBJECT
private:
    QuickLanuch();
public:
    enum eViewId{
        eViewId_Main
    };
    static QuickLanuch* Inst();
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
    void SigAppInfo(int x, int y,string type);
private:
    static QuickLanuch* m_pInst;
};

#endif // QUICKLANUCH_H
