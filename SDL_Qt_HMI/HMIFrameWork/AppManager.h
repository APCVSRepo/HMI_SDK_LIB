#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include "AppConfig.h"
#include <QWidget>
#include "Interface.h"
#include "App.h"
using namespace std;

class AppManager : public IAppManager
{

public:
    AppManager();
    virtual ~AppManager();
    virtual void RegisterApp(App* app);
    virtual void AppShow(string appId,string viewId = "Main");
    virtual void AppBack();
    virtual void Notify(string appId,map<string,string> parameter);    
private:
     bool IntertApp( App* app);
     App* findApp(string id);
     void Erase(App* app);


protected:
    void Push(App* app);
    void Pop();


private:
    vector<App*> m_pApp;
    vector<App*> m_pAppStack;
    App* m_pActiveApp;

};

#endif // APPMANAGER_H
