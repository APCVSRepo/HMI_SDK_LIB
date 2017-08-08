#ifndef UICLIENT_H_
#define UICLIENT_H_

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

#endif // UICLIENT_H_
