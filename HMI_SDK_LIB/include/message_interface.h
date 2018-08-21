/**
* @file			message_interface
* @brief		定义网络状态及rpc交互通知回调的基本接口函数
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef IMESSAGEINTERFACE_H
#define IMESSAGEINTERFACE_H

#include "json/json.h"
#include <string>
#include "app_common.h"

namespace hmisdk {

class IMessageInterface {
 public:
  virtual Result onRequest(Json::Value) = 0;
  virtual void onNotification(Json::Value) = 0;
  virtual void onResult(Json::Value) = 0;
  virtual void onRawData(void *p, int iLength) = 0;
  virtual void onError(std::string error) = 0;
};

class INetworkStatus {
 public:
  virtual void onConnected() = 0;
  virtual void onNetworkBroken() = 0;
};

}

#endif // IMESSAGEINTERFACE_H
