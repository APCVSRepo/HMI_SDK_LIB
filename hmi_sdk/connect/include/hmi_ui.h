/**
* @file			hmi_ui  
* @brief		UI画面显示通道，处理SDL发送的UI相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21 
* @version		A001 
* @copyright	ford                                                              
*/

#ifndef UICLIENT_H_
#define UICLIENT_H_

#include "hmi_channel.h"

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
