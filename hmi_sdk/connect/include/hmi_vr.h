#ifndef VRCLIENT_H_
#define VRCLIENT_H_

#include "hmi_channel.h"

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

#endif // VRCLIENT_H_
