#include "Phone.h"
#include "Phone/UI/PhoneWindow.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "Phone/data/PhoneData.h"
Phone* Phone::m_pInst = NULL;
Phone::Phone()
{

    m_bOutAppCall = false;
    setAppType(AppType_App);
    setAppId(PHONE_ID);
    InitViewFactory(PhoneVFactory::Inst());
    setMain(reinterpret_cast<void*>(new PhoneWindow()));
}

Phone *Phone::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new Phone();
    }
    return m_pInst;
}

void Phone::onAppShow(string appId, string viewId)
{
   connect(this,SIGNAL(SigAppShow(string,string)),this,SLOT(OnAppShow(string,string)),Qt::UniqueConnection);
   emit SigAppShow(appId,viewId);
}

void Phone::onAppHide()
{
    connect(this,SIGNAL(SigAppHide()),this,SLOT(OnAppHide()),Qt::UniqueConnection);
    emit SigAppHide();
}

void Phone::onNotify(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigNotify(string,map<string,string>)),this,SLOT(OnNotify(string,map<string,string>)),Qt::UniqueConnection);
    emit SigNotify(appId,parameter);
}

void Phone::onReply(string appId, map<string, string> parameter)
{
    connect(this,SIGNAL(SigReply(string,map<string,string>)),this,SLOT(OnReply(string,map<string,string>)),Qt::UniqueConnection);
    emit SigReply(appId,parameter);
}

bool Phone::IsOutAppCall()
{
    return m_bOutAppCall;
}

void Phone::OnAppShow(string appId, string viewId)
{
    INFO()<<"onAppShow" << QString::fromStdString(appId) << "viewid " <<QString::fromStdString(viewId);
    int state = getState();
    switch (state) {
    case AppStatus_Active:
    {
        if("Main" == viewId)
        {

            ViewForwardById(eViewId_KeyBoard);
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

void Phone::OnAppHide()
{
    m_bOutAppCall = false;
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

void Phone::OnNotify(string appId, map<string, string> parameter)
{
    INFO("Phone::onNotify appId=%s .",appId.c_str());
    map<string,string>::const_iterator it = parameter.find("Register");
    if(it != parameter.end())
    {
        string value = it->second;
        if("Finish" == value)
        {
            ViewForwardById(eViewId_KeyBoard);
        }
    }
     it = parameter.find("MessageDialNumber");
    if(it!=parameter.end())
    {
        string value = it->second;

        SPhoneInfo* info = PhoneData::Inst()->findContactsByNumber(QString::fromStdString( value));

        if(NULL != info)
        {
            PhoneData::Inst()->SetCallName(info->FirstName+" " + info->LastName);
            PhoneData::Inst()->SetCallNumber(QString::fromStdString( value));
            PhoneData::Inst()->SetCallTime(0);
            PhoneData::Inst()->SetCallStatus("Call");
            info->date = QDate::currentDate();
            info->time = QTime::currentTime();
            info->number = QString::fromStdString( value);
            PhoneData::Inst()->SetCallInfo(*info);
        }else{
            SPhoneInfo info;
            PhoneData::Inst()->SetCallName(QString::fromStdString( value));
            PhoneData::Inst()->SetCallNumber(QString::fromStdString( value));
            PhoneData::Inst()->SetCallTime(0);
            PhoneData::Inst()->SetCallStatus("Call");
            info.date = QDate::currentDate();
            info.time = QTime::currentTime();
            info.number = QString::fromStdString( value);
            info.FirstName = QString::fromStdString( value);
            PhoneData::Inst()->SetCallInfo(info);
        }


        if(AppStatus_Inactive == getState())
        {
            m_bOutAppCall = true;
            Phone::Inst()->ViewForwardById(Phone::eViewId_Calling);
            PhoneData::Inst()->SetViewId(Phone::eViewId_KeyBoard);
            HMIFrameWork::Inst()->AppShow(PHONE_ID,"Calling");
        }
        INFO() << "OnNotify = " << QString::fromStdString( it->second);
    }

}

void Phone::OnReply(string appId, map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("Button");
    if(it!=parameter.end())
    {
        INFO() << "OnReply = " << QString::fromStdString( it->second);
    }
}

