/**
* @file			sockets_to_sdl
* @brief		hmi与sdl底层通信层，使用socket方式进行数据交互，发送和接收原始数据，每个通道对应一个socket进行单独的数据交互
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef SOCKETS_TO_SDL_H_
#define SOCKETS_TO_SDL_H_

#ifdef WIN32
#include <WINSOCK2.H>
#endif
#include <pthread.h>
#include <queue>
#include "socket_manager_interface.h"

typedef struct _SEND_DATA {
  void *pData;
  int iLength;
} SEND_DATA;

class CSockHandle {
 public:
  CSockHandle(int bufSize = 1024);
  ~CSockHandle();
  bool Connect(IChannel *newChannel, std::string sIP, int iPort);
  void PushData(void *pData, int iLength);
  bool SendData();
  bool RecvData();
  void Close();
  int GetSocketID();
 private:
  IChannel *pDataReceiver;
  int m_iSocket;
  std::queue<SEND_DATA> m_SendData;

  unsigned char *m_pRecBuf;
  int m_iBufSize;

  mutable pthread_mutex_t m_SendMutex;
};

class SocketsToSDL : public ISocketManager {
 public:
  SocketsToSDL();
  virtual ~SocketsToSDL();

 public:
  bool ConnectTo(std::vector<IChannel *> Channels, INetworkStatus *pNetwork = 0);
  bool ConnectToVS(IChannel *ChannelVS, std::string sIP, int iPort, INetworkStatus *pNetwork = 0);
  void DelConnectToVS();
  void SendData(void *pHandle, void *pData, int iLength);
  void RunThread();

 private:
  bool CreateSignal();
  void Notify();
  void CloseSockets();

 private:
  int m_iReadSign;
  int m_iWriteSign;

  mutable pthread_mutex_t m_SendMutex;
  pthread_t m_SendThread;
  bool m_bTerminate;

  INetworkStatus *m_pNetwork;

 private:
  std::string m_sHost;
  int m_iPort;

  std::vector<CSockHandle *> m_SocketHandles;
};

#endif // SOCKETS_TO_SDL_H_

