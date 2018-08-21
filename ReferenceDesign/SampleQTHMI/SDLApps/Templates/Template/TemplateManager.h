/**
* @file			TemplateManager.h
* @brief		模板管理器类，各种模板保存的容器，并提供模板的增删找等操作
* @author		fanqiang
* @date			2017-9-21
* @version		A001
* @copyright	ford
*/

#ifndef TEMPLATEMANAGER_H_
#define TEMPLATEMANAGER_H_

#include <string>
#include <map>
#include "TemplateImp.h"
#include "app_list_interface.h"

using namespace hmisdk;

class TemplateManager {
 private:
  /**
   * 模板容器
   */
  std::map<std::string, TemplateImp> m_mapTemplates;


 public:
  TemplateManager();
  ~TemplateManager();

  /**
  * 创建默认模板
  * @param[in]	pList		app管理器接口
  * @return		无
  * @ref
  * @see
  * @note
  */
  void CreateDefault(AppListInterface *pList);

  /**
  * 新增模板
  * @param[in]	name		模板名
  * @param[in]	prop		模板属性
  * @return		模板是否建立成功
  * @ref
  * @see
  * @note		name、prop参数不能为空，重复建立同名会覆盖前面的模板
  */
  bool Create(std::string name, std::string prop);

  /**
  * 删除模板
  * @param[in]	name		模板名称
  * @return		无
  * @ref
  * @see
  * @note
  */
  void Remove(std::string name);

  /**
  * 通过模板名查找模板，若找到返回true，否则返回false
  * @param[in]	name		模板名称
  * @return		true:查找成功, false:未找到
  * @ref
  * @see
  * @note
  */
  bool Find(std::string name);

  /**
  * 通过模板名获取模板对象的引用
  * @param[in]	name		模板名称
  * @return		无
  * @ref
  * @see
  * @note
  */
  TemplateImp &Get(std::string name);

};

#endif // TEMPLATEMANAGER_H_
