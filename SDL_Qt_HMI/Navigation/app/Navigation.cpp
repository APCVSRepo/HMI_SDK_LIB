#include "Navigation.h"
#include "Navigation/UI/NavigationWindow.h"
#include "Navigation/Factory/NavigationVFactory.h"
#include "HMIFrameWork/log_interface.h"

Navigation* Navigation::m_pInst = NULL;

Navigation::Navigation()
{
    setAppType(AppType_App);
    setAppId(NAV_ID);
    InitViewFactory(NavigationVFactory::Inst());
    setMain(reinterpret_cast<void*>(new NavigationWindow()));
}

Navigation *Navigation::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new Navigation();
    }
    return m_pInst;
}

void Navigation::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void Navigation::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void Navigation::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void Navigation::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

const std::vector<NaviAppInfo> &Navigation::GetAppList() const
{
    return m_vNaviAppList;
}

void Navigation::OnAppShow(string appId, string viewId)
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

void Navigation::OnAppHide()
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

void Navigation::OnNotify(string appId, map<string, string> parameter)
{
    INFO("Navigation::onNotify appId=%s .",appId.c_str());

    {
        map<string, string>::iterator iter = parameter.find("NavigationAppList");
        if(iter != parameter.end())
        {
            m_vNaviAppList.clear();

            string str = iter->second;
            int appCount = QString::fromStdString(str).toInt();
            INFO()<<"Navigation::OnNotify:NavigationAppList:"<<appCount;

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
                INFO()<<"Navigation::OnNotify["<<i<<"]"<<m_vNaviAppList[i].appId<<" "<<m_vNaviAppList[i].appName.c_str()
                       <<" "<<m_vNaviAppList[i].appIcon.c_str();
            }

            emit SigUpdateAppList();
        }
        INFO()<<"Navigation::OnNotify:m_vNaviAppList.size():"<<m_vNaviAppList.size();
    }

}

void Navigation::OnReply(string appId, map<string, string> parameter)
{

}
