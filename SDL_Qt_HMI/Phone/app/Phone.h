#ifndef Phone_H
#define Phone_H

#include "HMIFrameWork/App.h"
#include "Phone/UI/KeyBoardView.h"
#include <QWidget>
#include "HMIFrameWork/AppConfig.h"
#include "Phone/Factory/PhoneVFactory.h"
#include <QObject>

enum eKeyBoard{
    eNumber_0,
    eNumber_1,
    eNumber_2,
    eNumber_3,
    eNumber_4,
    eNumber_5,
    eNumber_6,
    eNumber_7,
    eNumber_8,
    eNumber_9,
    eNumber_Delete,
    eNumber_Dial,
    eNumber_Star,
    eNumber_Well,

};

class Phone:public QObject,public App
{
    Q_OBJECT
private:
        Phone();
public:
    enum eViewId{
        eViewId_BTSetting,
        eViewId_KeyBoard,
        eViewId_Contacts,
        eViewId_Recents,
        eViewId_ContactsDetails,
        eViewId_Calling

    };

    static Phone* Inst();

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);
    void onReply(string appId, map<string, string> parameter);

    bool IsOutAppCall();
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
    bool m_bOutAppCall;
    static Phone *m_pInst;
};

#endif // Phone_H
