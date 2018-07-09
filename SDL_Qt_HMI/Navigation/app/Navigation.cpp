#include "Navigation.h"
#include "Navigation/UI/NavigationWindow.h"
#include "Navigation/Factory/NavigationVFactory.h"
#include "HMIFrameWork/log_interface.h"

Navi* Navi::m_pInst = NULL;

Navi::Navi()
{
    setAppType(AppType_App);
    setAppId(NAV_ID);
    InitViewFactory(NavigationVFactory::Inst());
    setMain(reinterpret_cast<void*>(new NavigationWindow()));
}

Navi *Navi::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new Navi();
    }
    return m_pInst;
}

void Navi::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void Navi::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void Navi::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void Navi::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

const std::vector<NaviAppInfo> &Navi::GetAppList() const
{
    return m_vNaviAppList;
}

void Navi::OnAppShow(string appId, string viewId)
{
    INFO("onAppShow:%s, viewId:%s", appId.c_str(), viewId.c_str());
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {
        ViewForwardById(eViewId_Main);
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->show();


    }
        break;
     case AppStatus_Inactive:

        break;
    default:
        break;
    }
}

void Navi::OnAppHide()
{
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {



    }
        break;
     case AppStatus_Inactive:
    {
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->hide();
    }
        break;
    default:
        break;
    }
}

void Navi::OnNotify(string appId, map<string, string> parameter)
{
    INFO("Navi::onNotify appId=%s .",appId.c_str());

    {
        map<string, string>::iterator iter = parameter.find("NavigationAppList");
        if(iter != parameter.end())
        {
            m_vNaviAppList.clear();

            string str = iter->second;
            int appCount = QString::fromStdString(str).toInt();

            for(int i = 0; i < appCount; ++i)
            {
                NaviAppInfo appInfo;

                map<string, string>::iterator iter = parameter.find(QString("appId").append(QString::number(i)).toStdString());
                if(iter != parameter.end())
                {
                    appInfo.appId = QString::fromStdString(iter->second).toInt();
                }

                iter = parameter.find(QString("appName").append(QString::number(i)).toStdString());
                if(iter != parameter.end())
                {
                    appInfo.appName = iter->second;
                }

                iter = parameter.find(QString("appIcon").append(QString::number(i)).toStdString());
                if(iter != parameter.end())
                {
                    appInfo.appIcon = iter->second;
                }

                m_vNaviAppList.push_back(appInfo);
            }

            emit SigUpdateAppList();
        }
    }

}

void Navi::OnReply(string appId, map<string, string> parameter)
{

}
