#ifndef NAVIGATIONCLIENT_H_
#define NAVIGATIONCLIENT_H_

#include "hmi_channel.h"

class Navigation : public Channel
{
public:
    Navigation();
    ~Navigation();
protected:
    void onRequest(Json::Value &);

private:

};

#endif // NAVIGATIONCLIENT_H_
