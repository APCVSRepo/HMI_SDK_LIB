#ifndef HMIFRAMEWORK_H
#define HMIFRAMEWORK_H

#include <QWidget>
#include "AppManager.h"

class HMIFrameWork
{
public:
    static HMIFrameWork *Inst();
    void RegisterApp(App *app,void* parent=NULL);

    void SetMain(void * pMain);
    void* GetMainWindow();
    void AppShow(string id,string view="Main");
    void AppBack();
    void Notify(string appId,map<string,string> parameter);
    void Reply(string appId,map<string,string> parameter);
    ~HMIFrameWork();
private:
    HMIFrameWork();

private:
    void *m_pMainWin;
    AppManager *m_pAppManager;
    static HMIFrameWork *m_pInstance;
};

#endif // HMIFRAMEWORK_H
