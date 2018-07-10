#include "MediaVFactory.h"
#include "Media/app/Media.h"
#include "Media/UI/MediaView.h"

MediaVFactory::MediaVFactory()
{
}

MediaVFactory * MediaVFactory::m_pInst = NULL;

MediaVFactory *MediaVFactory::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new MediaVFactory;
    }
    return m_pInst;
}

void *MediaVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(Media::Inst()->getMain());
    switch (viewId) {
    case Media::eViewId_Main:
    {
        MediaView* view = new MediaView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
