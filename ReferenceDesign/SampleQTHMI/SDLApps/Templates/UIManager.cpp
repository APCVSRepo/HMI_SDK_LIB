#include "UIManager.h"
#ifdef ANDROID
#include "android/log.h"
#include <unistd.h>
#endif
#if defined(WINCE)
#else
#include <sys/stat.h>
#endif

#ifdef WIN32
#include <qt_windows.h>
#endif

#ifdef linux
#include <unistd.h>
#endif

#include <QThread>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>

#ifdef SDL_SUPPORT_LIB
#include "main.h"
#endif
#include "Config/Config.h"
#include "Common/AppBase.h"
#include "Show/MediaShow.h"
#include "Show/GraphicSoftButtonShow.h"
#include "utils/VideoStream/CeVideoStream.h"
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/Data/SDLAppsData.h"
#include "SDLApps/app/SDLApps.h"

typedef AppListInterface *(*InitFunc)(UIInterface *);
typedef void  (*CloseFunc)();
extern UIManager *g_pUIManager;

std::string GetSDKLibPath() {
    const int iBuffLen = 512;
    char aPathBuff[iBuffLen];
    std::string strResult("");
#if defined(WIN32) || defined(WINCE)
    WCHAR wPathBuff[iBuffLen];
    int iRet = GetModuleFileName(NULL, wPathBuff, iBuffLen);
    int len = WideCharToMultiByte(CP_ACP, 0, wPathBuff, wcslen(wPathBuff), aPathBuff, iBuffLen, NULL, NULL);
    strResult = aPathBuff;
    int pos = strResult.find_last_of('\\', strResult.size() - 1);
    strResult.erase(pos, strResult.size() - 1);
    strResult += "\\";
#elif defined(__ANDROID__)
    getcwd(aPathBuff, iBuffLen);
    strResult = aPathBuff;
    strResult += "/../lib/";
#elif defined(linux)
    getcwd(aPathBuff, iBuffLen);
    strResult = aPathBuff;
    strResult += "/";
#endif
    return strResult;
}

UIManager::UIManager(QWidget *parent)
    : QWidget(parent)
    , m_bShowPopUpAudioPassThru(false)
{

}

void UIManager::SetAppListInterface(AppListInterface *pList) {
    m_pList = pList;

    //update app list
    std::vector<int> vAppIDs;
    std::vector<std::string> vAppNames;
    std::vector<std::string> vIconPath;
    std::vector<std::string> vAppTypes;
    m_pList->getAppList(vAppIDs, vAppNames, vIconPath, vAppTypes);
    SDLAppsData::GetInstance()->UpdateAppList(vAppIDs, vAppNames, vIconPath, vAppTypes);
    emit appListUpdateSignal();
}

bool UIManager::FindTemplate(std::string name) {
    return m_TplManager.Find(name);
}

//UIManager::UIManager(AppListInterface *pList, QWidget *parent) :
//    QWidget(parent) {
//    m_pList = pList;
//}

UIManager::~UIManager() {
    std::string strFilePath = GetSDKLibPath();
    strFilePath += "hmi_sdk";
    m_sdk.setFileName(strFilePath.c_str());

    // 释放HMISDK，动态调用UnInitHmiSdk函数
    CloseFunc unInit = (CloseFunc)m_sdk.resolve("UnInitHmiSdk");
    if (unInit) {
        unInit();
    } else {
        LOGE("can't load hmi sdk lib, %s", strFilePath.data());
    }
}

void UIManager::initAppHMI() {
#ifdef ANDROID
    UIConfig::loadResolution(QApplication::desktop()->width(), QApplication::desktop()->height() - 30);
#else
    UIConfig::loadResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

    m_TplManager.CreateDefault(m_pList);
    if (m_TplManager.Create("LARGE_GRAPHIC_WITH_SOFTBUTTONS", "this is large graphic template")) {
        TemplateImp &tpl = m_TplManager.Get("LARGE_GRAPHIC_WITH_SOFTBUTTONS");
        SDLAppsView *pMain = (SDLAppsView *)tpl.GetScene(ID_MAIN);
        QWidget *pParent = pMain->CenterWidget();

        tpl.SetScene(ID_SHOW, new CGraphicSoftButtonShow(m_pList, pParent));
    }

    m_iCurUI = ID_MAIN;
    m_sCurTpln = DEFAULT_TEMPLATE;

    connect(this, SIGNAL(onAppShowSignal(int)), this, SLOT(AppShowSlot(int)));
    connect(this, SIGNAL(OnAppUnregisterSignal(int)), this, SLOT(OnAppUnregisterSlot(int)));
    connect(this, SIGNAL(onVideoStartSignal()), this, SLOT(onVideoStartSlots()));
    connect(this, SIGNAL(onVideoStopSignal()), this, SLOT(onVideoStopSlots()));
    connect(this, SIGNAL(onAudioPassThruSignal()), this, SLOT(onAudioPassThruSlot()));
}

void UIManager::OnAppActivated(int appID)
{
    m_pList->OnAppActivated(appID);
}

//void UIManager::StopVideoStream()
//{
////    AppControl->OnCommandClick(-1);
//    m_pList->OnAppExit();
//}

void UIManager::ExitApp()
{
    m_pList->OnAppExit();
}

int UIManager::GetCurViewId()
{
    return m_iCurUI;
}

void UIManager::AudioPassThruFinish()
{
    INFO("UIManager::AudioPassThruFinish");
    m_bShowPopUpAudioPassThru = false;
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    AppControl->OnPerformAudioPassThru(0);
}

void UIManager::AudioPassThruCancel()
{
    INFO("UIManager::AudioPassThruCancel");
    m_bShowPopUpAudioPassThru = false;
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    AppControl->OnPerformAudioPassThru(5);
}

void UIManager::AudioPassThruTimeOut()
{
    INFO("UIManager::AudioPassThruTimeOut");
    m_bShowPopUpAudioPassThru = false;
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    AppControl->OnPerformAudioPassThru(5);
}

void UIManager::onAppActive() {

}

void UIManager::onAppStop() {

}

//show app
void UIManager::onAppShow(int type) {
    if ((type >= 0) && (type < ID_UI_MAX))
        emit onAppShowSignal(type);
}

void UIManager::onAppRegister(int appId)
{
    INFO("UIManager::onAppRegister");

    //update app list
    std::vector<int> vAppIDs;
    std::vector<std::string> vAppNames;
    std::vector<std::string> vIconPath;
    std::vector<std::string> vAppTypes;
    m_pList->getAppList(vAppIDs, vAppNames, vIconPath, vAppTypes);
    SDLAppsData::GetInstance()->UpdateAppList(vAppIDs, vAppNames, vIconPath, vAppTypes);
    emit appListUpdateSignal();
}

void UIManager::onAppUnregister(int appId) {
    INFO("UIManager::onAppUnregister appId:%d", appId);
    emit onVideoStopSignal();
    emit OnAppUnregisterSignal(appId);
}

void UIManager::OnAppUnregisterSlot(int appId) {
    //for navi
    if(SDLApps::Inst()->FromNavi())
    {
        SDLApps::Inst()->SetFromNavi(false);
        HMIFrameWork::Inst()->AppShow(NAV_ID);
    }

    if(SDLApps::Inst()->FromMedia())
    {
        SDLApps::Inst()->SetFromMedia(false);
        HMIFrameWork::Inst()->AppShow(MEDIA_ID);
    }
    AppDataInterface *pData = AppControl;
    if (pData && appId == pData->getAppID()) {
        // App异常退出提示框
        QMessageBox::about(this, "通知", QString(pData->getAppName().c_str()) + "App异常断开!");
    }

    HidePopupAudioPassThru();

    m_pList->appUnregistered(appId);

    //update app list
    INFO("UIManager::OnAppUnregisterSlot appId:%d", appId);
    std::vector<int> vAppIDs;
    std::vector<std::string> vAppNames;
    std::vector<std::string> vIconPath;
    std::vector<std::string> vAppTypes;
    m_pList->getAppList(vAppIDs, vAppNames, vIconPath, vAppTypes);
    SDLAppsData::GetInstance()->UpdateAppList(vAppIDs, vAppNames, vIconPath, vAppTypes);
    emit appListUpdateSignal();
}

void UIManager::onVideoStreamStart() {
    emit onVideoStartSignal();
}

void UIManager::onVideoStreamStop() {
    emit onVideoStopSignal();
}

void UIManager::onVideoStartSlots() {
#ifdef OS_LINUX
    SDLAppsView *pMain = (SDLAppsView *)m_TplManager.Get(DEFAULT_TEMPLATE).GetScene(ID_MAIN);
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    std::string tplname = pData->GetActiveTemplate();
    CeVideoStream *pVideoStream = (CeVideoStream *)m_TplManager.Get(tplname).GetScene(ID_VIDEOSTREAM);
    if (pMain) {
        pMain->HideAllComponent();
    }
    if (pVideoStream) {
        pVideoStream->startStream();
    }

    std::cout << "++++++++++++++++++id "<<AppControl->getAppID() <<"  " << AppControl->getAppName()<<"  "<<AppControl->getCurUI()<<std::endl;
#endif
}

void UIManager::onVideoStopSlots() {
#ifdef OS_LINUX
    SDLAppsView *pMain = (SDLAppsView *)m_TplManager.Get(DEFAULT_TEMPLATE).GetScene(ID_MAIN);
    AppDataInterface *pData = AppControl;
    if (!pData) return;
    std::string tplname = pData->GetActiveTemplate();
    CeVideoStream *pVideoStream = (CeVideoStream *)m_TplManager.Get(tplname).GetScene(ID_VIDEOSTREAM);
    if (pMain) {
        pMain->ShowAllComponent();
    }
    if (pVideoStream) {
        pVideoStream->stopStream();
    }

    //for navi
    if(SDLApps::Inst()->FromNavi())
    {
        HMIFrameWork::Inst()->AppShow(NAV_ID);
    }
#endif
}

void UIManager::AppShowSlot(int type) {
    INFO("type 1= %d", type);
    TemplateImp &curTpl = m_TplManager.Get(m_sCurTpln);
    // 画面是MAIN或APPLINK时，使用全局的默认模板画面
    if (ID_MAIN == type || ID_APPLINK == type || ID_DEVICEVIEW == type) {
        TemplateImp &tpl = m_TplManager.Get(DEFAULT_TEMPLATE);
        if (m_iCurUI != ID_MAIN) {
            curTpl.GetScene(m_iCurUI)->hide();
        }
        m_iCurUI = type;
        m_sCurTpln = DEFAULT_TEMPLATE;
        tpl.GetScene(m_iCurUI)->show();
        return;
    }
    INFO("type 2= %d", type);
    // 获取当前App使用的模板
    AppDataInterface *pData = AppControl;
    if (!pData)
        return;
    INFO("type 3= %d", type);
    std::string tplname = pData->GetActiveTemplate();
    TemplateImp &tpl = m_TplManager.Get(tplname);

    if (tpl.GetScene(m_iCurUI) == NULL)
        return;
    INFO("type 4= %d", type);
    if (type == ID_VIDEOSTREAM) {
        emit onVideoStartSignal();
    }
    INFO("type 5= %d", type);

    if(type == ID_AUDIOPASSTHRU)
    {
        emit onAudioPassThruSignal();
//        return;
    }

    // 特殊处理MEDIA模板Show画面的mediaclock请求
    if ("MEDIA" == tplname && ID_MEDIACLOCK == type) {
        CMediaShow *pShow = (CMediaShow *)tpl.GetScene(ID_SHOW);
        pShow->UpdateMediaClockTimer();
    } else {
        if (m_iCurUI != ID_MAIN) {
            curTpl.GetScene(m_iCurUI)->hide();
        }
        m_iCurUI = type;
        m_sCurTpln = tplname;
        INFO("type = %d", type);
        tpl.GetScene(m_iCurUI)->show();


        //if selected from navi module
        if(SDLApps::Inst()->FromNavi() && SDLApps::Inst()->getState() != AppStatus_Active)
        {
            HMIFrameWork::Inst()->AppShow(SDLAPPS_ID, "Navi");
        }
        //if selected from media module
        if(SDLApps::Inst()->FromMedia() && SDLApps::Inst()->getState() != AppStatus_Active)
        {
            HMIFrameWork::Inst()->AppShow(SDLAPPS_ID,"Media");
        }
    }
}

//void UIManager::waitMSec(int ms) {
//    Q_UNUSED(ms);
//}

void UIManager::tsSpeak(int VRID, std::string strText) {
    Q_UNUSED(VRID);
    Q_UNUSED(strText);
}

void UIManager::OnEndAudioPassThru() {
    INFO("UIManager::OnEndAudioPassThru");
    this->HidePopupAudioPassThru();

    AppDataInterface *pData = AppControl;
    if (!pData) return;
    AppControl->OnPerformAudioPassThru(0);
}

void UIManager::ShowDeviceList() {
    if (m_iCurUI == ID_DEVICEVIEW) {
        TemplateImp &tpl = m_TplManager.Get(DEFAULT_TEMPLATE);

        m_iCurUI = ID_DEVICEVIEW;
        m_sCurTpln = DEFAULT_TEMPLATE;
        tpl.GetScene(ID_DEVICEVIEW)->show();
    }
}

void UIManager::SetSDLStatus(bool bConnect) {
    // 使用默认模板的MAIN画面
    TemplateImp &tpl = m_TplManager.Get(DEFAULT_TEMPLATE);

    if (tpl.GetScene(ID_MAIN)) {
        SDLAppsView *pMain = (SDLAppsView *)tpl.GetScene(ID_MAIN);
        pMain->SetSDLStatus(bConnect);
    }
}

void UIManager::loadsdk() {
    std::string strFilePath = GetSDKLibPath();
    strFilePath += "hmi_sdk";
    m_sdk.setFileName(strFilePath.c_str());

    // 初始化HMISDK，动态调用InitHmiSdk函数
    InitFunc Init = (InitFunc)m_sdk.resolve("InitHmiSdk");
    if (Init) {
        /*AppListInterface *pApp = */Init(this);
    } else {
        ERROR("[SDL][Error]can't load hmi sdk lib, %s", strFilePath.data());
    }
    // 通知初始化完成
    emit finishLoadSDK();
}

void UIManager::onAudioPassThruSlot()
{
    INFO("[Enter]onAudioPassThruSlot");

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
    INFO("[Leave]onAudioPassThruSlot");
}

SDLAppsView *UIManager::getSDLAppsView()
{
    SDLAppsView *pMain = (SDLAppsView *)m_TplManager.Get(DEFAULT_TEMPLATE).GetScene(ID_MAIN);
    return pMain;
}

void UIManager::ShowPopupAudioPassThru(const string &appName, const string &duration, const string &contextA)
{
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

void UIManager::HidePopupAudioPassThru()
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
