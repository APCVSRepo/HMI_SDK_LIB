#include "AppManager.h"

#include <QDebug>

AppManager::AppManager()
    :m_pActiveApp(NULL)
{
}

AppManager::~AppManager()
{

}

void AppManager::RegisterApp(App *app)
{
    if(app)
    {
        if(app->getAppType() == AppType_HomeApp)
        {
            app->setState(AppStatus_Active);
            IntertApp(app);
        }else if(app->getAppType() == AppType_App)
        {
            app->setState(AppStatus_Inactive);
            IntertApp(app);
        }else if(app->getAppType() == AppType_Decorators)
        {
            app->setState(AppStatus_Inactive);
            IntertApp(app);
        }
    }
}

bool AppManager::IntertApp(App *app)
{
    if(app == NULL)
    {
        return false;
    }
    if(m_pApp.size()>0)
    {
        for(int i = 0 ;i < m_pApp.size();i++)
        {
           App* temp = m_pApp.at(i);
           if(temp->getAppID() == app->getAppID())
           {
               return true;
           }
        }
    }
     m_pApp.insert(m_pApp.begin(),app);
     return true;
}


void AppManager::AppShow(string appId,string viewId)
{
    App* app = findApp(appId);
    qDebug()<<"shwo appid = " << QString::fromStdString( appId) ;

    if(app)
    {
        if(app->getAppType() != AppType_Decorators)
        {
            App* temp = m_pActiveApp;
            Erase(app);
            Push(app);
            app->onAppShow(appId,viewId);
            if(temp)
            {
                temp->onAppHide();
            }
        }else if(app->getAppType() == AppType_Decorators)
        {
          app->setState(AppStatus_Active);
          app->onAppShow(appId,viewId);
        }

    }else
    {
        qDebug()<<"not " << QString::fromStdString(appId);
    }

}

void AppManager::AppBack()
{

    App* temp = m_pActiveApp;
    Pop();

    m_pActiveApp->onAppShow(m_pActiveApp->getAppID(),"AppBack");
    temp->onAppHide();
}

void AppManager::Notify(string appId, map<string, string> parameter)
{
    App* app = findApp(appId);
    if(app)
    {
        app->onNotify(appId,parameter);
    }
}

void AppManager::Erase(App *app)
{
   if(app)
   {
       int size = m_pAppStack.size();
       for(int i = 0; i < size ;i++)
       {
           if(app == m_pAppStack.at(i))
           {
               m_pAppStack.erase(m_pAppStack.begin()+i);
           }
       }
   }
}

App *AppManager::findApp(string id)
{
    vector<App*>::iterator itor = m_pApp.begin();
    App* pv = 0;
    for(;itor != m_pApp.end();++itor)
    {
        pv = *itor;
        string AppId = pv->getAppID();
        if(id == AppId)
        {
            return pv;
        }
    }

    return NULL;
}

void AppManager::Push(App* app)
{
    if(app == NULL)
    {
        qDebug()<<" push null";
        return;
    }

    if(m_pAppStack.size() > 0)
    {
        App* temp = m_pAppStack.at(0);
        if(app == temp || temp == NULL)
        {
            return;
        }
        m_pAppStack.insert(m_pAppStack.begin(),app);

        temp->setState(AppStatus_Inactive);
        app->setState(AppStatus_Active);

    }else
    {
        m_pAppStack.insert(m_pAppStack.begin(),app);
        app->setState(AppStatus_Active);
    }
    m_pActiveApp = app;
}

void AppManager::Pop()
{
    if(m_pAppStack.size() > 1)
    {
        App* _inactive = m_pAppStack.at(0);
        m_pAppStack.erase(m_pAppStack.begin());
        m_pActiveApp = m_pAppStack.at(0);
        _inactive->setState(AppStatus_Inactive);
        m_pActiveApp->setState(AppStatus_Active);

    }
}
