#include "Gen3UIManager.h"
#ifdef ANDROID
#include "android/log.h"
#include <unistd.h>
#endif
#if defined(WINCE)
#else
#include<sys/stat.h>
#endif

#include <QThread>
#include <QCoreApplication>
#include <QDir>

#ifdef SDL_SUPPORT_LIB
#include "main.h"
#endif
#include "Config/Config.h"
#include "Common/AppBase.h"
#include "Show/MediaShow.h"
#include "MainWindow/MainWindow.h"
#include "Show/GraphicSoftButtonShow.h"
#include "VideoStream/CeVideoStream.h"

#ifdef WIN32
#include <Windows.h>
#endif

#ifdef linux
#include <unistd.h>
#endif

typedef AppListInterface *(*InitFunc)(UIInterface *);
typedef void  (*CloseFunc)();
extern CGen3UIManager *g_pUIManager;

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

CGen3UIManager::CGen3UIManager(QWidget *parent) :
  QWidget(parent) {

}

void CGen3UIManager::SetAppListInterface(AppListInterface *pList) {
  m_pList = pList;
}

bool CGen3UIManager::FindTemplate(std::string name) {
    return m_TplManager.Find(name);
}

CGen3UIManager::CGen3UIManager(AppListInterface *pList, QWidget *parent) :
  QWidget(parent) {
  m_pList = pList;
}

CGen3UIManager::~CGen3UIManager() {
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

void CGen3UIManager::initAppHMI() {
#ifdef ANDROID
  UIConfig::loadResolution(QApplication::desktop()->width(), QApplication::desktop()->height() - 30);
#else
  UIConfig::loadResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

  m_TplManager.CreateDefault(m_pList);
  if(m_TplManager.Create("LARGE_GRAPHIC_WITH_SOFTBUTTONS", "this is large graphic template")){
      TemplateImp& tpl = m_TplManager.Get("LARGE_GRAPHIC_WITH_SOFTBUTTONS");
      MainWindow* pMain = (MainWindow*)tpl.GetScene(ID_MAIN);
      QWidget* pParent = pMain->CenterWidget();

      tpl.SetScene(ID_SHOW, new CGraphicSoftButtonShow(m_pList, pParent));
  }

  m_iCurUI = ID_MAIN;
  m_sCurTpln = DEFAULT_TEMPLATE;

  connect(this, SIGNAL(onAppShowSignal(int)), this, SLOT(AppShowSlot(int)));
  connect(this, SIGNAL(OnAppUnregisterSignal(int)), this, SLOT(OnAppUnregisterSlot(int)));
  connect(this, SIGNAL(onVideoStartSignal()), this,SLOT(onVideoStartSlots()));
  connect(this, SIGNAL(onVideoStopSignal()), this,SLOT(onVideoStopSlots()));
}

void CGen3UIManager::onAppActive() {

}

void CGen3UIManager::onAppStop() {

}

//show app
void CGen3UIManager::onAppShow(int type) {
  if ((type >= 0) && (type < ID_UI_MAX))
    emit onAppShowSignal(type);
}

void CGen3UIManager::onAppUnregister(int appId) {
  emit OnAppUnregisterSignal(appId);
}

void CGen3UIManager::OnAppUnregisterSlot(int appId) {
  m_pList->appUnregistered(appId);
}

void CGen3UIManager::onVideoStreamStart() {
  emit onVideoStartSignal();
}

void CGen3UIManager::onVideoStreamStop() {
  emit onVideoStopSignal();
}

void CGen3UIManager::onVideoStartSlots() {
    MainWindow* pMain = (MainWindow*)m_TplManager.Get(DEFAULT_TEMPLATE).GetScene(ID_MAIN);
    AppDataInterface *pData = m_pList->getActiveApp();
    if (!pData) return;
    std::string tplname = pData->GetActiveTemplate();
    CeVideoStream* pVideoStream = (CeVideoStream *)m_TplManager.Get(tplname).GetScene(ID_VIDEOSTREAM);
    if (pMain) {
        pMain->HideAllComponent();
    }
    if (pVideoStream) {
        pVideoStream->startStream();
    }
}

void CGen3UIManager::onVideoStopSlots() {
    MainWindow* pMain = (MainWindow*)m_TplManager.Get(DEFAULT_TEMPLATE).GetScene(ID_MAIN);
    AppDataInterface *pData = m_pList->getActiveApp();
    if (!pData) return;
    std::string tplname = pData->GetActiveTemplate();
    CeVideoStream* pVideoStream = (CeVideoStream *)m_TplManager.Get(tplname).GetScene(ID_VIDEOSTREAM);
    if (pMain) {
        pMain->ShowAllComponent();
    }
    if (pVideoStream) {
        pVideoStream->stopStream();
    }
}

void CGen3UIManager::AppShowSlot(int type) {

  TemplateImp& curTpl = m_TplManager.Get(m_sCurTpln);

  // 画面是MAIN或APPLINK时，使用全局的默认模板画面
  if (ID_MAIN == type || ID_APPLINK == type || ID_DEVICEVIEW == type) {
    TemplateImp& tpl = m_TplManager.Get(DEFAULT_TEMPLATE);
   if (m_iCurUI != ID_MAIN) {
        curTpl.GetScene(m_iCurUI)->hide();
   }
    m_iCurUI = type;
    m_sCurTpln = DEFAULT_TEMPLATE;
    tpl.GetScene(m_iCurUI)->show();
    return;
  }

  // 获取当前App使用的模板
  AppDataInterface *pData = m_pList->getActiveApp();
  if (!pData)
    return;

  std::string tplname = pData->GetActiveTemplate();
  TemplateImp& tpl = m_TplManager.Get(tplname);

  if (tpl.GetScene(m_iCurUI) == NULL)
    return;

  // 特殊处理MEDIA模板Show画面的mediaclock请求
  if ("MEDIA" == tplname && ID_MEDIACLOCK == type) {
    if (ID_SHOW == m_iCurUI) {
      CMediaShow *pShow = (CMediaShow *)tpl.GetScene(ID_SHOW);
      pShow->UpdateMediaColckTimer();
    }
  } else {
    if (m_iCurUI != ID_MAIN) {
        curTpl.GetScene(m_iCurUI)->hide();
    }
    m_iCurUI = type;
    m_sCurTpln = tplname;
    tpl.GetScene(m_iCurUI)->show();
  }
}

void CGen3UIManager::waitMSec(int ms) {

}

void CGen3UIManager::tsSpeak(int VRID, std::string strText) {

}

void CGen3UIManager::OnEndAudioPassThru() {
}

void CGen3UIManager::ShowDeviceList() {
  if (m_iCurUI == ID_DEVICEVIEW) {
      TemplateImp& tpl = m_TplManager.Get(DEFAULT_TEMPLATE);

      m_iCurUI = ID_DEVICEVIEW;
      m_sCurTpln = DEFAULT_TEMPLATE;
      tpl.GetScene(ID_DEVICEVIEW)->show();
  }
}

void CGen3UIManager::SetSDLStatus(bool bConnect) {
  // 使用默认模板的MAIN画面
  TemplateImp& tpl = m_TplManager.Get(DEFAULT_TEMPLATE);

  if (tpl.GetScene(ID_MAIN)) {
    MainWindow *pMain = (MainWindow *)tpl.GetScene(ID_MAIN);
    pMain->SetSDLStatus(bConnect);
  }
}

void CGen3UIManager::loadsdk() {
  std::string strFilePath = GetSDKLibPath();
  strFilePath += "hmi_sdk";
  m_sdk.setFileName(strFilePath.c_str());

  // 初始化HMISDK，动态调用InitHmiSdk函数
  InitFunc Init = (InitFunc)m_sdk.resolve("InitHmiSdk");
  if (Init) {
    AppListInterface *pApp = Init(this);
  } else {
    LOGE("can't load hmi sdk lib, %s", strFilePath.data());
  }

  // 通知初始化完成
  emit finishLoadSDK();
}
