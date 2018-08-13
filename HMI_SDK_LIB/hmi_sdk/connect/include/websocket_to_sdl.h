/**
* @file			websocket_to_sdl
* @brief		管理hmi与sdl交互的各个通道，关联每个通道和对应的socket，进行数据流程的转发以及与sdl连接状态的管理
* @author		zenghuan
* @date			2018-7-18
* @version		A001
* @copyright	ford
*/

#ifndef WEBSOCKET_TO_SDL_H_
#define WEBSOCKET_TO_SDL_H_

#ifdef WIN32
#include <WINSOCK2.H>
#endif
#include <pthread.h>
#include <queue>
#include "socket_manager_interface.h"

#include <thread>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include "WS_Session.h"

namespace hmisdk {

typedef std::shared_ptr<std::string> Message;

class CWebSockHandle{
 public:
  CWebSockHandle(int bufSize = 1024);
  ~CWebSockHandle();
  bool Connect(IChannel *newChannel, std::string sIP, int iPort);
  void PushData(std::string & message);
  bool SendData();
  void Close();
  void RunThread();
  void CheckThread();
  bool Check();
  bool ConnectStatus();
  IChannel *Channle();

 private:

  boost::asio::io_context m_ioc;
  std::shared_ptr<CWebsocketSession> m_WSSession;
  std::thread* m_WSThread;
  std::thread* m_CheckThread;
  std::queue<Message> m_SendData;
  IChannel *pDataReceiver;
  std::string Ip;
  int Port;
  bool m_bCheck;
  int m_iBufSize;
  mutable pthread_mutex_t m_SendMutex;
};

class WebsocketToSDL : public ISocketManager {
 public:
  WebsocketToSDL();
  virtual ~WebsocketToSDL();

 public:
  bool ConnectTo(std::vector<IChannel *> Channels, INetworkStatus *pNetwork = 0);
  bool ConnectToVS(IChannel *ChannelVS, std::string sIP, int iPort, INetworkStatus *pNetwork = 0);
  void DelConnectToVS();
  void SendData(void *pHandle, void *pData, int iLength);
  void RunThread();
  bool CheckConnect();

 private:
  bool CreateSignal();
  void Notify();
  void CloseSockets();



 private:
  int m_iReadSign;
  int m_iWriteSign;

  mutable pthread_mutex_t m_SendMutex;
  pthread_t m_SendThread;
  std::thread* m_ConnectThread;
  bool m_bTerminate;

  INetworkStatus *m_pNetwork;
 private:
  std::string m_sHost;
  int m_iPort;

  std::vector<CWebSockHandle *> m_SocketHandles;
};

}

#endif // WEBSOCKET_TO_SDL_H_

