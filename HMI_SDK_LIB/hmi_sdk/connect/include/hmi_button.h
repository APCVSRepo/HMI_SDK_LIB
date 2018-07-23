/**
* @file			hmi_button
* @brief		画面按钮事件响应通道，处理SDL发送的Buttons相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef BUTTONSCLIENT_H_
#define BUTTONSCLIENT_H_

#include "hmi_channel.h"

class Buttons : public Channel {
 public:
  Buttons();
  ~Buttons();
 public:
  void onRequest(Json::Value &);

 private:
};

#endif // BUTTONSCLIENT_H_
