#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "ISocketManager.h"
#include "IMessageInterface.h"
#include <vector>
#ifdef ANDROID
#include <unistd.h>
#endif

class JsonBuffer
{
public:
	JsonBuffer();

	bool getJsonFromBuffer(char * pData, int iLength, Json::Value& output);

private:
	std::string m_szBuffer;
};


extern Json::Value g_StaticConfigJson;
extern Json::Value g_VehicleInfoJson;
extern Json::Value g_StaticResultJson;

class ISocketManager;

class Channel:public IChannel
{
public:
    Channel(int startId,std::string Channelname);
    virtual ~Channel();

    static Json::Value ReadSpecifyJson(const char *fileName);
    static void ReadConfigJson();

    void SetCallback(IMessageInterface * pCallback);

    void onReceiveData(void * pData, int iLength);

    int RegisterReqId();
    int UnRegisterRegId();
	std::string	getChannelName();
    void setSocketManager(ISocketManager * pManager,void *pHandle=NULL);
	void onOpen();

protected:

	void unRegisterComponent();
	void sendError(int resultCode, int id, std::string method, std::string message);

	void SubscribeToNotification(std::string notification);
	void UnsubscribeFromNotification(std::string notification);

    void onMessage(Json::Value &jsonObj);

public:
	//IMessageCallback
    virtual void onRequest(Json::Value &);
    virtual void onNotification(Json::Value &);
    virtual void onResult(Json::Value &);
	virtual void onRawData(void * p, int iLength);
	virtual void onError(std::string error);
    void SendJson(Json::Value &data);
    virtual void sendError(int id,Json::Value &error);
    virtual void sendResult(int id,Json::Value &result);
    virtual void sendRequest(int id,const std::string mothod,const Json::Value &params=Json::Value::null);
    virtual void sendNotification(const std::string mothod,const Json::Value &params=Json::Value::null);
    virtual void onRegistered();
	virtual void onUnregistered();

    virtual void SetStaticResult(std::string attri,std::string ref,Json::Value value);
    virtual void sendResult(int id,std::string ref,Result code=RESULT_SUCCESS);
    virtual void sendError(int id,std::string ref,std::string message,Result code = RESULT_REJECTED);

    int GenerateId();
    std::string MethodName(std::string _mode,Json::Value _method);
protected:


protected:
    IMessageInterface * m_pCallback;
    ISocketManager * m_pSocketManager;
    void * m_pHandle;
private:

    int m_iIDRegRequest;
    int m_iIDUnRegRequest;
    int m_iIDStart;
    int m_iGenerateId;
	std::string m_sComponentName;

    Json::Value  m_StaticResult;

    JsonBuffer m_JsonBuffer;

};

#endif
