#include "SDLVFactory.h"
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"

SDLVFactory::SDLVFactory()
{
}
SDLVFactory * SDLVFactory::m_pInst = NULL;

SDLVFactory *SDLVFactory::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new SDLVFactory;
    }
    return m_pInst;
}

void *SDLVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(SDLApps::Inst()->getMain());
    switch (viewId) {
    case SDLApps::eViewId_SDL_Main:
    {
        SDLAppsView *view = SDLApps::Inst()->GetUIManager()->getSDLAppsView();
        if(view)
        {
            view->setParent(mainwin);
            view->setView(dynamic_cast<QWidget*>(view));
            return  dynamic_cast<CView*>(view);
        }
        INFO("[Error]SDLAppsView is NULL");
        return NULL;
    }
    default:
        return NULL;
    }
}
