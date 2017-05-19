#ifndef IMESSAGEINTERFACE_H
#define IMESSAGEINTERFACE_H

#include "json/json.h"
#include <string>
#include "AppCommon.h"
//#define _D(msg, args...) //fprintf(stderr,"[lk]-%s-%s():%d: " msg, __FILE__, __FUNCTION__, __LINE__, ##args)

class IMessageInterface
{
public:
    virtual Result onRequest(Json::Value) = 0;
    virtual void onNotification(Json::Value) = 0;
    virtual void onResult(Json::Value) = 0;
    virtual void onRawData(void * p, int iLength) = 0;
    virtual void onError(std::string error) = 0;
};

class INetworkStatus
{
public:
    virtual void onConnected() = 0;
    virtual void onNetworkBroken() = 0;
};

#endif // IMESSAGEINTERFACE_H
