/**
* @file			app_data
* @brief		AppDataInterface接口实现类，手机端每一个App的数据都有一个该接口的实例进行保存，数据包含各个RPC请求在HMI端需要显示的属性数据，比如Show、Alert请求中的画面元素显示的内容等，在UI需要使用这些数据时，通过该接口中对应的方法取得
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef APPDATA_H_
#define APPDATA_H_

#include "sdl_connector.h"
#include "app_data_interface.h"
#include "ui_interface.h"

namespace hmisdk {

class AppData : public AppDataInterface {
 public:
  AppData();
  ~AppData();

  // 增加一个退出app的指令
  void addExitAppCommand();
  Json::Value &getShowData();
  Json::Value &getAlertJson();
  Json::Value &getSlider();
  Json::Value &getScrollableMsgJson();
  Json::Value &getAudioPassThruJson();
  Json::Value &getInteractionJson();
  Json::Value &getMediaClockJson();
  Json::Value &getDialNumberJson();
  std::vector<SMenuCommand> getCommandList();
  std::vector<SMenuCommand> getCommandList(int subMenuID);
  std::string getUrlString();
  std::string getAppName();
  std::string getAppIconFile();
  std::string getAppType();
  Result recvFromServer(Json::Value);
  int getCurUI();
  int getAppID();
  void setUIManager(UIInterface *pcallBack);

  // bInApp: just show the UI of the app, or could bjump to the applist.
  bool ShowPreviousUI(bool bInApp = true);
  void OnShowCommand();
  void OnSoftButtonClick(int sbID, int mode, std::string strName = "");
  void OnCommandClick(int cmdID);
  void OnAlertResponse(int reason);
  void OnScrollMessageResponse(int reason);
  void OnSliderResponse( int code, int sliderPosition);
  void OnTTSSpeek(int code);
  void OnPerformAudioPassThru(int code);
  void OnPerformInteraction(int code, int choiceID, bool bVR = false);
  void OnSetMediaClockTimerResponse(int iCode);
  void OnVideoScreenTouch(TOUCH_TYPE touch, int x, int y);
  void OnDialNumber(int code);
  void OnPhoneCall(bool isActive);
  std::string GetActiveTemplate();
  void SetActiveTemplate(std::string);

 private:
  UIInterface *m_pUIManager;
  std::vector<int> m_vecUIStack;
  Json::Value m_JsonShow;
  Json::Value *m_pShowData;
  std::vector <SMenuCommand > m_MenuCommands;

  Json::Value m_JsonAlert;
  Json::Value m_JsonSlider;
  Json::Value m_JsonScrollableMessage;
  Json::Value m_JsonAudioPassThru;
  Json::Value m_JsonInteraction;
  Json::Value m_JsonMediaClock;
  Json::Value m_JsonTtsSpeak;
  Json::Value m_JsonVideoStream;
  Json::Value m_JsonDialNumber;

  void addCommand(Json::Value jsonObj);
  void addSubMenu(Json::Value jsonObj);
  void delCommand(Json::Value jsonObj);
  void delSubMenu(Json::Value jsonObj);
  void alert(Json::Value jsonObj);
  void slider(Json::Value jsonObj);
  void scrollableMessage(Json::Value jsonObj);
  void performAudioPassThru(Json::Value jsonObj);
  void performInteraction(Json::Value jsonObj);
  void systemRequest(Json::Value jsonObj);
  void tsSpeak(Json::Value jsonObj);
  void videoStreamStart(Json::Value jsonObj);
  void videoStreamStop(Json::Value jsonObj);
  void showUI(int);
  void dialNumber(Json::Value jsonObj);

 public:
  std::string m_strAppIconFilePath;
  int m_iAppID;
  std::string m_szAppName;
  std::string m_szAppType;

  /**
   * App画面显示对应的模板堆栈，在每个画面显示时，会将对应的模板保存到堆栈，方便在画面返回时，进行模板的恢复
   */
  std::vector<std::string> m_vecTplStack;

  /**
   * 最后调用SetDisplayLayout设置的模板名
   */
  std::string m_sLastTpl;

};

}

#endif // APPDATA_H_
