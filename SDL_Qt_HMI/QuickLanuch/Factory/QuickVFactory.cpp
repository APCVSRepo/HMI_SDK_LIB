#include "QuickVFactory.h"
#include "QuickLanuch/app/QuickLanuch.h"
#include "QuickLanuch/UI/QuickLanuchView.h"

QuickVFactory::QuickVFactory()
{
}

QuickVFactory * QuickVFactory::m_pInst = NULL;

QuickVFactory *QuickVFactory::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new QuickVFactory;
    }
    return m_pInst;
}

void *QuickVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(QuickLanuch::Inst()-> getMain());
    switch (viewId) {
    case QuickLanuch::eViewId_Main:
    {   QuickLanuchView* view = new QuickLanuchView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
