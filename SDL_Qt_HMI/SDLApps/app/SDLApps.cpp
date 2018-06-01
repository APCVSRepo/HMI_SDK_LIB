#include "SDLApps.h"
#include "SDLApps/UI/SDLAppsWindow.h"
SDLApps* SDLApps::m_pInst = NULL;

SDLApps::SDLApps()
{
    setAppType(AppType_App);
    setAppId(SDLAPPS_ID);
    InitViewFactory(SDLVFactory::Inst());
    setMain(reinterpret_cast<void*>(new SDLAppsWindow()));
}

SDLApps *SDLApps::Inst()
{
    if(m_pInst == NULL)
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

void SDLApps::OnAppShow(string appId, string viewId)
{
    int state = getState();
    INFO()<<" SDLApps appid = " << QString::fromStdString(appId) << "viewId" << QString::fromStdString( viewId);
    switch (state) {
    case AppStatus_Active:
    {
        ViewForwardById(eViewId_SDL_Main);
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
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->hide();
    }
        break;
    default:
        break;
    }
}

void SDLApps::OnNotify(string appId, map<string, string> parameter)
{

}

void SDLApps::OnReply(string appId, map<string, string> parameter)
{

}
