#ifndef TTSCLIENT_H_
#define TTSCLIENT_H_

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

#endif // TTSCLIENT_H_
