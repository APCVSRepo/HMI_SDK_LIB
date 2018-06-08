#include "Media.h"
#include "Media/UI/MediaWindow.h"
#include "Media/Factory/MediaVFactory.h"
#include "HMIFrameWork/log_interface.h"

Media* Media::m_pInst = NULL;

Media::Media()
{
    setAppType(AppType_App);
    setAppId(MEDIA_ID);
    InitViewFactory(MediaVFactory::Inst());
    setMain(reinterpret_cast<void*>(new MediaWindow()));
}

Media *Media::Inst()
{
    if(NULL == m_pInst )
    {
        m_pInst = new Media();
    }
    return m_pInst;
}

void Media::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void Media::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void Media::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void Media::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

const std::vector<MediaAppInfo> &Media::GetAppList() const
{
    return m_vMediaAppList;
}

void Media::OnAppShow(string appId, string viewId)
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

void Media::OnAppHide()
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

void Media::OnNotify(string appId, map<string, string> parameter)
{
    INFO("Media::onNotify appId=%s .",appId.c_str());

    {
        map<string, string>::iterator iter = parameter.find("MediaAppList");
        if(iter != parameter.end())
        {
            m_vMediaAppList.clear();

            string str = iter->second;
            int appCount = QString::fromStdString(str).toInt();
            INFO()<<"Media::OnNotify:MediaAppList:"<<appCount;

            for(int i = 0; i < appCount; ++i)
            {
                MediaAppInfo appInfo;

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

                m_vMediaAppList.push_back(appInfo);
                INFO()<<"Navigation::OnNotify["<<i<<"]"<<m_vMediaAppList[i].appId<<" "<<m_vMediaAppList[i].appName.c_str()
                       <<" "<<m_vMediaAppList[i].appIcon.c_str();
            }

            emit SigUpdateAppList();
        }
        INFO()<<"Media::OnNotify:m_vMediaAppList.size():"<<m_vMediaAppList.size();
    }
}

void Media::OnReply(string appId, map<string, string> parameter)
{

}
