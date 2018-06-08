#include "Home.h"
#include "Home/UI/HomeWindow.h"
#include "HMIFrameWork/HMIFrameWork.h"
Home* Home::m_pInst = NULL;
Home::Home()
    :m_bNotifyBTShow(false)
    ,m_NotifyBTShowId("")
{

    setAppType(AppType_App);
    setAppId(HOME_ID);
    InitViewFactory(HomeVFactory::Inst());
    setMain(reinterpret_cast<void*>(new HomeWindow()));
}

Home *Home::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new Home();
    }
    return m_pInst;
}

void Home::onAppShow(string appId, string viewId)
{
   connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
   emit SigAppShow(appId,viewId);
}

void Home::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}
void Home::HomeClicked()
{
   HMIFrameWork::Inst()->AppShow(HOME_ID);
}

void Home::SDLAppsClicked()
{
    HMIFrameWork::Inst()->AppShow(SDLAPPS_ID);
}

void Home::HVACClicked()
{
    HMIFrameWork::Inst()->AppShow(HVAC_ID);
}

void Home::MediaClicked()
{
    HMIFrameWork::Inst()->AppShow(MEDIA_ID);
}

void Home::MessageClicked()
{
    HMIFrameWork::Inst()->AppShow(MESSAGE_ID);
}

void Home::NavClicked()
{
    HMIFrameWork::Inst()->AppShow(NAV_ID);
}

void Home::PhoneClicked()
{
    HMIFrameWork::Inst()->AppShow(PHONE_ID);
}

void Home::SettingsClicked()
{
    map<string,string> p;
    p.insert(make_pair("Show","SettingsMain"));
    HMIFrameWork::Inst()->Notify(HOME_ID,p);
}

void Home::WeatherClicked()
{
    HMIFrameWork::Inst()->AppShow(WEATHER_ID);
}

bool Home::SetNotifyBTShowStatus(bool isShow)
{
    m_bNotifyBTShow = isShow;
    if(!isShow)
    {
       m_NotifyBTShowId = "";
    }
}

bool Home::GetNotifyBTShowStatus()
{
    return m_bNotifyBTShow;
}

string Home::GetNotifyBTShowId()
{
    return m_NotifyBTShowId;
}
void Home::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void Home::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

void Home::OnAppShow(string appId, string viewId)
{
    INFO()<<"onAppShow" << QString::fromStdString(appId) << "viewid " <<QString::fromStdString(viewId);
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {
        if("Main" == viewId)
        {
            ViewForwardById(eViewId_Main);
        }else if("SettingsMain" == viewId)
        {
            ViewForwardById(eViewId_Settings_Main);
        }
        else if("BootAnimation" == viewId)
        {
            ViewForwardById(eViewId_BootAnimation);
        }else if("BTSetting" == viewId)
        {
            ViewForwardById(eViewId_Settings_BT);
        }
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

void Home::OnAppHide()
{
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {



    }
        break;
     case AppStatus_Inactive:
    {
        if(Home::Inst()->GetNotifyBTShowStatus())
        {
            Home::Inst()->SetNotifyBTShowStatus(false);
        }
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->hide();
    }
        break;
    default:
        break;
    }
}

void Home::OnNotify(string appId, map<string, string> parameter)
{
    INFO("Home::onNotify appId=%s .",appId.c_str());

    map<string,string>::const_iterator it = parameter.find("AppClick");
    if(it!=parameter.end())
    {
        string type = it->second;
        if(HOME_ID == type)
        {
            HomeClicked();
        }else if(PHONE_ID == type)
        {
            PhoneClicked();
        }else if(SETTINGS_ID == type)
        {
            SettingsClicked();
        }else if(MEDIA_ID == type)
        {
            MediaClicked();
        }else if(HVAC_ID == type)
        {
            HVACClicked();
        }else if(WEATHER_ID == type)
        {
            WeatherClicked();
        }else if(SDLAPPS_ID == type)
        {
            SDLAppsClicked();
        }else if(MESSAGE_ID == type)
        {
            MessageClicked();
        }else if(NAV_ID == type)
        {
            NavClicked();
        }
    }
    it = parameter.find("QuickMove");
    if(it!=parameter.end())
    {
        string type = it->second;
        emit SigQuickMove(QString::fromStdString(type));
    }

    it = parameter.find("Show");
    if(it!=parameter.end())
    {

        string type = it->second;
        INFO()<<QString::fromStdString(type);

        if("SettingsMain" ==  type)
        {
            if(AppStatus_Active == getState())
            {
                INFO()<<" SettingsMain";
                ViewForwardById(eViewId_Settings_Main);
            }else
            {
                HMIFrameWork::Inst()->AppShow(HOME_ID,"SettingsMain");
            }
        }
    }
    it = parameter.find("action");
    if(it!=parameter.end())
    {
        string type = it->second;
        if("BootAnimationFinish" == type)
        {
            ViewForwardById(eViewId_Main);
            HMIFrameWork::Inst()->AppShow(STATUSBAR_ID);
            HMIFrameWork::Inst()->AppShow(QUICKLANUCH_ID);
        }
    }
    it = parameter.find("BTSetting");
    if(it!=parameter.end())
    {
        string type = it->second;
        if("Show" == type)
        {
            m_bNotifyBTShow = true;
            it = parameter.find("FromAppId");
            if(it!=parameter.end())
            {
                m_NotifyBTShowId = it->second;
            }
            if(getState() != AppStatus_Active)
            {
                HMIFrameWork::Inst()->AppShow(HOME_ID,"BTSetting");
            }else if(AppStatus_Active == getState())
            {
                ViewForwardById(eViewId_Settings_BT);
            }
        }
    }
}

void Home::OnReply(string appId, map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("Button");
    if(it!=parameter.end())
    {
        INFO() << "OnReply = " << QString::fromStdString( it->second);
    }
}

