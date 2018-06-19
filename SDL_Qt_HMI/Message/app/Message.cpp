#include "Message.h"
#include "Message/UI/MessageWindow.h"
#include "HMIFrameWork/HMIFrameWork.h"
Message* Message::m_pInst = NULL;
Message::Message()
{

    setAppType(AppType_App);
    setAppId(MESSAGE_ID);
    InitViewFactory(MessageVFactory::Inst());
    setMain(reinterpret_cast<void*>(new MessageWindow()));
}

Message *Message::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new Message();
    }
    return m_pInst;
}

void Message::onAppShow(string appId, string viewId)
{
   connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
   emit SigAppShow(appId,viewId);
}

void Message::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void Message::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void Message::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

void Message::OnAppShow(string appId, string viewId)
{
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {
        if("Main" == viewId)
        {

            ViewForwardById(eViewId_Messages);
        }
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->raise();
        mainwin->show();


    }
        break;
     case AppStatus_Inactive:

        break;
    default:
        break;
    }
}

void Message::OnAppHide()
{
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {



    }
        break;
     case AppStatus_Inactive:
    {
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->hide();
    }
        break;
    default:
        break;
    }
}

void Message::OnNotify(string appId, map<string, string> parameter)
{

}

void Message::OnReply(string appId, map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("Button");
    if(it!=parameter.end())
    {
    }
}

