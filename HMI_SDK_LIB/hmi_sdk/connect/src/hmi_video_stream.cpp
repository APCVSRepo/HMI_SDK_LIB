/**
* @file			hmi_video_stream
* @brief		VideoStream通道，处理SDL发送的VideoStream相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#include "hmi_video_stream.h"

namespace hmisdk {

CVideoStream::CVideoStream() : Channel(900, "VideoStream") {

}

CVideoStream::~CVideoStream() {

}

void CVideoStream::onRegistered() {

}

void CVideoStream::onUnregistered() {

}

void CVideoStream::onReceiveData(void *pData, int iLength) {
  m_pCallback->onRawData(pData, iLength);
}

void CVideoStream::onRequest(Json::Value &request) {

}

void CVideoStream::onNotification(Json::Value &jsonObj) {

}

}
