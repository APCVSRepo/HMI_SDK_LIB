#ifndef UIINTERFACE_H
#define UIINTERFACE_H
#include "AppDataInterface.h"
#include "AppCommon.h"


class UIInterface
{
public:
    virtual void onAppActive() = 0;
    virtual void onAppStop() = 0;
    virtual void onAppShow(int type) = 0;
    virtual void onAppUnregister(int appId) = 0;
    virtual void onVideoStreamStart() = 0;
    virtual void onVideoStreamStop() = 0;
    virtual void OnEndAudioPassThru() = 0;

    virtual void tsSpeak(int VRID, std::string strText) = 0;
    virtual void ShowDeviceList() = 0;
    virtual void SetSDLStatus(bool bConnect) = 0;
};

#endif // UIINTERFACE_H
