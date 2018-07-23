/**
* @file			hmi_video_stream
* @brief		VideoStream通道，处理SDL发送的VideoStream相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef CVIDEO_STREAM_H_
#define CVIDEO_STREAM_H_

#include "hmi_channel.h"

class CVideoStream : public Channel {
 public:
  CVideoStream();
  ~CVideoStream();
 protected:
  void onRegistered();
  void onUnregistered();
  void onReceiveData(void *pData, int iLength);

 public:
  void onRequest(Json::Value &);
  void onNotification(Json::Value &);

 private:
};

#endif // CVIDEO_STREAM_H_
