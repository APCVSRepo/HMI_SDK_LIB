/**
* @file			hmi_tts  
* @brief		TTS语音播放通道，处理SDL发送的TTS相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21 
* @version		A001 
* @copyright	ford                                                              
*/

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
