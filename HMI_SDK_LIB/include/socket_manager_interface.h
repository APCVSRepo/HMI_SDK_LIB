/**
* @file			message_interface
* @brief		定义通道及socket通信的基本接口函数
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef ISOCKETMANAGER_H
#define ISOCKETMANAGER_H
#include <string>
#include <vector>
#include "message_interface.h"


class ISocketManager;

class IChannel {
 public:
  virtual std::string	getChannelName() = 0;
  virtual void setSocketManager(ISocketManager *pManager, void *pHandle) = 0;
  virtual void onOpen() = 0;
  virtual void onReceiveData(void *pData, int iLength) = 0;
};

class ISocketManager {
 public:
  virtual bool ConnectTo(std::vector<IChannel *> Channels, INetworkStatus *pNetwork = 0) = 0;
  virtual bool ConnectToVS(IChannel *ChannelVS, std::string sIP, int iPort, INetworkStatus *pNetwork = 0) = 0;
  virtual void SendData(void *pHandle, void *pData, int iLength) = 0;
};

#endif // ISOCKETMANAGER_H
