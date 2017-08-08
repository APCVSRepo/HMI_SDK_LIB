#ifndef BASE_COMMUNICATIONCLIENT_H_
#define BASE_COMMUNICATIONCLIENT_H_

#include "hmi_channel.h"

class BasicCommunication : public Channel
{
public:
    BasicCommunication();
    ~BasicCommunication();
protected:
    void onRegistered();
    void onUnregistered();

public:
    void onRequest(Json::Value &);
    void onNotification(Json::Value &);

private:

};

#endif // BASE_COMMUNICATIONCLIENT_H_

