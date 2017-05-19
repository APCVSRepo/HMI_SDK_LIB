#ifndef VRCLIENT_H
#define VRCLIENT_H

#include "ISocketManager.h"
#include "Channel.h"

class VR : public Channel
{
public:
    VR();
    ~VR();
protected:
    void onRegistered();
    void onUnregistered();

    void onRequest(Json::Value &);

private:

};

#endif // VRCLIENT_H
