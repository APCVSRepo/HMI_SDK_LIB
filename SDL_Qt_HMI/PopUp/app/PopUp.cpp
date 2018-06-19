#include "PopUp.h"
#include "PopUp/UI/PopUpWindow.h"
#include "PopUp/Factory/PopUpVFactory.h"
#include "HMIFrameWork/log_interface.h"

#define ENABLE_POPUP_TEST

PopUp* PopUp::m_pInst = NULL;

PopUp::PopUp()
{
    setAppType(AppType_Decorators);
    setAppId(POPUP_ID);
    InitViewFactory(PopUpVFactory::Inst());
    setMain(reinterpret_cast<void*>(new PopUpWindow()));
}

PopUp *PopUp::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new PopUp();
    }
    return m_pInst;
}

void PopUp::onAppShow(string appId, string viewId)
{
    connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
    emit SigAppShow(appId,viewId);
}

void PopUp::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void PopUp::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void PopUp::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

void PopUp::OnAppShow(string appId, string viewId)
{
        setState(AppStatus_Active);
        ViewForwardById(eViewId_Main);
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->raise();
        mainwin->show();
}

void PopUp::OnAppHide()
{
    INFO("[PopUp] OnAppHide %d .",getState());
        setState(AppStatus_Inactive);
        QWidget* mainwin = reinterpret_cast<QWidget*>(getMain());
        mainwin->hide();
}

void PopUp::OnNotify(string appId, map<string, string> parameter)
{
    INFO("PopUp::onNotify appId=%s .",appId.c_str());

#ifdef ENABLE_POPUP_TEST
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
         it = parameter.find("PopUpId");
         if(it != parameter.end())
         {
            emit SigPopUpNotify(appId, parameter);
         }
     }
}

void PopUp::OnReply(string appId, map<string, string> parameter)
{

}
