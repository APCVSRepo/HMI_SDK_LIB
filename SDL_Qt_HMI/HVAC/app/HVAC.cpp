#include "HVAC.h"
#include "HVAC/UI/HVACWindow.h"
#include "HMIFrameWork/HMIFrameWork.h"
HVAC* HVAC::m_pInst = NULL;
HVAC::HVAC()
{

    setAppType(AppType_App);
    setAppId(HVAC_ID);
    InitViewFactory(HVACVFactory::Inst());
    setMain(reinterpret_cast<void*>(new HVACWindow()));
}

HVAC *HVAC::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new HVAC();
    }
    return m_pInst;
}

void HVAC::onAppShow(string appId, string viewId)
{
   connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
   emit SigAppShow(appId,viewId);
}

void HVAC::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void HVAC::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void HVAC::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

void HVAC::OnAppShow(string appId, string viewId)
{
    INFO()<<"onAppShow" << QString::fromStdString(appId) << "viewid " <<QString::fromStdString(viewId);
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {
        if(viewId == "Main")
        {

            ViewForwardById(eViewId_Front_On);
        }
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

void HVAC::OnAppHide()
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

void HVAC::OnNotify(string appId, map<string, string> parameter)
{
    INFO("HVAC::onNotify appId=%s .",appId.c_str());


}

void HVAC::OnReply(string appId, map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("Button");
    if(it!=parameter.end())
    {
        INFO() << "OnReply = " << QString::fromStdString( it->second);
    }
}

