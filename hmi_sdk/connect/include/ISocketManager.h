#ifndef ISOCKETMANAGER_H
#define ISOCKETMANAGER_H
#include <string>
#include <vector>
#include "IMessageInterface.h"


class ISocketManager;

class IChannel
{
public:
    virtual std::string	getChannelName() = 0;
    virtual void setSocketManager(ISocketManager * pManager, void * pHandle) = 0;
    virtual void onOpen() = 0;
    virtual void onReceiveData(void * pData, int iLength) = 0;
};

class ISocketManager
{
public:
    virtual bool ConnectTo(std::vector<IChannel *> Channels, INetworkStatus * pNetwork = 0) = 0;
    virtual bool ConnectToVS(IChannel * ChannelVS, std::string sIP, int iPort, INetworkStatus * pNetwork = 0) = 0;
    virtual void SendData(void * pHandle, void * pData, int iLength) = 0;
};

#endif // ISOCKETMANAGER_H
