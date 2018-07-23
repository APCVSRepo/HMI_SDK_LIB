/**
* @file			hmi_vr
* @brief		VR语音识别通道，处理SDL发送的VR相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef VRCLIENT_H_
#define VRCLIENT_H_

#include "hmi_channel.h"

class VR : public Channel {
 public:
  VR();
  ~VR();
 protected:
  void onRegistered();
  void onUnregistered();
  void onRequest(Json::Value &);

 private:

};

#endif // VRCLIENT_H_
