#ifndef APP_H
#define APP_H

#include "Interface.h"
#include <QWidget>
#include "CView.h"
#include "HMIFrameWork/ViewFactory.h"
class App:public IApp
{
public:
    App();
    virtual void setAppType(eAppType type);
    virtual void setAppId(string id);
    virtual void onAppShow(string appId,string viewId) ;
    virtual void onAppHide();
    virtual void onNotify(string appId,map<string,string> parameter);
    virtual void onReply(string appId,map<string,string> parameter);
    virtual eAppStatus getState();
    virtual void setState(eAppStatus state);
    virtual eAppType getAppType();
    virtual string getAppID();
    virtual void setMain(void* pMain);
    virtual void* getMain();

    virtual CView* CreateView(int viewId);
    virtual void AddView(CView* pView);
    virtual void ViewBack();
    virtual void ViewForwardById(int viewId);

    virtual void InitViewFactory(ViewFactory* viewFactory);
private:
    CView* findViewById(int viewId);
    void EraseView(CView* pView);
    void PushView(CView* pView);
private:
    eAppStatus m_state;
    eAppType m_appType;
    string m_appId;

    void* m_pMain;
    CView *m_pCurView;

    vector<CView*> m_pAppView;
    vector<CView*> m_pAppViewStack;

    ViewFactory *m_pViewFactory;
};

#endif // APP_H
