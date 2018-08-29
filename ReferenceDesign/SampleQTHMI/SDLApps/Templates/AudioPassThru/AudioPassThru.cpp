#include "AudioPassThru.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "SDLApps/app/SDLApps.h"

CAudioPassThru::CAudioPassThru(AppListInterface *pList, QWidget *parent)
    : QWidget(parent)
    , m_pList(pList)
    , m_bShowPopUpAudioPassThru(false)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }
}

void CAudioPassThru::OnAudioPassThruFinish()
{
    INFO("CAudioPassThru::AudioPassThruFinish");
    m_bShowPopUpAudioPassThru = false;
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    AppControl->OnPerformAudioPassThru(0);
}

void CAudioPassThru::OnAudioPassThruCancel()
{
    INFO("CAudioPassThru::AudioPassThruCancel");
    m_bShowPopUpAudioPassThru = false;
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    AppControl->OnPerformAudioPassThru(5);
}

void CAudioPassThru::OnAudioPassThruTimeOut()
{
    INFO("CAudioPassThru::AudioPassThruTimeOut");
    m_bShowPopUpAudioPassThru = false;
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    AppControl->OnPerformAudioPassThru(5);
}

void CAudioPassThru::showEvent(QShowEvent *)
{
    INFO("CAudioPassThru::showEvent show nothing; Show popup view instead.");

    if (AppControl) {
        QString appName = QString::fromStdString(AppControl->getAppName());

        rpcValueInterface &pObj = AppControl->getAudioPassThruJson();
        if (pObj.isNull())
            return;
        rpcValueInterface &jsonParams = pObj["params"];

        QString fieldtext1,fieldtext2;
        if(jsonParams.isMember("audioPassThruDisplayTexts"))
        {
            for(unsigned int i = 0; i < jsonParams["audioPassThruDisplayTexts"].size(); ++i)
            {
                rpcValueInterface  &fieldName = jsonParams["audioPassThruDisplayTexts"][i];

//                QString fieldtext;
                if ("audioPassThruDisplayText1" == fieldName["fieldName"].asString()) {

                    fieldtext1 = fieldName["fieldText"].asString().c_str();
                    INFO("fieldtext1: %s", fieldtext1.toStdString().c_str());
                }
                else if("audioPassThruDisplayText2" == fieldName["fieldName"].asString()) {

                    fieldtext2 = fieldName["fieldText"].asString().c_str();
                    INFO("fieldtext2: %s", fieldtext2.toStdString().c_str());
                }
            }
        }

        string maxDuration;
        if(jsonParams.isMember("maxDuration"))
        {
            maxDuration = jsonParams["maxDuration"].asString();
        }

        bool muteAudio = false;
        if(jsonParams.isMember("muteAudio"))
        {
            muteAudio = jsonParams["muteAudio"].asBool();
        }

        //show popup
        QString contextA = fieldtext1.append("\n").append(fieldtext2);
        ShowPopupAudioPassThru(AppControl->getAppName(), maxDuration, contextA.toStdString());
    }
}

void CAudioPassThru::hideEvent(QHideEvent *)
{
    INFO("CAudioPassThru::hideEvent");
    HidePopupAudioPassThru();
}

void CAudioPassThru::ShowPopupAudioPassThru(const string &appName, const string &duration, const string &contextA)
{
    //TODO:check signal-slot called times
    connect(SDLApps::Inst(),SIGNAL(SigAudioPassThruFinish()),this,SLOT(OnAudioPassThruFinish()),static_cast<Qt::ConnectionType>(Qt::AutoConnection|Qt::UniqueConnection));
    connect(SDLApps::Inst(),SIGNAL(SigAudioPassThruCancel()),this,SLOT(OnAudioPassThruCancel()),static_cast<Qt::ConnectionType>(Qt::AutoConnection|Qt::UniqueConnection));
    connect(SDLApps::Inst(),SIGNAL(SigAudioPassThruTimeOut()),this,SLOT(OnAudioPassThruTimeOut()),static_cast<Qt::ConnectionType>(Qt::AutoConnection|Qt::UniqueConnection));

    m_bShowPopUpAudioPassThru = true;

    map<string,string> msg;
    msg.insert(make_pair("PopUpType","General"));
    msg.insert(make_pair("PopUpId","AudioPassThru"));
    msg.insert(make_pair("Show","True"));
    msg.insert(make_pair("FromAppId",SDLAPPS_ID));
    msg.insert(make_pair("ButtonA","Finish"));
    msg.insert(make_pair("ReplyButtonA","AudioPassThruFinish"));
    msg.insert(make_pair("ButtonB","Cancel"));
    msg.insert(make_pair("ReplyButtonB","AudioPassThruCancel"));
    msg.insert(make_pair("Title",appName));
    msg.insert(make_pair("Time",duration));
    msg.insert(make_pair("TimeOut","AudioPassThruTimeOut"));
    msg.insert(make_pair("ContextA",contextA));

    HMIFrameWork::Inst()->Notify(POPUP_ID,msg);
}

void CAudioPassThru::HidePopupAudioPassThru()
{
    if(m_bShowPopUpAudioPassThru)
    {
        m_bShowPopUpAudioPassThru = false;

        map<string,string> msg;
        msg.insert(make_pair("PopUpType","General"));
        msg.insert(make_pair("PopUpId","AudioPassThru"));
        msg.insert(make_pair("Show","False"));

        HMIFrameWork::Inst()->Notify(POPUP_ID,msg);
    }
}
