#include "VRVFactory.h"
#include "VR/app/VR.h"
#include "VR/UI/VRView.h"
#include "VR/UI/VRInteractionView.h"

VRVFactory::VRVFactory()
{
}

VRVFactory * VRVFactory::m_pInst = NULL;

VRVFactory *VRVFactory::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new VRVFactory;
    }
    return m_pInst;
}

void *VRVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(VR::Inst()->getMain());
    switch (viewId) {
    case VR::eViewId_Main:
    {
        VRView* view = new VRView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case VR::eViewId_Interaction:
    {
        VRInteractionView* view = new VRInteractionView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
