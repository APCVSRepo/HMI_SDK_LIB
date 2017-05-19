#ifndef UICLIENT_H
#define UICLIENT_H

#include <json/json.h>
#include "ISocketManager.h"
#include "Channel.h"


class UI : public Channel
{
public:
    UI();
    ~UI();
protected:
    void onRegistered();
    void onUnregistered();
    void onRequest(Json::Value &);

private:

    Json::Value startRecordingNotify(Json::Value &);

public:
    void onSystemContext(std::string systemContext);
};

#endif // UICLIENT_H
