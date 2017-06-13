#include "Gen3UIManager.h"
//#include "AppData/AppList.h"
//#include <pthread.h>
#include <QThread>
#ifdef ANDROID
#include "android/log.h"
#include <unistd.h>
#endif

#include "Config/Config.h"
#if defined(WINCE)
#else
#include<sys/stat.h>
#endif
#include <QDir>
#ifdef SDL_SUPPORT_LIB
#include "main.h"
#endif

#include "Config/Config.h"

#include "VideoStream/CeVideoStream.h"

#include "MainWindow/MainWindow.h"
#include "AppListView/AppListView.h"
#include "CommandView/CommandView.h"
#include "Show/MediaShow.h"
#include "Alert/AlertView.h"
#include "ChoiceSet/ChoiceSet.h"
#include <QApplication>
#include <QDesktopWidget>
#include "ScrollableMessage/ScollMsgView.h"
#include "SliderView/SliderView.h"
#include "AppListView/DeviceListView.h"

#ifdef WIN32
#include <Windows.h>
#endif

#ifdef linux
#include <unistd.h>
#endif

typedef AppListInterface *(*InitFunc)(UIInterface *);
typedef void  (*CloseFunc)();
extern CGen3UIManager *g_pUIManager;

std::string GetSDKLibPath()
{
    const int iBuffLen = 512;
    char aPathBuff[iBuffLen];
    std::string strResult("");
#if defined(WIN32) || defined(WINCE)
    WCHAR wPathBuff[iBuffLen];
    int iRet = GetModuleFileName(NULL,wPathBuff,iBuffLen);
    int len = WideCharToMultiByte(CP_ACP,0,wPathBuff,wcslen(wPathBuff),aPathBuff,iBuffLen,NULL,NULL);
    strResult = aPathBuff;
    int pos = strResult.find_last_of('\\',strResult.size()-1);
    strResult.erase(pos,strResult.size()-1);
    strResult += "\\";
#elif defined(__ANDROID__)
    getcwd(aPathBuff,iBuffLen);
    strResult = aPathBuff;
    strResult += "/../lib/";
#elif defined(linux)
    getcwd(aPathBuff,iBuffLen);
    strResult = aPathBuff;
    strResult += "/";
#endif
    return strResult;
}

CGen3UIManager::CGen3UIManager(QWidget *parent) :
    QWidget(parent)
{
    for (int i = 0; i < ID_UI_MAX; ++i) {
        m_vUIWidgets[i] = NULL;
    }
}

void CGen3UIManager::SetAppListInterface(AppListInterface * pList)
{
    m_pList = pList;
}

CGen3UIManager::CGen3UIManager(AppListInterface * pList, QWidget *parent) :
    QWidget(parent)
{
    for (int i = 0; i < ID_UI_MAX; ++i) {
        m_vUIWidgets[i] = NULL;
    }
    m_pList = pList;
}

CGen3UIManager::~CGen3UIManager()
{
    for (int i = 0; i < ID_UI_MAX; ++i) {
        if (m_vUIWidgets[i]) {            
            delete m_vUIWidgets[i];
            m_vUIWidgets[i] = NULL;
        }
    }
}

void CGen3UIManager::initAppHMI()
{
#ifdef ANDROID
    UIConfig::loadResolution(QApplication::desktop()->width(),QApplication::desktop()->height()-30);
#else
    UIConfig::loadResolution(800,480);
#endif

    MainWindow * pMain = new MainWindow(m_pList);
    QWidget* pParent = pMain->CenterWidget();

    m_vUIWidgets[ID_APPLINK] = new CAppListView(m_pList, pParent);
    m_vUIWidgets[ID_CHOICESET] = new CChoiceSet(m_pList, pParent);
    m_vUIWidgets[ID_COMMAND]=new CCommandView(m_pList, pParent);
    m_vUIWidgets[ID_SHOW] = new CMediaShow(m_pList,pParent);
    m_vUIWidgets[ID_ALERT]=new AlertView(m_pList, pParent);
    m_vUIWidgets[ID_AUDIOPASSTHRU]=NULL;//new CAudioPassThru(m_pList, pParent);
    m_vUIWidgets[ID_CHOICESETVR]=NULL;//new CChoicesetVR(m_pList, pParent);
    m_vUIWidgets[ID_SCROLLMSG] = new CScollMsgView(m_pList, pParent);
    m_vUIWidgets[ID_SLIDER] = new CSliderView(m_pList, pParent);
    m_vUIWidgets[ID_NOTIFY]=NULL;//new Notify(pParent);
    m_vUIWidgets[ID_MEDIACLOCK] = NULL;
    m_vUIWidgets[ID_MAIN] = pMain;
    m_vUIWidgets[ID_DEVICEVIEW] = new CDeviceListView(m_pList, pParent);

    m_vUIWidgets[ID_VIDEOSTREAM] = new CeVideoStream(m_pList,pMain);

    for (int i = 0; i < ID_UI_MAX; ++i) {
        if (m_vUIWidgets[i] != NULL) {
            m_vUIWidgets[i]->hide();
        }
    }



    m_iCurUI = ID_MAIN;

    connect(this,SIGNAL(onAppShowSignal(int)),this,SLOT(AppShowSlot(int)));
    connect(this,SIGNAL(OnAppUnregisterSignal(int)),this,SLOT(OnAppUnregisterSlot(int)));
}

void CGen3UIManager::onAppActive()
{

}

void CGen3UIManager::onAppStop()
{

}

//show app
void CGen3UIManager::onAppShow(int type)
{
    if ((type >= 0) && (type < ID_UI_MAX))
        emit onAppShowSignal(type);
}

void CGen3UIManager::onAppUnregister(int appId)
{
    emit OnAppUnregisterSignal(appId);
}

void CGen3UIManager::OnAppUnregisterSlot(int appId)
{
    m_pList->appUnregistered(appId);
}

void CGen3UIManager::onVideoStreamStart(){

}

void CGen3UIManager::onVideoStreamStop(){

}

//void CGen3UIManager::onVideoStreamStart()
//{
//    fflush(stdout);
//    emit onVideoStartSignal();
//}

//void CGen3UIManager::onVideoStartSlots()
//{
//#ifndef WINCE

//#ifdef ANDROID
//    MediaCodecStream *pVideoStream = ((MediaCodecStream *)m_vUIWidgets[ID_VIDEOSTREAM]);
//    pVideoStream->startStream();
//    m_pList->IconnectToVS(pVideoStream, "127.0.0.1", 5050);
//#else
//    fflush(stdout);
//    std::string str_url = AppControl->getUrlString();
//    //_D("%s\n",str_url.data());

//    VideoStream *pVideoStream = ((VideoStream *)m_vUIWidgets[ID_VIDEOSTREAM]);//->StartVideoStream(str_url.c_str());
//    pVideoStream->setUrl(str_url.c_str());
//    pVideoStream->startStream();

//#endif

//#else
//    CeVideoStream *pVideoStream = ((CeVideoStream *)m_vUIWidgets[ID_VIDEOSTREAM]);
//    pVideoStream->startStream();
//#ifndef SDL_CALL_BACK
//    m_pList->IconnectToVS(pVideoStream, "127.0.0.1", 5050);
//#endif
//#endif

//}

//void CGen3UIManager::onVideoStreamStop()
//{
//#ifndef WINCE

//#ifdef ANDROID
//    m_pList->IdelConnectToVS();
//    ((MediaCodecStream *)m_vUIWidgets[ID_VIDEOSTREAM])->stopStream();
//#else
//    emit onVideoStopSignal();
//    ((VideoStream *)m_vUIWidgets[ID_VIDEOSTREAM])->stopStream();
//#endif
//#else
//#ifndef SDL_CALL_BACK
//    m_pList->IdelConnectToVS();
//#endif
//    ((CeVideoStream *)m_vUIWidgets[ID_VIDEOSTREAM])->stopStream();
//#endif
//}

//void CGen3UIManager::onVideoStopSlots()
//{
//}

void CGen3UIManager::AppShowSlot(int type)
{    
    if (m_vUIWidgets[m_iCurUI] == NULL) {
        return;
    }

    if (ID_MEDIACLOCK == type) {
        if (ID_SHOW == m_iCurUI)
        {
            CMediaShow *pShow = (CMediaShow *)m_vUIWidgets[ID_SHOW];
            pShow->UpdateMediaColckTimer();
        }
    }
    else {
        if (m_iCurUI != ID_MAIN) {

/*            if (m_iCurUI == ID_VIDEOSTREAM) {
#ifdef ANDROID
                ((MediaCodecStream *)m_vUIWidgets[m_iCurUI])->hideActivity();
#else
                m_vUIWidgets[m_iCurUI]->hide();
#endif
            } else */{
                m_vUIWidgets[m_iCurUI]->hide();
            }
        }
        //m_vUIWidgets[m_iCurUI]->hide();
        m_iCurUI = type;

/*        if (m_iCurUI == ID_VIDEOSTREAM) {
#ifdef ANDROID
            ((MediaCodecStream *)m_vUIWidgets[m_iCurUI])->showActivity();
#else
            m_vUIWidgets[m_iCurUI]->show();
#endif
        } else */{
            m_vUIWidgets[m_iCurUI]->show();
        }
    }
}

#include <QCoreApplication>
void CGen3UIManager::waitMSec(int ms)
{
    /*
    QTime t;
    t.start();
    while(t.elapsed()<ms)
        QCoreApplication::processEvents();
        */
}

void CGen3UIManager::tsSpeak(int VRID, std::string strText)
{
    /*
    bool ret = ts.speak(strText.c_str());


    switch(VRID) {
    case ID_DEFAULT:
        if(ret)
            AppControl->OnTTSSpeek(0);
        else
            AppControl->OnTTSSpeek(5);
        break;
    case ID_CANCEL:
        AppControl->OnPerformAudioPassThru(PERFORMAUDIOPASSTHRU_CANCEL);
        break;
    case ID_HELP:
        AppControl->OnPerformAudioPassThru(PERFORMAUDIOPASSTHRU_DONE);
        break;
    case ID_EXIT:
        AppControl->OnPerformAudioPassThru(PERFORMAUDIOPASSTHRU_DONE);
        m_pList->OnAppExit();
        break;
    case ID_SWITCHAPP:
        AppControl->OnPerformAudioPassThru(PERFORMAUDIOPASSTHRU_DONE);
        break;
    default:
        AppControl->OnPerformAudioPassThru(PERFORMAUDIOPASSTHRU_CANCEL);
        break;
    }
    */
}

void CGen3UIManager::OnEndAudioPassThru()
{
    //((CAudioPassThru *)m_vUIWidgets[ID_AUDIOPASSTHRU])->onButtonClickedSlots(PERFORMAUDIOPASSTHRU_CANCEL);
}

void CGen3UIManager::ShowDeviceList()
{
    if(m_iCurUI == ID_DEVICEVIEW)
    {
        if(m_vUIWidgets[m_iCurUI])
            m_vUIWidgets[m_iCurUI]->show();
    }
}

void CGen3UIManager::SetSDLStatus(bool bConnect)
{
    if(m_vUIWidgets[ID_MAIN]){
        MainWindow * pMain = (MainWindow *)m_vUIWidgets[ID_MAIN];
        pMain->SetSDLStatus(bConnect);
    }
}

void CGen3UIManager::loadsdk()
{
    std::string strFilePath = GetSDKLibPath();
    strFilePath += "hmi_sdk";
    m_sdk.setFileName(strFilePath.c_str());

    InitFunc Init = (InitFunc)m_sdk.resolve("HMISDK_Init");
    if (Init) {
        AppListInterface * pApp = Init(this);
    } else {
        LOGE("can't load hmi sdk lib, %s", strFilePath.data());
    }

    emit finishLoadSDK();
}
