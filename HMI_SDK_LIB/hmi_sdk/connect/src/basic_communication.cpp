/**
* @file			basic_communication
* @brief		App注册、设备App更新、状态变化等事件响应通道，处理SDL发送的BasicCommunication相关的RPC请求
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#include "basic_communication.h"
#include <iostream>
#include <string>
#include <json/json.h>
#include "global_first.h"

BasicCommunication::BasicCommunication() : Channel(500, "BasicCommunication") {
}

BasicCommunication::~BasicCommunication() {

}

void BasicCommunication::onRegistered() {
  SubscribeToNotification("BasicCommunication.OnPutFile");
  SubscribeToNotification("SDL.OnSystemError");
  SubscribeToNotification("SDL.OnStatusUpdate");
  SubscribeToNotification("SDL.OnAppPermissionChanged");
  SubscribeToNotification("BasicCommunication.OnFileRemoved");
  SubscribeToNotification("BasicCommunication.OnAppRegistered");
  SubscribeToNotification("BasicCommunication.OnAppUnregistered");
  SubscribeToNotification("BasicCommunication.PlayTone");
  SubscribeToNotification("BasicCommunication.OnSDLClose");
  SubscribeToNotification("SDL.OnSDLConsentNeeded");
  SubscribeToNotification("BasicCommunication.OnResumeAudioSource");
  sendNotification("BasicCommunication.OnReady");
}

void BasicCommunication::onUnregistered() {
  UnsubscribeFromNotification("BasicCommunication.OnAppRegistered");
  UnsubscribeFromNotification("BasicCommunication.OnAppUnregistered");
  UnsubscribeFromNotification("BasicCommunication.PlayTone");
  UnsubscribeFromNotification("BasicCommunication.SDLLog");
}

void BasicCommunication::onRequest(Json::Value &request) {
  std::string method = request["method"].asString();
  int id = request["id"].asInt();
  if (method == "BasicCommunication.MixingAudioSupported") {
    sendResult(id, "MixingAudioSupported");
  } else if (method == "BasicCommunication.AllowAllApps") {
    sendResult(id, "AllowAllApps");
  } else if (method == "BasicCommunication.AllowApp") {
    sendResult(id, "AllowApp");
  } else if (method == "BasicCommunication.AllowDeviceToConnect") {
    sendResult(id, "AllowDeviceToConnect");
  } else if (method == "BasicCommunication.UpdateAppList") {
    Result result = m_pCallback->onRequest(request);
    sendResult(id, "UpdateAppList");
  } else if (method == "BasicCommunication.UpdateDeviceList") {
    // add by fanqiang
    Result result = m_pCallback->onRequest(request);
    sendResult(id, "UpdateDeviceList", result);
  } else if (method == "BasicCommunication.ActivateApp") {
    Result result = m_pCallback->onRequest(request);
    // 不需要回复
    //sendResult(id, "ActivateApp");
  } else if (method == "BasicCommunication.IsReady") {
    sendResult(id, "IsReady");
  } else if (method == "BasicCommunication.GetSystemInfo") {
    sendResult(id, "GetSystemInfo");
  } else {
    Channel::onRequest(request);
  }
}

void BasicCommunication::onNotification(Json::Value &jsonObj) {
  std::string method = jsonObj["method"].asString();
  if (method == "BasicCommunication.SDLLog") {
//        int app_id=jsonObj["app_id"].asInt();
//        int correlation_id=jsonObj["correlation_id"].asInt();
//        std::string function=jsonObj["function"].asString();
//        Json::Value data=jsonObj["data"];
  } else {
    Channel::onNotification(jsonObj);
  }
}

