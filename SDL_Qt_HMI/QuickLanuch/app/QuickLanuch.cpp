#include "QuickLanuch.h"
#include "QuickLanuch/Factory/QuickVFactory.h"
#include "QuickLanuch/UI/QuickLanuchWindow.h"
QuickLanuch* QuickLanuch::m_pInst = NULL;

QuickLanuch::QuickLanuch()
{
    setAppType(AppType_Decorators);
    setAppId(QUICKLANUCH_ID);
    InitViewFactory(QuickVFactory::Inst());
    setMain(reinterpret_cast<void*>(new QuickLanuchWindow()));
}


QuickLanuch *QuickLanuch::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new QuickLanuch();
    }
    return m_pInst;
}

void QuickLanuch::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void QuickLanuch::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void QuickLanuch::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void QuickLanuch::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);

}

void QuickLanuch::OnAppShow(string appId, string viewId)
{
    INFO()<<"onAppShow" << QString::fromStdString(appId) << "viewid " <<QString::fromStdString(viewId);
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {
        ViewForwardById(eViewId_Main);
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->raise();
        mainwin->show();
    }
        break;
     case AppStatus_Inactive:

        break;
    default:
        break;
    }
}

void QuickLanuch::OnAppHide()
{
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {



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

void QuickLanuch::OnNotify(string appId, map<string, string> parameter)
{
    INFO("QuickLanuch::onNotify appId=%s .",appId.c_str());

    map<string,string>::const_iterator it = parameter.find("AppEditStatus");
    if(it!=parameter.end())
    {
        string status = it->second;
        if("true" == status)
        {
            QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
            mainwin->lower();
            mainwin->show();
        }else if("false" == status)
        {
            QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
            mainwin->raise();
            mainwin->show();
        }
    }
    it = parameter.find("QuickLanuchAppType");
    if(it!=parameter.end())
    {
        string type = it->second;
        int x = -1;
        int y = -1;
        it = parameter.find("QuickLanuchX");
        if(it!=parameter.end())
        {
            x = QString::fromStdString( it->second).toInt();
        }
        it = parameter.find("QuickLanuchY");
        if(it!=parameter.end())
        {
            y = QString::fromStdString( it->second).toInt();
        }

        emit SigAppInfo(x,y,type);
    }
    //QuickTriggerDomainStatus
    it = parameter.find("QuickTriggerDomainStatus");
    if(it!=parameter.end())
    {
        string status = it->second;
        string type = "";
        it = parameter.find("Type");
        if(it!=parameter.end())
        {
            type = it->second;
        }
        emit SigEnterQuick(QString::fromStdString(status),QString::fromStdString(type));
    }

}

void QuickLanuch::OnReply(string appId, map<string, string> parameter)
{

}


