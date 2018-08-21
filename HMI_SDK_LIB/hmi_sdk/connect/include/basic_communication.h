/**
* @file			basic_communication
* @brief		App注册、设备App更新、状态变化等事件响应通道，处理SDL发送的BasicCommunication相关的RPC请求
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef BASE_COMMUNICATIONCLIENT_H_
#define BASE_COMMUNICATIONCLIENT_H_

#include "hmi_channel.h"

namespace hmisdk {

class BasicCommunication : public Channel {
 public:
  BasicCommunication();
  ~BasicCommunication();
 protected:
  void onRegistered();
  void onUnregistered();

 public:
  void onRequest(Json::Value &);
  void onNotification(Json::Value &);

 private:

};

}

#endif // BASE_COMMUNICATIONCLIENT_H_

