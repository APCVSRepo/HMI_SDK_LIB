#include "NavigationVFactory.h"
#include "Navigation/app/Navigation.h"
#include "Navigation/UI/NavigationView.h"

NavigationVFactory::NavigationVFactory()
{
}

NavigationVFactory * NavigationVFactory::m_pInst = NULL;

NavigationVFactory *NavigationVFactory::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new NavigationVFactory;
    }
    return m_pInst;
}

void *NavigationVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(Navi::Inst()->getMain());
    switch (viewId) {
    case Navi::eViewId_Main:
    {
        NavigationView* view = new NavigationView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
