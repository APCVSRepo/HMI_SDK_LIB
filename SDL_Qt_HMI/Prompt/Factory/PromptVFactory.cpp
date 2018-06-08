#include "PromptVFactory.h"
#include "Prompt/app/Prompt.h"
#include "Prompt/UI/PromptViewUI.h"

PromptVFactory::PromptVFactory()
{
}

PromptVFactory * PromptVFactory::m_pInst = NULL;

PromptVFactory *PromptVFactory::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new PromptVFactory;
    }
    return m_pInst;
}

void *PromptVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(Prompt::Inst()->getMain());
    switch (viewId) {
    case Prompt::eViewId_Main:
    {
        PromptViewUI* view = new PromptViewUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
