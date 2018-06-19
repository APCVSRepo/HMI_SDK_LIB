#include "App.h"
#include <QWidget>
#include "log_interface.h"
App::App()
    :m_state(AppStatus_Inactive)
    ,m_pMain(NULL)
    ,m_pCurView(NULL)
{
    m_pAppView.clear();
    m_pAppViewStack.clear();
}

void App::setAppType(eAppType type)
{
    m_appType = type;
}

void App::setAppId(string id)
{
    m_appId = id;
}

void App::onAppShow(string appId, string viewId)
{
     Q_UNUSED(appId)
     Q_UNUSED(viewId)
}

void App::onAppHide()
{

}

void App::onNotify(string appId, map<string, string> parameter)
{
    Q_UNUSED(appId)
    Q_UNUSED(parameter)
}

void App::onReply(string appId, map<string, string> parameter)
{
    Q_UNUSED(appId)
    Q_UNUSED(parameter)
}

eAppStatus App::getState()
{
    return m_state;
}

void App::setState(eAppStatus state)
{
    m_state = state;
}

eAppType App::getAppType()
{
    return m_appType;
}

string App::getAppID()
{
    return m_appId;
}

void App::setMain(void *pMain)
{
    m_pMain = pMain;
}

void *App::getMain()
{
    return m_pMain;
}

CView* App::CreateView(int viewId)
{
    CView * pv = findViewById(viewId);
    if(NULL == pv)
    {
       void *pvv = m_pViewFactory->CreateProduct(viewId);
       if(NULL != pvv)
       {
           CView *pvvv = reinterpret_cast<CView*> (pvv);
           //pvvv->setView(reinterpret_cast<QWidget*> (pvv));
           AddView(pvvv);
           pvvv->setState(eviewStatus_Init);
           pvvv->viewAction(eviewStatus_Init);

           return pvvv;
       }

    }else{
        return pv;
    }
    return NULL;
}

void App::AddView(CView *pView)
{
    if(pView)
    {
        m_pAppView.insert(m_pAppView.begin(),pView);
    }

}

void App::ViewBack()
{
    if(m_pAppViewStack.size() > 1)
    {
        CView* pv = m_pAppViewStack.at(0);
        if(pv)
        {
            EraseView(pv);
            CView* pvv = m_pAppViewStack.at(0);
            QWidget *view = reinterpret_cast<QWidget*>(pv->getView());
            QWidget *_view = reinterpret_cast<QWidget*>(pvv->getView());

            if(view)
            {
                pv->setState(eViewStatus_Inactive);
                pv->viewAction(eViewStatus_Inactive);
                view->hide();
            }
            if(_view)
            {
                pvv->setState(eViewStatus_Active);
                pvv->viewAction(eViewStatus_Active);
                m_pCurView = pvv;
                _view->show();
            }
        }
    }
}

void App::ViewForwardById(int viewId)
{
    CView * pv = findViewById(viewId);
    if( NULL == pv )
    {
        pv =  CreateView(viewId);
    }
    if(m_pAppViewStack.size()>0)
    {
        CView* pvv = m_pAppViewStack.at(0);
        EraseView(pv);
        PushView(pv);
        if(pvv)
        {
            QWidget *view = reinterpret_cast<QWidget*> (pvv->getView());
            if(view)
            {
                pvv->setState(eViewStatus_Inactive);
                pvv->viewAction(eViewStatus_Inactive);
                view->hide();
            }
        }

        QWidget *_view = reinterpret_cast<QWidget*>(pv->getView());
        if(_view)
        {
            pv->setState(eViewStatus_Active);
            pv->viewAction(eViewStatus_Active);
            m_pCurView = pv;
            _view->show();
        }
    }
    else
    {
        QWidget *_view = reinterpret_cast<QWidget*>(pv->getView());
        if(_view)
        {
            PushView(pv);
            pv->setState(eViewStatus_Active);
            pv->viewAction(eViewStatus_Active);
            m_pCurView = pv;
            _view->show();
        }
    }

}

void App::InitViewFactory(ViewFactory *viewFactory)
{
    m_pViewFactory = viewFactory;
}


CView* App::findViewById(int viewId)
{
    vector<CView*>::iterator itor = m_pAppView.begin();
    CView* pv = NULL;
    for(;itor != m_pAppView.end();++itor)
    {
        pv = *itor;
        int id = pv->getViewId();
        if(id == viewId)
        {
            return pv;
        }
    }

    return NULL;
}

void App::EraseView(CView *pView)
{
    if(pView)
    {
        int size = m_pAppViewStack.size();
        for(int i = 0; i < size ;i++)
        {
            if(pView == m_pAppViewStack.at(i))
            {
                m_pAppViewStack.erase(m_pAppViewStack.begin()+i);
                return;
            }
        }
    }
}

void App::PushView(CView *pView)
{
    if( NULL == pView )
    {
        return;
    }

    if(m_pAppViewStack.size() > 0)
    {
        CView* temp = m_pAppViewStack.at(0);
        if(pView == temp || NULL == temp )
        {
            return;
        }
        m_pAppViewStack.insert(m_pAppViewStack.begin(),pView);

    }else
    {
        m_pAppViewStack.insert(m_pAppViewStack.begin(),pView);
    }
}

