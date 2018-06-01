#include "PhoneVFactory.h"
#include "Phone/app/Phone.h"
#include "Phone/UI/KeyBoardView.h"
#include "HMIFrameWork/CView.h"
#include "Phone/UI/ContactsView.h"
#include "Phone/UI/RecentsView.h"
#include "Phone/UI/ContactsDetailsView.h"
PhoneVFactory::PhoneVFactory()
{
}

PhoneVFactory * PhoneVFactory::m_pInst = NULL;

PhoneVFactory *PhoneVFactory::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new PhoneVFactory;
    }
    return m_pInst;
}

void *PhoneVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(Phone::Inst()-> getMain());
    switch (viewId) {
    case Phone::eViewId_KeyBoard:
    {
        KeyBoardView* view = new KeyBoardView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Phone::eViewId_Contacts:
    {
        ContactsView* view = new ContactsView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Phone::eViewId_Recents:
    {
        RecentsView* view = new RecentsView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Phone::eViewId_ContactsDetails:
    {
        ContactsDetailsView* view = new ContactsDetailsView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
