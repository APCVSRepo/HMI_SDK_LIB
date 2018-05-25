#include "StatusBar.h"
#include "StatusBar/UI/StatusBarWindow.h"
#include "StatusBar/Factory/StatusBarVFactory.h"
#include "HMIFrameWork/log_interface.h"

#define ENABLE_STATUSBAR_TEST

StatusBar* StatusBar::m_pInst = NULL;

StatusBar::StatusBar()
{
    setAppType(AppType_Decorators);
    setAppId(STATUSBAR_ID);
    InitViewFactory(StatusBarVFactory::Inst());
    setMain(reinterpret_cast<void*>(new StatusBarWindow()));
}

StatusBar *StatusBar::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new StatusBar();
    }
    return m_pInst;
}

void StatusBar::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void StatusBar::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void StatusBar::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void StatusBar::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void StatusBar::OnAppShow(string appId, string viewId)
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

void StatusBar::OnAppHide()
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

void StatusBar::OnNotify(string appId, map<string, string> parameter)
{
    INFO("StatusBar::onNotify appId=%s .",appId.c_str());

#ifdef ENABLE_STATUSBAR_TEST
    //Icon staus change
    emit SigIconStatusChanged(ICON_MSG, true, 34);
    emit SigIconStatusChanged(ICON_USB, true);
    emit SigIconStatusChanged(ICON_BT, true);
    emit SigIconStatusChanged(ICON_WIFI, true);

    //loading status change
    emit SigLoadingStatusChanged(true);

    //temperature change
    emit SigTemperatureChanged(22);

    //temperature unit change
    emit SigTemperatureUnitChanged(true);
#endif
}

void StatusBar::OnReply(string appId, map<string, string> parameter)
{

}
