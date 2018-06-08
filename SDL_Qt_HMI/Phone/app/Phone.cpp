#include "Phone.h"
#include "Phone/UI/PhoneWindow.h"
#include "HMIFrameWork/HMIFrameWork.h"
Phone* Phone::m_pInst = NULL;
Phone::Phone()
{

    setAppType(AppType_App);
    setAppId(PHONE_ID);
    InitViewFactory(PhoneVFactory::Inst());
    setMain(reinterpret_cast<void*>(new PhoneWindow()));
}

Phone *Phone::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new Phone();
    }
    return m_pInst;
}

void Phone::onAppShow(string appId, string viewId)
{
   connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
   emit SigAppShow(appId,viewId);
}

void Phone::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void Phone::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void Phone::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

void Phone::OnAppShow(string appId, string viewId)
{
    INFO()<<"onAppShow" << QString::fromStdString(appId) << "viewid " <<QString::fromStdString(viewId);
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {
        if("Main" == viewId)
        {

            ViewForwardById(eViewId_KeyBoard);
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

void Phone::OnAppHide()
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

void Phone::OnNotify(string appId, map<string, string> parameter)
{
    INFO("Phone::onNotify appId=%s .",appId.c_str());


}

void Phone::OnReply(string appId, map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("Button");
    if(it!=parameter.end())
    {
        INFO() << "OnReply = " << QString::fromStdString( it->second);
    }
}

