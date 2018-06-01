#include "PopUpVFactory.h"
#include "PopUp/app/PopUp.h"
#include "PopUp/UI/PopUpViewUI.h"

PopUpVFactory::PopUpVFactory()
{
}

PopUpVFactory * PopUpVFactory::m_pInst = NULL;

PopUpVFactory *PopUpVFactory::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new PopUpVFactory;
    }
    return m_pInst;
}

void *PopUpVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(PopUp::Inst()->getMain());
    switch (viewId) {
    case PopUp::eViewId_Main:
    {
        PopUpViewUI* view = new PopUpViewUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
