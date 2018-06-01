#include "HVACVFactory.h"
#include "HVAC/app/HVAC.h"
#include "HVAC/UI/HVACFrontView.h"
#include "HMIFrameWork/CView.h"
#include "HVAC/UI/HVACFrontViewOff.h"
#include "HVAC/UI/HVACRearView.h"
#include "HVAC/UI/HVACRearViewOff.h"

HVACVFactory::HVACVFactory()
{
}

HVACVFactory * HVACVFactory::m_pInst = NULL;

HVACVFactory *HVACVFactory::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new HVACVFactory;
    }
    return m_pInst;
}

void *HVACVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(HVAC::Inst()-> getMain());
    switch (viewId) {
    case HVAC::eViewId_Front_On:
    {
        HVACFrontView* view = new HVACFrontView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case HVAC::eViewId_Front_Off:
    {
        HVACFrontViewOff* view = new HVACFrontViewOff(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case HVAC::eViewId_Rear_On:
    {
        HVACRearView* view = new HVACRearView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case HVAC::eViewId_Rear_Off:
    {
        HVACRearView* view = new HVACRearView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
