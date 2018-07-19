/**
* @file			TemplateImp.h
* @brief		模板类，管理该模板对应的 所有画面，模板为一Hash类型的容器，容器大小固定为一个模板所有画面的数目，关键词为画面ID，键值为个画面对象的指针，此处为指针目的是为了多模板共享同一个画面对象
* @author		fanqiang
* @date			2017-9-21
* @version		A001
* @copyright	ford
*/

#ifndef TEMPLATEIMP_H_
#define TEMPLATEIMP_H_

#include <string>
#include <map>
#include <set>
#include "app_common.h"

class QWidget;

class TemplateImp {
 private:
  /**
   * 所有模板画面的集合
   */
  static std::set<QWidget *> m_setAllScene;

  /**
   * 场景画面对应关系
   */
  QWidget *m_vScenes[ID_UI_MAX];

  /**
   * 模板名
   */
  std::string m_sName;

  /**
   * SetDisplayLayout返回的模板属性
   */
  std::string m_sProperty;


 public:
  TemplateImp();
  TemplateImp(std::string name, std::string prop);
  ~TemplateImp();

  /**
  * 设置当前模板的指定画面
  * @param[in]	id		画面ID
  * @param[in]	pScene		画面对象指针
  * @return		无
  * @ref
  * @see
  * @note		模板所有画面初始化会用默认模板画面填充，多次设置同一画面时，最后设置的自动覆盖前一次的，但是不负责销毁对象
  */
  void SetScene(int id, QWidget *pScene);

  /**
  * 获取当前模板的指定画面
  * @param[in]	id		画面ID
  * @return		画面对象指针
  * @ref
  * @see
  * @note
  */
  QWidget *GetScene(int id);

  /**
  * 获取当前模板的模板名称
  * @return		当前模板的模板名称
  * @ref
  * @see
  * @note
  */
  std::string GetTemplateName();

  /**
  * 收到SetDisplayLayout请求后返回的模板属性
  * @return		模板属性
  * @ref
  * @see
  * @note
  */
  std::string GetProperty();

  /**
  * 销毁所有模板画面
  * @return
  * @ref
  * @see
  * @note   在模板管理器析构时调用该函数销毁所有画面
  */
  static void DestroyAllScene();

};
#endif // TEMPLATEIMP_H_
