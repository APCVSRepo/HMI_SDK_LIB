#ifndef CVIDEOSTREAM_H
#define CVIDEOSTREAM_H

#include "Channel.h"

class CVideoStream : public Channel
{
public:
    CVideoStream();
    ~CVideoStream();
protected:
    void onRegistered();
    void onUnregistered();
    void onReceiveData(void * pData, int iLength);

public:
    void onRequest(Json::Value &);
    void onNotification(Json::Value &);

private:
};

#endif // CVIDEOSTREAM_H
