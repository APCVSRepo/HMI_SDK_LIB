/**
* @file			hmi_navigation
* @brief		导航类应用视频传输、导航命令等响应通道，处理SDL发送的Navigation相关的RPC请求
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#include <hmi_navigation.h>
#include <iostream>
#include <string>
#include "json/json.h"

Navigation::Navigation() : Channel(800, "Navigation") {

}

Navigation::~Navigation() {

}

void Navigation::onRequest(Json::Value &request) {
  std::string method = request["method"].asString();
  int  id = request["id"].asInt();
  if (method == "Navigation.IsReady") {
    sendResult(id, "IsReady");
  } else if (method == "Navigation.ShowConstantTBT") {
    sendResult(id, "ShowConstantTBT");
  } else if (method == "Navigation.UpdateTurnList") {
    sendResult(id, "UpdateTurnList");
  } else if (method == "Navigation.AlertManeuver") {
    sendResult(id, "AlertManeuver");
  } else if (method == "Navigation.StartStream") {
    Result result = m_pCallback->onRequest(request);
    sendResult(id, "StartStream", result);
  } else if (method == "Navigation.StopStream") {
    Result result = m_pCallback->onRequest(request);
    sendResult(id, "StopStream", result);
  } else if (method == "Navigation.StartAudioStream") {
    Result result = m_pCallback->onRequest(request);
    sendResult(id, "StartAudioStream", result);
  } else if (method == "Navigation.StopAudioStream") {
    Result result = m_pCallback->onRequest(request);
    sendResult(id, "StopAudioStream", result);
  } else {
    Channel::onRequest(request);
  }
}
