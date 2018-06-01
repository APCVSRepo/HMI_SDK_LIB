#ifndef POPUP_H
#define POPUP_H

#include <QObject>
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"


class PopUp : public QObject, public App
{
    Q_OBJECT

private:
    explicit PopUp();

public:
    enum eViewId{
        eViewId_Main
    };

    static PopUp* Inst();

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

    void SigPopUpNotify(string appId,map<string, string> parameter);
private:
    static PopUp *m_pInst;


};

#endif // POPUP_H
