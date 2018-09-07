#include "SDLApps.h"
#include "SDLApps/UI/SDLAppsWindow.h"
#include "SDLApps/Data/SDLAppsData.h"
#include "SDLApps/Templates/Common/AppBase.h"

SDLApps* SDLApps::m_pInst = NULL;

SDLApps::SDLApps()
    :m_pUIManager(NULL)
    ,m_bFromNavi(false)
    ,m_bFromMedia(false)
{
    setAppType(AppType_App);
    setAppId(SDLAPPS_ID);
    InitViewFactory(SDLVFactory::Inst());
    setMain(reinterpret_cast<void*>(new SDLAppsWindow()));

    StartSDL();
}

SDLApps *SDLApps::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new SDLApps();
    }
    return m_pInst;
}

void SDLApps::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void SDLApps::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void SDLApps::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void SDLApps::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

UIManager *SDLApps::GetUIManager()
{
    return m_pUIManager;
}

bool SDLApps::FromNavi()
{
    return m_bFromNavi;
}

void SDLApps::SetFromNavi(bool bFromNavi)
{
    m_bFromNavi = bFromNavi;
}

bool SDLApps::FromMedia()
{
    return m_bFromMedia;
}

void SDLApps::SetFromMedia(bool bFromMedia)
{
    m_bFromMedia = bFromMedia;
}

//void SDLApps::UpdateAppList()
//{


//    map<string,string> tempMap;
//    tempMap["UpdateAppList"] = "AppRegistered";
////    myMap["UpdateAppList"] = "AppUnregistered";
//    tempMap["appID"] = "appID00001";
//    tempMap["appName"] = "appName00001";
//    tempMap["appType"] = "NAVIGATION";
//    tempMap["appIcon"] = "path:/xxxxx";
//    HMIFrameWork::Inst()->Notify(NAV_ID, tempMap);
//}

void SDLApps::OnAppShow(string appId, string viewId)
{
    int state = getState();
    INFO("[SDLApps] OnAppShow appId = %s , viewId = %s .",appId.c_str(),viewId.c_str());
    switch (state) {
    case AppStatus_Active:
    {
        ViewForwardById(eViewId_SDL_Main);
        //for navi
        if("Main" == viewId)
        {
            if(this->FromNavi())
            {
                INFO("[SDLApps::OnAppShow]return to APPLINK 1");
                SDLApps::Inst()->SetFromNavi(false);
                m_pUIManager->ExitApp();
                m_pUIManager->onAppShow(ID_APPLINK);
            }
            if(this->FromMedia())
            {
                INFO("[SDLApps::OnAppShow]return to APPLINK 2");
                SDLApps::Inst()->SetFromMedia(false);
                m_pUIManager->ExitApp();
//                m_pUIManager->StopVideoStream();
                m_pUIManager->onAppShow(ID_APPLINK);
            }
        }
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->show();
    }
        break;
    case AppStatus_Inactive:
    {

    }
        break;
    default:
        break;
    }
}

void SDLApps::OnAppHide()
{
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {

    }
        break;
     case AppStatus_Inactive:
    {
        INFO("void SDLApps::OnAppHide()");
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->hide();

        SDLApps::Inst()->SetFromNavi(false);
        SDLApps::Inst()->SetFromMedia(false);
    }
        break;
    default:
        break;
    }
}

void SDLApps::OnNotify(string appId, map<string, string> parameter)
{
    INFO("SDLApps::onNotify appId=%s .",appId.c_str());

    {
        map<string, string>::iterator iter = parameter.find("NaviAppSelected");
        if(iter != parameter.end())
        {
            int appId = QString::fromStdString(iter->second).toInt();
            m_pUIManager->OnAppActivated(appId);
            this->SetFromNavi(true);
//            HMIFrameWork::Inst()->AppShow(SDLAPPS_ID);
        }
    }
    {
        map<string, string>::iterator iter = parameter.find("MediaAppSelected");
        if(iter != parameter.end())
        {
           if(ID_SHOW == m_pUIManager->GetCurViewId())
           {
               HMIFrameWork::Inst()->AppShow(SDLAPPS_ID,"default");
           }
           else
           {
            int appId = QString::fromStdString(iter->second).toInt();
            m_pUIManager->OnAppActivated(appId);
            this->SetFromMedia(true);
           }
//            HMIFrameWork::Inst()->AppShow(SDLAPPS_ID,"Media");
        }
    }

    {
        map<string, string>::iterator iter = parameter.find("PhoneCallStatus");
        if(iter != parameter.end())
        {
            string value = iter->second;
            if(0 == value.compare("true"))
            {
                m_pUIManager->OnPhoneCall(true);
            }
            else
            {
                m_pUIManager->OnPhoneCall(false);
            }
        }
    }
}

void SDLApps::OnReply(string appId, map<string, string> parameter)
{
    Q_UNUSED(appId)

    map<string,string>::const_iterator it = parameter.find("Button");
    if(it!=parameter.end())
    {
        INFO("[SDLApps] OnReply = %s .", QString::fromStdString( it->second).toStdString().c_str());
        if("AudioPassThruFinish" == it->second)
        {
            emit SigAudioPassThruFinish();
        }
        else if("AudioPassThruCancel" == it->second)
        {
            emit SigAudioPassThruCancel();
        }
        else if("AudioPassThruTimeOut" == it->second)
        {
            emit SigAudioPassThruTimeOut();
        }
        else if("DialNumberCall" == it->second)
        {
            emit SigDialNumberCall();
        }
        else if("DialNumberCancel" == it->second)
        {
            emit SigDialNumberCancel();
        }
        else
        {
            //none
        }
    }
}

void SDLApps::OnAppListUpdate()
{
    INFO("SDLApps::OnAppListUpdate");
    {
        //Navi app list
        std::vector<SDLAppInfo> naviAppList = SDLAppsData::GetInstance()->GetNavigationAppList();

        map<string,string> tempMap;
        tempMap["NavigationAppList"] = QString::number(naviAppList.size()).toStdString();
        for(int i = 0; i < naviAppList.size(); ++i)
        {
            INFO("[NaviAppList][%d][%d][%s][%s][%s]", i, naviAppList[i].appId, naviAppList[i].appName.c_str(), naviAppList[i].appIcon.c_str(), naviAppList[i].appType.c_str());

            tempMap[QString("appId").append(QString::number(i)).toStdString()] = QString::number(naviAppList[i].appId).toStdString();
            tempMap[QString("appName").append(QString::number(i)).toStdString()] = naviAppList[i].appName;
            tempMap[QString("appIcon").append(QString::number(i)).toStdString()] = naviAppList[i].appIcon;
            //        tempMap[QString("appType").append(QString::number(i)).toStdString()] = naviAppList[i].appType;
        }
        INFO("[NaviAppList]END total: %ld", naviAppList.size());
        HMIFrameWork::Inst()->Notify(NAV_ID, tempMap);
    }
    {
        //Media app list
        std::vector<SDLAppInfo> mediaAppList = SDLAppsData::GetInstance()->GetMediaAppList();

        map<string,string> tempMap;
        tempMap["MediaAppList"] = QString::number(mediaAppList.size()).toStdString();
        for(int i = 0; i < mediaAppList.size(); ++i)
        {
            INFO("[MediaAppList][%d][%d][%s][%s][%s]", i, mediaAppList[i].appId, mediaAppList[i].appName.c_str(), mediaAppList[i].appIcon.c_str(), mediaAppList[i].appType.c_str());

            tempMap[QString("appId").append(QString::number(i)).toStdString()] = QString::number(mediaAppList[i].appId).toStdString();
            tempMap[QString("appName").append(QString::number(i)).toStdString()] = mediaAppList[i].appName;
            tempMap[QString("appIcon").append(QString::number(i)).toStdString()] = mediaAppList[i].appIcon;
            //        tempMap[QString("appType").append(QString::number(i)).toStdString()] = mediaAppList[i].appType;
        }
        INFO("[MediaAppList]END total: %ld", mediaAppList.size());
        HMIFrameWork::Inst()->Notify(MEDIA_ID, tempMap);
    }
}

void SDLApps::StartSDL()
{
    m_pUIManager  = new UIManager;
    m_pUIManager->loadsdk();

    connect(m_pUIManager, SIGNAL(appListUpdateSignal()), this, SLOT(OnAppListUpdate()));
}
