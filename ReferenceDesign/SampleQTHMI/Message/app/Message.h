#ifndef MESSAGE_H
#define MESSAGE_H

#include "HMIFrameWork/App.h"
#include <QWidget>
#include "HMIFrameWork/AppConfig.h"
#include "Message/Factory/MessageVFactory.h"
#include <QObject>


class Message:public QObject,public App
{
    Q_OBJECT
private:
        Message();
public:
    enum eViewId{
        eViewId_MessageList,
        eViewId_Messages,
        eViewId_MessagesNoNewInfo

    };

    static Message* Inst();

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
    static Message *m_pInst;
};

#endif // MESSAGE_H
