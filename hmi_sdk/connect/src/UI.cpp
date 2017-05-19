#include <global_first.h>
#include <UI.h>

#include <iostream>
#include <string>
#include "json/json.h"
//#include "Config/Config.h"

UI::UI() : Channel(600,"UI")
{

}

UI::~UI()
{

}

void UI::onRegistered()
{
    SubscribeToNotification("UI.ShowNotification");
    SubscribeToNotification("UI.CreateInteractionChoiceSet");
    SubscribeToNotification("UI.DeleteInteractionChoiceSet");
    SubscribeToNotification("UI.SubscribeButton");
    SubscribeToNotification("UI.UnsubscribeButton");
    SubscribeToNotification("UI.OnRecordStart");
}

void UI::onUnregistered()
{
    UnsubscribeFromNotification("UI.ShowNotification");
    UnsubscribeFromNotification("UI.CreateInteractionChoiceSet");
    UnsubscribeFromNotification("UI.DeleteInteractionChoiceSet");
    UnsubscribeFromNotification("UI.SubscribeButton");
    UnsubscribeFromNotification("UI.UnsubscribeButton");
}



void UI::onRequest(Json::Value &request)
{
    std::string method = request["method"].asString();
    int id = request["id"].asInt();
    if (method == "UI.SetGlobalProperties") {
        sendResult(id,"SetGlobalProperties");
    }else if (method == "UI.ResetGlobalProperties") {
        sendResult(id,"ResetGlobalProperties");
    }else if (method == "UI.ChangeRegistration") {
        sendResult(id,"ChangeRegistration");
    }else if (method == "UI.SetAppIcon") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"SetAppIcon",result);
        //sendResult(id,"SetAppIcon");
    }else if (method == "UI.GetSupportedLanguages") {
        sendResult(id,"GetSupportedLanguages");
    }else if (method == "UI.GetLanguage") {
        sendResult(id,"GetLanguage");
    }else if (method == "UI.GetCapabilities") {
        sendResult(id,"GetCapabilities");
    }else if (method == "UI.IsReady") {
        sendResult(id,"IsReady");
    }else if (method == "UI.ClosePopUp") {
        sendResult(id,"ClosePopUp");
    }else if (method == "UI.ShowVrHelp") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"ShowVrHelp",result);
    }else if (method == "UI.Alert") {
        Result result = m_pCallback->onRequest(request);
		if (result == RESULT_USER_WAIT)
			return;
        sendError(4,id,"UI.Alert","too many pending request");
        Json::Value params;
        params["systemContext"] = "MAIN";
        sendNotification("UI.OnSystemContext",params);
    }else if (method == "UI.Show") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"Show",result);
    }else if (method=="UI.ScrollableMessage") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"ScrollableMessage",result);
    }else if (method == "UI.AddCommand") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"AddCommand",result);
    }else if (method == "UI.DeleteCommand") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"DeleteCommand",result);
    }else if (method == "UI.AddSubMenu") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"AddSubMenu",result);
    }else if (method == "UI.DeleteSubMenu") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"DeleteSubMenu",result);
    }else if (method == "UI.PerformInteraction") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"PerformInteraction",result);
    }else if (method == "UI.SetMediaClockTimer") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"SetMediaClockTimer",result);
    }else if (method == "UI.PerformAudioPassThru") {
        m_pCallback->onRequest(request);
        sendNotification("UI.PerformAudioPassThruStart",startRecordingNotify(request));
    }else if (method == "UI.EndAudioPassThru") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"EndAudioPassThru",result);
    }else if (method == "UI.Slider") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"Slider",result);
    } else {
        Channel::onRequest(request);
    }
}


void UI::onSystemContext(std::string systemContext)
{
    Json::Value params;
    params["systemContext"] = systemContext;
    sendNotification("UI.OnSystemContext",params);
}


Json::Value UI::startRecordingNotify(Json::Value &request)
{
    Json::Value request_params;
    Json::Value params;
    request_params = request["params"];
    if (request_params.isMember("samplingRate")) {
        params["samplingRate"] = request_params["samplingRate"];
    }
    if (request_params.isMember("bitsPerSample")) {
        params["bitsPerSample"] = request_params["bitsPerSample"];
    }
    if (request_params.isMember("appID")) {
        params["appID"] = request_params["appID"];
    }
    if (request_params.isMember("audioType")) {
        params["audioType"] = request_params["audioType"];
    }
    if (request_params.isMember("maxDuration")) {
        params["maxDuration"] = request_params["maxDuration"];
    }
    params["audioPassThruType"] = "RECORD_SEND";
    params["saveAudioPassThruFile"] = "-";
    params["sendAudioPassThruFile"] = "-";
    return params;
}
