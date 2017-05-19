#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>

#include <HMISDK/include/json/json.h>

#include "HMISDK/include/connect/ClientSocket.h"

class BaseConnectThread : public QThread
{
    Q_OBJECT
public:
    BaseConnectThread();
    ~BaseConnectThread();
    void send(std::string);
    void disconnect();
    void closeWs();
    void connecto();

    void setHost(std::string m_sHost, int m_iPort);

protected:
    virtual void onRegistered();
    virtual void onUnregistered();
    virtual void onReady();

    virtual void onRequest(Json::Value);
    virtual void onNotification(Json::Value);
    virtual void onResult(Json::Value);

    virtual void run();

    void onOpen();
    void onMessage(Json::Value);
    void onError(std::string);
    void onClose();
    void onDisconnected();

    void registerComponent();
    void unregisterComponent();
    void subscribeToNotification(std::string);
    void unsubscribeFromNotification(std::string);
    void generateId();

    void sendResult();

    void sendError(int resultCode, int id, std::string method, std::string message);

    int m_iIDStart;
    int m_iRequestId;
    int m_iRegisterRequestId;
    int m_iUnregisterRequestId;
    int m_iIDRange;
    std::string m_sComponentName;
    int m_iAppID;

    std::string m_sHost;
    int m_iPort;
    ClientSocket m_Client_socket;

    Json::Value m_StaticConfigJson;
    Json::Value m_ResultCodeJson;

private:

};

#endif // WORKTHREAD_H
