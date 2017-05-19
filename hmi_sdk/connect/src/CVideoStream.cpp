#include "CVideoStream.h"

CVideoStream::CVideoStream() : Channel(900,"VideoStream")
{

}

CVideoStream::~CVideoStream()
{

}

void CVideoStream::onRegistered()
{

}

void CVideoStream::onUnregistered()
{

}

void CVideoStream::onReceiveData(void * pData, int iLength)
{
    m_pCallback->onRawData(pData, iLength);
}

void CVideoStream::onRequest(Json::Value &request)
{

}
void CVideoStream::onNotification(Json::Value &jsonObj)
{

}
