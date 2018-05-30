#include "HMIFrameWork.h"
#include "MainWindow.h"
#include <QWidget>
#include <QMainWindow>
HMIFrameWork *HMIFrameWork::m_pInstance = NULL;

HMIFrameWork *HMIFrameWork::Inst()
{
    if(NULL == m_pInstance)
    {
        m_pInstance = new HMIFrameWork;
    }
    return m_pInstance;
}

void HMIFrameWork::RegisterApp(App *app,void* parent)
{
    m_pAppManager->RegisterApp(app);
    if(NULL == parent)
    {
        QWidget* w = reinterpret_cast<QWidget*>(app->getMain());
        if(w)
            w->setParent(reinterpret_cast<QWidget*>(m_pMainWin));
    }
    else
    {
        QWidget* w = reinterpret_cast<QWidget*>(app->getMain());
        if(w)
            w->setParent(reinterpret_cast<QWidget*>(parent));
    }
}

void* HMIFrameWork::GetMainWindow()
{
    return m_pMainWin;
}

void HMIFrameWork::AppShow(string id, string view)
{
    m_pAppManager->AppShow(id,view);
}

void HMIFrameWork::AppBack()
{
    m_pAppManager->AppBack();
}

void HMIFrameWork::Notify(string appId, map<string, string> parameter)
{
    m_pAppManager->Notify(appId,parameter);
}

void HMIFrameWork::Reply(string appId, map<string, string> parameter)
{
    m_pAppManager->Reply(appId,parameter);
}

void HMIFrameWork::SetMain(void *pMain)
{
    m_pMainWin = pMain;
}

HMIFrameWork::HMIFrameWork()
    :m_pMainWin(NULL)
    ,m_pAppManager(NULL)
{
    m_pAppManager = new AppManager;
}

HMIFrameWork::~HMIFrameWork()
{
    if(m_pAppManager)
    {
        delete m_pAppManager;
        m_pAppManager = NULL;
    }
}
