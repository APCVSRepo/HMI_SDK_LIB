#include "SDLAppsData.h"
#include "HMIFrameWork/log_interface.h"

#define SDLAPPTEST

SDLAppsData *SDLAppsData::s_pInstance = NULL;

SDLAppsData *SDLAppsData::GetInstance()
{
    if(NULL == s_pInstance)
    {
        s_pInstance = new SDLAppsData;
    }
    return s_pInstance;
}

//void SDLAppsData::AppRegister(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath, std::vector<std::string> &vAppTypes)
//{
//    INFO("SDLAppsData::AppRegister");
//    m_AppInfos.clear();

//    for(int i = 0; i < vAppIDs.size(); ++i)
//    {
//        SDLAppInfo appInfo(vAppIDs[i],vAppNames[i],vIconPath[i],vAppTypes[i]);
//        m_AppInfos.push_back(appInfo);
//    }

//#ifdef SDLAPPTEST
//    SDLAppsData::GetInstance()->PrintAppList();
//#endif
//}

void SDLAppsData::UpdateAppList(std::vector<int> &vAppIDs, std::vector<string> &vAppNames, std::vector<string> &vIconPath, std::vector<string> &vAppTypes)
{
    INFO("SDLAppsData::UpdateAppList");
    m_vAppInfos.clear();

    for(int i = 0; i < vAppIDs.size(); ++i)
    {
        SDLAppInfo appInfo(vAppIDs[i],vAppNames[i],vIconPath[i],vAppTypes[i]);
        m_vAppInfos.push_back(appInfo);
    }

#ifdef SDLAPPTEST
    SDLAppsData::GetInstance()->PrintAppList();
#endif
}

std::vector<SDLAppInfo> SDLAppsData::GetNavigationAppList()
{
    std::vector<SDLAppInfo> result;
    for(int i = 0; i < m_vAppInfos.size(); ++i)
    {
        if("NAVIGATION" == m_vAppInfos[i].appType)
        {
            result.push_back(m_vAppInfos[i]);
        }
    }
    return result;
}

std::vector<SDLAppInfo> SDLAppsData::GetMediaAppList()
{
    std::vector<SDLAppInfo> result;
    for(int i = 0; i < m_vAppInfos.size(); ++i)
    {
        if("MEDIA" == m_vAppInfos[i].appType)
        {
            result.push_back(m_vAppInfos[i]);
        }
    }
    return result;
}

//void SDLAppsData::AppUnRegister(int id)
//{
//    INFO("SDLAppsData::AppUnRegister");
//    std::list<SDLAppInfo>::iterator iter = m_AppInfos.begin();
//    for(iter; iter!=m_AppInfos.end(); ++iter)
//    {
//        if(id == iter->appId)
//        {
//            m_AppInfos.erase(iter);
//            break;
//        }
//    }
//#ifdef SDLAPPTEST
//    SDLAppsData::GetInstance()->PrintAppList();
//#endif
//}

SDLAppsData::SDLAppsData(QObject *parent) :
    QObject(parent)
{
}

void SDLAppsData::PrintAppList()
{
    if(m_vAppInfos.size() <= 0)
    {
        INFO("AppList: [-] Empty");
        return;
    }

    std::vector<SDLAppInfo>::iterator iter = m_vAppInfos.begin();
    int index = 0;
    for(iter; iter != m_vAppInfos.end(); ++iter)
    {
        INFO("AppList: [%2d][%d][%s][%s][%s]", index, iter->appId, iter->appName.c_str(), iter->appIcon.c_str(), iter->appType.c_str());
        ++index;
    }
}
