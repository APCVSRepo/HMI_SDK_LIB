#include <hmi_vr.h>
#include <string>
#include <iostream>
#include "json/json.h"
#include <global_first.h>

VR::VR() : Channel(400,"VR")
{

}

VR::~VR()
{

}

void VR::onRegistered()
{
    SubscribeToNotification("VR.VRCancel");
	SubscribeToNotification("VR.VRStatus");
	SubscribeToNotification("VR.VRCommandHelp");
	SubscribeToNotification("VR.VRCommandTTS");
	SubscribeToNotification("VR.VRExitApp");
	SubscribeToNotification("VR.VRSwitchApp");
	SubscribeToNotification("VR.VRResult");
}

void VR::onUnregistered()
{
    UnsubscribeFromNotification("VR.VRCancel");
	UnsubscribeFromNotification("VR.VRStatus");
	UnsubscribeFromNotification("VR.VRCommandHelp");
	UnsubscribeFromNotification("VR.VRCommandTTS");
	UnsubscribeFromNotification("VR.VRExitApp");
	UnsubscribeFromNotification("VR.VRSwitchApp");
	UnsubscribeFromNotification("VR.VRResult");
}

void VR::onRequest(Json::Value &request)
{
    std::string method = request["method"].asString();
    int id = request["id"].asInt();
    if (method == "VR.GetSupportedLanguages") {
        sendResult(id,"GetSupportedLanguages");
    }else if (method == "VR.GetLanguage") {
        sendResult(id,"GetLanguage");
    }else if (method == "VR.ChangeRegistration") {
        sendResult(id,"ChangeRegistration");
    }else if (method == "VR.IsReady") {
        sendResult(id,"IsReady");
    }else if (method == "VR.GetCapabilities") {
        sendResult(id,"GetCapabilities");
    }else if (method == "VR.AddCommand") {
        Result result=m_pCallback->onRequest(request);
        sendResult(id,"AddCommand",result);
    }else if (method == "VR.DeleteCommand") {
        Result result=m_pCallback->onRequest(request);
        sendResult(id,"DeleteCommand",result);
    }else if (method=="VR.PerformInteraction") {
        Result result=m_pCallback->onRequest(request);
        sendResult(id,"PerformInteraction",result);
    } else {
        Channel::onRequest(request);
    }
}

