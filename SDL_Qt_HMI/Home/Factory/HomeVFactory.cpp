#include "HomeVFactory.h"
#include "Home/app/Home.h"
#include "Home/UI/HomeView.h"
#include "HMIFrameWork/CView.h"
HomeVFactory::HomeVFactory()
{
}

HomeVFactory * HomeVFactory::m_pInst = NULL;

HomeVFactory *HomeVFactory::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new HomeVFactory;
    }
    return m_pInst;
}

void *HomeVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(Home::Inst()-> getMain());
    switch (viewId) {
    case Home::eViewId_Main:
    {   HomeView* view = new HomeView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
