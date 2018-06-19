#include "MessageVFactory.h"
#include "Message/app/Message.h"
#include "HMIFrameWork/CView.h"
#include "Message/UI/MessagesView.h"
#include "Message/UI/MessageListView.h"
#include "Message/UI/MessagesNoNewInfoView.h"

MessageVFactory::MessageVFactory()
{
}

MessageVFactory * MessageVFactory::m_pInst = NULL;

MessageVFactory *MessageVFactory::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new MessageVFactory;
    }
    return m_pInst;
}

void *MessageVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(Message::Inst()-> getMain());
    switch (viewId) {
    case Message::eViewId_MessageList:
    {
        MessageListView* view = new MessageListView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Message::eViewId_Messages:
    {
        MessagesView* view = new MessagesView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    } case Message::eViewId_MessagesNoNewInfo:
    {
        MessagesNoNewInfoView* view = new MessagesNoNewInfoView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
