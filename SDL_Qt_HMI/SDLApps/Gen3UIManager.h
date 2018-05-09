#ifndef CGEN3UIMANAGER_H
#define CGEN3UIMANAGER_H

#include <QLibrary>
#include <QWidget>
#include "ui_interface.h"
#include "app_list_interface.h"
#include "Template/TemplateManager.h"
#include "SDLApps/UI/SDLAppsView.h"

class CGen3UIManager : public QWidget, public UIInterface {
  Q_OBJECT
 public:
  explicit CGen3UIManager(QWidget *parent = NULL);
  explicit CGen3UIManager(AppListInterface *pList, QWidget *parent = NULL);
  ~CGen3UIManager();

  void SetAppListInterface(AppListInterface *pList);
  bool FindTemplate(std::string name);

  void onAppActive();
  void onAppStop();
  //hmi
  void onAppShow(int type);
  void onAppUnregister(int appId);

  void onVideoStreamStart();
  void onVideoStreamStop();

  void tsSpeak(int VRID, std::string strText);

  void OnEndAudioPassThru();

  // add by fanqiang
  void ShowDeviceList();
  void SetSDLStatus(bool bConnect);
  void initAppHMI();

 signals:
  void onAppShowSignal(int type);
  void onAppActivatedSignal(AppDataInterface *pInterface);
  void OnAppUnregisterSignal(int appId);

  void onVideoStartSignal();
  void onVideoStopSignal();
  void finishLoadSDK();
 public slots:
  void AppShowSlot(int type);
  void OnAppUnregisterSlot(int appId);

  void onVideoStartSlots();
  void onVideoStopSlots();
  void loadsdk();
 public:
  SDLAppsView *getSDLAppsView();
 private:
  int m_iCurUI;
  std::string m_sCurTpln;
  AppListInterface *m_pList;
  QLibrary m_sdk;
  TemplateManager m_TplManager;

  void waitMSec(int ms);
};

#endif // CUIMANAGER_H
