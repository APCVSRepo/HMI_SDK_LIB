#ifndef TTSCLIENT_H_
#define TTSCLIENT_H_

#include "hmi_channel.h"

class TTS : public Channel
{
public:
    TTS();
    ~TTS();
protected:
    void onRequest(Json::Value &);

private:

};

#endif // TTSCLIENT_H_
