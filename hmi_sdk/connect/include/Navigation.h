#ifndef NAVIGATIONCLIENT_H
#define NAVIGATIONCLIENT_H


#include "json/json.h"
#include "ISocketManager.h"
#include "Channel.h"

class Navigation : public Channel
{
public:
    Navigation();
    ~Navigation();
protected:
    void onRequest(Json::Value &);

private:

};

#endif // NAVIGATIONCLIENT_H
