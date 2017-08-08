#ifndef BUTTONSCLIENT_H_
#define BUTTONSCLIENT_H_

#include "hmi_channel.h"

class Buttons : public Channel
{
public:
    Buttons();
    ~Buttons();
public:
    void onRequest(Json::Value &);

private:
};

#endif // BUTTONSCLIENT_H_
