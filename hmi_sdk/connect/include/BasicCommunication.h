#ifndef BASECOMMUNICATIONCLIENT_H
#define BASECOMMUNICATIONCLIENT_H

#include <json/json.h>

#include "Channel.h"

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

#endif // BASECOMMUNICATIONCLIENT_H

