/**
* @file			websocket_to_sdl
* @brief		管理hmi与sdl交互的各个通道，关联每个通道和对应的socket，进行数据流程的转发以及与sdl连接状态的管理
* @author		zenghuan
* @date			2018-7-18
* @version		A001
* @copyright	ford
*/

#include <websocket_to_sdl.h>
#ifdef OS_WIN32
#ifdef WINCE
#pragma comment(lib,"ws2.lib")
#else
#pragma comment(lib,"ws2_32.lib")
#endif
#else
#include <sys/select.h>
#include <errno.h>
#include <fcntl.h>
#include <memory.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#endif
#include "global_first.h"
#include "hmi_channel.h"

namespace hmisdk {

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

WebsocketToSDL::WebsocketToSDL()
  :	m_iReadSign(-1),
    m_iWriteSign(-1),
    m_SendThread(),
    m_bTerminate(false)
{
  m_sHost = "127.0.0.1";
  m_iPort = 8087;

#ifdef WIN32
  WSADATA wsa = { 0 };
  WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

WebsocketToSDL::~WebsocketToSDL() {
  m_bTerminate = true;
  Notify();
  pthread_join(m_SendThread, 0);

  CloseSockets();
}

void WebsocketToSDL::CloseSockets() {
  if (-1 != m_iReadSign)
#if defined(WIN32)
    closesocket(m_iReadSign);
#else
    close(m_iReadSign);
#endif

  if (-1 != m_iWriteSign)
#ifdef WIN32
    closesocket(m_iWriteSign);
#else
    close(m_iWriteSign);
#endif

  m_iReadSign = -1;
  m_iWriteSign = -1;
  m_bTerminate = true;

  int iNum = m_SocketHandles.size();
  for (int i = 0; i < iNum; ++i) {
    CWebSockHandle *pHandle = m_SocketHandles[i];
    pHandle->Close();
    delete pHandle;
  }
  m_SocketHandles.clear();
}

void WebsocketToSDL::Notify() {
  if (-1 == m_iWriteSign)
    return;

  char c = 0;
  ::send(m_iWriteSign, (const char *)&c, 1, 0);
}

bool WebsocketToSDL::CreateSignal() {
  int tcp1, tcp2;
  sockaddr_in name;
  memset(&name, 0, sizeof(name));
  name.sin_family = AF_INET;
  name.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
#ifdef WIN32
  int namelen = sizeof(name);
#else
  size_t namelen = sizeof(name);;
#endif

  tcp1 = tcp2 = -1;
  int tcp = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp == -1) {
    goto clean;
  }
  if (bind(tcp, (sockaddr *)&name, namelen) == -1) {
    goto clean;
  }
  if (::listen(tcp, 5) == -1) {
    goto clean;
  }
#ifdef WIN32
  if (getsockname(tcp, (sockaddr *)&name, &namelen) == -1) {
#else
  if (getsockname(tcp, (sockaddr *)&name, (socklen_t *)&namelen) == -1) {
#endif
    goto clean;
  }
  tcp1 = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp1 == -1) {
    goto clean;
  }
  if (-1 == connect(tcp1, (sockaddr *)&name, namelen)) {
    goto clean;
  }
#ifdef WIN32
  tcp2 = accept(tcp, (sockaddr *)&name, &namelen);
#else
  tcp2 = accept(tcp, (sockaddr *)&name, (socklen_t *)&namelen);
#endif
  if (tcp2 == -1) {
    goto clean;
  }
#ifdef WIN32
  if (closesocket(tcp) == -1) {
#else
  if (close(tcp) == -1) {
#endif
    goto clean;
  }
  m_iWriteSign = tcp1;
  m_iReadSign = tcp2;
#ifdef WIN32
  {
    u_long iMode = 1;
    ioctlsocket(m_iReadSign, FIONBIO, (u_long FAR *) &iMode);
  }
#else
#include<fcntl.h>
  fcntl(m_iReadSign, F_SETFL, O_NONBLOCK);
#endif
  return true;

clean:
  if (tcp != -1) {
#ifdef WIN32
    closesocket(tcp);
#else
    close(tcp);
#endif
  }
  if (tcp2 != -1) {
#ifdef WIN32
    closesocket(tcp2);
#else
    close(tcp2);
#endif
  }
  if (tcp1 != -1) {
#ifdef WIN32
    closesocket(tcp1);
#else
    close(tcp1);
#endif
  }
  return false;
}

void *StartSocketThread(void *p) {
  WebsocketToSDL *pThis = (WebsocketToSDL *)p;
  pThis->RunThread();
  return 0;
}

bool WebsocketToSDL::ConnectTo(std::vector<IChannel *> Channels, INetworkStatus *pNetwork) {
  m_pNetwork = pNetwork;
  if (!CreateSignal())
    return false;

  // add by fanqiang read sdl host address
  if (!g_StaticConfigJson.isNull()) {
    Json::Value sdladdr = g_StaticConfigJson["SDLAddr"];
    if (sdladdr.isMember("host"))
      m_sHost = sdladdr["host"].asCString();
    if (sdladdr.isMember("port"))
      m_iPort = sdladdr["port"].asInt();
  }

  int iNum = Channels.size();
  for (int i = 0; i < iNum; ++i) {
    CWebSockHandle *pHandle = new CWebSockHandle(1024);
    if (pHandle->Connect(Channels[i], m_sHost, m_iPort)) {
      m_SocketHandles.push_back(pHandle);
      Channels[i]->setSocketManager(this, pHandle);
    } else {
      goto FAILED;
    }
  }

  m_bTerminate = false;
  if (0 != pthread_create(&m_SendThread, 0, &StartSocketThread, this))
    goto FAILED;

  return true;

FAILED:
  CloseSockets();
  return false;
}

bool WebsocketToSDL::ConnectToVS( IChannel *ChannelVS, std::string sIP, int iPort, INetworkStatus *pNetwork) {
  m_pNetwork = pNetwork;

  CWebSockHandle *pHandle = new CWebSockHandle(576000);
  if (pHandle->Connect(ChannelVS, sIP, iPort)) {
    m_SocketHandles.push_back(pHandle);
    ChannelVS->setSocketManager(this, pHandle);
    Notify();
    return true;
  } else {
    return false;
  }
}

void WebsocketToSDL::DelConnectToVS() {
  CWebSockHandle *pHandle = m_SocketHandles.at(m_SocketHandles.size() - 1);

  m_SocketHandles.pop_back();
  Notify();
#ifdef WIN32
  Sleep(1000);
#else
  usleep(1000000);
#endif
//    shutdown(pHandle->m_i_socket, SHUT_RDWR);
  pHandle->Close();
}

void WebsocketToSDL::SendData(void *pHandle, void *pData, int iLength) {
  if (m_bTerminate)
    return;
  CWebSockHandle *p = (CWebSockHandle *)pHandle;
  std::string data = std::string((char*)pData);
  p->PushData(data);
  Notify();
}

void WebsocketToSDL::RunThread() {
#ifdef WIN32
  FD_SET fdRead;
  int fd_max = -1;
#else
  fd_set fdRead;
  fd_set fdWrite;
  int fd_max = m_iReadSign;
#endif
  while (!m_bTerminate) {

    FD_ZERO(&fdRead);
#ifndef WIN32
    FD_ZERO(&fdWrite);
#endif

    int iNum = m_SocketHandles.size();
    FD_SET(m_iReadSign, &fdRead);

#ifdef WIN32
    if (select(0, &fdRead, NULL, NULL, NULL) == SOCKET_ERROR) {
#else
    if (select(fd_max + 1, &fdRead, &fdWrite, NULL, NULL) == SOCKET_ERROR) {
#endif
      goto SOCKET_WRONG;
    }

    bool bSend = FD_ISSET(m_iReadSign, &fdRead);
    if (bSend) {
      unsigned char buffer[8];
      int bytes_read = 0;
      do {
        bytes_read = recv(m_iReadSign, (char *)buffer, sizeof(buffer), 0);
      } while (bytes_read > 0);
      iNum = m_SocketHandles.size();
      for (int i = 0; i < iNum; ++i) {
        if (i + 1 > m_SocketHandles.size()) {
          break;
        }
        CWebSockHandle *pHandle = m_SocketHandles[i];
        if (!pHandle->SendData())
          goto SOCKET_WRONG;
      }
    }
  }
  return;

SOCKET_WRONG:
  m_bTerminate = true;
  CloseSockets();

  if (m_pNetwork)
    m_pNetwork->onNetworkBroken();
  return;
}

bool WebsocketToSDL::CheckConnect()
{
    for (int i = 0; i < m_SocketHandles.size(); ++i) {
        if(!m_SocketHandles[i]->ConnectStatus())
        {
            return false;
        }
    }
    LOGD("CheckConnect is success. \n");
    return true;
}

CWebSockHandle::CWebSockHandle(int bufSize)
  : m_SendMutex()
  , m_WSThread(NULL)
  , m_CheckThread(NULL)
{
  m_bCheck = false;
  m_iBufSize = bufSize;
  pthread_mutex_init(&m_SendMutex, 0);
}


CWebSockHandle::~CWebSockHandle() {
  pthread_mutex_destroy(&m_SendMutex);
  if(NULL != m_WSThread)
  {
      m_WSThread->join();
      delete m_WSThread;
      m_WSThread = NULL;
  }
  if(NULL != m_CheckThread)
  {
      m_CheckThread->join();
      delete m_CheckThread;
      m_CheckThread = NULL;
  }
}

bool CWebSockHandle::Connect(IChannel *newChannel, std::string sIP, int iPort) {
  pDataReceiver = newChannel;
  Ip = sIP;
  Port = iPort;
  m_WSSession = std::make_shared<CWebsocketSession>(m_ioc);
  m_WSSession->ConnectChannle(newChannel);
  bool ret = m_WSSession->run(sIP.c_str(), std::to_string(iPort).c_str());
  if(ret)
  {
    if(NULL != m_WSThread)
    {
      m_WSThread->join();
      delete m_WSThread;
      m_WSThread = NULL;
    }
    m_WSThread = new std::thread(&CWebSockHandle::RunThread, this);
    m_bCheck = true;
    if(NULL == m_CheckThread)
    {
        m_CheckThread = new std::thread(&CWebSockHandle::CheckThread, this);
    }
    return true;
  }
  return false;
}
void CWebSockHandle::PushData(std::string &message)
{
    pthread_mutex_lock(&m_SendMutex);
    std::shared_ptr<std::string> message_ptr = std::make_shared<std::string>(message);
    m_SendData.push(message_ptr);
    pthread_mutex_unlock(&m_SendMutex);
}

bool CWebSockHandle::SendData() {

  bool bRet = true;
  pthread_mutex_lock(&m_SendMutex);
  while (!this->m_SendData.empty()) {
     Message message_ptr;
     message_ptr= this->m_SendData.front();
    try {
          m_WSSession->SendData(*message_ptr);
          this->m_SendData.pop();
    } catch (...) {
      bRet = false;
      break;
    }
  }
  pthread_mutex_unlock(&m_SendMutex);
  return bRet;
}

void CWebSockHandle::Close() {
  m_CheckThread->join();
  m_WSThread->join();
  m_WSSession->close();
  while (!this->m_SendData.empty()) {
    Message message_ptr;
    message_ptr = this->m_SendData.front();
    this->m_SendData.pop();
  }
}

void CWebSockHandle::RunThread()
{
    LOGD("---CWebSockHandle:RunThread enter .");
    m_ioc.run();
    if(NULL != m_WSSession)
    {
        LOGD("---CWebSockHandle:channle disconnect .\n");
        m_WSSession->setConnectStatus(false);
    }
    m_ioc.restart();
    m_bCheck = false;
    LOGD("---CWebSockHandle:RunThread exit .");
}

void CWebSockHandle::CheckThread()
{
    while (true) {
   // LOGD("CheckThread result %d .",Check());
    if(!Check())
    {
      Connect(pDataReceiver,Ip,Port);

    }
#ifdef WIN32
    Sleep(2000);
#else
    sleep(2);
#endif
    }
}

bool CWebSockHandle::Check()
{
    return m_bCheck;
}

bool CWebSockHandle::ConnectStatus()
{
    if(NULL != pDataReceiver)
    {
        return pDataReceiver->getchannelStatus();
    }

    return false;
}

IChannel *CWebSockHandle::Channle()
{
    return pDataReceiver;
}

}
