#include "StatusBarVFactory.h"
#include "StatusBar/app/StatusBar.h"
#include "StatusBar/UI/StatusBarView.h"

StatusBarVFactory::StatusBarVFactory()
{
}

StatusBarVFactory * StatusBarVFactory::m_pInst = NULL;

StatusBarVFactory *StatusBarVFactory::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new StatusBarVFactory;
    }
    return m_pInst;
}

void *StatusBarVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(StatusBar::Inst()->getMain());
    switch (viewId) {
    case StatusBar::eViewId_Main:
    {   StatusBarView* view = new StatusBarView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
