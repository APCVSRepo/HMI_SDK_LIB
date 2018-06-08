#include "VR.h"
#include "VR/UI/VRWindow.h"
#include "VR/Factory/VRVFactory.h"
#include "HMIFrameWork/log_interface.h"

VR* VR::m_pInst = NULL;

VR::VR()
{
    setAppType(AppType_App);
    setAppId(VR_ID);
    InitViewFactory(VRVFactory::Inst());
    setMain(reinterpret_cast<void*>(new VRWindow()));
}

VR *VR::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new VR();
    }
    return m_pInst;
}

void VR::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void VR::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void VR::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void VR::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

const std::vector<VRAppInfo> &VR::GetAppList() const
{
    return m_vVRAppList;
}

void VR::OnAppShow(string appId, string viewId)
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

void VR::OnAppHide()
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

void VR::OnNotify(string appId, map<string, string> parameter)
{
    INFO("VR::onNotify appId=%s .",appId.c_str());

    {
        map<string, string>::iterator iter = parameter.find("VRAppList");
        if(iter != parameter.end())
        {
            m_vVRAppList.clear();

            string str = iter->second;
            int appCount = QString::fromStdString(str).toInt();
            INFO()<<"VR::OnNotify:VRAppList:"<<appCount;

            for(int i = 0; i < appCount; ++i)
            {
                VRAppInfo appInfo;

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

                m_vVRAppList.push_back(appInfo);
                INFO()<<"Navigation::OnNotify["<<i<<"]"<<m_vVRAppList[i].appId<<" "<<m_vVRAppList[i].appName.c_str()
                       <<" "<<m_vVRAppList[i].appIcon.c_str();
            }

            emit SigUpdateAppList();
        }
        INFO()<<"VR::OnNotify:m_vVRAppList.size():"<<m_vVRAppList.size();
    }
}

void VR::OnReply(string appId, map<string, string> parameter)
{

}
