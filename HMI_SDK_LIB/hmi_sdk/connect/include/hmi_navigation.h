/**
* @file			hmi_navigation
* @brief		导航类应用视频传输、导航命令等响应通道，处理SDL发送的Navigation相关的RPC请求
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef NAVIGATIONCLIENT_H_
#define NAVIGATIONCLIENT_H_

#include "hmi_channel.h"

namespace hmisdk {

class Navigation : public Channel {
 public:
  Navigation();
  ~Navigation();
 protected:
  void onRequest(Json::Value &);

 private:

};

}

#endif // NAVIGATIONCLIENT_H_
