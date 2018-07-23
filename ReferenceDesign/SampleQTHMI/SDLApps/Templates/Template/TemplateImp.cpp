/**
* @file			TemplateImp.h
* @brief		模板类，管理该模板对应的 所有画面，模板为一Hash类型的容器，容器大小固定为一个模板所有画面的数目，关键词为画面ID，键值为个画面对象的指针，此处为指针目的是为了多模板共享同一个画面对象
* @author		fanqiang
* @date			2017-9-21
* @version		A001
* @copyright	ford
*/

#include "TemplateImp.h"
#include <QWidget>


std::set<QWidget *> TemplateImp::m_setAllScene;

TemplateImp::TemplateImp() {
  m_sName = DEFAULT_TEMPLATE;
  m_sProperty = DEFAULT_TEMPLATE_PROPERTY;

  for (int i = 0; i < ID_UI_MAX; ++i) {
    m_vScenes[i] = NULL;
  }
}

TemplateImp::TemplateImp(std::string name, std::string prop) {
  m_sName = name;
  m_sProperty = prop;

  for (int i = 0; i < ID_UI_MAX; ++i) {
    m_vScenes[i] = NULL;
  }
}

TemplateImp::~TemplateImp() {

}

void TemplateImp::SetScene(int id, QWidget *pScene) {
  if (id >= 0 && id < ID_UI_MAX && pScene) {
    pScene->hide();
    m_vScenes[id] = pScene;
    m_setAllScene.insert(pScene);
  }
}

QWidget *TemplateImp::GetScene(int id) {
  if (id >= 0 && id < ID_UI_MAX)
    return m_vScenes[id];

  return NULL;
}

std::string TemplateImp::GetTemplateName() {
  return m_sName;
}

std::string TemplateImp::GetProperty() {
  return m_sProperty;
}

void TemplateImp::DestroyAllScene() {
  std::set<QWidget *>::iterator it = m_setAllScene.begin();
  for (; it != m_setAllScene.end(); it++) {
    if (*it)
      delete *it;
  }
}
