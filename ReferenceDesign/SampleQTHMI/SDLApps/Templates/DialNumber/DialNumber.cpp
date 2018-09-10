#include "DialNumber.h"
#include <string>
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "SDLApps/app/SDLApps.h"

using std::string;

CDialNumber::CDialNumber(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_bShowPopUpDialNumber(false)
    ,m_dialNumber()
{
}

void CDialNumber::OnDialNumberCall()
{
    INFO("CDialNumber::OnDialNumberCall");
    m_bShowPopUpDialNumber = false;
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    AppControl->OnDialNumber(0);

    INFO("CDialNumber::OnDialNumberCall: %s",m_dialNumber.toStdString().c_str());
    map<string,string> p;
    p.insert(make_pair("MessageDialNumber",m_dialNumber.toStdString()));
    HMIFrameWork::Inst()->Notify(PHONE_ID,p);
}

void CDialNumber::OnDialNumberCancel()
{
    INFO("CDialNumber::OnDialNumberCancel");
    m_bShowPopUpDialNumber = false;
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    //HMI is busy with higher priority RPC
    AppControl->OnDialNumber(5);
}

void CDialNumber::showEvent(QShowEvent *)
{
    INFO("CDialNumber::showEvent show nothing; Show popup view instead.");

    if (AppControl) {
        QString appName = QString::fromStdString(AppControl->getAppName());

        rpcValueInterface &pObj = AppControl->getDialNumberJson();
        if (pObj.isNull())
            return;
        rpcValueInterface &jsonParams = pObj["params"];

        if(jsonParams.isMember("number"))
        {
            m_dialNumber = QString::fromStdString(jsonParams["number"].asString());
        }

        ShowPopupDialNumber(appName, m_dialNumber);
    }
}

void CDialNumber::hideEvent(QHideEvent *)
{
    HidePopupDialNumber();
}

void CDialNumber::ShowPopupDialNumber(const QString &appName, const QString &dialNumber)
{
    INFO("CDialNumber::ShowPopupDialNumber: %s, %s", appName.toStdString().c_str(), dialNumber.toStdString().c_str());
    connect(SDLApps::Inst(),SIGNAL(SigDialNumberCall()),this,SLOT(OnDialNumberCall()),static_cast<Qt::ConnectionType>(Qt::AutoConnection|Qt::UniqueConnection));
    connect(SDLApps::Inst(),SIGNAL(SigDialNumberCancel()),this,SLOT(OnDialNumberCancel()),static_cast<Qt::ConnectionType>(Qt::AutoConnection|Qt::UniqueConnection));

    QString contextA =
            appName + " is trying to call:\n" +
            dialNumber +
            "\nPress \"Call\" to dial or \"Cancel\" to close";

    m_bShowPopUpDialNumber = true;

    map<string,string> msg;
    msg.insert(make_pair("PopUpType","General"));
    msg.insert(make_pair("PopUpId","DialNumber"));
    msg.insert(make_pair("Show","True"));
    msg.insert(make_pair("FromAppId",SDLAPPS_ID));
    msg.insert(make_pair("ButtonA","Call"));
    msg.insert(make_pair("ReplyButtonA","DialNumberCall"));
    msg.insert(make_pair("ButtonB","Cancel"));
    msg.insert(make_pair("ReplyButtonB","DialNumberCancel"));
    msg.insert(make_pair("ContextA",contextA.toStdString()));

    HMIFrameWork::Inst()->Notify(POPUP_ID,msg);
    INFO("HMIFrameWork::Inst()->Notify(POPUP_ID,msg);");
}

void CDialNumber::HidePopupDialNumber()
{
    if(m_bShowPopUpDialNumber)
    {
        m_bShowPopUpDialNumber = false;

        map<string,string> msg;
        msg.insert(make_pair("PopUpType","General"));
        msg.insert(make_pair("PopUpId","DialNumber"));
        msg.insert(make_pair("Show","False"));

        HMIFrameWork::Inst()->Notify(POPUP_ID,msg);
    }
}
