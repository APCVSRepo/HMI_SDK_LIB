#ifndef PROMPT_H
#define PROMPT_H

#include <QObject>
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/AppConfig.h"


class Prompt : public QObject, public App
{
    Q_OBJECT

private:
    explicit Prompt();

public:
    enum eViewId{
        eViewId_Main
    };

    static Prompt* Inst();

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);
    void onReply(string appId, map<string, string> parameter);


    void UpdateWIndSize(const QSize& size);
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

    void SigPromptNotify(string appId,map<string, string> parameter);
private:
    static Prompt *m_pInst;


};

#endif // PROMPT_H
