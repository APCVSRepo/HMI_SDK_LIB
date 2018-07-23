#include "SDLAppsView.h"
#include "SDLApps/app/SDLApps.h"
#include "SDLApps/Templates/Config/Config.h"
#include "HMIFrameWork/log_interface.h"

SDLAppsView::SDLAppsView(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,CView(SDLApps::eViewId_SDL_Main)
    ,m_pCenter(NULL)
    ,m_pList(pList)
    ,m_bInVideoStream(false)
    ,m_bsdlStatus(false)
{
    this->setGeometry(0, 0, 800, 480);

    m_pCenter = new QWidget(this);
    m_pCenter->setGeometry(0, 40, 800, 480-40);

    this->hide();
}

SDLAppsView::~SDLAppsView() {
    delete m_pCenter;
}

void SDLAppsView::viewAction(int state)
{
    INFO("SDLAppsView viewAction: %d", state);
    if(eviewStatus_Init == state)
    {

    }
    else if(eViewStatus_Inactive == state)
    {

    }
    else
    {
        INFO("SDLAppsView::viewAction eViewStatus_Active");
        if(SDLApps::Inst()->FromNavi())
        {
            SDLApps::Inst()->GetUIManager()->onAppShow(ID_VIDEOSTREAM);
        }
        else if(SDLApps::Inst()->FromMedia())
        {
            SDLApps::Inst()->GetUIManager()->onAppShow(ID_SHOW);
        }else
        {
            SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);     ///<  App List
        }
    }
}

void SDLAppsView::HideAllComponent() {
    //TODO: hide statusbar and quicklanuch???
}

void SDLAppsView::ShowAllComponent() {
    //TODO: show statusbar and quicklanuch???
}

void SDLAppsView::HideMenuBar() {
    //TODO: hide statusbar???
}

void SDLAppsView::ShowMenuBar() {
    //TODO: show statusbar???
}

QWidget *SDLAppsView::CenterWidget() {
    return m_pCenter;
}

void SDLAppsView::SetSDLStatus(bool bConnect) {
    m_bsdlStatus = bConnect;
    //TODO: Update display of SDL connect status Icon??? Currently is not supported.
}
