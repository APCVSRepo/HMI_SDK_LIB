/**
* @file			hmi_channel
* @brief		hmi会将与sdl交互的数据分类，各种类型的数据通过不同的通道传递（UI、VR、TTS、Button等），该类为所有通过的基类
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#include<hmi_channel.h>
#ifndef WINCE
#include <sys/stat.h>
#endif
#ifdef OS_WIN32
#ifndef WINCE
#include <direct.h>
#endif
#else
#include <unistd.h>
#endif
#include<stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cassert>
#include <json/json.h>
#include "global_first.h"
#include "message_interface.h"

Json::Value g_StaticConfigJson;
Json::Value g_VehicleInfoJson;
Json::Value g_StaticResultJson;

JsonBuffer::JsonBuffer() {
  m_szBuffer = "";
}

bool JsonBuffer::getJsonFromBuffer(char *pData, int iLength, Json::Value &output) {
  if (pData != 0 && iLength > 0)
    m_szBuffer.append(pData, iLength);
  if (m_szBuffer.length() < 10)
    return false;

  int pos = m_szBuffer.find_first_of('\n');
  if (int(std::string::npos) == pos)
    return false;

  std::string szFirstJson = m_szBuffer.substr(0, pos + 1);
  if ((pos + 1) >= m_szBuffer.length())
    m_szBuffer = "";
  else
    m_szBuffer = m_szBuffer.substr(pos + 1);

  Json::Reader reader;
  if (reader.parse(szFirstJson, output)) {
    return true;
  }
  return false;
}

Channel::Channel(int startId, std::string Channelname)
  : m_pSocketManager(NULL) {
  m_bChannelStatus = false;
  m_iIDStart = -1;//register start
  m_iIDRegRequest = startId;//start
  m_iIDUnRegRequest = -1;
  m_sComponentName = Channelname;
  ReadConfigJson();
  m_StaticResult = g_StaticResultJson[m_sComponentName];
}

Channel::~Channel() {

}

void Channel::ReadConfigJson() {
  if (g_StaticConfigJson.isNull())
    g_StaticConfigJson = ReadSpecifyJson("staticConfigDB.json");
  if (g_StaticResultJson.isNull())
    g_StaticResultJson = ReadSpecifyJson("staticResult.json");
  if (g_VehicleInfoJson.isNull())
    g_VehicleInfoJson = ReadSpecifyJson("VehicleInfo.json");
}

Json::Value Channel::ReadSpecifyJson(const char *fileName) {
  char szPath[120];
  char szResult[120];
  Json::Value result;
#ifdef WIN32
#ifdef WINCE
  wchar_t wszPath[MAX_PATH];
  GetModuleFileName( NULL, wszPath, MAX_PATH );
  wchar_t *lpwszSplit = wcsrchr(wszPath, '\\');
  *lpwszSplit = 0;
  int nLength = WideCharToMultiByte(CP_ACP, 0, wszPath, -1, NULL, 0, NULL, NULL);
  memset(szPath, 0, sizeof(szPath));
  WideCharToMultiByte(CP_ACP, 0, wszPath, -1, szPath, nLength, NULL, NULL);
#else
  _getcwd(szPath, 120);
#endif
#elif ANDROID
  sprintf(szPath, "%s", CONFIG_DIR);
#else
  getcwd(szPath, 120);
#endif

#ifdef WIN32
  ::sprintf(szResult, "%s\\Config\\%s", szPath, fileName);
#elif ANDROID
  ::sprintf(szResult, "%s/%s", szPath, fileName);
#elif linux
  ::sprintf(szResult, "%s/Config/%s", szPath, fileName);
#else
  ::sprintf(szResult, "%s/%s", szPath, fileName);
#endif

  //staticResult
  std::ifstream ifs;
  ifs.open(szResult);
  if (ifs.is_open()) {
    Json::Reader reader;
    if (!reader.parse(ifs, result, false)) {
      //LOGE("%s read error",fileName);
    }
    ifs.close();
  } else {
    //LOGE("%s can't open",szResult);
  }
  return result;
}

void Channel::onReceiveData(void *pData, int iLength) {
  Json::Value rpc;
  while (m_JsonBuffer.getJsonFromBuffer((char *)pData, iLength, rpc)) {
    onMessage(rpc);
    pData = 0;
    iLength = 0;
  }
}

void Channel::onMessage(Json::Value &jsonObj) {
  LOGD("%s:receive:%s", m_sComponentName.c_str(), jsonObj.toStyledString().data());
  bool run = false;
  // id
  if (jsonObj.isMember("id")) {
    int msgID = jsonObj["id"].asInt();
    if (jsonObj.isMember("result")) {
      if (msgID == m_iIDRegRequest) {
        run = true;
        m_iIDStart = jsonObj["result"].asInt();
        m_iGenerateId = m_iIDStart;
        onRegistered();
      } else if (msgID == m_iIDUnRegRequest) {
        run = true;
        m_iIDUnRegRequest = jsonObj["result"].asInt();
        onUnregistered();
      } else {
        run = true;
        onResult(jsonObj);
      }
    } else if (jsonObj.isMember("error")) {
      run = true;
      onError(jsonObj["error"].asString()); //bug
      //onError(Json::Value(jsonObj["error"]).toStyledString());
    } else {
      run = true;
      onRequest(jsonObj);
    }
  } else {
    run = true;
    onNotification(jsonObj);
  }

  if (!run) {
    //LOGE("NOT USED");
  }
}

void Channel::setStaticResult(std::string attri, std::string ref, Json::Value value) {
  if (m_StaticResult.isMember(attri))
    m_StaticResult[attri][ref] = value;
}

int Channel::RegisterReqId() {
  return m_iIDRegRequest;
}

int Channel::UnRegisterRegId() {
  return m_iIDUnRegRequest;
}

void Channel::unRegisterComponent() {
  Json::Value params;
  params["componentName"] = m_sComponentName;
  sendRequest(m_iIDUnRegRequest, "MB.unregisterComponent", params);
}

void Channel::SetCallback(IMessageInterface *pCallback) {
  m_pCallback = pCallback;
}

void Channel::setSocketManager(ISocketManager *pSocketManager, void *pHandle) {
  m_pSocketManager = pSocketManager;
  m_pHandle = pHandle;
}

std::string	Channel::getChannelName() {
  return m_sComponentName;
}

void Channel::sendError(int resultCode, int id, std::string method, std::string message) {
  Json::Value error;
  Json::Value data;

  data["method"] = method;
  error["code"] = resultCode;
  error["data"] = data;
  error["message"] = message;
  sendError(id, error);
}

void Channel::sendJson(Json::Value &data) {
  LOGD("---send:%s", data.toStyledString().c_str());
  if (NULL == m_pSocketManager) {
    return;
  }
  Json::FastWriter writer;
  std::string json_file = writer.write(data);
  const char *pStr = json_file.c_str();
  m_pSocketManager->SendData(m_pHandle, (void *)pStr, json_file.length());
}

void Channel::onOpen() {
  Json::Value params;
  params["componentName"] = m_sComponentName;
  sendRequest(m_iIDRegRequest, "MB.registerComponent", params);
}

void Channel::onChannelStatus(bool channelStatus)
{
    if(channelStatus)
    {
        onOpen();
        LOGD("%s --- connect sdl . \n" ,m_sComponentName.c_str());
    }
    else
    {
        LOGD("%s --- disconnect sdl . \n" ,m_sComponentName.c_str());
    }
    m_bChannelStatus = channelStatus;
}

bool Channel::getchannelStatus()
{
    return m_bChannelStatus;
}

void Channel::onRegistered() {
}

void Channel::onUnregistered() {

}

int Channel::GenerateId() {
  ++m_iGenerateId;
  if (m_iGenerateId >= m_iIDStart + 1000) {
    m_iGenerateId = m_iIDStart;
  }
  return m_iGenerateId;
}

std::string Channel::MethodName(std::string _mode, Json::Value _method) {
  std::string mode = "";
  std::string method = "";
  std::string mms = _method.asString();
  int pos = mms.find_first_of('.');
  if (std::string::npos == pos) {
    //LOGE("method:find error,%d",pos);
    return method;
  }
  mode = mms.erase(pos);
  if (mode == _mode) {
    method = mms.erase(0, pos + 1);
  } else {
    //LOGE("mode(%s) is not match mode(%s)",mode.c_str(),_mode.c_str());
  }
  return method;
}

void Channel::onRequest(Json::Value &request) {
  int  id = request["id"].asInt();
  Json::Value method = request["method"];


  std::string ref = MethodName(getChannelName(), method);
  LOGD("static string %s , %s",m_StaticResult.toStyledString().c_str(),ref.c_str());



  if (m_StaticResult.isMember(ref)) {
    sendResult(id, ref);
  } else {
    //LOGE("%s.%s NOT use",getChannelName().c_str(),ref.c_str());
  }
}

void Channel::onNotification(Json::Value &data) {
  m_pCallback->onNotification(data);
}

void Channel::onResult(Json::Value &data) {
  m_pCallback->onResult(data);
}

void Channel::onRawData(void *p, int iLength) {
  m_pCallback->onRawData(p, iLength);
}

void Channel::onError(std::string error) {
  m_pCallback->onError(error);
}

void Channel::sendResult(int id, std::string ref, Result code) {
  if (code == RESULT_USER_WAIT)
    return;
  Json::Value result;
  if (m_StaticResult[ref].isMember("result"))
    result = m_StaticResult[ref]["result"];
  else
    result = m_StaticResult[ref];

  result["code"] = code;
  sendResult(id, result);
}

void Channel::sendError(int id, std::string ref, std::string msg, Result code) {
  Json::Value error;
  if (m_StaticResult[ref].isMember("error")) {
    error = m_StaticResult[ref]["error"];
    error["code"] = code;
    error["message"] = msg;
    sendError(id, error);
  } else {
    sendError(code, id, m_sComponentName + "." + ref, msg);
  }
}

void Channel::sendResult(int id, Json::Value &result) {
  Json::Value root;
  root["id"] = id;
  root["jsonrpc"] = "2.0";
  root["result"] = result;
  sendJson(root);
}

void Channel::sendRequest(int id, const std::string mothod, const Json::Value &params) {
  Json::Value root;
  root["id"] = id;
  root["jsonrpc"] = "2.0";
  root["method"] = mothod;
  if (!params.isNull())
    root["params"] = params;
  sendJson(root);
}

void Channel::sendError(int id, Json::Value &error) {
  Json::Value root;
  root["jsonrpc"] = "2.0";
  root["id"] = id;
  root["error"] = error;

  sendJson(root);
}

void Channel::sendNotification(const std::string mothod, const Json::Value &params) {
  Json::Value root;
  root["jsonrpc"] = "2.0";
  root["method"] = mothod;
  if (!params.isNull())
    root["params"] = params;
  sendJson(root);
}

void Channel::SubscribeToNotification(std::string notification) {
  Json::Value params;
  params["propertyName"] = notification;
  sendRequest(GenerateId(), "MB.subscribeTo", params);
}

void Channel::UnsubscribeFromNotification(std::string notification) {
  Json::Value params;
  params["propertyName"] = notification;
  sendRequest(GenerateId(), "MB.unsubscribeTo", params);
}
