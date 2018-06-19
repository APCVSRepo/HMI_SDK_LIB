#include "Prompt.h"
#include "Prompt/UI/PromptWindow.h"
#include "Prompt/Factory/PromptVFactory.h"
#include "HMIFrameWork/log_interface.h"

#define ENABLE_Prompt_TEST

Prompt* Prompt::m_pInst = NULL;

Prompt::Prompt()
{
    setAppType(AppType_Decorators);
    setAppId(PROMPT_ID);
    InitViewFactory(PromptVFactory::Inst());
    setMain(reinterpret_cast<void*>(new PromptWindow()));
}

Prompt *Prompt::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new Prompt();
    }
    return m_pInst;
}

void Prompt::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void Prompt::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void Prompt::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void Prompt::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

void Prompt::UpdateWIndSize(const QSize &size)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
    if(NULL != mainwin)
    {
        mainwin->setGeometry(QRect(0,40,800,size.height()));
    }
}

void Prompt::OnAppShow(string appId, string viewId)
{
        setState(AppStatus_Active);
        ViewForwardById(eViewId_Main);
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->raise();
        mainwin->show();
}

void Prompt::OnAppHide()
{
    INFO("[Prompt] OnAppHide ");

    setState(AppStatus_Inactive);
    QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
    mainwin->hide();
}

void Prompt::OnNotify(string appId, map<string, string> parameter)
{
    INFO("Prompt::onNotify appId=%s .",appId.c_str());

#ifdef ENABLE_Prompt_TEST
//    //Icon staus change
//    emit SigIconStatusChanged(ICON_MSG, true, 34);
//    emit SigIconStatusChanged(ICON_USB, true);
//    emit SigIconStatusChanged(ICON_BT, true);
//    emit SigIconStatusChanged(ICON_WIFI, true);

//    //loading status change
//    emit SigLoadingStatusChanged(true);

//    //temperature change
//    emit SigTemperatureChanged(22);

//    //temperature unit change
//    emit SigTemperatureUnitChanged(true);
#endif
     map<string,string>::const_iterator it = parameter.find("Register");
     if(it != parameter.end())
     {
         string value = it->second;
         if("Finish" == value)
         {
             CreateView(eViewId_Main);
         }
     }
     else
     {
         it = parameter.find("PromptId");
         if(it != parameter.end())
         {
            emit SigPromptNotify(appId, parameter);
         }
     }
}

void Prompt::OnReply(string appId, map<string, string> parameter)
{

}
