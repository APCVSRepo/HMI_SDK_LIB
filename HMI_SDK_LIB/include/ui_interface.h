/**
* @file			UIInterface.h
* @brief		调用侧按照要求需要实现的接口，用于控制画面的显示部分
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef UIINTERFACE_H
#define UIINTERFACE_H
#include "app_list_interface.h"

namespace hmisdk {

class UIInterface {
 public:
  /**
   * 通知激活App
   * @return		无
   * @ref
   * @see
   * @note		App列表中点击App图标会触发该事件
   */
  virtual void onAppActive() = 0;

  /**
   * 通知停止App
   * @return		无
   * @ref
   * @see
   * @note		退出App时会触发该事件
   */
  virtual void onAppStop() = 0;

  /**
   * 通知显示指定画面
   * @param[in]	type		画面ID
   * @return		无
   * @ref
   * @see			app_common.h ShowType枚举值定义
   * @note		切换到指定画面实现类实例进行显示
   */
  virtual void onAppShow(int type) = 0;

  /**
   * 通知App注册
   * @param[in]	appId		app对应的id
   * @return		无
   * @ref
   * @see
   * @note		App注册时会触发该事件
   */
  virtual void onAppRegister(int appId) = 0;

  /**
   * 通知取消App注册
   * @param[in]	appId		app对应的id
   * @return		无
   * @ref
   * @see
   * @note		App取消注册时会触发该事件
   */
  virtual void onAppUnregister(int appId) = 0;

  /**
   * 通知开启视频流传输
   * @return		无
   * @ref
   * @see
   * @note		开启视频流传输时会触发该事件
   */
  virtual void onVideoStreamStart() = 0;

  /**
   * 通知停止视频流传输
   * @return		无
   * @ref
   * @see
   * @note		停止视频流传输时会触发该事件
   */
  virtual void onVideoStreamStop() = 0;

  /**
   * 通知停止语音录音
   * @return		无
   * @ref
   * @see
   * @note		停止语音录音时会触发该事件
   */
  virtual void OnEndAudioPassThru() = 0;

  /**
   * 通知tts语音播放
   * @param[in]	VRID		请求类型
   * @param[in]	strText		语音播放文本
   * @return		无
   * @ref
   * @see			app_common.h VRID枚举值定义
   * @note		实现TTS语音文本的转换并进行播放
   */
  virtual void tsSpeak(int VRID, std::string strText) = 0;

  /**
   * 通知刷新设备列表
   * @return		无
   * @ref
   * @see
   * @note		收到刷新设备列表通知时会触发该事件
   */
  virtual void ShowDeviceList() = 0;

  /**
   * 通知当前SDL的连接状态
   * @param[in]	bConnect		连接状态，是否连接
   * @return		无
   * @ref
   * @see
   * @note
   */
  virtual void SetSDLStatus(bool bConnect) = 0;

  /**
   * 设置AppListInterface接口
   * @param[in]	pList		AppListInterface接口
   * @return		无
   * @ref
   * @see
   * @note		该函数会在SDK初始化时调用进行设置，保证后续UIInterface对该接口使用有效
   */
  virtual void SetAppListInterface(AppListInterface *pList) = 0;

  /**
   * 初始化UI画面部分
   * @return		无
   * @ref
   * @see
   * @note		需要实现初始化HMI资源，UI部分各个画面实现类的创建及初始化，保证后续对画面的操作有效
   */
  virtual void initAppHMI() = 0;

  /**
  * 通过模板名查找模板，若找到返回true，否则返回false
  * @param[in]	name		模板名称
  * @return		true:查找成功, false:未找到
  * @ref
  * @see
  * @note
  */
  virtual bool FindTemplate(std::string name) = 0;

  /**
  * 获取当前模板ID
  * @param      无
  * @return		当前模板ID
  * @ref
  * @see
  * @note
  */
  virtual int GetCurViewId() = 0;
};

}

#endif // UIINTERFACE_H
