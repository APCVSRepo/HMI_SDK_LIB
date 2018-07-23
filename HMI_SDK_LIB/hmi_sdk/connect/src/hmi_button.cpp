/**
* @file			hmi_button
* @brief		画面按钮事件响应通道，处理SDL发送的Buttons相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#include "hmi_button.h"
#include <iostream>
#include <string>
#include "json/json.h"
#include "global_first.h"

Buttons::Buttons() : Channel(200, "Buttons") {

}

Buttons::~Buttons() {

}

void Buttons::onRequest(Json::Value &request) {
  std::string method = request["method"].asString();
  int  id = request["id"].asInt();
  if (method == "Buttons.GetCapabilities") {
    sendResult(id, "GetCapabilities");
  } else if (method == "Buttons.IsReady") {
    sendResult(id, "IsReady");
  } else {
    Channel::onRequest(request);
  }
}

