#ifndef TTSCLIENT_H
#define TTSCLIENT_H

#include "Channel.h"

class TTS : public Channel
{
public:
    TTS();
    ~TTS();
protected:
    void onRequest(Json::Value &);

private:

};

#endif // TTSCLIENT_H
