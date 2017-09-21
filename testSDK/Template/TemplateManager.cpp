/**
* @file			TemplateManager.cpp
* @brief		模板管理器类，各种模板保存的容器，并提供模板的增删找等操作
* @author		fanqiang
* @date			2017-9-21
* @version		A001
* @copyright	ford
*/


#include "TemplateManager.h"
#include "../Config/Config.h"
#include "../VideoStream/CeVideoStream.h"
#include "../MainWindow/MainWindow.h"
#include "../AppListView/AppListView.h"
#include "../CommandView/CommandView.h"
#include "../Show/MediaShow.h"
#include "../Alert/AlertView.h"
#include "../ChoiceSet/ChoiceSet.h"
#include "../ScrollableMessage/ScollMsgView.h"
#include "../SliderView/SliderView.h"
#include "../AppListView/DeviceListView.h"
#include "TemplateImp.h"

TemplateManager::TemplateManager() {
  m_mapTemplates.clear();
}

TemplateManager::~TemplateManager() {
  TemplateImp::DestroyAllScene();
  m_mapTemplates.clear();
}

void TemplateManager::CreateDefault(AppListInterface *pList) {
  // 默认模板为
  TemplateImp tpl(DEFAULT_TEMPLATE, DEFAULT_TEMPLATE_PROPERTY);

  MainWindow *pMain = new MainWindow(pList);
  QWidget *pParent = pMain->CenterWidget();

  tpl.SetScene(ID_APPLINK, new CAppListView(pList, pParent));
  tpl.SetScene(ID_CHOICESET, new CChoiceSet(pList, pParent));
  tpl.SetScene(ID_COMMAND, new CCommandView(pList, pParent));
  tpl.SetScene(ID_SHOW, new CMediaShow(pList, pParent));
  tpl.SetScene(ID_ALERT, new AlertView(pList, pParent));
  tpl.SetScene(ID_AUDIOPASSTHRU, NULL);//new CAudioPassThru(pList, pParent);
  tpl.SetScene(ID_CHOICESETVR, NULL);//new CChoicesetVR(pList, pParent);
  tpl.SetScene(ID_SCROLLMSG, new CScollMsgView(pList, pParent));
  tpl.SetScene(ID_SLIDER, new CSliderView(pList, pParent));
  tpl.SetScene(ID_NOTIFY, NULL);//new Notify(pParent);
  tpl.SetScene(ID_MEDIACLOCK, NULL);
  tpl.SetScene(ID_MAIN, pMain);
  tpl.SetScene(ID_DEVICEVIEW, new CDeviceListView(pList, pParent));
  tpl.SetScene(ID_VIDEOSTREAM, new CeVideoStream(pList, pMain));

  for (int i = 0; i < ID_UI_MAX; ++i) {
    if (tpl.GetScene(i) != NULL) {
      tpl.GetScene(i)->hide();
    }
  }
  m_mapTemplates[DEFAULT_TEMPLATE] = tpl;
}

bool TemplateManager::Create(std::string name, std::string prop) {
  if (name.empty() || prop.empty())
    return false;

  if (!Find(DEFAULT_TEMPLATE))
    return false;

  // 其他模板复制默认模板
  TemplateImp tpl(name, prop);
  TemplateImp defaulttpl = m_mapTemplates[DEFAULT_TEMPLATE];

  for (int i = 0; i < ID_UI_MAX; i++) {
    tpl.SetScene(i, defaulttpl.GetScene(i));
  }

  m_mapTemplates[name] = tpl;

  return true;
}

void TemplateManager::Remove(std::string name) {
  if (Find(name))
    m_mapTemplates.erase(name);
}

bool TemplateManager::Find(std::string name) {
  if (m_mapTemplates.find(name) != m_mapTemplates.end())
    return true;

  return false;
}

TemplateImp &TemplateManager::Get(std::string name) {

  return m_mapTemplates[name];
}
